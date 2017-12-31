
#ifndef _PullVector_hh_
#define _PullVector_hh_

#include "TVector2.h"
#include "Definitions.hh"
using namespace Definitions;
class CFAT_Event;
class CFAT_Core;
struct PullVector: public TVector2
{
  PullVector(Double_t, Double_t);
  Double_t           & phi_component = fX;
  Double_t           & eta_component = fY;
  unsigned short     Ncomponents;
  VectorCode_t       origin_jet;
  void ls() const;
  const CFAT_Core  * origin_core_ptr_;
  const CFAT_Event * origin_event_ptr_;
};
#endif
