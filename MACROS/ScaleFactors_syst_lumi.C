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

TH2D* GetLumiScaledSystSF_2017(TString hist,string year){

        

        // https://twiki.cern.ch/twiki/bin/viewauth/CMS/DCUserPage -> To get the luminosity
        if(year=="2016"){
                TFile *f = new TFile("/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/TriggerSFs_2016.root","READ");
                TFile* f_B = new TFile("/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/TriggerSFsB_2016.root","READ");
                TFile* f_C = new TFile("/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/TriggerSFsC_2016.root","READ");
                TFile* f_D = new TFile("/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/TriggerSFsD_2016.root","READ");
                TFile* f_E = new TFile("/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/TriggerSFsE_2016.root","READ");
                TFile* f_F = new TFile("/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/TriggerSFsF_2016.root","READ");
                TFile* f_G = new TFile("/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/TriggerSFsG_2016.root","READ");
                TFile* f_H = new TFile("/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2016/TriggerSFsH_2016.root","READ");
        
                TH2D*  h2_all = (TH2D*)f->Get(hist);
                TH2D*  h_B = (TH2D*)f_B->Get(hist);
                TH2D*  h_C = (TH2D*)f_C->Get(hist);
                TH2D*  h_D = (TH2D*)f_D->Get(hist);
                TH2D*  h_E = (TH2D*)f_E->Get(hist);
                TH2D*  h_F = (TH2D*)f_F->Get(hist);
                TH2D*  h_G = (TH2D*)f_G->Get(hist);
                TH2D*  h_H = (TH2D*)f_H->Get(hist);

                //2016 (5.750490644+2.572903489+4.242291557+4.025228137+3.104509132+7.575824256+8.650628380) = 35.921875595
                h_B->Scale(0.160083);
                h_C->Scale(0.071625);
                h_D->Scale(0.1180977);
                h_E->Scale(0.1120551);
                h_F->Scale(0.0864239);
                h_G->Scale(0.2108972);
                h_H->Scale(0.2408178);

                TH2D* lumiSum = (TH2D*)h_B->Clone();
            	lumiSum->Add(h_C);
        	lumiSum->Add(h_D);
        	lumiSum->Add(h_E);
        	lumiSum->Add(h_F);
        	lumiSum->Add(h_G);
        	lumiSum->Add(h_H);


                TH2D* h2_fullDiff = (TH2D*)h2_all->Clone();
    	        h2_fullDiff->Add(lumiSum, -1);

  	        return h2_fullDiff;
        }

        if(year=="2017"){
                TFile *f = new TFile("/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2017/TriggerSFs_2017.root","READ");

                TFile* f_B = new TFile("/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2017/TriggerSFsB_2017.root","READ");
                TFile* f_C = new TFile("/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2017/TriggerSFsC_2017.root","READ");
                TFile* f_D = new TFile("/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2017/TriggerSFsD_2017.root","READ");
                TFile* f_E = new TFile("/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2017/TriggerSFsE_2017.root","READ");
                TFile* f_F = new TFile("/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2017/TriggerSFsF_2017.root","READ");

        
                TH2D*  h2_all = (TH2D*)f->Get(hist);
                TH2D*  h_B = (TH2D*)f_B->Get(hist);
                TH2D*  h_C = (TH2D*)f_C->Get(hist);
                TH2D*  h_D = (TH2D*)f_D->Get(hist);
                TH2D*  h_E = (TH2D*)f_E->Get(hist);
                TH2D*  h_F = (TH2D*)f_F->Get(hist);

                //2017 (4.793969902+9.632746395+4.247792714+9.314581016+13.540062032) = 41.529152059
                h_B->Scale(0.115436258);
                h_C->Scale(0.2319514345);
                h_D->Scale(0.1022846002);
                h_E->Scale(0.22429018061);
                h_F->Scale(0.32603752691);

                
                TH2D* lumiSum = (TH2D*)h_B->Clone();
            	lumiSum->Add(h_C);
        	lumiSum->Add(h_D);
        	lumiSum->Add(h_E);
        	lumiSum->Add(h_F);



                TH2D* h2_fullDiff = (TH2D*)h2_all->Clone();
    	        h2_fullDiff->Add(lumiSum, -1);

  	        return h2_fullDiff;
        }

        if(year=="2018"){
                TFile *f = new TFile("/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2018/TriggerSFs_2018.root","READ");

                TFile* f_A = new TFile("/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2018/TriggerSFsA_2018.root","READ");
                TFile* f_B = new TFile("/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2018/TriggerSFsB_2018.root","READ");
                TFile* f_C = new TFile("/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2018/TriggerSFsC_2018.root","READ");
                TFile* f_D = new TFile("/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/2018/TriggerSFsD_2018.root","READ");
        
                TH2D*  h2_all = (TH2D*)f->Get(hist);
                TH2D*  h_A = (TH2D*)f_A->Get(hist);
                TH2D*  h_B = (TH2D*)f_B->Get(hist);
                TH2D*  h_C = (TH2D*)f_C->Get(hist);
                TH2D*  h_D = (TH2D*)f_D->Get(hist);

                // NEW: 2018 (14.00+7.10+6.94+31.93)= 59.97
                h_A->Scale(0.233450058);
                h_B->Scale(0.11839253);
                h_C->Scale(0.115724529);
                h_D->Scale(0.532432883);

                TH2D* lumiSum = (TH2D*)h_B->Clone();
    	        lumiSum->Add(h_C);
    	        lumiSum->Add(h_D);
    	        lumiSum->Add(h_A);
                TH2D* h2_fullDiff = (TH2D*)h2_all->Clone();
    	        h2_fullDiff->Add(lumiSum, -1);

  	        return h2_fullDiff;
        }

}

