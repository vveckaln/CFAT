#include "PullVector.hh"
PullVector::PullVector(): TVector2()
{
  origin_jet = 255;
  Ncomponents = 0;
  origin_event_ptr_ = NULL;
}
PullVector::PullVector(Double_t rapidity, Double_t phi): TVector2(rapidity, phi)
{
  origin_jet = 255;
  Ncomponents = 0;
  origin_event_ptr_ = NULL;
}

void PullVector::SetPhiComponent(Double_t phi)
{
  phi_component_ = phi;
}

void PullVector::SetRapidityComponent(Double_t rapidity)
{
  rapidity_component_ = rapidity;
}


Double_t PullVector::GetPhiComponent() const
{
  return phi_component_;
}

Double_t PullVector::GetRapidityComponent() const 
{
  return rapidity_component_;
}


void PullVector::ls() const
{
  printf("Ls: phi %f rapidity %f\n", GetPhiComponent(), GetRapidityComponent());
}
