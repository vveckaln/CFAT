#include "ColourFlowAnalysisTool.hh"
#include "CFAT_Core.hh"


CFAT_Core::CFAT_Core()
{
  cfat_event_ = NULL;
  event_display_mode_ = 0;
}

CFAT_Event * CFAT_Core::GetCFATEvent()
{
  return cfat_event_;
}

TLorentzVector CFAT_Core::GetJetFromParticles(VectorCode_t vector_code, ChargeCode_t charge_code) 
{
  TLorentzVector calculated_jet(0, 0, 0, 0);
  for(pf_iter it = begin(vector_code); it != end(vector_code); it ++)
    {
      //printf("index %u\n", ((pf_cmssw*)it.operator->()) -> index_);
      TLorentzVector constituent_4vector ;
      
      if (charge_code == CHARGED and it -> GetCharge() == 0)
	continue;
      constituent_4vector = it -> GetLorentzVector();
      calculated_jet += constituent_4vector;
      
    }
  return calculated_jet;
}

PullVector CFAT_Core::CalculatePullVector(VectorCode_t vector_code, ChargeCode_t charge_code, PF_PTCutCode_t pf_ptcut_code) 
{
  PullVector ret(0.0, 0.0);
  ret.origin_jet = vector_code;
  ret.origin_core_ptr_ = this;
  //  const TLorentzVector charged_jet = GetChargedJet(vector_code);
  const TLorentzVector *jet = /*charge_code == CHARGED ? & charged_jet : */GetVector(vector_code);
  const TLorentzVector dumm = GetJetFromParticles(vector_code, charge_code);
  //  printf("dumm %f %f %u %u\n", dumm.Px(), dumm.Pz(), vector_code, charge_code);
  const TLorentzVector * jet_test = GetVector(vector_code, "particle", charge_code); //GetJetFromParticles(vector_code, charge_code);
  if (not jet_test)
    throw "no jet";


  if (fabs(jet_test -> Eta()) > 2.1) 
    throw "abs(eta) > 2.1 ";
  jet = jet_test;

  double Pt_jet_constituents = 0.0;
  unsigned short jet_const_index = 0;
  //  printf(" work_mode_ %u, vector_code %u charge_code %u  pf_ptcut_code %u\n", work_mode_, vector_code, charge_code, pf_ptcut_code);
  //printf("jet rapidity %f phi %f\n", jet -> Rapidity(), jet -> Phi());
  unsigned char ind = 0;  
  //  printf("pf_ptcut_code %u %u\n", pf_ptcut_code, PF_PT_GT_1p0_GEV);
  for(pf_iter it = begin(vector_code); it != end(vector_code); it ++)
    {
      
      TLorentzVector constituent_4vector ;
      if (charge_code == CHARGED and it -> GetCharge() == 0)
	continue;
      constituent_4vector = it -> GetLorentzVector();
      //  printf("pt %f \n", constituent_4vector.Pt());
      if (pf_ptcut_code == PF_PT_LE_0p5_GEV and constituent_4vector.Pt() > 0.5)
	continue;
      if (pf_ptcut_code == PF_PT_GT_0p5_GEV and constituent_4vector.Pt() <= 0.5)
	continue;
      if (pf_ptcut_code == PF_PT_GT_1p0_GEV and constituent_4vector.Pt() <= 1.0)
	{
	  //  printf("cont'ing\n");
	  continue;
	}
      jet_const_index ++; 
      Pt_jet_constituents += constituent_4vector.Pt();
      const TVector2 componentV2 = TVector2(
					    TVector2::Phi_mpi_pi(constituent_4vector.Phi() - jet -> Phi()), 
					    constituent_4vector.Rapidity() - jet -> Rapidity());
      //  printf("ind %u component rapidity %f phi %f diference rapidity %f phi %f\n", ind, constituent_4vector.Rapidity(), constituent_4vector.Phi(), componentV2.Py(), componentV2.Px());
      ind ++;
      if (std::isnan(constituent_4vector.Phi()))
	{
	  printf("constituent_4vector.Phi() not OAa number. Continuing to next component\n");
	  continue;
	}
      const double mag = componentV2.Mod();
      ret += mag * componentV2 * constituent_4vector.Pt();
      ret.Ncomponents ++;
    }
  //  printf("*************************\n");
  if (Pt_jet_constituents < 1E-10)
    {
      throw "PullVector CFAT_Event::CalculatePullVector(VectorCode_t, ChargeCode_t, PF_PTCutCode_t) const: Zero components";
    }
  
  const double scale = Pt_jet_constituents;
  ret /= scale;
  // printf ("pull vector Mod %f\n", ret.Mod());
  if (std::isnan(ret.phi_component))
    {
      throw "PullVector CFAT_Event::CalculatePullVector(VectorCode_t, ChargeCode_t, PF_PTCutCode_t) const: pull vector phi component NaN";

    }
  if (std::isnan(ret.eta_component))
    {
      throw "PullVector CFAT_Event::CalculatePullVector(VectorCode_t, ChargeCode_t, PF_PTCutCode_t) const: pull vector eta component NaN";

    }
  /*
  printf(" CHECK CHECK !!!!!! CHECK CHECK \n");
  {
    float phi_component = 0;
    float eta_component = 0;
    const float jet_phi = jet -> Phi();
    const float jet_eta = jet -> Rapidity();
    float Pt_jet_constituents = 0;
    MiniEvent_t * event_ptr_ = ((CFAT_Core_cmssw*) this) -> GetEvent();
    unsigned int size = work_mode_ == 0 ? event_ptr_ -> npf : event_ptr_ -> ngpf;
    for (unsigned int jet_const_index = 0; jet_const_index < size; jet_const_index ++)
      {
	TLorentzVector constituent_4vector;
	if (work_mode_ == 0)
	  {
	    if (event_ptr_ -> pf_j[jet_const_index] != ((CFAT_Core_cmssw*) this) -> GetIndex(LEADING_JET))
	      continue;
	    if (false and event_ptr_ -> pf_c[jet_const_index] == 0)
	      continue;
	    constituent_4vector.SetPtEtaPhiM(event_ptr_ -> pf_pt[jet_const_index], 
					     event_ptr_ -> pf_eta[jet_const_index], 
					     event_ptr_ -> pf_phi[jet_const_index], 
					     event_ptr_ -> pf_m[jet_const_index]
					     );
	    printf(" jet_const_index %u jet index %u Pt %f Px %f Py %f Pz %f E %f \n", jet_const_index, ((CFAT_Core_cmssw*) this) -> GetIndex(LEADING_JET), constituent_4vector.Pt(), constituent_4vector.Px(), constituent_4vector.Py(), constituent_4vector.Pz(), constituent_4vector.E());
	  }
	
	Pt_jet_constituents += constituent_4vector.Pt();
	const float delta_phi = TVector2::Phi_mpi_pi(constituent_4vector.Phi() - jet_phi);
	const float delta_eta = constituent_4vector.Rapidity() - jet_eta;
	const float mag = sqrt(delta_phi*delta_phi + delta_eta*delta_eta);
	phi_component += mag * delta_phi * constituent_4vector.Pt();
	eta_component += mag * delta_eta * constituent_4vector.Pt();
	
      }
    if (Pt_jet_constituents < 1E-6)
      throw "Zero components";
    const float scale = OnlyChargedConstituents ? Pt_jet_constituents;
    phi_component /= scale;
    eta_component /= scale;
    printf("check phi %f eta %f\n", phi_component, eta_component);
}
  printf(" ********************************************************* \n");
  printf("pv result phi %f eta %f\n", ret.phi_component, ret.eta_component);
  getchar();*/
  return ret;
}

