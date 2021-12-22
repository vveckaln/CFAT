#ifndef _Definitions_hh_
#define _Definitions_hh_
#include <map>

#define N_channels_types 3
#include "TH1F.h"
#include "WorkEnum_t.hh"
using namespace std;
//ClassDef(Definitions::WorkEnum_t, 1)
namespace Definitions
{
  //  #include "WorkEnum_t.hh"

  enum VectorEnum_t     {LEADING_JET, SCND_LEADING_JET, LEADING_B, SCND_LEADING_B, HAD_B, LEPT_B, HAD_W, HAD_T, LEPTON, NEUTRINO, LEPT_W, LEPT_T, BEAM, FAKE, ALLJETS = 255 };
  enum ParticlesEnum_t  {ALLPRT, JETPRT};
  enum ChargeEnum_t     {ALLCOMP, CHARGED};
  enum DeltaRCutEnum_t  {DELTAR_TOTAL, DELTAR_LE_1p0, DELTAR_GT_1p0};
  enum PF_PTCutEnum_t   {PF_PT_TOTAL, PF_PT_LE_0p5_GEV, PF_PT_GT_0p5_GEV, PF_PT_GT_1p0_GEV};
  enum HadW_PtCutEnum_t {HADW_PT_TOTAL, HADW_PT_LE_50p0_GEV, HADW_PT_GT_50p0_GEV}; 
  enum PFNEnum_t        {PFN_TOTAL, PFN_LE_20, PFN_GT_20};
  enum PVMagEnum_t      {PVMAG_TOTAL, PVMAG_LE_0p005, PVMAG_GT_0p005};
  enum Channel_t        {L, E, M};
  enum PA_plots_t       {PA_N, PA_E, PA_PT};
  enum Source_t         {MC, DATA};
  enum SelectionStage_t{L1, L1JGEQ4, L1JGEQ4B2, L1J4B2LJ2};
  //  enum class WorkEnum_t {RECO, GEN};
  typedef unsigned char VectorCode_t;
  typedef unsigned char ChannelCode_t;
  typedef unsigned char sourceCode_t;
  typedef unsigned char ChargeCode_t;
  typedef unsigned char WorkCode_t; 
  typedef unsigned char SourceCode_t;
  typedef unsigned char PF_PTCutCode_t;
  extern const char            N_charge_types_;
  extern const char          * tag_charge_types_[2];

  extern const char            N_jet_types_;
  extern const char          * tag_jet_types_[];

  extern const unsigned char   N_levels_types_;
  
  extern const char          * level_titles_[];

  extern const unsigned char   N_DeltaR_types_;
  extern const char          * tag_DeltaR_types_[];

  extern const unsigned char   N_PF_Pt_cuts_;
  extern const char          * PF_Pt_cuts_types_[];// = {"PFPtTotal", "PFPtle0p5GeV", "PFPtgt0p5GeV"};

  extern const unsigned char   N_HadW_Pt_cuts_;
  extern const char          * HadW_Pt_cuts_types_[];// = {"hadWPtTotal", "hadWPtle50p0GeV", "hadWPtGt50p0GeV"}; 

  extern const unsigned char   N_PF_N_cuts_;
  extern const char          * PF_N_cuts_types_[];// = {"PFN_Total", "PFNle20", "PFNgt20"};

  extern const unsigned char   N_PVMag_cuts_;
  extern const char *          PVMag_cuts_types_[];// = { "PVMag_Total", "PVMag_le_0p005", "PVMag_gt_0p005"};

  extern const char            N_particles_types_;
  extern const char          * tag_particles_types_[];

  extern const char            N_PA_plots_types_;
  extern const char          * tag_PA_plots_types_[];
  extern const char          * PA_plots_titles_[];
  
  extern const char            N_channels_types_;
  extern const char          * tag_channels_types_[];

  extern const char          * jet_titles_[];
  extern const char          * jet_names_[4];
  extern const char          * charge_titles_[];
  extern const char          * channel_titles_[];

  extern const unsigned char   N_sources_types_;
  extern const char          * tag_sources_types_[];
  extern const char          * title_sources_types_[];

  extern const unsigned char   N_selection_stages_;
  extern const char          * tag_selection_stages_[];
  extern const char          * title_selection_stages_[];

};
void Do(TH1F);
#endif
