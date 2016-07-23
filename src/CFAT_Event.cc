
#include "CFAT_Event.hh"
#include "CFAT_Core.hh"

//const int N_jet_types_ = 12;
//const unsigned char N_charge_types_ = 2;
const TLorentzVector * CFAT_Event::beam_ptr_ = new TLorentzVector();


PullVector::PullVector(Double_t phi, Double_t eta): TVector2(phi, eta)
{
  origin_jet = 255;
  Ncomponents = 0;
  origin_event_ptr_ = NULL;
}

CFAT_Event::store_struct::store_struct() 
{
  had_W = TLorentzVector(0.0, 0.0, 0.0, 0.0); 
  had_t = TLorentzVector(0.0, 0.0, 0.0, 0.0);
  lept_W =TLorentzVector(0.0, 0.0, 0.0, 0.0);
  lept_t =TLorentzVector(0.0, 0.0, 0.0, 0.0);
  
}

CFAT_Event::store_struct::~store_struct()
{
}


CFAT_Event::CFAT_Event()  
  
{
  event_number_                    = 0;
  weight_                          = 0;
  work_mode_                       = 0;
  had_W_ptr_                       = NULL;
  had_t_ptr_                       = NULL;
  
  lept_W_ptr_                      = NULL;
  lept_t_ptr_                      = NULL;
  fake_ptr_                        = NULL;

}

void CFAT_Event::SetCore(CFAT_Core & core)
{
  core_ptr_ = &core;
}

void CFAT_Event::SetWeight(double w)
{
  weight_ = w;
}

void CFAT_Event::SetEventNumber(unsigned long numb)
{
  event_number_ = numb;
}



const TLorentzVector *& CFAT_Event::GetVectorRef(VectorCode_t code) 
{

  switch(code)
    {
    case HAD_W:
      return had_W_ptr_;
    case HAD_T:
      return had_t_ptr_;
    case LEPT_W:
      return lept_W_ptr_;
    case LEPT_T:
      return lept_t_ptr_;
    case BEAM:
      return beam_ptr_;
    case FAKE:
      return fake_ptr_;
    default:
      return GetCore() -> GetVectorRef(code);
    }

}

void CFAT_Event::SetVector(VectorCode_t code, const TLorentzVector & lv)
{
  GetVectorRef(code) = & GetStoreRef(code);
  GetStoreRef(code) = lv;
}

TLorentzVector & CFAT_Event::GetStoreRef(VectorCode_t code) 
{
  switch(code)
    {
    
    case HAD_W:
      return store_.had_W;
    case HAD_T:
      return store_.had_t;
    case LEPT_W:
      return store_.lept_W;
    case LEPT_T:
      return store_.lept_t;
    default:
      throw "TLorentzVector & CFAT_Event::GetStoreRef(VectorCode_t) : check vector code";
    }

}


const TLorentzVector * const CFAT_Event::GetVector(VectorCode_t vector_code) const
{
  return (const TLorentzVector * const) const_cast< CFAT_Event * >(this) -> GetVectorRef(vector_code);
} 
CFAT_Core * CFAT_Event::GetCore()
{
  return core_ptr_;
}

void CFAT_Event::CompleteVectors()
{
  if (GetVector(LEADING_JET) and GetVector(SCND_LEADING_JET))
    {
      SetVector(HAD_W, * GetVector(LEADING_JET) + * GetVector(SCND_LEADING_JET));
    }
  if (GetVector(Definitions::LEPTON) and GetVector(Definitions::NEUTRINO))
    {
      SetVector(LEPT_W, * GetVector(Definitions::LEPTON) + * GetVector(Definitions::NEUTRINO));
    }

  if (GetVector(HAD_W) and GetVector(HAD_B))
    {
      SetVector(HAD_T, * GetVector(HAD_W) + * GetVector(HAD_B));
    }
  if (GetVector(LEPT_W) and GetVector(LEPT_B))
    {
      SetVector(LEPT_T, * GetVector(LEPT_W) + * GetVector(LEPT_B));
    }
  
}

void CFAT_Event::SetWorkMode(WorkCode_t work_code)
{
  work_mode_ = work_code;
  GetCore() -> SetWorkMode(work_code);
}

double CFAT_Event::Angle(VectorCode_t code1, VectorCode_t code2) const
{
  const TLorentzVector * jet1 = GetVector(code1);
  const TLorentzVector * jet2 = GetVector(code2);
  if (not jet1 or not jet2)
    throw "CFAT_Event::Angle(VectorCode_t, VectorCode_t) : null vectors. Please Check!";
  if (jet1 == beam_ptr_)
    {
      if (jet2 == beam_ptr_)
	return 0.0;
      else
	return TMath::ACos(jet2 -> Pz() / jet2 -> Vect().Mag());
    }
  else
    { 
      if (jet2 == beam_ptr_)
	return TMath::ACos(jet1 -> Pz() / jet1 -> Vect().Mag());
      else
	return jet1 -> Angle(jet2 -> Vect());
    }
}

