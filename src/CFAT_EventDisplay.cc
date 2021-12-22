#include "PullVector.hh"
#include "CFAT_Core.hh"
#include "TEllipse.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TH2F.h"
#include "TStyle.h"
#include "TArrow.h"
#include "TMarker.h"
#include "TLegend.h"
#include "TPad.h"
#include <iterator>
using namespace std;
TEllipseED::TEllipseED(Double_t x1, Double_t y1, Double_t r1, Double_t r2, Double_t phimin, Double_t phimax, Double_t theta): TEllipse(x1, y1, r1, r2, phimin, 360, theta)
{
  _jetindex = 255;
}

TEllipseED::~TEllipseED()
{

}

void CFAT_Core::EventDisplay(const PullVector & pv, float pull_angle/*, const TVector2 & jet_difference*/, ChargeCode_t charge_code) 
{
  if (event_display_mode_ == 0)
    return;
  if (not GetVector(HAD_B))
    return;
  static const float scale = 75.0;
  vector<TObject *> pointer_collector;
  vector<TEllipseED *> ellipse_collector;
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
		    leading_jet -> Phi() + 200 * pv.GetPhiComponent(),
		    leading_jet -> Rapidity() + 200 * pv.GetRapidityComponent()
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
  TPad *pad[2];
  for (unsigned char ind = 0; ind < 3; ind ++)
    {
      if (ind == 2)
	{
	  pad[0] = new TPad("pad1", "pad1", 0.0, 0.1, 1.0, 1.0);
	  pad[1] = new TPad("pad2", "pad2", 0.0, 0.0, 1.0, 0.1);
	  pointer_collector.push_back(pad[0]);
	  pointer_collector.push_back(pad[1]);
	}
      canvas[ind] = new TCanvas(histogram_name[ind], histogram_name[ind], 2.2*TMath::Pi()*500, 2.2*2.4*1.0/0.9*500);
      pointer_collector.push_back(canvas[ind]);
      if (ind == 2)
	{
	  canvas[2] -> cd();
	  pad[0] -> Draw();
	  pad[1] -> Draw();
	}
    }
  float DeltaR = leading_jet -> DeltaR(*scnd_leading_jet);
  vector<TH2F*> TH2F_ptr_collector;
  char dir_name[128];
  sprintf(dir_name, "event_displays/event_%lu_%s_%s_DeltaR_%f_pull_angle_%f", 
	  GetCFATEvent() -> GetEventNumber(), 
	  tag_levels_types_.at(work_mode_), 
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
	      tag_levels_types_.at(work_mode_), 
	      tag_charge_types_[charge_code],
	      DeltaR, 
	      pull_angle);
      TH2F * hist = new TH2F(name, "; #phi[rad]; y[a.u.]", 50, -1.1*TMath::Pi(), 1.1*TMath::Pi(), 50, -1.1*2.4, 1.1*2.4);
      TH2F_ptr_collector.push_back(hist);
      if (hist_ind < 2)
	canvas[hist_ind] -> cd();
      else 
	pad[0] -> cd();
      hist -> Draw("9");
    }

  const TLorentzVector * hadb = GetVector(HAD_B);
  TEllipse * hadb_ellipse = new TEllipse(hadb -> Phi(), hadb -> Rapidity(), hadb -> Pt()/scale, hadb -> Pt()/scale);
  hadb_ellipse -> SetLineColor(kGreen);
  hadb_ellipse -> SetFillStyle(0);
  hadb_ellipse -> SetLineStyle(kDashed);
  hadb_ellipse -> SetLineWidth(3);
  /*  canvas[2] -> cd();
      hadb_ellipse -> Draw();*/
  pad[0] -> cd();
  hadb_ellipse -> Draw();
  pointer_collector.push_back(hadb_ellipse);


  const TLorentzVector * leptb = GetVector(LEPT_B);
  TEllipse * leptb_ellipse = new TEllipse(leptb -> Phi(), leptb -> Rapidity(), leptb -> Pt()/scale, leptb -> Pt()/scale);
  printf("leptb phi%f % rap %f\n", leptb -> Phi(), leptb -> Rapidity());
  leptb_ellipse -> SetLineColor(kMagenta);
  leptb_ellipse -> SetFillStyle(0);
  leptb_ellipse -> SetLineWidth(3);
  leptb_ellipse -> SetLineStyle(kDashed);
  pad[0] -> cd();
  leptb_ellipse -> Draw();
  pointer_collector.push_back(leptb_ellipse);
  /*canvas[3] -> cd();
    leptb_ellipse -> Draw();*/
  
  const TLorentzVector * lepton = GetVector(LEPTON);
  TMarker * leptmarker = new TMarker(lepton -> Phi(), lepton -> Rapidity(), kMultiply);
  printf("lepton phi %f rap %f\n", lepton -> Phi(), lepton -> Rapidity());
  pad[0] -> cd();
  leptmarker -> Draw();
  leptmarker -> SetMarkerSize(14);
  pointer_collector.push_back(leptmarker);
  const unsigned char njets = 4;
  static const char * jet_titles[njets] = {"leading_jet", "scnd_leading_jet", "had_b", "lept_b"};
  const float jet_pt[njets] = {leading_jet -> Pt(), scnd_leading_jet -> Pt(), hadb -> Pt(), leptb -> Pt()};
  static const unsigned char jets[njets] = {LEADING_JET, SCND_LEADING_JET, HAD_B, LEPT_B};
  static const Color_t fill_colour[njets] = {kBlue, kRed, kGreen, kMagenta};
  
  for (unsigned char jet_index = 0; jet_index < njets; jet_index ++)
    {

      TLorentzVector checkpt(0.0, 0.0, 0.0, 0.0);
      const unsigned char vector_code = jets[jet_index];
      unsigned char ind = 0;
      unsigned char nparticles = 0;
      for(pf_iter it = begin(vector_code); it != end(vector_code); it ++)
	{
	  if (charge_code == CHARGED and it -> GetCharge() == 0)
	    {
	      printf("discarding neutral\n");
	      continue;
	    }
	  TLorentzVector particle = it -> GetLorentzVector();
	  ind ++;
	  checkpt += particle;
	  nparticles ++;
	  const float rapidity = particle.Rapidity();
	  const float phi   = particle.Phi();
	  const float radius = particle.Pt()/GetVector(vector_code) -> Pt();
	  TEllipseED * ellipse = new TEllipseED(phi, rapidity, radius, radius);
	  pointer_collector.push_back(ellipse);
	  ellipse -> _jetindex = jet_index;
	  ellipse_collector.push_back(ellipse);
	  //printf("Type %u Drawing %f %f %f\n", part_type_ind, Rapidity, phi, radius);
	  ellipse -> SetFillColor(fill_colour[jet_index]);
	  
	  // if (jet_index == 3)
	  //   printf("part phi %f rapi %f pt %f\n", phi, rapidity, particle.Pt());
	  if (jet_index < 2)
	    {
	      canvas[jet_index] -> cd(); // vector_code??
	      //ellipse -> Draw();
	    }
	  pad[0] -> cd();
	  //ellipse -> Draw();
	    
	}
      printf("jet %s pt from particles %f, jet_pt %f nparticles %u\n", jet_titles[jet_index], checkpt.Pt(), jet_pt[jet_index], nparticles);
    }
  bool sorted = true;
  do
    {
      sorted = true;
      for (vector<TEllipseED *>::iterator it = next(ellipse_collector.begin()); it != ellipse_collector.end(); it ++)
	{
	  if ((*prev(it)) -> GetR1() < (*it) -> GetR1())
	    {
	      TEllipseED * swap = *it;
	      * it = *prev(it);
	      * prev(it) = *it;
	      sorted = false;
	    }
	}
	     
    }
  while (not sorted);
  
  for (vector<TEllipseED *>::iterator it = ellipse_collector.begin(); it != ellipse_collector.end(); it ++)
    {
      if ( (*it) -> _jetindex < 2)
	{
	  canvas[(*it) -> _jetindex] -> cd(); 
	  (*it) -> Draw();
	}
      pad[0] -> cd();
      (*it) -> Draw();
    }

  pad[0] -> cd();
  pull_vector.Draw();
  jet_dif.Draw();

  TEllipse * leading_jet_ellipse = new TEllipse(
						leading_jet -> Phi(), 
						leading_jet -> Rapidity(), 
						leading_jet -> Pt()/scale,
						leading_jet -> Pt()/scale);
  leading_jet_ellipse -> SetLineWidth(3);
  leading_jet_ellipse -> SetFillStyle(0);
  canvas[0] -> cd();
  leading_jet_ellipse -> Draw();
  pad[0] -> cd();
  leading_jet_ellipse -> Draw();
  pointer_collector.push_back(leading_jet_ellipse);

  TEllipse * scnd_leading_jet_ellipse = new TEllipse(
						     scnd_leading_jet -> Phi(), 
						     scnd_leading_jet -> Rapidity(), 
						     scnd_leading_jet -> Pt()/scale,
						     scnd_leading_jet -> Pt()/scale);
  scnd_leading_jet_ellipse -> SetLineStyle(kDotted);
  scnd_leading_jet_ellipse -> SetLineWidth(3);
  scnd_leading_jet_ellipse -> SetFillStyle(0);
  pointer_collector.push_back(scnd_leading_jet_ellipse);
  canvas[1] -> cd();
  scnd_leading_jet_ellipse -> Draw();
  pad[0] -> cd();
  scnd_leading_jet_ellipse -> Draw();
  TLegend * legend = new TLegend(0.1, 0.15, 0.9, 0.9);
  pointer_collector.push_back(legend);
  legend -> SetLineWidth(0);
  legend -> SetFillStyle(0);
  legend -> SetNColumns(5);
  TEllipse * formatellipse[njets];
  const char * jettitles[njets] = {"j_{1}^{W}", "j_{2}^{W}", "j_{h}^{b}", "j_{l}^{b}"};
  for (unsigned char ellipse_ind = 0; ellipse_ind < njets; ellipse_ind ++)
    {
      formatellipse[ellipse_ind] = new TEllipse();
      formatellipse[ellipse_ind] -> SetFillColor(fill_colour[ellipse_ind]);
      legend -> AddEntry(formatellipse[ellipse_ind], jettitles[ellipse_ind], "f");
      pointer_collector.push_back(formatellipse[ellipse_ind]);
    }
  legend -> AddEntry(leptmarker, "lepton", "p");
  pad[1] -> cd();
  legend -> Draw();
  for (unsigned char ind = 0; ind < 3; ind ++)
    {
      char name[128];
      sprintf(name, "%s/%s_%s_%s_%lu_DeltaR_%f_pull_angle_%f", 
	      dir_name, 
	      tag_levels_types_.at(work_mode_), 
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
  /*delete leading_jet_ellipse; 
  delete scnd_leading_jet_ellipse;

  for (unsigned short ind = 0; ind < TH2F_ptr_collector.size(); ind ++)
    {
      delete TH2F_ptr_collector[ind];
      delete canvas[ind];
    }
  delete pad[0];
  delete pad[1];
  delete leptmarker;*/
}
