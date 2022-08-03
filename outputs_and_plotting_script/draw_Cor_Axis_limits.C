#include "TH1D.h"
#include "TH2D.h"
#include "TH2F.h"
#include "TTree.h"
#include "TFile.h"
#include "TDirectory.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TStyle.h"
#include "TChain.h"
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "TROOT.h"
#include <TColor.h>
#include <TF1.h>
#include <TH1F.h>
#include <TFile.h>
#include "TH1.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TAxis.h"
#include <TCanvas.h>
#include <TF1.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TPaveText.h>
#include <TMarker.h>
#include <TLine.h>
#include <TAxis.h>
#include <TStyle.h>
#include <TH1.h>
#include "TGraph.h"
#include "TPaletteAxis.h"
#include "TGraphAsymmErrors.h"
#include "TEfficiency.h"
#include "../include/setTDRStyle_teliko.C"

void print2DScaleFactorHistogramSimple(TCanvas* c0, TH2D* h2, string triggerSet, string variable)
{

  	gStyle->SetPaintTextFormat("1.3f");

  	c0->cd();
  	h2->Draw("colz e TEXT");
  	h2->GetZaxis()->SetRangeUser(0.89,1.01);
  	h2->GetZaxis()->SetLabelSize(0.03);
  	h2->GetXaxis()->SetLabelSize(0.04);
  	h2->GetYaxis()->SetLabelSize(0.04);
  	h2->GetYaxis()->SetTitleSize(0.045);
  	h2->GetXaxis()->SetTitleSize(0.045);

  	TLatex ltx1;
  	ltx1.SetTextAlign(9);
  	ltx1.SetTextFont(62);
  	ltx1.SetTextSize(0.025);
  	ltx1.SetNDC();
  	ltx1.DrawLatex(0.2, 0.59, triggerSet.c_str());


	// CMS box for plotting the canvases    ///////
	TPaveText *paveCMS = new TPaveText(0.15,0.96,0.91,0.99,"NDC");
	//paveCMS->AddText("#bf{CMS #it{Preliminary} 2016}        35.9 fb^{-1}    (13 TeV)");
	paveCMS->AddText("#bf{CMS #it{Preliminary} 2017}        41.5 fb^{-1}    (13 TeV)");
	//paveCMS->AddText("#bf{CMS #it{Preliminary} 2018}        59.8 fb^{-1}    (13 TeV)");
	paveCMS->SetFillColor(0);
	paveCMS->SetBorderSize(0);
	paveCMS->SetTextSize(0.04);
	paveCMS->SetTextFont(42);
	paveCMS->Draw();
	c0->Print( ("h_2DSF_" + triggerSet + "_" + variable + ".png").c_str() );


}

void FillHisto(TH2D &h1,TH2D* h2)
{

	for(int i=1; i<=h1.GetNbinsX();++i){
		for(int j=1; j<=h1.GetNbinsY();++j){
			h1.SetBinContent(i,j,h2->GetBinContent(i,j));
			h1.SetBinError(i,j,h2->GetBinError(i,j));
		}
	}


}


