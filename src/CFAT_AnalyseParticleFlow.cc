#include "ColourFlowAnalysisTool.hh"
#include "ParticleFlowTools.hh"
#include "Definitions.hh"
#include "CFAT_Core.hh"
using namespace Definitions;
void ColourFlowAnalysisTool::AnalyseParticleFlow() const
{
  CFAT_Core * core = GetEvent() -> GetCore();
  

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
  const Plane plane_qfurther_hadb(*q_further, had_b_jet_v3);
  const Plane * planes[Nplanes] = {&plane_hadb_qcloser, &plane_q1q2, & plane_qfurther_hadb};
  const char * plane_titles [Nplanes] = {"hbqc", "qlq2l", "qfhb"};
  for (unsigned char particle_code = 0; particle_code < N_particles_types_; particle_code ++)
    {
      for (unsigned char plane_index = 0; plane_index < Nplanes; plane_index ++)
	{
	  for (ChargeCode_t charge_code = 0; charge_code < N_charge_types_; charge_code ++)
	    {
	      unsigned int ind = 0;
	      for (CFAT_Core::pf_iter it = core -> begin(); it != core -> end(); it ++)
		{
		  //		  printf("ind %u work_code %u particle_code %u, plane_index %u, charge %u \n", ind, work_mode_, particle_code, plane_index, charge_code);
		  ind ++;
		  if (charge_code == CHARGED and it -> GetCharge() == 0)
		    continue;
		  const  TVector3 particle_v3 = it -> GetLorentzVector().Vect();

		  const Plane *plane = planes[plane_index];
		  const TVector3 projection = plane -> Project(particle_v3);
		  try
		    {
		      if (projection.Mag() < 1E-9)
			throw "Zero projection";
			  
		      if (plane -> ProjectsInside(particle_v3))
			{
			  const double angle_left_norm  = plane -> angle_left(particle_v3)/plane -> DefAngle();
			  //			  printf("%f\n", angle_left_norm);
			  //			  printf("angle right %f left %f right + left %f DefAngle %f\n", plane -> angle_left(particle_v3), plane -> angle_left(particle_v3),  plane -> angle_left(particle_v3) + plane -> angle_left(particle_v3), plane -> DefAngle());
	      
			  const TString prefix_PA_N = TString("chi") + plane_titles[plane_index] + "_" + tag_PA_plots_types_[PA_N] + "_" + tag_charge_types_[charge_code] + "_" + tag_levels_types_[work_mode_] + "_" + tag_particles_types_[particle_code];
			  const TString prefix_PA_E = TString("chi") + plane_titles[plane_index] + "_" + tag_PA_plots_types_[PA_E] + "_" + tag_charge_types_[charge_code] + "_" + tag_levels_types_[work_mode_] + "_" + tag_particles_types_[particle_code];
			  const TString prefix_PA_PT = TString("chi") + plane_titles[plane_index] + "_" + tag_PA_plots_types_[PA_PT] + "_" + tag_charge_types_[charge_code] + "_" + tag_levels_types_[work_mode_] + "_" + tag_particles_types_[particle_code];

			  if (particle_code == ALLPRT)
			    {
			      Fill1D(prefix_PA_N, angle_left_norm/* + plane_index*/);
			      Fill1D(prefix_PA_E, angle_left_norm/* + plane_index*/, it -> GetLorentzVector().E()/GetEvent() -> GetEventEnergy());
			      //  printf("particle_code %u trackedvectorcode %u\n", particle_code, it.GetTrackedVectorCode());
			     
			      //			      Fill1D(prefix_PA_PT, angle_left_norm + plane_index, it -> GetLorentzVector().Pt()/GetEvent() -> GetVectorRef(it.GetIterCore() -> GetVectorCode()) -> Pt());

			    }
			  else
			    {
				  
			      switch(plane_index)
				{
				case 0:
				  if (it.GetIterCore() -> GetVectorCode() == HAD_B or it.GetIterCore() -> GetVectorCode() == q_closer_index)
				    {
				      Fill1D(prefix_PA_N, angle_left_norm/* + plane_index*/);
				      Fill1D(prefix_PA_E, angle_left_norm/* + plane_index*/, it -> GetLorentzVector().E()/GetEvent() -> GetEventEnergy());
				      Fill1D(prefix_PA_PT, angle_left_norm/* + plane_index*/, it -> GetLorentzVector().Pt()/GetEvent() -> GetVectorRef(it.GetIterCore() -> GetVectorCode()) -> Pt());
				    }
				  break;
				case 1:
				  if (it.GetIterCore() -> GetVectorCode() == q_closer_index or it.GetIterCore() -> GetVectorCode() == q_further_index)
				    {
				      Fill1D(prefix_PA_N, angle_left_norm/* + plane_index*/);
				      Fill1D(prefix_PA_E, angle_left_norm/* + plane_index*/, it -> GetLorentzVector().E()/GetEvent() -> GetEventEnergy());
				      Fill1D(prefix_PA_PT, angle_left_norm/* + plane_index*/, it -> GetLorentzVector().Pt()/GetEvent() -> GetVectorRef(it.GetIterCore() -> GetVectorCode()) -> Pt());

				    }
				  break;
				
				case 2:
				  if (it.GetIterCore() -> GetVectorCode() == HAD_B or it.GetIterCore() -> GetVectorCode() == q_further_index)
				    {
				      Fill1D(prefix_PA_N, angle_left_norm/* + plane_index*/);
				      Fill1D(prefix_PA_E, angle_left_norm/* + plane_index*/, it -> GetLorentzVector().E()/GetEvent() -> GetEventEnergy());
				      Fill1D(prefix_PA_PT, angle_left_norm/* + plane_index*/, it -> GetLorentzVector().Pt()/GetEvent() -> GetVectorRef(it.GetIterCore() -> GetVectorCode()) -> Pt());

				    }
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
		      //		      printf("%s\n", e);
		    }
		}
	    }
	}
	    
    }
  const TVector3 leading_b_v3 = GetEvent() -> GetVector(LEADING_B) -> Vect();
  const TVector3 scnd_leading_b_v3 = GetEvent() -> GetVector(SCND_LEADING_B) -> Vect();
  Plane plane_bj(leading_b_v3, scnd_leading_b_v3);
  const unsigned char Nplanesj = 1;
  Plane * planesj[Nplanesj] = {&plane_bj};
  for (unsigned char particle_code = 0; particle_code < N_particles_types_; particle_code ++)
    {
      for (unsigned char plane_index = 0; plane_index < Nplanesj; plane_index ++)
	{
	  for (ChargeCode_t charge_code = 0; charge_code < N_charge_types_; charge_code ++)
	    {
	      unsigned int ind = 0;
	      for (CFAT_Core::pf_iter it = core -> begin(); it != core -> end(); it ++)
		{
		  /*	  printf("ind %u work_code %u particle_code %u, plane_index %u, charge %u \n", ind, work_mode_, particle_code, plane_index, charge_code);
		  printf("tracked vector %u it.GetIterCore() -> GetVectorCode()) %u  %p it.GetCore() -> GetVector(LEADING_B) %p\n", 
			 it.GetTrackedVectorCode(), 
			 it.GetIterCore() -> GetVectorCode(), 
			 it.GetIterCore() -> GetVectorCode() == 255 ? nullptr : it.GetCore() -> GetVector(it.GetIterCore() -> GetVectorCode()),
		  it.GetCore() -> GetVector(LEADING_B));
		  */
		  ind ++;
		  if (charge_code == CHARGED and it -> GetCharge() == 0)
		    continue;
		  const  TVector3 particle_v3 = it -> GetLorentzVector().Vect();

		  const Plane *plane = planesj[plane_index];
		  const TVector3 projection = plane -> Project(particle_v3);
		  try
		    {
		      if (projection.Mag() < 1E-9)
			throw "Zero projection";
			  
		      if (plane -> ProjectsInside(particle_v3))
			{
			  const double angle_left_norm  = plane -> angle_left(particle_v3)/plane -> DefAngle();
			  //			  printf("%f\n", angle_left_norm);
			  //			  printf("angle right %f left %f right + left %f DefAngle %f\n", plane -> angle_left(particle_v3), plane -> angle_left(particle_v3),  plane -> angle_left(particle_v3) + plane -> angle_left(particle_v3), plane -> DefAngle());
	      
			  const TString prefix_PA_Nj = TString("chiblb2l_") + tag_PA_plots_types_[PA_N] + "_" + tag_charge_types_[charge_code] + "_" + tag_levels_types_[work_mode_] + "_" + tag_particles_types_[particle_code];
			  const TString prefix_PA_Ej = TString("chiblb2l_") + tag_PA_plots_types_[PA_E] + "_" + tag_charge_types_[charge_code] + "_" + tag_levels_types_[work_mode_] + "_" + tag_particles_types_[particle_code];
			  const TString prefix_PA_PTj = TString("chiblb2l_") + tag_PA_plots_types_[PA_PT] + "_" + tag_charge_types_[charge_code] + "_" + tag_levels_types_[work_mode_] + "_" + tag_particles_types_[particle_code];

			  if (particle_code == ALLPRT)
			    {
			      Fill1D(prefix_PA_Nj, angle_left_norm/* + plane_index*/);
			      Fill1D(prefix_PA_Ej, angle_left_norm/* + plane_index*/, it -> GetLorentzVector().E()/GetEvent() -> GetEventEnergy());
			      //  printf("particle_code %u trackedvectorcode %u\n", particle_code, it.GetTrackedVectorCode());
			     
			      //Fill1D(prefix_PA_PTj, angle_left_norm + plane_index, it -> GetLorentzVector().Pt()/GetEvent() -> GetVectorRef(it.GetIterCore() -> GetVectorCode()) -> Pt());

			    }
			  else
			    {
				  
			      switch(plane_index)
				{
				  /*				case 0:
				  if (it.GetIterCore() -> GetVectorCode() == LEADING_JET or it.GetIterCore() -> GetVectorCode() == SCND_LEADING_JET)
				    {
				      Fill1D(prefix_PA_Nj, angle_left_norm + plane_index);
				      Fill1D(prefix_PA_Ej, angle_left_norm + plane_index, it -> GetLorentzVector().E()/GetEvent() -> GetEventEnergy());
				      Fill1D(prefix_PA_PTj, angle_left_norm + plane_index, it -> GetLorentzVector().Pt()/GetEvent() -> GetVectorRef(it.GetIterCore() -> GetVectorCode()) -> Pt());
				    }
				  break;*/
				case 0:
				  if (it.GetIterCore() -> GetVectorCode() != 255 and (it.GetCore() -> GetVector(it.GetIterCore() -> GetVectorCode()) == it.GetCore() -> GetVector(SCND_LEADING_B) or it.GetCore() -> GetVector(it.GetIterCore() -> GetVectorCode()) == it.GetCore() -> GetVector(LEADING_B)))
				    {
				      /*				      printf("angle right %f leading %s 2nd leading %s\n", 
					     angle_left_norm, 
					     it.GetCore() -> GetVector(it.GetIterCore() -> GetVectorCode()) == it.GetCore() -> GetVector(LEADING_B) ? "true" : "false", 
					     it.GetCore() -> GetVector(it.GetIterCore() -> GetVectorCode()) == it.GetCore() -> GetVector(SCND_LEADING_B) ? "true" : "false");*/
				      Fill1D(prefix_PA_Nj, angle_left_norm/* + plane_index*/);
				      Fill1D(prefix_PA_Ej, angle_left_norm/* + plane_index*/, it -> GetLorentzVector().E()/GetEvent() -> GetEventEnergy());
				      Fill1D(prefix_PA_PTj, angle_left_norm/* + plane_index*/, it -> GetLorentzVector().Pt()/GetEvent() -> GetVectorRef(it.GetIterCore() -> GetVectorCode()) -> Pt());

				    }
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
		      // printf("%s\n", e);
		    }
		}
	    }
	}
	    
    }
}


