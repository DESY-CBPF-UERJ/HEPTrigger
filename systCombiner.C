#include "TFile.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TLatex.h"
#include "TPaveText.h"
#include "TLine.h"
#include "TObjArray.h"

// #include "cmsStyle/tdrStyle.C"
#include "include/setTDRStyle_teliko.C"
#include "cmsStyle/CMS_lumi.C"
#include "include/trigEffStudy.h"
// Object Handlers
#include "src/leptonHandler.C"
#include "src/jetMetHandler.C"

#include <iostream>
#include <iomanip>
#include <fstream>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>


string recoVersion;


void print2DScaleFactorHistogramSimple(TCanvas* c0, TH2D* h2, string triggerSet, string variable,string year)
{
  gStyle->SetPaintTextFormat("1.3f");
  // gStyle->SetPaintTextFormat("1.5f");

  c0->cd();
  c0->SetLogy();
  c0->SetLogx();
  h2->GetXaxis()->SetMoreLogLabels();
  h2->GetYaxis()->SetMoreLogLabels();
  //h2->Draw("colz TEXT");
  h2->Draw("colz e TEXT");
  h2->GetZaxis()->SetLabelSize(0.03);
  // h2->GetZaxis()->SetRangeUser(0.9,1.01);
  h2->GetYaxis()->SetTitleSize(0.05);
  h2->GetXaxis()->SetTitleSize(0.05);

  TLatex ltx1;
  ltx1.SetTextAlign(9);
  ltx1.SetTextFont(62);
  ltx1.SetTextSize(0.025);
  ltx1.SetNDC();
  // ltx1.DrawLatex(0.2, 0.59, triggerSet.c_str());


        // CMS box for plotting the canvases    ///////
        TPaveText *paveCMS = new TPaveText(0.15,0.96,0.91,0.99,"NDC");
        if (year =="2016"){
         paveCMS->AddText("#bf{CMS #it{Preliminary} 2016}        35.9 fb^{-1}    (13 TeV)");
        }
        if (year =="2017"){
         paveCMS->AddText("#bf{CMS #it{Preliminary} 2017}        41.5 fb^{-1}    (13 TeV)");
        }
        if (year =="2018"){
         paveCMS->AddText("#bf{CMS #it{Preliminary} 2018}        59.8 fb^{-1}    (13 TeV)");
        }
        paveCMS->SetFillColor(0);
        paveCMS->SetBorderSize(0);
        paveCMS->SetTextSize(0.04);
        paveCMS->SetTextFont(42);

        paveCMS->Draw();

  //CMS_lumi( c0, 0, 33);

  //c0->SetLeftMargin(0.15);
  //c0->SetRightMargin(0.05);
  //c0->SetBottomMargin(0.15);

  c0->Print( (topDir + "/h_2DSF_" + triggerSet + "_" + variable + ".png").c_str() );

}


TH2D* get2DScaleFactorDifferenceHistogram(TCanvas* c0, TH2D* h_nom, TH2D* h_nJetsHigh, TH2D* h_nJetsLow, TH2D* h_nPVHigh, TH2D* h_nPVLow, string triggerSet, string variable)
{
  TH2D* h_fullDiff = (TH2D*)h_nom->Clone();
  for(int x_b=1; x_b < h_nom->GetNbinsX()+1; x_b++) {
    for(int y_b=1; y_b < h_nom->GetNbinsY()+1; y_b++) {
      h_fullDiff->SetBinContent(x_b, y_b, 0);
      h_fullDiff->SetBinError(x_b, y_b, 0);
    }
  }

  TH2D* h_njh = (TH2D*)h_nom->Clone();
  h_njh->Add(h_nJetsHigh, -1);
  TH2D* h_njl = (TH2D*)h_nom->Clone();
  h_njl->Add(h_nJetsLow, -1);
  TH2D* h_npvh = (TH2D*)h_nom->Clone();
  h_npvh->Add(h_nPVHigh, -1);
  TH2D* h_npvl = (TH2D*)h_nom->Clone();
  h_npvl->Add(h_nPVLow, -1);

  for(int x_b=1; x_b < h_nom->GetNbinsX()+1; x_b++) {
    for(int y_b=1; y_b < h_nom->GetNbinsY()+1; y_b++) {

     
      if( abs(h_njh->GetBinContent(x_b, y_b)) > abs(h_fullDiff->GetBinContent(x_b, y_b))) {
	h_fullDiff->SetBinContent(x_b, y_b, h_njh->GetBinContent(x_b, y_b));
	h_fullDiff->SetBinError  (x_b, y_b, h_njh->GetBinError(x_b, y_b));
      } // end if statement for nJets high

      if( abs(h_njl->GetBinContent(x_b, y_b)) > abs(h_fullDiff->GetBinContent(x_b, y_b))) {
	h_fullDiff->SetBinContent(x_b, y_b, h_njl->GetBinContent(x_b, y_b));
	h_fullDiff->SetBinError  (x_b, y_b, h_njl->GetBinError(x_b, y_b));
      } // end if statement for nJets high

      if( abs(h_npvh->GetBinContent(x_b, y_b)) > abs(h_fullDiff->GetBinContent(x_b, y_b))) {
	h_fullDiff->SetBinContent(x_b, y_b, h_npvh->GetBinContent(x_b, y_b));
	h_fullDiff->SetBinError  (x_b, y_b, h_npvh->GetBinError(x_b, y_b));
      } // end if statement for nJets high

      if( abs(h_npvl->GetBinContent(x_b, y_b)) > abs(h_fullDiff->GetBinContent(x_b, y_b))) {
	h_fullDiff->SetBinContent(x_b, y_b, h_npvl->GetBinContent(x_b, y_b));
	h_fullDiff->SetBinError  (x_b, y_b, h_npvl->GetBinError(x_b, y_b));
      } // end if statement for nJets high

    } // y_b loop
  } // x_b loop


  string maxName = h_fullDiff->GetName();
  h_fullDiff->SetName(  (maxName + "_maxDiff_nJetsNPV").c_str() );
  h_fullDiff->SetTitle( (maxName + "_maxDiff_nJetsNPV").c_str() );

  //print2DScaleFactorHistogramSimple(c0, h_fullDiff, triggerSet, (variable + "_maxDiff_nJetsNPV").c_str() );

  return h_fullDiff;

}



