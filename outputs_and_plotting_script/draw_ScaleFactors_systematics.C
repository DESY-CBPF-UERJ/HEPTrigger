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

TH2D* Get2DScaleFactorHistogram(TEfficiency* t_data, TEfficiency* t_ttbar, TH2D* ref){

	TH2D* h_sf = (TH2D*) ref->Clone();
  	double ratio = 0;
  	double err = 0;
  	for (int i =1; i < h_sf->GetNbinsX()+1; i++){
    		for (int j =1; j < h_sf->GetNbinsY()+1; j++){
      			// ** 1. Get central value of SF
                // Se o bin valor do t_ttbar for igual a diferente de 0, então ele calcula a eficiência como sendo t_data/t_ttbar. Caso seja igual a 0, então é 0
      			ratio = t_ttbar->GetEfficiency( t_ttbar->GetTotalHistogram()->GetBin(i,j) ) != 0 ? t_data->GetEfficiency( t_ttbar->GetTotalHistogram()->GetBin(i,j) )/t_ttbar->GetEfficiency( t_ttbar->GetTotalHistogram()->GetBin(i,j) ) : 0;
      			// ** 2. Get biggest error and take that as symmetric envelope --> conservative approach. probably a more intelligent way (https://www.jstor.org/stable/2531405)
                
      			err = t_data->GetEfficiencyErrorUp( t_ttbar->GetTotalHistogram()->GetBin(i,j) );
      			if (t_data->GetEfficiencyErrorLow( t_ttbar->GetTotalHistogram()->GetBin(i,j) ) > err)   err = t_data->GetEfficiencyErrorLow( t_ttbar->GetTotalHistogram()->GetBin(i,j) );
      			if (t_ttbar->GetEfficiencyErrorUp( t_ttbar->GetTotalHistogram()->GetBin(i,j) ) > err)   err = t_ttbar->GetEfficiencyErrorUp( t_ttbar->GetTotalHistogram()->GetBin(i,j) );
      			if (t_ttbar->GetEfficiencyErrorLow( t_ttbar->GetTotalHistogram()->GetBin(i,j) ) > err)  err = t_ttbar->GetEfficiencyErrorLow( t_ttbar->GetTotalHistogram()->GetBin(i,j) );
		      	if (ratio == 0) err = 0;

      			// ** 3. Set SF histogram content and error
      			h_sf->SetBinContent(i, j, ratio);
      			h_sf->SetBinError(i, j, err);
    		}
  	}

  	return h_sf;
}

