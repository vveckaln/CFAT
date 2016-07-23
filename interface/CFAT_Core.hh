
#ifndef _CFAT_Core_hh_
#define _CFAT_Core_hh_
#include "CFAT_Event.hh"
#include "Definitions.hh"

#include "TLorentzVector.h"

class pf
{
  
public:
  virtual double GetCharge() const = 0;
  virtual TLorentzVector GetLorentzVector() const = 0;
  void ls_particle() const;
  void Do();
};

class CFAT_Core
{
  friend class CFAT_Event;
  friend class ColourFlowAnalysisTool;
protected:
  virtual const TLorentzVector *& GetVectorRef(VectorCode_t code) = 0; 

  WorkCode_t work_mode_;
  const void * event_ptr_;
  class pf_iter_core;
  class pf_iter
  {
    friend class pf_iter_core;
    friend class CFAT_Core;
    CFAT_Core    * core_ptr_;
    pf_iter_core * iter_core_ptr_;
    bool CanDelete_;
    
  protected:
  public:
    ~pf_iter();
    pf_iter();
    bool operator != (const pf_iter &) ;
    pf_iter  operator++(int);
    pf * operator -> ();
    pf_iter_core * GetIterCore() const;
    void SetIterCore(pf_iter_core &);
    void SetCore(CFAT_Core &);
    void SetDeleteOption(bool option);
    pf_iter(pf_iter &&);
    pf_iter(const pf_iter &);
  };
  class pf_iter_core
  {
    friend class pf_iter;
  protected:
    
    pf           * const particle_ptr_;
    VectorCode_t           tracked_vector_;
    virtual pf           * operator -> () = 0;
    virtual bool           compare (const pf_iter_core *) = 0;
    pf_iter_core(pf * particle_ptr);
    
    virtual ~pf_iter_core();
  public:
    virtual void WhoAmI();
    void Do();
  };
  virtual void increment(pf_iter &)  = 0;
 
  virtual pf_iter begin(VectorCode_t) = 0;
  virtual pf_iter end(VectorCode_t) = 0;
  virtual const TLorentzVector * GetVector(VectorCode_t) = 0;
  virtual void SetWorkMode(WorkCode_t work_code) = 0;


  PullVector                       CalculatePullVector(VectorCode_t, ChargeCode_t = ALLCOMP, PF_PTCutCode_t = PF_PT_TOTAL) ; 
  TLorentzVector GetChargedJet(VectorCode_t vector_code) ;

  virtual void check(const char * = "") const = 0;
};


#endif
