#include "ColourFlowAnalysisTool.hh"
#include "CFAT_Event.hh"
#include "CFAT_Core.hh"
//#include "TopLJets2015/TopAnalysis/interface/Definitions_cmssw.hh"

#include "CFAT_Event.hh"
#include "Definitions.hh"

#include "CFAT_Core.hh"

ColourFlowAnalysisTool::ColourFlowAnalysisTool()
{
}

void ColourFlowAnalysisTool::Work()
{
  // const std::map<Definitions::WorkEnum_t, const char *>         tag_levels_types_ = {make_pair(WorkEnum_t::RECO, "reco"), 
  // 								                                make_pair(WorkEnum_t::GEN, "gen")};


  PlotAngleBetweenJets();
  //printf("probe CF A0-1\n");
  PlotJetDimensions();
  //printf("probe CF A0-2\n");
  AnalyseParticleFlow();
  //printf("probe CF A0-3\n");

  for (VectorCode_t jet1_code = 0; jet1_code < 4; jet1_code ++)
    {
      //      printf("jet1 code %u\n", jet1_code);
      if (not GetEvent() -> GetVector(jet1_code))
	{
	  //  printf("continuing\n");
	  continue;
	}
      //printf("probe CF A1\n");
      for (ChargeCode_t charge_code = 0; charge_code < 2; charge_code ++)
	{
	  //printf("charge code %u\n", charge_code);
	  try
	    {
	      const PullVector pull_vector = GetEvent() -> GetCore() -> CalculatePullVector(jet1_code, charge_code, PF_PT_GT_1p0_GEV);
	      // if (jet1_code == LEADING_JET)
	      // 	{
	      // 	  printf("here");
	      // 	  pull_vector.ls();
	      // 	}
	      const TString suffix =  TString("_") + tag_charge_types_[charge_code] + "_" + 
		tag_levels_types_.at(work_mode_) + "_" + 
		tag_jet_types_[jet1_code];
	      //	      printf("Pull vector %s pv eta %.9f phi%f mod %.9f\n", suffix.Data(), pull_vector.eta_component, pull_vector.phi_component, pull_vector.Mod());
	      if (fabs(pull_vector.GetPhiComponent()) < 0.02 and fabs(pull_vector.GetRapidityComponent()) < 0.02)
		{

		}
	      else
		{
		  Fill1D(TString("phi_PV_bckg") + suffix, pull_vector.GetPhiComponent());
		  Fill1D(TString("rapidity_PV_bckg") + suffix, pull_vector.GetRapidityComponent());
		  Fill1D(TString("mag_PV_bckg") + suffix, pull_vector.Mod());
		}
	      for (VectorCode_t jet2_code = 0; jet2_code < N_jet_types_; jet2_code ++)
		{
		  const TLorentzVector * jet2 = GetEvent() -> GetVector(jet2_code);
		  if (jet2_code == jet1_code)
		    {
		      continue;
		    }
		  //printf("jet2_code %u\n", jet2_code);
		  if ((jet1_code == LEADING_B or jet1_code == SCND_LEADING_B) and (jet2_code != LEADING_B and jet2_code != SCND_LEADING_B) 
		      or (jet2_code == LEADING_B or jet2_code == SCND_LEADING_B) and (jet1_code != LEADING_B and jet1_code != SCND_LEADING_B))
		    {
		      continue;
		    }
		  if (not jet2)
		    {
		      continue;
		    }
		  const double DeltaR = GetEvent() -> DeltaR(jet1_code, jet2_code);
		  const char * DeltaR_tag = DeltaR <= 1.0 ? tag_DeltaR_types_[DELTAR_LE_1p0] : tag_DeltaR_types_[DELTAR_GT_1p0];
		  
		  try
		    {
		      const TString infix = TString("_") + tag_charge_types_[charge_code] + "_" + 
			tag_levels_types_.at(work_mode_) + "_" + 
			tag_jet_types_[jet1_code] + "_" + 
			tag_jet_types_[jet2_code] + "_"; 
		      const double pull_angle = GetEvent() -> PullAngle(pull_vector, jet2_code);
		      if (work_mode_ == WorkEnum_t::GEN and jet1_code == LEADING_JET and jet2_code == SCND_LEADING_JET and charge_code == ALLCOMP and DeltaR > 1.0)
			{
			  GetEvent() -> GetCore() -> EventDisplay(pull_vector, pull_angle);
			  static unsigned long entry = 0;
			  entry ++;
			}
		      const double cos_pull_angle = TMath::Cos(pull_angle);
		      //      printf("event n %lu\n", GetEvent() -> GetEventNumber());
		      // if (work_mode_ == 1 and jet1_code == 0 and jet2_code == 1 and charge_code == 0 and GetEvent() -> GetEventNumber() == 781)
		      // 	{
		      // 	  printf("DeltaR %f\n", DeltaR);

		      // 	  printf("pull vector phi %f rapdity %f\n",  pull_vector.GetPhiComponent(), pull_vector.GetRapidityComponent());
		      // 	}
		      if (fabs(pull_vector.GetPhiComponent()) < 0.02 and fabs(pull_vector.GetRapidityComponent()) < 0.02)
			{
			  // if (work_mode_ == WorkEnum_t::RECO and jet1_code == LEADING_JET and jet2_code == SCND_LEADING_JET and charge_code == ALLCOMP and DeltaR > 1.0)
			  //   {
			  //     unsigned long eventnumber = GetEvent() -> GetEventNumber();
			  //     static unsigned int quotientbefore = 0;
			  //     unsigned int quotient = eventnumber - eventnumber % 1000;
			  //     float sumpa = 0.0;
			  //     static unsigned long nfill = 0;
			  //     sumpa += pull_angle;
			  //     if (quotient != quotientbefore)
			  // 	{
			  // 	  quotientbefore = quotient;
			  // 	  nfill = 0;
			  // 	  printf("sumpa %.9f\n", sumpa);
			  // 	  sumpa = 0.0;

			  // 	  getchar();
			  // 	}
			  //     printf("eventnumber %lu, filling %lu, pull_angle %f\n", eventnumber, nfill, pull_angle);
			  //     nfill ++;
			    
			    // }
			  //	  printf("filling pull_angle %f\n", pull_angle);
			  Fill1D(TString("pull_angle")     + infix + DeltaR_tag, pull_angle);
			  //Fill1D(TString("cos_pull_angle") + infix + DeltaR_tag       + "_" + tag_channel_, cos_pull_angle);
			  Fill1D(TString("pull_angle")     + infix + tag_DeltaR_types_[DELTAR_TOTAL], pull_angle);
			  //Fill1D(TString("cos_pull_angle") + infix + tag_DeltaR_types_[DELTAR_TOTAL] + "_" + tag_channel_, cos_pull_angle);

			  if (jet1_code == LEADING_JET      and jet2_code == SCND_LEADING_JET or 
			      jet1_code == SCND_LEADING_JET and jet2_code == LEADING_JET or
			      jet1_code == LEADING_B        and jet2_code == SCND_LEADING_B or
			      jet1_code == SCND_LEADING_B   and jet2_code == LEADING_B)
			    {
			      Fill1D(TString("phi_PV") + suffix, pull_vector.GetPhiComponent());
			      Fill1D(TString("rapidity_PV") + suffix, pull_vector.GetRapidityComponent());
			      Fill1D(TString("mag_PV") + suffix, pull_vector.Mod());
			      if (DeltaR > 1.0)
				{
				  double pull_vector_par = -10.0;
				  if (TMath::Cos(pull_angle) > 0.0)
				    {
				      pull_vector_par = pull_vector.Mod()*TMath::Cos(pull_angle);
				      //printf("probe CF A\n");
				      Fill1D(TString("mag_PV_par") + suffix, pull_vector_par);
				    }
				  //printf("probe CF B\n");
				  if (work_mode_ == WorkEnum_t::RECO and charge_code == CHARGED and jet1_code == LEADING_JET and jet2_code == SCND_LEADING_JET and GetEvent() -> GetEventNumber() == 781)
				    {
				      // GetEvent() -> GetCore() -> ls_particles(LEADING_JET, ALLCOMP);
				      // pull_vector.ls();
				      // const TLorentzVector leading_jet_particles = GetEvent() -> GetCore() -> GetJetFromParticles(LEADING_JET, CHARGED);
				      // const TLorentzVector * leading_jet = & leading_jet_particles;GetEvent() -> GetVector(LEADING_JET);
				      // printf("leading jet E %f Px %f Py %f Pz %f\n", leading_jet -> E(), leading_jet -> Px(), leading_jet -> Py(), leading_jet -> Pz());
				      // const TLorentzVector * scnd_leading_jet = GetEvent() -> GetVector(SCND_LEADING_JET);
				      // printf("scnd leading jet E %f Px %f Py %f Pz %f\n", scnd_leading_jet -> E(), scnd_leading_jet -> Px(), scnd_leading_jet -> Py(), scnd_leading_jet -> Pz());
				      //printf("pull angle %.6f\n", pull_angle);
				    }
				  StoreMigrationValues(charge_code, jet1_code, pull_angle, pull_vector.Mod(), pull_vector_par);
				}
			    }
 			  
			}
		      /*		      if (jet1_code == LEADING_JET and jet2_code == SCND_LEADING_JET and charge_code == ALLCOMP)
					      {
					      StoreMigrationValues(pull_angle);
					      }
		      */
		      
		}
	      catch (const char * e)
		{
		  //printf("Exception I: %s\n", e);
		}
	    }
	}
      catch(const char *e)
	{

	      //printf("Exception II: %s\n", e);
	    }
	}
      // printf("probe CFAT\n");

      //            continue;
      for (PF_PTCutCode_t pf_ptcut_code = 1; pf_ptcut_code < 3; pf_ptcut_code ++)
	{
	  try
	    {
	      const PullVector pull_vector = GetEvent() -> GetCore() -> CalculatePullVector(jet1_code, ALLCOMP, pf_ptcut_code);
	      const TString suffix =  TString("_") + PF_Pt_cuts_types_[pf_ptcut_code] + "_" + 
		tag_levels_types_.at(work_mode_) + "_" + 
		tag_jet_types_[jet1_code]; 
	      
	      if (fabs(pull_vector.GetPhiComponent()) > 0.015 or fabs(pull_vector.GetRapidityComponent()) > 0.015)
		{
		  Fill1D(TString("phi_PV_bckg") + suffix, pull_vector.GetPhiComponent());
		  Fill1D(TString("rapidity_PV_bckg") + suffix, pull_vector.GetRapidityComponent());
		  Fill1D(TString("mag_PV_bckg") + suffix, pull_vector.Mod());
	     	}
	      else
		{
		  Fill1D(TString("phi_PV") + suffix, pull_vector.GetPhiComponent());
		  Fill1D(TString("rapidity_PV") + suffix, pull_vector.GetRapidityComponent());
		  Fill1D(TString("mag_PV") + suffix, pull_vector.Mod());
		  
		}
	      for (VectorCode_t jet2_code = 0; jet2_code < N_jet_types_; jet2_code ++)
		{
		  if (jet2_code == jet1_code)
		    {
		      continue;
		    }
		  if ((jet1_code == LEADING_B or jet1_code == SCND_LEADING_B) and (jet2_code != LEADING_B and jet2_code != SCND_LEADING_B) 
		     or (jet2_code == LEADING_B or jet2_code == SCND_LEADING_B) and (jet1_code != LEADING_B and jet1_code != SCND_LEADING_B))
		    {
		      continue;
		    }
		  const TLorentzVector * jet2 = GetEvent() -> GetVector(jet2_code);
		  if (not jet2)
		    {
		      continue;
		    }
		  const double DeltaR = GetEvent() -> DeltaR(jet1_code, jet2_code);
		  const char * DeltaR_tag = DeltaR <= 1.0 ? tag_DeltaR_types_[DELTAR_LE_1p0] : tag_DeltaR_types_[DELTAR_GT_1p0];
		  
		  try
		    {

		      const double pull_angle = GetEvent() -> PullAngle(pull_vector, jet2_code);
		      
		      const double cos_pull_angle = TMath::Cos(pull_angle);
		      const TString infix = TString("_") + PF_Pt_cuts_types_[pf_ptcut_code] + "_" + 
			tag_levels_types_.at(work_mode_) + "_" + 
			tag_jet_types_[jet1_code] + "_" + 
			tag_jet_types_[jet2_code] + "_"; 
		      if (fabs(pull_vector.GetPhiComponent()) < 0.015 and fabs(pull_vector.GetRapidityComponent()) < 0.015)
			{
			  Fill1D(TString("pull_angle")     + infix + DeltaR_tag, pull_angle);
			  //			  Fill1D(TString("cos_pull_angle") + infix + DeltaR_tag       + "_" + tag_channel_, cos_pull_angle);
			  Fill1D(TString("pull_angle")     + infix + tag_DeltaR_types_[DELTAR_TOTAL], pull_angle);
			  //Fill1D(TString("cos_pull_angle") + infix + tag_DeltaR_types_[DELTAR_TOTAL] + "_" + tag_channel_, cos_pull_angle);
			}
		    }
		  catch (const char * e)
		    {
		      //      printf("Exception III %s\n", e);
		    }
		}
	    }
	  catch(const char *e)
	    {

	      //  printf("Exception IV %s\n", e);
	    }
	}


	  try
	    {
	      const PullVector pull_vector = GetEvent() -> GetCore() -> CalculatePullVector(jet1_code);

	      const char * PF_N_cuts_tag = pull_vector.Ncomponents <= 20 ? PF_N_cuts_types_[PFN_LE_20] : PF_N_cuts_types_[PFN_GT_20];
	      const char * HadW_Pt_cuts_tag = "TBD";
	      const char * PVMag_cuts_tag = pull_vector.Mod() <= 0.005 ? PVMag_cuts_types_[PVMAG_LE_0p005] :PVMag_cuts_types_[PVMAG_GT_0p005];
      //const char * tags[3] = {PF_N_cuts_tag, HadW_Pt_cuts_tag, PVMag_cuts_tag};
	      {
		const TString suffix =  TString("_") + PF_N_cuts_tag + "_" + 
		  tag_levels_types_.at(work_mode_) + "_" + 
		  tag_jet_types_[jet1_code];
	      
		if (fabs(pull_vector.GetPhiComponent()) > 0.015 or fabs(pull_vector.GetRapidityComponent()) > 0.015)
		  {
		    Fill1D(TString("phi_PV_bckg") + suffix, pull_vector.GetPhiComponent());
		    Fill1D(TString("rapidity_PV_bckg") + suffix, pull_vector.GetRapidityComponent());
		    Fill1D(TString("mag_PV_bckg") + suffix, pull_vector.Mod());
		  }
		else
		  {
		    Fill1D(TString("phi_PV") + suffix, pull_vector.GetPhiComponent());
		    Fill1D(TString("rapidity_PV") + suffix, pull_vector.GetRapidityComponent());
		    Fill1D(TString("mag_PV") + suffix, pull_vector.Mod());
		  
		  }
	      }
	      if (GetEvent() -> GetVector(HAD_W))
		{
		  HadW_Pt_cuts_tag = GetEvent() -> GetVector(HAD_W) -> Pt() <= 50.0 ? HadW_Pt_cuts_types_[HADW_PT_LE_50p0_GEV] : HadW_Pt_cuts_types_[HADW_PT_GT_50p0_GEV];

	      
		  const TString suffix =  TString("_") + HadW_Pt_cuts_tag + "_" + 
		    tag_levels_types_.at(work_mode_) + "_" + 
		    tag_jet_types_[jet1_code];
	      
		  if (fabs(pull_vector.GetPhiComponent()) > 0.015 or fabs(pull_vector.GetRapidityComponent()) > 0.015)
		    {
		      Fill1D(TString("phi_PV_bckg") + suffix, pull_vector.GetPhiComponent());
		      Fill1D(TString("rapidity_PV_bckg") + suffix, pull_vector.GetRapidityComponent());
		      Fill1D(TString("mag_PV_bckg") + suffix, pull_vector.Mod());
		    }
		  else
		    {
		      Fill1D(TString("phi_PV") + suffix, pull_vector.GetPhiComponent());
		      Fill1D(TString("rapidity_PV") + suffix, pull_vector.GetRapidityComponent());
		      Fill1D(TString("mag_PV") + suffix, pull_vector.Mod());
		  
		    }
		}
	      for (VectorCode_t jet2_code = 0; jet2_code < N_jet_types_; jet2_code ++)
		{
		  if (jet2_code == jet1_code)
		    {
		      continue;
		    }
		  if ((jet1_code == LEADING_B or jet1_code == SCND_LEADING_B) and (jet2_code != LEADING_B and jet2_code != SCND_LEADING_B) 
		     or (jet2_code == LEADING_B or jet2_code == SCND_LEADING_B) and (jet1_code != LEADING_B and jet1_code != SCND_LEADING_B))
		    {
		      continue;
		    }
		  const TLorentzVector * jet2 = GetEvent() -> GetVector(jet2_code);
		  
		  if (not jet2)
		    {
		      continue;
		    }
		  const double DeltaR = GetEvent() -> DeltaR(jet1_code, jet2_code);
		  const char * DeltaR_tag = DeltaR <= 1.0 ? tag_DeltaR_types_[DELTAR_LE_1p0] : tag_DeltaR_types_[DELTAR_GT_1p0];
		  try
		    {
		      const double pull_angle = GetEvent() -> PullAngle(pull_vector, jet2_code);
		      
		      const double cos_pull_angle = TMath::Cos(pull_angle);
		      {
			const TString infix = TString("_") + PF_N_cuts_tag + "_" + 
			  tag_levels_types_.at(work_mode_) + "_" + 
			  tag_jet_types_[jet1_code] + "_" + 
			  tag_jet_types_[jet2_code] + "_";
			if (fabs(pull_vector.GetPhiComponent()) < 0.015 and fabs(pull_vector.GetRapidityComponent()) < 0.015)
			  {
			    Fill1D(TString("pull_angle")     + infix + DeltaR_tag, pull_angle);
			    //Fill1D(TString("cos_pull_angle") + infix + DeltaR_tag       + "_" + tag_channel_, cos_pull_angle);
			    Fill1D(TString("pull_angle")     + infix + tag_DeltaR_types_[DELTAR_TOTAL], pull_angle);
			    //Fill1D(TString("cos_pull_angle") + infix + tag_DeltaR_types_[DELTAR_TOTAL] + "_" + tag_channel_, cos_pull_angle);
			  }
		      }
		      if (GetEvent() -> GetVector(HAD_W))
			{
			  const TString infix = TString("_") + HadW_Pt_cuts_tag + "_" + 
			    tag_levels_types_.at(work_mode_) + "_" + 
			    tag_jet_types_[jet1_code] + "_" + 
			    tag_jet_types_[jet2_code] + "_"; 
			  if (fabs(pull_vector.GetPhiComponent()) < 0.015 and fabs(pull_vector.GetRapidityComponent()) < 0.015)
			    {
			      Fill1D(TString("pull_angle")     + infix + DeltaR_tag, pull_angle);
			      //Fill1D(TString("cos_pull_angle") + infix + DeltaR_tag       + "_" + tag_channel_, cos_pull_angle);
			      Fill1D(TString("pull_angle")     + infix + tag_DeltaR_types_[DELTAR_TOTAL], pull_angle);
			      //Fill1D(TString("cos_pull_angle") + infix + tag_DeltaR_types_[DELTAR_TOTAL] + "_" + tag_channel_, cos_pull_angle);
			    }
			}

		      {
			const TString infix = TString("_") + PVMag_cuts_tag + "_" + 
			  tag_levels_types_.at(work_mode_) + "_" + 
			  tag_jet_types_[jet1_code] + "_" + 
			  tag_jet_types_[jet2_code] + "_"; 
			if (fabs(pull_vector.GetPhiComponent()) < 0.015 and fabs(pull_vector.GetRapidityComponent()) < 0.015)
			  {
			    Fill1D(TString("pull_angle")     + infix + DeltaR_tag, pull_angle);
			    //Fill1D(TString("cos_pull_angle") + infix + DeltaR_tag       + "_" + tag_channel_, cos_pull_angle);
			    Fill1D(TString("pull_angle")     + infix + tag_DeltaR_types_[DELTAR_TOTAL], pull_angle);
			    //Fill1D(TString("cos_pull_angle") + infix + tag_DeltaR_types_[DELTAR_TOTAL] + "_" + tag_channel_, cos_pull_angle);
			  }
		      }
		
		    }
		  catch (const char * e)
		    {
		      //      printf("Exception V %s\n", e);
		    }
		}
	    }
	  catch(const char *e)
	    {

	      // printf("Exception VI %s\n", e);
	    }
    }
  GetEvent() -> GetCore() -> AnalyseJetConstituents();
  // AnalyseParticleFlow();
  //PtRadiationProfile();
  
}