void draw_ScaleFactors_systematics()
{

        TString yearstring = "2016";

        setTDRStyle_teliko();

        // CMS box for plotting the canvases    ///////
        TPaveText *paveCMS = new TPaveText(0.18,0.96,0.93,0.99,"NDC");
        if(yearstring=="2016"){
            paveCMS->AddText("#bf{CMS #it{Preliminary} 2016}              35.9 fb^{-1}    (13 TeV)");
        }
        if(yearstring=="2017"){
            paveCMS->AddText("#bf{CMS #it{Preliminary} 2017}              41.5 fb^{-1}    (13 TeV)");
        }
        if(yearstring=="2018"){
            paveCMS->AddText("#bf{CMS #it{Preliminary} 2018}              59.8 fb^{-1}    (13 TeV)");
        }
        paveCMS->SetFillColor(0);
        paveCMS->SetBorderSize(0);
        paveCMS->SetTextSize(0.04);
        paveCMS->SetTextFont(42);



        //////////////////////////////////////////////
        //      DATA            //////////////////////
        //////////////////////////////////////////////

        // TFile *f = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl//TriggerFiles_2016/data/outfile_run2016H.root","READ");
        // TFile *f = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl//TriggerFiles_2017/data/outfile_run2017F.root","READ");
        
        //TFile *f = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl//TriggerFiles_2016/data/data_2016.root","READ");
        TFile *f = new TFile("/home/matheus/Desktop/tt-triggerEfficiency-DL/plots_19_6_2020_MC_2016_withSFs_9_1/data/outfile.root","READ");
        // TFile *f = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl//TriggerFiles_2017/data/data_2017.root","READ");
        // TFile *f = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl//TriggerFiles_2018/data/data_2018.root","READ");
        // TFile *f = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl//TriggerFiles_2018/data/outfile_run2018D.root","READ");


        f->cd();

        // TString s = "";
        // TString s = "_NJETSHIGH";
        // TString s = "_NJETSLOW";
        // TString s = "_NPVHIGH";
        // TString s = "_NPVLOW";
        // TString s = "_METHIGH";
         TString s = "_METLOW";


        //      Double Electron stream (OR of Single & Double electron triggers)        ///////////////

        TEfficiency* Eff_DoubleEl_OR_vs_el0_pt_vs_eta      = (TEfficiency*)f->Get("h_DoubleEl_OR__X__allMET"+s+"_el0_pt_vs_eta_TEff2D");
        TEfficiency* Eff_DoubleEl_OR_vs_el1_pt_vs_eta      = (TEfficiency*)f->Get("h_DoubleEl_OR__X__allMET"+s+"_el1_pt_vs_eta_TEff2D");
        TEfficiency* Eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt   = (TEfficiency*)f->Get("h_DoubleEl_OR__X__allMET"+s+"_el0_pt_vs_el1_pt_TEff2D");
        TEfficiency* Eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta = (TEfficiency*)f->Get("h_DoubleEl_OR__X__allMET"+s+"_el0_eta_vs_el1_eta_TEff2D");
        TH2D* h_DoubleEl_OR__X__allMET_el0_pt_vs_eta = (TH2D*) f->Get("h_DoubleEl_OR__X__allMET"+s+"_el0_pt_vs_eta");
        TH2D* h_DoubleEl_OR__X__allMET_el1_pt_vs_eta = (TH2D*) f->Get("h_DoubleEl_OR__X__allMET"+s+"_el1_pt_vs_eta");
        TH2D* h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt = (TH2D*) f->Get("h_DoubleEl_OR__X__allMET"+s+"_el0_pt_vs_el1_pt");
        TH2D* h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta = (TH2D*) f->Get("h_DoubleEl_OR__X__allMET"+s+"_el0_eta_vs_el1_eta");


        //      EMu stream (OR of Single & Double electron triggers)    ///////////////

        TEfficiency* Eff_EMu_OR_vs_el0_pt_vs_eta          = (TEfficiency*)f->Get("h_EMu_OR__X__allMET"+s+"_el0_pt_vs_eta_TEff2D");
        TEfficiency* Eff_EMu_OR_vs_mu0_pt_vs_eta          = (TEfficiency*)f->Get("h_EMu_OR__X__allMET"+s+"_mu0_pt_vs_eta_TEff2D");
        TEfficiency* Eff_EMu_OR_vs_mu0_eta_vs_el0_eta     = (TEfficiency*)f->Get("h_EMu_OR__X__allMET"+s+"_mu0_eta_vs_el0_eta_TEff2D");
        TEfficiency* Eff_EMu_OR_vs_mu0_pt_vs_el0_pt       = (TEfficiency*)f->Get("h_EMu_OR__X__allMET"+s+"_mu0_pt_vs_el0_pt_TEff2D");
        TH2D* h_EMu_OR__X__allMET_el0_pt_vs_eta = (TH2D*) f->Get("h_EMu_OR__X__allMET"+s+"_el0_pt_vs_eta");
        TH2D* h_EMu_OR__X__allMET_mu0_pt_vs_eta = (TH2D*) f->Get("h_EMu_OR__X__allMET"+s+"_mu0_pt_vs_eta");
        TH2D* h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta = (TH2D*) f->Get("h_EMu_OR__X__allMET"+s+"_mu0_eta_vs_el0_eta");
        TH2D* h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt = (TH2D*) f->Get("h_EMu_OR__X__allMET"+s+"_mu0_pt_vs_el0_pt");

        //      Double Muon stream (OR of Single & Double electron triggers)    ///////////////

        TEfficiency* Eff_DoubleMu_OR_vs_mu1_pt_vs_eta       = (TEfficiency*)f->Get("h_DoubleMu_OR__X__allMET"+s+"_mu1_pt_vs_eta_TEff2D");
        TEfficiency* Eff_DoubleMu_OR_vs_mu0_pt_vs_eta       = (TEfficiency*)f->Get("h_DoubleMu_OR__X__allMET"+s+"_mu0_pt_vs_eta_TEff2D");
        TEfficiency* Eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt    = (TEfficiency*)f->Get("h_DoubleMu_OR__X__allMET"+s+"_mu0_pt_vs_mu1_pt_TEff2D");
        TEfficiency* Eff_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta  = (TEfficiency*)f->Get("h_DoubleMu_OR__X__allMET"+s+"_mu0_eta_vs_mu1_eta_TEff2D");
        TH2D* h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta = (TH2D*) f->Get("h_DoubleMu_OR__X__allMET"+s+"_mu1_pt_vs_eta");
        TH2D* h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta = (TH2D*) f->Get("h_DoubleMu_OR__X__allMET"+s+"_mu0_pt_vs_eta");
        TH2D* h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt = (TH2D*) f->Get("h_DoubleMu_OR__X__allMET"+s+"_mu0_pt_vs_mu1_pt");
        TH2D* h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta = (TH2D*) f->Get("h_DoubleMu_OR__X__allMET"+s+"_mu0_eta_vs_mu1_eta");
        ///////////////////


        //////////////////////////////////////////////
        //      MC              //////////////////////
        //////////////////////////////////////////////
        TFile *f_MC;
        if(yearstring=="2016"){
            f_MC  = new TFile("/home/matheus/Desktop/tt-triggerEfficiency-DL/plots_19_6_2020_MC_2016_withSFs_9_1/MC/outfile.root","READ");
        }
        if(yearstring=="2017"){
            f_MC  = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl//TriggerFiles_2017/MC/outfile_2017.root","READ");
        }
        if(yearstring=="2018"){
            f_MC  = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl//TriggerFiles_2018/MC/outfile_2018.root","READ");
        }

        f_MC->cd();

        //      Double Electron stream (OR of Single & Double electron triggers)        ///////////////
        TEfficiency* Eff_DoubleEl_OR_vs_el0_pt_MC_vs_eta      = (TEfficiency*)f_MC->Get("h_DoubleEl_OR__X__allMET"+s+"_el0_pt_vs_eta_TEff2D");
        TEfficiency* Eff_DoubleEl_OR_vs_el1_pt_MC_vs_eta      = (TEfficiency*)f_MC->Get("h_DoubleEl_OR__X__allMET"+s+"_el1_pt_vs_eta_TEff2D");
        TEfficiency* Eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_MC   = (TEfficiency*)f_MC->Get("h_DoubleEl_OR__X__allMET"+s+"_el0_pt_vs_el1_pt_TEff2D");
        TEfficiency* Eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta_MC = (TEfficiency*)f_MC->Get("h_DoubleEl_OR__X__allMET"+s+"_el0_eta_vs_el1_eta_TEff2D");

        //      EMu stream (OR of Single & Double electron triggers)    ///////////////
        TEfficiency* Eff_EMu_OR_vs_el0_pt_MC_vs_eta          = (TEfficiency*)f_MC->Get("h_EMu_OR__X__allMET"+s+"_el0_pt_vs_eta_TEff2D");
        TEfficiency* Eff_EMu_OR_vs_mu0_pt_MC_vs_eta          = (TEfficiency*)f_MC->Get("h_EMu_OR__X__allMET"+s+"_mu0_pt_vs_eta_TEff2D");
        TEfficiency* Eff_EMu_OR_vs_mu0_eta_vs_el0_eta_MC     = (TEfficiency*)f_MC->Get("h_EMu_OR__X__allMET"+s+"_mu0_eta_vs_el0_eta_TEff2D");
        TEfficiency* Eff_EMu_OR_vs_mu0_pt_vs_el0_pt_MC       = (TEfficiency*)f_MC->Get("h_EMu_OR__X__allMET"+s+"_mu0_pt_vs_el0_pt_TEff2D");

        //      Double Muon stream (OR of Single & Double electron triggers)    ///////////////
        TEfficiency* Eff_DoubleMu_OR_vs_mu1_pt_MC_vs_eta       = (TEfficiency*)f_MC->Get("h_DoubleMu_OR__X__allMET"+s+"_mu1_pt_vs_eta_TEff2D");
        TEfficiency* Eff_DoubleMu_OR_vs_mu0_pt_MC_vs_eta       = (TEfficiency*)f_MC->Get("h_DoubleMu_OR__X__allMET"+s+"_mu0_pt_vs_eta_TEff2D");
        TEfficiency* Eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_MC    = (TEfficiency*)f_MC->Get("h_DoubleMu_OR__X__allMET"+s+"_mu0_pt_vs_mu1_pt_TEff2D");
        TEfficiency* Eff_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta_MC  = (TEfficiency*)f_MC->Get("h_DoubleMu_OR__X__allMET"+s+"_mu0_eta_vs_mu1_eta_TEff2D");

	/////////////////////////////
	    TH2D *eff_DoubleEl_OR_vs_el0_pt_vs_eta = Get2DScaleFactorHistogram(Eff_DoubleEl_OR_vs_el0_pt_vs_eta,Eff_DoubleEl_OR_vs_el0_pt_MC_vs_eta,h_DoubleEl_OR__X__allMET_el0_pt_vs_eta);
        TH2D *eff_DoubleEl_OR_vs_el1_pt_vs_eta = Get2DScaleFactorHistogram(Eff_DoubleEl_OR_vs_el1_pt_vs_eta,Eff_DoubleEl_OR_vs_el1_pt_MC_vs_eta,h_DoubleEl_OR__X__allMET_el1_pt_vs_eta);
        TH2D *eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt = Get2DScaleFactorHistogram(Eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt,Eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_MC,h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt);
        TH2D *eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta = Get2DScaleFactorHistogram(Eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta,Eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta_MC,h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta);

        TH2D *eff_EMu_OR_vs_el0_pt_vs_eta = Get2DScaleFactorHistogram(Eff_EMu_OR_vs_el0_pt_vs_eta,Eff_EMu_OR_vs_el0_pt_MC_vs_eta,h_EMu_OR__X__allMET_el0_pt_vs_eta);
        TH2D *eff_EMu_OR_vs_mu0_pt_vs_eta = Get2DScaleFactorHistogram(Eff_EMu_OR_vs_mu0_pt_vs_eta,Eff_EMu_OR_vs_mu0_pt_MC_vs_eta,h_EMu_OR__X__allMET_mu0_pt_vs_eta);
        TH2D *eff_EMu_OR_vs_mu0_eta_vs_el0_eta = Get2DScaleFactorHistogram(Eff_EMu_OR_vs_mu0_eta_vs_el0_eta,Eff_EMu_OR_vs_mu0_eta_vs_el0_eta_MC,h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta);
        TH2D *eff_EMu_OR_vs_mu0_pt_vs_el0_pt = Get2DScaleFactorHistogram(Eff_EMu_OR_vs_mu0_pt_vs_el0_pt,Eff_EMu_OR_vs_mu0_pt_vs_el0_pt_MC,h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt);

        TH2D *eff_DoubleMu_OR_vs_mu1_pt_vs_eta = Get2DScaleFactorHistogram(Eff_DoubleMu_OR_vs_mu1_pt_vs_eta,Eff_DoubleMu_OR_vs_mu1_pt_MC_vs_eta,h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta);
        TH2D *eff_DoubleMu_OR_vs_mu0_pt_vs_eta = Get2DScaleFactorHistogram(Eff_DoubleMu_OR_vs_mu0_pt_vs_eta,Eff_DoubleMu_OR_vs_mu0_pt_MC_vs_eta,h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta);
        TH2D *eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt = Get2DScaleFactorHistogram(Eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt,Eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_MC,h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt);
        TH2D *eff_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta = Get2DScaleFactorHistogram(Eff_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta,Eff_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta_MC,h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta);

	//////////////////////////////

	// Double Electron
        TCanvas *c1 = new TCanvas("c1","c1");
        c1->cd();
        //eff_DoubleEl_OR_vs_el0_pt_vs_eta->GetZaxis()->SetRangeUser(0.90,1.01);
	    c1->SetRightMargin(0.15);
	    eff_DoubleEl_OR_vs_el0_pt_vs_eta->SetLabelSize(0.04, "XYZ");
        eff_DoubleEl_OR_vs_el0_pt_vs_eta->Draw("TEXT E colz");
    	paveCMS->Draw("same");
    	c1->SaveAs("SF_DoubleEl_OR_el0_pt_vs_eta_"+yearstring+"_"+s+".png");
    	c1->Close();

        TCanvas *c2 = new TCanvas("c2","c2");
        c2->cd();
	    //DoubleEl->Draw("same");
        //eff_DoubleEl_OR_vs_el1_pt_vs_eta->GetZaxis()->SetRangeUser(0.90,1.01);
    	c2->SetRightMargin(0.15);
    	eff_DoubleEl_OR_vs_el1_pt_vs_eta->SetLabelSize(0.04, "XYZ");
        eff_DoubleEl_OR_vs_el1_pt_vs_eta->Draw("TEXT E colz");
    	paveCMS->Draw("same");
    	c2->SaveAs("SF_DoubleEl_OR_el1_pt_vs_eta_"+yearstring+"_"+s+".png");
        c2->Close();

        TCanvas *c3 = new TCanvas("c3","c3");
        c3->cd();
        //eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->GetZaxis()->SetRangeUser(0.90,1.01);
    	c3->SetRightMargin(0.15);
    	eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->SetLabelSize(0.04, "XYZ");
        eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->Draw("TEXT E colz");
    	//DoubleEl->Draw("same");
    	paveCMS->Draw("same");
    	c3->SaveAs("SF_DoubleEl_OR_el0_pt_vs_el1_pt_"+yearstring+"_"+s+".png");
        c3->Close();

        TCanvas *c4 = new TCanvas("c4","c4");
        c4->cd();
	    //DoubleEl->Draw("same");
        //eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta->GetZaxis()->SetRangeUser(0.90,1.01);
    	c4->SetRightMargin(0.15);
    	eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta->SetLabelSize(0.04, "XYZ");
        eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta->Draw("TEXT E colz");
    	paveCMS->Draw("same");
    	c4->SaveAs("SF_DoubleEl_OR_el0_eta_vs_el1_eta_"+yearstring+"_"+s+".png");
        c4->Close();

	// EMu

        TCanvas *cc1 = new TCanvas("cc1","cc1");
        cc1->cd();
        //eff_EMu_OR_vs_el0_pt_vs_eta->GetZaxis()->SetRangeUser(0.90,1.01);
    	cc1->SetRightMargin(0.15);
    	eff_EMu_OR_vs_el0_pt_vs_eta->SetLabelSize(0.04, "XYZ");
        eff_EMu_OR_vs_el0_pt_vs_eta->Draw("TEXT E colz");
    	//ElMu->Draw("same");
    	paveCMS->Draw("same");
    	cc1->SaveAs("SF_EMu_OR_el0_pt_vs_eta_"+yearstring+"_"+s+".png");
        cc1->Close();

        TCanvas *cc2 = new TCanvas("cc2","cc2");
        cc2->cd();
	    //ElMu->Draw("same");
        //eff_EMu_OR_vs_mu0_pt_vs_eta->GetZaxis()->SetRangeUser(0.90,1.01);
    	cc2->SetRightMargin(0.15);
    	eff_EMu_OR_vs_mu0_pt_vs_eta->SetLabelSize(0.04, "XYZ");
        eff_EMu_OR_vs_mu0_pt_vs_eta->Draw("TEXT E colz");
    	paveCMS->Draw("same");
    	cc2->SaveAs("SF_EMu_OR_vs_mu0_pt_vs_eta_"+yearstring+"_"+s+".png");
        cc2->Close();

        TCanvas *cc3 = new TCanvas("cc3","cc3");
        cc3->cd();
        //eff_EMu_OR_vs_mu0_eta_vs_el0_eta->GetZaxis()->SetRangeUser(0.90,1.01);
    	cc3->SetRightMargin(0.15);
    	eff_EMu_OR_vs_mu0_eta_vs_el0_eta->SetLabelSize(0.04, "XYZ");
        eff_EMu_OR_vs_mu0_eta_vs_el0_eta->Draw("TEXT E colz");
    	//ElMu->Draw("same");
    	paveCMS->Draw("same");
    	cc3->SaveAs("SF_EMu_OR_vs_mu0_eta_vs_el0_eta_"+yearstring+"_"+s+".png");
        cc3->Close();

        TCanvas *cc4 = new TCanvas("cc4","cc4");
        cc4->cd();
        //eff_EMu_OR_vs_mu0_pt_vs_el0_pt->GetZaxis()->SetRangeUser(0.90,1.01);
    	cc4->SetRightMargin(0.15);
    	eff_EMu_OR_vs_mu0_pt_vs_el0_pt->SetLabelSize(0.04, "XYZ");
        eff_EMu_OR_vs_mu0_pt_vs_el0_pt->Draw("TEXT E colz");
    	//ElMu->Draw("same");
    	paveCMS->Draw("same");
    	cc4->SaveAs("SF_EMu_OR_vs_mu0_pt_vs_el0_pt_"+yearstring+"_"+s+".png");
        cc4->Close();

	// DoubleMu

        TCanvas *ccc1 = new TCanvas("ccc1","ccc1");
        ccc1->cd();
        //eff_DoubleMu_OR_vs_mu1_pt_vs_eta->GetZaxis()->SetRangeUser(0.90,1.01);
    	ccc1->SetRightMargin(0.15);
    	eff_DoubleMu_OR_vs_mu1_pt_vs_eta->SetLabelSize(0.04, "XYZ");
        eff_DoubleMu_OR_vs_mu1_pt_vs_eta->Draw("TEXT E colz");
    	//DoubleMu->Draw("same");
    	paveCMS->Draw("same");
    	ccc1->SaveAs("SF_DoubleMu_OR_mu1_pt_vs_eta_"+yearstring+"_"+s+".png");
        ccc1->Close();

        TCanvas *ccc2 = new TCanvas("ccc2","ccc2");
        ccc2->cd();
        //eff_DoubleMu_OR_vs_mu0_pt_vs_eta->GetZaxis()->SetRangeUser(0.90,1.01);
    	ccc2->SetRightMargin(0.15);
    	eff_DoubleMu_OR_vs_mu0_pt_vs_eta->SetLabelSize(0.04, "XYZ");
        eff_DoubleMu_OR_vs_mu0_pt_vs_eta->Draw("TEXT E colz");
    	//DoubleMu->Draw("same");
    	paveCMS->Draw("same");
    	ccc2->SaveAs("SF_DoubleMu_OR_vs_mu0_pt_vs_eta_"+yearstring+"_"+s+".png");
        ccc2->Close();

        TCanvas *ccc3 = new TCanvas("ccc3","ccc3");
        ccc3->cd();
        //eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->GetZaxis()->SetRangeUser(0.90,1.01);
    	ccc3->SetRightMargin(0.15);
    	eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->SetLabelSize(0.04, "XYZ");
        eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->Draw("TEXT E colz");
    	//DoubleMu->Draw("same");
    	paveCMS->Draw("same");
    	ccc3->SaveAs("SF_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_"+yearstring+"_"+s+".png");
        ccc3->Close();

        TCanvas *ccc4 = new TCanvas("ccc4","ccc4");
        ccc4->cd();
        //eff_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta->GetZaxis()->SetRangeUser(0.90,1.01);
    	ccc4->SetRightMargin(0.15);
    	eff_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta->SetLabelSize(0.04, "XYZ");
        eff_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta->Draw("TEXT E colz");
    	//DoubleMu->Draw("same");
    	paveCMS->Draw("same");
    	ccc4->SaveAs("SF_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta_"+yearstring+"_"+s+".png");
        ccc4->Close();


        // f=new TFile("TriggerSFs_2016_H"+s+".root","RECREATE");
        // f=new TFile("TriggerSFs_2017_F"+s+".root","RECREATE");
        f=new TFile("TriggerSFs_2016"+s+".root","RECREATE");
        // f=new TFile("TriggerSFs_2017"+s+".root","RECREATE");
        // f=new TFile("TriggerSFs_2018_D"+s+".root","RECREATE");
        // f=new TFile("TriggerSFs_2018"+s+".root","RECREATE");
        // f=new TFile("Final_triggerSFs_2018_with_lepton_and_PU_SFs"+s+".root","RECREATE");

        eff_DoubleEl_OR_vs_el0_pt_vs_eta->SetName("h_DoubleEl_OR__X__allMET_el0_pt_vs_eta");
        eff_DoubleEl_OR_vs_el0_pt_vs_eta->Write();
        eff_DoubleEl_OR_vs_el1_pt_vs_eta->SetName("h_DoubleEl_OR__X__allMET_el1_pt_vs_eta");
        eff_DoubleEl_OR_vs_el1_pt_vs_eta->Write();
 	    eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->SetName("h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt");
        eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->Write();
        eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta->SetName("h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta");
        eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta->Write();

        eff_EMu_OR_vs_el0_pt_vs_eta->SetName("h_EMu_OR__X__allMET_el0_pt_vs_eta");
        eff_EMu_OR_vs_el0_pt_vs_eta->Write();
        eff_EMu_OR_vs_mu0_pt_vs_eta->SetName("h_EMu_OR__X__allMET_mu0_pt_vs_eta");
        eff_EMu_OR_vs_mu0_pt_vs_eta->Write();
        eff_EMu_OR_vs_mu0_eta_vs_el0_eta->SetName("h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta");
        eff_EMu_OR_vs_mu0_eta_vs_el0_eta->Write();
        eff_EMu_OR_vs_mu0_pt_vs_el0_pt->SetName("h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt");
        eff_EMu_OR_vs_mu0_pt_vs_el0_pt->Write();

        eff_DoubleMu_OR_vs_mu1_pt_vs_eta->SetName("h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta");
        eff_DoubleMu_OR_vs_mu1_pt_vs_eta->Write();
        eff_DoubleMu_OR_vs_mu0_pt_vs_eta->SetName("h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta");
        eff_DoubleMu_OR_vs_mu0_pt_vs_eta->Write();
        eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->SetName("h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt");
        eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->Write();
        eff_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta->SetName("h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta");
        eff_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta->Write();


}
