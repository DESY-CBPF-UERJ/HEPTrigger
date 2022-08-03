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
  	h2->GetZaxis()->SetRangeUser(0.9,1.1);
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
	//paveCMS->AddText("#bf{CMS #it{Preliminary} 2017}        41.5 fb^{-1}    (13 TeV)");
	paveCMS->AddText("#bf{CMS #it{Preliminary} 2018}        59.8 fb^{-1}    (13 TeV)");
	paveCMS->SetFillColor(0);
	paveCMS->SetBorderSize(0);
	paveCMS->SetTextSize(0.04);
	paveCMS->SetTextFont(42);
	paveCMS->Draw();
	c0->Print( ("h_2DSF_Ratio_" + triggerSet + "_" + variable + ".png").c_str() );


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


void draw_SF_ratio()
{

 	gROOT->LoadMacro("../include/setTDRStyle_teliko.C");
	setTDRStyle_teliko();


	//////////////////////////////////////////////
	//      SFs             //////////////////////
	//////////////////////////////////////////////

	//TFile *f = new TFile("trigger_SF_root_files_lep-PU_SFs_RunII_v02_desy_ntuples_24_6_2020/tth_dileptonic_2DscaleFactors_MC_PU-lep_SFs_withSysts_2016BCDEFGH_24-06-20_updated_axis_limits.root","READ");
        //TFile *f = new TFile("trigger_SF_root_files_lep-PU_SFs_RunII_v02_desy_ntuples_24_6_2020/tth_dileptonic_2DscaleFactors_MC_PU-lep_SFs_withSysts_2017BCDEF_24-06-20_updated_axis_limits.root","READ");
        TFile *f = new TFile("trigger_SF_root_files_lep-PU_SFs_RunII_v02_desy_ntuples_24_6_2020/tth_dileptonic_2DscaleFactors_MC_PU-lep_SFs_withSysts_2018ABCD_24-06-20_updated_axis_limits.root","READ");

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

        //TFile *f1 = new TFile("Trigger_SF_root_files/Final_Trigger_SF_with_systematics_2016_Updated_axis_limits.root","READ");
        //TFile *f1 = new TFile("Trigger_SF_root_files/Final_Trigger_SF_with_systematics_2017_Updated_axis_limits.root","READ");
        TFile *f1 = new TFile("Trigger_SF_root_files/Final_Trigger_SF_with_systematics_2018_Updated_axis_limits.root","READ");

        f1->cd();

        //      Double Electron stream (OR of Single & Double electron triggers)        ///////////////

        TH2D* h_DoubleEl_OR__X__allMET_el0_pt_vs_eta_den = (TH2D*) f1->Get("h_DoubleEl_OR__X__allMET_el0_pt_vs_eta_withSysts");
        TH2D* h_DoubleEl_OR__X__allMET_el1_pt_vs_eta_den = (TH2D*) f1->Get("h_DoubleEl_OR__X__allMET_el1_pt_vs_eta_withSysts");
        TH2D* h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt_den = (TH2D*) f1->Get("h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt_withSysts");
        TH2D* h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta_den = (TH2D*) f1->Get("h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta_withSysts");

        //      EMu stream (OR of Single & Double electron triggers)    ///////////////

        TH2D* h_EMu_OR__X__allMET_el0_pt_vs_eta_den = (TH2D*) f1->Get("h_EMu_OR__X__allMET_el0_pt_vs_eta_withSysts");
        TH2D* h_EMu_OR__X__allMET_mu0_pt_vs_eta_den = (TH2D*) f1->Get("h_EMu_OR__X__allMET_mu0_pt_vs_eta_withSysts");
        TH2D* h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta_den = (TH2D*) f1->Get("h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta_withSysts");
        TH2D* h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt_den = (TH2D*) f1->Get("h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt_withSysts");

        //      Double Muon stream (OR of Single & Double electron triggers)    ///////////////

        TH2D* h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta_den = (TH2D*) f1->Get("h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta_withSysts");
        TH2D* h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta_den = (TH2D*) f1->Get("h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta_withSysts");
        TH2D* h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt_den = (TH2D*) f1->Get("h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt_withSysts");
        TH2D* h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta_den = (TH2D*) f1->Get("h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta_withSysts");

	//Ratios

	h_DoubleEl_OR__X__allMET_el0_pt_vs_eta->Divide(h_DoubleEl_OR__X__allMET_el0_pt_vs_eta_den);
	h_DoubleEl_OR__X__allMET_el1_pt_vs_eta->Divide(h_DoubleEl_OR__X__allMET_el1_pt_vs_eta_den);
	h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt->Divide(h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt_den);
	h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta->Divide(h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta_den);

	h_EMu_OR__X__allMET_el0_pt_vs_eta->Divide(h_EMu_OR__X__allMET_el0_pt_vs_eta_den);
	h_EMu_OR__X__allMET_mu0_pt_vs_eta->Divide(h_EMu_OR__X__allMET_mu0_pt_vs_eta_den);
	h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta->Divide(h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta_den);
	h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt->Divide(h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt_den);

	h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta->Divide(h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta_den);
	h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta->Divide(h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta_den);
	h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt->Divide(h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt_den);
	h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta->Divide(h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta_den);
	/*
	//Difference
        h_DoubleEl_OR__X__allMET_el0_pt_vs_eta->Add(h_DoubleEl_OR__X__allMET_el0_pt_vs_eta_den,-1.);
        h_DoubleEl_OR__X__allMET_el1_pt_vs_eta->Add(h_DoubleEl_OR__X__allMET_el1_pt_vs_eta_den,-1.);
        h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt->Add(h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt_den,-1.);
        h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta->Add(h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta_den,-1.);

        h_EMu_OR__X__allMET_el0_pt_vs_eta->Add(h_EMu_OR__X__allMET_el0_pt_vs_eta_den,-1.);
        h_EMu_OR__X__allMET_mu0_pt_vs_eta->Add(h_EMu_OR__X__allMET_mu0_pt_vs_eta_den,-1.);
        h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta->Add(h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta_den,-1.);
        h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt->Add(h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt_den,-1.);

        h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta->Add(h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta_den,-1.);
        h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta->Add(h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta_den,-1.);
        h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt->Add(h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt_den,-1.);
        h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta->Add(h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta_den,-1.);
	*/

	// Plotting

 	TCanvas* c1 = new TCanvas("c1", "c1");

	print2DScaleFactorHistogramSimple(c1, h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta, "DoubleMu_OR__X__allMET", "mu0_pt_vs_eta");
	print2DScaleFactorHistogramSimple(c1, h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta, "DoubleMu_OR__X__allMET", "mu1_pt_vs_eta");
	print2DScaleFactorHistogramSimple(c1, h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt, "DoubleMu_OR__X__allMET", "mu0_pt_vs_mu1_pt");
	print2DScaleFactorHistogramSimple(c1, h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta, "DoubleMu_OR__X__allMET", "mu0_eta_vs_mu1_eta");

	print2DScaleFactorHistogramSimple(c1, h_DoubleEl_OR__X__allMET_el0_pt_vs_eta, "DoubleEl_OR__X__allMET", "el0_pt_vs_eta");
	print2DScaleFactorHistogramSimple(c1, h_DoubleEl_OR__X__allMET_el1_pt_vs_eta, "DoubleEl_OR__X__allMET", "el1_pt_vs_eta");
	print2DScaleFactorHistogramSimple(c1, h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt, "DoubleEl_OR__X__allMET", "el0_pt_vs_el1_pt");
	print2DScaleFactorHistogramSimple(c1, h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta, "DoubleEl_OR__X__allMET", "el0_eta_vs_el1_eta");

	print2DScaleFactorHistogramSimple(c1, h_EMu_OR__X__allMET_mu0_pt_vs_eta, "EMu_OR__X__allMET", "mu0_pt_vs_eta");
	print2DScaleFactorHistogramSimple(c1, h_EMu_OR__X__allMET_el0_pt_vs_eta, "EMu_OR__X__allMET", "el0_pt_vs_eta");
	print2DScaleFactorHistogramSimple(c1, h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt, "EMu_OR__X__allMET", "mu0_pt_vs_el0_pt");
	print2DScaleFactorHistogramSimple(c1, h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta, "EMu_OR__X__allMET", "mu0_eta_vs_el0_eta");



}
