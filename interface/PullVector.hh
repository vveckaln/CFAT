
#ifndef _PullVector_hh_
#define _PullVector_hh_

#include "TVector2.h"
#include "Definitions.hh"
using namespace Definitions;
class CFAT_Event;
class CFAT_Core;
struct PullVector: public TVector2
{
  PullVector();
  void               SetPhiComponent(Double_t);
  void               SetRapidityComponent(Double_t);
  Double_t           GetPhiComponent() const;
  Double_t           GetRapidityComponent() const;
  unsigned short     Ncomponents;
  VectorCode_t       origin_jet;
  void ls() const;
  const CFAT_Core  * origin_core_ptr_;
  const CFAT_Event * origin_event_ptr_;
private:
  PullVector(Double_t, Double_t);
  Double_t           & rapidity_component_ = fX;
  Double_t           & phi_component_ = fY;
};
#endif
