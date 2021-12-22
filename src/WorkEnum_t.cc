#include <stdio.h>
#include "WorkEnum_t.hh"
// const std::map<Definitions::WorkEnum_t, const char *>         Definitions::tag_levels_types_ = {make_pair(WorkEnum_t::RECO, "reco"), 
// 								                                make_pair(WorkEnum_t::GEN, "gen")};

// std::map<Definitions::WorkEnum_t, TString>         Definitions::tag_levels_types_ = {{WorkEnum_t::RECO, TString("reco")}, 
// 										     {WorkEnum_t::GEN, TString("gen")}};

const std::map<Definitions::WorkEnum_t, const char *>         Definitions::tag_levels_types_ = 
  {
    {WorkEnum_t::RECO, "reco"}, 
    {WorkEnum_t::GEN, "gen"}
  };


//#include "Rtypes.h"
//NamespaceImp(Definitions)
void testfunc()
{
  printf("testfunc\n");
}
