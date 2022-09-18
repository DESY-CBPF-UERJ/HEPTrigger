// Author:  Ben Tannenwald
// Date:    Mar 1, 2018
// Purpose: Make header for histogramming functions

#include <TFile.h>
#include <TDirectory.h>
#include <TTree.h>
#include <TBranch.h>
#include <TCanvas.h>
#include <TH2.h>
#include <TLatex.h>
#include <TString.h>
#include <TObjArray.h>
#include <TEfficiency.h>
#include <TGraphAsymmErrors.h>

// #include "../cmsStyle/tdrStyle.C"
#include "setTDRStyle_teliko.C"
#include "../cmsStyle/CMS_lumi.C"
//#include "crossSections.h"

#include <sys/stat.h>
#include <sys/types.h>

#include <iostream>
#include <iomanip>      // std::setprecision
#include <sstream>

void fillHistogramsByStream(leptonHandler lepTool, jetMetHandler jetMetTool, TObjArray* array, string nameHLT, string filename, string stream="",bool N_eff= false)
{

	// initialization
	// TH1D* h0 = new TH1D();
	// TH2D* h2 = new TH2D();
	TH1D* h0;
	TH2D* h2;
	if (stream !=  "")
		stream = ("_" + stream).c_str();


	double totalWeight = 1.;

	// ** I. lepton SFs
	double lepSF = 1.;
	double muonSF = 1.;
	double electronSF = 1.;
	double pileup_SF = 1.;
    double genWeight = 1.;
	double evtWeight = 1.;

	if (lepTool.isMC) {
		// evtWeight = 1;
		evtWeight = jetMetTool.evtWeight;
		if (N_eff){
			evtWeight = evtWeight*evtWeight;
		}
	}
	// totalWeight*=lepSF;
	// totalWeight*=pileup_SF;
	//std::cout<<"Peso "<<evtWeight<<std::endl;
	//totalWeight=1;
	//if(totalWeight==0){
	//	std::cout<<"uepa"<<std::endl;
	//}
	//if(evtWeight < 0){
	//	evtWeight = 0;
	//}
	//totalWeight=evtWeight;
	totalWeight=evtWeight;

	
	

	// std::cout<<"###################################################################################"<<std::endl;
	// std::cout<<"Histograma: "<<stream<<std::endl;
	// std::cout<<"Com peso: "<<totalWeight<<std::endl;
	// cout<<"lepSF: "<<lepSF<<" pileup_SF: "<<pileup_SF<<" genWeight: "<<genWeight<<endl;
	// cout<<"TotalWeight: "<<totalWeight<<endl; 
	//std::cout<<"totalWeight = "<<totalWeight<<std::endl;

	// ** II. cross-section SFs
	/*double xSec = 999999;
	Color_t c_plotColor = 0;
	string sampleName = "PENELOPE";
	setSampleVariables(filename, &xSec, &c_plotColor, &sampleName);
	std::cout << "sampleName: " << sampleName << "\txSec [pb]: " << xSec << "\tplotColor: " << c_plotColor << std::endl;
	*/

	// ===  Method B: FAST  ===
	//cout << ("h_" + nameHLT + stream + "_el0_pt").c_str() << endl;

	//std::cout << "FILL\t" <<("h_" + nameHLT + stream + "_el0_pt").c_str() << std::endl;
	h0 = (TH1D*)array->FindObject( ("h_" + nameHLT + stream + "_el0_pt").c_str() );
	h0->Fill( lepTool.leadPt_el, totalWeight );

	h0 = (TH1D*)array->FindObject( ("h_" + nameHLT + stream + "_el1_pt").c_str() );
	h0->Fill( lepTool.subPt_el, totalWeight );

	h0 = (TH1D*)array->FindObject( ("h_" + nameHLT + stream + "_el0_eta").c_str() );
	h0->Fill( lepTool.leadEta_el, totalWeight );

	h0 = (TH1D*)array->FindObject( ("h_" + nameHLT + stream + "_el1_eta").c_str() );
	h0->Fill( lepTool.subEta_el, totalWeight );

	h0 = (TH1D*)array->FindObject( ("h_" + nameHLT + stream + "_mu0_pt").c_str() );
	h0->Fill( lepTool.leadPt_mu, totalWeight );

	h0 = (TH1D*)array->FindObject( ("h_" + nameHLT + stream + "_mu1_pt").c_str() );
	h0->Fill( lepTool.subPt_mu, totalWeight );

	h0 = (TH1D*)array->FindObject( ("h_" + nameHLT + stream + "_mu0_eta").c_str() );
	h0->Fill( lepTool.leadEta_mu, totalWeight );

	h0 = (TH1D*)array->FindObject( ("h_" + nameHLT + stream + "_mu1_eta").c_str() );
	h0->Fill( lepTool.subEta_mu, totalWeight );

	h0 = (TH1D*)array->FindObject( ("h_" + nameHLT + stream + "_mu0_relIso").c_str() );
	h0->Fill( lepTool.leadRelIso_mu, totalWeight );

	h0 = (TH1D*)array->FindObject( ("h_" + nameHLT + stream + "_el0_relIso").c_str() );
	h0->Fill( lepTool.leadRelIso_el, totalWeight );

	h0 = (TH1D*)array->FindObject( ("h_" + nameHLT + stream + "_njets").c_str() );
	h0->Fill( jetMetTool.nJets, totalWeight );

	h0 = (TH1D*)array->FindObject( ("h_" + nameHLT + stream + "_nbtags").c_str() );
	h0->Fill( jetMetTool.nBTags, totalWeight );

	h0 = (TH1D*)array->FindObject( ("h_" + nameHLT + stream + "_mll").c_str() );
	h0->Fill( lepTool.mll, totalWeight );

	h0 = (TH1D*)array->FindObject( ("h_" + nameHLT + stream + "_met").c_str() );
	h0->Fill( jetMetTool.MET, totalWeight );

	h0 = (TH1D*)array->FindObject( ("h_" + nameHLT + stream + "_nPV").c_str() );
	h0->Fill( jetMetTool.nPV, totalWeight );

	if ( nameHLT.find("Channel")!=string::npos ) return; //skip filling of trigger SFs for analysis plots


	// di-muon (and e+mu)
	h2 = (TH2D*)array->FindObject( ("h_" + nameHLT + stream + "_mu0_pt_vs_eta").c_str() );
	h2->Fill( lepTool.leadPt_mu, abs(lepTool.leadEta_mu), totalWeight );

	h2 = (TH2D*)array->FindObject( ("h_" + nameHLT + stream + "_mu1_pt_vs_eta").c_str() );
	h2->Fill( lepTool.subPt_mu, abs(lepTool.subEta_mu), totalWeight );

	h2 = (TH2D*)array->FindObject( ("h_" + nameHLT + stream + "_mu0_pt_vs_mu1_pt").c_str() );
	h2->Fill( lepTool.leadPt_mu, lepTool.subPt_mu, totalWeight );

	h2 = (TH2D*)array->FindObject( ("h_" + nameHLT + stream + "_mu0_eta_vs_mu1_eta").c_str() );
	h2->Fill( abs(lepTool.leadEta_mu), abs(lepTool.subEta_mu), totalWeight );

	// di-electron (and e+mu)
	h2 = (TH2D*)array->FindObject( ("h_" + nameHLT + stream + "_el0_pt_vs_eta").c_str() );
	h2->Fill( lepTool.leadPt_el, abs(lepTool.leadEta_el), totalWeight );

	h2 = (TH2D*)array->FindObject( ("h_" + nameHLT + stream + "_el1_pt_vs_eta").c_str() );
	h2->Fill( lepTool.subPt_el, abs(lepTool.subEta_el), totalWeight );

	h2 = (TH2D*)array->FindObject( ("h_" + nameHLT + stream + "_el0_pt_vs_el1_pt").c_str() );
	h2->Fill( lepTool.leadPt_el, lepTool.subPt_el, totalWeight );

	h2 = (TH2D*)array->FindObject( ("h_" + nameHLT + stream + "_el0_eta_vs_el1_eta").c_str() );
	h2->Fill( abs(lepTool.leadEta_el), abs(lepTool.subEta_el), totalWeight );

	// e+mu only
	h2 = (TH2D*)array->FindObject( ("h_" + nameHLT + stream + "_mu0_pt_vs_el0_pt").c_str() );
	h2->Fill( lepTool.leadPt_mu, lepTool.leadPt_el, totalWeight );

	h2 = (TH2D*)array->FindObject( ("h_" + nameHLT + stream + "_mu0_eta_vs_el0_eta").c_str() );
	h2->Fill( abs(lepTool.leadEta_mu), abs(lepTool.leadEta_el), totalWeight );



	return;
}

