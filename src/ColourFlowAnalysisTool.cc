#include "ColourFlowAnalysisTool.hh"
//#include "TopLJets2015/TopAnalysis/interface/Definitions_cmssw.hh"

#include "CFAT_Event.hh"
#include "Definitions.hh"

#include "CFAT_Core.hh"

ColourFlowAnalysisTool::ColourFlowAnalysisTool()
{
}

void ColourFlowAnalysisTool::Work()
{
  PlotAngleBetweenJets();
  PlotJetDimensions();
  for (VectorCode_t jet1_code = 0; jet1_code < 2; jet1_code ++)
    {
      for (ChargeCode_t charge_code = 0; charge_code < 2; charge_code ++)
	{
	  try
	    {
	      const PullVector pull_vector = GetEvent() -> GetCore() -> CalculatePullVector(jet1_code, charge_code);
	      const TString suffix =  TString("_") + tag_charge_types_[charge_code] + "_" + 
		tag_levels_[work_mode_] + "_" + 
		tag_jet_types_[jet1_code] + "_" + 
		tag_channel_;
	      printf("%s\n", suffix.Data());
	      if (fabs(pull_vector.phi_component) > 0.015 or fabs(pull_vector.eta_component) > 0.015)
		{
		  Fill1D(TString("phi_PV_bckg") + suffix, pull_vector.phi_component);
		  Fill1D(TString("eta_PV_bckg") + suffix, pull_vector.eta_component);
		  Fill1D(TString("mag_PV_bckg") + suffix, pull_vector.Mod());
	     	}
	      else
		{
		  Fill1D(TString("phi_PV") + suffix, pull_vector.phi_component);
		  Fill1D(TString("eta_PV") + suffix, pull_vector.eta_component);
		  Fill1D(TString("mag_PV") + suffix, pull_vector.Mod());
		  
		}
	      for (VectorCode_t jet2_code = 0; jet2_code < CFAT_Event::N_jet_types_; jet2_code ++)
		{
		  const TLorentzVector * jet2 = GetEvent() -> GetVector(jet2_code);

		  if (jet2_code == jet1_code)
		    continue;
		  if (not jet2)
		    continue;
		  const double DeltaR = GetEvent() -> DeltaR(jet1_code, jet2_code);
		  const char * DeltaR_tag = DeltaR <= 1.0 ? tag_DeltaR_types_[DELTAR_LE_1p0] : tag_DeltaR_types_[DELTAR_GT_1p0];
		  
		  try
		    {
		      const double pull_angle = GetEvent() -> PullAngle(pull_vector, jet2_code);
		      
		      const double cos_pull_angle = TMath::Cos(pull_angle);
		      const TString infix = TString("_") + tag_charge_types_[charge_code] + "_" + 
			tag_levels_[work_mode_] + "_" + 
			tag_jet_types_[jet1_code] + "_:_" + 
			tag_jet_types_[jet2_code] + "_"; 
		      if (fabs(pull_vector.phi_component) < 0.015 and fabs(pull_vector.eta_component) < 0.015)
			{
			  Fill1D(TString("pull_angle")     + infix + DeltaR_tag       + "_" + tag_channel_, pull_angle);
			  Fill1D(TString("cos_pull_angle") + infix + DeltaR_tag       + "_" + tag_channel_, cos_pull_angle);
			  Fill1D(TString("pull_angle")     + infix + tag_DeltaR_types_[DELTAR_TOTAL] + "_" + tag_channel_, pull_angle);
			  Fill1D(TString("cos_pull_angle") + infix + tag_DeltaR_types_[DELTAR_TOTAL] + "_" + tag_channel_, cos_pull_angle);
			}
		    }
		  catch (const char * e)
		    {
		      printf("Exception I: %s\n", e);
		    }
		}
	    }
	  catch(const char *e)
	    {

	      printf("Exception II%s\n", e);
	    }
	}
      
      for (PF_PTCutCode_t pf_ptcut_code = 1; pf_ptcut_code < 3; pf_ptcut_code ++)
	{
	  try
	    {
	      const PullVector pull_vector = GetEvent() -> GetCore() -> CalculatePullVector(jet1_code, ALLCOMP, pf_ptcut_code);
	      
	      const TString suffix =  TString("_") + PF_Pt_cuts_types_[pf_ptcut_code] + "_" + 
		tag_levels_[work_mode_] + "_" + 
		tag_jet_types_[jet1_code] + "_" + 
		tag_channel_;
	      
	      if (fabs(pull_vector.phi_component) > 0.015 or fabs(pull_vector.eta_component) > 0.015)
		{
		  Fill1D(TString("phi_PV_bckg") + suffix, pull_vector.phi_component);
		  Fill1D(TString("eta_PV_bckg") + suffix, pull_vector.eta_component);
		  Fill1D(TString("mag_PV_bckg") + suffix, pull_vector.Mod());
	     	}
	      else
		{
		  Fill1D(TString("phi_PV") + suffix, pull_vector.phi_component);
		  Fill1D(TString("eta_PV") + suffix, pull_vector.eta_component);
		  Fill1D(TString("mag_PV") + suffix, pull_vector.Mod());
		  
		}
	      for (VectorCode_t jet2_code = 0; jet2_code < CFAT_Event::N_jet_types_; jet2_code ++)
		{
		  const TLorentzVector * jet2 = GetEvent() -> GetVector(jet2_code);
		  
		  if (jet2_code == jet1_code)
		    continue;
		  if (not jet2)
		    continue;
		  const double DeltaR = GetEvent() -> DeltaR(jet1_code, jet2_code);
		  const char * DeltaR_tag = DeltaR <= 1.0 ? tag_DeltaR_types_[DELTAR_LE_1p0] : tag_DeltaR_types_[DELTAR_GT_1p0];
		  
		  try
		    {
		      const double pull_angle = GetEvent() -> PullAngle(pull_vector, jet2_code);
		      
		      const double cos_pull_angle = TMath::Cos(pull_angle);
		      const TString infix = TString("_") + PF_Pt_cuts_types_[pf_ptcut_code] + "_" + 
			tag_levels_[work_mode_] + "_" + 
			tag_jet_types_[jet1_code] + "_:_" + 
			tag_jet_types_[jet2_code] + "_"; 
		      if (fabs(pull_vector.phi_component) < 0.015 and fabs(pull_vector.eta_component) < 0.015)
			{
			  Fill1D(TString("pull_angle")     + infix + DeltaR_tag       + "_" + tag_channel_, pull_angle);
			  Fill1D(TString("cos_pull_angle") + infix + DeltaR_tag       + "_" + tag_channel_, cos_pull_angle);
			  Fill1D(TString("pull_angle")     + infix + tag_DeltaR_types_[DELTAR_TOTAL] + "_" + tag_channel_, pull_angle);
			  Fill1D(TString("cos_pull_angle") + infix + tag_DeltaR_types_[DELTAR_TOTAL] + "_" + tag_channel_, cos_pull_angle);
			}
		    }
		  catch (const char * e)
		    {
		      printf("Exception III %s\n", e);
		    }
		}
	    }
	  catch(const char *e)
	    {

	      printf("Exception IV %s\n", e);
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
		  tag_levels_[work_mode_] + "_" + 
		  tag_jet_types_[jet1_code] + "_" + 
		  tag_channel_;
	      
		if (fabs(pull_vector.phi_component) > 0.015 or fabs(pull_vector.eta_component) > 0.015)
		  {
		    Fill1D(TString("phi_PV_bckg") + suffix, pull_vector.phi_component);
		    Fill1D(TString("eta_PV_bckg") + suffix, pull_vector.eta_component);
		    Fill1D(TString("mag_PV_bckg") + suffix, pull_vector.Mod());
		  }
		else
		  {
		    Fill1D(TString("phi_PV") + suffix, pull_vector.phi_component);
		    Fill1D(TString("eta_PV") + suffix, pull_vector.eta_component);
		    Fill1D(TString("mag_PV") + suffix, pull_vector.Mod());
		  
		  }
	      }
	      if (GetEvent() -> GetVector(HAD_W))
		{
		  HadW_Pt_cuts_tag = GetEvent() -> GetVector(HAD_W) -> Pt() <= 50.0 ? HadW_Pt_cuts_types_[HADW_PT_LE_50p0_GEV] : HadW_Pt_cuts_types_[HADW_PT_GT_50p0_GEV];

	      
		  const TString suffix =  TString("_") + HadW_Pt_cuts_tag + "_" + 
		    tag_levels_[work_mode_] + "_" + 
		    tag_jet_types_[jet1_code] + "_" + 
		    tag_channel_;
	      
		  if (fabs(pull_vector.phi_component) > 0.015 or fabs(pull_vector.eta_component) > 0.015)
		    {
		      Fill1D(TString("phi_PV_bckg") + suffix, pull_vector.phi_component);
		      Fill1D(TString("eta_PV_bckg") + suffix, pull_vector.eta_component);
		      Fill1D(TString("mag_PV_bckg") + suffix, pull_vector.Mod());
		    }
		  else
		    {
		      Fill1D(TString("phi_PV") + suffix, pull_vector.phi_component);
		      Fill1D(TString("eta_PV") + suffix, pull_vector.eta_component);
		      Fill1D(TString("mag_PV") + suffix, pull_vector.Mod());
		  
		    }
		}
	      for (VectorCode_t jet2_code = 0; jet2_code < CFAT_Event::N_jet_types_; jet2_code ++)
		{
		  const TLorentzVector * jet2 = GetEvent() -> GetVector(jet2_code);
		  
		  if (jet2_code == jet1_code)
		    continue;
		  if (not jet2)
		    continue;
		  const double DeltaR = GetEvent() -> DeltaR(jet1_code, jet2_code);
		  const char * DeltaR_tag = DeltaR <= 1.0 ? tag_DeltaR_types_[DELTAR_LE_1p0] : tag_DeltaR_types_[DELTAR_GT_1p0];
		  try
		    {
		      const double pull_angle = GetEvent() -> PullAngle(pull_vector, jet2_code);
		      
		      const double cos_pull_angle = TMath::Cos(pull_angle);
		      {
			const TString infix = TString("_") + PF_N_cuts_tag + "_" + 
			  tag_levels_[work_mode_] + "_" + 
			  tag_jet_types_[jet1_code] + "_:_" + 
			  tag_jet_types_[jet2_code] + "_";
			if (fabs(pull_vector.phi_component) < 0.015 and fabs(pull_vector.eta_component) < 0.015)
			  {
			    Fill1D(TString("pull_angle")     + infix + DeltaR_tag       + "_" + tag_channel_, pull_angle);
			    Fill1D(TString("cos_pull_angle") + infix + DeltaR_tag       + "_" + tag_channel_, cos_pull_angle);
			    Fill1D(TString("pull_angle")     + infix + tag_DeltaR_types_[DELTAR_TOTAL] + "_" + tag_channel_, pull_angle);
			    Fill1D(TString("cos_pull_angle") + infix + tag_DeltaR_types_[DELTAR_TOTAL] + "_" + tag_channel_, cos_pull_angle);
			  }
		      }
		      if (GetEvent() -> GetVector(HAD_W))
			{
			  const TString infix = TString("_") + HadW_Pt_cuts_tag + "_" + 
			    tag_levels_[work_mode_] + "_" + 
			    tag_jet_types_[jet1_code] + "_:_" + 
			    tag_jet_types_[jet2_code] + "_"; 
			  if (fabs(pull_vector.phi_component) < 0.015 and fabs(pull_vector.eta_component) < 0.015)
			    {
			      Fill1D(TString("pull_angle")     + infix + DeltaR_tag       + "_" + tag_channel_, pull_angle);
			      Fill1D(TString("cos_pull_angle") + infix + DeltaR_tag       + "_" + tag_channel_, cos_pull_angle);
			      Fill1D(TString("pull_angle")     + infix + tag_DeltaR_types_[DELTAR_TOTAL] + "_" + tag_channel_, pull_angle);
			      Fill1D(TString("cos_pull_angle") + infix + tag_DeltaR_types_[DELTAR_TOTAL] + "_" + tag_channel_, cos_pull_angle);
			    }
			}

		      {
			const TString infix = TString("_") + PVMag_cuts_tag + "_" + 
			  tag_levels_[work_mode_] + "_" + 
			  tag_jet_types_[jet1_code] + "_:_" + 
			  tag_jet_types_[jet2_code] + "_"; 
			if (fabs(pull_vector.phi_component) < 0.015 and fabs(pull_vector.eta_component) < 0.015)
			  {
			    Fill1D(TString("pull_angle")     + infix + DeltaR_tag       + "_" + tag_channel_, pull_angle);
			    Fill1D(TString("cos_pull_angle") + infix + DeltaR_tag       + "_" + tag_channel_, cos_pull_angle);
			    Fill1D(TString("pull_angle")     + infix + tag_DeltaR_types_[DELTAR_TOTAL] + "_" + tag_channel_, pull_angle);
			    Fill1D(TString("cos_pull_angle") + infix + tag_DeltaR_types_[DELTAR_TOTAL] + "_" + tag_channel_, cos_pull_angle);
			  }
		      }
		
		    }
		  catch (const char * e)
		    {
		      printf("Exception V %s\n", e);
		    }
		}
	    }
	  catch(const char *e)
	    {

	      printf("Exception VI %s\n", e);
	    }


    }
  // AnalyseParticleFlow();
  //PtRadiationProfile();
  
}

