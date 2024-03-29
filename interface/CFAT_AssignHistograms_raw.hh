#ifndef _CFAT_AssignHistograms_raw_hh_
#define _CFAT_AssignHistograms_raw_hh_

template<typename TargetType, typename CreateHistoType>
void AssignHistograms_raw(TargetType &, CreateHistoType); 

#endif

#include "CFAT_Event.hh"
#include "Definitions.hh"

using namespace Definitions;
template<typename TargetType, typename CreateHistoType>
void AssignHistograms_raw(TargetType  & target, CreateHistoType CreateHistogram1DT) 
{
  // const std::map<Definitions::WorkEnum_t, const char *>         tag_levels_types_ = {make_pair(WorkEnum_t::RECO, "reco"), 
  // 								                                make_pair(WorkEnum_t::GEN, "gen")};

  /*for (WorkCode_t level_code = 0; level_code < N_levels_types_; level_code ++)
    {

      CreateHistogram1DT(target, TString("beta_jetsum_lab_frame") + "_" +  tag_jet_types_[HAD_W] + "_" + tag_levels_[level_code], "; #beta; Events", 20, -0.1, 1.1);
      CreateHistogram1DT(target, TString("beta_jet_jetsum_frame") + "_" + tag_levels_[level_code], "; #beta; Events", 20, -0.1, 1.1);
      CreateHistogram1DT(target, TString("beta_jet_lab_frame") + "_" + tag_levels_[level_code], "; #beta; Events", 20, -0.1, 1.1);
      CreateHistogram1DT(target, TString("beta_angle_jet_jetsum_jetsum_frame") + "_" + tag_levels_[level_code], "; #beta; Events", 20, -0.1, 2*TMath::Pi() + 0.1);

      CreateHistogram1DT(target, TString("beta_angle_particle_jet_jet_frame") + "_" + tag_levels_[level_code], "; #beta; Events", 20, -0.1, 2*TMath::Pi() + 0.1);

      CreateHistogram1DT(target, TString("beta_particle_jet_frame") + "_" + tag_levels_[level_code], "; #beta; Events", 20, -0.1, 1.1);
    }*/
  
  static const unsigned char ncategories_PA         = 1;
  /*static const char * cat_title_PA[ncategories_PA]     = {"pull_angle",     "cos_pull_angle" };
  static const unsigned short nbins_PA[ncategories_PA] = {100,               100              };
  static const double min_PA[ncategories_PA]           = {-1.*TMath::Pi(), -1.2             };
  static const double max_PA[ncategories_PA]           = {- min_PA[0],         -min_PA[1]          };
  static const char* axes_PA[ncategories_PA]           = {"; pull angle [rad]; Events",  "; cos; Events"  };
*/
  static const char * cat_title_PA[ncategories_PA]     = {"pull_angle"                 };
  static const unsigned short nbins_PA[ncategories_PA] = {80,                          };
  static const double min_PA[ncategories_PA]           = {-1.0*TMath::Pi()             };
  static const double max_PA[ncategories_PA]           = {- min_PA[0]                  };
  static const char* axes_PA[ncategories_PA]           = {"; pull angle [rad]; Events" };


  for (unsigned char cat_index = 0; cat_index < ncategories_PA; cat_index++)
    {
      for (WorkCode_t level_code = 0; level_code < N_levels_types_; level_code ++)
	{
	  const WorkEnum_t workmode = WorkEnum_t(level_code); 
	  for (unsigned char jet1_code = 0; jet1_code < 4; jet1_code ++)
	    {
	      for (VectorCode_t jet2_code = 0; jet2_code < N_jet_types_; jet2_code ++)
		{
		  if (jet1_code == jet2_code)
		    {
		      continue;
		    }
		  if((jet1_code == LEADING_B or jet1_code == SCND_LEADING_B) and (jet2_code != LEADING_B and jet2_code != SCND_LEADING_B) 
		     or (jet2_code == LEADING_B or jet2_code == SCND_LEADING_B) and (jet1_code != LEADING_B and jet1_code != SCND_LEADING_B))
		    {
		      continue;
		    }
		  else
		    {
		    }
		  for (unsigned char DeltaR_index = 0; DeltaR_index < N_DeltaR_types_; DeltaR_index ++)
		    {
		      const TString postfix = TString("_") + tag_levels_types_.at(workmode) + "_" +
			tag_jet_types_[jet1_code] + "_" + 
			tag_jet_types_[jet2_code] + "_" + 
			tag_DeltaR_types_[DeltaR_index];

		      for (unsigned char charge_index = 0; charge_index < 2; charge_index ++)
			{
			  const TString hash_key = TString(cat_title_PA[cat_index]) + "_" + 
			    tag_charge_types_[charge_index] +
			    postfix;
			  //			  printf(" %u %s %u %f %f\n", cat_index, axes_PA[cat_index], nbins_PA[cat_index], min_PA[cat_index], max_PA[cat_index]); 
			  CreateHistogram1DT(target, hash_key, axes_PA[cat_index], nbins_PA[cat_index], min_PA[cat_index], max_PA[cat_index]);
			  //			  CreateHistogram1DT(target, hash_key + "_EXP",  axes_PA[cat_index], nbins_PA[cat_index], min_PA[cat_index], max_PA[cat_index]);

			}
		      for (unsigned char PF_Pt_cut_index = 1; PF_Pt_cut_index < N_PF_Pt_cuts_; PF_Pt_cut_index ++)
			{
			  const TString hash_key = TString(cat_title_PA[cat_index]) + "_" + 
			    PF_Pt_cuts_types_[PF_Pt_cut_index] +
			    postfix;
			  
			  CreateHistogram1DT(target, hash_key, axes_PA[cat_index], nbins_PA[cat_index], min_PA[cat_index], max_PA[cat_index]);



			}

		      for (unsigned char HadW_Pt_cut_index = 1; HadW_Pt_cut_index < 3; HadW_Pt_cut_index ++)
			{
			  const TString hash_key = TString(cat_title_PA[cat_index]) + "_" + 
			    HadW_Pt_cuts_types_[HadW_Pt_cut_index] +
			    postfix;
			  CreateHistogram1DT(target, hash_key, axes_PA[cat_index], nbins_PA[cat_index], min_PA[cat_index], max_PA[cat_index]);
			}

		      for (unsigned char PF_N_cut_index = 1; PF_N_cut_index < 3; PF_N_cut_index ++)
			{
			  const TString hash_key = TString(cat_title_PA[cat_index]) + "_" + 
			    PF_N_cuts_types_[PF_N_cut_index] + 
			    postfix;
			  CreateHistogram1DT(target, hash_key, axes_PA[cat_index], nbins_PA[cat_index], min_PA[cat_index], max_PA[cat_index]);
			}
		      
		      for (unsigned char PVMag_cut_index = 1; PVMag_cut_index < 3; PVMag_cut_index ++)
			{
			  const TString hash_key = TString(cat_title_PA[cat_index]) + "_" + 
			    PVMag_cuts_types_[PVMag_cut_index] + 
			    postfix;
			  CreateHistogram1DT(target, hash_key, axes_PA[cat_index], nbins_PA[cat_index], min_PA[cat_index], max_PA[cat_index]);
			}



		    }
		}
    
	    }
	}
    }

  static const unsigned char ncategories_PV = 7;
  static const char * cat_title_PV[ncategories_PV]     = {"phi_PV",                "rapidity_PV",               "mag_PV",          "mag_PV_par",                 "phi_PV_bckg",           "rapidity_PV_bckg",            "mag_PV_bckg"};
  static const unsigned short nbins_PV[ncategories_PV] = {80,                      80,                      80,                    80,                           80,                      80,                       80          };
  static const double min_PV[ncategories_PV]           = {-0.008*TMath::Pi(),       -0.02,                   0.0,                  0.0,                      - TMath::Pi() -0.2,      - 5.0,                    0.0          };
  static const double max_PV[ncategories_PV]           = {- min_PV[0],             -min_PV[1],              0.05,                  0.05,                     TMath::Pi() + 0.2,       5.0,                      6.0          };
  static const char* axes_PV[ncategories_PV]           = {"; #phi [rad]; Events",  "; y [a.u.]; Events", "; magn. [a.u.]; Events", "magn. [a.u.] ||; Events", "#phi [rad]; Events",   "; y [a.u.]; Events", "; magn. [a.u.]; Events"};
  for (unsigned char cat_index = 0; cat_index < ncategories_PV; cat_index++)
    {
      for (WorkCode_t level_index = 0; level_index < N_levels_types_; level_index ++)
	{ 
	  const WorkEnum_t workmode = WorkEnum_t(level_index); 
	  for (unsigned char jet1_index = 0; jet1_index < 6; jet1_index ++)
	    {
	      const TString postfix = TString("_") + 
		tag_levels_types_.at(workmode) + "_" +
		tag_jet_types_[jet1_index];
	      for (unsigned char charge_index = 0; charge_index < 2; charge_index ++)
		{
		  const TString hash_key = TString(cat_title_PV[cat_index]) + "_" + 
		    tag_charge_types_[charge_index] + 
		    postfix;
		  CreateHistogram1DT(target, hash_key, axes_PV[cat_index], nbins_PV[cat_index], min_PV[cat_index], max_PV[cat_index]);
		}
	      for (unsigned char PF_Pt_cut_index = 1; PF_Pt_cut_index < 3; PF_Pt_cut_index ++)
		{
		  const TString hash_key = TString(cat_title_PV[cat_index]) + "_" + 
		    PF_Pt_cuts_types_[PF_Pt_cut_index] + 
		    postfix;
		  CreateHistogram1DT(target, hash_key, axes_PV[cat_index], nbins_PV[cat_index], min_PV[cat_index], max_PV[cat_index]);
		}
	      for (unsigned char HadW_Pt_cut_index = 1; HadW_Pt_cut_index < 3; HadW_Pt_cut_index ++)
		{
		  const TString hash_key = TString(cat_title_PV[cat_index]) + "_" + 
		    HadW_Pt_cuts_types_[HadW_Pt_cut_index] + 
		    postfix;
		  CreateHistogram1DT(target, hash_key, axes_PV[cat_index], nbins_PV[cat_index], min_PV[cat_index], max_PV[cat_index]);
		}
	      for (unsigned char PF_N_cut_index = 1; PF_N_cut_index < 3; PF_N_cut_index ++)
		{
		  const TString hash_key = TString(cat_title_PV[cat_index]) + "_" + 
		    PF_N_cuts_types_[PF_N_cut_index] + 
		    postfix;
		  CreateHistogram1DT(target, hash_key, axes_PV[cat_index], nbins_PV[cat_index], min_PV[cat_index], max_PV[cat_index]);
		}


	    }
	}
    }

  /*    for (unsigned char level_index = 0; level_index < 2; level_index ++)
	{ 
	  for (unsigned char charge_index = 0; charge_index < 2; charge_index ++)
	    {
	      for (unsigned char jet1_index = 0; jet1_index < 2; jet1_index ++)
		{
		  const TString hash_key = TString("phi_eta_PV_") + 
		    tag_charge_types_[charge_index] + "_" + 
		    tag_levels_[level_index] + "_" +
		    tag_jet_types_[jet1_index] + "_" + 
		    tag_channel_;
		  plots2D_ptr_ -> operator[](hash_key) = new TH2F(hash_key, 
								hash_key + "; #phi[rad]; #eta[a.u.]", 
								  100, -0.016, 0.016,  
								  100, -0.016, 0.016 
							        );

		
		}
	    }
	}
*/

  /*      
  static const unsigned char ncategories_CTRL              = 2;
  static const char * branch[2]                            = {"had", "lept"};
  static const char * cat_title_CTRL[ncategories_CTRL]     = {"W_mass",         "t_mass"    };
  static const unsigned short nbins_CTRL[ncategories_CTRL] = {100,              100         };
  static const double min_CTRL[ncategories_CTRL]           = {0,                50          };
  static const double max_CTRL[ncategories_CTRL]           = {150,              400         };
  static const char* axes_CTRL[ncategories_CTRL]           = {"; GeV; Events",  "; GeV; Events"};
  for (unsigned char branch_index = 0; branch_index < 2; branch_index ++)
    {
      for (unsigned char level_index = 0; level_index < 2; level_index ++)
	{
	  for (unsigned char cat_index = 0; cat_index < ncategories_CTRL; cat_index ++)
	    { 
	      const TString hash_key = TString(branch[branch_index]) + "_" + tag_levels_[level_index] + "_" + cat_title_CTRL[cat_index]; 
	      plots_ptr_ -> operator[](hash_key) = new TH1F(hash_key, hash_key + axes_CTRL[cat_index], nbins_CTRL[cat_index], min_CTRL[cat_index], max_CTRL[cat_index]);
	    }
	}
	}*/
  //const char * particles[2] = {"all", "jet"};
    
  for (unsigned char DeltaR_index = 0; DeltaR_index < N_DeltaR_types_; DeltaR_index ++)
    {
      for (WorkCode_t level_code = 0; level_code < N_levels_types_; level_code ++)
	{ 
	  const WorkEnum_t workmode = WorkEnum_t(level_code); 

	  for (VectorCode_t jet1_code = 0; jet1_code < N_jet_types_; jet1_code ++)
	    {
	      if (not (jet1_code == BEAM or jet1_code == LEADING_JET or jet1_code == LEPTON))
		continue;
	      for (VectorCode_t jet2_code = jet1_code + 1; jet2_code < N_jet_types_; jet2_code ++)
		{
		  if (not (jet2_code == BEAM or jet2_code == LEADING_JET or jet2_code == LEPTON))
		    continue;
		  const TString postfix = TString("_") + tag_jet_types_[jet1_code] + "_" + tag_jet_types_[jet2_code] + "_" + tag_levels_types_.at(workmode) + "_" + tag_DeltaR_types_[DeltaR_index];
		  {
		    const TString hash_key = TString("angle") + postfix; 
		    CreateHistogram1DT(target, hash_key, "; angle [rad]; Events", 50, -0.1, TMath::Pi() + 0.1);
		  }
		  // {
		  //   const TString hash_key = TString("jet_dif_phi") + postfix;
		  //   CreateHistogram1DT(target, hash_key, "; #phi [rad]; Events", 50, -1.2 * TMath::Pi(), 1.2 * TMath::Pi());
		  
		  // }
		  // {
		  //   const TString hash_key = TString("jet_dif_eta") + postfix; 
		  //   CreateHistogram1DT(target, hash_key, "; #eta; Events", 50, -5.2, 5.2);
		  
		  // }
		}
	    }

	}
    }
  
  
  for (WorkCode_t level_code = 0; level_code < N_levels_types_; level_code ++)
    { 
      const WorkEnum_t workmode = WorkEnum_t(level_code); 

      for (ChargeCode_t charge_code = 0; charge_code < N_charge_types_; charge_code ++)
	{
	  for (unsigned char particle_index = 0; particle_index < N_particles_types_; particle_index ++)
	    {
	      for (unsigned char PA_plots_type_ind = 0; PA_plots_type_ind < N_PA_plots_types_; PA_plots_type_ind ++)
		{
		  const TString title = TString("; #Phi_{") + PA_plots_titles_[PA_plots_type_ind] + "}; Events";
		  {
		    const TString hash_key = TString("chiqlq2l_") + tag_PA_plots_types_[PA_plots_type_ind] + "_" + tag_charge_types_[charge_code] + "_" + tag_levels_types_.at(workmode) + "_" + tag_particles_types_[particle_index];
		    CreateHistogram1DT(target, hash_key, title, 40, -0.0, 1.0);
		  }
		  {
		    const TString hash_key = TString("chihbqc_") + tag_PA_plots_types_[PA_plots_type_ind] + "_" + tag_charge_types_[charge_code] + "_" + tag_levels_types_.at(workmode) + "_" + tag_particles_types_[particle_index];
		    CreateHistogram1DT(target, hash_key, title, 40, -0.0, 1.0);
		  }
		  {
		    const TString hash_key = TString("chiqfhb_") + tag_PA_plots_types_[PA_plots_type_ind] + "_" + tag_charge_types_[charge_code] + "_" + tag_levels_types_.at(workmode) + "_" + tag_particles_types_[particle_index];
		    CreateHistogram1DT(target, hash_key, title, 40, -0.0, 1.0);
		  }
		  {
		    const TString hash_key = TString("chiblb2l_") + tag_PA_plots_types_[PA_plots_type_ind] + "_" + tag_charge_types_[charge_code] + "_" + tag_levels_types_.at(workmode) + "_" + tag_particles_types_[particle_index];
		    CreateHistogram1DT(target, hash_key, title, 40, 0.0, 1.0);
		  }
		}
	    }
	}
    }
  
  static const unsigned char jets[4] = {LEADING_JET, SCND_LEADING_JET, LEADING_B, SCND_LEADING_B};
  for (WorkCode_t level_code = 0; level_code < N_levels_types_; level_code ++)
    { 
      const WorkEnum_t workmode = WorkEnum_t(level_code); 
      // for (VectorCode_t jet_index = 0; jet_index < 4; jet_index ++)
      // 	{
      // 	  unsigned char vector_code = jets[jet_index];
      // 	  const unsigned char nbins = 11;
      // 	  double bins[nbins + 1];
      // 	  const float binmin = 0.0;
      // 	  const float binmax = 1.0;
      // 	  const float step = (binmax - binmin)/(nbins - 1);
      // 	  for (unsigned char bind = 0; bind <= 10; bind ++)
      // 	    {
      // 	      bins[bind] = bind * step;
      // 	    }
      // 	  bins[nbins + 1] = bins[nbins] + step/2.0;
	 
      // 	  {
      // 	    const TString hash_key = TString("JetConst_EventChargedContentN_") + tag_levels_types_[level_code] + "_" + tag_jet_types_[vector_code];
      // 	    CreateHistogram1DT(target, hash_key, "; \\frac{charged}{all}; Events", nbins, bins);
      // 	  }
      // 	  {
      // 	    const TString hash_key = TString("JetConst_EventChargedContentE_") + tag_levels_types_[level_code] + "_" + tag_jet_types_[vector_code];
      // 	    CreateHistogram1DT(target, hash_key, "; \\frac{charged}{all}; Events", nbins, bins);
      // 	  }
      // 	}
      for (ChargeCode_t charge_code = 0; charge_code < N_charge_types_; charge_code ++)
	{
	  {
	    const TString hash_key = TString("JetConst_EventE_") + tag_charge_types_[charge_code] + "_" + tag_levels_types_.at(workmode);
	    CreateHistogram1DT(target, hash_key, "; E[GeV]; Events", 300, 0.0, 450.0);
	  }
	  for (VectorCode_t jet_index = 0; jet_index < 4; jet_index ++)
	    {
	      unsigned char vector_code = jets[jet_index];
	      {
		const TString hash_key = TString("JetConst_TotalE_") + tag_charge_types_[charge_code] + "_" + tag_levels_types_.at(workmode) + "_" + tag_jet_types_[vector_code];
		CreateHistogram1DT(target, hash_key, "; E [GeV]; Events", 150, 0.0, 150.0);
	      }
	      {
		const TString hash_key = TString("JetConst_E_") + tag_charge_types_[charge_code] + "_" + tag_levels_types_.at(workmode) + "_" + tag_jet_types_[vector_code];
		CreateHistogram1DT(target, hash_key, "; E [GeV]; Events", 30, 0.0, 20.0);
	      }


	      // {
	      // 	const TString hash_key = TString("JetConst_TotalPx_") + tag_charge_types_[charge_code] + "_" + tag_levels_[level_code] + "_" + tag_jet_types_[vector_code];
	      // 	CreateHistogram1DT(target, hash_key, "; Px[GeV]; Events", 100, 0.0, 100.0);
	      // }
	      // {
	      // 	const TString hash_key = TString("JetConst_TotalPy_") + tag_charge_types_[charge_code] + "_" + tag_levels_[level_code] + "_" + tag_jet_types_[vector_code];
	      // 	CreateHistogram1DT(target, hash_key, "; Py[GeV]; Events", 100, 0.0, 100.0);
	      // }
	      {
		const TString hash_key = TString("JetConst_Pt_") + tag_charge_types_[charge_code] + "_" + tag_levels_types_.at(workmode) + "_" + tag_jet_types_[vector_code];
		CreateHistogram1DT(target, hash_key, "; Pt [GeV]; Events", 30, 0.0, 20.0);
	      }
	      // {
	      // 	const TString hash_key = TString("JetConst_TotalPz_") + tag_charge_types_[charge_code] + "_" + tag_levels_[level_code] + "_" + tag_jet_types_[vector_code];
	      // 	CreateHistogram1DT(target, hash_key, "; Pz[GeV]; Events", 75, 0.0, 100.0);
	      // }
	      {
		const TString hash_key = TString("JetConst_M_") + tag_charge_types_[charge_code] + "_" + tag_levels_types_.at(workmode) + "_" + tag_jet_types_[vector_code];
		CreateHistogram1DT(target, hash_key, "; M [GeV]; Events", 150, -0.1, 1.5);
	      }

	      {
		const TString hash_key = TString("JetConst_N_") + tag_charge_types_[charge_code] + "_" + tag_levels_types_.at(workmode) + "_" + tag_jet_types_[vector_code];
		CreateHistogram1DT(target, hash_key, "; number; Events", 36, -0.5, 35.5);
	      }


	    }
	}
    }
  
  /*
  plots_ptr_ -> operator[]("had_b_flavour")              = new TH1F("had_b_flavour", "had_b_flavour; flavour; Events", 21, -10.5, 10.5);
  plots_ptr_ -> operator[]("lept_b_flavour")             = new TH1F("lept_b_flavour", "lept_b_flavour; flavour; Events", 21, -10.5, 10.5);
111111111
  plots_ptr_ -> operator[]("leading_jet_flavour")        = new TH1F("leading_jet_flavour", "leading_jet_flavour; flavour; Events", 21, -10.5, 10.5);
  plots_ptr_ -> operator[]("second_leading_jet_flavour") = new TH1F("second_leading_jet_flavour", "second_leading_jet_flavour; flavour; Events", 21, -10.5, 10.5);
  */
  /*for (unsigned char level_index = 0; level_index < 2; level_index ++)
    { 
      for (unsigned char charge_index = 0; charge_index < 2; charge_index ++)
	{
	  for (unsigned char jet1_index = 0; jet1_index < 2; jet1_index ++)
	    {

	      {
		const TString hash_key = TString("phi_PV_Euclidian_") +
		  tag_charge_types_[charge_index] + "_" + 
		  tag_levels_[level_index] + "_" +
		  tag_jet_types_[jet1_index]; 
		plots_ptr_ -> operator[](hash_key)       = new TH1F(hash_key, hash_key + "; #phi[rad]; Events", 50, -0.2, 2 * TMath::Pi() + 0.2);
	      }
	      
	    }
	}
    }
  */
  /* 
 for (unsigned char level_index = 0; level_index < 1; level_index ++)
    { 
      for (unsigned char charge_index = 0; charge_index < 2; charge_index ++)
	{
	  for (unsigned char jet1_index = 0; jet1_index < 2; jet1_index ++)
	    {
	      const TString hash_key = TString("PUPPI_weight_") +
		tag_charge_types_[charge_index] + "_" + 
		tag_levels_[level_index] + "_" +
		tag_jet_types_[jet1_index]; 
	      //printf("%s\n", hash_key.Data());
	      plots_ptr_ -> operator[](hash_key)       = new TH1F(hash_key, hash_key + "; weight; Events", 25, -0.1, 1.1);
	    }
	}
    }
*/
  for (WorkCode_t level_code = 0; level_code < N_levels_types_; level_code ++)
    { 
      const WorkEnum_t workmode = WorkEnum_t(level_code); 

      for (VectorCode_t jet1_code = 0; jet1_code < N_jet_types_; jet1_code ++)
	{
	  const TString postfix = TString("_") + tag_levels_types_.at(workmode) + "_" + tag_jet_types_[jet1_code]; 
	    
	  /*{
	    const TString hash_key = TString("jet_phi") + postfix;
	    CreateHistogram1DT(target, hash_key, "; #phi [rad]; Events", 50, -0.2 - TMath::Pi(), TMath::Pi() + 0.2);
	  }
	  {
	    const TString hash_key = TString("jet_rapidity") + postfix;
	    CreateHistogram1DT(target, hash_key, "; #eta; Events", 100, -5.2, 5.2);
	  }
	  {
	    const TString hash_key = TString("jet_eta") + postfix;
	    CreateHistogram1DT(target, hash_key, "; #eta; Events", 100, -5.2, 5.2);
	  }
	  {
	    const float mass_norm_max[CFAT_Event::N_jet_types_] = {1.1, 1.1, 1.1, 2.1, 2.1, 0.2, 0.2, 1.1, 2.1, 2.1, 2.0, 2.0};
	    
	    const TString hash_key = TString("jet_mass_norm") + postfix;
	    CreateHistogram1DT(target, hash_key, "; mass_norm; Events", 100, -0.1, mass_norm_max[jet1_code]);
	  }
	  {
	    const TString hash_key = TString("jet_pt_norm") + postfix;
	    CreateHistogram1DT(target, hash_key, "; pt_norm; Events", 100, 0, 1.1);
	  }
	  {
	    const TString hash_key = TString("jet_pz_norm") + postfix;
	    CreateHistogram1DT(target, hash_key, "; pz_norm; Events", 100, -1.1, 1.1);
	  }
	  {
	    const TString hash_key = TString("jet_px_norm") + postfix;
	    CreateHistogram1DT(target, hash_key, "; px_norm; Events", 100, -1.1, 1.1);
	  }*/
	  {
	    //  enum VectorEnum_t                  {LEADING_JET, SCND_LEADING_JET, LEADING_B, SCND_LEADING_B, HAD_B, LEPT_B, HAD_W, HAD_T, LEPTON, NEUTRINO, LEPT_W, LEPT_T, BEAM, FAKE, ALLJETS = 255 };

	    const float mass_min[N_jet_types_] = {-1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 50.0,  75.0, -0.1, -0.1, 50.0,  75.0,   0.0, -1.0};
	    const float mass_max[N_jet_types_] = {30.0, 30.0, 30.0, 30.0, 30.0, 30.0, 115.0, 400.0,  1.0,  1.0, 90.0, 400.0, 100.0,  1.0};
	    const TString hash_key = TString("jet_mass") + postfix;
	    CreateHistogram1DT(target, hash_key, "; mass; Events", 80, mass_min[jet1_code], mass_max[jet1_code]);
	  }
	  {
	    //	    enum VectorEnum_t     {LEADING_JET, SCND_LEADING_JET, HAD_B, HAD_W, HAD_T, LEPTON, NEUTRINO, LEPT_B, LEPT_W, LEPT_T, BEAM, FAKE };

	    const float pt_max[N_jet_types_] = {200.0, 200.0, 200.0, 200.0, 200.0, 250.0, 250.0, 200.0, 200.0, 200.0, 250.0, 250.0, 200.0, 200.0};
	    const TString hash_key = TString("jet_pt") + postfix;
	    CreateHistogram1DT(target, hash_key, "; pt; Events", 100, 0.0, pt_max[jet1_code]);
	  }
	  {
	    //	    enum VectorEnum_t     {LEADING_JET, SCND_LEADING_JET, HAD_B, HAD_W, HAD_T, LEPTON, NEUTRINO, LEPT_B, LEPT_W, LEPT_T, BEAM, FAKE };

	    const float pt_max[N_jet_types_] = {200.0, 200.0, 200.0, 200.0, 200.0, 250.0, 250.0, 200.0, 200.0, 200.0, 250.0, 250.0, 200.0, 200.0};
	    const TString hash_key = TString("jet_pt_nosf") + postfix;
	    CreateHistogram1DT(target, hash_key, "; pt; Events", 100, 0.0, pt_max[jet1_code]);
	  }
	  /*
	  {
	    const TString hash_key = TString("jet_pz") + postfix;
	    CreateHistogram1DT(target, hash_key, "; pz; Events", 100, - 300.0, 300.0);
	  }
	  {
	    const TString hash_key = TString("jet_px") + postfix;
	    CreateHistogram1DT(target, hash_key, "; px; Events", 100, - 220.0, 220.0);
	    }*/



	  //printf("%s %s\n", hash_key_phi.Data(), hash_key_eta.Data());
	}
    }
    
  //  ConfigurePtRadiationProfileTool();

}

