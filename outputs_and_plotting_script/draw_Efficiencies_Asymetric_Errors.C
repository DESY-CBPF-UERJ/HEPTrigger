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
#include "TEfficiency.h"
#include "../include/setTDRStyle_teliko.C"

TCanvas* Create_Canvas(TEfficiency* data, TEfficiency* mc, string stream){


        gROOT->LoadMacro("../include/setTDRStyle_teliko.C");
        setTDRStyle_teliko();

        // CMS box for plotting the canvases    ///////
        TPaveText *paveCMS = new TPaveText(0.15,0.96,0.91,0.99,"NDC");
        //paveCMS->AddText("#bf{CMS #it{Preliminary} 2016}        35.9 fb^{-1}    (13 TeV)");
        //paveCMS->AddText("#bf{CMS #it{Preliminary} 2017}        41.5 fb^{-1}    (13 TeV)");
        paveCMS->AddText("#bf{CMS #it{Preliminary} 2018}        59.8 fb^{-1}    (13 TeV)");
        paveCMS->SetFillColor(0);
        paveCMS->SetBorderSize(0);
        paveCMS->SetTextSize(0.04);
        paveCMS->SetTextFont(42);


        TPaveText *DoubleEl = new TPaveText(.5,.2,.85,.3,"NDC");
        DoubleEl->AddText("Double Electron Stream");
        DoubleEl->SetTextSize(0.035);
        DoubleEl->SetFillColor(0);
        DoubleEl->SetFillStyle(0);
        DoubleEl->SetBorderSize(0);
        DoubleEl->SetTextAlign(13);
        DoubleEl->SetTextFont(12);
        DoubleEl->SetTextColor(kBlack);

        TPaveText *ElMu = new TPaveText(.5,.2,.85,.3,"NDC");
        ElMu->AddText("Electron-Muon Stream");
        ElMu->SetTextSize(0.035);
        ElMu->SetFillColor(0);
        ElMu->SetFillStyle(0);
        ElMu->SetBorderSize(0);
        ElMu->SetTextAlign(13);
        ElMu->SetTextFont(12);
        ElMu->SetTextColor(kBlack);

        TPaveText *DoubleMu = new TPaveText(.5,.2,.85,.3,"NDC");
        DoubleMu->AddText("Double Muon Stream");
        DoubleMu->SetTextSize(0.035);
        DoubleMu->SetFillColor(0);
        DoubleMu->SetFillStyle(0);
        DoubleMu->SetBorderSize(0);
        DoubleMu->SetTextAlign(13);
        DoubleMu->SetTextFont(12);
        DoubleMu->SetTextColor(kBlack);

        TLegend *l = new TLegend(.5, .3, .7, .45);
        l->AddEntry(data,"Data","lp");
        l->AddEntry(mc,"MC ","lp");
        l->SetTextSize(0.03);

        TCanvas *c = new TCanvas("c1","c");
        c->cd();
        c->SetGrid();
        mc->SetMarkerColor(kRed);
        mc->SetLineColor(kRed);
        mc->Draw();
        mc->Paint("");
        char t1[50];
	char t2[50];
        char t3[50];
        sprintf (t1,";");
        sprintf (t2,"%s",mc->GetPaintedGraph()->GetXaxis()->GetTitle());
        sprintf (t3,";Efficiency");
        strcat(t1,t2);
        strcat(t1,t3);
	mc->SetTitle(t1);
        TGraphAsymmErrors* gr = (TGraphAsymmErrors*)mc->GetPaintedGraph();
        gr->Draw("ep");
        gr->SetMinimum(0.5);
        gr->SetMaximum(1.05);
        TH1D* temp =  (TH1D*)(mc->GetCopyTotalHisto());
        gr->GetXaxis()->SetRangeUser( temp->GetXaxis()->GetXmin(), temp->GetXaxis()->GetXmax() );
        gr->Draw("ep");
        gr->GetYaxis()->SetTitle("Efficiency");
        //eff_DoubleEl_OR_vs_el0_pt_MC->Draw();
        data->Draw("same");
        data->Paint("");
        TGraphAsymmErrors* gr2 = (TGraphAsymmErrors*)data->GetPaintedGraph();
        gr2->Draw("ep same");
        gr2->GetYaxis()->SetTitle("Efficiency");
	if(stream.compare("ee") == 0)        DoubleEl->Draw("same");
        if(stream.compare("em") == 0)        ElMu->Draw("same");
        if(stream.compare("mm") == 0)        DoubleMu->Draw("same");
        l->Draw("same");
        paveCMS->Draw("same");
        c->Update();

	return c;

}


