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


void Correlations(TH2D* h_corr,char name[50]){

	    double Xeff_lep,Xeff_met,Xeff_lepXmet,Xeff_lep_err,Xeff_met_err,Xeff_lepXmet_err,Xcorr,Xcorr_err;
    	TH2D* h_lepFired 	   = (TH2D*)h_corr->Clone();
    	TH2D* h_metFired 	   = (TH2D*)h_corr->Clone();
    	TH2D* h_lepXmetFired 	   = (TH2D*)h_corr->Clone();
    	TH2D* h_total              = (TH2D*)h_corr->Clone();


    	// * a. set 0s where appropriate
    	h_lepFired->SetBinContent(h_lepFired->GetXaxis()->FindBin("Not Fired"), h_lepFired->GetYaxis()->FindBin("Not Fired"), 0);
    	h_lepFired->SetBinContent(h_lepFired->GetXaxis()->FindBin("Not Fired"), h_lepFired->GetYaxis()->FindBin("Fired"), 0);
    	h_metFired->SetBinContent(h_metFired->GetXaxis()->FindBin("Fired"), h_metFired->GetYaxis()->FindBin("Not Fired"), 0);
    	h_metFired->SetBinContent(h_metFired->GetXaxis()->FindBin("Not Fired"), h_metFired->GetYaxis()->FindBin("Not Fired"), 0);
    	h_lepXmetFired->SetBinContent(h_lepXmetFired->GetXaxis()->FindBin("Not Fired"), h_lepXmetFired->GetYaxis()->FindBin("Not Fired"), 0);
    	h_lepXmetFired->SetBinContent(h_lepXmetFired->GetXaxis()->FindBin("Not Fired"), h_lepXmetFired->GetYaxis()->FindBin("Fired"), 0);
    	h_lepXmetFired->SetBinContent(h_lepXmetFired->GetXaxis()->FindBin("Fired"), h_lepXmetFired->GetYaxis()->FindBin("Not Fired"), 0);

    	// * b. rebin
    	h_lepFired->Rebin2D(2, 2);
    	h_metFired->Rebin2D(2, 2);
    	h_lepXmetFired->Rebin2D(2, 2);
    	h_total->Rebin2D(2, 2);

    	// * c. get efficiencies
    	TEfficiency *tEff_lep = new TEfficiency(*h_lepFired, *h_total);
    	TEfficiency *tEff_met = new TEfficiency(*h_metFired, *h_total);
    	TEfficiency *tEff_lepXmet = new TEfficiency(*h_lepXmetFired, *h_total);

    	Xeff_lep = tEff_lep->GetEfficiency( tEff_lep->GetTotalHistogram()->GetBin(1,1) );
    	Xeff_met = tEff_met->GetEfficiency( tEff_met->GetTotalHistogram()->GetBin(1,1) );
    	Xeff_lepXmet = tEff_lepXmet->GetEfficiency( tEff_lepXmet->GetTotalHistogram()->GetBin(1,1) );
    	Xeff_lep_err = tEff_lep->GetEfficiencyErrorLow( tEff_lep->GetTotalHistogram()->GetBin(1,1) ) > tEff_lep->GetEfficiencyErrorUp( tEff_lep->GetTotalHistogram()->GetBin(1,1) ) ? tEff_lep->GetEfficiencyErrorLow( tEff_lep->GetTotalHistogram()->GetBin(1,1) ) : tEff_lep->GetEfficiencyErrorUp( tEff_lep->GetTotalHistogram()->GetBin(1,1) );
    	Xeff_met_err = tEff_met->GetEfficiencyErrorLow( tEff_met->GetTotalHistogram()->GetBin(1,1) ) > tEff_met->GetEfficiencyErrorUp( tEff_met->GetTotalHistogram()->GetBin(1,1) ) ? tEff_met->GetEfficiencyErrorLow( tEff_met->GetTotalHistogram()->GetBin(1,1) ) : tEff_met->GetEfficiencyErrorUp( tEff_met->GetTotalHistogram()->GetBin(1,1) );
   	    Xeff_lepXmet_err = tEff_lepXmet->GetEfficiencyErrorLow( tEff_lepXmet->GetTotalHistogram()->GetBin(1,1) ) > tEff_lepXmet->GetEfficiencyErrorUp( tEff_lepXmet->GetTotalHistogram()->GetBin(1,1) ) ? tEff_lepXmet->GetEfficiencyErrorLow( tEff_lepXmet->GetTotalHistogram()->GetBin(1,1) ) : tEff_lepXmet->GetEfficiencyErrorUp( tEff_lepXmet->GetTotalHistogram()->GetBin(1,1) );

        // std::cout<<Xeff_lep<<" "<<Xeff_met<<" "<<Xeff_lepXmet<<std::endl;

    	Xcorr = Xeff_lep * Xeff_met / Xeff_lepXmet;
    	Xcorr_err = Xcorr * sqrt( (Xeff_lep_err/Xeff_lep)*(Xeff_lep_err/Xeff_lep) + (Xeff_met_err/Xeff_met)*(Xeff_met_err/Xeff_met) + (Xeff_lepXmet_err/Xeff_lepXmet)*(Xeff_lepXmet_err/Xeff_lepXmet) );

    	cout << "Correlation between "  << name << " = \t" <<  Xcorr << " +/- " << Xcorr_err << endl;
    	cout << "Difference "  << name << " = \t" <<  1.-Xcorr << " +/- " << Xcorr_err << endl;

}