void fillEfficiencyHistograms(leptonHandler lepTool, jetMetHandler jetMetTool, TObjArray* array, string nameHLT, string filename, bool splitStreams=false, bool N_eff = false)
{
	//cout << "fillEfficiencyHistograms()" << endl;
	fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename,"", N_eff);

	// fill histograms separated by stream if necessary --> should be needed for denominator in efficiency calculations
	if (splitStreams) {
		if ( lepTool.passSLCuts_el && jetMetTool.passSLJetMetCuts) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "elStreamSL",N_eff);
		if ( lepTool.passSLCuts_mu && jetMetTool.passSLJetMetCuts) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "muStreamSL",N_eff);
		if ( lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "elStreamDL",N_eff);
		if ( lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "muStreamDL",N_eff);
		if ( lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "emuStreamDL",N_eff);

		//Charis : Added the below histogramms so that no need to run multiple times for systematics derivation
		if ( lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts && (jetMetTool.passNjetsCuts == 1)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "elStreamDL_njetshigh",N_eff);
		if ( lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts && (jetMetTool.passNjetsCuts == 1)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "muStreamDL_njetshigh",N_eff);
		if ( lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts && (jetMetTool.passNjetsCuts == 1)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "emuStreamDL_njetshigh",N_eff);
		if ( lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts && (jetMetTool.passNjetsCuts == 0)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "elStreamDL_njetslow",N_eff);
		if ( lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts && (jetMetTool.passNjetsCuts == 0)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "muStreamDL_njetslow",N_eff);
		if ( lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts && (jetMetTool.passNjetsCuts == 0)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "emuStreamDL_njetslow",N_eff);

		if ( lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts && (jetMetTool.passNPVCuts == 1)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "elStreamDL_npvhigh",N_eff);
		if ( lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts && (jetMetTool.passNPVCuts == 1)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "muStreamDL_npvhigh",N_eff);
		if ( lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts && (jetMetTool.passNPVCuts == 1)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "emuStreamDL_npvhigh",N_eff);
		if ( lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts && (jetMetTool.passNPVCuts == 0)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "elStreamDL_npvlow",N_eff);
		if ( lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts && (jetMetTool.passNPVCuts == 0)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "muStreamDL_npvlow",N_eff);
		if ( lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts && (jetMetTool.passNPVCuts == 0)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "emuStreamDL_npvlow",N_eff);

		if ( lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts && (jetMetTool.passMETCuts == 1)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "elStreamDL_methigh",N_eff);
		if ( lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts && (jetMetTool.passMETCuts == 1)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "muStreamDL_methigh",N_eff);
		if ( lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts && (jetMetTool.passMETCuts == 1)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "emuStreamDL_methigh",N_eff);
		if ( lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts && (jetMetTool.passMETCuts == 0)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "elStreamDL_metlow",N_eff);
		if ( lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts && (jetMetTool.passMETCuts == 0)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "muStreamDL_metlow",N_eff);
		if ( lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts && (jetMetTool.passMETCuts == 0)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "emuStreamDL_metlow",N_eff);
		//No extra muon
		if ( lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts && (lepTool.MuonExtraNumber == 0)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "elStreamDL_ExNumMu0",N_eff);
		if ( lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts && (lepTool.MuonExtraNumber == 0)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "muStreamDL_ExNumMu0",N_eff);
		if ( lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts && (lepTool.MuonExtraNumber == 0)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "emuStreamDL_ExNumMu0",N_eff);
		//One extra muon
		if ( lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts && (lepTool.MuonExtraNumber == 1)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "elStreamDL_ExNumMu1",N_eff);
		if ( lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts && (lepTool.MuonExtraNumber == 1)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "muStreamDL_ExNumMu1",N_eff);
		if ( lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts && (lepTool.MuonExtraNumber == 1)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "emuStreamDL_ExNumMu1",N_eff);
		//Two extra muon
		if ( lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts && (lepTool.MuonExtraNumber == 2)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "elStreamDL_ExNumMu2",N_eff);
		if ( lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts && (lepTool.MuonExtraNumber == 2)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "muStreamDL_ExNumMu2",N_eff);
		if ( lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts && (lepTool.MuonExtraNumber == 2)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "emuStreamDL_ExNumMu2",N_eff);
		//No extra electron
		if ( lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts && (lepTool.ElectronExtraNumber == 0)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "elStreamDL_ExNumEl0",N_eff);
		if ( lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts && (lepTool.ElectronExtraNumber == 0)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "muStreamDL_ExNumEl0",N_eff);
		if ( lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts && (lepTool.ElectronExtraNumber == 0)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "emuStreamDL_ExNumEl0",N_eff);
		//One extra electron
		if ( lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts && (lepTool.ElectronExtraNumber == 1)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "elStreamDL_ExNumEl1",N_eff);
		if ( lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts && (lepTool.ElectronExtraNumber == 1)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "muStreamDL_ExNumEl1",N_eff);
		if ( lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts && (lepTool.ElectronExtraNumber == 1)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "emuStreamDL_ExNumEl1",N_eff);
		//Two extra electron
		if ( lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts && (lepTool.ElectronExtraNumber == 2)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "elStreamDL_ExNumEl2",N_eff);
		if ( lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts && (lepTool.ElectronExtraNumber == 2)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "muStreamDL_ExNumEl2",N_eff);
		if ( lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts && (lepTool.ElectronExtraNumber == 2)) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, filename, "emuStreamDL_ExNumEl2",N_eff);


  }
}

void fillStackHistograms(leptonHandler lepTool, jetMetHandler jetMetTool, TObjArray* array, string nameHLT, string sample, bool N_eff)
{
	//cout << "fillEfficiencyHistograms()" << endl;
	fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, sample, sample,N_eff);
	if ( jetMetTool.nJets == 2 && jetMetTool.nBTags == 1) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, sample, (sample + "_2j1b").c_str() ,N_eff);
	if ( jetMetTool.nJets == 2 && jetMetTool.nBTags == 2) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, sample, (sample + "_2j2b").c_str() ,N_eff);
	if ( jetMetTool.nJets == 3 && jetMetTool.nBTags == 1) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, sample, (sample + "_3j1b").c_str() ,N_eff);
	if ( jetMetTool.nJets == 3 && jetMetTool.nBTags == 2) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, sample, (sample + "_3j2b").c_str() ,N_eff);
	if ( jetMetTool.nJets == 3 && jetMetTool.nBTags == 3) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, sample, (sample + "_3j3b").c_str() ,N_eff);
	if ( jetMetTool.nJets >= 4 && jetMetTool.nBTags == 1) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, sample, (sample + "_4j1b").c_str() ,N_eff);
	if ( jetMetTool.nJets >= 4 && jetMetTool.nBTags == 2) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, sample, (sample + "_4j2b").c_str() ,N_eff);
	if ( jetMetTool.nJets >= 4 && jetMetTool.nBTags == 3) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, sample, (sample + "_4j3b").c_str() ,N_eff);
	if ( jetMetTool.nJets >= 4 && jetMetTool.nBTags >= 4) fillHistogramsByStream( lepTool, jetMetTool, array, nameHLT, sample, (sample + "_4j4b").c_str() ,N_eff);
}

void fillStackHistogramsByChannel(leptonHandler lepTool, jetMetHandler jetMetTool, TObjArray* array, string sample,bool N_eff = false)
{
	// *** 1. Dilepton, ee
	if ((lepTool.passSLtriggers_el || lepTool.passDLtriggers_el) && lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts) fillStackHistograms(lepTool, jetMetTool, array, "eeChannel", sample,N_eff);
	// *** 2. Dilepton, mumu
	if ((lepTool.passSLtriggers_mu || lepTool.passDLtriggers_mu) && lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts) fillStackHistograms(lepTool, jetMetTool, array, "mumuChannel", sample,N_eff);
	// *** 3. Dilepton, emu
	if ((lepTool.passSLtriggers_el || lepTool.passSLtriggers_mu || lepTool.passDLtriggers_emu) && lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts) fillStackHistograms(lepTool, jetMetTool, array, "emuChannel", sample,N_eff);
}


void init2DCorrelationHistograms(TObjArray* array, string nameHLT)
{
	TH2D* h_2dCorr = new TH2D();
	// TH2D* h_2dCorr;

	// for (int i = 0; i < metTriggers.size(); i++) {
	for (uint i = 0; i < metTriggers.size(); i++) {
		//cout << metTriggers.at(i) << endl;
		h_2dCorr = new TH2D(("h_" + nameHLT + "__vs__" + metTriggers.at(i)).c_str(), ("h_" + nameHLT + "__vs__" + metTriggers.at(i)).c_str(), 2, 0, 2, 2, 0, 2);
		array->AddLast(h_2dCorr); // add histo to TObjArray
	}

	//cout << "number " << nameHLT << " histos: " << array->GetSize() << endl;

}