TH2D* get2DScaleFactorDifferenceHistogram_v2(TCanvas* c0, TH2D* h_nom, TH2D* h_nJetsHigh, TH2D* h_nJetsLow, TH2D* h_nPVHigh, TH2D* h_nPVLow, TH2D* h_METHigh, TH2D* h_METLow, string triggerSet, string variable)
{

  TH2D* h_fullDiff = (TH2D*)h_nom->Clone();
  for(int x_b=1; x_b < h_nom->GetNbinsX()+1; x_b++) {
    for(int y_b=1; y_b < h_nom->GetNbinsY()+1; y_b++) {
      h_fullDiff->SetBinContent(x_b, y_b, 0);
      h_fullDiff->SetBinError(x_b, y_b, 0);
    }
  }

  TH2D* h_njh = (TH2D*)h_nom->Clone();
  h_njh->Add(h_nJetsHigh, -1);
  TH2D* h_njl = (TH2D*)h_nom->Clone();
  h_njl->Add(h_nJetsLow, -1);
  TH2D* h_npvh = (TH2D*)h_nom->Clone();
  h_npvh->Add(h_nPVHigh, -1);
  TH2D* h_npvl = (TH2D*)h_nom->Clone();
  h_npvl->Add(h_nPVLow, -1);
  TH2D* h_meth = (TH2D*)h_nom->Clone();
  h_meth->Add(h_METHigh, -1);
  TH2D* h_metl = (TH2D*)h_nom->Clone();
  h_metl->Add(h_METLow, -1);
  
 


  std::cout<<"======================================================================"<<endl;
  for(int x_b=1; x_b < h_nom->GetNbinsX()+1; x_b++) {
    for(int y_b=1; y_b < h_nom->GetNbinsY()+1; y_b++) {


      // std::cout<<"Valor do h_nom: "<<h_nom->GetBinContent(x_b, y_b)<<endl;
      // std::cout<<"Valor do h_njh: "<<h_njh->GetBinContent(x_b, y_b)<<endl;
      // std::cout<<"Valor do h_njl: "<<h_njl->GetBinContent(x_b, y_b)<<endl;
      // std::cout<<"Valor do h_npvh: "<<h_npvh->GetBinContent(x_b, y_b)<<endl;
      // std::cout<<"Valor do h_npvl: "<<h_npvl->GetBinContent(x_b, y_b)<<endl;
      // std::cout<<"Valor do h_MEtLow: "<<h_metl->GetBinContent(x_b, y_b)<<endl;
      // std::cout<<"Valor do h_METHigh: "<<h_meth->GetBinContent(x_b, y_b)<<endl;



      if( abs(h_njh->GetBinContent(x_b, y_b)) > abs(h_fullDiff->GetBinContent(x_b, y_b))) {
	h_fullDiff->SetBinContent(x_b, y_b, h_njh->GetBinContent(x_b, y_b));
	h_fullDiff->SetBinError  (x_b, y_b, h_njh->GetBinError(x_b, y_b));
      } // end if statement for nJets high

      if( abs(h_njl->GetBinContent(x_b, y_b)) > abs(h_fullDiff->GetBinContent(x_b, y_b))) {
	h_fullDiff->SetBinContent(x_b, y_b, h_njl->GetBinContent(x_b, y_b));
	h_fullDiff->SetBinError  (x_b, y_b, h_njl->GetBinError(x_b, y_b));
      } // end if statement for nJets high

      if( abs(h_npvh->GetBinContent(x_b, y_b)) > abs(h_fullDiff->GetBinContent(x_b, y_b))) {
	h_fullDiff->SetBinContent(x_b, y_b, h_npvh->GetBinContent(x_b, y_b));
	h_fullDiff->SetBinError  (x_b, y_b, h_npvh->GetBinError(x_b, y_b));
      } // end if statement for nJets high

      if( abs(h_npvl->GetBinContent(x_b, y_b)) > abs(h_fullDiff->GetBinContent(x_b, y_b))) {
	h_fullDiff->SetBinContent(x_b, y_b, h_npvl->GetBinContent(x_b, y_b));
	h_fullDiff->SetBinError  (x_b, y_b, h_npvl->GetBinError(x_b, y_b));
      } // end if statement for nJets high

      if( abs(h_meth->GetBinContent(x_b, y_b)) > abs(h_fullDiff->GetBinContent(x_b, y_b))) {
	h_fullDiff->SetBinContent(x_b, y_b, h_meth->GetBinContent(x_b, y_b));
	h_fullDiff->SetBinError  (x_b, y_b, h_meth->GetBinError(x_b, y_b));
      } // end if statement for MET high

      if( abs(h_metl->GetBinContent(x_b, y_b)) > abs(h_fullDiff->GetBinContent(x_b, y_b))) {
	h_fullDiff->SetBinContent(x_b, y_b, h_metl->GetBinContent(x_b, y_b));
	h_fullDiff->SetBinError  (x_b, y_b, h_metl->GetBinError(x_b, y_b));
      } // end if statement for MET low

    // cout<<"h_fullDiff(x_b, y_b) "<<abs(h_fullDiff->GetBinContent(x_b, y_b))<<endl;
    } // y_b loop
  } // x_b loop



  string maxName = h_fullDiff->GetName();
  h_fullDiff->SetName(  (maxName + "_maxDiff_nJetsNPVMET").c_str() );
  std::cout<<(maxName + "_maxDiff_nJetsNPVMET").c_str() <<endl;
  h_fullDiff->SetTitle( (maxName + "_maxDiff_nJetsNPVMET").c_str() );

  //print2DScaleFactorHistogramSimple(c0, h_fullDiff, triggerSet, (variable + "_maxDiff_nJetsNPVMET").c_str() );

  delete h_npvl;
  delete h_npvh;
  delete h_metl;
  delete h_meth;
  delete h_njl;
  delete h_njh;

  return h_fullDiff;

}


