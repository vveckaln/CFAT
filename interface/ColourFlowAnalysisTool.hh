
#ifndef _ColourFlowAnalysisTool_hh_
#define _ColourFlowAnalysisTool_hh_
#include "CFAT_Event.hh"

#include "TLorentzVector.h"
#include "TH1.h"
#include "TString.h"
class TCanvas;
#include "TH2F.h"
#include <map>

using namespace std;

class ColourFlowAnalysisTool
{

  WorkCode_t work_mode_;
  CFAT_Event * cfat_event_ptr_;
  
public:
  ColourFlowAnalysisTool();
  
  void     * plots_ptr_;
  void     * plots2D_ptr_;
  CFAT_Event * GetEvent() const;
  void SetEvent (CFAT_Event &);
  void SetWorkMode(WorkCode_t);
  void Work();
  void Fill1D(const TString &, const double) const;
  //void (*Fill1D_ptr_)(const TString &, const double) const;
  void PlotAngleBetweenJets() const;
  void PlotJetDimensions() const;
  void Do();
};

#endif