CFAT_Event * ColourFlowAnalysisTool::GetEvent() const
{
  return cfat_event_ptr_;
}

void ColourFlowAnalysisTool::SetEvent(CFAT_Event & event)
{
  cfat_event_ptr_ = &event;
  
}

/*void ColourFlowAnalysisTool::Fill1D(const TString & key, double value) const
{
  plots_ptr_ -> operator[](key) -> Fill(value, GetEvent() -> weight_);

  } */

void ColourFlowAnalysisTool::SetWorkMode(WorkCode_t mode)
{
  work_mode_ = mode;
  
  GetEvent() -> SetWorkMode(mode);
}


void ColourFlowAnalysisTool::PlotAngleBetweenJets() const
{
  for (VectorCode_t jet1_code = 0; jet1_code < CFAT_Event::N_jet_types_; jet1_code ++)
    {
      const TLorentzVector * jet1 = GetEvent() -> GetVector(jet1_code);
      if (not jet1)
	continue;
      for (VectorCode_t jet2_code = jet1_code + 1; jet2_code < CFAT_Event::N_jet_types_; jet2_code ++)
	{
	  const TLorentzVector * jet2 = GetEvent() -> GetVector(jet2_code);
	  if (not jet2)
	    continue;
	  const double DeltaR = GetEvent() -> DeltaR(jet1_code, jet2_code);
	  const unsigned char DeltaR_index = DeltaR < 1.0 ? DELTAR_LE_1p0 : DELTAR_GT_1p0;
          
	  const TString infix = TString(tag_jet_types_[jet1_code]) + "_:_" + 
	    tag_jet_types_[jet2_code] + "_" + 
	    tag_levels_[work_mode_] + "_"; 
	  const TString hash_key1_angle = TString("angle_") + 
	    infix +
	    tag_DeltaR_types_[DeltaR_index];


	  const double angle = GetEvent() -> Angle(jet1_code, jet2_code);
	  Fill1D(hash_key1_angle, angle);
	  const TString hash_key2_angle = TString("angle_") + 
	    infix +
	    tag_DeltaR_types_[DELTAR_TOTAL];
	  Fill1D(hash_key2_angle, angle);
          if (jet2 != CFAT_Event::beam_ptr_)
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
	    }

       	}
    }
}

