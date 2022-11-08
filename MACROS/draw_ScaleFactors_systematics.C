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
#include <math.h> 




TH2D* Get2DScaleFactorHistogram(TEfficiency* t_data, TEfficiency* t_ttbar, TH2D* ref){


	TH2D* h_sf = (TH2D*) ref->Clone();

  	double ratio = 0;
  	double err = 0;
  	for (int i =1; i < h_sf->GetNbinsX()+1; i++){
    		for (int j =1; j < h_sf->GetNbinsY()+1; j++){
                // t_data->SetStatisticOption(TEfficiency::kBJeffrey);
                // t_ttbar->SetStatisticOption(TEfficiency::kBJeffrey);
                // std::cout<<"Option dos dados: "<<t_data->GetStatisticOption()<<endl;
                // std::cout<<"Option do MC: "<<t_ttbar->GetStatisticOption()<<endl;
                // t_ttbar->SetStatisticOption(TEfficiency::kBUniform);
      			// ** 1. Get central value of SF

                // std::cout<<"valor do bin do MC"<<t_ttbar->GetEfficiency( t_ttbar->GetTotalHistogram()->GetBin(i,j) )<<endl;
                // Se o bin valor do t_ttbar for igual a diferente de 0, então ele calcula a eficiência como sendo t_data/t_ttbar. Caso seja igual a 0, então é 0
      			ratio = t_ttbar->GetEfficiency( t_data->GetTotalHistogram()->GetBin(i,j) ) != 0 ? t_data->GetEfficiency( t_data->GetTotalHistogram()->GetBin(i,j) )/t_ttbar->GetEfficiency( t_data->GetTotalHistogram()->GetBin(i,j) ) : 0;
      			// ** 2. Get biggest error and take that as symmetric envelope --> conservative approach. probably a more intelligent way (https://www.jstor.org/stable/2531405)
                //std::cout<<"uepa"<<std::endl;
                
                // std::cout<<"===================================================="<<std::endl;
                // std::cout<<"bin("<<i<<","<<j<<")"<<std::endl;

                // // if (t_data->GetEfficiency( t_ttbar->GetTotalHistogram()->GetBin(i,j) ) == 1){
                //     std::cout<<"Name of histograms: "<<t_data->GetName()<<std::endl;
                //     std::cout<<"Data efficiency value : "<<t_data->GetEfficiency( t_data->GetTotalHistogram()->GetBin(i,j) )<<std::endl;
                //     std::cout<<"Data Error UP: "<<t_data->GetEfficiencyErrorUp( t_data->GetTotalHistogram()->GetBin(i,j) )<<std::endl;
                //     std::cout<<"Data Error LOW: "<<t_data->GetEfficiencyErrorLow( t_data->GetTotalHistogram()->GetBin(i,j) )<<std::endl;
                //     // std::cout<<"Peso = "<<t_data->GetWeight()<<std::endl;
                // // }
                // // if(t_ttbar->GetEfficiency( t_ttbar->GetTotalHistogram()->GetBin(i,j) ) == 1){
                //     std::cout<<"MC efficiency value : "<<t_ttbar->GetEfficiency( t_data->GetTotalHistogram()->GetBin(i,j) )<<std::endl;
                //     std::cout<<"MC Error UP: "<<t_ttbar->GetEfficiencyErrorUp( t_data->GetTotalHistogram()->GetBin(i,j) )<<std::endl;
                //     std::cout<<"MC Error LOW: "<<t_ttbar->GetEfficiencyErrorLow( t_data->GetTotalHistogram()->GetBin(i,j) )<<std::endl;
                    // std::cout<<"Peso = "<<t_ttbar->GetWeight()<<std::endl;
                // }
                err = t_data->GetEfficiencyErrorUp( t_data->GetTotalHistogram()->GetBin(i,j) );        
      			if (t_data->GetEfficiencyErrorLow( t_data->GetTotalHistogram()->GetBin(i,j) ) > err)   err = t_data->GetEfficiencyErrorLow( t_data->GetTotalHistogram()->GetBin(i,j) );
      			if (t_ttbar->GetEfficiencyErrorUp( t_data->GetTotalHistogram()->GetBin(i,j) ) > err)   err = t_ttbar->GetEfficiencyErrorUp( t_data->GetTotalHistogram()->GetBin(i,j) );
      			if (t_ttbar->GetEfficiencyErrorLow( t_data->GetTotalHistogram()->GetBin(i,j) ) > err)  err = t_ttbar->GetEfficiencyErrorLow( t_data->GetTotalHistogram()->GetBin(i,j) );
		      	if (ratio == 0) err = 0;

                // std::cout<<"SF value: "<<ratio<<std::endl;
                // std::cout<<"SF error: "<<err<<std::endl;
                // std::cout<<"===================================================="<<std::endl;

      			// ** 3. Set SF histogram content and error
      			h_sf->SetBinContent(i, j, ratio);
      			h_sf->SetBinError(i, j, err);
    		}
  	}

  	return h_sf;
}







TH2D* Get2DScaleFactorHistogram_v2(TEfficiency* t_data, TEfficiency* t_ttbar,TH2D* MC_S,TH2D* MC_S2,TH2D* MC_F,TH2D* MC_F2, TH2D* ref,bool type = 0){

	TH2D* h_sf = (TH2D*) ref->Clone();

    //Essa parte e usada devido a incerteza do MC. Uma vez que ele esta sendo calculado com base nesse topico: 
    // https://cms-talk.web.cern.ch/t/correct-method-for-acquisition-of-efficiency-uncertainty/6357/8

    double ratio = 0;
  	double err = 0;

    double err_s = 0;
    double value_s = 0;
    double err_f = 0;
    double value_f = 0;
    double err_r = 0;
    double value_r = 0;
    double err_e = 0;        // Erro da eficiencia de MC


    double z_min = 0;
    double z_max = 0;
    //LOOP do calculo do erro do s
    for (int i =1; i < h_sf->GetNbinsX()+1; i++){
    		for (int j =1; j < h_sf->GetNbinsY()+1; j++){
                // ** 1. Adquiring values and erros of s,f and r.
                value_s = MC_S->GetBinContent(i,j) ;
                err_s = sqrt(MC_S2->GetBinContent(i,j) );
                value_f = MC_F->GetBinContent(i,j) ;
                err_f = sqrt(MC_F2->GetBinContent(i,j) );
                value_r = value_f/value_s;
                err_r = value_r*sqrt(pow(err_s/value_s,2)+pow(err_f/value_f,2));
                err_e = err_r/pow(1+value_r,2);

                // ** 2 Defining the value and error of SF
                ratio = t_ttbar->GetEfficiency( t_data->GetTotalHistogram()->GetBin(i,j) ) != 0 ? t_data->GetEfficiency( t_data->GetTotalHistogram()->GetBin(i,j) )/t_ttbar->GetEfficiency( t_data->GetTotalHistogram()->GetBin(i,j) ) : 0;
                //err UP
                if(type == 0){
                    err = ratio*sqrt(pow(t_data->GetEfficiencyErrorUp( t_data->GetTotalHistogram()->GetBin(i,j) )/t_data->GetEfficiency( t_data->GetTotalHistogram()->GetBin(i,j) ),2)+pow(err_e/t_ttbar->GetEfficiency( t_data->GetTotalHistogram()->GetBin(i,j) ),2) );
                }
                //err DOWN
                if(type == 1){
                    err = ratio*sqrt(pow(t_data->GetEfficiencyErrorLow( t_data->GetTotalHistogram()->GetBin(i,j) )/t_data->GetEfficiency( t_data->GetTotalHistogram()->GetBin(i,j) ),2)+pow(err_e/t_ttbar->GetEfficiency( t_data->GetTotalHistogram()->GetBin(i,j) ),2) );
                }

                // if (ratio>1){
                //     if ((ratio-ratio*sqrt(pow(t_data->GetEfficiencyErrorLow( t_data->GetTotalHistogram()->GetBin(i,j) )/t_data->GetEfficiency( t_data->GetTotalHistogram()->GetBin(i,j) ),2)+pow(err_e/t_ttbar->GetEfficiency( t_data->GetTotalHistogram()->GetBin(i,j) ),2) )) > 1){
                //         std::cout<<"Bins ("<<i<<","<<j<<") tem erro UP"<<endl;
                //     }
                // }

                // if (ratio<1){
                //     if ((ratio+ratio*sqrt(pow(t_data->GetEfficiencyErrorUp( t_data->GetTotalHistogram()->GetBin(i,j) )/t_data->GetEfficiency( t_data->GetTotalHistogram()->GetBin(i,j) ),2)+pow(err_e/t_ttbar->GetEfficiency( t_data->GetTotalHistogram()->GetBin(i,j) ),2) )) < 1){
                //         std::cout<<"Bins ("<<i<<","<<j<<") tem erro UP"<<endl;
                //     }
                // }


		      	//if (ratio == 0) err = 0;
                // ** 3. Set SF histogram content and error
      			h_sf->SetBinContent(i, j, floorf(ratio*10000)/10000);
      			h_sf->SetBinError(i, j, floorf(err*10000)/10000);
                //h_sf->GetZaxis()->SetRange(0,2);
                if (ratio != 0){
                    if(z_min == 0){
                        z_min = floorf(ratio*10000)/10000;
                    }
                    if(z_min > floorf(ratio*10000)/10000 & z_min != 0){
                        z_min = floorf(ratio*10000)/10000;
                    }
                    if(z_max < floorf(ratio*10000)/10000){
                        z_max = floorf(ratio*10000)/10000;
                    }
                }
                

            }

    }
    h_sf->SetMaximum(z_max);
    h_sf->SetMinimum(z_min);
  	return h_sf;
}

