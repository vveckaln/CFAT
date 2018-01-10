#include <cmath>
#include "CFAT_Core.hh"
#include "PullVector.hh"
#include "ColourFlowAnalysisTool.hh"

PullVector CFAT_Core::CalculatePullVectorEXP(VectorCode_t vector_code, VectorCode_t vector_code2, ChargeCode_t charge_code, PF_PTCutCode_t pf_ptcut_code) 
{
  PullVector ret(0.0, 0.0);
  ret.origin_jet = vector_code;
  ret.origin_core_ptr_ = this;
  //  const TLorentzVector charged_jet = GetChargedJet(vector_code);

  const TLorentzVector *jet1 = /*charge_code == CHARGED ? & charged_jet : */GetVector(vector_code);
  TLorentzVector jet1_unboost = *jet1;
  const TLorentzVector *jet2 = GetCFATEvent() -> GetVector(vector_code2);
  TLorentzVector jet2_unboost = *jet2;
  TLorentzVector jetsum = *jet1 + *jet2;
  const double Msum = jetsum.M();
  const double b_sum = jetsum.P()/sqrt(pow(Msum, 2) + pow(jetsum.P(), 2));
  const double bx_sum = b_sum * jetsum.Px()/jetsum.P(); 
  const double by_sum = b_sum * jetsum.Py()/jetsum.P();
  const double bz_sum = b_sum * jetsum.Pz()/jetsum.P();

  const double Mjet = jet1 -> M();
  const double Pjet = jet1 -> P();
  const double b_jet = Pjet/sqrt(pow(Mjet, 2) + pow(Pjet, 2));
  const double bx_jet = b_jet * jet1 -> Px()/Pjet; 
  const double by_jet = b_jet * jet1 -> Py()/Pjet;
  const double bz_jet = b_jet * jet1 -> Pz()/Pjet;


  jet1_unboost.Boost(-bx_sum, -by_sum, -bz_sum);

  double Pt_jet_constituents = 0.0;
  unsigned short jet_const_index = 0;
  unsigned char ind = 0;  
  for(pf_iter it = begin(vector_code); it != end(vector_code); it ++)
    {
      
      TLorentzVector constituent_4vector ;
      if (charge_code == CHARGED and it -> GetCharge() == 0)
	continue;
      constituent_4vector = it -> GetLorentzVector();
      constituent_4vector.Boost(-bx_jet, -by_jet, -bz_jet);
      jet_const_index ++; 
      Pt_jet_constituents += constituent_4vector.Pt();
      const TVector2 componentV2 = TVector2(
					    TVector2::Phi_mpi_pi(constituent_4vector.Phi() - jet1_unboost.Phi()), 
					    constituent_4vector.Rapidity() - jet1_unboost.Rapidity());
      //  printf("ind %u component rapidity %f phi %f diference rapidity %f phi %f\n", ind, constituent_4vector.Rapidity(), constituent_4vector.Phi(), componentV2.Py(), componentV2.Px());
      ind ++;
      if (std::isnan(constituent_4vector.Phi()))
	{
	  printf("constituent_4vector.Phi() not a number. Continuing to next component\n");
	  continue;
	}
      const double mag = componentV2.Mod();
      ret += mag * componentV2 * constituent_4vector.Pt();
      ret.Ncomponents ++;
      if (vector_code2 == SCND_LEADING_JET)
	{
	  GetCFATEvent() -> GetCFAT() -> Fill1D(TString("beta_jetsum_lab_frame")   + "_" + tag_jet_types_[HAD_W] + "_" + tag_levels_types_[work_mode_], b_sum);
	  GetCFATEvent() -> GetCFAT() -> Fill1D(TString("beta_jet_lab_frame")      + "_" + tag_levels_types_[work_mode_], b_jet);

	  GetCFATEvent() -> GetCFAT() -> Fill1D(TString("beta_jet_jetsum_frame")   + "_" + tag_levels_types_[work_mode_], jet1_unboost.P()/sqrt(pow(jet1_unboost.P(), 2) + pow(jet1_unboost.M(), 2)));
	  GetCFATEvent() -> GetCFAT() -> Fill1D(TString("beta_particle_jet_frame") + "_" + tag_levels_types_[work_mode_], constituent_4vector.P()/sqrt(pow(constituent_4vector.P(), 2) + pow(constituent_4vector.M(), 2)));
	}
    }
  if (Pt_jet_constituents < 1E-10)
    {
      throw "PullVector CFAT_Event::CalculatePullVectorEXP(VectorCode_t, ChargeCode_t, PF_PTCutCode_t) const: Zero components";
    }
  
  const double scale = Pt_jet_constituents;
  ret /= scale;
  // printf ("pull vector Mod %f\n", ret.Mod());
  if (std::isnan(ret.phi_component))
    {
      throw "PullVector CFAT_Event::CalculatePullVectorEXP(VectorCode_t, ChargeCode_t, PF_PTCutCode_t) const: pull vector phi component NaN";

    }
  if (std::isnan(ret.eta_component))
    {
      throw "PullVector CFAT_Event::CalculatePullVectorEXP(VectorCode_t, ChargeCode_t, PF_PTCutCode_t) const: pull vector eta component NaN";

    }
  return ret;
  printf("PullVector CFAT_Core::CalculatePullVectorEXP END\n");

}
