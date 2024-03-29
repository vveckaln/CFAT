#ifndef _CFAT_Core_hh_
#define _CFAT_Core_hh_
//#include "PullVector.hh"

#include "CFAT_Event.hh"
#include "Definitions.hh"
#include "TLorentzVector.h"
#include "pf.hh"
#include "TEllipse.h"

class PullVector;
class CFAT_Core
{
  friend class CFAT_Event;
  friend class ColourFlowAnalysisTool;
protected:
  virtual const TLorentzVector *& GetVectorRef(VectorCode_t code) = 0; 
  unsigned char      event_display_mode_;
  WorkEnum_t         work_mode_;
  const void       * event_ptr_;
  CFAT_Event       * cfat_event_;

  class pf_iter_core;
  class pf_iter
  {
    friend class pf_iter_core;
    friend class CFAT_Core;
    CFAT_Core    * core_ptr_;
    pf_iter_core * iter_core_ptr_;
    bool           CanDelete_;
    VectorCode_t   tracked_vector_code_; //vector code tracked by the iterator, 255 if tracks all jets
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
    CFAT_Core * GetCore() const;
    void SetDeleteOption(bool option);
    void SetTrackedVectorCode(VectorCode_t );
    VectorCode_t GetTrackedVectorCode() const;
    pf_iter(pf_iter &&);
    pf_iter(const pf_iter &);
  };
  class pf_iter_core
  {
    friend class pf_iter;
  protected:
    pf_iter              * iter_ptr_;
    pf                   * const particle_ptr_;
    VectorCode_t           tracked_vector_;
    virtual pf           * operator -> () = 0;
    virtual bool           compare (const pf_iter_core *) = 0;
  
    pf_iter_core(pf * particle_ptr);
    
    virtual ~pf_iter_core();
  public:
    virtual VectorCode_t   GetVectorCode() const = 0; //returns either of the following LEADING_JET, SCND_LEADING_JET, HAD_B, LEPT_B
  
    pf_iter *    GetIter() const;
    virtual void WhoAmI();
    void Do();
  };
  virtual void increment(pf_iter &)  = 0;
 
  virtual pf_iter begin(VectorCode_t) = 0;
  virtual pf_iter end(VectorCode_t) = 0;
  virtual pf_iter begin() = 0;
  virtual pf_iter end() = 0;
  virtual void SetWorkMode(WorkEnum_t work_code) = 0;

 
  PullVector                       CalculatePullVector(VectorCode_t, ChargeCode_t = ALLCOMP, PF_PTCutCode_t = PF_PT_TOTAL) ; 
  PullVector                       CalculatePullVectorEXP(VectorCode_t, VectorCode_t, ChargeCode_t = ALLCOMP, PF_PTCutCode_t = PF_PT_TOTAL) ; 

  void AnalyseJetConstituents();
  TLorentzVector GetJetFromParticles(VectorCode_t vector_code, ChargeCode_t = ALLCOMP, PF_PTCutCode_t = PF_PT_GT_1p0_GEV) ;
  virtual const TLorentzVector * GetVector(VectorCode_t, const char * particle = nullptr, ChargeCode_t = ALLCOMP) = 0;
  
  virtual void check(const char * = "") const = 0;
  void EventDisplay(const PullVector & pv, float pull_angle/*, const TVector2 & jet_difference*/, ChargeCode_t = ALLCOMP);
public:
  CFAT_Core();
  virtual void RecomputeJetsFromParticles() = 0;
  virtual void Reset() = 0;
  CFAT_Event * GetCFATEvent();
  void SetEventDisplayMode(unsigned char);
  void ls_particles(VectorCode_t, ChargeCode_t = ALLCOMP);
};

class TEllipseED: public TEllipse
{
public:
  TEllipseED(Double_t x1, Double_t y1, Double_t r1, Double_t r2=0, Double_t phimin=0, Double_t phimax=360, Double_t theta=0);
  unsigned char _jetindex;
  virtual ~TEllipseED();
};

#endif