CFAT_Event * ColourFlowAnalysisTool::GetEvent() const
{
  return cfat_event_ptr_;
}

void ColourFlowAnalysisTool::Reset()
{
  GetEvent() -> Reset();
}

void ColourFlowAnalysisTool::SetEvent(CFAT_Event & event)
{
  cfat_event_ptr_ = &event;
  event.cfat_ = this;
}

void ColourFlowAnalysisTool::SetWorkMode(WorkEnum_t mode)
{
  
  work_mode_ = mode;
  // printf("setting work mode\n");
  // if (mode == WorkEnum_t::RECO)
  //   {
  //     printf("is reco\n");
  //     printf("%s\n", tag_levels_types_.at(mode));
  //   }
  // else if (mode == WorkEnum_t::GEN)
  //   {
  //     printf("is gen\n");
  //     printf("%s\n", tag_levels_types_.at(mode));
  //   }
  // else
  //   {
  //   }
  GetEvent() -> SetWorkMode(mode);
}


void ColourFlowAnalysisTool::PlotAngleBetweenJets() const
{
  const std::map<Definitions::WorkEnum_t, const char *>         tag_levels_types_ = {make_pair(WorkEnum_t::RECO, "reco"), 
 								                                make_pair(WorkEnum_t::GEN, "gen")};

  for (VectorCode_t jet1_code = 0; jet1_code < N_jet_types_; jet1_code ++)
    {
      const TLorentzVector * jet1 = GetEvent() -> GetVector(jet1_code);
      if (not jet1)
	{
	  continue;
	}
      if (not (jet1_code == BEAM or jet1_code == LEADING_JET or jet1_code == LEPTON))
	{
	  continue;
	}
      for (VectorCode_t jet2_code = jet1_code + 1; jet2_code < N_jet_types_; jet2_code ++)
	{
	  const TLorentzVector * jet2 = GetEvent() -> GetVector(jet2_code);
	  if (not jet2)
	    {
	      continue;
	    }
	  if (not (jet2_code == BEAM or jet2_code == LEADING_JET or jet2_code == LEPTON))
	    {
	      continue;
	    }
	  const double DeltaR = GetEvent() -> DeltaR(jet1_code, jet2_code);
	  const unsigned char DeltaR_index = DeltaR < 1.0 ? DELTAR_LE_1p0 : DELTAR_GT_1p0;
          
	  const TString infix = TString(tag_jet_types_[jet1_code]) + "_" + 
						      tag_jet_types_[jet2_code] + "_" + 
						      tag_levels_types_.at(work_mode_) + "_"; 
	  const TString hash_key1_angle = TString("angle_") + 
	    infix +
	    tag_DeltaR_types_[DeltaR_index];


	  const double angle = GetEvent() -> Angle(jet1_code, jet2_code);
	  Fill1D(hash_key1_angle, angle);
	  const TString hash_key2_angle = TString("angle_") + 
	    infix +
	    tag_DeltaR_types_[DELTAR_TOTAL];
	  Fill1D(hash_key2_angle, angle);
	  /*          if (jet2 != CFAT_Event::beam_ptr_)
	    {
	      const TVector2 jet_difference_phi_eta(TVector2::Phi_mpi_pi(jet2 -> Phi() - jet1 -> Phi()), jet2 -> Rapidity() - jet1 -> Rapidity());
	      {
		const TString hash_key = TString("jet_dif_phi_") + 
		  infix +
		  tag_DeltaR_types_[DeltaR_index];
		Fill1D(hash_key, jet_difference_phi_eta.Px());
	  					     
	      }
	
	      {
		const TString hash_key = TString("jet_dif_phi_") + 
		  infix +
		  tag_DeltaR_types_[DELTAR_TOTAL];
		Fill1D(hash_key, jet_difference_phi_eta.Px());
	  					     
	      }
	
	      {
		const TString hash_key = TString("jet_dif_eta_") + 
		  infix +
		  tag_DeltaR_types_[DeltaR_index];
		Fill1D(hash_key, jet_difference_phi_eta.Py());
	  					     
	      }
	
	      {
		const TString hash_key = TString("jet_dif_eta_") + 
		  infix +
		  tag_DeltaR_types_[DELTAR_TOTAL];
		Fill1D(hash_key, jet_difference_phi_eta.Py());
	  					     
	      }
	      }*/

       	}
    }
}