void ColourFlowAnalysisTool::PlotJetDimensions() const
{
  for (VectorCode_t jet_code = 0; jet_code < CFAT_Event::N_jet_types_; jet_code ++)
    {
      const TLorentzVector *jet = GetEvent() -> GetVector(jet_code); 
      
      if (not jet)
	continue;
      const TString sufix = TString(tag_levels_[work_mode_]) + "_" +
	tag_jet_types_[jet_code];
      //printf("test %s %s \n", (TString("jet_phi_") +  sufix).Data(), (TString("jet_rapidity_") +  sufix).Data()); 
      if (jet == CFAT_Event::beam_ptr_)
	continue;
      Fill1D(TString("jet_phi_")       + sufix,  jet -> Phi());
      Fill1D(TString("jet_rapidity_")  + sufix,  jet -> Rapidity());
      Fill1D(TString("jet_eta_")       + sufix,  jet -> Eta());
      const double P = sqrt(pow(jet -> Pt(), 2) + pow(jet -> Pz(), 2));
      Fill1D(TString("jet_mass_norm_") + sufix,  jet -> M()/P);
      Fill1D(TString("jet_pt_norm_")   + sufix,  jet -> Pt()/P);
      Fill1D(TString("jet_pz_norm_")   + sufix,  jet -> Pz()/P);
      Fill1D(TString("jet_px_norm_")   + sufix,  jet -> Px()/P);

      Fill1D(TString("jet_mass_")      + sufix,  jet -> M());
      Fill1D(TString("jet_pt_")        + sufix,  jet -> Pt());
      Fill1D(TString("jet_pz_")        + sufix,  jet -> Pz());
      Fill1D(TString("jet_px_")        + sufix,  jet -> Px());

    }
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
