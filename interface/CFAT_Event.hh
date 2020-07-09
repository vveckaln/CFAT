#ifndef _CFAT_Event_hh_
#define _CFAT_Event_hh_
#include "Definitions.hh"


#include "TVector2.h"
#include "TLorentzVector.h"
//#include "PullVector.hh"
using namespace std;
using namespace Definitions;
  

class ColourFlowAnalysisTool;
class CFAT_Core;
class PullVector;
class CFAT_Event
{

  friend class ColourFlowAnalysisTool;
  ColourFlowAnalysisTool        *  cfat_;
  CFAT_Core                     *  core_ptr_;
  WorkCode_t                       work_mode_;
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
public:
  void                             Reset();
  CFAT_Core *                      GetCore();
  CFAT_Core *                      GetCore() const ;
  ColourFlowAnalysisTool *         GetCFAT();

  vector<double>                   weights_;
  CFAT_Event();
  void                             AddLightJets(const vector<TLorentzVector> &, const vector<unsigned short> &);
  void                             AddBJets(const vector<TLorentzVector> &, const vector<unsigned short> &);
  void                             CompleteVectors();
  TLorentzVector                   GetChargedJet(VectorCode_t) const;
  void                             SetCore(CFAT_Core &);
  void                             SetWeights(vector<double>);
  vector<double>                   GetWeights() const;
  void                             SetEventNumber(unsigned long);
  void                             AddVector(VectorCode_t, const TLorentzVector *);
  const TLorentzVector * const     GetVector(VectorCode_t, const char * = 0, ChargeCode_t = ALLCOMP) const;

  unsigned short                   GetIndex(VectorCode_t) const;
  double                           Angle(VectorCode_t, VectorCode_t) const;
  double                           DeltaR(VectorCode_t, VectorCode_t) const;
  double                           PullAngle(const PullVector &, VectorCode_t, const char * option = 0, ChargeCode_t = ALLCOMP) const;
  double                           PullAngleEXP(const PullVector &, VectorCode_t) const;

  unsigned long                    GetEventNumber() const;
  //  PullVector                       CalculatePullVector(VectorCode_t, ChargeCode_t = ALLCOMP, PF_PTCutCode_t = PF_PT_TOTAL) const; 
  //TVector2                         CalculatePullVectorEuclidian(const TLorentzVector & jet, unsigned char index, bool OnlyChargedConstituents) const;
  double                           GetEventEnergy() const;
  double                           GetEventPt() const;
  };

#endif
