#ifndef _pf_hh_
#define _pf_hh_
#include "TLorentzVector.h"
class pf
{
  
public:
  virtual double GetCharge() const = 0;
  virtual TLorentzVector GetLorentzVector() const = 0;
  
  virtual void ls() const;

  void Do();
};
#endif