void createEfficiencyHistograms(TObjArray* array, string nameHLT, string stream="", int era = 0)
{
	
	//Essa variaveis vão ser usadas para criar os const int dos bins
	Int_t index_lea_mumu = 0,index_sub_mumu=0,index_lea_elel=0,index_sub_elel=0,index_ele_elmu=0,index_mu_elmu=0;

	if (era == 2018 || era == 2016){
		index_lea_mumu = 4;
		index_sub_mumu = 2;
		index_lea_elel = 4;
		index_sub_elel = 2;
		index_ele_elmu = 4;
		index_mu_elmu = 4;
	}

	if (era == 2017){
		index_lea_mumu = 4;
		index_sub_mumu = 3;
		index_lea_elel = 4;
		index_sub_elel = 3;
		index_ele_elmu = 4;
		index_mu_elmu = 4;
	}

	// if(era == 2016){
	const Int_t nbins_Neff_2D_SubElEl = index_sub_elel;
	Double_t edges_nbins_Neff_2D_SubElEl[nbins_Neff_2D_SubElEl + 1];

	const Int_t nbins_Neff_2D_LeaElEl = index_lea_elel;
	Double_t edges_nbins_Neff_2D_LeaElEl[nbins_Neff_2D_LeaElEl + 1];


		//Vou colocar bins diferentes para cada CANAl
	const Int_t nbins_Neff_2D_SubMuMu = index_sub_mumu;
	Double_t edges_nbins_Neff_2D_SubMuMu[nbins_Neff_2D_SubMuMu + 1];

	const Int_t nbins_Neff_2D_LeaMuMu = index_lea_mumu;	
	Double_t edges_nbins_Neff_2D_LeaMuMu[nbins_Neff_2D_LeaMuMu + 1];


	//Vou colocar bins diferentes para cada CANAl
	const Int_t nbins_Neff_2D_SubElMu = index_ele_elmu;
	Double_t edges_nbins_Neff_2D_SubElMu[nbins_Neff_2D_SubElMu + 1];

	const Int_t nbins_Neff_2D_LeaElMu = index_mu_elmu;
	Double_t edges_nbins_Neff_2D_LeaElMu[nbins_Neff_2D_LeaElMu + 1];






	//Colocando os bins corretos para cada ano!
	if (era == 2018 || era == 2016){
		// CANAL MUMU
		edges_nbins_Neff_2D_SubMuMu[0] = {20.0};
		edges_nbins_Neff_2D_SubMuMu[1] = {25.0};
		edges_nbins_Neff_2D_SubMuMu[2] = {200.0};
		edges_nbins_Neff_2D_LeaMuMu[0] = {40.0};
		edges_nbins_Neff_2D_LeaMuMu[1] = {60.0};
		edges_nbins_Neff_2D_LeaMuMu[2] = {80.0};
		edges_nbins_Neff_2D_LeaMuMu[3] = {100.0};
		edges_nbins_Neff_2D_LeaMuMu[4] = {200.0};
		//CANAL ELEL
		edges_nbins_Neff_2D_SubElEl[0]={20};
		edges_nbins_Neff_2D_SubElEl[1]={35};
		edges_nbins_Neff_2D_SubElEl[2]={200};
		edges_nbins_Neff_2D_LeaElEl[0]={40};
		edges_nbins_Neff_2D_LeaElEl[1]={60};
		edges_nbins_Neff_2D_LeaElEl[2]={80};
		edges_nbins_Neff_2D_LeaElEl[3]={100};
		edges_nbins_Neff_2D_LeaElEl[4]={200};
		//CANAL ELMu-> DESNECESSARIO UMA VEZ QUE SAO IGUAIS PARA TODOS OS ANOS. MANTIVE CASO SEJA NECESSARIO USAR
		edges_nbins_Neff_2D_SubElMu[0]={20};
		edges_nbins_Neff_2D_SubElMu[1]={30};
		edges_nbins_Neff_2D_SubElMu[2]={40};
		edges_nbins_Neff_2D_SubElMu[3]={60};
		edges_nbins_Neff_2D_SubElMu[4]={200};
		edges_nbins_Neff_2D_LeaElMu[0]={20};
		edges_nbins_Neff_2D_LeaElMu[1]={30};
		edges_nbins_Neff_2D_LeaElMu[2]={40};
		edges_nbins_Neff_2D_LeaElMu[3]={60};
		edges_nbins_Neff_2D_LeaElMu[4]={200};

	}

	if (era == 2017){
		// CANAL MUMU
		edges_nbins_Neff_2D_SubMuMu[0] = {20.0};
		edges_nbins_Neff_2D_SubMuMu[1] = {25.0};
		edges_nbins_Neff_2D_SubMuMu[2] = {30.0};
		edges_nbins_Neff_2D_SubMuMu[3] = {200.0};
		edges_nbins_Neff_2D_LeaMuMu[0] = {40.0};
		edges_nbins_Neff_2D_LeaMuMu[1] = {60.0};
		edges_nbins_Neff_2D_LeaMuMu[2] = {80.0};
		edges_nbins_Neff_2D_LeaMuMu[3] = {100.0};
		edges_nbins_Neff_2D_LeaMuMu[4] = {200.0};
		//CANAL ELEL
		edges_nbins_Neff_2D_SubElEl[0]={20};
		edges_nbins_Neff_2D_SubElEl[1]={40};
		edges_nbins_Neff_2D_SubElEl[2]={60};
		edges_nbins_Neff_2D_SubElEl[3]={200};
		edges_nbins_Neff_2D_LeaElEl[0]={40}; //40
		edges_nbins_Neff_2D_LeaElEl[1]={60}; //60
		edges_nbins_Neff_2D_LeaElEl[2]={80}; //80
		edges_nbins_Neff_2D_LeaElEl[3]={100}; //100
		edges_nbins_Neff_2D_LeaElEl[4]={200}; //200
		//CANAL ELMu-> DESNECESSARIO UMA VEZ QUE SAO IGUAIS PARA TODOS OS ANOS. MANTIVE CASO SEJA NECESSARIO USAR
		edges_nbins_Neff_2D_SubElMu[0]={20};
		edges_nbins_Neff_2D_SubElMu[1]={30};
		edges_nbins_Neff_2D_SubElMu[2]={40};
		edges_nbins_Neff_2D_SubElMu[3]={60};
		edges_nbins_Neff_2D_SubElMu[4]={200};
		edges_nbins_Neff_2D_LeaElMu[0]={20};
		edges_nbins_Neff_2D_LeaElMu[1]={30};
		edges_nbins_Neff_2D_LeaElMu[2]={40};
		edges_nbins_Neff_2D_LeaElMu[3]={60};
		edges_nbins_Neff_2D_LeaElMu[4]={200};

	}
	
	
	
	
	// Leading electron pT

	// === 09-18-18 (bin optimization) ===
	const Int_t nbins_subleadPt_2D = 3;
	// const Int_t nbins_subleadPt_2D = 1;     // GILSON
	Double_t edges_subleadPt_2D[nbins_subleadPt_2D + 1] = {20.0, 50.0, 90.0, 200.0};
	
	// // if(era == 2016){
	// const Int_t nbins_Neff_2D_SubElEl = 3;
	// Double_t edges_nbins_Neff_2D_SubElEl[4] = {20.0,40,60, 200.0};

	// const Int_t nbins_Neff_2D_LeaElEl = 4;
	// Double_t edges_nbins_Neff_2D_LeaElEl[nbins_Neff_2D_LeaElEl + 1] = {40,60,80,100,200};


	// 	//Vou colocar bins diferentes para cada CANAl
	// const Int_t nbins_Neff_2D_SubMuMu = 3;
	// Double_t edges_nbins_Neff_2D_SubMuMu[nbins_Neff_2D_SubMuMu + 1] = {20.0, 25.0,30, 200.0};

	// const Int_t nbins_Neff_2D_LeaMuMu = 4;	
	// Double_t edges_nbins_Neff_2D_LeaMuMu[nbins_Neff_2D_LeaMuMu + 1] = {40,60,80,100,200};


	// //Vou colocar bins diferentes para cada CANAl
	// const Int_t nbins_Neff_2D_SubElMu = 4;
	// Double_t edges_nbins_Neff_2D_SubElMu[nbins_Neff_2D_SubElMu + 1] = {20.0, 30.0, 40.0,60, 200.0};

	// const Int_t nbins_Neff_2D_LeaElMu = 4;
	// Double_t edges_nbins_Neff_2D_LeaElMu[nbins_Neff_2D_LeaElMu + 1] = {20,30,40,60,200};


	


	// === 09-13-18 (bin optimization) ===
	const Int_t nbins_pt_2D = 4;
	//Double_t edges_pt_2D[nbins_pt_2D + 1] = {20.0, 50.0, 80.0, 120.0, 200.0};
	Double_t edges_pt_2D[nbins_pt_2D + 1] = {40.0, 60.0, 80.0, 120.0, 200.0};
	// === 09-11-18 (matching AN2016_392) ===
	const Int_t nbins_pt = 6;
	Double_t edges_pt[nbins_pt + 1] = {20.0, 30.0, 40.0, 60.0, 80.0, 100.0, 200.0};
	// === pre 09-11-18 ===
	//const Int_t nbins_pt = 7;
	//Double_t edges_pt[nbins_pt + 1] = {20.0, 30.0, 40.0, 60.0, 80.0, 100.0, 200.0, 300.0};
	// === pre 04-11-18 ===
	//const Int_t nbins_pt = 27;
	//Double_t edges_pt[nbins_pt + 1] = {20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0, 100.0, 110.0, 120.0, 130.0, 140.0, 150.0, 160.0, 170.0, 180.0, 190.0, 200.0, 210.0, 220.0, 230.0, 240.0, 250.0, 260.0, 270.0, 280.0, 300.0};

	//std::cout << "INIT\t" << ("h_" + nameHLT + stream + "_el0_pt").c_str() << std::endl;
	TH1D* h_el0_pt = new TH1D( ("h_" + nameHLT + stream + "_el0_pt").c_str(),  ("h_" + nameHLT + stream + "_el0_pt").c_str(), nbins_Neff_2D_LeaElEl, edges_nbins_Neff_2D_LeaElEl );
	h_el0_pt->SetXTitle("Leading Electron p_{T} [GeV]");
	h_el0_pt->SetYTitle("Entries / Bin");
	TH1D* h_el1_pt = new TH1D( ("h_" + nameHLT + stream + "_el1_pt").c_str(),  ("h_" + nameHLT + stream + "_el1_pt").c_str(), nbins_Neff_2D_SubElEl, edges_nbins_Neff_2D_SubElEl );
	h_el1_pt->SetXTitle("Sub-Leading Electron p_{T} [GeV]");
	h_el1_pt->SetYTitle("Entries / Bin");

	TH1D* h_mu0_pt = new TH1D( ("h_" + nameHLT + stream + "_mu0_pt").c_str(),  ("h_" + nameHLT + stream + "_mu0_pt").c_str(), nbins_Neff_2D_LeaMuMu, edges_nbins_Neff_2D_LeaMuMu );
	h_mu0_pt->SetXTitle("Leading Muon p_{T} [GeV]");
	h_mu0_pt->SetYTitle("Entries / Bin");
	TH1D* h_mu1_pt = new TH1D( ("h_" + nameHLT + stream + "_mu1_pt").c_str(),  ("h_" + nameHLT + stream + "_mu1_pt").c_str(), nbins_Neff_2D_SubMuMu, edges_nbins_Neff_2D_SubMuMu );
	h_mu1_pt->SetXTitle("Sub-Leading Muon p_{T} [GeV]");
	h_mu1_pt->SetYTitle("Entries / Bin");

	// Leading electron eta
	// === 09-18-18 (bin optimization) ===
	//const Int_t nbins_EtaByEta_2D = 2;
	const Int_t nbins_EtaByEta_2D = 3;									   // GILSON
	//Double_t edges_EtaByEta_2D[nbins_EtaByEta_2D + 1] = {0, 1.2, 2.4};
	Double_t edges_EtaByEta_2D[nbins_EtaByEta_2D + 1] = {0,0.5,1.5,2.4};   // GILSON
	//const Int_t nbins_eta_2D = 4;
	//Double_t edges_eta_2D[nbins_eta_2D + 1] = {0, 0.4, 0.9, 1.5, 2.4};
	//const Int_t nbins_subleadEta_2D = 3;
	//Double_t edges_subleadEta_2D[nbins_eta_2D + 1] = {0, 0.4, 0.9, 2.4};
	const Int_t nbins_eta_2D = 3;											// GILSON
	Double_t edges_eta_2D[nbins_eta_2D + 1] = {0,0.5,1.5,2.4};				// GILSON
	const Int_t nbins_subleadEta_2D = 3;									// GILSON
	Double_t edges_subleadEta_2D[nbins_eta_2D + 1] = {0,0.5,1.5,2.4};		// GILSON

	// === 09-13-18 (bin optimization) ===
	//const Int_t nbins_eta_2D = 5;
	//Double_t edges_eta_2D[nbins_eta_2D + 1] = {0, 0.4, 0.9, 1.2, 1.8, 2.4};
	// === 09-11-18 (matching AN2016_392) ===
	const Int_t nbins_eta_el = 15;
	Double_t edges_eta_el[nbins_eta_el + 1] = {-2.4, -2.1, -1.566, -1.4442, -1.0, -0.6, -0.3, -0.1, 0.1, 0.3, 0.6, 1.0, 1.4442, 1.5666, 2.1, 2.4};
	const Int_t nbins_eta_mu = 16;
	Double_t edges_eta_mu[nbins_eta_mu + 1] = {-2.4, -2.1, -1.8, -1.5, -1.2, -0.9, -0.5, -0.2, 0.0, 0.2, 0.5, 0.9, 1.2, 1.5, 1.8, 2.1, 2.4};
	//const Int_t nbins_eta_2D = 5;
	//Double_t edges_eta_2D[nbins_eta_2D + 1] = {0, 0.4, 0.9, 1.2, 2.1, 2.4};
	// === pre 09-11-18 ===
	//const Int_t nbins_eta = 5;
	//Double_t edges_eta[nbins_eta + 1] = {-2.5, -1.5, -0.75, 0.75, 1.5, 2.5};
	TH1D* h_el0_eta = new TH1D( ("h_" + nameHLT + stream + "_el0_eta").c_str(),  ("h_" + nameHLT + stream + "_el0_eta").c_str(), nbins_eta_el, edges_eta_el );
	h_el0_eta->SetMinimum(0.0);
	h_el0_eta->SetXTitle("Leading Electron #eta");
	h_el0_eta->SetYTitle("Entries / Bin");
	TH1D* h_el1_eta = new TH1D( ("h_" + nameHLT + stream + "_el1_eta").c_str(),  ("h_" + nameHLT + stream + "_el1_eta").c_str(), nbins_eta_el, edges_eta_el );
	h_el1_eta->SetMinimum(0.0);
	h_el1_eta->SetXTitle("Sub-Leading Electron #eta");
	h_el1_eta->SetYTitle("Entries / Bin");

	TH1D* h_mu0_eta = new TH1D( ("h_" + nameHLT + stream + "_mu0_eta").c_str(),  ("h_" + nameHLT + stream + "_mu0_eta").c_str(), nbins_eta_mu, edges_eta_mu );
	h_mu0_eta->SetMinimum(0.0);
	h_mu0_eta->SetXTitle("Leading Muon #eta");
	h_mu0_eta->SetYTitle("Entries / Bin");
	TH1D* h_mu1_eta = new TH1D( ("h_" + nameHLT + stream + "_mu1_eta").c_str(),  ("h_" + nameHLT + stream + "_mu1_eta").c_str(), nbins_eta_mu, edges_eta_mu );
	h_mu1_eta->SetMinimum(0.0);
	h_mu1_eta->SetXTitle("Sub-Leading Muon #eta");
	h_mu1_eta->SetYTitle("Entries / Bin");

	// N_jets
	// === 09-11-18 (matching AN2016_392) ===
	TH1D* h_njets = new TH1D( ("h_" + nameHLT + stream + "_njets").c_str(),  ("h_" + nameHLT + stream + "_njets").c_str(), 12, 0, 12);
	//TH1D* h_njets = new TH1D( ("h_" + nameHLT + stream + "_njets").c_str(),  ("h_" + nameHLT + stream + "_njets").c_str(), 8, 4, 12);
	//TH1D* h_njets = new TH1D( ("h_" + nameHLT + stream + "_njets").c_str(),  ("h_" + nameHLT + stream + "_njets").c_str(), 12, 0, 12);
	h_njets->SetXTitle("N_{jets}");
	h_njets->SetYTitle("Entries / Bin");

	// N_btags
	// === 11-15-18 (how did i not have this before?) ===
	TH1D* h_nbtags = new TH1D( ("h_" + nameHLT + stream + "_nbtags").c_str(),  ("h_" + nameHLT + stream + "_nbtags").c_str(), 8, 0, 8);
	h_nbtags->SetXTitle("N_{b-tags}");
	h_nbtags->SetYTitle("Entries / Bin");

	// m_ll
	TH1D* h_mll = new TH1D( ("h_" + nameHLT + stream + "_mll").c_str(),  ("h_" + nameHLT + stream + "_mll").c_str(), 25, 0, 200);
	h_mll->SetXTitle("M_{ll}");
	h_mll->SetYTitle("Entries / Bin");

	// MET
	//const Int_t nbins_met = 11;
	//Double_t edges_met[nbins_met + 1] = {0.0, 20.0, 40.0, 60.0, 80.0, 100.0, 125.0, 150.0, 175.0, 200.0, 250.0, 300.0};
	// ==== 4-11-18 ====
	//const Int_t nbins_met = 23;
	//Double_t edges_met[nbins_met + 1] = {0.0, 20.0, 40.0, 60.0, 80.0, 100.0, 125.0, 135.0, 145.0, 155.0, 165.0, 175.0, 185.0, 195.0, 205.0, 215.0, 225.0, 235.0, 245.0, 255.0, 265.0, 275.0, 285.0, 300.0};
	// ==== 4-16-18 ====
	//const Int_t nbins_met = 18;
	//Double_t edges_met[nbins_met + 1] = {110.0, 125.0, 135.0, 145.0, 155.0, 165.0, 175.0, 185.0, 195.0, 205.0, 215.0, 225.0, 235.0, 245.0, 255.0, 265.0, 275.0, 285.0, 300.0};
	// ==== 06-11-18 ====
	//const Int_t nbins_met = 8;
	//Double_t edges_met[nbins_met + 1] = {100.0, 125.0, 150.0, 175.0, 200.0, 225.0, 250.0, 275.0, 300.0};
	// ==== 07-09-18 ====
	//const Int_t nbins_met = 12;
	//Double_t edges_met[nbins_met + 1] = {0.0, 25.0, 50.0, 75.0, 100.0, 125.0, 150.0, 175.0, 200.0, 225.0, 250.0, 275.0, 300.0};
	// === 09-11-18 (matching AN2016_392) ===
	const Int_t nbins_met = 9;
	Double_t edges_met[nbins_met + 1] = {0.0, 20.0, 40.0, 60.0, 80.0, 100.0, 125.0, 150.0, 175.0, 200.0};
	TH1D* h_met = new TH1D( ("h_" + nameHLT + stream + "_met").c_str(),  ("h_" + nameHLT + stream + "_met").c_str(), nbins_met, edges_met );
	h_met->SetXTitle("Missing Transverse Energy (MET) [GeV]");
	h_met->SetYTitle("Entries / Bin");

	// N_vtx
	TH1D* h_nPV = new TH1D( ("h_" + nameHLT + stream + "_nPV").c_str(),  ("h_" + nameHLT + stream + "_nPV").c_str(), 20, 0, 60);
	h_nPV->SetXTitle("N_{PV}");
	h_nPV->SetYTitle("Entries / Bin");

	// leading relIso
	TH1D* h_mu0_relIso = new TH1D( ("h_" + nameHLT + stream + "_mu0_relIso").c_str(),  ("h_" + nameHLT + stream + "_mu0_relIso").c_str(), 13, 0, 0.13);
	h_mu0_relIso->SetXTitle("Leading Muon Rel. Iso");
	h_mu0_relIso->SetYTitle("Entries / Bin");
	TH1D* h_el0_relIso = new TH1D( ("h_" + nameHLT + stream + "_el0_relIso").c_str(),  ("h_" + nameHLT + stream + "_el0_relIso").c_str(), 13, 0, 0.13);
	h_el0_relIso->SetXTitle("Leading Electron Rel. Iso");
	h_el0_relIso->SetYTitle("Entries / Bin");

	array->AddLast(h_el0_pt);
	array->AddLast(h_el1_pt);
	array->AddLast(h_el0_eta);
	array->AddLast(h_el1_eta);
	array->AddLast(h_mu0_pt);
	array->AddLast(h_mu1_pt);
	array->AddLast(h_mu0_eta);
	array->AddLast(h_mu1_eta);
	array->AddLast(h_mu0_relIso);
	array->AddLast(h_el0_relIso);
	array->AddLast(h_njets);
	array->AddLast(h_nbtags);
	array->AddLast(h_mll);
	array->AddLast(h_met);
	array->AddLast(h_nPV);

	if ( nameHLT.find("Channel")!=string::npos ) return; //skip filling of trigger SFs for analysis plots

	// 2D di-electron (and e+mu)
	TH2D* h_el0_pt_vs_eta = new TH2D( ("h_" + nameHLT + stream + "_el0_pt_vs_eta").c_str(),  ("h_" + nameHLT + stream + "_el0_pt_vs_eta").c_str(), nbins_pt_2D, edges_pt_2D, nbins_eta_2D, edges_eta_2D );
	h_el0_pt_vs_eta->SetXTitle("Leading Electron p_{T} [GeV]");
	h_el0_pt_vs_eta->SetYTitle("Leading Electron |#eta|");
	TH2D* h_el1_pt_vs_eta = new TH2D( ("h_" + nameHLT + stream + "_el1_pt_vs_eta").c_str(),  ("h_" + nameHLT + stream + "_el1_pt_vs_eta").c_str(), nbins_subleadPt_2D, edges_subleadPt_2D, nbins_subleadEta_2D, edges_subleadEta_2D );
	h_el1_pt_vs_eta->SetXTitle("Sub-Leading Electron p_{T} [GeV]");
	h_el1_pt_vs_eta->SetYTitle("Sub-Leading Electron |#eta|");
	TH2D* h_el0_eta_vs_el1_eta = new TH2D( ("h_" + nameHLT + stream + "_el0_eta_vs_el1_eta").c_str(),  ("h_" + nameHLT + stream + "_el0_eta_vs_el1_eta").c_str(), nbins_EtaByEta_2D, edges_EtaByEta_2D, nbins_EtaByEta_2D, edges_EtaByEta_2D );
	h_el0_eta_vs_el1_eta->SetXTitle("Leading Electron |#eta|");
	h_el0_eta_vs_el1_eta->SetYTitle("Sub-Leading Electron |#eta|");
	//TH2D* h_el0_pt_vs_el1_pt = new TH2D( ("h_" + nameHLT + stream + "_el0_pt_vs_el1_pt").c_str(),  ("h_" + nameHLT + stream + "_el0_pt_vs_el1_pt").c_str(), nbins_subleadPt_2D, edges_subleadPt_2D, nbins_subleadPt_2D, edges_subleadPt_2D );
	TH2D* h_el0_pt_vs_el1_pt = new TH2D( ("h_" + nameHLT + stream + "_el0_pt_vs_el1_pt").c_str(),  ("h_" + nameHLT + stream + "_el0_pt_vs_el1_pt").c_str(), nbins_Neff_2D_LeaElEl, edges_nbins_Neff_2D_LeaElEl, nbins_Neff_2D_SubElEl, edges_nbins_Neff_2D_SubElEl);
	h_el0_pt_vs_el1_pt->SetXTitle("Leading Electron p_{T} [GeV]");
	h_el0_pt_vs_el1_pt->SetYTitle("Sub-Leading Electron p_{T} [GeV]");

	// 2D muon dimon (and e+mu)
	TH2D* h_mu0_pt_vs_eta = new TH2D( ("h_" + nameHLT + stream + "_mu0_pt_vs_eta").c_str(),  ("h_" + nameHLT + stream + "_mu0_pt_vs_eta").c_str(), nbins_pt_2D, edges_pt_2D, nbins_eta_2D, edges_eta_2D );
	h_mu0_pt_vs_eta->SetXTitle("Leading Muon p_{T} [GeV]");
	h_mu0_pt_vs_eta->SetYTitle("Leading Muon |#eta|");
	TH2D* h_mu1_pt_vs_eta = new TH2D( ("h_" + nameHLT + stream + "_mu1_pt_vs_eta").c_str(),  ("h_" + nameHLT + stream + "_mu1_pt_vs_eta").c_str(), nbins_subleadPt_2D, edges_subleadPt_2D, nbins_subleadEta_2D, edges_subleadEta_2D );
	h_mu1_pt_vs_eta->SetXTitle("Sub-Leading Muon p_{T} [GeV]");
	h_mu1_pt_vs_eta->SetYTitle("Sub-Leading Muon |#eta|");
	TH2D* h_mu0_eta_vs_mu1_eta = new TH2D( ("h_" + nameHLT + stream + "_mu0_eta_vs_mu1_eta").c_str(),  ("h_" + nameHLT + stream + "_mu0_eta_vs_mu1_eta").c_str(), nbins_EtaByEta_2D, edges_EtaByEta_2D, nbins_EtaByEta_2D, edges_EtaByEta_2D );
	h_mu0_eta_vs_mu1_eta->SetXTitle("Leading Muon |#eta|");
	h_mu0_eta_vs_mu1_eta->SetYTitle("Sub-Leading Muon |#eta|");
	//TH2D* h_mu0_pt_vs_mu1_pt = new TH2D( ("h_" + nameHLT + stream + "_mu0_pt_vs_mu1_pt").c_str(),  ("h_" + nameHLT + stream + "_mu0_pt_vs_mu1_pt").c_str(), nbins_subleadPt_2D, edges_subleadPt_2D, nbins_subleadPt_2D, edges_subleadPt_2D );
	TH2D* h_mu0_pt_vs_mu1_pt = new TH2D( ("h_" + nameHLT + stream + "_mu0_pt_vs_mu1_pt").c_str(),  ("h_" + nameHLT + stream + "_mu0_pt_vs_mu1_pt").c_str(), nbins_Neff_2D_LeaMuMu, edges_nbins_Neff_2D_LeaMuMu, nbins_Neff_2D_SubMuMu, edges_nbins_Neff_2D_SubMuMu );
	h_mu0_pt_vs_mu1_pt->SetXTitle("Leading Muon p_{T} [GeV]");
	h_mu0_pt_vs_mu1_pt->SetYTitle("Sub-Leading Muon p_{T} [GeV]");

	// 2D e+mu
	TH2D* h_mu0_eta_vs_el0_eta = new TH2D( ("h_" + nameHLT + stream + "_mu0_eta_vs_el0_eta").c_str(),  ("h_" + nameHLT + stream + "_mu0_eta_vs_el0_eta").c_str(), nbins_EtaByEta_2D, edges_EtaByEta_2D, nbins_EtaByEta_2D, edges_EtaByEta_2D );
	h_mu0_eta_vs_el0_eta->SetXTitle("Leading Muon |#eta|");
	h_mu0_eta_vs_el0_eta->SetYTitle("Leading Electron |#eta|");
	TH2D* h_mu0_pt_vs_el0_pt = new TH2D( ("h_" + nameHLT + stream + "_mu0_pt_vs_el0_pt").c_str(),  ("h_" + nameHLT + stream + "_mu0_pt_vs_el0_pt").c_str(), nbins_Neff_2D_LeaElMu, edges_nbins_Neff_2D_LeaElMu, nbins_Neff_2D_SubElMu, edges_nbins_Neff_2D_SubElMu );
	h_mu0_pt_vs_el0_pt->SetXTitle("Muon p_{T} [GeV]");
	h_mu0_pt_vs_el0_pt->SetYTitle("Electron p_{T} [GeV]");

	array->AddLast(h_el0_pt_vs_eta);
	array->AddLast(h_el1_pt_vs_eta);
	array->AddLast(h_el0_eta_vs_el1_eta);
	array->AddLast(h_el0_pt_vs_el1_pt);

	array->AddLast(h_mu0_pt_vs_eta);
	array->AddLast(h_mu1_pt_vs_eta);
	array->AddLast(h_mu0_eta_vs_mu1_eta);
	array->AddLast(h_mu0_pt_vs_mu1_pt);

	array->AddLast(h_mu0_pt_vs_el0_pt);
	array->AddLast(h_mu0_eta_vs_el0_eta);

	return;
}