TH2D* make2DSFwithSysts(TCanvas* c0, TObjArray* array, string triggerSet, string variable,string path,string year){
  string hist = ("h_" + triggerSet + "_" + variable).c_str();


  std::cout<<"string:"<<path+"/TriggerSFs_"+year+".root"<<endl;
  std::cout<<"hist:"<<hist<<endl;

  TH2D* h_nom       = (TH2D*) ((TFile*)array->FindObject((path+"/TriggerSFs_"+year+".root").c_str()))->Get( hist.c_str() );
  TH2D* h_periodDep = (TH2D*) ((TFile*)array->FindObject((path+"/TriggerSFs_"+year+"_lumi.root").c_str()))->Get( hist.c_str() );
  TH2D* h_highNjets = (TH2D*) ((TFile*)array->FindObject((path+"/TriggerSFs_"+year+"_NJETSHIGH.root").c_str()))->Get( hist.c_str() );
  TH2D* h_lowNjets  = (TH2D*) ((TFile*)array->FindObject((path+"/TriggerSFs_"+year+"_NJETSLOW.root").c_str()))->Get( hist.c_str() );
  TH2D* h_lowNPV    = (TH2D*) ((TFile*)array->FindObject((path+"/TriggerSFs_"+year+"_NPVLOW.root").c_str()))->Get( hist.c_str() );
  TH2D* h_highNPV   = (TH2D*) ((TFile*)array->FindObject((path+"/TriggerSFs_"+year+"_NPVHIGH.root").c_str()))->Get( hist.c_str() );
  TH2D* h_lowMET    = (TH2D*) ((TFile*)array->FindObject((path+"/TriggerSFs_"+year+"_METLOW.root").c_str()))->Get( hist.c_str() );
  TH2D* h_highMET   = (TH2D*) ((TFile*)array->FindObject((path+"/TriggerSFs_"+year+"_METHIGH.root").c_str()))->Get( hist.c_str() );

  TH2D* h_ExNumMu0      = (TH2D*) ((TFile*)array->FindObject((path+"/Systematic_uncertain_ExNumMu0.root").c_str()))->Get( hist.c_str() );
  TH2D* h_ExNumMu1      = (TH2D*) ((TFile*)array->FindObject((path+"/Systematic_uncertain_ExNumMu1.root").c_str()))->Get( hist.c_str() );
  TH2D* h_ExNumMu2      = (TH2D*) ((TFile*)array->FindObject((path+"/Systematic_uncertain_ExNumMu2.root").c_str()))->Get( hist.c_str() );
  TH2D* h_ExNumEl0      = (TH2D*) ((TFile*)array->FindObject((path+"/Systematic_uncertain_ExNumEl0.root").c_str()))->Get( hist.c_str() );
  TH2D* h_ExNumEl1      = (TH2D*) ((TFile*)array->FindObject((path+"/Systematic_uncertain_ExNumEl1.root").c_str()))->Get( hist.c_str() );
  TH2D* h_ExNumEl2      = (TH2D*) ((TFile*)array->FindObject((path+"/Systematic_uncertain_ExNumEl2.root").c_str()))->Get( hist.c_str() );
  TH2D* h_DeltaRZone0      = (TH2D*) ((TFile*)array->FindObject((path+"/Systematic_uncertain_DeltaRZone0.root").c_str()))->Get( hist.c_str() );
  TH2D* h_DeltaRZone1      = (TH2D*) ((TFile*)array->FindObject((path+"/Systematic_uncertain_DeltaRZone1.root").c_str()))->Get( hist.c_str() );
  TH2D* h_DeltaRZone2      = (TH2D*) ((TFile*)array->FindObject((path+"/Systematic_uncertain_DeltaRZone2.root").c_str()))->Get( hist.c_str() );
  TH2D* h_DeltaRZone3      = (TH2D*) ((TFile*)array->FindObject((path+"/Systematic_uncertain_DeltaRZone3.root").c_str()))->Get( hist.c_str() );



  // *** A. Set correlation error

  double totalCorrelationBinError = 0.0;
  //2016
  // Correlation between h_HLT_DoubleEl_OR__vs__HLT_allMET = 	0.999668 +/- 0.00241962
  // Difference h_HLT_DoubleEl_OR__vs__HLT_allMET = 	0.000332424 +/- 0.00241962
  // Correlation between h_HLT_EMu_OR__vs__HLT_allMET = 	0.996689 +/- 0.00113682
  // Difference h_HLT_EMu_OR__vs__HLT_allMET = 	0.00331054 +/- 0.00113682
  // Correlation between h_HLT_DoubleMu_OR__vs__HLT_allMET = 	0.999203 +/- 0.00155332
  // Difference h_HLT_DoubleMu_OR__vs__HLT_allMET = 	0.000796615 +/- 0.00155332
  // if (triggerSet.find("DoubleEl")!=string::npos)      totalCorrelationBinError = 0.001;
  // else if (triggerSet.find("DoubleMu")!=string::npos) totalCorrelationBinError = 0.001;
  // else if (triggerSet.find("EMu")!=string::npos)      totalCorrelationBinError = 0.003;
  //2017
    // Correlation between h_HLT_DoubleEl_OR__vs__HLT_allMET = 	0.999232 +/- 0.00291903
    // Difference h_HLT_DoubleEl_OR__vs__HLT_allMET = 	0.00076777 +/- 0.00291903
    // Correlation between h_HLT_EMu_OR__vs__HLT_allMET = 	1.00008 +/- 0.00199728
    // Difference h_HLT_EMu_OR__vs__HLT_allMET = 	-7.9924e-05 +/- 0.00199728
    // Correlation between h_HLT_DoubleMu_OR__vs__HLT_allMET = 	1.00285 +/- 0.00286695
    // Difference h_HLT_DoubleMu_OR__vs__HLT_allMET = 	-0.00284588 +/- 0.00286695
  // if (triggerSet.find("DoubleEl")!=string::npos)      totalCorrelationBinError = 0.001;
  // else if (triggerSet.find("DoubleMu")!=string::npos) totalCorrelationBinError = 0.003;
  // else if (triggerSet.find("EMu")!=string::npos)      totalCorrelationBinError = 0.001;
  //2018
    //   Correlation between h_HLT_DoubleEl_OR__vs__HLT_allMET = 	0.998466 +/- 0.00330602
    // Difference h_HLT_DoubleEl_OR__vs__HLT_allMET = 	0.00153408 +/- 0.00330602
    // Correlation between h_HLT_EMu_OR__vs__HLT_allMET = 	0.995298 +/- 0.00139482
    // Difference h_HLT_EMu_OR__vs__HLT_allMET = 	0.00470158 +/- 0.00139482
    // Correlation between h_HLT_DoubleMu_OR__vs__HLT_allMET = 	0.999155 +/- 0.00198071
    // Difference h_HLT_DoubleMu_OR__vs__HLT_allMET = 	0.000845338 +/- 0.00198071
  if (triggerSet.find("DoubleEl")!=string::npos)      totalCorrelationBinError = 0.002;
  else if (triggerSet.find("DoubleMu")!=string::npos) totalCorrelationBinError = 0.001;
  else if (triggerSet.find("EMu")!=string::npos)      totalCorrelationBinError = 0.005;


  // *** B. Get period dependence error (lumi-weighted)
  TH2D* nom_with_systs  = (TH2D*)h_nom->Clone();
  TH2D* syst_periodDep  = (TH2D*)h_periodDep->Clone();
  //print2DScaleFactorHistogramSimple(c0, h_periodDep, triggerSet, variable.c_str() );
  print2DScaleFactorHistogramSimple(c0, h_periodDep, triggerSet, (variable + "_lumiDiff_periodDep").c_str() ,year);


  // *** C. first get max diff of high/low nJets/nPV w.r.t. nominal
  //TH2D* syst_highLowNjetsNPV = get2DScaleFactorDifferenceHistogram(c0, h_nom, h_highNjets, h_lowNjets, h_highNPV, h_lowNPV, triggerSet, variable);
  TH2D* syst_highLowNjetsNPVMET = get2DScaleFactorDifferenceHistogram_v2(c0, h_nom, h_highNjets, h_lowNjets, h_highNPV, h_lowNPV, h_highMET, h_lowMET, triggerSet, variable);

  std::cout<<"Histograma: "<<(variable + "_withSysts").c_str()<<endl;
  // *** D. then calculate full error envelope
  double binError = 0;
  double region_error = 0;
  for(int x_b=1; x_b < nom_with_systs->GetNbinsX()+1; x_b++) {
    for(int y_b=1; y_b < nom_with_systs->GetNbinsY()+1; y_b++) {
      // std::cout<<"Valor da incerteza dos periodos ("<<x_b<<","<<y_b<<"):"<<syst_periodDep->GetBinContent(x_b, y_b)<<endl;
      // std::cout<<"Valor da incerteza das regiões ("<<x_b<<","<<y_b<<"):"<<syst_highLowNjetsNPVMET->GetBinContent(x_b, y_b)<<endl;
      // std::cout<<"Valor da incerteza da região ExNumMu0 ("<<x_b<<","<<y_b<<"):"<<h_ExNumMu0->GetBinContent(x_b, y_b)<<endl;
      // std::cout<<"Valor da incerteza da região ExNumMu1 ("<<x_b<<","<<y_b<<"):"<<h_ExNumMu1->GetBinContent(x_b, y_b)<<endl;
      // std::cout<<"Valor da incerteza da região ExNumMu2 ("<<x_b<<","<<y_b<<"):"<<h_ExNumMu2->GetBinContent(x_b, y_b)<<endl;
      // if (abs(h_ExNumMu2->GetBinContent(x_b, y_b)) > 0.3){
      //   cout<<"FODEU DE VEZ"<<endl;
      // }
      // std::cout<<"Valor da incerteza da região ExNumEl0 ("<<x_b<<","<<y_b<<"):"<<h_ExNumEl0->GetBinContent(x_b, y_b)<<endl;
      // std::cout<<"Valor da incerteza da região ExNumEl1 ("<<x_b<<","<<y_b<<"):"<<h_ExNumEl1->GetBinContent(x_b, y_b)<<endl;
      // std::cout<<"Valor da incerteza da região ExNumEl2 ("<<x_b<<","<<y_b<<"):"<<h_ExNumEl2->GetBinContent(x_b, y_b)<<endl;
      // std::cout<<"Valor da incerteza da região DeltaRZona0 ("<<x_b<<","<<y_b<<"):"<<h_DeltaRZone0->GetBinContent(x_b, y_b)<<endl;
      // std::cout<<"Valor da incerteza da região DeltaRZona1 ("<<x_b<<","<<y_b<<"):"<<h_DeltaRZone1->GetBinContent(x_b, y_b)<<endl;
      // std::cout<<"Valor da incerteza da região DeltaRZona2 ("<<x_b<<","<<y_b<<"):"<<h_DeltaRZone2->GetBinContent(x_b, y_b)<<endl;
      // std::cout<<"Valor da incerteza da região DeltaRZona3 ("<<x_b<<","<<y_b<<"):"<<h_DeltaRZone3->GetBinContent(x_b, y_b)<<endl;
      region_error = 0;

      if( abs(syst_highLowNjetsNPVMET->GetBinContent(x_b, y_b)) > abs(region_error)) {
	      region_error = syst_highLowNjetsNPVMET->GetBinContent(x_b, y_b);
      } // end if statement for nJets high
      //  if( abs(h_ExNumMu0->GetBinContent(x_b, y_b)) > abs(region_error)) {
	    //   region_error = h_ExNumMu0->GetBinContent(x_b, y_b);
      // } // end if statement for nJets high
      //  if( abs(h_ExNumMu1->GetBinContent(x_b, y_b)) > abs(region_error)) {
	    //   region_error = h_ExNumMu1->GetBinContent(x_b, y_b);
      // } // end if statement for nJets high
      //  if( abs(h_ExNumMu2->GetBinContent(x_b, y_b)) > abs(region_error)) {
	    //   region_error = h_ExNumMu2->GetBinContent(x_b, y_b);
      // } // end if statement for nJets high
      //  if( abs(h_ExNumEl0->GetBinContent(x_b, y_b)) > abs(region_error)) {
	    //   region_error = h_ExNumEl0->GetBinContent(x_b, y_b);
      // } // end if statement for nJets high
      //  if( abs(h_ExNumEl1->GetBinContent(x_b, y_b)) > abs(region_error)) {
	    //   region_error = h_ExNumEl1->GetBinContent(x_b, y_b);
      // } // end if statement for nJets high
      //  if( abs(h_ExNumEl2->GetBinContent(x_b, y_b)) > abs(region_error)) {
	    //   region_error = h_ExNumEl2->GetBinContent(x_b, y_b);
      // } // end if statement for nJets high
       if( abs(h_DeltaRZone0->GetBinContent(x_b, y_b)) > abs(region_error)) {
	      region_error = h_DeltaRZone0->GetBinContent(x_b, y_b);
      } // end if statement for nJets high
       if( abs(h_DeltaRZone1->GetBinContent(x_b, y_b)) > abs(region_error)) {
	      region_error = h_DeltaRZone1->GetBinContent(x_b, y_b);
      } // end if statement for nJets high
       if( abs(h_DeltaRZone2->GetBinContent(x_b, y_b)) > abs(region_error)) {
	      region_error = h_DeltaRZone2->GetBinContent(x_b, y_b);
      } // end if statement for nJets high
       if( abs(h_DeltaRZone2->GetBinContent(x_b, y_b)) > abs(region_error)) {
	      region_error = h_DeltaRZone3->GetBinContent(x_b, y_b);
      } // end if statement for nJets high

      // binError = abs(h_ExNumEl1->GetBinContent(x_b, y_b));
      binError = sqrt(syst_periodDep->GetBinContent(x_b, y_b)*syst_periodDep->GetBinContent(x_b, y_b) + region_error*region_error + totalCorrelationBinError*totalCorrelationBinError); 
      //binError = sqrt( nom_with_systs->GetBinError(x_b, y_b)*nom_with_systs->GetBinError(x_b, y_b) + syst_periodDep->GetBinContent(x_b, y_b)*syst_periodDep->GetBinContent(x_b, y_b) + syst_highLowNjetsNPV->GetBinContent(x_b, y_b)*syst_highLowNjetsNPV->GetBinContent(x_b, y_b) + totalCorrelationBinError*totalCorrelationBinError);
      // /binError = sqrt( nom_with_systs->GetBinError(x_b, y_b)*nom_with_systs->GetBinError(x_b, y_b) + syst_periodDep->GetBinContent(x_b, y_b)*syst_periodDep->GetBinContent(x_b, y_b) + syst_highLowNjetsNPVMET->GetBinContent(x_b, y_b)*syst_highLowNjetsNPVMET->GetBinContent(x_b, y_b) + totalCorrelationBinError*totalCorrelationBinError);
      // binError = sqrt(syst_periodDep->GetBinContent(x_b, y_b)*syst_periodDep->GetBinContent(x_b, y_b) + syst_highLowNjetsNPVMET->GetBinContent(x_b, y_b)*syst_highLowNjetsNPVMET->GetBinContent(x_b, y_b) + totalCorrelationBinError*totalCorrelationBinError);
      //binError = sqrt( nom_with_systs->GetBinError(x_b, y_b)*nom_with_systs->GetBinError(x_b, y_b) + syst_highLowNjetsNPVMET->GetBinContent(x_b, y_b)*syst_highLowNjetsNPVMET->GetBinContent(x_b, y_b) + totalCorrelationBinError*totalCorrelationBinError);
      nom_with_systs->SetBinContent(x_b, y_b, binError);
      // nom_with_systs->SetBinError(x_b, y_b, 0);
    }
  }
  string hname = nom_with_systs->GetName();
  nom_with_systs->SetName(  (hname + "_withSysts").c_str() );
  nom_with_systs->SetTitle( (hname + "_withSysts").c_str() );

  print2DScaleFactorHistogramSimple(c0, nom_with_systs, triggerSet, (variable + "_withSysts").c_str() ,year);

  delete syst_highLowNjetsNPVMET;
  delete syst_periodDep;

  return nom_with_systs;
}

