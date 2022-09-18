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

TH2D* Get_data(TString hist,string Tag_region, string year){


        TFile *f = new TFile(("/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/"+year+"/TriggerSFs_"+year+".root").c_str(),"READ");
        TFile* f_region = new TFile(("/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/"+year+"/TriggerSFs_"+year+Tag_region+".root").c_str(),"READ");
        

        TH2D*  h_default = (TH2D*)f->Get(hist);
        TH2D*  h_new = (TH2D*)f_region->Get(hist);

    	TH2D* h2_fullDiff = (TH2D*)h_default->Clone();
    	h2_fullDiff->Add(h_new, -1);
  	return h2_fullDiff; //Return the difference between teh region and the default
}

void Systematic_regions(string Tag_region, string year)
{

        

        //      Double Electron stream (OR of Single & Double electron triggers)        ///////////////

        TH2D* h_DoubleEl_OR__X__allMET_el0_pt_vs_eta = Get_data("h_DoubleEl_OR__X__allMET_el0_pt_vs_eta",Tag_region,year);
        TH2D* h_DoubleEl_OR__X__allMET_el1_pt_vs_eta = Get_data("h_DoubleEl_OR__X__allMET_el1_pt_vs_eta",Tag_region,year);
        TH2D* h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt = Get_data("h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt",Tag_region,year);
        TH2D* h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta = Get_data("h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta",Tag_region,year);

        //      EMu stream (OR of Single & Double electron triggers)    ///////////////

        TH2D* h_EMu_OR__X__allMET_el0_pt_vs_eta = Get_data("h_EMu_OR__X__allMET_el0_pt_vs_eta",Tag_region,year);
        TH2D* h_EMu_OR__X__allMET_mu0_pt_vs_eta = Get_data("h_EMu_OR__X__allMET_mu0_pt_vs_eta",Tag_region,year);
        TH2D* h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta = Get_data("h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta",Tag_region,year);
        TH2D* h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt = Get_data("h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt",Tag_region,year);

        //      Double Muon stream (OR of Single & Double electron triggers)    ///////////////

        TH2D* h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta = Get_data("h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta",Tag_region,year);
        TH2D* h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta = Get_data("h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta",Tag_region,year);
        TH2D* h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt = Get_data("h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt",Tag_region,year);
        TH2D* h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta = Get_data("h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta",Tag_region,year);
        ///////////////////

        TFile* f=new TFile(("/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/"+year+"/Systematic_uncertain"+Tag_region+".root").c_str(),"RECREATE");

        h_DoubleEl_OR__X__allMET_el0_pt_vs_eta->SetName("h_DoubleEl_OR__X__allMET_el0_pt_vs_eta");
        h_DoubleEl_OR__X__allMET_el0_pt_vs_eta->Write();
        h_DoubleEl_OR__X__allMET_el1_pt_vs_eta->SetName("h_DoubleEl_OR__X__allMET_el1_pt_vs_eta");
        h_DoubleEl_OR__X__allMET_el1_pt_vs_eta->Write();
        h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt->SetName("h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt");
        h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt->Write();
        h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta->SetName("h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta");
        h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta->Write();

        h_EMu_OR__X__allMET_el0_pt_vs_eta->SetName("h_EMu_OR__X__allMET_el0_pt_vs_eta");
        h_EMu_OR__X__allMET_el0_pt_vs_eta->Write();
        h_EMu_OR__X__allMET_mu0_pt_vs_eta->SetName("h_EMu_OR__X__allMET_mu0_pt_vs_eta");
        h_EMu_OR__X__allMET_mu0_pt_vs_eta->Write();
        h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta->SetName("h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta");
        h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta->Write();
        h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt->SetName("h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt");
        h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt->Write();

        h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta->SetName("h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta");
        h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta->Write();
        h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta->SetName("h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta");
        h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta->Write();
        h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt->SetName("h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt");
        h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt->Write();
        h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta->SetName("h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta");
        h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta->Write();


}
