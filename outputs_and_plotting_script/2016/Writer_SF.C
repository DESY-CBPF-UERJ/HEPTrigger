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
#include "/home/matheus/Desktop/tt-triggerEfficiency-DL/JSON_files/json.hpp"
using json = nlohmann::json;

void Writer_SF(string path,string path_2,string year){


    //Primeiro vamos ler o arquivo que contém os SF
    TFile *f = new TFile((path+"TriggerSFs_"+year+".root").c_str(),"READ");
    TFile *f_2 = new TFile((path_2+"tt_dileptonic_2DscaleFactors_withSysts_"+year+"ABCD.root").c_str(),"READ");


    //Pegamos a informação dos graficos 2D que contém os valores dos SFs, para diferentes canais
    //ELETRON-ELETRON
    TH2D* h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt_up = (TH2D*) f->Get("h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt_up");
    TH2D* h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt_down = (TH2D*) f->Get("h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt_down");
    //ELETRON-MUON
    TH2D* h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt_up = (TH2D*) f->Get("h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt_up");
    TH2D* h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt_down = (TH2D*) f->Get("h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt_down");
    //MUON-MUON
    TH2D* h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt_up = (TH2D*) f->Get("h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt_up");
    TH2D* h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt_down = (TH2D*) f->Get("h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt_down");

    //HISTOGRAMAS DO SYSTEMATICO
    TH2D* h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt = (TH2D*) f_2->Get("h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt_withSysts");
    //ELETRON-MUON
    TH2D* h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt = (TH2D*) f_2->Get("h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt_withSysts");
    //MUON-MUON
    TH2D* h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt = (TH2D*) f_2->Get("h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt_withSysts");


    //Criando a ESTRUTURA do JSON
    json jsin;
    //Pegando os valores do SF e do seu erro pro canal ELETRON-ELETRON
    
    //jsin["ttbar"]["DoubleEl"]["SF"] = 0;
    //jsin["ttbar"]["DoubleEl"]["SF_err"] = 0;

  	double ratio = 0;
  	double err_up = 0;
    double err_down = 0;
    double bin_x_low = 0;
    double bin_x_up = 0;
    double bin_y_low = 0;
    double bin_y_up = 0;
    double err_syst = 0;
    //LOOP DOUBLE-EL
    TH2D* h_sf = (TH2D*) h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt_up->Clone();
    TH2D* h_sf_2 = (TH2D*) h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt_down->Clone();
  	TH2D* h_sf_syst = (TH2D*) h_DoubleEl_OR__X__allMET_el0_pt_vs_el1_pt->Clone();
    for (int i =1; i < h_sf->GetNbinsX()+1; i++){
    		for (int j =1; j < h_sf->GetNbinsY()+1; j++){
      			ratio = h_sf->GetBinContent(i,j);
                err_up = h_sf->GetBinError(i,j);
                err_down = h_sf_2->GetBinError(i,j);
                bin_x_low = h_sf->GetXaxis()->GetBinLowEdge(i);
                bin_y_low = h_sf->GetYaxis()->GetBinLowEdge(j);
                bin_x_up = h_sf->GetXaxis()->GetBinUpEdge(i);
                bin_y_up = h_sf->GetYaxis()->GetBinUpEdge(j);
                err_syst = h_sf_syst->GetBinError(i,j);
                
                if (ratio == 0){
                  err_up = 0;
                  err_down = 0;
                  err_syst = 0;
                }
                //std::cout<<"Devemos no intervalo de Lep0_pt: "<<bin_x_low<<"-"<<bin_x_up<<" e Lep1_pt: "<<bin_y_low<<"-"<<bin_y_up<<endl; 
                jsin["DoubleEl"].push_back( {{"lep0_pt_min",bin_x_low},{"lep0_pt_max",bin_x_up},{"lep1_pt_min",bin_y_low},{"lep1_pt_max",bin_y_up},{"SF",ratio},{"SF_err_up",err_up},{"SF_err_down",err_down},{"SF_err_syst",err_syst}}  );
            }
  	}
    //LOOP EL-MU
    TH2D* h_sf2 = (TH2D*) h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt_up->Clone();
    TH2D* h_sf2_2 = (TH2D*) h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt_down->Clone();
    TH2D* h_sf2_syst = (TH2D*) h_EMu_OR__X__allMET_mu0_pt_vs_el0_pt->Clone();

    for (int i =1; i < h_sf2->GetNbinsX()+1; i++){
    		for (int j =1; j < h_sf2->GetNbinsY()+1; j++){
      			ratio = h_sf2->GetBinContent(i,j);
                err_up = h_sf2->GetBinError(i,j);
                err_down = h_sf2_2->GetBinError(i,j);
                bin_x_low = h_sf2->GetXaxis()->GetBinLowEdge(i);
                bin_y_low = h_sf2->GetYaxis()->GetBinLowEdge(j);
                bin_x_up = h_sf2->GetXaxis()->GetBinUpEdge(i);
                bin_y_up = h_sf2->GetYaxis()->GetBinUpEdge(j);
                err_syst = h_sf2_syst->GetBinError(i,j);

                if (ratio == 0){
                  err_up = 0;
                  err_down = 0;
                  err_syst = 0;
                }
                //std::cout<<"Devemos no intervalo de Lep0_pt: "<<bin_x_low<<"-"<<bin_x_up<<" e Lep1_pt: "<<bin_y_low<<"-"<<bin_y_up<<endl; 
                jsin["ElMu"].push_back( {{"lep0_pt_min",bin_x_low},{"lep0_pt_max",bin_x_up},{"lep1_pt_min",bin_y_low},{"lep1_pt_max",bin_y_up},{"SF",ratio},{"SF_err_up",err_up},{"SF_err_down",err_down},{"SF_err_syst",err_syst}}  );
            }
  	}
    //LOOP EL-MU
    TH2D* h_sf3 = (TH2D*) h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt_up->Clone();
    TH2D* h_sf3_2 = (TH2D*) h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt_down->Clone();
    TH2D* h_sf3_syst = (TH2D*) h_DoubleMu_OR__X__allMET_mu0_pt_vs_mu1_pt->Clone();
    for (int i =1; i < h_sf3->GetNbinsX()+1; i++){
    		for (int j =1; j < h_sf3->GetNbinsY()+1; j++){
      			ratio = h_sf3->GetBinContent(i,j);
                err_up = h_sf3->GetBinError(i,j);
                err_down = h_sf3_2->GetBinError(i,j);
                bin_x_low = h_sf3->GetXaxis()->GetBinLowEdge(i);
                bin_y_low = h_sf3->GetYaxis()->GetBinLowEdge(j);
                bin_x_up = h_sf3->GetXaxis()->GetBinUpEdge(i);
                bin_y_up = h_sf3->GetYaxis()->GetBinUpEdge(j);
                err_syst = h_sf3_syst->GetBinError(i,j);
                if (ratio == 0){
                  err_up = 0;
                  err_down = 0;
                  err_syst = 0;
                }
                //std::cout<<"Devemos no intervalo de Lep0_pt: "<<bin_x_low<<"-"<<bin_x_up<<" e Lep1_pt: "<<bin_y_low<<"-"<<bin_y_up<<endl; 
                jsin["DoubleMu"].push_back( {{"lep0_pt_min",bin_x_low},{"lep0_pt_max",bin_x_up},{"lep1_pt_min",bin_y_low},{"lep1_pt_max",bin_y_up},{"SF",ratio},{"SF_err_up",err_up},{"SF_err_down",err_down},{"SF_err_syst",err_syst}}  );
            }
  	}
    
    std::cout << jsin.dump(4) << '\n';
    string out_path_name =  "/home/matheus/Desktop/tt-triggerEfficiency-DL/JSON_files/SF_"+year+"_MC.json";
    std::ofstream file(out_path_name);
    file << jsin.dump(4);



 }