void initEfficiencyHistograms(TObjArray* array, string nameHLT, bool splitStreams, int era = 0)
{
	// always create general histograms
	createEfficiencyHistograms(array, nameHLT,"",era);
	if (splitStreams) { // create plots split by presence of good electron or muon if necessary --> should be needed for denominator in efficiency calculations
		createEfficiencyHistograms(array, nameHLT, "_elStreamSL",era);
		createEfficiencyHistograms(array, nameHLT, "_muStreamSL",era);
		createEfficiencyHistograms(array, nameHLT, "_elStreamDL",era);
		createEfficiencyHistograms(array, nameHLT, "_muStreamDL",era);
		createEfficiencyHistograms(array, nameHLT, "_emuStreamDL",era);

		createEfficiencyHistograms(array, nameHLT, "_elStreamDL_njetshigh",era);
		createEfficiencyHistograms(array, nameHLT, "_muStreamDL_njetshigh",era);
		createEfficiencyHistograms(array, nameHLT, "_emuStreamDL_njetshigh",era);
		createEfficiencyHistograms(array, nameHLT, "_elStreamDL_njetslow",era);
		createEfficiencyHistograms(array, nameHLT, "_muStreamDL_njetslow",era);
		createEfficiencyHistograms(array, nameHLT, "_emuStreamDL_njetslow",era);

		createEfficiencyHistograms(array, nameHLT, "_elStreamDL_npvhigh",era);
		createEfficiencyHistograms(array, nameHLT, "_muStreamDL_npvhigh",era);
		createEfficiencyHistograms(array, nameHLT, "_emuStreamDL_npvhigh",era);
		createEfficiencyHistograms(array, nameHLT, "_elStreamDL_npvlow",era);
		createEfficiencyHistograms(array, nameHLT, "_muStreamDL_npvlow",era);
		createEfficiencyHistograms(array, nameHLT, "_emuStreamDL_npvlow",era);

		createEfficiencyHistograms(array, nameHLT, "_elStreamDL_methigh",era);
		createEfficiencyHistograms(array, nameHLT, "_muStreamDL_methigh",era);
		createEfficiencyHistograms(array, nameHLT, "_emuStreamDL_methigh",era);
		createEfficiencyHistograms(array, nameHLT, "_elStreamDL_metlow",era);
		createEfficiencyHistograms(array, nameHLT, "_muStreamDL_metlow",era);
		createEfficiencyHistograms(array, nameHLT, "_emuStreamDL_metlow",era);

		createEfficiencyHistograms(array, nameHLT, "_elStreamDL_ExNumMu0",era);
		createEfficiencyHistograms(array, nameHLT, "_muStreamDL_ExNumMu0",era);
		createEfficiencyHistograms(array, nameHLT, "_emuStreamDL_ExNumMu0",era);
		createEfficiencyHistograms(array, nameHLT, "_elStreamDL_ExNumMu1",era);
		createEfficiencyHistograms(array, nameHLT, "_muStreamDL_ExNumMu1",era);
		createEfficiencyHistograms(array, nameHLT, "_emuStreamDL_ExNumMu1",era);
		createEfficiencyHistograms(array, nameHLT, "_elStreamDL_ExNumMu2",era);
		createEfficiencyHistograms(array, nameHLT, "_muStreamDL_ExNumMu2",era);
		createEfficiencyHistograms(array, nameHLT, "_emuStreamDL_ExNumMu2",era);

		createEfficiencyHistograms(array, nameHLT, "_elStreamDL_ExNumEl0",era);
		createEfficiencyHistograms(array, nameHLT, "_muStreamDL_ExNumEl0",era);
		createEfficiencyHistograms(array, nameHLT, "_emuStreamDL_ExNumEl0",era);
		createEfficiencyHistograms(array, nameHLT, "_elStreamDL_ExNumEl1",era);
		createEfficiencyHistograms(array, nameHLT, "_muStreamDL_ExNumEl1",era);
		createEfficiencyHistograms(array, nameHLT, "_emuStreamDL_ExNumEl1",era);
		createEfficiencyHistograms(array, nameHLT, "_elStreamDL_ExNumEl2",era);
		createEfficiencyHistograms(array, nameHLT, "_muStreamDL_ExNumEl2",era);
		createEfficiencyHistograms(array, nameHLT, "_emuStreamDL_ExNumEl2",era);
		

	}

}