/*
TH2D* make2DSFwithSysts(TCanvas* c0, TFile* nom, TFile* periodDep, TFile* highMET, TFile* lowMET, string triggerSet, string variable){
  string hist = ("h_" + triggerSet + "_" + variable).c_str();
  TH2D* h_nom       = (TH2D*)nom->Get( hist.c_str() );
  TH2D* h_periodDep = (TH2D*)periodDep->Get( (hist + "_maxDiff_periodDep").c_str() );
  TH2D* h_highMET   = (TH2D*)highMET->Get( hist.c_str() );
  TH2D* h_lowMET    = (TH2D*)lowMET->Get( hist.c_str() );

  TH2D* nom_with_systs  = (TH2D*)h_nom->Clone();
  TH2D* syst_periodDep  = (TH2D*)h_periodDep->Clone();
  TH2D* syst_highLowMET = (TH2D*)h_highMET->Clone();
  syst_highLowMET->Add(h_lowMET, -1);
  syst_highLowMET->Scale(0.5);

  double binError = 0;
  for(int x_b=1; x_b < nom_with_systs->GetNbinsX()+1; x_b++) {
    for(int y_b=1; y_b < nom_with_systs->GetNbinsY()+1; y_b++) {
      binError = sqrt( nom_with_systs->GetBinError(x_b, y_b)*nom_with_systs->GetBinError(x_b, y_b) + syst_periodDep->GetBinContent(x_b, y_b)*syst_periodDep->GetBinContent(x_b, y_b) + syst_highLowMET->GetBinContent(x_b, y_b)*syst_highLowMET->GetBinContent(x_b, y_b) );
      nom_with_systs->SetBinError(x_b, y_b, binError);
    }
  }
  string hname = nom_with_systs->GetName();
  nom_with_systs->SetName(  (hname + "_withSysts").c_str() );
  nom_with_systs->SetTitle( (hname + "_withSysts").c_str() );

  print2DScaleFactorHistogramSimple(c0, nom_with_systs, triggerSet, (variable + "_withSysts").c_str() );

  return nom_with_systs;
}
*/

