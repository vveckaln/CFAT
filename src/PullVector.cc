#include "PullVector.hh"
PullVector::PullVector(Double_t phi, Double_t eta): TVector2(phi, eta)
{
  origin_jet = 255;
  Ncomponents = 0;
  origin_event_ptr_ = NULL;
}

void PullVector::ls() const
{
  printf("Ls: phi %f eta %f\n", phi_component, eta_component);
}