void CFAT_Core::AnalyseJetConstituents() 
{
  const ColourFlowAnalysisTool * cfat = GetCFATEvent() -> GetCFAT();
  static const unsigned char jets[4] = {LEADING_JET, SCND_LEADING_JET, LEADING_B, SCND_LEADING_B};
  float Ncharged[4]; float Nall[4];
  float Echarged[4]; float Eall[4];
  for (unsigned char charge_code = 0; charge_code < N_charge_types_; charge_code ++)
    {
      const TString hist_title_Eventenergy = TString("JetConst_EventE_") + tag_charge_types_[charge_code] + "_" + tag_levels_types_[work_mode_];
      float energy_leading_jet = 0.0;
      float energy_2nd_leading_jet = 0.0;
	   

      for (unsigned char jet_index = 0; jet_index < 4; jet_index ++)
	{
	  const unsigned char vector_code = jets[jet_index];


	  float Totalenergy = 0.0;
	  float Totalpx = 0.0;
	  float Totalpy = 0.0;
	  float Totalpz = 0.0;
	  unsigned int N = 0;
	  const TString hist_title_energy      = TString("JetConst_E_")       + tag_charge_types_[charge_code] + "_" + tag_levels_types_[work_mode_] + "_" + tag_jet_types_[vector_code];
	  const TString hist_title_Totalenergy = TString("JetConst_TotalE_")  + tag_charge_types_[charge_code] + "_" + tag_levels_types_[work_mode_] + "_" + tag_jet_types_[vector_code];
	  const TString hist_title_Totalpx     = TString("JetConst_TotalPx_") + tag_charge_types_[charge_code] + "_" + tag_levels_types_[work_mode_] + "_" + tag_jet_types_[vector_code];
	  const TString hist_title_Totalpy     = TString("JetConst_TotalPy_") + tag_charge_types_[charge_code] + "_" + tag_levels_types_[work_mode_] + "_" + tag_jet_types_[vector_code];
	  const TString hist_title_Totalpz     = TString("JetConst_TotalPz_") + tag_charge_types_[charge_code] + "_" + tag_levels_types_[work_mode_] + "_" + tag_jet_types_[vector_code];

	  const TString hist_title_pt          = TString("JetConst_Pt_")      + tag_charge_types_[charge_code] + "_" + tag_levels_types_[work_mode_] + "_" + tag_jet_types_[vector_code];
	  const TString hist_title_m           = TString("JetConst_M_")       + tag_charge_types_[charge_code] + "_" + tag_levels_types_[work_mode_] + "_" + tag_jet_types_[vector_code];
	  const TString hist_title_N           = TString("JetConst_N_")       + tag_charge_types_[charge_code] + "_" + tag_levels_types_[work_mode_] + "_" + tag_jet_types_[vector_code];

	  for(pf_iter it = begin(vector_code); it != end(vector_code); it ++)
	    {
	      if (charge_code == CHARGED and it -> GetCharge() == 0)
		continue;
	      N ++;
	      TLorentzVector particle = it -> GetLorentzVector();
	      Totalenergy += particle.E();
	      Totalpx += particle.Px();
	      Totalpy += particle.Py();
	      Totalpz += particle.Pz();
 	      cfat -> Fill1D(hist_title_energy, particle.E());
 	      cfat -> Fill1D(hist_title_pt, particle.Pt());
	      cfat -> Fill1D(hist_title_m, particle.M());
	      //	      if (work_mode_ == 1)
	      //printf("mass %.9f charge %f\n", particle.M(), it -> GetCharge());
	    }
	  cfat -> Fill1D(hist_title_Totalenergy, Totalenergy);
	  // cfat -> Fill1D(hist_title_Totalpx, Totalpx);
	  // cfat -> Fill1D(hist_title_Totalpy, Totalpy);
	  // cfat -> Fill1D(hist_title_Totalpz, Totalpz);
	  cfat -> Fill1D(hist_title_N, N);
	  
	  if (vector_code == LEADING_JET)
	    energy_leading_jet = Totalenergy;
	 
	  else if (vector_code == SCND_LEADING_JET)
	    energy_2nd_leading_jet = Totalenergy;
	  if (charge_code == CHARGED)
	    {
	      Ncharged[jet_index] = N;
	      Echarged[jet_index] = Totalenergy;
	    }
	  else if (charge_code == ALLCOMP)
	    {
	      Nall[jet_index] = N;
	      Eall[jet_index] = Totalenergy;
	    }


	}
      cfat -> Fill1D(hist_title_Eventenergy, energy_leading_jet + energy_2nd_leading_jet);
      

    }
    for (VectorCode_t jet_index = 0; jet_index < 4; jet_index ++)
    {
      const unsigned char vector_code = jets[jet_index];
      const TString hist_title_EventChargedContentN = TString("JetConst_EventChargedContentN_") + tag_levels_types_[work_mode_] + "_" + tag_jet_types_[vector_code];
      const TString hist_title_EventChargedContentE = TString("JetConst_EventChargedContentE_") + tag_levels_types_[work_mode_] + "_" + tag_jet_types_[vector_code];
      cfat -> Fill1D(hist_title_EventChargedContentN, Ncharged[jet_index]/Nall[jet_index]);
      cfat -> Fill1D(hist_title_EventChargedContentE, Echarged[jet_index]/Eall[jet_index]);
    }

}

void CFAT_Core::SetEventDisplayMode(unsigned char mode)
{
  event_display_mode_ = mode;
}

void CFAT_Core::ls_particles(VectorCode_t vector_code, ChargeCode_t charge_code)
{
  unsigned int ind = 0;
  printf("\nCFAT_Core listing particles of vector %u\n", vector_code);
  for(pf_iter it = begin(vector_code); it != end(vector_code); it ++)
    {
      if (charge_code == CHARGED and it -> GetCharge() == 0)
	continue;
      const TLorentzVector particle = it -> GetLorentzVector(); 
      printf("ind %u, phi %f, eta %f, pt %f, m %f\n", ind, particle.Phi(), particle.Eta(), particle.Pt(), particle.M());
      ind ++;
    }
  printf("Listing done\n");
}
