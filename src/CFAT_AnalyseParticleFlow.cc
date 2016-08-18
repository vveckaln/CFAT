#include "ColourFlowAnalysisTool.hh"
#include "ParticleFlowTools.hh"
#include "Definitions.hh"
#include "CFAT_Core.hh"
using namespace Definitions;
void ColourFlowAnalysisTool::AnalyseParticleFlow() const
{
  if (not GetEvent() -> GetVector(HAD_B))
    return;
  const static unsigned char Nplanes = 3;
  const static unsigned char Njets = 3;
  const TVector3 leading_light_jet_v3 = GetEvent() -> GetVector(LEADING_JET) -> Vect();
  
  const TVector3 second_leading_light_jet_v3 = GetEvent() -> GetVector(SCND_LEADING_JET) -> Vect();
  const TVector3 had_b_jet_v3 = GetEvent() -> GetVector(HAD_B) -> Vect();
  ;
  
  Plane plane_q1q2(leading_light_jet_v3, second_leading_light_jet_v3);
  const double angle1 = leading_light_jet_v3.Angle(had_b_jet_v3);
  const double angle2 = second_leading_light_jet_v3.Angle(had_b_jet_v3);
  
  const TVector3 * q_closer = & leading_light_jet_v3;
  VectorCode_t q_closer_index = LEADING_JET;
  const TVector3 * q_further = & second_leading_light_jet_v3;
  VectorCode_t q_further_index = SCND_LEADING_JET;
  if (angle1 > angle2)
    {
      q_closer = & second_leading_light_jet_v3;
      q_closer_index = SCND_LEADING_JET;
      q_further = & leading_light_jet_v3;
      q_further_index = LEADING_JET;
      plane_q1q2.SwitchDef();
    }

  const Plane plane_hadb_qcloser(had_b_jet_v3, *q_closer );
  const Plane plane_hadb_qfurther(*q_further, had_b_jet_v3);
  const Plane * planes[Nplanes] = {&plane_hadb_qcloser, &plane_q1q2, & plane_hadb_qfurther};
  CFAT_Core * core = GetEvent() -> GetCore();
  for (ChargeCode_t charge_code = 0; charge_code < N_charge_types_; charge_code ++)
    {
      for (WorkCode_t work_code = 0; work_code < N_levels_types_; work_code ++)
	{
	  
	  for (CFAT_Core::pf_iter it = core -> begin(); it != core -> end(); it ++)
	    {
	      if (charge_code == CHARGED and it -> GetCharge() == 0)
		continue;
	      const  TVector3 particle_v3 = it -> GetLorentzVector().Vect();

	      for (unsigned char particle_code = 0; particle_code < N_particles_types_; particle_code ++)
		{
		  for (unsigned char plane_index = 0; plane_index < Nplanes; plane_index ++)
		    {
		      const Plane *plane = planes[plane_index];
		      const TVector3 projection = plane -> Project(particle_v3);
		      //		      printf("charge %u work_code %u particle_code %u, plane_index %u \n profection px %.9f py %.9f pz %.9f\n", charge_code, work_code, particle_code, plane_index, projection.Px(), projection.Py(), projection.Pz());
		      try
			{
			  if (projection.Mag() < 1E-9)
			    throw "Zero projection";
			  
			  if (plane -> ProjectsInside(particle_v3))
			    {
			      const double angle_right_norm  = plane -> angle_right(particle_v3)/plane -> DefAngle();
			      //			  printf("%f\n", angle_right_norm);

	      
			      const TString prefix = TString("chi_") + tag_charge_types_[charge_code] + "_" + tag_levels_[work_code] + "_" + tag_particles_types_[particle_code];
			      if (particle_code == ALLPRT)
				{
				  Fill1D(prefix, angle_right_norm + plane_index);
				}
			      else
				{
				  
				  switch(plane_index)
				    {
				    case 0:
				      if (it.GetIterCore() -> GetVectorCode() == HAD_B or it.GetIterCore() -> GetVectorCode() == q_closer_index)
					Fill1D(prefix, angle_right_norm + plane_index);
				      break;
				    case 1:
				      if (it.GetIterCore() -> GetVectorCode() == q_closer_index or it.GetIterCore() -> GetVectorCode() == q_further_index)
					Fill1D(prefix, angle_right_norm + plane_index);
				      break;
				
				    case 2:
				      if (it.GetIterCore() -> GetVectorCode() == HAD_B or it.GetIterCore() -> GetVectorCode() == q_further_index)
					Fill1D(prefix, angle_right_norm + plane_index);
				      break;
				    } 
				}
			      /* 
				 if (const_jet_specific)
				 {
				 plots_ptr_ -> operator[](prefix + DeltaR_tag + "_jet") -> Fill(angle1/angle, weight_);
				 plots_ptr_ -> operator[](prefix + tag_DeltaR_types_[2] + "_jet") -> Fill(angle1/angle, weight_);
		 
				 }*/
		  
			    }
			}
		      catch (const char *e)
			{
			  printf("%s\n", e);
			}
		    }
		}
	    }
	    
	}
    }

}