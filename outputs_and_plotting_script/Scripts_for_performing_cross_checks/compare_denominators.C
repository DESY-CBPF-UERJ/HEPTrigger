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
#include "TGraphAsymmErrors.h"
#include </afs/cern.ch/work/c/ckoraka/codes/setTDRStyle_teliko.C>

void compare_denominators()
{

 	gROOT->LoadMacro("/afs/cern.ch/work/c/ckoraka/codes/setTDRStyle_teliko.C");
        setTDRStyle_teliko();

        // CMS box for plotting the canvases    ///////
        TPaveText *paveCMS = new TPaveText(0.18,0.96,0.93,0.99,"NDC");
        paveCMS->AddText("#bf{CMS #it{Preliminary}}              41.5 fb^{-1}    (13 TeV)");
        //paveCMS->AddText("#bf{CMS #it{Preliminary}}              RunD    (13 TeV)");
        paveCMS->SetFillColor(0);
        paveCMS->SetBorderSize(0);
        paveCMS->SetTextSize(0.04);
        paveCMS->SetTextFont(42);


	//////////////////////////////////////////////
	//	DATA		//////////////////////
	//////////////////////////////////////////////

	//TFile *f  = new TFile("plots_11-06-19_All_2017_Data_Charis/data/outfile.root","READ");
	//TFile *f  = new TFile("plots_08-06-19_RunB/data/outfile.root","READ");
	//TFile *f  = new TFile("plots_08-06-19_RunC/data/outfile.root","READ");
	//TFile *f  = new TFile("plots_08-06-19_RunD/data/outfile.root","READ");
	TFile *f  = new TFile("plots_14-06-19_MET_2017_RunC_31March2018/data/outfile.root","READ");
	//TFile *f  = new TFile("plots_14-06-19_MET_2017_RunB_31March2018_update_in_MET_triggers/data/outfile.root","READ");
        f->cd();

	//	Double Electron stream (OR of Single & Double electron triggers)	///////////////

        TH1D* h_HLT_allMET_elStreamDL_el0_pt = (TH1D*) f->Get("h_HLT_allMET_elStreamDL_el0_pt");
        TH1D* h_DoubleEl_OR__X__allMET_el0_pt = (TH1D*) f->Get("h_DoubleEl_OR__X__allMET_el0_pt");
	TH1D *eff_DoubleEl_OR_vs_el0_pt = (TH1D*)h_DoubleEl_OR__X__allMET_el0_pt->Clone();
	//TH1D *eff_DoubleEl_OR_vs_el0_pt = (TH1D*)h_HLT_allMET_elStreamDL_el0_pt->Clone();
	//eff_DoubleEl_OR_vs_el0_pt->Divide(h_HLT_allMET_elStreamDL_el0_pt);

        TH1D* h_HLT_allMET_elStreamDL_el1_pt = (TH1D*) f->Get("h_HLT_allMET_elStreamDL_el1_pt");
        TH1D* h_DoubleEl_OR__X__allMET_el1_pt = (TH1D*) f->Get("h_DoubleEl_OR__X__allMET_el1_pt");
	TH1D *eff_DoubleEl_OR_vs_el1_pt = (TH1D*)h_DoubleEl_OR__X__allMET_el1_pt->Clone();
	//TH1D *eff_DoubleEl_OR_vs_el1_pt = (TH1D*)h_HLT_allMET_elStreamDL_el1_pt->Clone();
	//eff_DoubleEl_OR_vs_el1_pt->Divide(h_HLT_allMET_elStreamDL_el1_pt);

        TH1D* h_HLT_allMET_elStreamDL_el0_eta = (TH1D*) f->Get("h_HLT_allMET_elStreamDL_el0_eta");
        TH1D* h_DoubleEl_OR__X__allMET_el0_eta = (TH1D*) f->Get("h_DoubleEl_OR__X__allMET_el0_eta");
	TH1D *eff_DoubleEl_OR_vs_el0_eta = (TH1D*)h_DoubleEl_OR__X__allMET_el0_eta->Clone();
	//TH1D *eff_DoubleEl_OR_vs_el0_eta = (TH1D*)h_HLT_allMET_elStreamDL_el0_eta->Clone();
	//eff_DoubleEl_OR_vs_el0_eta->Divide(h_HLT_allMET_elStreamDL_el0_eta);

        TH1D* h_HLT_allMET_elStreamDL_el1_eta = (TH1D*) f->Get("h_HLT_allMET_elStreamDL_el1_eta");
        TH1D* h_DoubleEl_OR__X__allMET_el1_eta = (TH1D*) f->Get("h_DoubleEl_OR__X__allMET_el1_eta");
	TH1D *eff_DoubleEl_OR_vs_el1_eta = (TH1D*)h_DoubleEl_OR__X__allMET_el1_eta->Clone();
	//TH1D *eff_DoubleEl_OR_vs_el1_eta = (TH1D*)h_HLT_allMET_elStreamDL_el1_eta->Clone();
	//eff_DoubleEl_OR_vs_el1_eta->Divide(h_HLT_allMET_elStreamDL_el1_eta);

        TH1D* h_HLT_allMET_elStreamDL_nPV = (TH1D*) f->Get("h_HLT_allMET_elStreamDL_nPV");
        TH1D* h_DoubleEl_OR__X__allMET_nPV = (TH1D*) f->Get("h_DoubleEl_OR__X__allMET_nPV");
	TH1D *eff_DoubleEl_OR_vs_nPV = (TH1D*)h_DoubleEl_OR__X__allMET_nPV->Clone();
	//TH1D *eff_DoubleEl_OR_vs_nPV = (TH1D*)h_HLT_allMET_elStreamDL_nPV->Clone();
	//eff_DoubleEl_OR_vs_nPV->Divide(h_HLT_allMET_elStreamDL_nPV);

        TH1D* h_HLT_allMET_elStreamDL_met = (TH1D*) f->Get("h_HLT_allMET_elStreamDL_met");
        TH1D* h_DoubleEl_OR__X__allMET_met = (TH1D*) f->Get("h_DoubleEl_OR__X__allMET_met");
	TH1D *eff_DoubleEl_OR_vs_met = (TH1D*)h_DoubleEl_OR__X__allMET_met->Clone();
	//TH1D *eff_DoubleEl_OR_vs_met = (TH1D*)h_HLT_allMET_elStreamDL_met->Clone();
	//eff_DoubleEl_OR_vs_met->Divide(h_HLT_allMET_elStreamDL_met);

        TH1D* h_HLT_allMET_elStreamDL_njets = (TH1D*) f->Get("h_HLT_allMET_elStreamDL_njets");
        TH1D* h_DoubleEl_OR__X__allMET_njets = (TH1D*) f->Get("h_DoubleEl_OR__X__allMET_njets");
	TH1D *eff_DoubleEl_OR_vs_njets = (TH1D*)h_DoubleEl_OR__X__allMET_njets->Clone();
	//TH1D *eff_DoubleEl_OR_vs_njets = (TH1D*)h_HLT_allMET_elStreamDL_njets->Clone();
	//eff_DoubleEl_OR_vs_njets->Divide(h_HLT_allMET_elStreamDL_njets);


	//	EMu stream (OR of Single & Double electron triggers)	///////////////

        TH1D* h_HLT_allMET_emuStreamDL_el0_pt = (TH1D*) f->Get("h_HLT_allMET_emuStreamDL_el0_pt");
        TH1D* h_EMu_OR__X__allMET_el0_pt = (TH1D*) f->Get("h_EMu_OR__X__allMET_el0_pt");
	TH1D *eff_EMu_OR_vs_el0_pt = (TH1D*)h_EMu_OR__X__allMET_el0_pt->Clone();
	//TH1D *eff_EMu_OR_vs_el0_pt = (TH1D*)h_HLT_allMET_emuStreamDL_el0_pt->Clone();
	//eff_EMu_OR_vs_el0_pt->Divide(h_HLT_allMET_emuStreamDL_el0_pt);

        TH1D* h_HLT_allMET_emuStreamDL_mu0_pt = (TH1D*) f->Get("h_HLT_allMET_emuStreamDL_mu0_pt");
        TH1D* h_EMu_OR__X__allMET_mu0_pt = (TH1D*) f->Get("h_EMu_OR__X__allMET_mu0_pt");
	TH1D *eff_EMu_OR_vs_mu0_pt = (TH1D*)h_EMu_OR__X__allMET_mu0_pt->Clone();
	//TH1D *eff_EMu_OR_vs_mu0_pt = (TH1D*)h_HLT_allMET_emuStreamDL_mu0_pt->Clone();
	//eff_EMu_OR_vs_mu0_pt->Divide(h_HLT_allMET_emuStreamDL_mu0_pt);

        TH1D* h_HLT_allMET_emuStreamDL_el0_eta = (TH1D*) f->Get("h_HLT_allMET_emuStreamDL_el0_eta");
        TH1D* h_EMu_OR__X__allMET_el0_eta = (TH1D*) f->Get("h_EMu_OR__X__allMET_el0_eta");
	TH1D *eff_EMu_OR_vs_el0_eta = (TH1D*)h_EMu_OR__X__allMET_el0_eta->Clone();
	//TH1D *eff_EMu_OR_vs_el0_eta = (TH1D*)h_HLT_allMET_emuStreamDL_el0_eta->Clone();
	//eff_EMu_OR_vs_el0_eta->Divide(h_HLT_allMET_emuStreamDL_el0_eta);

        TH1D* h_HLT_allMET_emuStreamDL_mu0_eta = (TH1D*) f->Get("h_HLT_allMET_emuStreamDL_mu0_eta");
        TH1D* h_EMu_OR__X__allMET_mu0_eta = (TH1D*) f->Get("h_EMu_OR__X__allMET_mu0_eta");
	TH1D *eff_EMu_OR_vs_mu0_eta = (TH1D*)h_EMu_OR__X__allMET_mu0_eta->Clone();
	//TH1D *eff_EMu_OR_vs_mu0_eta = (TH1D*)h_HLT_allMET_emuStreamDL_mu0_eta->Clone();
	//eff_EMu_OR_vs_mu0_eta->Divide(h_HLT_allMET_emuStreamDL_mu0_eta);

        TH1D* h_HLT_allMET_emuStreamDL_nPV = (TH1D*) f->Get("h_HLT_allMET_emuStreamDL_nPV");
        TH1D* h_EMu_OR__X__allMET_nPV = (TH1D*) f->Get("h_EMu_OR__X__allMET_nPV");
	TH1D *eff_EMu_OR_vs_nPV = (TH1D*)h_EMu_OR__X__allMET_nPV->Clone();
	//TH1D *eff_EMu_OR_vs_nPV = (TH1D*)h_HLT_allMET_emuStreamDL_nPV->Clone();
	//eff_EMu_OR_vs_nPV->Divide(h_HLT_allMET_emuStreamDL_nPV);

        TH1D* h_HLT_allMET_emuStreamDL_met = (TH1D*) f->Get("h_HLT_allMET_emuStreamDL_met");
        TH1D* h_EMu_OR__X__allMET_met = (TH1D*) f->Get("h_EMu_OR__X__allMET_met");
	TH1D *eff_EMu_OR_vs_met = (TH1D*)h_EMu_OR__X__allMET_met->Clone();
	//TH1D *eff_EMu_OR_vs_met = (TH1D*)h_HLT_allMET_emuStreamDL_met->Clone();
	//eff_EMu_OR_vs_met->Divide(h_HLT_allMET_emuStreamDL_met);

        TH1D* h_HLT_allMET_emuStreamDL_njets = (TH1D*) f->Get("h_HLT_allMET_emuStreamDL_njets");
        TH1D* h_EMu_OR__X__allMET_njets = (TH1D*) f->Get("h_EMu_OR__X__allMET_njets");
	TH1D *eff_EMu_OR_vs_njets = (TH1D*)h_EMu_OR__X__allMET_njets->Clone();
	//TH1D *eff_EMu_OR_vs_njets = (TH1D*)h_HLT_allMET_emuStreamDL_njets->Clone();
	//eff_EMu_OR_vs_njets->Divide(h_HLT_allMET_emuStreamDL_njets);

	//	Double Muon stream (OR of Single & Double electron triggers)	///////////////

        TH1D* h_HLT_allMET_muStreamDL_mu1_pt = (TH1D*) f->Get("h_HLT_allMET_muStreamDL_mu1_pt");
        TH1D* h_DoubleMu_OR__X__allMET_mu1_pt = (TH1D*) f->Get("h_DoubleMu_OR__X__allMET_mu1_pt");
	TH1D *eff_DoubleMu_OR_vs_mu1_pt = (TH1D*)h_DoubleMu_OR__X__allMET_mu1_pt->Clone();
	//TH1D *eff_DoubleMu_OR_vs_mu1_pt = (TH1D*)h_HLT_allMET_muStreamDL_mu1_pt->Clone();
	//eff_DoubleMu_OR_vs_mu1_pt->Divide(h_HLT_allMET_muStreamDL_mu1_pt);

        TH1D* h_HLT_allMET_muStreamDL_mu0_pt = (TH1D*) f->Get("h_HLT_allMET_muStreamDL_mu0_pt");
        TH1D* h_DoubleMu_OR__X__allMET_mu0_pt = (TH1D*) f->Get("h_DoubleMu_OR__X__allMET_mu0_pt");
	TH1D *eff_DoubleMu_OR_vs_mu0_pt = (TH1D*)h_DoubleMu_OR__X__allMET_mu0_pt->Clone();
	//TH1D *eff_DoubleMu_OR_vs_mu0_pt = (TH1D*)h_HLT_allMET_muStreamDL_mu0_pt->Clone();
	//eff_DoubleMu_OR_vs_mu0_pt->Divide(h_HLT_allMET_muStreamDL_mu0_pt);

        TH1D* h_HLT_allMET_muStreamDL_mu1_eta = (TH1D*) f->Get("h_HLT_allMET_muStreamDL_mu1_eta");
        TH1D* h_DoubleMu_OR__X__allMET_mu1_eta = (TH1D*) f->Get("h_DoubleMu_OR__X__allMET_mu1_eta");
	TH1D *eff_DoubleMu_OR_vs_mu1_eta = (TH1D*)h_DoubleMu_OR__X__allMET_mu1_eta->Clone();
	//TH1D *eff_DoubleMu_OR_vs_mu1_eta = (TH1D*)h_HLT_allMET_muStreamDL_mu1_eta->Clone();
	//eff_DoubleMu_OR_vs_mu1_eta->Divide(h_HLT_allMET_muStreamDL_mu1_eta);

        TH1D* h_HLT_allMET_muStreamDL_mu0_eta = (TH1D*) f->Get("h_HLT_allMET_muStreamDL_mu0_eta");
        TH1D* h_DoubleMu_OR__X__allMET_mu0_eta = (TH1D*) f->Get("h_DoubleMu_OR__X__allMET_mu0_eta");
	TH1D *eff_DoubleMu_OR_vs_mu0_eta = (TH1D*)h_DoubleMu_OR__X__allMET_mu0_eta->Clone();
	//TH1D *eff_DoubleMu_OR_vs_mu0_eta = (TH1D*)h_HLT_allMET_muStreamDL_mu0_eta->Clone();
	//eff_DoubleMu_OR_vs_mu0_eta->Divide(h_HLT_allMET_muStreamDL_mu0_eta);

        TH1D* h_HLT_allMET_muStreamDL_nPV = (TH1D*) f->Get("h_HLT_allMET_muStreamDL_nPV");
        TH1D* h_DoubleMu_OR__X__allMET_nPV = (TH1D*) f->Get("h_DoubleMu_OR__X__allMET_nPV");
	TH1D *eff_DoubleMu_OR_vs_nPV = (TH1D*)h_DoubleMu_OR__X__allMET_nPV->Clone();
	//TH1D *eff_DoubleMu_OR_vs_nPV = (TH1D*)h_HLT_allMET_muStreamDL_nPV->Clone();
	//eff_DoubleMu_OR_vs_nPV->Divide(h_HLT_allMET_muStreamDL_nPV);

        TH1D* h_HLT_allMET_muStreamDL_met = (TH1D*) f->Get("h_HLT_allMET_muStreamDL_met");
        TH1D* h_DoubleMu_OR__X__allMET_met = (TH1D*) f->Get("h_DoubleMu_OR__X__allMET_met");
	TH1D *eff_DoubleMu_OR_vs_met = (TH1D*)h_DoubleMu_OR__X__allMET_met->Clone();
	//TH1D *eff_DoubleMu_OR_vs_met = (TH1D*)h_HLT_allMET_muStreamDL_met->Clone();
	//eff_DoubleMu_OR_vs_met->Divide(h_HLT_allMET_muStreamDL_met);

        TH1D* h_HLT_allMET_muStreamDL_njets = (TH1D*) f->Get("h_HLT_allMET_muStreamDL_njets");
        TH1D* h_DoubleMu_OR__X__allMET_njets = (TH1D*) f->Get("h_DoubleMu_OR__X__allMET_njets");
	TH1D *eff_DoubleMu_OR_vs_njets = (TH1D*)h_DoubleMu_OR__X__allMET_njets->Clone();
	//TH1D *eff_DoubleMu_OR_vs_njets = (TH1D*)h_HLT_allMET_muStreamDL_njets->Clone();
	//eff_DoubleMu_OR_vs_njets->Divide(h_HLT_allMET_muStreamDL_njets);

	///////////////////

	//////////////////////////////////////////////
	//	MC		//////////////////////
	//////////////////////////////////////////////

        //TFile *f_MC  = new TFile("TT_Dileptonic_MC_Ben.root","READ");
        //TFile *f_MC  = new TFile("plots_08-06-19_RubB_bens_files/data/outfile.root","READ");
        TFile *f_MC  = new TFile("Run2017C_BenNtuples.root","READ");
	//TFile *f_MC  = new TFile("plots_08-06-19_Bens_inputs_RunD/data/outfile.root","READ");
	//TFile *f_MC  = new TFile("plots_14-06-19_MET_2017_RunC_31March2018/data/outfile.root","READ");
	//TFile *f_MC  = new TFile("plots_14-06-19_MET_2017_RunB_31March2018/data/outfile.root","READ");
	//TFile *f_MC  = new TFile("plots_15-06-19_MET_2017_RunB_BEN_update_in_MET_triggers/data/outfile.root","READ");


      	f_MC->cd();

	//	Double Electron stream (OR of Single & Double electron triggers)	//////////////
    
        TH1D* h_HLT_allMET_elStreamDL_el0_pt_MC = (TH1D*) f_MC->Get("h_HLT_allMET_elStreamDL_el0_pt");
        TH1D* h_DoubleEl_OR__X__allMET_el0_pt_MC = (TH1D*) f_MC->Get("h_DoubleEl_OR__X__allMET_el0_pt");
        TH1D *eff_DoubleEl_OR_vs_el0_pt_MC = (TH1D*)h_DoubleEl_OR__X__allMET_el0_pt_MC->Clone();
        //TH1D *eff_DoubleEl_OR_vs_el0_pt_MC = (TH1D*)h_HLT_allMET_elStreamDL_el0_pt_MC->Clone();
        //eff_DoubleEl_OR_vs_el0_pt_MC->Divide(h_HLT_allMET_elStreamDL_el0_pt_MC);

        TH1D* h_HLT_allMET_elStreamDL_el1_pt_MC = (TH1D*) f_MC->Get("h_HLT_allMET_elStreamDL_el1_pt");
        TH1D* h_DoubleEl_OR__X__allMET_el1_pt_MC = (TH1D*) f_MC->Get("h_DoubleEl_OR__X__allMET_el1_pt");
        TH1D *eff_DoubleEl_OR_vs_el1_pt_MC = (TH1D*)h_DoubleEl_OR__X__allMET_el1_pt_MC->Clone();
        //TH1D *eff_DoubleEl_OR_vs_el1_pt_MC = (TH1D*)h_HLT_allMET_elStreamDL_el1_pt_MC->Clone();
        //eff_DoubleEl_OR_vs_el1_pt_MC->Divide(h_HLT_allMET_elStreamDL_el1_pt_MC);

        TH1D* h_HLT_allMET_elStreamDL_el0_eta_MC = (TH1D*) f_MC->Get("h_HLT_allMET_elStreamDL_el0_eta");
        TH1D* h_DoubleEl_OR__X__allMET_el0_eta_MC = (TH1D*) f_MC->Get("h_DoubleEl_OR__X__allMET_el0_eta");
        TH1D *eff_DoubleEl_OR_vs_el0_eta_MC = (TH1D*)h_DoubleEl_OR__X__allMET_el0_eta_MC->Clone();
        //TH1D *eff_DoubleEl_OR_vs_el0_eta_MC = (TH1D*)h_HLT_allMET_elStreamDL_el0_eta_MC->Clone();
        //eff_DoubleEl_OR_vs_el0_eta_MC->Divide(h_HLT_allMET_elStreamDL_el0_eta_MC);

        TH1D* h_HLT_allMET_elStreamDL_el1_eta_MC = (TH1D*) f_MC->Get("h_HLT_allMET_elStreamDL_el1_eta");
        TH1D* h_DoubleEl_OR__X__allMET_el1_eta_MC = (TH1D*) f_MC->Get("h_DoubleEl_OR__X__allMET_el1_eta");
        TH1D *eff_DoubleEl_OR_vs_el1_eta_MC = (TH1D*)h_DoubleEl_OR__X__allMET_el1_eta_MC->Clone();
        //TH1D *eff_DoubleEl_OR_vs_el1_eta_MC = (TH1D*)h_HLT_allMET_elStreamDL_el1_eta_MC->Clone();
        //eff_DoubleEl_OR_vs_el1_eta_MC->Divide(h_HLT_allMET_elStreamDL_el1_eta_MC);

        TH1D* h_HLT_allMET_elStreamDL_nPV_MC = (TH1D*) f_MC->Get("h_HLT_allMET_elStreamDL_nPV");
        TH1D* h_DoubleEl_OR__X__allMET_nPV_MC = (TH1D*) f_MC->Get("h_DoubleEl_OR__X__allMET_nPV");
        TH1D *eff_DoubleEl_OR_vs_nPV_MC = (TH1D*)h_DoubleEl_OR__X__allMET_nPV_MC->Clone();
        //TH1D *eff_DoubleEl_OR_vs_nPV_MC = (TH1D*)h_HLT_allMET_elStreamDL_nPV_MC->Clone();
        //eff_DoubleEl_OR_vs_nPV_MC->Divide(h_HLT_allMET_elStreamDL_nPV_MC);

        TH1D* h_HLT_allMET_elStreamDL_met_MC = (TH1D*) f_MC->Get("h_HLT_allMET_elStreamDL_met");
        TH1D* h_DoubleEl_OR__X__allMET_met_MC = (TH1D*) f_MC->Get("h_DoubleEl_OR__X__allMET_met");
        TH1D *eff_DoubleEl_OR_vs_met_MC = (TH1D*)h_DoubleEl_OR__X__allMET_met_MC->Clone();
        //TH1D *eff_DoubleEl_OR_vs_met_MC = (TH1D*)h_HLT_allMET_elStreamDL_met_MC->Clone();
        //eff_DoubleEl_OR_vs_met_MC->Divide(h_HLT_allMET_elStreamDL_met_MC);

        TH1D* h_HLT_allMET_elStreamDL_njets_MC = (TH1D*) f_MC->Get("h_HLT_allMET_elStreamDL_njets");
        TH1D* h_DoubleEl_OR__X__allMET_njets_MC = (TH1D*) f_MC->Get("h_DoubleEl_OR__X__allMET_njets");
        TH1D *eff_DoubleEl_OR_vs_njets_MC = (TH1D*)h_DoubleEl_OR__X__allMET_njets_MC->Clone();
        //TH1D *eff_DoubleEl_OR_vs_njets_MC = (TH1D*)h_HLT_allMET_elStreamDL_njets_MC->Clone();
        //eff_DoubleEl_OR_vs_njets_MC->Divide(h_HLT_allMET_elStreamDL_njets_MC);

	//	EMu stream (OR of Single & Double electron triggers)	//////////////

        TH1D* h_HLT_allMET_emuStreamDL_el0_pt_MC = (TH1D*) f_MC->Get("h_HLT_allMET_emuStreamDL_el0_pt");
        TH1D* h_EMu_OR__X__allMET_el0_pt_MC = (TH1D*) f_MC->Get("h_EMu_OR__X__allMET_el0_pt");
        TH1D *eff_EMu_OR_vs_el0_pt_MC = (TH1D*)h_EMu_OR__X__allMET_el0_pt_MC->Clone();
        //TH1D *eff_EMu_OR_vs_el0_pt_MC = (TH1D*)h_HLT_allMET_emuStreamDL_el0_pt_MC->Clone();
        //eff_EMu_OR_vs_el0_pt_MC->Divide(h_HLT_allMET_emuStreamDL_el0_pt_MC);

        TH1D* h_HLT_allMET_emuStreamDL_mu0_pt_MC = (TH1D*) f_MC->Get("h_HLT_allMET_emuStreamDL_mu0_pt");
        TH1D* h_EMu_OR__X__allMET_mu0_pt_MC = (TH1D*) f_MC->Get("h_EMu_OR__X__allMET_mu0_pt");
        TH1D *eff_EMu_OR_vs_mu0_pt_MC = (TH1D*)h_EMu_OR__X__allMET_mu0_pt_MC->Clone();
        //TH1D *eff_EMu_OR_vs_mu0_pt_MC = (TH1D*)h_HLT_allMET_emuStreamDL_mu0_pt_MC->Clone();
        //eff_EMu_OR_vs_mu0_pt_MC->Divide(h_HLT_allMET_emuStreamDL_mu0_pt_MC);

        TH1D* h_HLT_allMET_emuStreamDL_el0_eta_MC = (TH1D*) f_MC->Get("h_HLT_allMET_emuStreamDL_el0_eta");
        TH1D* h_EMu_OR__X__allMET_el0_eta_MC = (TH1D*) f_MC->Get("h_EMu_OR__X__allMET_el0_eta");
        TH1D *eff_EMu_OR_vs_el0_eta_MC = (TH1D*)h_EMu_OR__X__allMET_el0_eta_MC->Clone();
        //TH1D *eff_EMu_OR_vs_el0_eta_MC = (TH1D*)h_HLT_allMET_emuStreamDL_el0_eta_MC->Clone();
        //eff_EMu_OR_vs_el0_eta_MC->Divide(h_HLT_allMET_emuStreamDL_el0_eta_MC);

        TH1D* h_HLT_allMET_emuStreamDL_mu0_eta_MC = (TH1D*) f_MC->Get("h_HLT_allMET_emuStreamDL_mu0_eta");
        TH1D* h_EMu_OR__X__allMET_mu0_eta_MC = (TH1D*) f_MC->Get("h_EMu_OR__X__allMET_mu0_eta");
        TH1D *eff_EMu_OR_vs_mu0_eta_MC = (TH1D*)h_EMu_OR__X__allMET_mu0_eta_MC->Clone();
        //TH1D *eff_EMu_OR_vs_mu0_eta_MC = (TH1D*)h_HLT_allMET_emuStreamDL_mu0_eta_MC->Clone();
        //eff_EMu_OR_vs_mu0_eta_MC->Divide(h_HLT_allMET_emuStreamDL_mu0_eta_MC);

        TH1D* h_HLT_allMET_emuStreamDL_nPV_MC = (TH1D*) f_MC->Get("h_HLT_allMET_emuStreamDL_nPV");
        TH1D* h_EMu_OR__X__allMET_nPV_MC = (TH1D*) f_MC->Get("h_EMu_OR__X__allMET_nPV");
        TH1D *eff_EMu_OR_vs_nPV_MC = (TH1D*)h_EMu_OR__X__allMET_nPV_MC->Clone();
        //TH1D *eff_EMu_OR_vs_nPV_MC = (TH1D*)h_HLT_allMET_emuStreamDL_nPV_MC->Clone();
        //eff_EMu_OR_vs_nPV_MC->Divide(h_HLT_allMET_emuStreamDL_nPV_MC);

        TH1D* h_HLT_allMET_emuStreamDL_met_MC = (TH1D*) f_MC->Get("h_HLT_allMET_emuStreamDL_met");
        TH1D* h_EMu_OR__X__allMET_met_MC = (TH1D*) f_MC->Get("h_EMu_OR__X__allMET_met");
        TH1D *eff_EMu_OR_vs_met_MC = (TH1D*)h_EMu_OR__X__allMET_met_MC->Clone();
        //TH1D *eff_EMu_OR_vs_met_MC = (TH1D*)h_HLT_allMET_emuStreamDL_met_MC->Clone();
        //eff_EMu_OR_vs_met_MC->Divide(h_HLT_allMET_emuStreamDL_met_MC);

        TH1D* h_HLT_allMET_emuStreamDL_njets_MC = (TH1D*) f_MC->Get("h_HLT_allMET_emuStreamDL_njets");
        TH1D* h_EMu_OR__X__allMET_njets_MC = (TH1D*) f_MC->Get("h_EMu_OR__X__allMET_njets");
        TH1D *eff_EMu_OR_vs_njets_MC = (TH1D*)h_EMu_OR__X__allMET_njets_MC->Clone();
        //TH1D *eff_EMu_OR_vs_njets_MC = (TH1D*)h_HLT_allMET_emuStreamDL_njets_MC->Clone();
        //eff_EMu_OR_vs_njets_MC->Divide(h_HLT_allMET_emuStreamDL_njets_MC);

	//	Double Muon stream (OR of Single & Double electron triggers)	//////////////

        TH1D* h_HLT_allMET_muStreamDL_mu1_pt_MC = (TH1D*) f_MC->Get("h_HLT_allMET_muStreamDL_mu1_pt");
        TH1D* h_DoubleMu_OR__X__allMET_mu1_pt_MC = (TH1D*) f_MC->Get("h_DoubleMu_OR__X__allMET_mu1_pt");
        TH1D *eff_DoubleMu_OR_vs_mu1_pt_MC = (TH1D*)h_DoubleMu_OR__X__allMET_mu1_pt_MC->Clone();
        //TH1D *eff_DoubleMu_OR_vs_mu1_pt_MC = (TH1D*)h_HLT_allMET_muStreamDL_mu1_pt_MC->Clone();
        //eff_DoubleMu_OR_vs_mu1_pt_MC->Divide(h_HLT_allMET_muStreamDL_mu1_pt_MC);

        TH1D* h_HLT_allMET_muStreamDL_mu0_pt_MC = (TH1D*) f_MC->Get("h_HLT_allMET_muStreamDL_mu0_pt");
        TH1D* h_DoubleMu_OR__X__allMET_mu0_pt_MC = (TH1D*) f_MC->Get("h_DoubleMu_OR__X__allMET_mu0_pt");
        TH1D *eff_DoubleMu_OR_vs_mu0_pt_MC = (TH1D*)h_DoubleMu_OR__X__allMET_mu0_pt_MC->Clone();
        //TH1D *eff_DoubleMu_OR_vs_mu0_pt_MC = (TH1D*)h_HLT_allMET_muStreamDL_mu0_pt_MC->Clone();
        //eff_DoubleMu_OR_vs_mu0_pt_MC->Divide(h_HLT_allMET_muStreamDL_mu0_pt_MC);

        TH1D* h_HLT_allMET_muStreamDL_mu1_eta_MC = (TH1D*) f_MC->Get("h_HLT_allMET_muStreamDL_mu1_eta");
        TH1D* h_DoubleMu_OR__X__allMET_mu1_eta_MC = (TH1D*) f_MC->Get("h_DoubleMu_OR__X__allMET_mu1_eta");
        TH1D *eff_DoubleMu_OR_vs_mu1_eta_MC = (TH1D*)h_DoubleMu_OR__X__allMET_mu1_eta_MC->Clone();
        //TH1D *eff_DoubleMu_OR_vs_mu1_eta_MC = (TH1D*)h_HLT_allMET_muStreamDL_mu1_eta_MC->Clone();
        //eff_DoubleMu_OR_vs_mu1_eta_MC->Divide(h_HLT_allMET_muStreamDL_mu1_eta_MC);

        TH1D* h_HLT_allMET_muStreamDL_mu0_eta_MC = (TH1D*) f_MC->Get("h_HLT_allMET_muStreamDL_mu0_eta");
        TH1D* h_DoubleMu_OR__X__allMET_mu0_eta_MC = (TH1D*) f_MC->Get("h_DoubleMu_OR__X__allMET_mu0_eta");
        TH1D *eff_DoubleMu_OR_vs_mu0_eta_MC = (TH1D*)h_DoubleMu_OR__X__allMET_mu0_eta_MC->Clone();
        //TH1D *eff_DoubleMu_OR_vs_mu0_eta_MC = (TH1D*)h_HLT_allMET_muStreamDL_mu0_eta_MC->Clone();
        //eff_DoubleMu_OR_vs_mu0_eta_MC->Divide(h_HLT_allMET_muStreamDL_mu0_eta_MC);

        TH1D* h_HLT_allMET_muStreamDL_nPV_MC = (TH1D*) f_MC->Get("h_HLT_allMET_muStreamDL_nPV");
        TH1D* h_DoubleMu_OR__X__allMET_nPV_MC = (TH1D*) f_MC->Get("h_DoubleMu_OR__X__allMET_nPV");
        TH1D *eff_DoubleMu_OR_vs_nPV_MC = (TH1D*)h_DoubleMu_OR__X__allMET_nPV_MC->Clone();
        //TH1D *eff_DoubleMu_OR_vs_nPV_MC = (TH1D*)h_HLT_allMET_muStreamDL_nPV_MC->Clone();
        //eff_DoubleMu_OR_vs_nPV_MC->Divide(h_HLT_allMET_muStreamDL_nPV_MC);

        TH1D* h_HLT_allMET_muStreamDL_met_MC = (TH1D*) f_MC->Get("h_HLT_allMET_muStreamDL_met");
        TH1D* h_DoubleMu_OR__X__allMET_met_MC = (TH1D*) f_MC->Get("h_DoubleMu_OR__X__allMET_met");
        TH1D *eff_DoubleMu_OR_vs_met_MC = (TH1D*)h_DoubleMu_OR__X__allMET_met_MC->Clone();
        //TH1D *eff_DoubleMu_OR_vs_met_MC = (TH1D*)h_HLT_allMET_muStreamDL_met_MC->Clone();
        //eff_DoubleMu_OR_vs_met_MC->Divide(h_HLT_allMET_muStreamDL_met_MC);

        TH1D* h_HLT_allMET_muStreamDL_njets_MC = (TH1D*) f_MC->Get("h_HLT_allMET_muStreamDL_njets");
        TH1D* h_DoubleMu_OR__X__allMET_njets_MC = (TH1D*) f_MC->Get("h_DoubleMu_OR__X__allMET_njets");
        TH1D *eff_DoubleMu_OR_vs_njets_MC = (TH1D*)h_DoubleMu_OR__X__allMET_njets_MC->Clone(); 
        //TH1D *eff_DoubleMu_OR_vs_njets_MC = (TH1D*)h_HLT_allMET_muStreamDL_njets_MC->Clone();
        //eff_DoubleMu_OR_vs_njets_MC->Divide(h_HLT_allMET_muStreamDL_njets_MC);

        ///////////////////
	cout<<"DoubleEl : "<<endl;
	cout<<"Denominator integral = "<<h_HLT_allMET_elStreamDL_el0_pt->Integral()<<endl;
	cout<<"Numerator integral = "<<h_DoubleEl_OR__X__allMET_el0_pt->Integral()<<endl;
	cout<<"MC Denominator integral = "<<h_HLT_allMET_elStreamDL_el0_pt_MC->Integral()<<endl;
	cout<<"MC Numerator integral = "<<h_DoubleEl_OR__X__allMET_el0_pt_MC->Integral()<<endl;
	cout<<"Efficiency Data = "<< h_DoubleEl_OR__X__allMET_el0_pt->Integral() / h_HLT_allMET_elStreamDL_el0_pt->Integral()<<endl;
	cout<<"Efficiency MC = "<< h_DoubleEl_OR__X__allMET_el0_pt_MC->Integral() / h_HLT_allMET_elStreamDL_el0_pt_MC->Integral()<<endl;
        /////////////////////////////////////////////////////

        ///////////////////
	cout<<"EMu : "<<endl;
	cout<<"Denominator integral = "<<h_HLT_allMET_emuStreamDL_el0_pt->Integral()<<endl;
	cout<<"Numerator integral = "<<h_EMu_OR__X__allMET_el0_pt->Integral()<<endl;
	cout<<"MC Denominator integral = "<<h_HLT_allMET_emuStreamDL_el0_pt_MC->Integral()<<endl;
	cout<<"MC Numerator integral = "<<h_EMu_OR__X__allMET_el0_pt_MC->Integral()<<endl;
	cout<<"Efficiency Data = "<< h_EMu_OR__X__allMET_el0_pt->Integral() / h_HLT_allMET_emuStreamDL_el0_pt->Integral()<<endl;
	cout<<"Efficiency MC = "<< h_EMu_OR__X__allMET_el0_pt_MC->Integral() / h_HLT_allMET_emuStreamDL_el0_pt_MC->Integral()<<endl;
        /////////////////////////////////////////////////////

        ///////////////////
	cout<<"DoubleMu : "<<endl;
	cout<<"Denominator integral = "<<h_HLT_allMET_muStreamDL_mu0_pt->Integral()<<endl;
	cout<<"Numerator integral = "<<h_DoubleMu_OR__X__allMET_mu0_pt->Integral()<<endl;
	cout<<"MC Denominator integral = "<<h_HLT_allMET_muStreamDL_mu0_pt_MC->Integral()<<endl;
	cout<<"MC Numerator integral = "<<h_DoubleMu_OR__X__allMET_mu0_pt_MC->Integral()<<endl;
	cout<<"Efficiency Data = "<< h_DoubleMu_OR__X__allMET_mu0_pt->Integral() / h_HLT_allMET_muStreamDL_mu0_pt->Integral()<<endl;
	cout<<"Efficiency MC = "<< h_DoubleMu_OR__X__allMET_mu0_pt_MC->Integral() / h_HLT_allMET_muStreamDL_mu0_pt_MC->Integral()<<endl;
        /////////////////////////////////////////////////////


        TPaveText *DoubleEl = new TPaveText(.5,.5,.7,.6,"NDC");
        //TPaveText *DoubleEl = new TPaveText(.5,.2,.85,.3,"NDC");
        DoubleEl->AddText("Double Electron Stream");
        DoubleEl->SetTextSize(0.022); //0.035
        DoubleEl->SetFillColor(0);
        DoubleEl->SetFillStyle(0);
        DoubleEl->SetBorderSize(0);
        DoubleEl->SetTextAlign(13);
        DoubleEl->SetTextFont(12);
        DoubleEl->SetTextColor(kBlack);

        TPaveText *ElMu = new TPaveText(.5,.5,.7,.6,"NDC");
        //TPaveText *ElMu = new TPaveText(.5,.2,.85,.3,"NDC");
        ElMu->AddText("Electron-Muon Stream");
        ElMu->SetTextSize(0.022);
        ElMu->SetFillColor(0);
        ElMu->SetFillStyle(0);
        ElMu->SetBorderSize(0);
        ElMu->SetTextAlign(13);
        ElMu->SetTextFont(12);
        ElMu->SetTextColor(kBlack);

        TPaveText *DoubleMu = new TPaveText(.5,.5,.7,.6,"NDC");
        //TPaveText *DoubleMu = new TPaveText(.5,.2,.85,.3,"NDC");
        DoubleMu->AddText("Double Muon Stream");
        DoubleMu->SetTextSize(0.022);
        DoubleMu->SetFillColor(0);
        DoubleMu->SetFillStyle(0);
        DoubleMu->SetBorderSize(0);
        DoubleMu->SetTextAlign(13);
        DoubleMu->SetTextFont(12);
        DoubleMu->SetTextColor(kBlack);

        TLegend *l = new TLegend(.5, .6, .7, .75);
        //TLegend *l = new TLegend(.5, .3, .8, .45);
        //l->AddEntry(eff_DoubleEl_OR_vs_el0_pt,"Data","lp");
        //l->AddEntry(eff_DoubleEl_OR_vs_el0_pt_MC,"MC ","lp");
        l->AddEntry(eff_DoubleEl_OR_vs_el0_pt,"My Ntuples - 31March2018","lp");
        l->AddEntry(eff_DoubleEl_OR_vs_el0_pt_MC,"Bens Ntuples","lp");
        l->SetTextSize(0.022);//0.03

	// Double Electron

        TCanvas *c1 = new TCanvas("c1","c1");
        c1->cd();
	c1->SetGrid();
        //eff_DoubleEl_OR_vs_el0_pt_MC->GetYaxis()->SetRangeUser(0.,1.05);
        //eff_DoubleEl_OR_vs_el0_pt->GetYaxis()->SetRangeUser(0.,1.05);
        eff_DoubleEl_OR_vs_el0_pt_MC->SetMarkerColor(kRed);
        eff_DoubleEl_OR_vs_el0_pt_MC->SetLineColor(kRed);
        eff_DoubleEl_OR_vs_el0_pt_MC->Draw("HIST");
        eff_DoubleEl_OR_vs_el0_pt->Draw("HIST same");
	DoubleEl->Draw("same");
	l->Draw("same");
	paveCMS->Draw("same");
	c1->SaveAs("eff_DoubleEl_OR_vs_el0_pt.png");

        TCanvas *c2 = new TCanvas("c2","c2");
        c2->cd();
	c2->SetGrid();
        //eff_DoubleEl_OR_vs_el1_pt_MC->GetYaxis()->SetRangeUser(0.,1.05);
        //eff_DoubleEl_OR_vs_el1_pt->GetYaxis()->SetRangeUser(0.,1.05);
        eff_DoubleEl_OR_vs_el1_pt_MC->SetMarkerColor(kRed);
        eff_DoubleEl_OR_vs_el1_pt_MC->SetLineColor(kRed);
        eff_DoubleEl_OR_vs_el1_pt_MC->Draw("HIST");
	DoubleEl->Draw("same");
        eff_DoubleEl_OR_vs_el1_pt->Draw("HIST same");
	l->Draw("same");
	paveCMS->Draw("same");
	c2->SaveAs("eff_DoubleEl_OR_vs_el1_pt.png");

        TCanvas *c3 = new TCanvas("c3","c3");
        c3->cd();
	c3->SetGrid();
        //eff_DoubleEl_OR_vs_el0_eta_MC->GetYaxis()->SetRangeUser(0.,1.05);
        //eff_DoubleEl_OR_vs_el0_eta->GetYaxis()->SetRangeUser(0.,1.05);
        eff_DoubleEl_OR_vs_el0_eta_MC->SetMarkerColor(kRed);
        eff_DoubleEl_OR_vs_el0_eta_MC->SetLineColor(kRed);
        eff_DoubleEl_OR_vs_el0_eta_MC->Draw("HIST");
        eff_DoubleEl_OR_vs_el0_eta->Draw("HIST same");
	DoubleEl->Draw("same");
	l->Draw("same");
	paveCMS->Draw("same");
	c3->SaveAs("eff_DoubleEl_OR_vs_el0_eta.png");

        TCanvas *c4 = new TCanvas("c4","c4");
        c4->cd();
	c4->SetGrid();
        //eff_DoubleEl_OR_vs_el1_eta_MC->GetYaxis()->SetRangeUser(0.,1.05);
        //eff_DoubleEl_OR_vs_el1_eta->GetYaxis()->SetRangeUser(0.,1.05);
        eff_DoubleEl_OR_vs_el1_eta_MC->SetMarkerColor(kRed);
        eff_DoubleEl_OR_vs_el1_eta_MC->SetLineColor(kRed);
        eff_DoubleEl_OR_vs_el1_eta_MC->Draw("HIST");
	DoubleEl->Draw("same");
        eff_DoubleEl_OR_vs_el1_eta->Draw("HIST same");
	l->Draw("same");
	paveCMS->Draw("same");
	c4->SaveAs("eff_DoubleEl_OR_vs_el1_eta.png");

        TCanvas *c5 = new TCanvas("c5","c5");
        c5->cd();
	c5->SetGrid();
        //eff_DoubleEl_OR_vs_nPV_MC->GetYaxis()->SetRangeUser(0.,1.05);
        //eff_DoubleEl_OR_vs_nPV->GetYaxis()->SetRangeUser(0.,1.05);
        eff_DoubleEl_OR_vs_nPV_MC->SetMarkerColor(kRed);
        eff_DoubleEl_OR_vs_nPV_MC->SetLineColor(kRed);
        eff_DoubleEl_OR_vs_nPV_MC->Draw("HIST");
	DoubleEl->Draw("same");
        eff_DoubleEl_OR_vs_nPV->Draw("HIST same");
	l->Draw("same");
	paveCMS->Draw("same");
	c5->SaveAs("eff_DoubleEl_OR_vs_nPV.png");

        TCanvas *c6 = new TCanvas("c6","c6");
        c6->cd();
	c6->SetGrid();
        //eff_DoubleEl_OR_vs_met_MC->GetYaxis()->SetRangeUser(0.,1.05);
        //eff_DoubleEl_OR_vs_met->GetYaxis()->SetRangeUser(0.,1.05);
        eff_DoubleEl_OR_vs_met_MC->SetMarkerColor(kRed);
        eff_DoubleEl_OR_vs_met_MC->SetLineColor(kRed);
        eff_DoubleEl_OR_vs_met_MC->Draw("HIST");
	DoubleEl->Draw("same");
        eff_DoubleEl_OR_vs_met->Draw("HIST same");
	l->Draw("same");
	paveCMS->Draw("same");
	c6->SaveAs("eff_DoubleEl_OR_vs_met.png");

        TCanvas *c7 = new TCanvas("c7","c7");
        c7->cd();
	c7->SetGrid();
        //eff_DoubleEl_OR_vs_njets_MC->GetYaxis()->SetRangeUser(0.,1.05);
        //eff_DoubleEl_OR_vs_njets->GetYaxis()->SetRangeUser(0.,1.05);
        eff_DoubleEl_OR_vs_njets_MC->SetMarkerColor(kRed);
        eff_DoubleEl_OR_vs_njets_MC->SetLineColor(kRed);
        eff_DoubleEl_OR_vs_njets_MC->Draw("HIST");
	DoubleEl->Draw("same");
        eff_DoubleEl_OR_vs_njets->Draw("HIST same");
	l->Draw("same");
	paveCMS->Draw("same");
	c7->SaveAs("eff_DoubleEl_OR_vs_njets.png");

	// EMu

        TCanvas *cc1 = new TCanvas("cc1","cc1");
        cc1->cd();
	cc1->SetGrid();
        //eff_EMu_OR_vs_el0_pt_MC->GetYaxis()->SetRangeUser(0.,1.05);
        //eff_EMu_OR_vs_el0_pt->GetYaxis()->SetRangeUser(0.,1.05);
        eff_EMu_OR_vs_el0_pt_MC->SetMarkerColor(kRed);
        eff_EMu_OR_vs_el0_pt_MC->SetLineColor(kRed);
        eff_EMu_OR_vs_el0_pt_MC->Draw("HIST");
        eff_EMu_OR_vs_el0_pt->Draw("HIST same");
	ElMu->Draw("same");
	l->Draw("same");
	paveCMS->Draw("same");
	cc1->SaveAs("eff_EMu_OR_vs_el0_pt.png");

        TCanvas *cc2 = new TCanvas("cc2","cc2");
        cc2->cd();
	cc2->SetGrid();
        //eff_EMu_OR_vs_mu0_pt_MC->GetYaxis()->SetRangeUser(0.,1.05);
        //eff_EMu_OR_vs_mu0_pt->GetYaxis()->SetRangeUser(0.,1.05);
        eff_EMu_OR_vs_mu0_pt_MC->SetMarkerColor(kRed);
        eff_EMu_OR_vs_mu0_pt_MC->SetLineColor(kRed);
        eff_EMu_OR_vs_mu0_pt_MC->Draw("HIST");
        eff_EMu_OR_vs_mu0_pt->Draw("HIST same");
	ElMu->Draw("same");
	l->Draw("same");
	paveCMS->Draw("same");
	cc2->SaveAs("eff_EMu_OR_vs_mu0_pt.png");

        TCanvas *cc3 = new TCanvas("cc3","cc3");
        cc3->cd();
	cc3->SetGrid();
        //eff_EMu_OR_vs_el0_eta_MC->GetYaxis()->SetRangeUser(0.,1.05);
        //eff_EMu_OR_vs_el0_eta->GetYaxis()->SetRangeUser(0.,1.05);
        eff_EMu_OR_vs_el0_eta_MC->SetMarkerColor(kRed);
        eff_EMu_OR_vs_el0_eta_MC->SetLineColor(kRed);
        eff_EMu_OR_vs_el0_eta_MC->Draw("HIST");
        eff_EMu_OR_vs_el0_eta->Draw("HIST same");
	ElMu->Draw("same");
	l->Draw("same");
	paveCMS->Draw("same");
	cc3->SaveAs("eff_EMu_OR_vs_el0_eta.png");

        TCanvas *cc4 = new TCanvas("cc4","cc4");
        cc4->cd();
	cc4->SetGrid();
        //eff_EMu_OR_vs_mu0_eta_MC->GetYaxis()->SetRangeUser(0.,1.05);
        //eff_EMu_OR_vs_mu0_eta->GetYaxis()->SetRangeUser(0.,1.05);
        eff_EMu_OR_vs_mu0_eta_MC->SetMarkerColor(kRed);
        eff_EMu_OR_vs_mu0_eta_MC->SetLineColor(kRed);
        eff_EMu_OR_vs_mu0_eta_MC->Draw("HIST");
        eff_EMu_OR_vs_mu0_eta->Draw("HIST same");
	ElMu->Draw("same");
	l->Draw("same");
	paveCMS->Draw("same");
	cc4->SaveAs("eff_EMu_OR_vs_mu0_eta.png");

        TCanvas *cc5 = new TCanvas("cc5","cc5");
        cc5->cd();
	cc5->SetGrid();
        //eff_EMu_OR_vs_nPV_MC->GetYaxis()->SetRangeUser(0.,1.05);
        //eff_EMu_OR_vs_nPV->GetYaxis()->SetRangeUser(0.,1.05);
        eff_EMu_OR_vs_nPV_MC->SetMarkerColor(kRed);
        eff_EMu_OR_vs_nPV_MC->SetLineColor(kRed);
        eff_EMu_OR_vs_nPV_MC->Draw("HIST");
        eff_EMu_OR_vs_nPV->Draw("HIST same");
	ElMu->Draw("same");
	l->Draw("same");
	paveCMS->Draw("same");
	cc5->SaveAs("eff_EMu_OR_vs_nPV.png");

        TCanvas *cc6 = new TCanvas("cc6","cc6");
        cc6->cd();
	cc6->SetGrid();
        //eff_EMu_OR_vs_met_MC->GetYaxis()->SetRangeUser(0.,1.05);
        //eff_EMu_OR_vs_met->GetYaxis()->SetRangeUser(0.,1.05);
        eff_EMu_OR_vs_met_MC->SetMarkerColor(kRed);
        eff_EMu_OR_vs_met_MC->SetLineColor(kRed);
        eff_EMu_OR_vs_met_MC->Draw("HIST");
	ElMu->Draw("same");
        eff_EMu_OR_vs_met->Draw("HIST same");
	l->Draw("same");
	paveCMS->Draw("same");
	cc6->SaveAs("eff_EMu_OR_vs_met.png");

        TCanvas *cc7 = new TCanvas("cc7","cc7");
        cc7->cd();
	cc7->SetGrid();
        //eff_EMu_OR_vs_njets_MC->GetYaxis()->SetRangeUser(0.,1.05);
        //eff_EMu_OR_vs_njets->GetYaxis()->SetRangeUser(0.,1.05);
        eff_EMu_OR_vs_njets_MC->SetMarkerColor(kRed);
        eff_EMu_OR_vs_njets_MC->SetLineColor(kRed);
        eff_EMu_OR_vs_njets_MC->Draw("HIST");
	ElMu->Draw("same");
        eff_EMu_OR_vs_njets->Draw("HIST same");
	l->Draw("same");
	paveCMS->Draw("same");
	cc7->SaveAs("eff_EMu_OR_vs_njets.png");

	// DoubleMu

        TCanvas *ccc1 = new TCanvas("ccc1","ccc1");
        ccc1->cd();
	ccc1->SetGrid();
        //eff_DoubleMu_OR_vs_mu1_pt_MC->GetYaxis()->SetRangeUser(0.,1.05);
        //eff_DoubleMu_OR_vs_mu1_pt->GetYaxis()->SetRangeUser(0.,1.05);
        eff_DoubleMu_OR_vs_mu1_pt_MC->SetMarkerColor(kRed);
        eff_DoubleMu_OR_vs_mu1_pt_MC->SetLineColor(kRed);
        eff_DoubleMu_OR_vs_mu1_pt_MC->Draw("HIST");
        eff_DoubleMu_OR_vs_mu1_pt->Draw("HIST same");
	DoubleMu->Draw("same");
	l->Draw("same");
	paveCMS->Draw("same");
	ccc1->SaveAs("eff_DoubleMu_OR_vs_mu1_pt.png");

        TCanvas *ccc2 = new TCanvas("ccc2","ccc2");
        ccc2->cd();
	ccc2->SetGrid();
        //eff_DoubleMu_OR_vs_mu0_pt_MC->GetYaxis()->SetRangeUser(0.,1.05);
        //eff_DoubleMu_OR_vs_mu0_pt->GetYaxis()->SetRangeUser(0.,1.05);
        eff_DoubleMu_OR_vs_mu0_pt_MC->SetMarkerColor(kRed);
        eff_DoubleMu_OR_vs_mu0_pt_MC->SetLineColor(kRed);
        eff_DoubleMu_OR_vs_mu0_pt_MC->Draw("HIST");
        eff_DoubleMu_OR_vs_mu0_pt->Draw("HIST same");
	DoubleMu->Draw("same");
	l->Draw("same");
	paveCMS->Draw("same");
	ccc2->SaveAs("eff_DoubleMu_OR_vs_mu0_pt.png");
	
        TCanvas *ccc3 = new TCanvas("ccc3","ccc3");
        ccc3->cd();
	ccc3->SetGrid();
        //eff_DoubleMu_OR_vs_mu1_eta_MC->GetYaxis()->SetRangeUser(0.,1.05);
        //eff_DoubleMu_OR_vs_mu1_eta->GetYaxis()->SetRangeUser(0.,1.05);
        eff_DoubleMu_OR_vs_mu1_eta_MC->SetMarkerColor(kRed);
        eff_DoubleMu_OR_vs_mu1_eta_MC->SetLineColor(kRed);
        eff_DoubleMu_OR_vs_mu1_eta_MC->Draw("HIST");
        eff_DoubleMu_OR_vs_mu1_eta->Draw("HIST same");
	DoubleMu->Draw("same");
	l->Draw("same");
	paveCMS->Draw("same");
	ccc3->SaveAs("eff_DoubleMu_OR_vs_mu1_eta.png");

        TCanvas *ccc4 = new TCanvas("ccc4","ccc4");
        ccc4->cd();
	ccc4->SetGrid();
        //eff_DoubleMu_OR_vs_mu0_eta_MC->GetYaxis()->SetRangeUser(0.,1.05);
        //eff_DoubleMu_OR_vs_mu0_eta->GetYaxis()->SetRangeUser(0.,1.05);
        eff_DoubleMu_OR_vs_mu0_eta_MC->SetMarkerColor(kRed);
        eff_DoubleMu_OR_vs_mu0_eta_MC->SetLineColor(kRed);
        eff_DoubleMu_OR_vs_mu0_eta_MC->Draw("HIST");
        eff_DoubleMu_OR_vs_mu0_eta->Draw("HIST same");
	DoubleMu->Draw("same");
	l->Draw("same");
	paveCMS->Draw("same");
	ccc4->SaveAs("eff_DoubleMu_OR_vs_mu0_eta.png");

        TCanvas *ccc5 = new TCanvas("ccc5","ccc5");
        ccc5->cd();
	ccc5->SetGrid();
        //eff_DoubleMu_OR_vs_nPV_MC->GetYaxis()->SetRangeUser(0.,1.05);
        //eff_DoubleMu_OR_vs_nPV->GetYaxis()->SetRangeUser(0.,1.05);
        eff_DoubleMu_OR_vs_nPV_MC->SetMarkerColor(kRed);
        eff_DoubleMu_OR_vs_nPV_MC->SetLineColor(kRed);
        eff_DoubleMu_OR_vs_nPV_MC->Draw("HIST");
	DoubleMu->Draw("same");
        eff_DoubleMu_OR_vs_nPV->Draw("HIST same");
	l->Draw("same");
	paveCMS->Draw("same");
	ccc5->SaveAs("eff_DoubleMu_OR_vs_nPV.png");

        TCanvas *ccc6 = new TCanvas("ccc6","ccc6");
        ccc6->cd();
	ccc6->SetGrid();
        //eff_DoubleMu_OR_vs_met_MC->GetYaxis()->SetRangeUser(0.,1.05);
        //eff_DoubleMu_OR_vs_met->GetYaxis()->SetRangeUser(0.,1.05);
        eff_DoubleMu_OR_vs_met_MC->SetMarkerColor(kRed);
        eff_DoubleMu_OR_vs_met_MC->SetLineColor(kRed);
        eff_DoubleMu_OR_vs_met_MC->Draw("HIST");
	DoubleMu->Draw("same");
        eff_DoubleMu_OR_vs_met->Draw("HIST same");
	l->Draw("same");
	paveCMS->Draw("same");
	ccc6->SaveAs("eff_DoubleMu_OR_vs_met.png");

        TCanvas *ccc7 = new TCanvas("ccc7","ccc7");
        ccc7->cd();
	ccc7->SetGrid();
        //eff_DoubleMu_OR_vs_njets_MC->GetYaxis()->SetRangeUser(0.,1.05);
        //eff_DoubleMu_OR_vs_njets->GetYaxis()->SetRangeUser(0.,1.05);
        eff_DoubleMu_OR_vs_njets_MC->SetMarkerColor(kRed);
        eff_DoubleMu_OR_vs_njets_MC->SetLineColor(kRed);
        eff_DoubleMu_OR_vs_njets_MC->Draw("HIST");
	DoubleMu->Draw("same");
        eff_DoubleMu_OR_vs_njets->Draw("HIST same");
	l->Draw("same");
	paveCMS->Draw("same");
	ccc7->SaveAs("eff_DoubleMu_OR_vs_njets.png");
}