void ColourFlowAnalysisTool::PlotJetDimensions() const
{
  const std::map<Definitions::WorkEnum_t, const char *>         tag_levels_types_ = {make_pair(WorkEnum_t::RECO, "reco"), 
 								                                make_pair(WorkEnum_t::GEN, "gen")};

  for (VectorCode_t jet_code = 0; jet_code < N_jet_types_; jet_code ++)
    {
      const TLorentzVector * jet = GetEvent() -> GetVector(jet_code); 
      
      if (not jet)
	{
	  continue;
	}
      const TString suffix = TString(tag_levels_types_.at(work_mode_)) + "_" +
	tag_jet_types_[jet_code];
      //printf("test %s %s \n", (TString("jet_phi_") +  sufix).Data(), (TString("jet_rapidity_") +  sufix).Data()); 
      if (jet == CFAT_Event::beam_ptr_)
	{
	  continue;
	}
      //  Fill1D(TString("jet_phi_")       + suffix,  jet -> Phi());
      //Fill1D(TString("jet_rapidity_")  + suffix,  jet -> Rapidity());
      //Fill1D(TString("jet_eta_")       + suffix,  jet -> Eta());
      //const double P = sqrt(pow(jet -> Pt(), 2) + pow(jet -> Pz(), 2));
      //Fill1D(TString("jet_mass_norm_") + suffix,  jet -> M()/P);
      //Fill1D(TString("jet_pt_norm_")   + suffix,  jet -> Pt()/P);
      //Fill1D(TString("jet_pz_norm_")   + suffix,  jet -> Pz()/P);
      //Fill1D(TString("jet_px_norm_")   + suffix,  jet -> Px()/P);

      Fill1D(TString("jet_mass_")      + suffix,  jet -> M());
      Fill1D(TString("jet_pt_")        + suffix,  jet -> Pt());
      Fill1D(TString("jet_pt_nosf_")    + suffix,  jet -> Pt(), 1.0, "NOTOPPTSF");
      //Fill1D(TString("jet_pz_")        + suffix,  jet -> Pz());
      //Fill1D(TString("jet_px_")        + suffix,  jet -> Px());

    }
}
void ColourFlowAnalysisTool::SetChannel(ChannelCode_t code)
{
  channel_code_ = code;
}