void initializeHistograms(TObjArray* array, string nameHLT, bool splitStreams=false, int era = 0)
{
	//Criação dos histogramas 2x2 de correlaçao entre ativado ou não
	init2DCorrelationHistograms(array, nameHLT);
	//Cria o canvas (com os bins) de varias variaveis de interesse
	initEfficiencyHistograms(array, nameHLT, splitStreams, era);

	return;
}

void initStackHistograms(TObjArray* array, string nameHLT, string sample, int era = 0)
{
	// always create general histograms
	createEfficiencyHistograms(array, nameHLT, ("_" + sample).c_str() ,era);
	createEfficiencyHistograms(array, nameHLT, ("_" + sample + "_2j1b").c_str() ,era);
	createEfficiencyHistograms(array, nameHLT, ("_" + sample + "_2j2b").c_str() ,era);
	createEfficiencyHistograms(array, nameHLT, ("_" + sample + "_3j1b").c_str() ,era);
	createEfficiencyHistograms(array, nameHLT, ("_" + sample + "_3j2b").c_str() ,era);
	createEfficiencyHistograms(array, nameHLT, ("_" + sample + "_3j3b").c_str() ,era);
	createEfficiencyHistograms(array, nameHLT, ("_" + sample + "_4j1b").c_str() ,era);
	createEfficiencyHistograms(array, nameHLT, ("_" + sample + "_4j2b").c_str() ,era);
	createEfficiencyHistograms(array, nameHLT, ("_" + sample + "_4j3b").c_str() ,era);
	createEfficiencyHistograms(array, nameHLT, ("_" + sample + "_4j4b").c_str() ,era);

}
void initializeStackHistograms(TObjArray* array, string sample,int era = 0)
{
	if (sample.find("ttbar")==string::npos) { // simple if not ttbar
		initStackHistograms(array, "eeChannel", sample,era);
		initStackHistograms(array, "emuChannel", sample,era);
		initStackHistograms(array, "mumuChannel", sample,era);
	}
	else { // if ttbar, need separate histograms for tt+X flavors
		initStackHistograms(array, "eeChannel",   "ttlf",era);
		initStackHistograms(array, "emuChannel",  "ttlf",era);
		initStackHistograms(array, "mumuChannel", "ttlf",era);
		initStackHistograms(array, "eeChannel",   "ttcc",era);
		initStackHistograms(array, "emuChannel",  "ttcc",era);
		initStackHistograms(array, "mumuChannel", "ttcc",era);
		initStackHistograms(array, "eeChannel",   "ttbb",era);
		initStackHistograms(array, "emuChannel",  "ttbb",era);
		initStackHistograms(array, "mumuChannel", "ttbb",era);
		initStackHistograms(array, "eeChannel",   "ttb",era);
		initStackHistograms(array, "emuChannel",  "ttb",era);
		initStackHistograms(array, "mumuChannel", "ttb",era);
		initStackHistograms(array, "eeChannel",   "tt2b",era);
		initStackHistograms(array, "emuChannel",  "tt2b",era);
		initStackHistograms(array, "mumuChannel", "tt2b",era);
	}
	return;
}


void fill2DCorrHistogramsWithLabels(TH2D*& hist, int passHLT_lep, int passHLT_MET)
{
    // std::cout<<hist->GetName()<<" "<<passHLT_lep<<" "<<passHLT_MET<<std::endl;
	if (passHLT_lep && passHLT_MET)
		hist->Fill("Fired", "Fired", 1);
	else if (passHLT_lep && !passHLT_MET)
		hist->Fill("Fired", "Not Fired", 1);
	else if (!passHLT_lep && passHLT_MET)
		hist->Fill("Not Fired", "Fired", 1);
	else // !passHLT_lep && !passHLT_MET)
		hist->Fill("Not Fired", "Not Fired", 1);

}

