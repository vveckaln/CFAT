
#include "CFAT_Core.hh"
 
void pf::Do()
{
  printf("Hello from pf %p\n", this);
}

void pf::ls_particle() const
{
  const TLorentzVector  lv = GetLorentzVector();
  printf("Pt %f Px %f Py %f Pz %f E %f\n", lv.Pt(), lv.Px(), lv.Py(), lv.Pz(), lv.E());
}


CFAT_Core::pf_iter::pf_iter()
{
  iter_core_ptr_ = NULL;
  CanDelete_ = true;
}



CFAT_Core::pf_iter::pf_iter(pf_iter && other): iter_core_ptr_(other.iter_core_ptr_), CanDelete_(other.CanDelete_)
{
  other.iter_core_ptr_ = NULL;
}

CFAT_Core::pf_iter::pf_iter(const pf_iter & other): iter_core_ptr_(other.iter_core_ptr_), CanDelete_(other.CanDelete_)
{
  core_ptr_ = NULL;
}

CFAT_Core::pf_iter_core * CFAT_Core::pf_iter::GetIterCore() const
{
  return iter_core_ptr_;
}

void CFAT_Core::pf_iter::SetCore(CFAT_Core & other)
{
  core_ptr_ = & other;
}

void CFAT_Core::pf_iter::SetIterCore(pf_iter_core & other)
{
  iter_core_ptr_ = & other;
}

void CFAT_Core::pf_iter::SetDeleteOption(bool option)
{
  CanDelete_ = option;
}


CFAT_Core::pf_iter::~pf_iter()
{
  if (iter_core_ptr_ and CanDelete_)
    {
      delete iter_core_ptr_;
      iter_core_ptr_ = NULL;
    }
}

pf * CFAT_Core::pf_iter::operator -> ()
{
  return iter_core_ptr_ -> particle_ptr_; 
}

bool CFAT_Core::pf_iter::operator != (const pf_iter & other)
{
  
  return iter_core_ptr_ -> compare(other.iter_core_ptr_); 
}


CFAT_Core::pf_iter CFAT_Core::pf_iter::operator ++ (int)
{
  pf_iter ret = *this;
  core_ptr_ -> increment(*this);
  return ret;
}

CFAT_Core::pf_iter_core::pf_iter_core(pf * particle ): particle_ptr_(particle)
{
  tracked_vector_ = 255;
}

CFAT_Core::pf_iter_core::~pf_iter_core()
{
}

void CFAT_Core::pf_iter_core::Do()
{
  printf("Hello from CFAT_Core::pf_iter_core %p\n", this);
}

void CFAT_Core::pf_iter_core::WhoAmI()
{
  printf("I am CFAT_Core::pf_iter_core %p\n", this);
}

TLorentzVector CFAT_Core::GetChargedJet(VectorCode_t vector_code) 
{
  TLorentzVector charged_jet(0, 0, 0, 0);
  for(pf_iter it = begin(vector_code); it != end(vector_code); it ++)
    {
      //printf("index %u\n", ((pf_cmssw*)it.operator->()) -> index_);
      TLorentzVector constituent_4vector ;
      
      if (it -> GetCharge() == 0)
	continue;
      constituent_4vector = it -> GetLorentzVector();
      charged_jet += constituent_4vector;
      
    }
  return charged_jet;
}



PullVector CFAT_Core::CalculatePullVector(VectorCode_t vector_code, ChargeCode_t charge_code, PF_PTCutCode_t pf_ptcut_code) 
{
  PullVector ret(0.0, 0.0);
  ret.origin_jet = vector_code;
  ret.origin_core_ptr_ = this;
  const TLorentzVector charged_jet = GetChargedJet(vector_code);
  const TLorentzVector *jet = charge_code == CHARGED ? & charged_jet : GetVector(vector_code);
  double Pt_jet_constituents = 0.0;
  unsigned short jet_const_index = 0;
  for(pf_iter it = begin(vector_code); it != end(vector_code); it ++)
    {
      
      TLorentzVector constituent_4vector ;
      if (charge_code == CHARGED and it -> GetCharge() == 0)
	continue;
      constituent_4vector = it -> GetLorentzVector();
      if (pf_ptcut_code == PF_PT_LE_0p5_GEV and constituent_4vector.Pt() > 0.5)
	continue;
      if (pf_ptcut_code == PF_PT_GT_0p5_GEV and constituent_4vector.Pt() <= 0.5)
	continue;
      jet_const_index ++; 
      Pt_jet_constituents += constituent_4vector.Pt();
      
      const TVector2 componentV2 = TVector2(
					    TVector2::Phi_mpi_pi(constituent_4vector.Phi() - jet -> Phi()), 
					    constituent_4vector.Rapidity() - jet -> Rapidity());
      if (std::isnan(constituent_4vector.Phi()))
	{
	  printf("constituent_4vector.Phi() not a number. Continuing to next component\n");
	  continue;
	}
      const double mag = componentV2.Mod();
      ret += mag * componentV2 * constituent_4vector.Pt();
      ret.Ncomponents ++;
    }
  if (Pt_jet_constituents < 1E-10)
    {
      throw "PullVector CFAT_Event::CalculatePullVector(VectorCode_t, ChargeCode_t, PF_PTCutCode_t) const: Zero components";
    }
  
  const double scale = Pt_jet_constituents;
  ret /= scale;
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
