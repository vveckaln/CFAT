#ifndef _CFAT_Event_hh_
#define _CFAT_Event_hh_
#include "Definitions.hh"


#include "TVector2.h"
#include "TLorentzVector.h"
using namespace std;
using namespace Definitions;
  
enum ChargeEnum_t     {ALLCOMP, CHARGED};
enum DeltaRCutEnum_t  {DELTAR_TOTAL, DELTAR_LE_1p0, DELTAR_GT_1p0};
enum PF_PTCutEnum_t   {PF_PT_TOTAL, PF_PT_LE_0p5_GEV, PF_PT_GT_0p5_GEV};
enum HadW_PtCutEnum_t {HADW_PT_TOTAL, HADW_PT_LE_50p0_GEV, HADW_PT_GT_50p0_GEV}; 
enum PFNEnum_t        {PFN_TOTAL, PFN_LE_20, PFN_GT_20};
enum PVMagEnum_t      {PVMAG_TOTAL, PVMAG_LE_0p005, PVMAG_GT_0p005};
typedef unsigned char ChargeCode_t;
typedef unsigned char WorkCode_t;
typedef unsigned char PF_PTCutCode_t;
class CFAT_Event;
class CFAT_Core;
struct PullVector: public TVector2
{
  PullVector(Double_t, Double_t);
  Double_t           & phi_component = fX;
  Double_t           & eta_component = fY;
  unsigned short     Ncomponents;
  VectorCode_t       origin_jet;
  const CFAT_Core  * origin_core_ptr_;
  const CFAT_Event * origin_event_ptr_;
};

class CFAT_Event
{

  friend class ColourFlowAnalysisTool;
  CFAT_Core * core_ptr_;
  WorkCode_t                         work_mode_;
  
  
  double                           weight_;
  unsigned long                    event_number_;
  
  const TLorentzVector           * had_W_ptr_;
  const TLorentzVector           * had_t_ptr_;
  
  const TLorentzVector           * lept_W_ptr_;
  const TLorentzVector           * lept_t_ptr_;
  const TLorentzVector           * fake_ptr_;
  static const TLorentzVector    * beam_ptr_;
  struct store_struct
  {
    TLorentzVector had_W;
    TLorentzVector had_t;
    TLorentzVector lept_W;
    TLorentzVector lept_t;
    store_struct();
    ~store_struct();
  } store_;
  const TLorentzVector *&          GetVectorRef(VectorCode_t) ;
  TLorentzVector &                 GetStoreRef(VectorCode_t);
  void                             SetWorkMode(WorkCode_t);
  void                             SetVector(VectorCode_t, const TLorentzVector &);
  CFAT_Core *                      GetCore();
public:
  static const unsigned char       N_charge_types_ = 2;
  static const unsigned char       N_jet_types_ = 12;  
  
  CFAT_Event();
  void                             AddLightJets(const vector<TLorentzVector> &, const vector<unsigned short> &);
  void                             AddBJets(const vector<TLorentzVector> &, const vector<unsigned short> &);
  void                             CompleteVectors();
  TLorentzVector                   GetChargedJet(VectorCode_t) const;
  void                             SetCore(CFAT_Core &);
  void                             SetWeight(double);
  void                             SetEventNumber(unsigned long);
  void                             AddVector(VectorCode_t, const TLorentzVector *);
  const TLorentzVector * const     GetVector(VectorCode_t) const;

  unsigned short                   GetIndex(VectorCode_t) const;
  double                           Angle(VectorCode_t, VectorCode_t) const;
  double                           DeltaR(VectorCode_t, VectorCode_t) const;
  double                           PullAngle(const PullVector &, VectorCode_t) const;
  //  PullVector                       CalculatePullVector(VectorCode_t, ChargeCode_t = ALLCOMP, PF_PTCutCode_t = PF_PT_TOTAL) const; 
  //TVector2                         CalculatePullVectorEuclidian(const TLorentzVector & jet, unsigned char index, bool OnlyChargedConstituents) const;

  };

#endif