void Compute_correlations()
{

    // gROOT->LoadMacro("/afs/cern.ch/work/c/ckoraka/codes/setTDRStyle_teliko.C");
    // setTDRStyle_teliko();
    // setTDRStyle();

    // CMS box for plotting the canvases    ///////
    // TPaveText *paveCMS = new TPaveText(0.15,0.96,0.91,0.99,"NDC");
    //paveCMS->AddText("#bf{CMS #it{Preliminary} 2016}        35.9 fb^{-1}    (13 TeV)");
    // paveCMS->AddText("#bf{CMS #it{Preliminary} 2017}        41.5 fb^{-1}    (13 TeV)");
    // paveCMS->AddText("#bf{CMS #it{Preliminary} 2018}        59.8 fb^{-1}    (13 TeV)");
    // paveCMS->SetFillColor(0);
    // paveCMS->SetBorderSize(0);
    // paveCMS->SetTextSize(0.04);
    // paveCMS->SetTextFont(42);


	//////////////////////////////////////////////
	//	MC		//////////////////////
	//////////////////////////////////////////////

    //TFile *f_MC  = new TFile("Final_Trigger_SF_results_using_DESY_ntuples/2016_TT_Dileptonic_MC.root","READ");
    //TFile *f_MC  = new TFile("Final_Trigger_SF_results_using_DESY_ntuples/2017_TT_Dileptonic_MC.root","READ");
    // TFile *f_MC  = new TFile("Final_Trigger_SF_results_using_DESY_ntuples/2018_TT_Dileptonic_MC.root","READ");
    // TFile *f_MC  = new TFile("../TriggerFiles_2016/MC/outfile_2016.root","READ");
    // TFile *f_MC  = new TFile("../TriggerFiles_2017/MC/outfile_2017.root","READ");
    TFile *f_MC  = new TFile("../TriggerFiles_2018/MC/outfile_2018.root","READ");
 	f_MC->cd();

	char MET_triggers_2016[21][100] = {
        "h_HLT_DoubleEl_OR__vs__HLT_MET200",
        "h_HLT_DoubleEl_OR__vs__HLT_PFMET120_PFMHT120_IDTight",
        "h_HLT_DoubleEl_OR__vs__HLT_PFMET170_HBHECleaned",
        "h_HLT_DoubleEl_OR__vs__HLT_PFMET300",
        "h_HLT_DoubleEl_OR__vs__HLT_PFHT300_PFMET110",
        "h_HLT_DoubleEl_OR__vs__HLT_PFMETNoMu120_PFMHTNoMu120_IDTight",
        "h_HLT_DoubleEl_OR__vs__HLT_allMET",
    	"h_HLT_EMu_OR__vs__HLT_MET200",
    	"h_HLT_EMu_OR__vs__HLT_PFMET120_PFMHT120_IDTight",
    	"h_HLT_EMu_OR__vs__HLT_PFMET170_HBHECleaned",
    	"h_HLT_EMu_OR__vs__HLT_PFMET300",
    	"h_HLT_EMu_OR__vs__HLT_PFHT300_PFMET110",
    	"h_HLT_EMu_OR__vs__HLT_PFMETNoMu120_PFMHTNoMu120_IDTight",
    	"h_HLT_EMu_OR__vs__HLT_allMET",
        "h_HLT_DoubleMu_OR__vs__HLT_MET200",
        "h_HLT_DoubleMu_OR__vs__HLT_PFMET120_PFMHT120_IDTight",
        "h_HLT_DoubleMu_OR__vs__HLT_PFMET170_HBHECleaned",
        "h_HLT_DoubleMu_OR__vs__HLT_PFMET300",
        "h_HLT_DoubleMu_OR__vs__HLT_PFHT300_PFMET110",
        "h_HLT_DoubleMu_OR__vs__HLT_PFMETNoMu120_PFMHTNoMu120_IDTight",
        "h_HLT_DoubleMu_OR__vs__HLT_allMET"
    };

    char MET_triggers_2017[18][100] = {
        "h_HLT_DoubleEl_OR__vs__HLT_PFHT500_PFMET100_PFMHT100_IDTight",
        "h_HLT_DoubleEl_OR__vs__HLT_PFHT700_PFMET85_PFMHT85_IDTight",
        "h_HLT_DoubleEl_OR__vs__HLT_PFHT800_PFMET75_PFMHT75_IDTight",
        "h_HLT_DoubleEl_OR__vs__HLT_PFMET120_PFMHT120_IDTight",
        "h_HLT_DoubleEl_OR__vs__HLT_PFMET250_HBHECleaned",
        "h_HLT_DoubleEl_OR__vs__HLT_allMET",
        "h_HLT_EMu_OR__vs__HLT_PFHT500_PFMET100_PFMHT100_IDTight",
        "h_HLT_EMu_OR__vs__HLT_PFHT700_PFMET85_PFMHT85_IDTight",
        "h_HLT_EMu_OR__vs__HLT_PFHT800_PFMET75_PFMHT75_IDTight",
        "h_HLT_EMu_OR__vs__HLT_PFMET120_PFMHT120_IDTight",
        "h_HLT_EMu_OR__vs__HLT_PFMET250_HBHECleaned",
        "h_HLT_EMu_OR__vs__HLT_allMET",
    	"h_HLT_DoubleMu_OR__vs__HLT_PFHT500_PFMET100_PFMHT100_IDTight",
    	"h_HLT_DoubleMu_OR__vs__HLT_PFHT700_PFMET85_PFMHT85_IDTight",
    	"h_HLT_DoubleMu_OR__vs__HLT_PFHT800_PFMET75_PFMHT75_IDTight",
    	"h_HLT_DoubleMu_OR__vs__HLT_PFMET120_PFMHT120_IDTight",
    	"h_HLT_DoubleMu_OR__vs__HLT_PFMET250_HBHECleaned",
    	"h_HLT_DoubleMu_OR__vs__HLT_allMET"
    };

    char MET_triggers_2018[30][100] = {
        "h_HLT_DoubleEl_OR__vs__HLT_PFMET120_PFMHT120_IDTight",
        "h_HLT_DoubleEl_OR__vs__HLT_PFMET200_HBHE_BeamHaloCleaned",
        "h_HLT_DoubleEl_OR__vs__HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned",
        "h_HLT_DoubleEl_OR__vs__HLT_PFMETNoMu120_PFMHTNoMu120_IDTight",
        "h_HLT_DoubleEl_OR__vs__HLT_PFMET120_PFMHT120_IDTight_PFHT60",
        "h_HLT_DoubleEl_OR__vs__HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60",
        "h_HLT_DoubleEl_OR__vs__HLT_PFHT500_PFMET100_PFMHT100_IDTight",
        "h_HLT_DoubleEl_OR__vs__HLT_PFHT700_PFMET85_PFMHT85_IDTight",
        "h_HLT_DoubleEl_OR__vs__HLT_PFHT800_PFMET75_PFMHT75_IDTight",
        "h_HLT_DoubleEl_OR__vs__HLT_allMET",
        "h_HLT_EMu_OR__vs__HLT_PFMET120_PFMHT120_IDTight",
        "h_HLT_EMu_OR__vs__HLT_PFMET200_HBHE_BeamHaloCleaned",
        "h_HLT_EMu_OR__vs__HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned",
        "h_HLT_EMu_OR__vs__HLT_PFMETNoMu120_PFMHTNoMu120_IDTight",
        "h_HLT_EMu_OR__vs__HLT_PFMET120_PFMHT120_IDTight_PFHT60",
        "h_HLT_EMu_OR__vs__HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60",
        "h_HLT_EMu_OR__vs__HLT_PFHT500_PFMET100_PFMHT100_IDTight",
        "h_HLT_EMu_OR__vs__HLT_PFHT700_PFMET85_PFMHT85_IDTight",
        "h_HLT_EMu_OR__vs__HLT_PFHT800_PFMET75_PFMHT75_IDTight",
        "h_HLT_EMu_OR__vs__HLT_allMET",
    	"h_HLT_DoubleMu_OR__vs__HLT_PFMET120_PFMHT120_IDTight",
    	"h_HLT_DoubleMu_OR__vs__HLT_PFMET200_HBHE_BeamHaloCleaned",
    	"h_HLT_DoubleMu_OR__vs__HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned",
    	"h_HLT_DoubleMu_OR__vs__HLT_PFMETNoMu120_PFMHTNoMu120_IDTight",
    	"h_HLT_DoubleMu_OR__vs__HLT_PFMET120_PFMHT120_IDTight_PFHT60",
    	"h_HLT_DoubleMu_OR__vs__HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60",
    	"h_HLT_DoubleMu_OR__vs__HLT_PFHT500_PFMET100_PFMHT100_IDTight",
    	"h_HLT_DoubleMu_OR__vs__HLT_PFHT700_PFMET85_PFMHT85_IDTight",
    	"h_HLT_DoubleMu_OR__vs__HLT_PFHT800_PFMET75_PFMHT75_IDTight",
        "h_HLT_DoubleMu_OR__vs__HLT_allMET"
    };


	for(int i=0; i<30;++i){
		// if(!(i==6 || i==13 || i ==20) ) continue; // 2016
		// if(!(i==5 || i==11 || i ==17) ) continue; // 2017
        if(!(i==9 || i==19 || i ==29) ) continue; // 2018

        // TH2D* correletion  = (TH2D*)f_MC->Get(MET_triggers_2016[i]);
        // TH2D* correletion  = (TH2D*)f_MC->Get(MET_triggers_2017[i]);
        TH2D* correletion  = (TH2D*)f_MC->Get(MET_triggers_2018[i]);
        // std::cout<<correletion->GetName()<<std::endl;
        //TCanvas *c = new TCanvas("c1","c1");
        //TPaveText *trig = new TPaveText(.08,.05,.90,.1,"NDC");
        //trig->AddText(MET_triggers_2017[i]);
        //trig->SetTextSize(0.027);
        //trig->SetFillColor(0);
        //trig->SetFillStyle(0);
        //trig->SetBorderSize(0);
        //trig->SetTextAlign(13);
        //trig->SetTextColor(kBlack);
        //correletion->SetLabelSize(0.025, "Z");
        //correletion->Draw("TEXT E colz");
        //paveCMS->Draw("same");
        //trig->Draw("same");
        //TString s = MET_triggers_2017[i];
        //c->SaveAs(s+".png");
        // Correlations(correletion,MET_triggers_2016[i]);
        // Correlations(correletion,MET_triggers_2017[i]);
        Correlations(correletion,MET_triggers_2018[i]);
	}


}
