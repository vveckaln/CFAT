
#include "CFAT_Event.hh"
#include "CFAT_Core.hh"
#include "PullVector.hh"
//const int N_jet_types_ = 12;
//const unsigned char N_charge_types_ = 2;
const TLorentzVector * CFAT_Event::beam_ptr_ = new TLorentzVector();




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
  work_mode_                       = 0;
  had_W_ptr_                       = NULL;
  had_t_ptr_                       = NULL;
  
  lept_W_ptr_                      = NULL;
  lept_t_ptr_                      = NULL;
  fake_ptr_                        = NULL;
  cfat_                            = NULL;
  core_ptr_                        = NULL;
}

void CFAT_Event::SetCore(CFAT_Core & core)
{
  core_ptr_ = &core;
  core.cfat_event_ = this;
}

void CFAT_Event::SetWeights(vector<double> w)
{
  weights_ = w;
}

vector<double> CFAT_Event::GetWeights() const
{
  return weights_;
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

ColourFlowAnalysisTool * CFAT_Event::GetCFAT()
{
  return cfat_;
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
	if ((code1 == HAD_B or code1 == HAD_T) and (code2 == HAD_B or code2 == HAD_T) and work_mode_ == 0)
	  
	  	  {
		    /*  printf("code1 %u code2 %u\n", code1, code2);
	    printf("jet 1 px %f py %f pz %f\n", jet1 -> Px(), jet1 -> Py(), jet1 -> Pz());
	    printf("jet 2 px %f py %f pz %f\n", jet2 -> Px(), jet2 -> Py(), jet2 -> Pz());
	    printf("angle %f\n", jet1 -> Angle(jet2 -> Vect()));
	    printf("angle %f\n", jet1 -> Vect() . Angle(jet2 -> Vect()));
	    printf("angle %f\n", TVector3(jet1 -> Px(), jet1 -> Py(), 0.0).Angle(TVector3(jet2 -> Px(), jet2 -> Py(), 0.0)));
	    getchar();
	  */  }
	return jet1 -> Angle(jet2 -> Vect());
    }
}

double CFAT_Event::DeltaR(VectorCode_t code1, VectorCode_t code2) const
{
  const TLorentzVector * jet1 = GetVector(code1);
  const TLorentzVector * jet2 = GetVector(code2);
  if (not jet1 or not jet2)
    {
      printf("vc1 %u %p vc2 %u %p\n", code1, jet1, code2, jet2);
      throw "CFAT_Event::DeltaR(VectorCode_t, VectorCode_t) : null vectors. Please Check!";
    }
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
      
      const TVector2 jet_difference(TVector2::Phi_mpi_pi(jet2 -> Phi() - jet1 -> Phi()), jet2 -> Rapidity() - jet1 -> Rapidity());
      
      
  
     
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
      if (std::isnan(jet_difference.Phi() - pv.Phi()))
	{
	  throw "double CFAT_Event::PullAngle(const PullVector & pv, VectorCode_t code2) const: result NaN";
	}
      return TVector2::Phi_mpi_pi(jet_difference.Phi() - pv.Phi());//Must be pv.Phi()
    }
      
}

double CFAT_Event::PullAngleEXP(const PullVector & pv, VectorCode_t code2) const
{

  //printf("double CFAT_Event::PullAngleEXP START\n");
  const TLorentzVector * jet1 = GetVector(pv.origin_jet);
  const TLorentzVector * jet2 = GetVector(code2);
  if (not jet1 or not jet2)
    throw "double CFAT_Event::PullAngle(const PullVector &, VectorCode_t) : null vectors. Please Check!";
  if (pv.Mod() < 1E-10)
    throw "double CFAT_Event::PullAngle(const PullVector &, VectorCode_t) : zero pull vector";
 
  if (jet2 == beam_ptr_)
    return TMath::ACos(pv.eta_component / pv.Mod());
  else
    {
      TLorentzVector jet1_unboost = *jet1;
      TLorentzVector jet2_unboost = *jet2;
      const TLorentzVector sumjet = *jet1 + *jet2;
      const double Msum = sumjet . M();
      const double b_sumjet = sumjet. P()/sqrt(pow(Msum, 2) + pow(sumjet.P(), 2));
      const double bz_sumjet = b_sumjet * sumjet.Pz()/sumjet.P();
      const double bx_sumjet = b_sumjet * sumjet.Px()/sumjet.P(); 
      const double by_sumjet = b_sumjet * sumjet.Py()/sumjet.P(); 
      jet1_unboost.Boost(-bx_sumjet, -by_sumjet, -bz_sumjet);
      jet2_unboost.Boost(-bx_sumjet, -by_sumjet, -bz_sumjet);
      const TVector2 jet_difference(/*jet2_unboost.Phi() - jet1_unboost.Phi()*/ 0.0, jet2_unboost.Rapidity() - jet1_unboost.Rapidity());
      //      printf("jet diff px %f py %f pv px %f py %f\n", jet_difference.Px(), jet_difference.Py(), pv.Px(), pv.Py());
      if (std::isnan(jet_difference.Phi() - pv.Phi()))
	{
	  throw "double CFAT_Event::PullAngleEXP(const PullVector & pv, VectorCode_t code2) const: result NaN";
	}
   
      return TVector2::Phi_mpi_pi(jet_difference.Phi() - pv.Phi());//Must be pv.Phi()
    }
  printf("double CFAT_Event::PullAngleEXP END\n");
      
}


unsigned long CFAT_Event::GetEventNumber() const
{
  return event_number_;
}

double CFAT_Event::GetEventEnergy() const
{
  return GetVector(HAD_B) -> E() + GetVector(HAD_W) -> E() + GetVector(LEPT_B) -> E() + GetVector(LEPT_W) -> E();
}

double CFAT_Event::GetEventPt() const
{
  return GetVector(HAD_B) -> Pt() + GetVector(HAD_W) -> Pt() + GetVector(LEPT_B) -> Pt() + GetVector(LEPT_W) -> Pt();

}
