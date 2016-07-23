#include "Definitions.hh"
#include "CFAT_Event.hh"

/*using namespace Definitions;
{*/
const char          * Definitions::tag_channel_                                = "4j2t";
const char          * Definitions::tag_charge_types_[2]                        = {"allconst", "chconst"};
const char          * Definitions::tag_jet_types_[CFAT_Event::N_jet_types_]    = 
    {"leading_jet", "2nd_leading_jet", "had_b", "had_w", "had_t", "lepton", "neutrino", "lept_b", "lept_w", "lept_t", "beam", "fake"};
//    0              1                  2         3       4         5        6           7          8        9         10      11         
const unsigned char   Definitions::N_DeltaR_types_                             = 3;
const char          * Definitions::tag_DeltaR_types_[N_DeltaR_types_]          = {"DeltaRTotal", "DeltaRle1.0", "DeltaRgt1.0"}; 
//const unsigned char   Definitions::N_levels_types_                             = 1;

//const char          * Definitions::tag_levels_[N_levels_types_]                = {"Rivet"};
const unsigned char   Definitions::N_PF_Pt_cuts_                               = 3;
const char          * Definitions::PF_Pt_cuts_types_[N_PF_Pt_cuts_]            = {"PFPtTotal", "PFPtle0p5GeV", "PFPtgt0p5GeV"};

const unsigned char   Definitions::N_HadW_Pt_cuts_                             = 3;
const char          * Definitions::HadW_Pt_cuts_types_[N_PF_Pt_cuts_]          = {"hadWPtTotal", "hadWPtle50p0GeV", "hadWPtgt50p0GeV"}; 

const unsigned char   Definitions::N_PF_N_cuts_                                = 3;
const char          * Definitions::PF_N_cuts_types_[N_PF_N_cuts_]              = {"PFNTotal", "PFNle20", "PFNgt20"};

const unsigned char   Definitions::N_PVMag_cuts_                               = 3;
const char          * Definitions::PVMag_cuts_types_[N_PVMag_cuts_]            = {"PVMagTotal", "PVMagle0p005", "PVMaggt0p005"};



//}

