// #ifndef _Definitions_hh_
// #define _Definitions_hh_
#ifndef _Definitions_WorkEnum_t_hh_
#define _Definitions_WorkEnum_t_hh_
//ClassDef(Definitions::WorkEnum_t, 1) https://root-forum.cern.ch/t/add-enum-class-in-namespace-to-root/47925/2
#include <map>
#include "TString.h"
using namespace std;
namespace Definitions
{
  enum class WorkEnum_t {RECO, GEN};
  extern const map<WorkEnum_t, const char *>         tag_levels_types_;
  //  extern map<WorkEnum_t, TString>         tag_levels_types_;
}

void testfunc();
#endif