template<typename TargetType, typename CreateHistoType>
void AssignHistograms_raw_array(TargetType  & target, CreateHistoType CreateHistogram1DT) 
{
  static const unsigned char jets[4] = {LEADING_JET, SCND_LEADING_JET, LEADING_B, SCND_LEADING_B};
  for (WorkCode_t level_code = 0; level_code < N_levels_types_; level_code ++)
    { 
      const WorkEnum_t workmode = WorkEnum_t(level_code); 
      for (VectorCode_t jet_index = 0; jet_index < 4; jet_index ++)
	{
	  unsigned char vector_code = jets[jet_index];
	  const unsigned char nbins = 11;
	  double bins[nbins + 1];
	  const float binmin = 0.0;
	  const float binmax = 1.0;
	  const float step = (binmax - binmin)/(nbins - 1);
	  for (unsigned char bind = 0; bind < nbins; bind ++)
	    {
	      bins[bind] = bind * step;
	    }
	  bins[nbins] = bins[nbins - 1] + step/2.0;
	 
	  {
	    const TString hash_key = TString("JetConst_EventChargedContentN_") + tag_levels_types_.at(workmode) + "_" + tag_jet_types_[vector_code];
	    CreateHistogram1DT(target, hash_key, "; \\frac{charged}{all}; Events", nbins, bins);
	  }
	  {
	    const TString hash_key = TString("JetConst_EventChargedContentE_") + tag_levels_types_.at(workmode) + "_" + tag_jet_types_[vector_code];
	    CreateHistogram1DT(target, hash_key, "; \\frac{charged}{all}; Events", nbins, bins);
	  }
	}
    }
}