TH2D* Get2DNEffHistogram(TH2D* h_nume, TH2D* h_deno, TH2D* ref){
    TH2D* h_Neff = (TH2D*) ref->Clone();
    //h_Neff->Reset();
    double value = 0;
    for (int i =1; i < h_Neff->GetNbinsX()+1; i++){
    		for (int j =1; j < h_Neff->GetNbinsY()+1; j++){
                value = round((h_nume->GetBinContent(i,j)*h_nume->GetBinContent(i,j))/h_deno->GetBinContent(i,j));
                // std::cout<<"h_nume: "<< value<<endl;
            h_Neff->SetBinContent(i, j, value);
      		//h_Neff->SetBinError(i, j, 0);
            }
        
    }
    return h_Neff;

}

TH2D* MakeTH2DHistogram(TEfficiency* t_data,TH2D* ref){
    TH2D* h_clone = (TH2D*) ref->Clone();
    //h_Neff->Reset();
    double value = 0;
    double err = 0;
    for (int i =1; i < h_clone->GetNbinsX()+1; i++){
    		for (int j =1; j < h_clone->GetNbinsY()+1; j++){
                value = floorf(t_data->GetEfficiency(t_data->GetTotalHistogram()->GetBin(i,j))*1000)/1000;
                //std::cout<<"err"<<value<<endl;
                err = floorf(t_data->GetEfficiencyErrorLow( t_data->GetTotalHistogram()->GetBin(i,j))*1000)/1000;  
                // std::cout<<"Valor com erro"<< t_data->GetEfficiency(t_data->GetTotalHistogram()->GetBin(i,j))<<" error: "<<t_data->GetEfficiencyErrorLow( t_data->GetTotalHistogram()->GetBin(i,j))<<endl;
                // if (t_data->GetEfficiency(t_data->GetTotalHistogram()->GetBin(i,j)) + t_data->GetEfficiencyErrorLow( t_data->GetTotalHistogram()->GetBin(i,j)))
            // std::cout<<"----------------------------------------------------------------------"<<err<<endl;
            h_clone->SetBinContent(i, j, value);
      		h_clone->SetBinError(i, j, err);
            }
    }
    return h_clone;
}