void systCombiner(string path,string out_path, string year)
{
  
  topDir = out_path+"Final_"+year+"_SFs_with_full_systematics";
  struct stat sb;
  if (!(stat(topDir.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))){
                cout << "top-level director, " << topDir << " , DNE. Creating now" << endl;
                mkdir(topDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH);
  }

  //gROOT->LoadMacro("/afs/cern.ch/work/c/ckoraka/codes/setTDRStyle_teliko.C");
  // setTDRStyle();
  setTDRStyle_teliko();

  // ** 0. Drawing options
  //TCanvas* c1 = new TCanvas("c1", "c1", 800, 800);
  TCanvas* c1 = new TCanvas("c1", "c1");

  // * A. CMS Style
  // setTDRStyle();
  setTDRStyle_teliko();
  //writeExtraText = true;       // if extra text
  //extraText  = "Internal";  // default extra text is "Preliminary"
  //lumi_sqrtS = "#sqrt{s} = 13 TeV";       // used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)
  int iPeriod = 0;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 0=free form (uses lumi_sqrtS)
  //cmsTextSize = 0.3;
  //lumiTextSize = 0.3;

  TObjArray* f_infiles = new TObjArray();

  // *** 1. Set input and output files
  // std::cout<<"string:"<<path+"/TriggerSFs_2016.root"<<endl;
  if(year == "2016"){
    TFile *f_nom       = new TFile((path+"/TriggerSFs_2016.root").c_str(), "READ");
    TFile *f_periodDep = new TFile((path+"/TriggerSFs_2016_lumi.root").c_str(), "READ");
    TFile *f_highNjets = new TFile((path+"/TriggerSFs_2016_NJETSHIGH.root").c_str(), "READ");
    TFile *f_lowNjets  = new TFile((path+"/TriggerSFs_2016_NJETSLOW.root").c_str(), "READ");
    TFile *f_lowNPV    = new TFile((path+"/TriggerSFs_2016_NPVLOW.root").c_str(), "READ");
    TFile *f_highNPV   = new TFile((path+"/TriggerSFs_2016_NPVHIGH.root").c_str(), "READ");
    TFile *f_lowMET    = new TFile((path+"/TriggerSFs_2016_METLOW.root").c_str(), "READ");
    TFile *f_highMET   = new TFile((path+"/TriggerSFs_2016_METHIGH.root").c_str(), "READ");

    f_infiles->AddLast(f_nom);
    f_infiles->AddLast(f_periodDep);
    f_infiles->AddLast(f_highNjets);
    f_infiles->AddLast(f_lowNjets);
    f_infiles->AddLast(f_highNPV);
    f_infiles->AddLast(f_lowNPV);
    f_infiles->AddLast(f_highMET);
    f_infiles->AddLast(f_lowMET);
  }
  if (year == "2017"){
    TFile *f_nom       = new TFile((path+"/TriggerSFs_2017.root").c_str(), "READ");
    TFile *f_periodDep = new TFile((path+"/TriggerSFs_2017_lumi.root").c_str(), "READ");
    TFile *f_highNjets = new TFile((path+"/TriggerSFs_2017_NJETSHIGH.root").c_str(), "READ");
    TFile *f_lowNjets  = new TFile((path+"/TriggerSFs_2017_NJETSLOW.root").c_str(), "READ");
    TFile *f_lowNPV    = new TFile((path+"/TriggerSFs_2017_NPVLOW.root").c_str(), "READ");
    TFile *f_highNPV   = new TFile((path+"/TriggerSFs_2017_NPVHIGH.root").c_str(), "READ");
    TFile *f_lowMET    = new TFile((path+"/TriggerSFs_2017_METLOW.root").c_str(), "READ");
    TFile *f_highMET   = new TFile((path+"/TriggerSFs_2017_METHIGH.root").c_str(), "READ");

    f_infiles->AddLast(f_nom);
    f_infiles->AddLast(f_periodDep);
    f_infiles->AddLast(f_highNjets);
    f_infiles->AddLast(f_lowNjets);
    f_infiles->AddLast(f_highNPV);
    f_infiles->AddLast(f_lowNPV);
    f_infiles->AddLast(f_highMET);
    f_infiles->AddLast(f_lowMET);
  } 
  if (year == "2018"){
    TFile *f_nom       = new TFile((path+"/TriggerSFs_2018.root").c_str(), "READ");
    TFile *f_periodDep = new TFile((path+"/TriggerSFs_2018_lumi.root").c_str(), "READ");
    TFile *f_highNjets = new TFile((path+"/TriggerSFs_2018_NJETSHIGH.root").c_str(), "READ");
    TFile *f_lowNjets  = new TFile((path+"/TriggerSFs_2018_NJETSLOW.root").c_str(), "READ");
    TFile *f_lowNPV    = new TFile((path+"/TriggerSFs_2018_NPVLOW.root").c_str(), "READ");
    TFile *f_highNPV   = new TFile((path+"/TriggerSFs_2018_NPVHIGH.root").c_str(), "READ");
    TFile *f_lowMET    = new TFile((path+"/TriggerSFs_2018_METLOW.root").c_str(), "READ");
    TFile *f_highMET   = new TFile((path+"/TriggerSFs_2018_METHIGH.root").c_str(), "READ");
    
    f_infiles->AddLast(f_nom);
    f_infiles->AddLast(f_periodDep);
    f_infiles->AddLast(f_highNjets);
    f_infiles->AddLast(f_lowNjets);
    f_infiles->AddLast(f_highNPV);
    f_infiles->AddLast(f_lowNPV);
    f_infiles->AddLast(f_highMET);
    f_infiles->AddLast(f_lowMET);
  }



  TFile *f_ExNumMu0   = new TFile((path+"/Systematic_uncertain_ExNumMu0.root").c_str(), "READ");
  TFile *f_ExNumMu1   = new TFile((path+"/Systematic_uncertain_ExNumMu1.root").c_str(), "READ");
  TFile *f_ExNumMu2   = new TFile((path+"/Systematic_uncertain_ExNumMu2.root").c_str(), "READ");
  TFile *f_ExNumEl0   = new TFile((path+"/Systematic_uncertain_ExNumEl0.root").c_str(), "READ");
  TFile *f_ExNumEl1   = new TFile((path+"/Systematic_uncertain_ExNumEl1.root").c_str(), "READ");
  TFile *f_ExNumEl2   = new TFile((path+"/Systematic_uncertain_ExNumEl2.root").c_str(), "READ");

  TFile *f_DeltaRZone0   = new TFile((path+"/Systematic_uncertain_DeltaRZone0.root").c_str(), "READ");
  TFile *f_DeltaRZone1   = new TFile((path+"/Systematic_uncertain_DeltaRZone1.root").c_str(), "READ");
  TFile *f_DeltaRZone2   = new TFile((path+"/Systematic_uncertain_DeltaRZone2.root").c_str(), "READ");
  TFile *f_DeltaRZone3   = new TFile((path+"/Systematic_uncertain_DeltaRZone3.root").c_str(), "READ");
  
  //  TFile *f_outSysts  = new TFile( (path+"/tt_dileptonic_2DscaleFactors_withSysts_2016BCDEFGH_"+date+".root").c_str(), "RECREATE");
  // TFile *f_outSysts  = new TFile( ("tt_dileptonic_2DscaleFactors_withSysts_2017BCDEF_"+date+".root").c_str(), "RECREATE");
  
  //TFile *f_outSysts  = new TFile( ("tth_dileptonic_2DscaleFactors_MC_PU-lep_SFs_withSysts_2017BCDEF_"+date+".root").c_str(), "RECREATE");
  //TFile *f_outSysts  = new TFile( ("tth_dileptonic_2DscaleFactors_MC_PU-lep_SFs_withSysts_2018ABCD_"+date+".root").c_str(), "RECREATE");

  TFile *f_outSysts  = new TFile( (topDir+"/tt_dileptonic_2DscaleFactors_withSysts_"+year+"ABCD.root").c_str(), "RECREATE");

  
  f_infiles->AddLast(f_ExNumMu0);
  f_infiles->AddLast(f_ExNumMu1);
  f_infiles->AddLast(f_ExNumMu2);
  f_infiles->AddLast(f_ExNumEl0);
  f_infiles->AddLast(f_ExNumEl1);
  f_infiles->AddLast(f_ExNumEl2);
  f_infiles->AddLast(f_DeltaRZone0);
  f_infiles->AddLast(f_DeltaRZone1);
  f_infiles->AddLast(f_DeltaRZone2);
  f_infiles->AddLast(f_DeltaRZone3);



  // *** 2. Get Histograms
  TH2D* h_DoubleMu_mu0_pt_eta      = make2DSFwithSysts(c1, f_infiles, "DoubleMu_OR__X__allMET", "mu0_pt_vs_eta",path,year);
  TH2D* h_DoubleMu_mu1_pt_eta      = make2DSFwithSysts(c1, f_infiles, "DoubleMu_OR__X__allMET", "mu1_pt_vs_eta",path,year);
  TH2D* h_DoubleMu_mu0_pt_mu1_pt   = make2DSFwithSysts(c1, f_infiles, "DoubleMu_OR__X__allMET", "mu0_pt_vs_mu1_pt",path,year);
  TH2D* h_DoubleMu_mu0_eta_mu1_eta = make2DSFwithSysts(c1, f_infiles, "DoubleMu_OR__X__allMET", "mu0_eta_vs_mu1_eta",path,year);


  TH2D* h_DoubleEl_el0_pt_eta      = make2DSFwithSysts(c1, f_infiles, "DoubleEl_OR__X__allMET", "el0_pt_vs_eta",path,year);
  TH2D* h_DoubleEl_el1_pt_eta      = make2DSFwithSysts(c1, f_infiles, "DoubleEl_OR__X__allMET", "el1_pt_vs_eta",path,year);
  TH2D* h_DoubleEl_el0_pt_el1_pt   = make2DSFwithSysts(c1, f_infiles, "DoubleEl_OR__X__allMET", "el0_pt_vs_el1_pt",path,year);
  TH2D* h_DoubleEl_el0_eta_el1_eta = make2DSFwithSysts(c1, f_infiles, "DoubleEl_OR__X__allMET", "el0_eta_vs_el1_eta",path,year);

  TH2D* h_EMu_mu0_pt_eta      = make2DSFwithSysts(c1, f_infiles, "EMu_OR__X__allMET", "mu0_pt_vs_eta",path,year);
  TH2D* h_EMu_el0_pt_eta      = make2DSFwithSysts(c1, f_infiles, "EMu_OR__X__allMET", "el0_pt_vs_eta",path,year);
  TH2D* h_EMu_mu0_pt_el0_pt   = make2DSFwithSysts(c1, f_infiles, "EMu_OR__X__allMET", "mu0_pt_vs_el0_pt",path,year);
  TH2D* h_EMu_mu0_eta_el0_eta = make2DSFwithSysts(c1, f_infiles, "EMu_OR__X__allMET", "mu0_eta_vs_el0_eta",path,year);

  f_outSysts->Write();
  f_outSysts->Close();

  return;
}