// void fill2DCorrHistograms(yggdrasilEventVars* eve, TObjArray*& array, string nameHLT, int passHLT, jetMetHandler jetMetTool)
void fill2DCorrHistograms(EventVars* eve, TObjArray*& array, string nameHLT, int passHLT, jetMetHandler jetMetTool)
{
	// TH2D* temp = new TH2D();
	// TH2D* hist = new TH2D();
	TH2D* hist;
	string hname = "";

	// for (int i = 0; i < metTriggers.size(); i++) {
	for (uint i = 0; i < metTriggers.size(); i++) {

		hname = ("h_" + nameHLT + "__vs__" + metTriggers.at(i)).c_str();
		// *** 1. get histogram from array
		/*
		// ===  Method A: SAFE  ===
		temp = new TH2D();
		if( array->FindObject( hname.c_str()) )
		temp = (TH2D*)array->FindObject( hname.c_str() );
		else {
		if(verbose) cout<<"returnArrayHisto, NOT FOUND: "<<hname<<endl;
		}
		hist = (TH2D*)temp->Clone(); // store histogram and avoid mem issues (hopefully)
		*/

		// ===  Method B: FAST  ===
		hist = (TH2D*)array->FindObject( hname.c_str() );
        // std::cout<<hist->GetName()<<std::endl;


		// *** 2. Fill histograms depending on variable

		// if(      metTriggers.at(i) == "HLT_PFHT500_PFMET100_PFMHT100_IDTight")fill2DCorrHistogramsWithLabels(hist, passHLT, eve->passHLT_PFHT500_PFMET100_PFMHT100_IDTight_v_);
		// else if( metTriggers.at(i) == "HLT_PFHT700_PFMET85_PFMHT85_IDTight")fill2DCorrHistogramsWithLabels(hist, passHLT, eve->passHLT_PFHT700_PFMET85_PFMHT85_IDTight_v_);
		// else if( metTriggers.at(i) == "HLT_PFHT800_PFMET75_PFMHT75_IDTight")fill2DCorrHistogramsWithLabels(hist, passHLT, eve->passHLT_PFHT800_PFMET75_PFMHT75_IDTight_v_);
		// else if( metTriggers.at(i) == "HLT_PFMET250_HBHECleaned")fill2DCorrHistogramsWithLabels(hist, passHLT, eve->passHLT_PFMET250_HBHECleaned_v_);
		// else if( metTriggers.at(i) == "HLT_PFMET120_PFMHT120_IDTight")fill2DCorrHistogramsWithLabels(hist, passHLT, eve->passHLT_PFMET120_PFMHT120_IDTight_v_);
		// else if( metTriggers.at(i) == "HLT_allMET")fill2DCorrHistogramsWithLabels(hist, passHLT, jetMetTool.passAllMETTriggers);
		// else if( metTriggers.at(i) == "HLT_PFMET200_HBHE_BeamHaloCleaned")fill2DCorrHistogramsWithLabels(hist, passHLT, eve->passHLT_PFMET200_HBHE_BeamHaloCleaned_v_);
		// else if( metTriggers.at(i) == "HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned")fill2DCorrHistogramsWithLabels(hist, passHLT, eve->passHLT_PFMETTypeOne200_HBHE_BeamHaloCleaned_v_);
		// else if( metTriggers.at(i) == "HLT_PFMETNoMu120_PFMHTNoMu120_IDTight")fill2DCorrHistogramsWithLabels(hist, passHLT, eve->passHLT_PFMETNoMu120_PFMHTNoMu120_IDTight_v_);
		// else if( metTriggers.at(i) == "HLT_PFMET120_PFMHT120_IDTight_PFHT60")fill2DCorrHistogramsWithLabels(hist, passHLT, eve->passHLT_PFMET120_PFMHT120_IDTight_PFHT60_v_);
		// else if( metTriggers.at(i) == "HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60")fill2DCorrHistogramsWithLabels(hist, passHLT, eve->passHLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60_v_);
		// else if( metTriggers.at(i) == "HLT_MET200")fill2DCorrHistogramsWithLabels(hist, passHLT, eve->passHLT_MET200_v_);
		// else if( metTriggers.at(i) == "HLT_PFMET170_HBHECleaned")fill2DCorrHistogramsWithLabels(hist, passHLT, eve->passHLT_PFMET170_HBHECleaned_v_);
		// else if( metTriggers.at(i) == "HLT_PFMET300")fill2DCorrHistogramsWithLabels(hist, passHLT, eve->passHLT_PFMET300_v_);
		// else if( metTriggers.at(i) == "HLT_PFHT300_PFMET110")fill2DCorrHistogramsWithLabels(hist, passHLT, eve->passHLT_PFHT300_PFMET110_v_);

		if(      metTriggers.at(i) == "HLT_PFHT500_PFMET100_PFMHT100_IDTight")fill2DCorrHistogramsWithLabels(hist, passHLT, eve->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_);
		else if( metTriggers.at(i) == "HLT_PFHT700_PFMET85_PFMHT85_IDTight")fill2DCorrHistogramsWithLabels(hist, passHLT, eve->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_);
		else if( metTriggers.at(i) == "HLT_PFHT800_PFMET75_PFMHT75_IDTight")fill2DCorrHistogramsWithLabels(hist, passHLT, eve->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_);
		else if( metTriggers.at(i) == "HLT_PFMET250_HBHECleaned")fill2DCorrHistogramsWithLabels(hist, passHLT, eve->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_);
		else if( metTriggers.at(i) == "HLT_PFMET120_PFMHT120_IDTight")fill2DCorrHistogramsWithLabels(hist, passHLT, eve->HLT_PFMET120_PFMHT120_IDTight_);                               //
		else if( metTriggers.at(i) == "HLT_allMET")fill2DCorrHistogramsWithLabels(hist, passHLT, jetMetTool.passAllMETTriggers);                                                       //
		else if( metTriggers.at(i) == "HLT_PFMET200_HBHE_BeamHaloCleaned")fill2DCorrHistogramsWithLabels(hist, passHLT, eve->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_);
		else if( metTriggers.at(i) == "HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned")fill2DCorrHistogramsWithLabels(hist, passHLT, eve->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_);
		else if( metTriggers.at(i) == "HLT_PFMETNoMu120_PFMHTNoMu120_IDTight")fill2DCorrHistogramsWithLabels(hist, passHLT, eve->HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_);               //
		else if( metTriggers.at(i) == "HLT_PFMET120_PFMHT120_IDTight_PFHT60")fill2DCorrHistogramsWithLabels(hist, passHLT, eve->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_);
		else if( metTriggers.at(i) == "HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60")fill2DCorrHistogramsWithLabels(hist, passHLT, eve->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_);
		else if( metTriggers.at(i) == "HLT_MET200")fill2DCorrHistogramsWithLabels(hist, passHLT, eve->HLT_MET200_);                                                                     //
		
		else if( metTriggers.at(i) == "HLT_PFMET170_HBHECleaned")fill2DCorrHistogramsWithLabels(hist, passHLT, eve->HLT_PFMET170_HBHECleaned_);                                         //
		else if( metTriggers.at(i) == "HLT_PFMET300")fill2DCorrHistogramsWithLabels(hist, passHLT, eve->HLT_PFMET300_);                                                                 //

		else if( metTriggers.at(i) == "HLT_PFHT300_PFMET110")fill2DCorrHistogramsWithLabels(hist, passHLT, eve->HLT_PFHT300_PFMET110_);                                                 //





	}
}


void addOverflow(TH1D*& histo)
{
	// put overflow bin at end
	int maxBin = histo->GetNbinsX();
	histo->SetBinContent( maxBin, histo->GetBinContent( maxBin ) + histo->GetBinContent( maxBin+1 ) );
	histo->SetBinError  ( maxBin, sqrt( histo->GetBinError(maxBin)*histo->GetBinError(maxBin) + histo->GetBinError(maxBin+1)*histo->GetBinError(maxBin+1) ) );
	histo->SetBinContent( maxBin + 1, 0 );
	histo->SetBinError( maxBin + 1, 0 );
}

void addUnderflow(TH1D*& histo)
{
	// add underflow bin to first bin
	histo->SetBinContent( 1, histo->GetBinContent( 0 ) + histo->GetBinContent( 1 ) );
	histo->SetBinError  ( 1, sqrt( histo->GetBinError(0)*histo->GetBinError(0) + histo->GetBinError(1)*histo->GetBinError(1) ) );
	histo->SetBinContent( 0, 0 );
	histo->SetBinError( 0, 0 );
}

void addOverflow2D(TH2D*& histo)
{
	// Purpose: Put overflow bin at end (sidenote... how is there not a native ROOT function for this?)

	// *** 1. Loop over y axis
	int maxBin = histo->GetNbinsX();
	for (int bY=0; bY < histo->GetNbinsY()+1; bY++) {
		histo->SetBinContent( maxBin, bY, histo->GetBinContent( maxBin, bY ) + histo->GetBinContent( maxBin+1, bY ) );
		histo->SetBinError  ( maxBin, bY, sqrt( histo->GetBinError(maxBin, bY)*histo->GetBinError(maxBin, bY) + histo->GetBinError(maxBin+1, bY)*histo->GetBinError(maxBin+1, bY) ) );
		histo->SetBinContent( maxBin + 1, bY, 0 );
		histo->SetBinError( maxBin + 1, bY, 0 );
	}

	// *** 2. Loop over x axis
	maxBin = histo->GetNbinsY();
	for (int bX=0; bX < histo->GetNbinsX()+1; bX++) {
		histo->SetBinContent( bX, maxBin, histo->GetBinContent( bX, maxBin ) + histo->GetBinContent( bX, maxBin+1 ) );
		histo->SetBinError  ( bX, maxBin, sqrt( histo->GetBinError(bX, maxBin)*histo->GetBinError(bX, maxBin) + histo->GetBinError(bX, maxBin+1)*histo->GetBinError(bX, maxBin+1) ) );
		histo->SetBinContent( bX, maxBin + 1, 0 );
		histo->SetBinError( bX, maxBin + 1, 0 );
	}

}

void addUnderflow2D(TH2D*& histo)
{
	// Purpose: add underflow bin to first bin (sidenote... how is there not a native ROOT function for this?)

	// *** 1. Loop over y axis
	for (int bY=0; bY < histo->GetNbinsY()+1; bY++) {
		histo->SetBinContent( 1, bY, histo->GetBinContent( 0, bY ) + histo->GetBinContent( 1, bY ) );
		histo->SetBinError  ( 1, bY, sqrt( histo->GetBinError( 0, bY)*histo->GetBinError( 0, bY) + histo->GetBinError( 1, bY)*histo->GetBinError( 1, bY) ) );
		histo->SetBinContent( 0, bY, 0 );
		histo->SetBinError( 0, bY, 0 );
	}

	// *** 2. Loop over x axis
	for (int bX=0; bX < histo->GetNbinsX()+1; bX++) {
		histo->SetBinContent( bX, 1, histo->GetBinContent( bX, 0 ) + histo->GetBinContent( bX, 1 ) );
		histo->SetBinError  ( bX, 1, sqrt( histo->GetBinError(bX, 0 )*histo->GetBinError(bX, 0) + histo->GetBinError(bX, 1)*histo->GetBinError(bX, 1) ) );
		histo->SetBinContent( bX, 0, 0 );
		histo->SetBinError( bX, 0, 0 );
	}

}

void draw1DHistograms(TObjArray* array, TCanvas* c0, string nameHLT, string var)
{

	TH1D *h0 = (TH1D*)array->FindObject( ("h_" + nameHLT + "_" + var).c_str() );
	// *** 3. Do the drawing
	c0->cd();
	h0->Sumw2();
	addOverflow(h0);
	addUnderflow(h0);
	h0->Draw("e");

	// *** 4. Set CMS style
	//CMS_lumi( canv, iPeriod, iPos ); // <-- notes
	CMS_lumi( c0, 0, 33);

	// *** 5. Print plots
	struct stat sb;
	std::string tempDir = (topDir + nameHLT).c_str();
	if (!(stat(tempDir.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))){
		// cout << nameHLT << " subdirectory , " << tempDir << " , DNE. Creating now" << endl;
		mkdir(tempDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH);
	}
	if( printPlots) {
		c0->Print( (tempDir + "/" + h0->GetName() + ".eps").c_str());
		c0->Print( (tempDir + "/" + h0->GetName() + ".png").c_str());
	}

	//if (dumpFile)
	//  outfile->Write();
}


void draw2DHistograms(TObjArray* array, TCanvas* c0, string nameHLT, string var)
{
	TH2D *h0 = (TH2D*)array->FindObject( ("h_" + nameHLT + "_" + var).c_str() );
	// *** 3. Do the drawing
	c0->cd();
	h0->Sumw2();
	addOverflow2D(h0);
	addUnderflow2D(h0);
	//h0->Draw("e");

	// *** 4. Set CMS style
	//CMS_lumi( canv, iPeriod, iPos ); // <-- notes
	CMS_lumi( c0, 0, 33);

	// *** 5. Print plots
	struct stat sb;
	std::string tempDir = (topDir + nameHLT).c_str();
	if (!(stat(tempDir.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))){
		// cout << nameHLT << " subdirectory , " << tempDir << " , DNE. Creating now" << endl;
		mkdir(tempDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH);
	}
	if( printPlots) {
		c0->Print( (tempDir + "/" + h0->GetName() + ".eps").c_str());
		c0->Print( (tempDir + "/" + h0->GetName() + ".png").c_str());
	}

	//if (dumpFile)
	//  outfile->Write();
}


