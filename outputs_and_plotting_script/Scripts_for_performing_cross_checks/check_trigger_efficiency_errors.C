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

double BetaInverse(double x,double p, double q)
{
	double result(0.0);
  	double dy = 0.001;
  	double eMin = 100;
  	for(int i=0;i<1000;i++){
      		double y = i*dy;
      		double e = fabs(TMath::BetaIncomplete(y,p,q)-x);
      		if (e<eMin){
          		eMin = e;
          		result = y;
        	}
    	}
  	return result;
}


void check_trigger_efficiency_errors()
{

 	gROOT->LoadMacro("/afs/cern.ch/work/c/ckoraka/codes/setTDRStyle_teliko.C");
        setTDRStyle_teliko();

	//////////////////////////////////////////////
	//	DATA		//////////////////////
	//////////////////////////////////////////////

	TFile *f = new TFile("/afs/cern.ch/work/c/ckoraka/For_ttH_Hbb_DL_Trigger_ScaleFactors/setup_for_github/CMSSW_9_4_13_patch2/src/TopAnalysis/ttH-triggerEff-Legacy_datasets/outputs_and_plotting_script/Final_Trigger_SF_results_using_DESY_ntuples/2016_TT_Dileptonic_MC.root","READ");
	f->cd();

	//	Double Electron stream (OR of Single & Double electron triggers)	///////////////

        TH1D* h_HLT_allMET_elStreamDL_el0_pt = (TH1D*) f->Get("h_HLT_allMET_elStreamDL_el0_pt");
        TH1D* h_DoubleEl_OR__X__allMET_el0_pt = (TH1D*) f->Get("h_DoubleEl_OR__X__allMET_el0_pt");
	TH1D *eff_DoubleEl_OR_vs_el0_pt = (TH1D*)h_DoubleEl_OR__X__allMET_el0_pt->Clone();
	eff_DoubleEl_OR_vs_el0_pt->Divide(h_HLT_allMET_elStreamDL_el0_pt);

        TH1D* h_HLT_allMET_elStreamDL_el1_pt = (TH1D*) f->Get("h_HLT_allMET_elStreamDL_el1_pt");
        TH1D* h_DoubleEl_OR__X__allMET_el1_pt = (TH1D*) f->Get("h_DoubleEl_OR__X__allMET_el1_pt");
	TH1D *eff_DoubleEl_OR_vs_el1_pt = (TH1D*)h_DoubleEl_OR__X__allMET_el1_pt->Clone();
	eff_DoubleEl_OR_vs_el1_pt->Divide(h_HLT_allMET_elStreamDL_el1_pt);

	///////////////////

 	// MODE      : 0 IS Clopper Pearson ,  1 is Gaussian
   	int MODE = 1;
	double scale;

  	double a  = 0.3173;
  	double vx[1000],vy[1000],vexl[1000],vexh[1000],veyl[1000],veyh[1000];
  	for(int i=0;i<h_HLT_allMET_elStreamDL_el0_pt->GetNbinsX();++i)
    	{
      		double N1 = h_HLT_allMET_elStreamDL_el0_pt->GetBinContent(i+1);
      		double N2 = h_DoubleEl_OR__X__allMET_el0_pt->GetBinContent(i+1);
      		double p  = 0;
      		double eU = 0;
      		double eL = 0;
      		double aeff = (1-a)/2;
      		double n,w;
      		if (N1 > 0){
          		p = N2/N1;
          		n = N1+N2;
          		w = N2/n;
          		if (MODE==0) // Clopper-Pearson for binomial
            		{
              			scale = 1.0; // makes sense only for the unprescaled trigger
              			if (N1*p>100 || N1*(1-p)>100)
                		{
                  			eU = sqrt(p*(1-p)/N1);
                  			eL = sqrt(p*(1-p)/N1);
                		}
              			else
                		{
                  			eU = (1-BetaInverse(aeff,N1-N2,N2+1))-p;
                  			eL = p-(1-BetaInverse(1-aeff,N1-N2+1,N2));
                		}
            		}
          		else if (MODE==1) // Wilson for binomial
            		{
              			scale = 1.0; // makes sense only for the unprescaled trigger
              			double d = sqrt(p*(1-p)/N1+0.25/(N1*N1));
              			eU = (p+0.5/N1+d)/(1+1/N1)-p;
              			eL = p-(p+0.5/N1-d)/(1+1/N1);
            		}
          		else // Wilson for Poisson ratio
           		{
              			double d  = sqrt(w*(1-w)/n+0.25/(n*n));
              			double UB = (w+0.5/n+d)/(1+1/n);
              			double LB = (w+0.5/n-d)/(1+1/n);
              			eU = UB/(1-UB)-p;
              			eL = p-LB/(1-LB);
            		}
        	}
      		//cout<<N1<<" "<<N2<<" "<<p<<" "<<eL<<" "<<eU<<endl;
      		vx[i]   = h_HLT_allMET_elStreamDL_el0_pt->GetBinCenter(i+1);
      		vy[i]   = p*scale;
      		vexl[i] = h_HLT_allMET_elStreamDL_el0_pt->GetBinWidth(i+1)/2;
      		vexh[i] = h_HLT_allMET_elStreamDL_el0_pt->GetBinWidth(i+1)/2;
      		veyl[i] = eL*scale;
      		veyh[i] = eU*scale;
		cout<<"For point "<< vx[i]<<" the efficiency is  = "<<vy[i]<<endl;
		cout<<"Low y error is = "<< veyl[i] <<" and high y error is = "<<veyh[i] <<endl;
    	}
	TGraphAsymmErrors *gEff = new TGraphAsymmErrors(h_HLT_allMET_elStreamDL_el0_pt->GetNbinsX(),vx,vy,vexl,vexh,veyl,veyh);
}