void ScaleFactors_syst_lumi(string year)
{

        

        //      Double Electron stream (OR of Single & Double electron triggers)        ///////////////

        TH2D* h_DoubleEl_OR__X__allMET_el0_pt_vs_eta = GetLumiScaledSystSF_2017("h_DoubleEl_OR__X__allMET_el0_pt_vs_eta",year);
        TH2D* h_DoubleEl_OR__X__allMET_el1_pt_vs_eta = GetLumiScaledSystSF_2017("h_DoubleEl_OR__X__allMET_el1_pt_vs_eta",year);
        TH2D* h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt = GetLumiScaledSystSF_2017("h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt",year);
        TH2D* h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta = GetLumiScaledSystSF_2017("h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta",year);

        //      EMu stream (OR of Single & Double electron triggers)    ///////////////

        TH2D* h_EMu_OR__X__allMET_el0_pt_vs_eta = GetLumiScaledSystSF_2017("h_EMu_OR__X__allMET_el0_pt_vs_eta",year);
        TH2D* h_EMu_OR__X__allMET_mu0_pt_vs_eta = GetLumiScaledSystSF_2017("h_EMu_OR__X__allMET_mu0_pt_vs_eta",year);
        TH2D* h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta = GetLumiScaledSystSF_2017("h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta",year);
        TH2D* h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt = GetLumiScaledSystSF_2017("h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt",year);

        //      Double Muon stream (OR of Single & Double electron triggers)    ///////////////

        TH2D* h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta = GetLumiScaledSystSF_2017("h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta",year);
        TH2D* h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta = GetLumiScaledSystSF_2017("h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta",year);
        TH2D* h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt = GetLumiScaledSystSF_2017("h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt",year);
        TH2D* h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta = GetLumiScaledSystSF_2017("h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta",year);
        ///////////////////

        TFile* f=new TFile(("/home/matheus/Desktop/tt-triggerEfficiency-DL/outputs_and_plotting_script/"+year+"/TriggerSFs_"+year+"_lumi.root").c_str(),"RECREATE");

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