void plot1Dand2DHistograms(TObjArray* array, TCanvas* c0, string nameHLT)
{
	draw1DHistograms(array, c0, nameHLT, "el0_pt");
	draw1DHistograms(array, c0, nameHLT, "el0_eta");
	draw1DHistograms(array, c0, nameHLT, "el1_pt");
	draw1DHistograms(array, c0, nameHLT, "el1_eta");
	draw1DHistograms(array, c0, nameHLT, "mu0_pt");
	draw1DHistograms(array, c0, nameHLT, "mu0_eta");
	draw1DHistograms(array, c0, nameHLT, "mu0_relIso");
	draw1DHistograms(array, c0, nameHLT, "el0_relIso");
	draw1DHistograms(array, c0, nameHLT, "mu1_pt");
	draw1DHistograms(array, c0, nameHLT, "mu1_eta");
	draw1DHistograms(array, c0, nameHLT, "njets");
	draw1DHistograms(array, c0, nameHLT, "mll");
	draw1DHistograms(array, c0, nameHLT, "met");
	draw1DHistograms(array, c0, nameHLT, "nPV");

	draw2DHistograms(array, c0, nameHLT, "mu0_pt_vs_eta");
	draw2DHistograms(array, c0, nameHLT, "mu1_pt_vs_eta");
	draw2DHistograms(array, c0, nameHLT, "mu0_pt_vs_mu1_pt");
	draw2DHistograms(array, c0, nameHLT, "mu0_eta_vs_mu1_eta");

	draw2DHistograms(array, c0, nameHLT, "el0_pt_vs_eta");
	draw2DHistograms(array, c0, nameHLT, "el1_pt_vs_eta");
	draw2DHistograms(array, c0, nameHLT, "el0_pt_vs_el1_pt");
	draw2DHistograms(array, c0, nameHLT, "el0_eta_vs_el1_eta");

	draw2DHistograms(array, c0, nameHLT, "mu0_pt_vs_el0_pt");
	draw2DHistograms(array, c0, nameHLT, "mu0_eta_vs_el0_eta");
}


void plot2Dcorrelations(TObjArray* array, TCanvas* c0, string nameHLT)
{

	// TH2D* temp = new TH2D();
	TH2D* temp;

	// for (int i = 0; i < metTriggers.size(); i++) {
	for (uint i = 0; i < metTriggers.size(); i++) {
		// *** 0. Create histogram name
		string hname = ("h_" + nameHLT + "__vs__" + metTriggers.at(i)).c_str();

		// *** 1. Get histogram from array
		// temp = new TH2D();
		if( array->FindObject( hname.c_str()) )
			temp = (TH2D*)array->FindObject( hname.c_str() );
		else {
			if(verbose) cout<<"returnArrayHisto, NOT FOUND: "<<hname<<endl;
			temp = new TH2D();
		}
		TH2D* h0 = (TH2D*)temp->Clone();

		h0->SetXTitle( nameHLT.c_str() );
		h0->SetYTitle( metTriggers.at(i).c_str() );

		// *** 2. Setup LaTeX for printing correlation factor on plot
		TLatex ltx1;
		ltx1.SetTextAlign(9);
		ltx1.SetTextFont(62);
		ltx1.SetTextSize(0.04);
		ltx1.SetNDC();

		string s_corr;          // string which will contain the result
		std::ostringstream os_corr;  // stream used for the conversion
		os_corr << std::fixed;
		os_corr << std::setprecision(2) << h0->GetCorrelationFactor();
		s_corr = os_corr.str(); // set 'Result' to the contents of the stream


		// *** 3. Do the drawing
		c0->cd();
		h0->Draw("colz");
		ltx1.DrawLatex(0.55, 0.80, ("Corr. Factor = " + s_corr).c_str());

		cout << "Correlation Factor (" << nameHLT.c_str() << " vs " << metTriggers.at(i).c_str() << "): " << s_corr.c_str() << endl;

		// *** 4. Set CMS style
		//CMS_lumi( canv, iPeriod, iPos ); // <-- notes
		CMS_lumi( c0, 0, 11);


		// *** 5. Print plots
		struct stat sb;
		std::string tempDir = (topDir + "corr2D" + "/" + nameHLT).c_str();
		if (!(stat(tempDir.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))){
			// cout << nameHLT << " subdirectory , " << tempDir << " , DNE. Creating now" << endl;
			mkdir(tempDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH);
		}
		if( printPlots) {
			c0->Print( (tempDir + "/" + h0->GetName() + ".eps").c_str());
			c0->Print( (tempDir + "/" + h0->GetName() + ".png").c_str());
		}
	}    // end metTriggers for loop

	return;
}

void drawEfficiencyHistograms(TCanvas* c0, TObjArray* a_numerator, string nameHLT_num, TObjArray* a_denominator, string nameHLT_denom, string var)
{

	// *** 1. Get the histograms
	TH1D* h_num   = (TH1D*)a_numerator->FindObject( ("h_" + nameHLT_num + "_" + var).c_str() );
	TH1D* h_denom = (TH1D*)a_denominator->FindObject( ("h_" + nameHLT_denom + "_" + var).c_str() );
	h_num->Sumw2();
	h_denom->Sumw2();
	addOverflow(h_num);
	addOverflow(h_denom);
	addUnderflow(h_num);
	addUnderflow(h_denom);


	// cout << h_num->GetName() << " has " << h_num->GetEntries() << " entries." << endl;
	// cout << h_denom->GetName() << " has " << h_denom->GetEntries() << " entries." << endl;

	// *** 2. Divide to get efficiency
	TH1D* h_eff = (TH1D*)h_num->Clone();
	string s_eff = h_num->GetName();
	s_eff = (s_eff + "_Eff").c_str();

	h_eff->SetName( s_eff.c_str() );
	h_eff->SetTitle( s_eff.c_str() );
	h_eff->Divide(h_denom);
	h_eff->SetYTitle("Efficiency / Bin");
	//if(h_eff->GetMaximum() < 1.0)
	h_eff->SetMaximum(1.1);
	//if(h_eff->GetMinimum() > 0.0)
	h_eff->SetMinimum(0.0);

	// *** 3. Do the drawing
	c0->cd();
	h_eff->Sumw2();
	h_eff->Draw("e");

	// *** 4. Setup LaTeX for printing correlation factor on plot
	TLatex ltx1;
	ltx1.SetTextAlign(9);
	ltx1.SetTextFont(62);
	ltx1.SetTextSize(0.025);
	ltx1.SetNDC();
	ltx1.DrawLatex(0.25, 0.80, nameHLT_num.c_str() );

	// *** 5. Set CMS style
	//CMS_lumi( canv, iPeriod, iPos ); // <-- notes
	CMS_lumi( c0, 0, 33);

	// *** 6. Print plots
	struct stat sb;
	std::string tempDir = (topDir + nameHLT_num).c_str();
	if (!(stat(tempDir.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))){
		// cout << nameHLT_num << " subdirectory , " << tempDir << " , DNE. Creating now" << endl;
		mkdir(tempDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH);
	}
	tempDir = (tempDir + "/efficiency1D/").c_str();
	if (!(stat(tempDir.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))){
		// cout << nameHLT_num << " subdirectory , " << tempDir << " , DNE. Creating now" << endl;
		mkdir(tempDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH);
	}
	if( printPlots) {
		c0->Print( (tempDir + h_eff->GetName() + ".eps").c_str());
		c0->Print( (tempDir + h_eff->GetName() + ".png").c_str());
	}

}

void drawEfficiencyHistograms_v2(TCanvas* c0, TObjArray* a_numerator, string nameHLT_num, TObjArray* a_denominator, string nameHLT_denom, string var)
{

	// *** 1. Get the histograms
	TH1D* h_num   = (TH1D*)a_numerator->FindObject( ("h_" + nameHLT_num + "_" + var).c_str() );
	TH1D* h_denom = (TH1D*)a_denominator->FindObject( ("h_" + nameHLT_denom + "_" + var).c_str() );
	//cout << h_num->GetName() << " has " << h_num->GetEntries() << " entries." << endl;
	//cout << h_denom->GetName() << " has " << h_denom->GetEntries() << " entries." << endl;
	h_num->Sumw2();
	h_denom->Sumw2();
	addOverflow(h_num);
	addOverflow(h_denom);
	addUnderflow(h_num);
	addUnderflow(h_denom);

	

	// *** 2. Divide to get efficiency
	TH1D* h_eff = (TH1D*)h_num->Clone();
	string s_eff = h_num->GetName();
	s_eff = (s_eff + "_TH1").c_str();

	//h_eff->Divide(h_denom);
	h_eff->SetName( s_eff.c_str() );
	h_eff->SetTitle( s_eff.c_str() );
	h_eff->SetYTitle("Efficiency / Bin");
	h_eff->SetMaximum(1.1);
	h_eff->SetMinimum(0.0);

	TEfficiency* tEff = new TEfficiency(*h_eff, *h_denom);
	//tEff->SetStatisticOption(TEfficiency::kFNormal);
	// std::cout<<"Nome do grafico 1D numerador: "<<("h_" + nameHLT_num + "_" + var).c_str()<<endl;
	// std::cout<<"Nome do grafico 1D denominador: "<<("h_" + nameHLT_denom + "_" + var).c_str()<<endl;
	// std::cout<<"Option do graf 1D: "<<tEff->GetStatisticOption()<<endl;
	// std::cout<<"Nivel de confianca dos dados: "<<tEff->GetConfidenceLevel()<<endl;
	s_eff = h_num->GetName();
	s_eff = (s_eff + "_TEff").c_str();
	tEff->SetName( s_eff.c_str() );
	tEff->SetTitle( s_eff.c_str() );

	//std::cout<<"Histograma "<<tEff->GetName()<<" com peso de "<<tEff->GetWeight()<<std::endl;


	// *** 3. Do the drawing
	//h_eff->Sumw2();
	c0->cd();
	tEff->Draw();
	tEff->Paint("");
	// std::cout<<"Option do grafico 1D apos dar Draw(): "<<tEff->GetStatisticOption()<<endl;
	// std::cout<<"Nivel de confianca dos dados apos mudar o option: "<<tEff->GetConfidenceLevel()<<endl;

	TGraphAsymmErrors* gr = (TGraphAsymmErrors*)tEff->GetPaintedGraph();
	gr->SetMinimum(0);
	gr->SetMaximum(1.1);
	//cout << s_eff << ", Min: " << h_eff->GetXaxis()->GetXmin()  << ", Max: " << h_eff->GetXaxis()->GetXmax() << endl;
	gr->GetXaxis()->SetRangeUser( h_eff->GetXaxis()->GetXmin(), h_eff->GetXaxis()->GetXmax() );

	tEff->Draw();
	//c0->Update();

	// *** 4. Setup LaTeX for printing correlation factor on plot
	TLatex ltx1;
	ltx1.SetTextAlign(9);
	ltx1.SetTextFont(62);
	ltx1.SetTextSize(0.025);
	ltx1.SetNDC();
	ltx1.DrawLatex(0.25, 0.80, nameHLT_num.c_str() );

	// *** 5. Set CMS style
	//CMS_lumi( canv, iPeriod, iPos ); // <-- notes
	CMS_lumi( c0, 0, 33);

	// *** 6. Print plots
	struct stat sb;
	std::string tempDir = (topDir + nameHLT_num ).c_str();
	if (!(stat(tempDir.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))){
		// cout << nameHLT_num << " subdirectory , " << tempDir << " , DNE. Creating now" << endl;
		mkdir(tempDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH);
	}
	tempDir = (tempDir + "/efficiency1D/").c_str();
	if (!(stat(tempDir.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))){
		// cout << nameHLT_num << " subdirectory , " << tempDir << " , DNE. Creating now" << endl;
		mkdir(tempDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH);
	}
	if( printPlots) {
		c0->Print( (tempDir + tEff->GetName() + ".eps").c_str());
		c0->Print( (tempDir + tEff->GetName() + ".png").c_str());
	}

	// add to efficiency for storing in outfile
	a_Efficiencies->AddLast(tEff);
}

