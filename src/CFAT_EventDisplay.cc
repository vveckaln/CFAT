#include "PullVector.hh"
#include "CFAT_Core.hh"
#include "TEllipse.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TH2F.h"
#include "TStyle.h"
#include "TArrow.h"

void CFAT_Core::EventDisplay(const PullVector & pv, float pull_angle/*, const TVector2 & jet_difference*/, ChargeCode_t charge_code) 
{
  if (event_display_mode_ == 0)
    return;

  gStyle -> SetOptStat(0);
  gROOT -> SetBatch(kTRUE); 
  //  const char* histogram_name[4] = {"leading_jet", "2nd_leading_jet", "other", "total"};
  const char* histogram_name[3] = {"leading_jet", "2nd_leading_jet", "total"};

  const TLorentzVector * leading_jet = GetVector(LEADING_JET);
  const TLorentzVector * scnd_leading_jet = GetVector(SCND_LEADING_JET);
  if (leading_jet -> Pt() > 150.0)
    return;
  TLine pull_vector(leading_jet -> Phi(),
		    leading_jet -> Rapidity(), 
		    leading_jet -> Phi() + 200 * pv.phi_component,
		    leading_jet -> Rapidity() + 200 * pv.eta_component
		    );
  pull_vector.SetLineWidth(3);
  pull_vector.SetLineStyle(kDashDotted);
  TLine jet_dif(leading_jet -> Phi(),
		leading_jet -> Rapidity(), 
		scnd_leading_jet -> Phi(),
		scnd_leading_jet -> Rapidity()
		);
  jet_dif.SetLineStyle(kDashed);
  jet_dif.SetLineWidth(3);
  TCanvas *canvas[3];
  for (unsigned char ind = 0; ind < 3; ind ++)
    {
      canvas[ind] = new TCanvas(histogram_name[ind], histogram_name[ind], 2.2*TMath::Pi()*500, 2.2*2.4*500);
    }
  
  float DeltaR = leading_jet -> DeltaR(*scnd_leading_jet);
  vector<TH2F*> TH2F_ptr_collector;
  char dir_name[128];
  sprintf(dir_name, "event_displays/event_%lu_%s_%s_DeltaR_%f_pull_angle_%f", 
	  GetCFATEvent() -> GetEventNumber(), 
	  tag_levels_[work_mode_], 
	  tag_charge_types_[charge_code], 
	  DeltaR, 
	  pull_angle);
  system(TString("mkdir ") + TString(dir_name).ReplaceAll(".", "p"));
  for (unsigned char hist_ind = 0; hist_ind < 3; hist_ind ++)
    {
      char name[128];
      sprintf(name, "event_display_%s_event_%lu_%s_%s_#DeltaR_%f_pull_angle_%f", 
	      histogram_name[hist_ind], 
	      GetCFATEvent() -> GetEventNumber(), 
	      tag_levels_[work_mode_], 
	      tag_charge_types_[charge_code],
	      DeltaR, 
	      pull_angle);
      TH2F * hist = new TH2F(name, "; #phi[rad]; y[a.u.]", 50, -1.1*TMath::Pi(), 1.1*TMath::Pi(), 50, -1.1*2.4, 1.1*2.4);
      TH2F_ptr_collector.push_back(hist);
      canvas[hist_ind] -> cd();
      hist -> Draw("9");
    }
 
 
  /*  TEllipse * b_jets[2];
  for (unsigned char ind = 0; ind < b_jets_ptr_ -> size(); ind ++)
    {
      const TLorentzVector * b_jet = &b_jets_ptr_ -> operator[](ind);
      b_jets[ind] = new TEllipse(b_jet -> Rapidity(), b_jet -> Phi(), b_jet -> Pt()/150);
      b_jets[ind] -> SetLineStyle(kDashed);
      canvas[2] -> cd();
      b_jets[ind] -> Draw();
      canvas[3] -> cd();
      b_jets[ind] -> Draw();
    }
  */
  const Color_t fill_colour[3] = {kBlue, kRed, kGreen};
  vector<TEllipse*> pointer_collector;
  
  static const unsigned char jets[2] = {LEADING_JET, SCND_LEADING_JET};
  for (unsigned char jet_index = 0; jet_index < 2; jet_index ++)
    {

      const unsigned char vector_code = jets[jet_index];
      unsigned char ind = 0;
      for(pf_iter it = begin(vector_code); it != end(vector_code); it ++)
	{
	  if (charge_code == CHARGED and it -> GetCharge() == 0)
	    continue;
	  TLorentzVector particle = it -> GetLorentzVector();
	  ind ++;
	  const float rapidity = particle.Rapidity();
	  const float phi   = particle.Phi();
	  const float radius = particle.Pt()/GetVector(vector_code) -> Pt();
	  TEllipse * ellipse = new TEllipse(phi, rapidity, radius, radius);
	  pointer_collector.push_back(ellipse);
	  //printf("Type %u Drawing %f %f %f\n", part_type_ind, Rapidity, phi, radius);
	  ellipse -> SetFillColor(fill_colour[jet_index]);
	  canvas[jet_index] -> cd();
	  ellipse -> Draw();
	  canvas[2] -> cd();
	  ellipse -> Draw();
	    
	}
    }
  canvas[2] -> cd();
  pull_vector.Draw();
  jet_dif.Draw();

  TEllipse * leading_jet_ellipse = new TEllipse(
						leading_jet -> Phi(), 
						leading_jet -> Rapidity(), 
						leading_jet -> Pt()/75.0,
						leading_jet -> Pt()/75.0);
  leading_jet_ellipse -> SetLineWidth(3);
  leading_jet_ellipse -> SetFillStyle(0);
  canvas[0] -> cd();
  leading_jet_ellipse -> Draw();
  canvas[2] -> cd();
  leading_jet_ellipse -> Draw();


  TEllipse * scnd_leading_jet_ellipse = new TEllipse(
						     scnd_leading_jet -> Phi(), 
						     scnd_leading_jet -> Rapidity(), 
						     scnd_leading_jet -> Pt()/75.0,
						     scnd_leading_jet -> Pt()/75.0);
  scnd_leading_jet_ellipse -> SetLineStyle(kDotted);
  scnd_leading_jet_ellipse -> SetLineWidth(3);
  scnd_leading_jet_ellipse -> SetFillStyle(0);
  canvas[1] -> cd();
  scnd_leading_jet_ellipse -> Draw();
  canvas[2] -> cd();
  scnd_leading_jet_ellipse -> Draw();


  for (unsigned char ind = 0; ind < 3; ind ++)
    {
      char name[128];
      sprintf(name, "%s/%s_%s_%s_%lu_DeltaR_%f_pull_angle_%f", 
	      dir_name, 
	      tag_levels_[work_mode_], 
	      tag_charge_types_[charge_code], 
	      histogram_name[ind], 
	      GetCFATEvent() -> GetEventNumber(), 
	      DeltaR, 
	      pull_angle); 
      const TString name_str = TString(name).ReplaceAll(".", "p");
      canvas[ind] -> SaveAs(name_str + ".pdf");
      printf("%p\n", canvas[ind]);
      canvas[ind] -> SaveAs(name_str + ".png");
      canvas[ind] -> SaveAs(name_str + ".eps");
    }
  for (unsigned short ind = 0; ind < pointer_collector.size(); ind ++)
    {
      delete pointer_collector[ind];
    }
  delete leading_jet_ellipse; 
  delete scnd_leading_jet_ellipse;

  for (unsigned short ind = 0; ind < TH2F_ptr_collector.size(); ind ++)
    {
      delete TH2F_ptr_collector[ind];
      delete canvas[ind];
    }
}
