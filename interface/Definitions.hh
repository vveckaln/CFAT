#ifndef _Definitions_hh_
#define _Definitions_hh_

#define N_channels_types 3
#include "TH1F.h"
namespace Definitions
{

  enum VectorEnum_t     {LEADING_JET, SCND_LEADING_JET, HAD_B, HAD_W, HAD_T, LEPTON, NEUTRINO, LEPT_B, LEPT_W, LEPT_T, BEAM, FAKE, ALLJETS = 255 };
  enum ParticlesEnum_t  {ALLPRT, JETPRT};
  enum ChargeEnum_t     {ALLCOMP, CHARGED};
  enum DeltaRCutEnum_t  {DELTAR_TOTAL, DELTAR_LE_1p0, DELTAR_GT_1p0};
  enum PF_PTCutEnum_t   {PF_PT_TOTAL, PF_PT_LE_0p5_GEV, PF_PT_GT_0p5_GEV};
  enum HadW_PtCutEnum_t {HADW_PT_TOTAL, HADW_PT_LE_50p0_GEV, HADW_PT_GT_50p0_GEV}; 
  enum PFNEnum_t        {PFN_TOTAL, PFN_LE_20, PFN_GT_20};
  enum PVMagEnum_t      {PVMAG_TOTAL, PVMAG_LE_0p005, PVMAG_GT_0p005};
  enum Channel_t        {L, E, M};
  enum PA_plots_t       {PA_N, PA_E, PA_PT};
  enum Sources_t        {MC, DATA};
  enum SelectionStages_t{L1, L1JGT4, L1JGT42B, L1J4B2LJ2};
  typedef unsigned char VectorCode_t;
  typedef unsigned char ChannelCode_t;
  typedef unsigned char sourceCode_t;
  extern const char            N_charge_types_;
  extern const char          * tag_charge_types_[2];

  extern const char            N_jet_types_;
  extern const char          * tag_jet_types_[];

  extern const unsigned char   N_levels_types_;
  extern const char          * tag_levels_types_[];

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

  extern const char            N_channels_types_;
  extern const char          * tag_channels_types_[];

  extern const char          * jet_titles_[];
  extern const char          * charge_titles_[];
  extern const char          * level_titles_[];
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
