#ifndef _Definitions_hh_
#define _Definitions_hh_

namespace Definitions
{
  enum VectorEnum_t     {LEADING_JET, SCND_LEADING_JET, HAD_B, HAD_W, HAD_T, LEPTON, NEUTRINO, LEPT_B, LEPT_W, LEPT_T, BEAM, FAKE };

  typedef unsigned char VectorCode_t;

  extern const char          * tag_channel_;
  extern const char          * tag_charge_types_[2];
  extern const char          * tag_jet_types_[];
  extern const unsigned char   N_DeltaR_types_;
  extern const unsigned char   N_levels_types_;
  extern const char          * tag_DeltaR_types_[];
  extern const unsigned char   N_PF_Pt_cuts_;
  extern const char          * PF_Pt_cuts_types_[];// = {"PFPtTotal", "PFPtle0p5GeV", "PFPtgt0p5GeV"};
  extern const unsigned char   N_HadW_Pt_cuts_;
  extern const char          * HadW_Pt_cuts_types_[];// = {"hadWPtTotal", "hadWPtle50p0GeV", "hadWPtGt50p0GeV"}; 
  extern const unsigned char   N_PF_N_cuts_;
  extern const char          * PF_N_cuts_types_[];// = {"PFN_Total", "PFNle20", "PFNgt20"};
  extern const unsigned char   N_PVMag_cuts_;
  extern const char *          PVMag_cuts_types_[];// = { "PVMag_Total", "PVMag_le_0p005", "PVMag_gt_0p005"};
  extern const char          * tag_levels_[];
};
#endif