double CFAT_Event::DeltaR(VectorCode_t code1, VectorCode_t code2) const
{
  const TLorentzVector * jet1 = GetVector(code1);
  const TLorentzVector * jet2 = GetVector(code2);
  if (not jet1 or not jet2)
    throw "CFAT_Event::DeltaR(VectorCode_t, VectorCode_t) : null vectors. Please Check!";
  if (jet1 == beam_ptr_)
    {
      if (jet2 == beam_ptr_)
	return 0.0;
      else
	return 100.0;
    }
  else
    { 
      if (jet2 == beam_ptr_)
	return 100.0;
      else
	return jet1 -> DeltaR(*jet2);
    }
}

double CFAT_Event::PullAngle(const PullVector & pv, VectorCode_t code2) const
{
  const TLorentzVector * jet1 = GetVector(pv.origin_jet);
  const TLorentzVector * jet2 = GetVector(code2);
  //printf("Calculating pull angle Pt %f Phi %f Rapidity %f \n", jet2 -> Pt(), jet2 -> Phi(), jet2 -> Rapidity());
  if (not jet1 or not jet2)
    throw "double CFAT_Event::PullAngle(const PullVector &, VectorCode_t) : null vectors. Please Check!";
  if (pv.Mod() < 1E-10)
    throw "double CFAT_Event::PullAngle(const PullVector &, VectorCode_t) : zero pull vector";
 
  if (jet2 == beam_ptr_)
    return TMath::ACos(pv.eta_component / pv.Mod());
  else
    {
      
      const TVector2 jet_difference(jet2 -> Phi() - jet1 -> Phi(), jet2 -> Rapidity() - jet1 -> Rapidity());
      /*{
	PullVector pull_vector = pv;
	const float magnitude_pull = pull_vector.Mod();
	const float phi_dif = jet_difference.Px();
	const float eta_dif = jet_difference.Py();
	const float magnitude_dif = sqrt(phi_dif*phi_dif + eta_dif*eta_dif);
	float pull_angle = 0;
	
	    const float cos_pullangle = (pull_vector.phi_component*phi_dif + pull_vector.eta_component*eta_dif)/
	      (magnitude_pull * magnitude_dif);
	    pull_angle = TMath::ACos(cos_pullangle);
	    if (pull_vector.eta_component - eta_dif < 0) 
	      pull_angle *= -1;
	    printf("check result %f \n", pull_angle);
      }	  
      const double result = TVector2::Phi_mpi_pi(jet_difference.Phi() - pv.Phi());
      printf(" result %f \n", result);*/
      return TVector2::Phi_mpi_pi(jet_difference.Phi() - pv.Phi());//Must be pv.Phi()
    }
      
}

/*
PullVector CFAT_Event::CalculatePullVector(VectorCode_t vector_code, ChargeCode_t charge_code, PF_PTCutCode_t pf_ptcut_code) const
{
  PullVector ret(0.0, 0.0);
  
  ret.origin_jet = vector_code;
  ret.origin_event_ptr_ = this;
  TLorentzVector charged_jet;
  if (charge_code == CHARGED)
    charged_jet = GetChargedJet(vector_code);
  const TLorentzVector * jet = charge_code == ALLCOMP ? GetVector(vector_code) : & charged_jet;
  const TVector2 jetV2(jet -> Phi(), jet -> Rapidity());
  double Pt_jet_constituents = 0.0;
  for (unsigned int jet_const_index = 0; jet_const_index < PF.size; jet_const_index ++)
    {
      TLorentzVector constituent_4vector ;
      if (PF.jet_index[jet_const_index] != GetIndex(vector_code))
	continue;
      if (charge_code == CHARGED and PF.charge[jet_const_index] == 0)
	continue;
      constituent_4vector = PF.GetPF(jet_const_index);
      if (pf_ptcut_code == PF_PT_LE_0p5_GEV and constituent_4vector.Pt() > 0.5)
	continue;
      if (pf_ptcut_code == PF_PT_GT_0p5_GEV and constituent_4vector.Pt() <= 0.5)
	continue;
      Pt_jet_constituents += constituent_4vector.Pt();
      const TVector2 componentV2 = TVector2(
					  TVector2::Phi_mpi_pi(constituent_4vector.Phi()), 
					  constituent_4vector.Rapidity())
	- jetV2;
      const double mag = componentV2.Mod();
      ret += mag * componentV2 * constituent_4vector.Pt();
      ret.Ncomponents ++;
    }
  if (Pt_jet_constituents < 1E-10)
    throw "PullVector CFAT_Event::CalculatePullVector(VectorCode_t, ChargeCode_t, PF_PTCutCode_t) const: Zero components";
  const double scale =  Pt_jet_constituents;
  ret /= scale;
  return ret;
  }*/
/*
TLorentzVector CFAT_Event::GetChargedJet(VectorCode_t vector_code) const
{
  TLorentzVector charged_jet(0, 0, 0, 0);
  for (unsigned int jet_const_index = 0; jet_const_index < PF.size; jet_const_index ++)
    {
      TLorentzVector constituent_4vector ;
      if (PF.jet_index[jet_const_index] != GetIndex(vector_code))
	continue;
      if (PF.charge[jet_const_index] == 0)
	continue;
      constituent_4vector = PF.GetPF(jet_const_index);
      charged_jet += constituent_4vector;
      
    }
    
  return charged_jet;
}
*/