void draw_Efficiencies_Asymetric_Errors()
{

	//////////////////////////////////////////////
	//	DATA		//////////////////////
	//////////////////////////////////////////////

	TFile *f = new TFile("Final_Trigger_SF_results_using_DESY_ntuples/MET_Dataset_2016_All_Runs.root","READ");
        //TFile *f = new TFile("Final_Trigger_SF_results_using_DESY_ntuples/MET_Dataset_2017_All_Runs.root","READ");
        //TFile *f = new TFile("Final_Trigger_SF_results_using_DESY_ntuples/MET_Dataset_2018_All_Runs.root","READ");

	f->cd();

	//	Double Electron stream (OR of Single & Double electron triggers)	///////////////

  	TEfficiency* eff_DoubleEl_OR_vs_el0_pt  = (TEfficiency*)f->Get("h_DoubleEl_OR__X__allMET_el0_pt_TEff");
        TEfficiency* eff_DoubleEl_OR_vs_el1_pt  = (TEfficiency*)f->Get("h_DoubleEl_OR__X__allMET_el1_pt_TEff");
        TEfficiency* eff_DoubleEl_OR_vs_el0_eta = (TEfficiency*)f->Get("h_DoubleEl_OR__X__allMET_el0_eta_TEff");
        TEfficiency* eff_DoubleEl_OR_vs_el1_eta = (TEfficiency*)f->Get("h_DoubleEl_OR__X__allMET_el1_eta_TEff");
        TEfficiency* eff_DoubleEl_OR_vs_nPV     = (TEfficiency*)f->Get("h_DoubleEl_OR__X__allMET_nPV_TEff");
        TEfficiency* eff_DoubleEl_OR_vs_met     = (TEfficiency*)f->Get("h_DoubleEl_OR__X__allMET_met_TEff");
        TEfficiency* eff_DoubleEl_OR_vs_njets   = (TEfficiency*)f->Get("h_DoubleEl_OR__X__allMET_njets_TEff");

	//	EMu stream (OR of Single & Double electron triggers)	///////////////

        TEfficiency* eff_EMu_OR_vs_el0_pt      = (TEfficiency*)f->Get("h_EMu_OR__X__allMET_el0_pt_TEff");
        TEfficiency* eff_EMu_OR_vs_mu0_pt      = (TEfficiency*)f->Get("h_EMu_OR__X__allMET_mu0_pt_TEff");
        TEfficiency* eff_EMu_OR_vs_el0_eta     = (TEfficiency*)f->Get("h_EMu_OR__X__allMET_el0_eta_TEff");
        TEfficiency* eff_EMu_OR_vs_mu0_eta     = (TEfficiency*)f->Get("h_EMu_OR__X__allMET_mu0_eta_TEff");
        TEfficiency* eff_EMu_OR_vs_nPV         = (TEfficiency*)f->Get("h_EMu_OR__X__allMET_nPV_TEff");
        TEfficiency* eff_EMu_OR_vs_met         = (TEfficiency*)f->Get("h_EMu_OR__X__allMET_met_TEff");
        TEfficiency* eff_EMu_OR_vs_njets       = (TEfficiency*)f->Get("h_EMu_OR__X__allMET_njets_TEff");

	//	Double Muon stream (OR of Single & Double electron triggers)	///////////////

        TEfficiency* eff_DoubleMu_OR_vs_mu0_pt       = (TEfficiency*)f->Get("h_DoubleMu_OR__X__allMET_mu0_pt_TEff");
        TEfficiency* eff_DoubleMu_OR_vs_mu1_pt       = (TEfficiency*)f->Get("h_DoubleMu_OR__X__allMET_mu1_pt_TEff");
        TEfficiency* eff_DoubleMu_OR_vs_mu0_eta      = (TEfficiency*)f->Get("h_DoubleMu_OR__X__allMET_mu0_eta_TEff");
        TEfficiency* eff_DoubleMu_OR_vs_mu1_eta      = (TEfficiency*)f->Get("h_DoubleMu_OR__X__allMET_mu1_eta_TEff");
        TEfficiency* eff_DoubleMu_OR_vs_nPV          = (TEfficiency*)f->Get("h_DoubleMu_OR__X__allMET_nPV_TEff");
        TEfficiency* eff_DoubleMu_OR_vs_met          = (TEfficiency*)f->Get("h_DoubleMu_OR__X__allMET_met_TEff");
        TEfficiency* eff_DoubleMu_OR_vs_njets        = (TEfficiency*)f->Get("h_DoubleMu_OR__X__allMET_njets_TEff");

	///////////////////

	//////////////////////////////////////////////
	//	MC		//////////////////////
	//////////////////////////////////////////////


        TFile *f_MC  = new TFile("Final_Trigger_SF_results_using_DESY_ntuples/2016_TT_Dileptonic_MC.root","READ");
        //TFile *f_MC  = new TFile("Final_Trigger_SF_results_using_DESY_ntuples/2017_TT_Dileptonic_MC.root","READ");
        //TFile *f_MC  = new TFile("Final_Trigger_SF_results_using_DESY_ntuples/2018_TT_Dileptonic_MC.root","READ");
     	f_MC->cd();

        TEfficiency* eff_DoubleEl_OR_vs_el0_pt_MC  = (TEfficiency*)f_MC->Get("h_DoubleEl_OR__X__allMET_el0_pt_TEff");
        TEfficiency* eff_DoubleEl_OR_vs_el1_pt_MC  = (TEfficiency*)f_MC->Get("h_DoubleEl_OR__X__allMET_el1_pt_TEff");
        TEfficiency* eff_DoubleEl_OR_vs_el0_eta_MC = (TEfficiency*)f_MC->Get("h_DoubleEl_OR__X__allMET_el0_eta_TEff");
        TEfficiency* eff_DoubleEl_OR_vs_el1_eta_MC = (TEfficiency*)f_MC->Get("h_DoubleEl_OR__X__allMET_el1_eta_TEff");
        TEfficiency* eff_DoubleEl_OR_vs_nPV_MC     = (TEfficiency*)f_MC->Get("h_DoubleEl_OR__X__allMET_nPV_TEff");
        TEfficiency* eff_DoubleEl_OR_vs_met_MC     = (TEfficiency*)f_MC->Get("h_DoubleEl_OR__X__allMET_met_TEff");
        TEfficiency* eff_DoubleEl_OR_vs_njets_MC   = (TEfficiency*)f_MC->Get("h_DoubleEl_OR__X__allMET_njets_TEff");

        //      EMu stream (OR of Single & Double electron triggers)    ///////////////

        TEfficiency* eff_EMu_OR_vs_el0_pt_MC      = (TEfficiency*)f_MC->Get("h_EMu_OR__X__allMET_el0_pt_TEff");
        TEfficiency* eff_EMu_OR_vs_mu0_pt_MC      = (TEfficiency*)f_MC->Get("h_EMu_OR__X__allMET_mu0_pt_TEff");
        TEfficiency* eff_EMu_OR_vs_el0_eta_MC     = (TEfficiency*)f_MC->Get("h_EMu_OR__X__allMET_el0_eta_TEff");
        TEfficiency* eff_EMu_OR_vs_mu0_eta_MC     = (TEfficiency*)f_MC->Get("h_EMu_OR__X__allMET_mu0_eta_TEff");
        TEfficiency* eff_EMu_OR_vs_nPV_MC         = (TEfficiency*)f_MC->Get("h_EMu_OR__X__allMET_nPV_TEff");
        TEfficiency* eff_EMu_OR_vs_met_MC         = (TEfficiency*)f_MC->Get("h_EMu_OR__X__allMET_met_TEff");
        TEfficiency* eff_EMu_OR_vs_njets_MC       = (TEfficiency*)f_MC->Get("h_EMu_OR__X__allMET_njets_TEff");

        //      Double Muon stream (OR of Single & Double electron triggers)    ///////////////

        TEfficiency* eff_DoubleMu_OR_vs_mu0_pt_MC       = (TEfficiency*)f_MC->Get("h_DoubleMu_OR__X__allMET_mu0_pt_TEff");
        TEfficiency* eff_DoubleMu_OR_vs_mu1_pt_MC       = (TEfficiency*)f_MC->Get("h_DoubleMu_OR__X__allMET_mu1_pt_TEff");
        TEfficiency* eff_DoubleMu_OR_vs_mu0_eta_MC      = (TEfficiency*)f_MC->Get("h_DoubleMu_OR__X__allMET_mu0_eta_TEff");
        TEfficiency* eff_DoubleMu_OR_vs_mu1_eta_MC      = (TEfficiency*)f_MC->Get("h_DoubleMu_OR__X__allMET_mu1_eta_TEff");
        TEfficiency* eff_DoubleMu_OR_vs_nPV_MC          = (TEfficiency*)f_MC->Get("h_DoubleMu_OR__X__allMET_nPV_TEff");
        TEfficiency* eff_DoubleMu_OR_vs_met_MC          = (TEfficiency*)f_MC->Get("h_DoubleMu_OR__X__allMET_met_TEff");
        TEfficiency* eff_DoubleMu_OR_vs_njets_MC        = (TEfficiency*)f_MC->Get("h_DoubleMu_OR__X__allMET_njets_TEff");


        TCanvas *c = new TCanvas("c1","c");
        c->cd();
        eff_DoubleEl_OR_vs_el0_pt_MC->Draw();
	double x,y;
        eff_DoubleEl_OR_vs_el0_pt_MC->Paint("");
        TGraphAsymmErrors* gr2 = (TGraphAsymmErrors*)eff_DoubleEl_OR_vs_el0_pt_MC->GetPaintedGraph();
        gr2->GetPoint(0,x,y);
        cout<<"x = "<<x<<", y = "<<y<<", error low = "<<gr2->GetErrorYlow(0)<<", error high = "<<gr2->GetErrorYhigh(0)<<endl;
        gr2->GetPoint(1,x,y);
        cout<<"x = "<<x<<", y = "<<y<<", error low = "<<gr2->GetErrorYlow(1)<<", error high = "<<gr2->GetErrorYhigh(1)<<endl;
        gr2->GetPoint(2,x,y);
        cout<<"x = "<<x<<", y = "<<y<<", error low = "<<gr2->GetErrorYlow(2)<<", error high = "<<gr2->GetErrorYhigh(2)<<endl;
        gr2->GetPoint(3,x,y);
        cout<<"x = "<<x<<", y = "<<y<<", error low = "<<gr2->GetErrorYlow(3)<<", error high = "<<gr2->GetErrorYhigh(3)<<endl;
        gr2->GetPoint(4,x,y);
        cout<<"x = "<<x<<", y = "<<y<<", error low = "<<gr2->GetErrorYlow(4)<<", error high = "<<gr2->GetErrorYhigh(4)<<endl;




	TCanvas *c1 = Create_Canvas(eff_DoubleEl_OR_vs_el0_pt,eff_DoubleEl_OR_vs_el0_pt_MC,"ee");
	c1->SaveAs("eff_DoubleEl_OR_vs_el0_pt.png");
        TCanvas *c2 = Create_Canvas(eff_DoubleEl_OR_vs_el1_pt,eff_DoubleEl_OR_vs_el1_pt_MC,"ee");
        c2->SaveAs("eff_DoubleEl_OR_vs_el1_pt.png");
        TCanvas *c3 = Create_Canvas(eff_DoubleEl_OR_vs_el0_eta,eff_DoubleEl_OR_vs_el0_eta_MC,"ee");
        c3->SaveAs("eff_DoubleEl_OR_vs_el0_eta.png");
        TCanvas *c4 = Create_Canvas(eff_DoubleEl_OR_vs_el1_eta,eff_DoubleEl_OR_vs_el1_eta_MC,"ee");
        c4->SaveAs("eff_DoubleEl_OR_vs_el1_eta.png");
        TCanvas *c5 = Create_Canvas(eff_DoubleEl_OR_vs_nPV,eff_DoubleEl_OR_vs_nPV_MC,"ee");
        c5->SaveAs("eff_DoubleEl_OR_vs_nPV.png");
        TCanvas *c6 = Create_Canvas(eff_DoubleEl_OR_vs_met,eff_DoubleEl_OR_vs_met_MC,"ee");
        c6->SaveAs("eff_DoubleEl_OR_vs_met.png");
        TCanvas *c7 = Create_Canvas(eff_DoubleEl_OR_vs_njets,eff_DoubleEl_OR_vs_njets_MC,"ee");
        c7->SaveAs("eff_DoubleEl_OR_vs_njets.png");

        TCanvas *c8 = Create_Canvas(eff_EMu_OR_vs_el0_pt,eff_EMu_OR_vs_el0_pt_MC,"em");
        c8->SaveAs("eff_EMu_OR_vs_el0_pt.png");
        TCanvas *c9 = Create_Canvas(eff_EMu_OR_vs_el0_eta,eff_EMu_OR_vs_el0_eta_MC,"em");
        c9->SaveAs("eff_EMu_OR_vs_el0_eta.png");
        TCanvas *c10 = Create_Canvas(eff_EMu_OR_vs_mu0_pt,eff_EMu_OR_vs_mu0_pt_MC,"em");
        c10->SaveAs("eff_EMu_OR_vs_mu0_pt.png");
        TCanvas *c11 = Create_Canvas(eff_EMu_OR_vs_mu0_eta,eff_EMu_OR_vs_mu0_eta_MC,"em");
        c11->SaveAs("eff_EMu_OR_vs_mu0_eta.png");
        TCanvas *c12 = Create_Canvas(eff_EMu_OR_vs_nPV,eff_EMu_OR_vs_nPV_MC,"em");
        c12->SaveAs("eff_EMu_OR_vs_nPV.png");
        TCanvas *c13 = Create_Canvas(eff_EMu_OR_vs_met,eff_EMu_OR_vs_met_MC,"em");
        c13->SaveAs("eff_EMu_OR_vs_met.png");
        TCanvas *c14 = Create_Canvas(eff_EMu_OR_vs_njets,eff_EMu_OR_vs_njets_MC,"em");
        c14->SaveAs("eff_EMu_OR_vs_njets.png");

        TCanvas *c15 = Create_Canvas(eff_DoubleMu_OR_vs_mu0_pt,eff_DoubleMu_OR_vs_mu0_pt_MC,"mm");
        c15->SaveAs("eff_DoubleMu_OR_vs_mu0_pt.png");
        TCanvas *c16 = Create_Canvas(eff_DoubleMu_OR_vs_mu1_pt,eff_DoubleMu_OR_vs_mu1_pt_MC,"mm");
        c16->SaveAs("eff_DoubleMu_OR_vs_mu1_pt.png");
        TCanvas *c17 = Create_Canvas(eff_DoubleMu_OR_vs_mu0_eta,eff_DoubleMu_OR_vs_mu0_eta_MC,"mm");
        c17->SaveAs("eff_DoubleMu_OR_vs_mu0_eta.png");
        TCanvas *c18 = Create_Canvas(eff_DoubleMu_OR_vs_mu1_eta,eff_DoubleMu_OR_vs_mu1_eta_MC,"mm");
        c18->SaveAs("eff_DoubleMu_OR_vs_mu1_eta.png");
        TCanvas *c19 = Create_Canvas(eff_DoubleMu_OR_vs_nPV,eff_DoubleMu_OR_vs_nPV_MC,"mm");
        c19->SaveAs("eff_DoubleMu_OR_vs_nPV.png");
        TCanvas *c20 = Create_Canvas(eff_DoubleMu_OR_vs_met,eff_DoubleMu_OR_vs_met_MC,"mm");
        c20->SaveAs("eff_DoubleMu_OR_vs_met.png");
        TCanvas *c21 = Create_Canvas(eff_DoubleMu_OR_vs_njets,eff_DoubleMu_OR_vs_njets_MC,"mm");
        c21->SaveAs("eff_DoubleMu_OR_vs_njets.png");
}
