
#ifndef _ColourFlowAnalysisTool_hh_
#define _ColourFlowAnalysisTool_hh_
#include "CFAT_Event.hh"
#include "PullVector.hh"
#include "TLorentzVector.h"
#include "TH1.h"
#include "TString.h"
class TCanvas;
#include "TH2F.h"
#include <map>
//enum Definitions::WorkEnum_t
using namespace std;

class ColourFlowAnalysisTool
{

  CFAT_Event * cfat_event_ptr_;
protected:
  WorkEnum_t work_mode_;
  ChannelCode_t channel_code_;
  //  unsigned char nsyst_;
public:
  ColourFlowAnalysisTool();
  void     * plots_ptr_;
  void     * plots2D_ptr_;
  void Reset();
  CFAT_Event * GetEvent() const;
  void SetEvent (CFAT_Event &);
  void SetWorkMode(WorkEnum_t);
  void SetChannel(ChannelCode_t);
  ChannelCode_t GetChannel() const;
  WorkEnum_t  GetWorkMode() const;
  void Work();
  inline virtual void Fill1D(const TString & key, double value , double weight = 1.0, const char * option = "") const = 0;

  inline virtual void Fill2D(const TString &, double, double, double weight) const = 0;
  //void (*Fill1D_ptr_)(const TString &, const double) const;
  void PlotAngleBetweenJets() const;
  void PlotJetDimensions() const;
  void Do();
  void AnalyseParticleFlow() const;
  void virtual ResetMigrationValues() = 0;
  bool migrationvaluesstored;
  void virtual StoreMigrationValues(ChargeCode_t chargecode, VectorCode_t jetcode, double pa, double mag, double mag_par) = 0;
  void virtual PlotMigrationValues() = 0;

  virtual ~ColourFlowAnalysisTool();
};

#endif