void draw_Cor_Axis_limits()
{

 	gROOT->LoadMacro("../include/setTDRStyle_teliko.C");
	setTDRStyle_teliko();


	//////////////////////////////////////////////
	//      SFs             //////////////////////
	//////////////////////////////////////////////

	//TFile *f = new TFile("tth_dileptonic_2DscaleFactors_MC_PU-lep_SFs_withSysts_2016BCDEFGH_24-06-20.root","READ");
        TFile *f = new TFile("tth_dileptonic_2DscaleFactors_MC_PU-lep_SFs_withSysts_2017BCDEF_24-06-20.root","READ");
        //TFile *f = new TFile("tth_dileptonic_2DscaleFactors_MC_PU-lep_SFs_withSysts_2018ABCD_24-06-20.root","READ");


	f->cd();

	//      Double Electron stream (OR of Single & Double electron triggers)        ///////////////

	TH2D* h_DoubleEl_OR__X__allMET_el0_pt_vs_eta = (TH2D*) f->Get("h_DoubleEl_OR__X__allMET_el0_pt_vs_eta_withSysts");
	TH2D* h_DoubleEl_OR__X__allMET_el1_pt_vs_eta = (TH2D*) f->Get("h_DoubleEl_OR__X__allMET_el1_pt_vs_eta_withSysts");
	TH2D* h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt = (TH2D*) f->Get("h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt_withSysts");
 	TH2D* h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta = (TH2D*) f->Get("h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta_withSysts");

	//      EMu stream (OR of Single & Double electron triggers)    ///////////////

	TH2D* h_EMu_OR__X__allMET_el0_pt_vs_eta = (TH2D*) f->Get("h_EMu_OR__X__allMET_el0_pt_vs_eta_withSysts");
	TH2D* h_EMu_OR__X__allMET_mu0_pt_vs_eta = (TH2D*) f->Get("h_EMu_OR__X__allMET_mu0_pt_vs_eta_withSysts");
	TH2D* h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta = (TH2D*) f->Get("h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta_withSysts");
	TH2D* h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt = (TH2D*) f->Get("h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt_withSysts");

	//      Double Muon stream (OR of Single & Double electron triggers)    ///////////////

	TH2D* h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta = (TH2D*) f->Get("h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta_withSysts");
	TH2D* h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta = (TH2D*) f->Get("h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta_withSysts");
	TH2D* h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt = (TH2D*) f->Get("h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt_withSysts");
	TH2D* h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta = (TH2D*) f->Get("h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta_withSysts");


  	const Int_t nbins_subleadPt_2D = 3;
  	Double_t edges_subleadPt_2D[nbins_subleadPt_2D + 1] = {15.0, 50.0, 90.0, 200.0};
  	Double_t edges_leadPt_2D[nbins_subleadPt_2D + 1] = {25.0, 50.0, 90.0, 200.0};
  	const Int_t nbins_pt_2D = 4;
  	Double_t edges_pt_2D[nbins_pt_2D + 1] = {25.0, 50.0, 80.0, 120.0, 200.0};
	const Int_t nbins_pt_2D_emu = 4;
	Double_t edges_pt_2D_emu[nbins_pt_2D + 1] = {15.0, 50.0, 80.0, 120.0, 200.0};

 	const Int_t nbins_eta_2D = 4;
  	Double_t edges_eta_2D[nbins_eta_2D + 1] = {0, 0.4, 0.9, 1.5, 2.4};
  	const Int_t nbins_subleadEta_2D = 3;
  	Double_t edges_subleadEta_2D[nbins_eta_2D + 1] = {0, 0.4, 0.9, 2.4};


	TH2D* h_DoubleEl_OR__X__allMET_el0_pt_vs_eta_new = new TH2D("h_DoubleEl_OR__X__allMET_el0_pt_vs_eta","h_DoubleEl_OR__X__allMET_el0_pt_vs_eta",nbins_pt_2D,edges_pt_2D,nbins_eta_2D,edges_eta_2D);
	h_DoubleEl_OR__X__allMET_el0_pt_vs_eta_new->SetXTitle(h_DoubleEl_OR__X__allMET_el0_pt_vs_eta->GetXaxis()->GetTitle());
	h_DoubleEl_OR__X__allMET_el0_pt_vs_eta_new->SetYTitle(h_DoubleEl_OR__X__allMET_el0_pt_vs_eta->GetYaxis()->GetTitle());

	TH2D* h_DoubleEl_OR__X__allMET_el1_pt_vs_eta_new = new TH2D("h_DoubleEl_OR__X__allMET_el1_pt_vs_eta","h_DoubleEl_OR__X__allMET_el1_pt_vs_eta",nbins_subleadPt_2D,edges_subleadPt_2D,nbins_subleadEta_2D,edges_subleadEta_2D);
	h_DoubleEl_OR__X__allMET_el1_pt_vs_eta_new->SetXTitle(h_DoubleEl_OR__X__allMET_el1_pt_vs_eta->GetXaxis()->GetTitle());
	h_DoubleEl_OR__X__allMET_el1_pt_vs_eta_new->SetYTitle(h_DoubleEl_OR__X__allMET_el1_pt_vs_eta->GetYaxis()->GetTitle());

	TH2D* h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt_new = new TH2D("h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt","h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt",nbins_subleadPt_2D,edges_leadPt_2D,nbins_subleadPt_2D,edges_subleadPt_2D);
	h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt_new->SetXTitle(h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt->GetXaxis()->GetTitle());
	h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt_new->SetYTitle(h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt->GetYaxis()->GetTitle());


	TH2D* h_EMu_OR__X__allMET_el0_pt_vs_eta_new = new TH2D("h_EMu_OR__X__allMET_el0_pt_vs_eta","h_EMu_OR__X__allMET_el0_pt_vs_eta",nbins_pt_2D_emu,edges_pt_2D_emu,nbins_eta_2D,edges_eta_2D);
	h_EMu_OR__X__allMET_el0_pt_vs_eta_new->SetXTitle(h_EMu_OR__X__allMET_el0_pt_vs_eta->GetXaxis()->GetTitle());
	h_EMu_OR__X__allMET_el0_pt_vs_eta_new->SetYTitle(h_EMu_OR__X__allMET_el0_pt_vs_eta->GetYaxis()->GetTitle());


	TH2D* h_EMu_OR__X__allMET_mu0_pt_vs_eta_new = new TH2D("h_EMu_OR__X__allMET_mu0_pt_vs_eta","h_EMu_OR__X__allMET_mu0_pt_vs_eta",nbins_pt_2D_emu,edges_pt_2D_emu,nbins_eta_2D,edges_eta_2D);
	h_EMu_OR__X__allMET_mu0_pt_vs_eta_new->SetXTitle(h_EMu_OR__X__allMET_mu0_pt_vs_eta->GetXaxis()->GetTitle());
	h_EMu_OR__X__allMET_mu0_pt_vs_eta_new->SetYTitle(h_EMu_OR__X__allMET_mu0_pt_vs_eta->GetYaxis()->GetTitle());


	TH2D* h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt_new = new TH2D("h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt","h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt",nbins_pt_2D_emu,edges_pt_2D_emu,nbins_pt_2D_emu,edges_pt_2D_emu);
	h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt_new->SetXTitle(h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt->GetXaxis()->GetTitle());
	h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt_new->SetYTitle(h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt->GetYaxis()->GetTitle());


	TH2D* h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta_new = new TH2D("h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta","h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta",nbins_pt_2D,edges_pt_2D,nbins_eta_2D,edges_eta_2D);
	h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta_new->SetXTitle(h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta->GetXaxis()->GetTitle());
	h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta_new->SetYTitle(h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta->GetYaxis()->GetTitle());

	TH2D* h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta_new = new TH2D("h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta","h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta",nbins_subleadPt_2D,edges_subleadPt_2D,nbins_subleadEta_2D,edges_subleadEta_2D);
	h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta_new->SetXTitle(h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta->GetXaxis()->GetTitle());
	h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta_new->SetYTitle(h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta->GetYaxis()->GetTitle());


 	TH2D* h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt_new = new TH2D("h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt","h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt",nbins_subleadPt_2D,edges_leadPt_2D,nbins_subleadPt_2D,edges_subleadPt_2D);
	h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt_new->SetXTitle(h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt->GetXaxis()->GetTitle());
	h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt_new->SetYTitle(h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt->GetYaxis()->GetTitle());


	FillHisto(*h_DoubleEl_OR__X__allMET_el0_pt_vs_eta_new,h_DoubleEl_OR__X__allMET_el0_pt_vs_eta);
	FillHisto(*h_DoubleEl_OR__X__allMET_el1_pt_vs_eta_new,h_DoubleEl_OR__X__allMET_el1_pt_vs_eta);
	FillHisto(*h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt_new,h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt);

	FillHisto(*h_EMu_OR__X__allMET_el0_pt_vs_eta_new,h_EMu_OR__X__allMET_el0_pt_vs_eta);
	FillHisto(*h_EMu_OR__X__allMET_mu0_pt_vs_eta_new,h_EMu_OR__X__allMET_mu0_pt_vs_eta);
	FillHisto(*h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt_new,h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt);

	FillHisto(*h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta_new,h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta);
	FillHisto(*h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta_new,h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta);
	FillHisto(*h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt_new,h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt);


 	TCanvas* c1 = new TCanvas("c1", "c1");

	//f=new TFile("tth_dileptonic_2DscaleFactors_MC_PU-lep_SFs_withSysts_2016BCDEFGH_24-06-20_updated_axis_limits.root","RECREATE");
        f=new TFile("tth_dileptonic_2DscaleFactors_MC_PU-lep_SFs_withSysts_2017BCDEF_24-06-20_updated_axis_limits.root","RECREATE");
        //f=new TFile("tth_dileptonic_2DscaleFactors_MC_PU-lep_SFs_withSysts_2018ABCD_24-06-20_updated_axis_limits.root","RECREATE");

	print2DScaleFactorHistogramSimple(c1, h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta_new, "DoubleMu_OR__X__allMET", "mu0_pt_vs_eta");
	print2DScaleFactorHistogramSimple(c1, h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta_new, "DoubleMu_OR__X__allMET", "mu1_pt_vs_eta");
	print2DScaleFactorHistogramSimple(c1, h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt_new, "DoubleMu_OR__X__allMET", "mu0_pt_vs_mu1_pt");
	print2DScaleFactorHistogramSimple(c1, h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta, "DoubleMu_OR__X__allMET", "mu0_eta_vs_mu1_eta");

	print2DScaleFactorHistogramSimple(c1, h_DoubleEl_OR__X__allMET_el0_pt_vs_eta_new, "DoubleEl_OR__X__allMET", "el0_pt_vs_eta");
	print2DScaleFactorHistogramSimple(c1, h_DoubleEl_OR__X__allMET_el1_pt_vs_eta_new, "DoubleEl_OR__X__allMET", "el1_pt_vs_eta");
	print2DScaleFactorHistogramSimple(c1, h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt_new, "DoubleEl_OR__X__allMET", "el0_pt_vs_el1_pt");
	print2DScaleFactorHistogramSimple(c1, h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta, "DoubleEl_OR__X__allMET", "el0_eta_vs_el1_eta");

	print2DScaleFactorHistogramSimple(c1, h_EMu_OR__X__allMET_mu0_pt_vs_eta_new, "EMu_OR__X__allMET", "mu0_pt_vs_eta");
	print2DScaleFactorHistogramSimple(c1, h_EMu_OR__X__allMET_el0_pt_vs_eta_new, "EMu_OR__X__allMET", "el0_pt_vs_eta");
	print2DScaleFactorHistogramSimple(c1, h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt_new, "EMu_OR__X__allMET", "mu0_pt_vs_el0_pt");
	print2DScaleFactorHistogramSimple(c1, h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta, "EMu_OR__X__allMET", "mu0_eta_vs_el0_eta");


	h_DoubleEl_OR__X__allMET_el0_pt_vs_eta_new->SetName("h_DoubleEl_OR__X__allMET_el0_pt_vs_eta_withSysts");
	h_DoubleEl_OR__X__allMET_el0_pt_vs_eta_new->Write();
	h_DoubleEl_OR__X__allMET_el1_pt_vs_eta_new->SetName("h_DoubleEl_OR__X__allMET_el1_pt_vs_eta_withSysts");
	h_DoubleEl_OR__X__allMET_el1_pt_vs_eta_new->Write();
	h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt_new->SetName("h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt_withSysts");
	h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt_new->Write();
	h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta->SetName("h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta_withSysts");
	h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta->Write();

	h_EMu_OR__X__allMET_el0_pt_vs_eta_new->SetName("h_EMu_OR__X__allMET_el0_pt_vs_eta_withSysts");
	h_EMu_OR__X__allMET_el0_pt_vs_eta_new->Write();
	h_EMu_OR__X__allMET_mu0_pt_vs_eta_new->SetName("h_EMu_OR__X__allMET_mu0_pt_vs_eta_withSysts");
	h_EMu_OR__X__allMET_mu0_pt_vs_eta_new->Write();
	h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta->SetName("h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta_withSysts");
	h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta->Write();
	h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt_new->SetName("h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt_withSysts");
	h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt_new->Write();

	h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta_new->SetName("h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta_withSysts");
	h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta_new->Write();
	h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta_new->SetName("h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta_withSysts");
	h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta_new->Write();
	h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt_new->SetName("h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt_withSysts");
	h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt_new->Write();
	h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta->SetName("h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta_withSysts");
	h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta->Write();

}
