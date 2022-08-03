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

TH2D* GetLumiScaledSystSF_2017(TString hist){

        // TFile *f = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/outputs_and_plotting_script/TriggerSFs_2016.root","READ");
        TFile *f = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/outputs_and_plotting_script/TriggerSFs_2017.root","READ");
        // TFile *f = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/outputs_and_plotting_script/TriggerSFs_2018.root","READ");

        // TFile* f_A = new TFile("","READ");
        // TFile* f_B = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/outputs_and_plotting_script/TriggerSFs_2016_B.root","READ");
        // TFile* f_C = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/outputs_and_plotting_script/TriggerSFs_2016_C.root","READ");
        // TFile* f_D = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/outputs_and_plotting_script/TriggerSFs_2016_D.root","READ");
        // TFile* f_E = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/outputs_and_plotting_script/TriggerSFs_2016_E.root","READ");
        // TFile* f_F = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/outputs_and_plotting_script/TriggerSFs_2016_F.root","READ");
        // TFile* f_G = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/outputs_and_plotting_script/TriggerSFs_2016_G.root","READ");
        // TFile* f_H = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/outputs_and_plotting_script/TriggerSFs_2016_H.root","READ");
        TFile* f_B = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/outputs_and_plotting_script/TriggerSFs_2017_B.root","READ");
        TFile* f_C = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/outputs_and_plotting_script/TriggerSFs_2017_C.root","READ");
        TFile* f_D = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/outputs_and_plotting_script/TriggerSFs_2017_D.root","READ");
        TFile* f_E = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/outputs_and_plotting_script/TriggerSFs_2017_E.root","READ");
        TFile* f_F = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/outputs_and_plotting_script/TriggerSFs_2017_F.root","READ");
        // TFile* f_A = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/outputs_and_plotting_script/TriggerSFs_2018_A.root","READ");
        // TFile* f_B = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/outputs_and_plotting_script/TriggerSFs_2018_B.root","READ");
        // TFile* f_C = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/outputs_and_plotting_script/TriggerSFs_2018_C.root","READ");
        // TFile* f_D = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl/outputs_and_plotting_script/TriggerSFs_2018_D.root","READ");

        TH2D*  h2_all = (TH2D*)f->Get(hist);
        // TH2D*  h_A = (TH2D*)f_A->Get(hist);
        TH2D*  h_B = (TH2D*)f_B->Get(hist);
        TH2D*  h_C = (TH2D*)f_C->Get(hist);
        TH2D*  h_D = (TH2D*)f_D->Get(hist);
        TH2D*  h_E = (TH2D*)f_E->Get(hist);
        TH2D*  h_F = (TH2D*)f_F->Get(hist);
        // TH2D*  h_G = (TH2D*)f_G->Get(hist);
        // TH2D*  h_H = (TH2D*)f_H->Get(hist);

	    //2016 (5.750490644+2.572903489+4.242291557+4.025228137+3.104509132+7.575824256+8.650628380) = 35.921875595
        // h_B->Scale(0.160083);
        // h_C->Scale(0.071625);
        // h_D->Scale(0.1180977);
        // h_E->Scale(0.1120551);
        // h_F->Scale(0.0864239);
        // h_G->Scale(0.2108972);
        // h_H->Scale(0.2408178);
	    //2017 (4.793969902+9.632746395+4.247792714+9.314581016+13.540062032) = 41.529152059
        h_B->Scale(0.115436258);
        h_C->Scale(0.2319514345);
        h_D->Scale(0.1022846002);
        h_E->Scale(0.22429018061);
        h_F->Scale(0.32603752691);
	    //2018 (14.027614284+7.066552169+6.898816878+31.747581871) = 59.740565202
        // h_A->Scale(0.23480886);
        // h_B->Scale(0.11828733);
        // h_C->Scale(0.115479605);
        // h_D->Scale(0.531424197);

    	TH2D* lumiSum = (TH2D*)h_B->Clone();
    	lumiSum->Add(h_C);
    	lumiSum->Add(h_D);
    	lumiSum->Add(h_E);
    	lumiSum->Add(h_F);
    	// lumiSum->Add(h_G);
    	// lumiSum->Add(h_H);
    	// lumiSum->Add(h_A);

    	TH2D* h2_fullDiff = (TH2D*)h2_all->Clone();
    	h2_fullDiff->Add(lumiSum, -1);

  	return h2_fullDiff;
}

void ScaleFactors_syst_lumi()
{


        //      Double Electron stream (OR of Single & Double electron triggers)        ///////////////

        TH2D* h_DoubleEl_OR__X__allMET_el0_pt_vs_eta = GetLumiScaledSystSF_2017("h_DoubleEl_OR__X__allMET_el0_pt_vs_eta");
        TH2D* h_DoubleEl_OR__X__allMET_el1_pt_vs_eta = GetLumiScaledSystSF_2017("h_DoubleEl_OR__X__allMET_el1_pt_vs_eta");
        TH2D* h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt = GetLumiScaledSystSF_2017("h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt");
        TH2D* h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta = GetLumiScaledSystSF_2017("h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta");

        //      EMu stream (OR of Single & Double electron triggers)    ///////////////

        TH2D* h_EMu_OR__X__allMET_el0_pt_vs_eta = GetLumiScaledSystSF_2017("h_EMu_OR__X__allMET_el0_pt_vs_eta");
        TH2D* h_EMu_OR__X__allMET_mu0_pt_vs_eta = GetLumiScaledSystSF_2017("h_EMu_OR__X__allMET_mu0_pt_vs_eta");
        TH2D* h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta = GetLumiScaledSystSF_2017("h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta");
        TH2D* h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt = GetLumiScaledSystSF_2017("h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt");

        //      Double Muon stream (OR of Single & Double electron triggers)    ///////////////

        TH2D* h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta = GetLumiScaledSystSF_2017("h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta");
        TH2D* h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta = GetLumiScaledSystSF_2017("h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta");
        TH2D* h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt = GetLumiScaledSystSF_2017("h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt");
        TH2D* h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta = GetLumiScaledSystSF_2017("h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta");
        ///////////////////

        TFile* f=new TFile("TriggerSFs_2017_lumi.root","RECREATE");

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