void draw2DEfficiencyHistograms_v2(TCanvas* c0, TObjArray* a_numerator, string nameHLT_num, TObjArray* a_denominator, string nameHLT_denom, string var)
{

	// *** 1. Get the histograms
	TH2D* h_num   = (TH2D*)a_numerator->FindObject( ("h_" + nameHLT_num + "_" + var).c_str() );
	TH2D* h_denom = (TH2D*)a_denominator->FindObject( ("h_" + nameHLT_denom + "_" + var).c_str() );
	//cout << h_num->GetName() << " has " << h_num->GetEntries() << " entries." << endl;
	//cout << h_denom->GetName() << " has " << h_denom->GetEntries() << " entries." << endl;
	h_num->Sumw2();
	h_denom->Sumw2();
	addOverflow2D(h_num);
	addOverflow2D(h_denom);
	addUnderflow2D(h_num);
	addUnderflow2D(h_denom);

	

	// *** 2. Divide to get efficiency
	TH2D* h_eff = (TH2D*)h_num->Clone();
	string s_eff = h_num->GetName();
	s_eff = (s_eff + "_TH2").c_str();

	//h_eff->Divide(h_denom);
	h_eff->SetName( s_eff.c_str() );
	h_eff->SetTitle( s_eff.c_str() );
	h_eff->SetYTitle("Efficiency / Bin");
	//h_eff->SetMaximum(1.1);
	//h_eff->SetMinimum(0.0);


	TEfficiency* tEff = new TEfficiency(*h_eff, *h_denom);
	//tEff->SetStatisticOption(TEfficiency::kFNormal);
	// std::cout<<"Option do grafico 2D : "<<tEff->GetStatisticOption()<<endl;
	// std::cout<<"Nivel de confianca dos dados apos mudar o option: "<<tEff->GetConfidenceLevel()<<endl;
	s_eff = h_num->GetName();
	s_eff = (s_eff + "_TEff2D").c_str();
	tEff->SetName( s_eff.c_str() );
	tEff->SetTitle( s_eff.c_str() );

	//std::cout<<"Histograma "<<tEff->GetName()<<" com peso de "<<tEff->GetWeight()<<std::endl;
	// *** 3. Do the drawing
	//h_eff->Sumw2();
	c0->cd();
	tEff->Draw();
	tEff->Paint("");
	// std::cout<<"Option do grafico 2D apos dar Draw(): "<<tEff->GetStatisticOption()<<endl;
	// std::cout<<"Nivel de confianca dos dados apos mudar o option: "<<tEff->GetConfidenceLevel()<<endl;
	//TGraphAsymmErrors* gr = (TGraphAsymmErrors*)tEff->GetPaintedGraph();
	//gr->SetMinimum(0);
	//gr->SetMaximum(1.1);
	//cout << s_eff << ", Min: " << h_eff->GetXaxis()->GetXmin()  << ", Max: " << h_eff->GetXaxis()->GetXmax() << endl;
	//gr->GetXaxis()->SetRangeUser( h_eff->GetXaxis()->GetXmin(), h_eff->GetXaxis()->GetXmax() );

	tEff->Draw();
	// std::cout<<"Option do grafico 2D apos dar Draw() pela segunda vez: "<<tEff->GetStatisticOption()<<endl;
	// std::cout<<"Nivel de confianca dos dados apos mudar o option: "<<tEff->GetConfidenceLevel()<<endl;
	//c0->Update();

	// *** 4. Setup LaTeX for printing correlation factor on plot
	TLatex ltx1;
	ltx1.SetTextAlign(9);
	ltx1.SetTextFont(62);
	ltx1.SetTextSize(0.025);
	ltx1.SetNDC();
	ltx1.DrawLatex(0.25, 0.80, nameHLT_num.c_str() );

	// *** 5. Set CMS style
	//CMS_lumi( canv, iPeriod, iPos ); // <-- notes
	CMS_lumi( c0, 0, 33);

	// *** 6. Print plots
	struct stat sb;
	std::string tempDir = (topDir + nameHLT_num ).c_str();
	if (!(stat(tempDir.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))){
		// cout << nameHLT_num << " subdirectory , " << tempDir << " , DNE. Creating now" << endl;
		mkdir(tempDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH);
	}
	tempDir = (tempDir + "/efficiency1D/").c_str();
	if (!(stat(tempDir.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))){
		// cout << nameHLT_num << " subdirectory , " << tempDir << " , DNE. Creating now" << endl;
		mkdir(tempDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH);
	}
	if( printPlots) {
		c0->Print( (tempDir + tEff->GetName() + ".eps").c_str());
		c0->Print( (tempDir + tEff->GetName() + ".png").c_str());
	}

	// add to efficiency for storing in outfile
	a_Efficiencies->AddLast(tEff);
}

void makeEfficiencyHistograms(TCanvas* c0, TObjArray* a_numerator, string nameHLT_num, TObjArray* a_denominator, string nameHLT_denom)
{
	/*drawEfficiencyHistograms(c0, a_numerator, nameHLT_num, a_denominator, nameHLT_denom, "el0_pt");
	drawEfficiencyHistograms(c0, a_numerator, nameHLT_num, a_denominator, nameHLT_denom, "njets");
	drawEfficiencyHistograms(c0, a_numerator, nameHLT_num, a_denominator, nameHLT_denom, "met");
	*/
	drawEfficiencyHistograms_v2(c0, a_numerator, nameHLT_num, a_denominator, nameHLT_denom, "el0_pt");
	drawEfficiencyHistograms_v2(c0, a_numerator, nameHLT_num, a_denominator, nameHLT_denom, "el0_eta");
	drawEfficiencyHistograms_v2(c0, a_numerator, nameHLT_num, a_denominator, nameHLT_denom, "el1_pt");
	drawEfficiencyHistograms_v2(c0, a_numerator, nameHLT_num, a_denominator, nameHLT_denom, "el1_eta");
	drawEfficiencyHistograms_v2(c0, a_numerator, nameHLT_num, a_denominator, nameHLT_denom, "mu0_pt");
	drawEfficiencyHistograms_v2(c0, a_numerator, nameHLT_num, a_denominator, nameHLT_denom, "mu0_eta");
	drawEfficiencyHistograms_v2(c0, a_numerator, nameHLT_num, a_denominator, nameHLT_denom, "mu0_relIso");
	drawEfficiencyHistograms_v2(c0, a_numerator, nameHLT_num, a_denominator, nameHLT_denom, "el0_relIso");
	drawEfficiencyHistograms_v2(c0, a_numerator, nameHLT_num, a_denominator, nameHLT_denom, "mu1_pt");
	drawEfficiencyHistograms_v2(c0, a_numerator, nameHLT_num, a_denominator, nameHLT_denom, "mu1_eta");
	drawEfficiencyHistograms_v2(c0, a_numerator, nameHLT_num, a_denominator, nameHLT_denom, "njets");
	drawEfficiencyHistograms_v2(c0, a_numerator, nameHLT_num, a_denominator, nameHLT_denom, "mll");
	drawEfficiencyHistograms_v2(c0, a_numerator, nameHLT_num, a_denominator, nameHLT_denom, "met");
	drawEfficiencyHistograms_v2(c0, a_numerator, nameHLT_num, a_denominator, nameHLT_denom, "nPV");

	draw2DEfficiencyHistograms_v2(c0, a_numerator, nameHLT_num, a_denominator, nameHLT_denom, "mu0_pt_vs_eta");
	draw2DEfficiencyHistograms_v2(c0, a_numerator, nameHLT_num, a_denominator, nameHLT_denom, "mu1_pt_vs_eta");
	draw2DEfficiencyHistograms_v2(c0, a_numerator, nameHLT_num, a_denominator, nameHLT_denom, "mu0_pt_vs_mu1_pt");
	draw2DEfficiencyHistograms_v2(c0, a_numerator, nameHLT_num, a_denominator, nameHLT_denom, "mu0_eta_vs_mu1_eta");

	draw2DEfficiencyHistograms_v2(c0, a_numerator, nameHLT_num, a_denominator, nameHLT_denom, "el0_pt_vs_eta");
	draw2DEfficiencyHistograms_v2(c0, a_numerator, nameHLT_num, a_denominator, nameHLT_denom, "el1_pt_vs_eta");
	draw2DEfficiencyHistograms_v2(c0, a_numerator, nameHLT_num, a_denominator, nameHLT_denom, "el0_pt_vs_el1_pt");
	draw2DEfficiencyHistograms_v2(c0, a_numerator, nameHLT_num, a_denominator, nameHLT_denom, "el0_eta_vs_el1_eta");

	draw2DEfficiencyHistograms_v2(c0, a_numerator, nameHLT_num, a_denominator, nameHLT_denom, "mu0_pt_vs_el0_pt");
	draw2DEfficiencyHistograms_v2(c0, a_numerator, nameHLT_num, a_denominator, nameHLT_denom, "mu0_eta_vs_el0_eta");

}

TH1D* returnRatioHistogram(TH1D* data, TH1D* pred)
{
	TH1D* h_ratio = (TH1D*)data->Clone();
	double binError, ratio, errData, errPred = 0;

	for(int b = 0; b < h_ratio->GetNbinsX() + 1; b++) {
		binError = 0;
		errPred  = 0;
		errData  = 0;
		ratio = 0.15;

		if (pred->GetBinContent(b) > 0 ) {
			ratio =  data->GetBinContent(b) / pred->GetBinContent(b);
			errData = data->GetBinContent(b) != 0 ? (data->GetBinError(b)/data->GetBinContent(b))*(data->GetBinError(b)/data->GetBinContent(b)) : 0;
			errPred = pred->GetBinContent(b) != 0 ? (pred->GetBinError(b)/pred->GetBinContent(b))*(pred->GetBinError(b)/pred->GetBinContent(b)) : 0;
			binError = ratio * sqrt( errData + errPred);
			if(data->GetBinContent(b) != 0) {
				h_ratio->SetBinContent(b, ratio);
				h_ratio->SetBinError(b, binError);
			}
		}

	}
	return h_ratio;
}