void draw_ScaleFactors_systematics(string year,string local_data_root,string local_MC_root, string sufix, string dir_out, int type = 0, string data_type = "")
{

        TString yearstring = year;
        TString output = dir_out;
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
        
        TFile *f = new TFile(local_data_root.c_str(),"READ");
        // TFile *f = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl//TriggerFiles_2017/data/data_2017.root","READ");
        // TFile *f = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl//TriggerFiles_2018/data/data_2018.root","READ");
        // TFile *f = new TFile("/nfs/dust/cms/user/sewuchte/analysisFWK/TriggEffs/CMSSW_10_2_22/src/TopAnalysis/tth-triggerefficiency-dl//TriggerFiles_2018/data/outfile_run2018D.root","READ");


        f->cd();
        bool Skip = false;
        // TString s = "";
        // TString s = "_NJETSHIGH";
        // TString s = "_NJETSLOW";
        // TString s = "_NPVHIGH";
        // TString s = "_NPVLOW";
        // TString s = "_METHIGH";
        //TString s = "_METLOW";
         TString s = sufix;
         string tag = "";
         if (type == 0){
             s = "";
             //sufix = "";
         }

         if (data_type == "_NJETSHIGH" || data_type == "_NJETSLOW" || data_type == "_NJETSLOW" || data_type == "_NPVHIGH" || data_type == "_NPVLOW" || data_type == "_METHIGH" || data_type == "_METLOW" || data_type == "_ExNumMu0" || data_type == "_ExNumMu1" || data_type == "_ExNumMu2" || data_type == "_ExNumEl0" || data_type == "_ExNumEl1" || data_type == "_ExNumEl2" || data_type == "_DeltaRZone0" || data_type == "_DeltaRZone1" || data_type == "_DeltaRZone2" || data_type == "_DeltaRZone3"){
             s = data_type;
             tag = data_type;
             Skip = true; // We dont make some plots if this differents regions, so this code skip them if this boolian is true
         }

        string dir_output = dir_out + "TriggerSFs"+sufix+"_"+year+tag+".root"; 
        std::cout<<"Arquivo que estou acessando: "<<dir_output<<endl;
        std::cout<<"Valor do s : "<< s<<endl;
        std::cout<<"============================================================"<<endl;
        std::cout<<"Nome do data_type: "<<data_type<<endl;
        std::cout<<"============================================================"<<endl;

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
            f_MC  = new TFile(local_MC_root.c_str(),"READ");
        }
        if(yearstring=="2017"){
            f_MC  = new TFile(local_MC_root.c_str(),"READ");
        }
        if(yearstring=="2018"){
            f_MC  = new TFile(local_MC_root.c_str(),"READ");
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


        // Taking the histograms from file f, in order to do the check if gaussian aproximation is possible
        TH2D* h_DoubleEl_OR__X__allMET_NumWin_el0_pt_vs_el1_pt = (TH2D*) f_MC->Get("h_DoubleEl_OR__X__allMET_NumSum2Win"+s+"_el0_pt_vs_el1_pt");
        TH2D* h_DoubleEl_OR__X__allMET_DenWin_el0_pt_vs_el1_pt = (TH2D*) f_MC->Get("h_DoubleEl_OR__X__allMET_DenSum2Win"+s+"_el0_pt_vs_el1_pt");
        TH2D* h_DoubleEl_OR__X__allMET_NumFail_el0_pt_vs_el1_pt = (TH2D*) f_MC->Get("h_DoubleEl_OR__X__allMET_NumSum2Fail"+s+"_el0_pt_vs_el1_pt");
        TH2D* h_DoubleEl_OR__X__allMET_DenFail_el0_pt_vs_el1_pt = (TH2D*) f_MC->Get("h_DoubleEl_OR__X__allMET_DenSum2Fail"+s+"_el0_pt_vs_el1_pt");

        TH2D* h_DoubleMu_OR__X__allMET_NumWin_mu0_pt_vs_mu1_pt = (TH2D*) f_MC->Get("h_DoubleMu_OR__X__allMET_NumSum2Win"+s+"_mu0_pt_vs_mu1_pt");
        TH2D* h_DoubleMu_OR__X__allMET_DenWin_mu0_pt_vs_mu1_pt = (TH2D*) f_MC->Get("h_DoubleMu_OR__X__allMET_DenSum2Win"+s+"_mu0_pt_vs_mu1_pt");
        TH2D* h_DoubleMu_OR__X__allMET_NumFail_mu0_pt_vs_mu1_pt = (TH2D*) f_MC->Get("h_DoubleMu_OR__X__allMET_NumSum2Fail"+s+"_mu0_pt_vs_mu1_pt");
        TH2D* h_DoubleMu_OR__X__allMET_DenFail_mu0_pt_vs_mu1_pt = (TH2D*) f_MC->Get("h_DoubleMu_OR__X__allMET_DenSum2Fail"+s+"_mu0_pt_vs_mu1_pt");

        TH2D* h_EMu_OR__X__allMET_NumWin_mu0_pt_vs_el0_pt = (TH2D*) f_MC->Get("h_EMu_OR__X__allMET_NumSum2Win"+s+"_mu0_pt_vs_el0_pt");
        TH2D* h_EMu_OR__X__allMET_DenWin_mu0_pt_vs_el0_pt = (TH2D*) f_MC->Get("h_EMu_OR__X__allMET_DenSum2Win"+s+"_mu0_pt_vs_el0_pt");
        TH2D* h_EMu_OR__X__allMET_NumFail_mu0_pt_vs_el0_pt = (TH2D*) f_MC->Get("h_EMu_OR__X__allMET_NumSum2Fail"+s+"_mu0_pt_vs_el0_pt");
        TH2D* h_EMu_OR__X__allMET_DenFail_mu0_pt_vs_el0_pt = (TH2D*) f_MC->Get("h_EMu_OR__X__allMET_DenSum2Fail"+s+"_mu0_pt_vs_el0_pt");

	/////////////////////////////
	    TH2D *eff_DoubleEl_OR_vs_el0_pt_vs_eta = Get2DScaleFactorHistogram(Eff_DoubleEl_OR_vs_el0_pt_vs_eta,Eff_DoubleEl_OR_vs_el0_pt_MC_vs_eta,h_DoubleEl_OR__X__allMET_el0_pt_vs_eta);
        TH2D *eff_DoubleEl_OR_vs_el1_pt_vs_eta = Get2DScaleFactorHistogram(Eff_DoubleEl_OR_vs_el1_pt_vs_eta,Eff_DoubleEl_OR_vs_el1_pt_MC_vs_eta,h_DoubleEl_OR__X__allMET_el1_pt_vs_eta);
        TH2D *eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt = Get2DScaleFactorHistogram(Eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt,Eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_MC,h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt);
        // if (Skip==false){
        //     TH2D *eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_up = Get2DScaleFactorHistogram_v2(Eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt,Eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_MC,h_DoubleEl_OR__X__allMET_NumWin_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_DenWin_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_NumFail_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_DenFail_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt,0);    
        //     TH2D *eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_down = Get2DScaleFactorHistogram_v2(Eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt,Eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_MC,h_DoubleEl_OR__X__allMET_NumWin_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_DenWin_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_NumFail_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_DenFail_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt,1);
        // }
        TH2D *eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta = Get2DScaleFactorHistogram(Eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta,Eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta_MC,h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta);
        TH2D *eff_EMu_OR_vs_mu0_pt_vs_el0_pt = Get2DScaleFactorHistogram(Eff_EMu_OR_vs_mu0_pt_vs_el0_pt,Eff_EMu_OR_vs_mu0_pt_vs_el0_pt_MC,h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt);
        TH2D *eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt = Get2DScaleFactorHistogram(Eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt,Eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_MC,h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt);
///////////////////////
//N efficiency do numero de eventos que passaram e voltaram do El e Mu
        // TH2D *NeffWin_DoubleEl_OR_vs_el0_pt_vs_el1_pt = Get2DNEffHistogram(h_DoubleEl_OR__X__allMET_NumWin_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_DenWin_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_DenWin_el0_pt_vs_el1_pt);
        // TH2D *NeffFail_DoubleEl_OR_vs_el0_pt_vs_el1_pt = Get2DNEffHistogram(h_DoubleEl_OR__X__allMET_NumFail_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_DenFail_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_DenFail_el0_pt_vs_el1_pt);

        // TH2D *NeffWin_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt = Get2DNEffHistogram(h_DoubleMu_OR__X__allMET_NumWin_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_DenWin_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_DenWin_mu0_pt_vs_mu1_pt); 
        // TH2D *NeffFail_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt = Get2DNEffHistogram(h_DoubleMu_OR__X__allMET_NumFail_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_DenFail_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_DenFail_mu0_pt_vs_mu1_pt);

        // TH2D *NeffWin_EMu_OR_vs_mu0_pt_vs_el0_pt = Get2DNEffHistogram(h_EMu_OR__X__allMET_NumWin_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_DenWin_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_DenWin_mu0_pt_vs_el0_pt);
        // TH2D *NeffFail_EMu_OR_vs_mu0_pt_vs_el0_pt = Get2DNEffHistogram(h_EMu_OR__X__allMET_NumFail_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_DenFail_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_DenFail_mu0_pt_vs_el0_pt);



//Valor da efficiency dos graficos 2D

        TH2D *TH2D_eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt = MakeTH2DHistogram(Eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt);
        TH2D *TH2D_eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt = MakeTH2DHistogram(Eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt);
        TH2D *TH2D_eff_EMu_OR_vs_mu0_pt_vs_el0_pt = MakeTH2DHistogram(Eff_EMu_OR_vs_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt);

///////////////////////
        TH2D *eff_EMu_OR_vs_el0_pt_vs_eta = Get2DScaleFactorHistogram(Eff_EMu_OR_vs_el0_pt_vs_eta,Eff_EMu_OR_vs_el0_pt_MC_vs_eta,h_EMu_OR__X__allMET_el0_pt_vs_eta);
        TH2D *eff_EMu_OR_vs_mu0_pt_vs_eta = Get2DScaleFactorHistogram(Eff_EMu_OR_vs_mu0_pt_vs_eta,Eff_EMu_OR_vs_mu0_pt_MC_vs_eta,h_EMu_OR__X__allMET_mu0_pt_vs_eta);
        TH2D *eff_EMu_OR_vs_mu0_eta_vs_el0_eta = Get2DScaleFactorHistogram(Eff_EMu_OR_vs_mu0_eta_vs_el0_eta,Eff_EMu_OR_vs_mu0_eta_vs_el0_eta_MC,h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta);
        // if(Skip ==false){
        //     TH2D *eff_EMu_OR_vs_mu0_pt_vs_el0_pt_up = Get2DScaleFactorHistogram_v2(Eff_EMu_OR_vs_mu0_pt_vs_el0_pt,Eff_EMu_OR_vs_mu0_pt_vs_el0_pt_MC,h_EMu_OR__X__allMET_NumWin_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_DenWin_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_NumFail_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_DenFail_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt,0);
        //     TH2D *eff_EMu_OR_vs_mu0_pt_vs_el0_pt_down = Get2DScaleFactorHistogram_v2(Eff_EMu_OR_vs_mu0_pt_vs_el0_pt,Eff_EMu_OR_vs_mu0_pt_vs_el0_pt_MC,h_EMu_OR__X__allMET_NumWin_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_DenWin_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_NumFail_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_DenFail_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt,1);    
        // }


        TH2D *eff_DoubleMu_OR_vs_mu1_pt_vs_eta = Get2DScaleFactorHistogram(Eff_DoubleMu_OR_vs_mu1_pt_vs_eta,Eff_DoubleMu_OR_vs_mu1_pt_MC_vs_eta,h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta);
        TH2D *eff_DoubleMu_OR_vs_mu0_pt_vs_eta = Get2DScaleFactorHistogram(Eff_DoubleMu_OR_vs_mu0_pt_vs_eta,Eff_DoubleMu_OR_vs_mu0_pt_MC_vs_eta,h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta);
        // if(Skip==false){
        //     TH2D *eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_up = Get2DScaleFactorHistogram_v2(Eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt,Eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_MC,h_DoubleMu_OR__X__allMET_NumWin_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_DenWin_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_NumFail_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_DenFail_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt,0);
        //     TH2D *eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_down = Get2DScaleFactorHistogram_v2(Eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt,Eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_MC,h_DoubleMu_OR__X__allMET_NumWin_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_DenWin_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_NumFail_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_DenFail_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt,1);
        // }
        
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
        if(type != 0){c1->SaveAs(output+"SF_DoubleEl_OR_el0_pt_vs_eta_"+yearstring+s+".png");}
    	c1->Close();

        TCanvas *c2 = new TCanvas("c2","c2");
        c2->cd();
	    //DoubleEl->Draw("same");
        //eff_DoubleEl_OR_vs_el1_pt_vs_eta->GetZaxis()->SetRangeUser(0.90,1.01);
    	c2->SetRightMargin(0.15);
    	eff_DoubleEl_OR_vs_el1_pt_vs_eta->SetLabelSize(0.04, "XYZ");
        eff_DoubleEl_OR_vs_el1_pt_vs_eta->Draw("TEXT E colz");
    	paveCMS->Draw("same");
    	if(type != 0){c2->SaveAs(output+"SF_DoubleEl_OR_el1_pt_vs_eta_"+yearstring+s+".png");}
        c2->Close();


        // if(Skip==false){
        //     TH2D *eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_up = Get2DScaleFactorHistogram_v2(Eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt,Eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_MC,h_DoubleEl_OR__X__allMET_NumWin_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_DenWin_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_NumFail_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_DenFail_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt,0);    
        //     TH2D *eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_down = Get2DScaleFactorHistogram_v2(Eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt,Eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_MC,h_DoubleEl_OR__X__allMET_NumWin_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_DenWin_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_NumFail_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_DenFail_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt,1);
        //     TCanvas *c3 = new TCanvas("c3","c3");
        //     c3->cd();
        //     //eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->GetZaxis()->SetRangeUser(0.90,1.01);
    	//     c3->SetRightMargin(0.15);
        //     // c3->SetLogy();
        //     // c3->SetLogx();
    	//     eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_up->SetLabelSize(0.04, "XYZ");
        //     eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_up->Draw("TEXT E colz");
        //     c3->SetLogy();
        //     c3->SetLogx();
        //     eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_up->GetXaxis()->SetMoreLogLabels();
        //     eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_up->GetYaxis()->SetMoreLogLabels();
    	//     //DoubleEl->Draw("same");
    	//     paveCMS->Draw("same");
    	//     if(type != 0){c3->SaveAs(output+"SF_DoubleEl_OR_el0_pt_vs_el1_pt_up_"+yearstring+s+".png");}
        //     c3->Close();

        //     TCanvas *d3 = new TCanvas("d3","d3");
        //     d3->cd();
        //     //eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->GetZaxis()->SetRangeUser(0.90,1.01);
    	//     d3->SetRightMargin(0.15);
    	//     eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_down->SetLabelSize(0.04, "XYZ");
        //     eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_down->Draw("TEXT E colz");
        //     d3->SetLogy();
        //     d3->SetLogx();
        //     eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_down->GetXaxis()->SetMoreLogLabels();
        //     eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_down->GetYaxis()->SetMoreLogLabels();
    	//     //DoubleEl->Draw("same");
    	//     paveCMS->Draw("same");
    	//     if(type != 0){d3->SaveAs(output+"SF_DoubleEl_OR_el0_pt_vs_el1_pt_down_"+yearstring+s+".png");}
        //     d3->Close();
        // }

        TCanvas *f3 = new TCanvas("f3","f3");
        f3->cd();
    	f3->SetRightMargin(0.15);
    	eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->SetLabelSize(0.04, "XYZ");
        eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->Draw("TEXT E colz");
        f3->SetLogy();
        f3->SetLogx();
        eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->GetXaxis()->SetMoreLogLabels();
        eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->GetYaxis()->SetMoreLogLabels();
    	paveCMS->Draw("same");
    	if(type != 0){f3->SaveAs(output+"SF_DoubleEl_OR_el0_pt_vs_el1_pt_"+yearstring+s+".png");}
        f3->Close();


        TCanvas *c4 = new TCanvas("c4","c4");
        c4->cd();
	    //DoubleEl->Draw("same");
        //eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta->GetZaxis()->SetRangeUser(0.90,1.01);
    	c4->SetRightMargin(0.15);
    	eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta->SetLabelSize(0.04, "XYZ");
        eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta->Draw("TEXT E colz");
    	paveCMS->Draw("same");
    	if(type != 0){c4->SaveAs(output+"SF_DoubleEl_OR_el0_eta_vs_el1_eta_"+yearstring+s+".png");}
        c4->Close();

    
    
    if(Skip==false){
        TH2D *NeffWin_DoubleEl_OR_vs_el0_pt_vs_el1_pt = Get2DNEffHistogram(h_DoubleEl_OR__X__allMET_NumWin_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_DenWin_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_DenWin_el0_pt_vs_el1_pt);
        TH2D *NeffFail_DoubleEl_OR_vs_el0_pt_vs_el1_pt = Get2DNEffHistogram(h_DoubleEl_OR__X__allMET_NumFail_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_DenFail_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_DenFail_el0_pt_vs_el1_pt);
        //Including gaussian aproximation
        TCanvas *c5 = new TCanvas("c5","c5");
        c5->cd();
        //eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->GetZaxis()->SetRangeUser(0.90,1.01);
    	c5->SetRightMargin(0.15);
    	NeffWin_DoubleEl_OR_vs_el0_pt_vs_el1_pt->SetLabelSize(0.04, "XYZ");
        NeffWin_DoubleEl_OR_vs_el0_pt_vs_el1_pt->Draw("TEXT colz");
    	//DoubleEl->Draw("same");
    	paveCMS->Draw("same");
    	if(type != 0){c5->SaveAs(output+"NeffWin_DoubleEl_OR_vs_el0_pt_vs_el1_pt"+yearstring+s+".png");}
        c5->Close();

        TCanvas *c6 = new TCanvas("c6","c6");
        c6->cd();
        //eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->GetZaxis()->SetRangeUser(0.90,1.01);
    	c6->SetRightMargin(0.15);
    	NeffFail_DoubleEl_OR_vs_el0_pt_vs_el1_pt->SetLabelSize(0.04, "XYZ");
        NeffFail_DoubleEl_OR_vs_el0_pt_vs_el1_pt->Draw("TEXT colz");
    	//DoubleEl->Draw("same");
    	paveCMS->Draw("same");
    	if(type != 0){c6->SaveAs(output+"NeffFail_DoubleEl_OR_vs_el0_pt_vs_el1_pt"+yearstring+s+".png");}
        c6->Close();

    }
        TCanvas *c7 = new TCanvas("c7","c7");
        c7->cd();
        //eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->GetZaxis()->SetRangeUser(0.90,1.01);
    	c7->SetRightMargin(0.15);
    	TH2D_eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->SetLabelSize(0.04, "XYZ");
        TH2D_eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->Draw("TEXT E colz");
        c7->SetLogy();
        c7->SetLogx();
        // TH2D_eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->GetYaxis()->SetRange(0., 199);
        TH2D_eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->GetXaxis()->SetMoreLogLabels();
        TH2D_eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->GetYaxis()->SetMoreLogLabels();
        
    	//DoubleEl->Draw("same");
    	paveCMS->Draw("same");
    	if(type != 0){c7->SaveAs(output+"Data_eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt"+yearstring+s+".png");}
        c7->Close();



	// EMu

        TCanvas *cc1 = new TCanvas("cc1","cc1");
        cc1->cd();
        //eff_EMu_OR_vs_el0_pt_vs_eta->GetZaxis()->SetRangeUser(0.90,1.01);
    	cc1->SetRightMargin(0.15);
    	eff_EMu_OR_vs_el0_pt_vs_eta->SetLabelSize(0.04, "XYZ");
        eff_EMu_OR_vs_el0_pt_vs_eta->Draw("TEXT E colz");
    	//ElMu->Draw("same");
    	paveCMS->Draw("same");
    	if(type != 0){cc1->SaveAs(output+"SF_EMu_OR_el0_pt_vs_eta_"+yearstring+s+".png");}
        cc1->Close();

        TCanvas *cc2 = new TCanvas("cc2","cc2");
        cc2->cd();
	    //ElMu->Draw("same");
        //eff_EMu_OR_vs_mu0_pt_vs_eta->GetZaxis()->SetRangeUser(0.90,1.01);
    	cc2->SetRightMargin(0.15);
    	eff_EMu_OR_vs_mu0_pt_vs_eta->SetLabelSize(0.04, "XYZ");
        eff_EMu_OR_vs_mu0_pt_vs_eta->Draw("TEXT E colz");
    	paveCMS->Draw("same");
    	if(type != 0){cc2->SaveAs(output+"SF_EMu_OR_vs_mu0_pt_vs_eta_"+yearstring+s+".png");}
        cc2->Close();

        TCanvas *cc3 = new TCanvas("cc3","cc3");
        cc3->cd();
        //eff_EMu_OR_vs_mu0_eta_vs_el0_eta->GetZaxis()->SetRangeUser(0.90,1.01);
    	cc3->SetRightMargin(0.15);
    	eff_EMu_OR_vs_mu0_eta_vs_el0_eta->SetLabelSize(0.04, "XYZ");
        eff_EMu_OR_vs_mu0_eta_vs_el0_eta->Draw("TEXT E colz");
    	//ElMu->Draw("same");
    	paveCMS->Draw("same");
    	if(type != 0){cc3->SaveAs(output+"SF_EMu_OR_vs_mu0_eta_vs_el0_eta_"+yearstring+s+".png");}
        cc3->Close();

       
        TCanvas *ff4 = new TCanvas("cc4","cc4");
        ff4->cd();
    	ff4->SetRightMargin(0.15);
    	eff_EMu_OR_vs_mu0_pt_vs_el0_pt->SetLabelSize(0.04, "XYZ");
        eff_EMu_OR_vs_mu0_pt_vs_el0_pt->Draw("TEXT E colz");
        ff4->SetLogy();
        ff4->SetLogx();
        eff_EMu_OR_vs_mu0_pt_vs_el0_pt->GetXaxis()->SetMoreLogLabels();
        eff_EMu_OR_vs_mu0_pt_vs_el0_pt->GetYaxis()->SetMoreLogLabels();
    	//ElMu->Draw("same");
    	paveCMS->Draw("same");
    	if(type != 0){ff4->SaveAs(output+"SF_EMu_OR_vs_mu0_pt_vs_el0_pt_"+yearstring+s+".png");}
        ff4->Close();

        // if(Skip==false){
        //     TH2D *eff_EMu_OR_vs_mu0_pt_vs_el0_pt_up = Get2DScaleFactorHistogram_v2(Eff_EMu_OR_vs_mu0_pt_vs_el0_pt,Eff_EMu_OR_vs_mu0_pt_vs_el0_pt_MC,h_EMu_OR__X__allMET_NumWin_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_DenWin_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_NumFail_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_DenFail_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt,0);
        //     TH2D *eff_EMu_OR_vs_mu0_pt_vs_el0_pt_down = Get2DScaleFactorHistogram_v2(Eff_EMu_OR_vs_mu0_pt_vs_el0_pt,Eff_EMu_OR_vs_mu0_pt_vs_el0_pt_MC,h_EMu_OR__X__allMET_NumWin_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_DenWin_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_NumFail_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_DenFail_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt,1);    
        //     TCanvas *cc4 = new TCanvas("cc4","cc4");
        //     cc4->cd();
        //     //eff_EMu_OR_vs_mu0_pt_vs_el0_pt->GetZaxis()->SetRangeUser(0.90,1.01);
    	//     cc4->SetRightMargin(0.15);
        //     eff_EMu_OR_vs_mu0_pt_vs_el0_pt_up->SetLabelSize(0.04, "XYZ");
        //     eff_EMu_OR_vs_mu0_pt_vs_el0_pt_up->Draw("TEXT E colz");
        //     cc4->SetLogy();
        //     cc4->SetLogx();
        //     eff_EMu_OR_vs_mu0_pt_vs_el0_pt_up->GetXaxis()->SetMoreLogLabels();
        //     eff_EMu_OR_vs_mu0_pt_vs_el0_pt_up->GetYaxis()->SetMoreLogLabels();
        // 	//ElMu->Draw("same");
    	//     paveCMS->Draw("same");
        // 	if(type != 0){cc4->SaveAs(output+"SF_EMu_OR_vs_mu0_pt_vs_el0_pt_up_"+yearstring+s+".png");}
        //     cc4->Close();


        //     TCanvas *dd4 = new TCanvas("dd4","dd4");
        //     dd4->cd();
        //     //eff_EMu_OR_vs_mu0_pt_vs_el0_pt->GetZaxis()->SetRangeUser(0.90,1.01);
    	//     dd4->SetRightMargin(0.15);
    	//     eff_EMu_OR_vs_mu0_pt_vs_el0_pt_down->SetLabelSize(0.04, "XYZ");
        //     eff_EMu_OR_vs_mu0_pt_vs_el0_pt_down->Draw("TEXT E colz");
        //     dd4->SetLogy();
        //     dd4->SetLogx();
        //     eff_EMu_OR_vs_mu0_pt_vs_el0_pt_down->GetXaxis()->SetMoreLogLabels();
        //     eff_EMu_OR_vs_mu0_pt_vs_el0_pt_down->GetYaxis()->SetMoreLogLabels();
    	//     //ElMu->Draw("same");
    	//     paveCMS->Draw("same");
    	//     if(type != 0){dd4->SaveAs(output+"SF_EMu_OR_vs_mu0_pt_vs_el0_pt_down_"+yearstring+s+".png");}
        //     dd4->Close();
        // }
        //Including gaussian aproximation
        
        if(Skip==false){
            TH2D *NeffWin_EMu_OR_vs_mu0_pt_vs_el0_pt = Get2DNEffHistogram(h_EMu_OR__X__allMET_NumWin_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_DenWin_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_DenWin_mu0_pt_vs_el0_pt);
            TH2D *NeffFail_EMu_OR_vs_mu0_pt_vs_el0_pt = Get2DNEffHistogram(h_EMu_OR__X__allMET_NumFail_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_DenFail_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_DenFail_mu0_pt_vs_el0_pt);

            TCanvas *cc5 = new TCanvas("cc5","cc5");
            cc5->cd();
    	    cc5->SetRightMargin(0.15);
    	    NeffWin_EMu_OR_vs_mu0_pt_vs_el0_pt->SetLabelSize(0.04, "XYZ");
            NeffWin_EMu_OR_vs_mu0_pt_vs_el0_pt->Draw("TEXT colz");
    	    //DoubleEl->Draw("same");
    	    paveCMS->Draw("same");
    	    if(type != 0){cc5->SaveAs(output+"NeffWin_EMu_OR_vs_mu0_pt_vs_el0_pt_"+yearstring+s+".png");}
            cc5->Close();

            TCanvas *cc6 = new TCanvas("c6","c6");
            cc6->cd();
            //eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->GetZaxis()->SetRangeUser(0.90,1.01);
    	    cc6->SetRightMargin(0.15);
    	    NeffFail_EMu_OR_vs_mu0_pt_vs_el0_pt->SetLabelSize(0.04, "XYZ");
            NeffFail_EMu_OR_vs_mu0_pt_vs_el0_pt->Draw("TEXT colz");
    	    //DoubleEl->Draw("same");
    	    paveCMS->Draw("same");
    	    if(type != 0){cc6->SaveAs(output+"NeffFail_EMu_OR_vs_mu0_pt_vs_el0_pt_"+yearstring+s+".png");}
            cc6->Close();
        }
        TCanvas *cc7 = new TCanvas("cc7","cc7");
        cc7->cd();
        //eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->GetZaxis()->SetRangeUser(0.90,1.01);
    	cc7->SetRightMargin(0.15);
    	TH2D_eff_EMu_OR_vs_mu0_pt_vs_el0_pt->SetLabelSize(0.04, "XYZ");
        TH2D_eff_EMu_OR_vs_mu0_pt_vs_el0_pt->Draw("TEXT E colz");
        cc7->SetLogy();
        cc7->SetLogx();
        TH2D_eff_EMu_OR_vs_mu0_pt_vs_el0_pt->GetXaxis()->SetMoreLogLabels();
        TH2D_eff_EMu_OR_vs_mu0_pt_vs_el0_pt->GetYaxis()->SetMoreLogLabels();
    	//DoubleEl->Draw("same");
    	paveCMS->Draw("same AP");
    	if(type != 0){cc7->SaveAs(output+"Data_eff_EMu_OR_vs_mu0_pt_vs_el0_pt"+yearstring+s+".png");}
        cc7->Close();


	// DoubleMu

        TCanvas *ccc1 = new TCanvas("ccc1","ccc1");
        ccc1->cd();
        //eff_DoubleMu_OR_vs_mu1_pt_vs_eta->GetZaxis()->SetRangeUser(0.90,1.01);
    	ccc1->SetRightMargin(0.15);
    	eff_DoubleMu_OR_vs_mu1_pt_vs_eta->SetLabelSize(0.04, "XYZ");
        eff_DoubleMu_OR_vs_mu1_pt_vs_eta->Draw("TEXT E colz");
    	//DoubleMu->Draw("same");
    	paveCMS->Draw("same");
    	if(type != 0){ccc1->SaveAs(output+"SF_DoubleMu_OR_mu1_pt_vs_eta_"+yearstring+s+".png");}
        ccc1->Close();

        TCanvas *ccc2 = new TCanvas("ccc2","ccc2");
        ccc2->cd();
        //eff_DoubleMu_OR_vs_mu0_pt_vs_eta->GetZaxis()->SetRangeUser(0.90,1.01);
    	ccc2->SetRightMargin(0.15);
    	eff_DoubleMu_OR_vs_mu0_pt_vs_eta->SetLabelSize(0.04, "XYZ");
        eff_DoubleMu_OR_vs_mu0_pt_vs_eta->Draw("TEXT E colz");
    	//DoubleMu->Draw("same");
    	paveCMS->Draw("same");
    	if(type != 0){ccc2->SaveAs(output+"SF_DoubleMu_OR_vs_mu0_pt_vs_eta_"+yearstring+s+".png");}
        ccc2->Close();


        TCanvas *fff3 = new TCanvas("ccc3","ccc3");
        fff3->cd();
        //eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->GetZaxis()->SetRangeUser(0.90,1.01);
    	fff3->SetRightMargin(0.15);
    	eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->SetLabelSize(0.04, "XYZ");
        eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->Draw("TEXT E colz");
        fff3->SetLogy();
        fff3->SetLogx();
        eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->GetXaxis()->SetMoreLogLabels();
        eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->GetYaxis()->SetMoreLogLabels();
    	//DoubleMu->Draw("same");
    	paveCMS->Draw("same");
    	if(type != 0){fff3->SaveAs(output+"SF_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_"+yearstring+s+".png");}
        fff3->Close();

        // if(Skip==false){
        //     TH2D *eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_up = Get2DScaleFactorHistogram_v2(Eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt,Eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_MC,h_DoubleMu_OR__X__allMET_NumWin_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_DenWin_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_NumFail_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_DenFail_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt,0);
        //     TH2D *eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_down = Get2DScaleFactorHistogram_v2(Eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt,Eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_MC,h_DoubleMu_OR__X__allMET_NumWin_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_DenWin_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_NumFail_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_DenFail_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt,1);
        //     TCanvas *ccc3 = new TCanvas("ccc3","ccc3");
        //     ccc3->cd();
        //     //eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->GetZaxis()->SetRangeUser(0.90,1.01);
    	//     ccc3->SetRightMargin(0.15);
    	//     eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_up->SetLabelSize(0.04, "XYZ");
        //     eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_up->Draw("TEXT E colz");
        //     ccc3->SetLogy();
        //     ccc3->SetLogx();
        //     eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_up->GetXaxis()->SetMoreLogLabels();
        //     eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_up->GetYaxis()->SetMoreLogLabels();
    	//     //DoubleMu->Draw("same");
    	//     paveCMS->Draw("same");
    	//     if(type != 0){ccc3->SaveAs(output+"SF_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_up_"+yearstring+s+".png");}
        //     ccc3->Close();

        //     TCanvas *ddd3 = new TCanvas("ddd3","ddd3");
        //     ddd3->cd();
        //     //eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->GetZaxis()->SetRangeUser(0.90,1.01);
    	//     ddd3->SetRightMargin(0.15);
    	//     eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_down->SetLabelSize(0.04, "XYZ");
        //     eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_down->Draw("TEXT E colz");
        //     ddd3->SetLogy();
        //     ddd3->SetLogx();
        //     eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_down->GetXaxis()->SetMoreLogLabels();
        //     eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_down->GetYaxis()->SetMoreLogLabels();
    	//     //DoubleMu->Draw("same");
    	//     paveCMS->Draw("same");
    	//     if(type != 0){ddd3->SaveAs(output+"SF_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_down_"+yearstring+s+".png");}
        //     ddd3->Close();
        // }
        TCanvas *ccc4 = new TCanvas("ccc4","ccc4");
        ccc4->cd();
        //eff_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta->GetZaxis()->SetRangeUser(0.90,1.01);
    	ccc4->SetRightMargin(0.15);
    	eff_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta->SetLabelSize(0.04, "XYZ");
        eff_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta->Draw("TEXT E colz");
    	//DoubleMu->Draw("same");
    	paveCMS->Draw("same");
    	if(type != 0){ccc4->SaveAs(output+"SF_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta_"+yearstring+s+".png");}
        ccc4->Close();
    if(Skip==false){
        TH2D *NeffWin_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt = Get2DNEffHistogram(h_DoubleMu_OR__X__allMET_NumWin_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_DenWin_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_DenWin_mu0_pt_vs_mu1_pt); 
        TH2D *NeffFail_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt = Get2DNEffHistogram(h_DoubleMu_OR__X__allMET_NumFail_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_DenFail_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_DenFail_mu0_pt_vs_mu1_pt);
        //Including gaussian aproximation
        TCanvas *ccc5 = new TCanvas("ccc5","ccc5");
        ccc5->cd();
    	ccc5->SetRightMargin(0.15);
    	NeffWin_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->SetLabelSize(0.04, "XYZ");
        NeffWin_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->Draw("TEXT colz");
    	//DoubleEl->Draw("same");
    	paveCMS->Draw("same");
    	if(type != 0){ccc5->SaveAs(output+"NeffWin_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_"+yearstring+s+".png");}
        ccc5->Close();

        TCanvas *ccc6 = new TCanvas("ccc6","ccc6");
        ccc6->cd();
        //eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->GetZaxis()->SetRangeUser(0.90,1.01);
    	ccc6->SetRightMargin(0.15);
    	NeffFail_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->SetLabelSize(0.04, "XYZ");
        NeffFail_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->Draw("TEXT colz");
    	//DoubleEl->Draw("same");
    	paveCMS->Draw("same");
    	if(type != 0){ccc6->SaveAs(output+"NeffFail_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_"+yearstring+s+".png");}
        ccc6->Close();
    }
        TCanvas *ccc7 = new TCanvas("ccc7","ccc7");
        ccc7->cd();
        //eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->GetZaxis()->SetRangeUser(0.90,1.01);
    	ccc7->SetRightMargin(0.15);
    	TH2D_eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->SetLabelSize(0.04, "XYZ");
        TH2D_eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->Draw("TEXT E colz");
        ccc7->SetLogy();
        ccc7->SetLogx();
        TH2D_eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->GetXaxis()->SetMoreLogLabels();
        TH2D_eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->GetYaxis()->SetMoreLogLabels();

    	//DoubleEl->Draw("same");
    	paveCMS->Draw("same");
    	if(type != 0){ccc7->SaveAs(output+"Data_eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_"+yearstring+s+".png");}
        ccc7->Close();




        // f=new TFile("TriggerSFs_2016_H"+s+".root","RECREATE");
        // f=new TFile("TriggerSFs_2017_F"+s+".root","RECREATE");
        f=new TFile(dir_output.c_str(),"RECREATE");
        // f=new TFile("TriggerSFs_2017"+s+".root","RECREATE");
        // f=new TFile("TriggerSFs_2018_D"+s+".root","RECREATE");
        // f=new TFile("TriggerSFs_2018"+s+".root","RECREATE");
        // f=new TFile("Final_triggerSFs_2018_with_lepton_and_PU_SFs"+s+".root","RECREATE");
        eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->SetName("h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt");
        eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->Write();
        eff_DoubleEl_OR_vs_el0_pt_vs_eta->SetName("h_DoubleEl_OR__X__allMET_el0_pt_vs_eta");
        eff_DoubleEl_OR_vs_el0_pt_vs_eta->Write();
        eff_DoubleEl_OR_vs_el1_pt_vs_eta->SetName("h_DoubleEl_OR__X__allMET_el1_pt_vs_eta");
        eff_DoubleEl_OR_vs_el1_pt_vs_eta->Write();
        if(Skip==false){
            TH2D *eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_up = Get2DScaleFactorHistogram_v2(Eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt,Eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_MC,h_DoubleEl_OR__X__allMET_NumWin_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_DenWin_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_NumFail_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_DenFail_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt,0);    
            TH2D *eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_down = Get2DScaleFactorHistogram_v2(Eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt,Eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_MC,h_DoubleEl_OR__X__allMET_NumWin_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_DenWin_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_NumFail_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_DenFail_el0_pt_vs_el1_pt,h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt,1);
            TCanvas *c3 = new TCanvas("c3","c3");
            c3->cd();
            //eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->GetZaxis()->SetRangeUser(0.90,1.01);
    	    c3->SetRightMargin(0.15);
            // c3->SetLogy();
            // c3->SetLogx();
    	    eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_up->SetLabelSize(0.04, "XYZ");
            eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_up->Draw("TEXT E colz");
            c3->SetLogy();
            c3->SetLogx();
            eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_up->GetXaxis()->SetMoreLogLabels();
            eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_up->GetYaxis()->SetMoreLogLabels();
    	    //DoubleEl->Draw("same");
    	    paveCMS->Draw("same");
    	    if(type != 0){c3->SaveAs(output+"SF_DoubleEl_OR_el0_pt_vs_el1_pt_up_"+yearstring+s+".png");}
            c3->Close();

            TCanvas *d3 = new TCanvas("d3","d3");
            d3->cd();
            //eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt->GetZaxis()->SetRangeUser(0.90,1.01);
    	    d3->SetRightMargin(0.15);
    	    eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_down->SetLabelSize(0.04, "XYZ");
            eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_down->Draw("TEXT E colz");
            d3->SetLogy();
            d3->SetLogx();
            eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_down->GetXaxis()->SetMoreLogLabels();
            eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_down->GetYaxis()->SetMoreLogLabels();
    	    //DoubleEl->Draw("same");
    	    paveCMS->Draw("same");
    	    if(type != 0){d3->SaveAs(output+"SF_DoubleEl_OR_el0_pt_vs_el1_pt_down_"+yearstring+s+".png");}
            d3->Close();

 	        eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_up->SetName("h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt_up");
            eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_up->Write();
            eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_down->SetName("h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt_down");
            eff_DoubleEl_OR_vs_el0_pt_vs_el1_pt_down->Write();
        }
        eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta->SetName("h_DoubleEl_OR__X__allMET_el0_eta_vs_el1_eta");
        eff_DoubleEl_OR_vs_el0_eta_vs_el1_eta->Write();
        // NeffWin_DoubleEl_OR_vs_el0_pt_vs_el1_pt->SetName("h_effWin_DoubleEl_OR_vs_el0_pt_vs_el1_pt");
        // NeffWin_DoubleEl_OR_vs_el0_pt_vs_el1_pt->Write();
        // NeffFail_DoubleEl_OR_vs_el0_pt_vs_el1_pt->SetName("h_effFail_DoubleEl_OR_vs_el0_pt_vs_el1_pt");
        // NeffFail_DoubleEl_OR_vs_el0_pt_vs_el1_pt->Write();
       

        eff_EMu_OR_vs_mu0_pt_vs_el0_pt->SetName("h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt");
        eff_EMu_OR_vs_mu0_pt_vs_el0_pt->Write();
        eff_EMu_OR_vs_el0_pt_vs_eta->SetName("h_EMu_OR__X__allMET_el0_pt_vs_eta");
        eff_EMu_OR_vs_el0_pt_vs_eta->Write();
        eff_EMu_OR_vs_mu0_pt_vs_eta->SetName("h_EMu_OR__X__allMET_mu0_pt_vs_eta");
        eff_EMu_OR_vs_mu0_pt_vs_eta->Write();
        eff_EMu_OR_vs_mu0_eta_vs_el0_eta->SetName("h_EMu_OR__X__allMET_mu0_eta_vs_el0_eta");
        eff_EMu_OR_vs_mu0_eta_vs_el0_eta->Write();
        if(Skip==false){
            TH2D *eff_EMu_OR_vs_mu0_pt_vs_el0_pt_up = Get2DScaleFactorHistogram_v2(Eff_EMu_OR_vs_mu0_pt_vs_el0_pt,Eff_EMu_OR_vs_mu0_pt_vs_el0_pt_MC,h_EMu_OR__X__allMET_NumWin_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_DenWin_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_NumFail_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_DenFail_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt,0);
            TH2D *eff_EMu_OR_vs_mu0_pt_vs_el0_pt_down = Get2DScaleFactorHistogram_v2(Eff_EMu_OR_vs_mu0_pt_vs_el0_pt,Eff_EMu_OR_vs_mu0_pt_vs_el0_pt_MC,h_EMu_OR__X__allMET_NumWin_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_DenWin_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_NumFail_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_DenFail_mu0_pt_vs_el0_pt,h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt,1);    
            TCanvas *cc4 = new TCanvas("cc4","cc4");
            cc4->cd();
            //eff_EMu_OR_vs_mu0_pt_vs_el0_pt->GetZaxis()->SetRangeUser(0.90,1.01);
    	    cc4->SetRightMargin(0.15);
            eff_EMu_OR_vs_mu0_pt_vs_el0_pt_up->SetLabelSize(0.04, "XYZ");
            eff_EMu_OR_vs_mu0_pt_vs_el0_pt_up->Draw("TEXT E colz");
            cc4->SetLogy();
            cc4->SetLogx();
            eff_EMu_OR_vs_mu0_pt_vs_el0_pt_up->GetXaxis()->SetMoreLogLabels();
            eff_EMu_OR_vs_mu0_pt_vs_el0_pt_up->GetYaxis()->SetMoreLogLabels();
        	//ElMu->Draw("same");
    	    paveCMS->Draw("same");
        	if(type != 0){cc4->SaveAs(output+"SF_EMu_OR_vs_mu0_pt_vs_el0_pt_up_"+yearstring+s+".png");}
            cc4->Close();


            TCanvas *dd4 = new TCanvas("dd4","dd4");
            dd4->cd();
            //eff_EMu_OR_vs_mu0_pt_vs_el0_pt->GetZaxis()->SetRangeUser(0.90,1.01);
    	    dd4->SetRightMargin(0.15);
    	    eff_EMu_OR_vs_mu0_pt_vs_el0_pt_down->SetLabelSize(0.04, "XYZ");
            eff_EMu_OR_vs_mu0_pt_vs_el0_pt_down->Draw("TEXT E colz");
            dd4->SetLogy();
            dd4->SetLogx();
            eff_EMu_OR_vs_mu0_pt_vs_el0_pt_down->GetXaxis()->SetMoreLogLabels();
            eff_EMu_OR_vs_mu0_pt_vs_el0_pt_down->GetYaxis()->SetMoreLogLabels();
    	    //ElMu->Draw("same");
    	    paveCMS->Draw("same");
    	    if(type != 0){dd4->SaveAs(output+"SF_EMu_OR_vs_mu0_pt_vs_el0_pt_down_"+yearstring+s+".png");}
            dd4->Close();
            eff_EMu_OR_vs_mu0_pt_vs_el0_pt_up->SetName("h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt_up");
            eff_EMu_OR_vs_mu0_pt_vs_el0_pt_up->Write();
            eff_EMu_OR_vs_mu0_pt_vs_el0_pt_down->SetName("h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt_down");
            eff_EMu_OR_vs_mu0_pt_vs_el0_pt_down->Write();
        }
        // NeffWin_EMu_OR_vs_mu0_pt_vs_el0_pt->SetName("h_effWin_EMu_OR_vs_mu0_pt_vs_el0_pt");
        // NeffWin_EMu_OR_vs_mu0_pt_vs_el0_pt->Write();
        // NeffFail_EMu_OR_vs_mu0_pt_vs_el0_pt->SetName("h_effFail_EMu_OR_vs_mu0_pt_vs_el0_pt");
        // NeffFail_EMu_OR_vs_mu0_pt_vs_el0_pt->Write();


        eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->SetName("h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt");
        eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->Write();
        eff_DoubleMu_OR_vs_mu1_pt_vs_eta->SetName("h_DoubleMu_OR__X__allMET_mu1_pt_vs_eta");
        eff_DoubleMu_OR_vs_mu1_pt_vs_eta->Write();
        eff_DoubleMu_OR_vs_mu0_pt_vs_eta->SetName("h_DoubleMu_OR__X__allMET_mu0_pt_vs_eta");
        eff_DoubleMu_OR_vs_mu0_pt_vs_eta->Write();
        if(Skip==false){
            TH2D *eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_up = Get2DScaleFactorHistogram_v2(Eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt,Eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_MC,h_DoubleMu_OR__X__allMET_NumWin_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_DenWin_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_NumFail_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_DenFail_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt,0);
            TH2D *eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_down = Get2DScaleFactorHistogram_v2(Eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt,Eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_MC,h_DoubleMu_OR__X__allMET_NumWin_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_DenWin_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_NumFail_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_DenFail_mu0_pt_vs_mu1_pt,h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt,1);
            TCanvas *ccc3 = new TCanvas("ccc3","ccc3");
            ccc3->cd();
            //eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->GetZaxis()->SetRangeUser(0.90,1.01);
    	    ccc3->SetRightMargin(0.15);
    	    eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_up->SetLabelSize(0.04, "XYZ");
            eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_up->Draw("TEXT E colz");
            ccc3->SetLogy();
            ccc3->SetLogx();
            eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_up->GetXaxis()->SetMoreLogLabels();
            eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_up->GetYaxis()->SetMoreLogLabels();
    	    //DoubleMu->Draw("same");
    	    paveCMS->Draw("same");
    	    if(type != 0){ccc3->SaveAs(output+"SF_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_up_"+yearstring+s+".png");}
            ccc3->Close();

            TCanvas *ddd3 = new TCanvas("ddd3","ddd3");
            ddd3->cd();
            //eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->GetZaxis()->SetRangeUser(0.90,1.01);
    	    ddd3->SetRightMargin(0.15);
    	    eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_down->SetLabelSize(0.04, "XYZ");
            eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_down->Draw("TEXT E colz");
            ddd3->SetLogy();
            ddd3->SetLogx();
            eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_down->GetXaxis()->SetMoreLogLabels();
            eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_down->GetYaxis()->SetMoreLogLabels();
    	    //DoubleMu->Draw("same");
    	    paveCMS->Draw("same");
    	    if(type != 0){ddd3->SaveAs(output+"SF_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_down_"+yearstring+s+".png");}
            ddd3->Close();
            eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_up->SetName("h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt_up");
            eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_up->Write();
            eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_down->SetName("h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt_down");
            eff_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt_down->Write();
        }
        eff_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta->SetName("h_DoubleMu_OR__X__allMET_mu0_eta_vs_mu1_eta");
        eff_DoubleMu_OR_vs_mu0_eta_vs_mu1_eta->Write();
        // NeffWin_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->SetName("h_effWin_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt");
        // NeffWin_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->Write();
        // NeffFail_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->SetName("h_effFail_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt");
        // NeffFail_DoubleMu_OR_vs_mu0_pt_vs_mu1_pt->Write();





}