ChannelCode_t ColourFlowAnalysisTool::GetChannel() const
{
  return channel_code_;
}

WorkEnum_t ColourFlowAnalysisTool::GetWorkMode() const
{
  return work_mode_;
}



/*
void ColourFlowAnalysisTool::PlotPUPPIWeight(unsigned char jet_vector_index, unsigned char jet_index, unsigned char charge_index) const
{
  const TString hash_key = TString("PUPPI_weight_") +
		tag_charge_types_[charge_index] + "_" + 
		tag_levels_[work_mode_] + "_" +
		tag_jet_types_[jet_vector_index]; 
  //printf("test %s\n", hash_key.Data());
  static const bool OnlyChargedConstituents[2] = {false, true};
  unsigned int size = work_mode_ == 0 ? event_ptr_ -> npf : event_ptr_ -> ngpf;
  for (unsigned int jet_const_index = 0; jet_const_index < size; jet_const_index ++)
    {
      if (work_mode_ == 0)
	{
	  if (event_ptr_ -> pf_j[jet_const_index] != jet_index)
	    continue;
	  if (OnlyChargedConstituents[charge_index] and event_ptr_ -> pf_id[jet_const_index] == 0)
	    continue;
	  plots_ptr_ -> operator[](hash_key) -> Fill(event_ptr_ -> pf_puppiWgt[jet_const_index], weight_);

	}
      else
	{
	  return;

	}
		
    }
  
}
*/

void ColourFlowAnalysisTool::Do()
{

}

ColourFlowAnalysisTool::~ColourFlowAnalysisTool()
{

}
