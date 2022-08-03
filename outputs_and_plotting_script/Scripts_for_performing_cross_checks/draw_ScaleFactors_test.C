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
#include </afs/cern.ch/work/c/ckoraka/codes/setTDRStyle_teliko.C>

void draw_ScaleFactors_test()
{

 	gROOT->LoadMacro("/afs/cern.ch/work/c/ckoraka/codes/setTDRStyle_teliko.C");
        setTDRStyle_teliko();

        // CMS box for plotting the canvases    ///////
        TPaveText *paveCMS = new TPaveText(0.18,0.96,0.93,0.99,"NDC");
        //paveCMS->AddText("#bf{CMS #it{Preliminary} 2016}              35.9 fb^{-1}    (13 TeV)");
        //paveCMS->AddText("#bf{CMS #it{Preliminary} 2017}              41.5 fb^{-1}    (13 TeV)");
        paveCMS->AddText("#bf{CMS #it{Preliminary} 2018}              59.8 fb^{-1}    (13 TeV)");
        paveCMS->SetFillColor(0);
        paveCMS->SetBorderSize(0);
        paveCMS->SetTextSize(0.04);
        paveCMS->SetTextFont(42);


	//////////////////////////////////////////////
	//	DATA		//////////////////////
	//////////////////////////////////////////////

        //TFile *f = new TFile("output_rootfiles_with_efficiencies/2016/efficiency_MET_2016_All_Runs.root","READ");
        //TFile *f = new TFile("output_rootfiles_with_efficiencies/2017/efficiency_MET_allRuns_2017.root","READ");
        TFile *f = new TFile("output_rootfiles_with_efficiencies/2018/MET_2018_all_data.root","READ");
        f->cd();

	//	Double Electron stream (OR of Single & Double electron triggers)	///////////////

        TH2D* h_HLT_allMET_elStreamDL_el0_pt_vs_eta = (TH2D*) f->Get("h_HLT_allMET_elStreamDL_el0_pt_vs_eta");
        TH2D* h_DoubleEl_OR__X__allMET_el0_pt_vs_eta = (TH2D*) f->Get("h_DoubleEl_OR__X__allMET_el0_pt_vs_eta");
	TH2D *eff_DoubleEl_OR_vs_el0_pt_vs_eta = (TH2D*)h_DoubleEl_OR__X__allMET_el0_pt_vs_eta->Clone();
	eff_DoubleEl_OR_vs_el0_pt_vs_eta->Divide(h_HLT_allMET_elStreamDL_el0_pt_vs_eta);

        TH2D* h_HLT_allMET_elStreamDL_el1_pt_vs_eta = (TH2D*) f->Get("h_HLT_allMET_elStreamDL_el1_pt_vs_eta");
        TH2D* h_DoubleEl_OR__X__allMET_el1_pt_vs_eta = (TH2D*) f->Get("h_DoubleEl_OR__X__allMET_el1_pt_vs_eta");
	TH2D *eff_DoubleEl_OR_vs_el1_pt_vs_eta = (TH2D*)h_DoubleEl_OR__X__allMET_el1_pt_vs_eta->Clone();
	eff_DoubleEl_OR_vs_el1_pt_vs_eta->Divide(h_HLT_allMET_elStreamDL_el1_pt_vs_eta);

        TH2D* h_HLT_allMET_elStreamDL_el0_pt_vs_el1_pt = (TH2D*) f->Get("h_HLT_allMET_elStreamDL_el0_pt_vs_el1_pt");
        TH2D* h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt = (TH2D*) f->Get("h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt");
	TH2D *eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt = (TH2D*)h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt->Clone();
	eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->Divide(h_HLT_allMET_elStreamDL_el0_pt_vs_el1_pt);

        TH2D* h_HLT_allMET_elStreamDL_el0_eta_vs_el1_eta = (TH2D*) f->Get("h_HLT_allMET_elStreamDL_el0_eta_vs_el1_eta");
        TH2D* h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta = (TH2D*) f->Get("h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta");
	TH2D *eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta = (TH2D*)h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta->Clone();
	eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta->Divide(h_HLT_allMET_elStreamDL_el0_eta_vs_el1_eta);

 


	//	EMu stream (OR of Single & Double electron triggers)	///////////////

        TH2D* h_HLT_allMET_emuStreamDL_el0_pt_vs_eta = (TH2D*) f->Get("h_HLT_allMET_emuStreamDL_el0_pt_vs_eta");
        TH2D* h_EMu_OR__X__allMET_el0_pt_vs_eta = (TH2D*) f->Get("h_EMu_OR__X__allMET_el0_pt_vs_eta");
	TH2D *eff_EMu_OR_vs_el0_pt_vs_eta = (TH2D*)h_EMu_OR__X__allMET_el0_pt_vs_eta->Clone();
	eff_EMu_OR_vs_el0_pt_vs_eta->Divide(h_HLT_allMET_emuStreamDL_el0_pt_vs_eta);

        TH2D* h_HLT_allMET_emuStreamDL_mu0_pt_vs_eta = (TH2D*) f->Get("h_HLT_allMET_emuStreamDL_mu0_pt_vs_eta");
        TH2D* h_EMu_OR__X__allMET_mu0_pt_vs_eta = (TH2D*) f->Get("h_EMu_OR__X__allMET_mu0_pt_vs_eta");
	TH2D *eff_EMu_OR_vs_mu0_pt_vs_eta = (TH2D*)h_EMu_OR__X__allMET_mu0_pt_vs_eta->Clone();
	eff_EMu_OR_vs_mu0_pt_vs_eta->Divide(h_HLT_allMET_emuStreamDL_mu0_pt_vs_eta);

        TH2D* h_HLT_allMET_emuStreamDL_mu0_eta_vs_el0_eta = (TH2D*) f->Get("h_HLT_allMET_emuStreamDL_mu0_eta_vs_el0_eta");
        TH2D* h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta = (TH2D*) f->Get("h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta");
	TH2D *eff_EMu_OR_vs_mu0_eta_vs_el0_eta = (TH2D*)h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta->Clone();
	eff_EMu_OR_vs_mu0_eta_vs_el0_eta->Divide(h_HLT_allMET_emuStreamDL_mu0_eta_vs_el0_eta);

        TH2D* h_HLT_allMET_emuStreamDL_mu0_pt_vs_el0_pt = (TH2D*) f->Get("h_HLT_allMET_emuStreamDL_mu0_pt_vs_el0_pt");
        TH2D* h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt = (TH2D*) f->Get("h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt");
	TH2D *eff_EMu_OR_vs_mu0_pt_vs_el0_pt = (TH2D*)h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt->Clone();
	eff_EMu_OR_vs_mu0_pt_vs_el0_pt->Divide(h_HLT_allMET_emuStreamDL_mu0_pt_vs_el0_pt);


	//	Double Muon stream (OR of Single & Double electron triggers)	///////////////

        TH2D* h_HLT_allMET_muStreamDL_mu1_pt_vs_eta = (TH2D*) f->Get("h_HLT_allMET_muStreamDL_mu1_pt_vs_eta");
        TH2D* h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta = (TH2D*) f->Get("h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta");
	TH2D *eff_DoubleMu_OR_vs_mu1_pt_vs_eta = (TH2D*)h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta->Clone();
	eff_DoubleMu_OR_vs_mu1_pt_vs_eta->Divide(h_HLT_allMET_muStreamDL_mu1_pt_vs_eta);

        TH2D* h_HLT_allMET_muStreamDL_mu0_pt_vs_eta = (TH2D*) f->Get("h_HLT_allMET_muStreamDL_mu0_pt_vs_eta");
        TH2D* h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta = (TH2D*) f->Get("h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta");
	TH2D *eff_DoubleMu_OR_vs_mu0_pt_vs_eta = (TH2D*)h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta->Clone();
	eff_DoubleMu_OR_vs_mu0_pt_vs_eta->Divide(h_HLT_allMET_muStreamDL_mu0_pt_vs_eta);

        TH2D* h_HLT_allMET_muStreamDL_mu0_pt_vs_mu1_pt = (TH2D*) f->Get("h_HLT_allMET_muStreamDL_mu0_pt_vs_mu1_pt");
        TH2D* h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt = (TH2D*) f->Get("h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt");
	TH2D *eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt = (TH2D*)h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt->Clone();
	eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->Divide(h_HLT_allMET_muStreamDL_mu0_pt_vs_mu1_pt);

        TH2D* h_HLT_allMET_muStreamDL_mu0_eta_vs_mu1_eta = (TH2D*) f->Get("h_HLT_allMET_muStreamDL_mu0_eta_vs_mu1_eta");
        TH2D* h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta = (TH2D*) f->Get("h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta");
	TH2D *eff_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta = (TH2D*)h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta->Clone();
	eff_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta->Divide(h_HLT_allMET_muStreamDL_mu0_eta_vs_mu1_eta);


	///////////////////

	//////////////////////////////////////////////
	//	MC		//////////////////////
	//////////////////////////////////////////////

        //TFile *f_MC  = new TFile("output_rootfiles_with_efficiencies/2016/MC_TT_DL_2016_94X.root","READ");
        //TFile *f_MC  = new TFile("output_rootfiles_with_efficiencies/2017/efficiency_MC_TT_DL_2017.root","READ");
        TFile *f_MC  = new TFile("output_rootfiles_with_efficiencies/2018/TT_DL_MC_efficiency_2018_102X.root","READ");
        f_MC->cd();

	//	Double Electron stream (OR of Single & Double electron triggers)	//////////////
    
        TH2D* h_HLT_allMET_elStreamDL_el0_pt_MC_vs_eta = (TH2D*) f_MC->Get("h_HLT_allMET_elStreamDL_el0_pt_vs_eta");
        TH2D* h_DoubleEl_OR__X__allMET_el0_pt_MC_vs_eta = (TH2D*) f_MC->Get("h_DoubleEl_OR__X__allMET_el0_pt_vs_eta");
        TH2D *eff_DoubleEl_OR_vs_el0_pt_MC_vs_eta = (TH2D*)h_DoubleEl_OR__X__allMET_el0_pt_MC_vs_eta->Clone();
        eff_DoubleEl_OR_vs_el0_pt_MC_vs_eta->Divide(h_HLT_allMET_elStreamDL_el0_pt_MC_vs_eta);

        TH2D* h_HLT_allMET_elStreamDL_el1_pt_MC_vs_eta = (TH2D*) f_MC->Get("h_HLT_allMET_elStreamDL_el1_pt_vs_eta");
        TH2D* h_DoubleEl_OR__X__allMET_el1_pt_MC_vs_eta = (TH2D*) f_MC->Get("h_DoubleEl_OR__X__allMET_el1_pt_vs_eta");
        TH2D *eff_DoubleEl_OR_vs_el1_pt_MC_vs_eta = (TH2D*)h_DoubleEl_OR__X__allMET_el1_pt_MC_vs_eta->Clone();
        eff_DoubleEl_OR_vs_el1_pt_MC_vs_eta->Divide(h_HLT_allMET_elStreamDL_el1_pt_MC_vs_eta);

        TH2D* h_HLT_allMET_elStreamDL_el0_pt_vs_el1_pt_MC = (TH2D*) f_MC->Get("h_HLT_allMET_elStreamDL_el0_pt_vs_el1_pt");
        TH2D* h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt_MC = (TH2D*) f_MC->Get("h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt");
        TH2D *eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_MC = (TH2D*)h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt_MC->Clone();
        eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_MC->Divide(h_HLT_allMET_elStreamDL_el0_pt_vs_el1_pt_MC);

        TH2D* h_HLT_allMET_elStreamDL_el0_eta_vs_el1_eta_MC = (TH2D*) f_MC->Get("h_HLT_allMET_elStreamDL_el0_eta_vs_el1_eta");
        TH2D* h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta_MC = (TH2D*) f_MC->Get("h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta");
        TH2D *eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta_MC = (TH2D*)h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta_MC->Clone();
        eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta_MC->Divide(h_HLT_allMET_elStreamDL_el0_eta_vs_el1_eta_MC);


	//	EMu stream (OR of Single & Double electron triggers)	//////////////

        TH2D* h_HLT_allMET_emuStreamDL_el0_pt_MC_vs_eta = (TH2D*) f_MC->Get("h_HLT_allMET_emuStreamDL_el0_pt_vs_eta");
        TH2D* h_EMu_OR__X__allMET_el0_pt_MC_vs_eta = (TH2D*) f_MC->Get("h_EMu_OR__X__allMET_el0_pt_vs_eta");
        TH2D *eff_EMu_OR_vs_el0_pt_MC_vs_eta = (TH2D*)h_EMu_OR__X__allMET_el0_pt_MC_vs_eta->Clone();
        eff_EMu_OR_vs_el0_pt_MC_vs_eta->Divide(h_HLT_allMET_emuStreamDL_el0_pt_MC_vs_eta);

        TH2D* h_HLT_allMET_emuStreamDL_mu0_pt_MC_vs_eta = (TH2D*) f_MC->Get("h_HLT_allMET_emuStreamDL_mu0_pt_vs_eta");
        TH2D* h_EMu_OR__X__allMET_mu0_pt_MC_vs_eta = (TH2D*) f_MC->Get("h_EMu_OR__X__allMET_mu0_pt_vs_eta");
        TH2D *eff_EMu_OR_vs_mu0_pt_MC_vs_eta = (TH2D*)h_EMu_OR__X__allMET_mu0_pt_MC_vs_eta->Clone();
        eff_EMu_OR_vs_mu0_pt_MC_vs_eta->Divide(h_HLT_allMET_emuStreamDL_mu0_pt_MC_vs_eta);

        TH2D* h_HLT_allMET_emuStreamDL_mu0_eta_vs_el0_eta_MC = (TH2D*) f_MC->Get("h_HLT_allMET_emuStreamDL_mu0_eta_vs_el0_eta");
        TH2D* h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta_MC = (TH2D*) f_MC->Get("h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta");
        TH2D *eff_EMu_OR_vs_mu0_eta_vs_el0_eta_MC = (TH2D*)h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta_MC->Clone();
        eff_EMu_OR_vs_mu0_eta_vs_el0_eta_MC->Divide(h_HLT_allMET_emuStreamDL_mu0_eta_vs_el0_eta_MC);

        TH2D* h_HLT_allMET_emuStreamDL_mu0_pt_vs_el0_pt_MC = (TH2D*) f_MC->Get("h_HLT_allMET_emuStreamDL_mu0_pt_vs_el0_pt");
        TH2D* h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt_MC = (TH2D*) f_MC->Get("h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt");
        TH2D *eff_EMu_OR_vs_mu0_pt_vs_el0_pt_MC = (TH2D*)h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt_MC->Clone();
        eff_EMu_OR_vs_mu0_pt_vs_el0_pt_MC->Divide(h_HLT_allMET_emuStreamDL_mu0_pt_vs_el0_pt_MC);


	//	Double Muon stream (OR of Single & Double electron triggers)	//////////////

        TH2D* h_HLT_allMET_muStreamDL_mu1_pt_MC_vs_eta= (TH2D*) f_MC->Get("h_HLT_allMET_muStreamDL_mu1_pt_vs_eta");
        TH2D* h_DoubleMu_OR__X__allMET_mu1_pt_MC_vs_eta = (TH2D*) f_MC->Get("h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta");
        TH2D *eff_DoubleMu_OR_vs_mu1_pt_MC_vs_eta = (TH2D*)h_DoubleMu_OR__X__allMET_mu1_pt_MC_vs_eta->Clone();
        eff_DoubleMu_OR_vs_mu1_pt_MC_vs_eta->Divide(h_HLT_allMET_muStreamDL_mu1_pt_MC_vs_eta);

        TH2D* h_HLT_allMET_muStreamDL_mu0_pt_MC_vs_eta = (TH2D*) f_MC->Get("h_HLT_allMET_muStreamDL_mu0_pt_vs_eta");
        TH2D* h_DoubleMu_OR__X__allMET_mu0_pt_MC_vs_eta = (TH2D*) f_MC->Get("h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta");
        TH2D *eff_DoubleMu_OR_vs_mu0_pt_MC_vs_eta = (TH2D*)h_DoubleMu_OR__X__allMET_mu0_pt_MC_vs_eta->Clone();
        eff_DoubleMu_OR_vs_mu0_pt_MC_vs_eta->Divide(h_HLT_allMET_muStreamDL_mu0_pt_MC_vs_eta);

        TH2D* h_HLT_allMET_muStreamDL_mu0_pt_vs_mu1_pt_MC = (TH2D*) f_MC->Get("h_HLT_allMET_muStreamDL_mu0_pt_vs_mu1_pt");
        TH2D* h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt_MC = (TH2D*) f_MC->Get("h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt");
        TH2D *eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_MC = (TH2D*)h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt_MC->Clone();
        eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_MC->Divide(h_HLT_allMET_muStreamDL_mu0_pt_vs_mu1_pt_MC);

        TH2D* h_HLT_allMET_muStreamDL_mu0_eta_vs_mu1_eta_MC = (TH2D*) f_MC->Get("h_HLT_allMET_muStreamDL_mu0_eta_vs_mu1_eta");
        TH2D* h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta_MC = (TH2D*) f_MC->Get("h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta");
        TH2D *eff_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta_MC = (TH2D*)h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta_MC->Clone();
        eff_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta_MC->Divide(h_HLT_allMET_muStreamDL_mu0_eta_vs_mu1_eta_MC);


	/////////////////////////////

	eff_DoubleEl_OR_vs_el0_pt_vs_eta->Divide(eff_DoubleEl_OR_vs_el0_pt_MC_vs_eta);
	eff_DoubleEl_OR_vs_el1_pt_vs_eta->Divide(eff_DoubleEl_OR_vs_el1_pt_MC_vs_eta);
	eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->Divide(eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_MC);
	eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta->Divide(eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta_MC);

	eff_EMu_OR_vs_el0_pt_vs_eta->Divide(eff_EMu_OR_vs_el0_pt_MC_vs_eta);
	eff_EMu_OR_vs_mu0_pt_vs_eta->Divide(eff_EMu_OR_vs_mu0_pt_MC_vs_eta);
	eff_EMu_OR_vs_mu0_eta_vs_el0_eta->Divide(eff_EMu_OR_vs_mu0_eta_vs_el0_eta_MC);
	eff_EMu_OR_vs_mu0_pt_vs_el0_pt->Divide(eff_EMu_OR_vs_mu0_pt_vs_el0_pt_MC);

	eff_DoubleMu_OR_vs_mu1_pt_vs_eta->Divide(eff_DoubleMu_OR_vs_mu1_pt_MC_vs_eta);
	eff_DoubleMu_OR_vs_mu0_pt_vs_eta->Divide(eff_DoubleMu_OR_vs_mu0_pt_MC_vs_eta);
	eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->Divide(eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_MC);
	eff_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta->Divide(eff_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta_MC);

	//////////////////////////////

        //TPaveText *DoubleEl = new TPaveText(.5,.5,.85,.6,"NDC");
        TPaveText *DoubleEl = new TPaveText(.5,.2,.85,.3,"NDC");
        DoubleEl->AddText("Double Electron Stream");
        DoubleEl->SetTextSize(0.035);
        DoubleEl->SetFillColor(0);
        DoubleEl->SetFillStyle(0);
        DoubleEl->SetBorderSize(0);
        DoubleEl->SetTextAlign(13);
        DoubleEl->SetTextFont(12);
        DoubleEl->SetTextColor(kBlack);

        //TPaveText *ElMu = new TPaveText(.5,.5,.85,.6,"NDC");
        TPaveText *ElMu = new TPaveText(.5,.2,.85,.3,"NDC");
        ElMu->AddText("Electron-Muon Stream");
        ElMu->SetTextSize(0.035);
        ElMu->SetFillColor(0);
        ElMu->SetFillStyle(0);
        ElMu->SetBorderSize(0);
        ElMu->SetTextAlign(13);
        ElMu->SetTextFont(12);
        ElMu->SetTextColor(kBlack);

        //TPaveText *DoubleMu = new TPaveText(.5,.5,.85,.6,"NDC");
        TPaveText *DoubleMu = new TPaveText(.5,.2,.85,.3,"NDC");
        DoubleMu->AddText("Double Muon Stream");
        DoubleMu->SetTextSize(0.035);
        DoubleMu->SetFillColor(0);
        DoubleMu->SetFillStyle(0);
        DoubleMu->SetBorderSize(0);
        DoubleMu->SetTextAlign(13);
        DoubleMu->SetTextFont(12);
        DoubleMu->SetTextColor(kBlack);

	// Double Electron

        TCanvas *c1 = new TCanvas("c1","c1");
        c1->cd();
        eff_DoubleEl_OR_vs_el0_pt_vs_eta->GetZaxis()->SetRangeUser(0.90,1.01);
	c1->SetRightMargin(0.15);
	eff_DoubleEl_OR_vs_el0_pt_vs_eta->SetLabelSize(0.04, "XYZ");
        eff_DoubleEl_OR_vs_el0_pt_vs_eta->Draw("TEXT colz");
	//DoubleEl->Draw("same");
	paveCMS->Draw("same");
	c1->SaveAs("SF_DoubleEl_OR_el0_pt_vs_eta.png");

        TCanvas *c2 = new TCanvas("c2","c2");
        c2->cd();
	//DoubleEl->Draw("same");
        eff_DoubleEl_OR_vs_el1_pt_vs_eta->GetZaxis()->SetRangeUser(0.90,1.01);
	c2->SetRightMargin(0.15);
	eff_DoubleEl_OR_vs_el1_pt_vs_eta->SetLabelSize(0.04, "XYZ");
        eff_DoubleEl_OR_vs_el1_pt_vs_eta->Draw("TEXT colz");
	paveCMS->Draw("same");
	c2->SaveAs("SF_DoubleEl_OR_el1_pt_vs_eta.png");

        TCanvas *c3 = new TCanvas("c3","c3");
        c3->cd();
        eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->GetZaxis()->SetRangeUser(0.90,1.01);
	c3->SetRightMargin(0.15);
	eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->SetLabelSize(0.04, "XYZ");
        eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->Draw("TEXT colz");
	//DoubleEl->Draw("same");
	paveCMS->Draw("same");
	c3->SaveAs("SF_DoubleEl_OR_el0_pt_vs_el1_pt.png");

        TCanvas *c4 = new TCanvas("c4","c4");
        c4->cd();
	//DoubleEl->Draw("same");
        eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta->GetZaxis()->SetRangeUser(0.90,1.01);
	c4->SetRightMargin(0.15);
	eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta->SetLabelSize(0.04, "XYZ");
        eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta->Draw("TEXT colz");
	paveCMS->Draw("same");
	c4->SaveAs("SF_DoubleEl_OR_el0_eta_vs_el1_eta.png");

	// EMu

        TCanvas *cc1 = new TCanvas("cc1","cc1");
        cc1->cd();
        eff_EMu_OR_vs_el0_pt_vs_eta->GetZaxis()->SetRangeUser(0.90,1.01);
	cc1->SetRightMargin(0.15);
	eff_EMu_OR_vs_el0_pt_vs_eta->SetLabelSize(0.04, "XYZ");
        eff_EMu_OR_vs_el0_pt_vs_eta->Draw("TEXT colz");
	//ElMu->Draw("same");
	paveCMS->Draw("same");
	cc1->SaveAs("SF_EMu_OR_el0_pt_vs_eta.png");

        TCanvas *cc2 = new TCanvas("cc2","cc2");
        cc2->cd();
	//ElMu->Draw("same");
        eff_EMu_OR_vs_mu0_pt_vs_eta->GetZaxis()->SetRangeUser(0.90,1.01);
	cc2->SetRightMargin(0.15);
	eff_EMu_OR_vs_mu0_pt_vs_eta->SetLabelSize(0.04, "XYZ");
        eff_EMu_OR_vs_mu0_pt_vs_eta->Draw("TEXT colz");
	paveCMS->Draw("same");
	cc2->SaveAs("SF_EMu_OR_vs_mu0_pt_vs_eta.png");

        TCanvas *cc3 = new TCanvas("cc3","cc3");
        cc3->cd();
        eff_EMu_OR_vs_mu0_eta_vs_el0_eta->GetZaxis()->SetRangeUser(0.90,1.01);
	cc3->SetRightMargin(0.15);
	eff_EMu_OR_vs_mu0_eta_vs_el0_eta->SetLabelSize(0.04, "XYZ");
        eff_EMu_OR_vs_mu0_eta_vs_el0_eta->Draw("TEXT colz");
	//ElMu->Draw("same");
	paveCMS->Draw("same");
	cc3->SaveAs("SF_EMu_OR_vs_mu0_eta_vs_el0_eta.png");

        TCanvas *cc4 = new TCanvas("cc4","cc4");
        cc4->cd();
        eff_EMu_OR_vs_mu0_pt_vs_el0_pt->GetZaxis()->SetRangeUser(0.90,1.01);
	cc4->SetRightMargin(0.15);
	eff_EMu_OR_vs_mu0_pt_vs_el0_pt->SetLabelSize(0.04, "XYZ");
        eff_EMu_OR_vs_mu0_pt_vs_el0_pt->Draw("TEXT colz");
	//ElMu->Draw("same");
	paveCMS->Draw("same");
	cc4->SaveAs("SF_EMu_OR_vs_mu0_pt_vs_el0_pt.png");

	// DoubleMu

        TCanvas *ccc1 = new TCanvas("ccc1","ccc1");
        ccc1->cd();
        eff_DoubleMu_OR_vs_mu1_pt_vs_eta->GetZaxis()->SetRangeUser(0.90,1.01);
	ccc1->SetRightMargin(0.15);
	eff_DoubleMu_OR_vs_mu1_pt_vs_eta->SetLabelSize(0.04, "XYZ");
        eff_DoubleMu_OR_vs_mu1_pt_vs_eta->Draw("TEXT colz");
	//DoubleMu->Draw("same");
	paveCMS->Draw("same");
	ccc1->SaveAs("SF_DoubleMu_OR_mu1_pt_vs_eta.png");

        TCanvas *ccc2 = new TCanvas("ccc2","ccc2");
        ccc2->cd();
        eff_DoubleMu_OR_vs_mu0_pt_vs_eta->GetZaxis()->SetRangeUser(0.90,1.01);
	ccc2->SetRightMargin(0.15);
	eff_DoubleMu_OR_vs_mu0_pt_vs_eta->SetLabelSize(0.04, "XYZ");
        eff_DoubleMu_OR_vs_mu0_pt_vs_eta->Draw("TEXT colz");
	//DoubleMu->Draw("same");
	paveCMS->Draw("same");
	ccc2->SaveAs("SF_DoubleMu_OR_vs_mu0_pt_vs_eta.png");
	
        TCanvas *ccc3 = new TCanvas("ccc3","ccc3");
        ccc3->cd();
        eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->GetZaxis()->SetRangeUser(0.90,1.01);
	ccc3->SetRightMargin(0.15);
	eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->SetLabelSize(0.04, "XYZ");
        eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->Draw("TEXT colz");
	//DoubleMu->Draw("same");
	paveCMS->Draw("same");
	ccc3->SaveAs("SF_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt.png");

        TCanvas *ccc4 = new TCanvas("ccc4","ccc4");
        ccc4->cd();
        eff_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta->GetZaxis()->SetRangeUser(0.90,1.01);
	ccc4->SetRightMargin(0.15);
	eff_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta->SetLabelSize(0.04, "XYZ");
        eff_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta->Draw("TEXT colz");
	//DoubleMu->Draw("same");
	paveCMS->Draw("same");
	ccc4->SaveAs("SF_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta.png");


        f=new TFile("Preliminary_Legacy_triggerSFs_2018.root","RECREATE");

        eff_DoubleEl_OR_vs_el0_pt_vs_eta->SetName("eff_DoubleEl_OR_vs_el0_pt_vs_eta");
        eff_DoubleEl_OR_vs_el0_pt_vs_eta->Write();
        eff_DoubleEl_OR_vs_el1_pt_vs_eta->SetName("eff_DoubleEl_OR_vs_el1_pt_vs_eta");
        eff_DoubleEl_OR_vs_el1_pt_vs_eta->Write();
 	eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->SetName("eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt");
        eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->Write();
        eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta->SetName("eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta");
        eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta->Write();

        eff_EMu_OR_vs_el0_pt_vs_eta->SetName("eff_EMu_OR_vs_el0_pt_vs_eta");
        eff_EMu_OR_vs_el0_pt_vs_eta->Write();
        eff_EMu_OR_vs_mu0_pt_vs_eta->SetName("eff_EMu_OR_vs_mu0_pt_vs_eta");
        eff_EMu_OR_vs_mu0_pt_vs_eta->Write();
        eff_EMu_OR_vs_mu0_eta_vs_el0_eta->SetName("eff_EMu_OR_vs_mu0_eta_vs_el0_eta");
        eff_EMu_OR_vs_mu0_eta_vs_el0_eta->Write();
        eff_EMu_OR_vs_mu0_pt_vs_el0_pt->SetName("eff_EMu_OR_vs_mu0_pt_vs_el0_pt");
        eff_EMu_OR_vs_mu0_pt_vs_el0_pt->Write();

        eff_DoubleMu_OR_vs_mu1_pt_vs_eta->SetName("eff_DoubleMu_OR_vs_mu1_pt_vs_eta");
        eff_DoubleMu_OR_vs_mu1_pt_vs_eta->Write();
        eff_DoubleMu_OR_vs_mu0_pt_vs_eta->SetName("eff_DoubleMu_OR_vs_mu0_pt_vs_eta");
        eff_DoubleMu_OR_vs_mu0_pt_vs_eta->Write();
        eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->SetName("eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt");
        eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->Write();
        eff_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta->SetName("eff_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta");
        eff_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta->Write();



}

