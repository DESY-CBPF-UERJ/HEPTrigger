
// Author:  Ben Tannenwald
// Date:    Feb 27, 2018
// Purpose: Macro to make trigger correlation/efficiency plots

#include <TFile.h>
#include <TDirectory.h>
#include <TTree.h>
#include <TBranch.h>
#include <TCanvas.h>
#include <TSystem.h>
#include <TChain.h>
#include <TFileCollection.h>
#include <TH2.h>
#include <TLatex.h>
#include <TString.h>
#include <TObjArray.h>

// #include "include/YggdrasilEventVars.h"
#include "include/EventVars.h"
#include "include/trigEffStudy.h"
#include "include/histogramHandler.h"

// Object Handlers
#include "src/leptonHandler.C"
#include "src/jetMetHandler.C"

#include <iostream>
#include <iomanip>      // std::setprecision
#include <sstream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

// void printProgBar( const int percent );
void printProgBar( const int& percent );
void plot2Dcorr( TCanvas*& c0, TH2D*& h0, string xtitle, string ytitle);

void trigEffStudy(string p_topDir="", string p_isMC="", string p_passFile="", string p_trigSF="", int era=0)
{
	// *** 0. Set style, set file, set output directory
	// ** A. Set output directory and global bools
	topDir = "plots_19_6_2020_MC_2016_withSFs_9_1/";
	if (p_topDir != "") topDir = p_topDir;
	isMC = true;
	isTrigSF = true;
	if (p_isMC != "") isMC = (p_isMC=="true" || p_isMC=="True") ? true : false;
	if (p_trigSF != "") isTrigSF = (p_trigSF=="true" || p_trigSF=="True") ? true : false;

	if(isTrigSF) cout<<"### p_trigSF=="<<p_trigSF<<" is TRUE!!!"<<endl;
	else	     cout<<"### p_trigSF=="<<p_trigSF<<" is FALSE!!!"<<endl;

    cout<<"ERA = "<<era<<endl;

	singleFile = true;
	fileList="";
	printPlots = false;
	dumpFile = true;
	verbose = false;
	// ** B. Set input file
	// TChain* fChain = new TChain("ttHTreeMaker/worldTree");
	TChain* fChain = new TChain("convertedTree");
	if(singleFile) { // single file
		if (p_passFile==""){ // basically a local test
			if (isMC){ //MC
        			fChain->AddFile("/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2016/MC.root");
      			}
	      		else{ // data!
				fChain->AddFile("/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2016/Data.root");
      			}
    		}
    		else // pass name of analysis file --> this probably means Condor submission
      			fChain->AddFile( p_passFile.c_str() );
				
  	}
  	else{ // entire directory
			if (isMC)
			fileList="";
      			//fileList="input_file";
    		else // data!
      			fileList="";
    		// check to make sure fileList
    		if(gSystem->AccessPathName(fileList.c_str()) )
      		{
			cout<<"Input list file /"<<fileList.c_str()<<" DNE."<<endl;
			gSystem->Exit(0);
	      	}
    		TFileCollection *fc= new TFileCollection("fc","files",fileList.c_str());
    		fChain->AddFileInfoList((TCollection*)fc->GetList());
  	}

	// ** C. Check subdirectory structure for requested options and create directories if necessary
	// * i. Check if topdir exists
	struct stat sb;
	if (!(stat(topDir.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))){
		cout << "top-level director, " << topDir << " , DNE. Creating now" << endl;
		mkdir(topDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH);
	}

	// * ii. Create corr2D subdir
	std::string sampleDir = "";
	if(isMC)
		sampleDir = "/MC";
	else
		sampleDir = "/data";

	topDir = (topDir + sampleDir + "/").c_str();
	if (!(stat(topDir.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))){
		cout << "sample subdirectory , " << topDir << " , DNE. Creating now" << endl;
		mkdir(topDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH);
	}
	// * iii. Set output file
	if(p_passFile == "")
		outfile = new TFile( (topDir + "/outfile.root").c_str(), "RECREATE");
	else // add identifier so no overwrites
		outfile = new TFile( (topDir + "/outfile" + p_passFile.substr(p_passFile.find_last_of("_"), p_passFile.find(".root")) ).c_str(), "RECREATE");

	// * iv. Create corr2D subdir
	std::string tempDir = (topDir + "corr2D" + "/").c_str();
	if (!(stat(tempDir.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))){
		cout << "corr2D subdirectory , " << tempDir << " , DNE. Creating now" << endl;
		mkdir(tempDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH);
	}

	// ** D. CMS Style
	// setTDRStyle();
	setTDRStyle_teliko();
	writeExtraText = true;	// if extra text
	//extraText  = "Internal";  // default extra text is "Preliminary"
	lumi_sqrtS = "#sqrt{s} = 13 TeV";       // used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)
  	int iPeriod = 0;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV, 0=free form (uses lumi_sqrtS)

	std::cout<<"era="<<era<<endl;

	// *** 1. Define histograms and canvasses
	TCanvas *c0 = new TCanvas("c0", "c0", 50, 50, 800, 600);

	initializeHistograms(a_HLT_allMET, "HLT_allMET", true,era);

	initializeHistograms(a_DoubleEl_OR__X__allMET_DenSum2Fail, "DoubleEl_OR__X__allMET_DenSum2Fail",false,era);
	initializeHistograms(a_DoubleEl_OR__X__allMET_DenSum2Win, "DoubleEl_OR__X__allMET_DenSum2Win",false,era);
	initializeHistograms(a_DoubleEl_OR__X__allMET_NumSum2Fail, "DoubleEl_OR__X__allMET_NumSum2Fail",false,era);
	initializeHistograms(a_DoubleEl_OR__X__allMET_NumSum2Win, "DoubleEl_OR__X__allMET_NumSum2Win",false,era);

	initializeHistograms(a_EMu_OR__X__allMET_DenSum2Fail, "EMu_OR__X__allMET_DenSum2Fail",false,era);
	initializeHistograms(a_EMu_OR__X__allMET_DenSum2Win, "EMu_OR__X__allMET_DenSum2Win",false,era);
	initializeHistograms(a_EMu_OR__X__allMET_NumSum2Fail, "EMu_OR__X__allMET_NumSum2Fail",false,era);
	initializeHistograms(a_EMu_OR__X__allMET_NumSum2Win, "EMu_OR__X__allMET_NumSum2Win",false,era);


	initializeHistograms(a_DoubleMu_OR__X__allMET_DenSum2Fail, "DoubleMu_OR__X__allMET_DenSum2Fail",false,era);
	initializeHistograms(a_DoubleMu_OR__X__allMET_DenSum2Win, "DoubleMu_OR__X__allMET_DenSum2Win",false,era);
	initializeHistograms(a_DoubleMu_OR__X__allMET_NumSum2Fail, "DoubleMu_OR__X__allMET_NumSum2Fail",false,era);
	initializeHistograms(a_DoubleMu_OR__X__allMET_NumSum2Win, "DoubleMu_OR__X__allMET_NumSum2Win",false,era);

	initializeHistograms(a_HLT_DoubleMu_OR, "HLT_DoubleMu_OR",false,era);
	initializeHistograms(a_HLT_DoubleEl_OR, "HLT_DoubleEl_OR",false,era);
	initializeHistograms(a_HLT_EMu_OR, "HLT_EMu_OR",false,era);
	initializeHistograms(a_DoubleMu_OR__X__allMET, "DoubleMu_OR__X__allMET",false,era);
	initializeHistograms(a_DoubleEl_OR__X__allMET, "DoubleEl_OR__X__allMET",false,era);
	initializeHistograms(a_EMu_OR__X__allMET, "EMu_OR__X__allMET",false,era);

    initializeHistograms(a_HLT_DoubleMu_OR_NJETSHIGH, "HLT_DoubleMu_OR_NJETSHIGH",false,era);
    initializeHistograms(a_HLT_DoubleEl_OR_NJETSHIGH, "HLT_DoubleEl_OR_NJETSHIGH",false,era);
    initializeHistograms(a_HLT_EMu_OR_NJETSHIGH, "HLT_EMu_OR_NJETSHIGH",false,era);
    initializeHistograms(a_DoubleMu_OR__X__allMET_NJETSHIGH, "DoubleMu_OR__X__allMET_NJETSHIGH",false,era);
    initializeHistograms(a_DoubleEl_OR__X__allMET_NJETSHIGH, "DoubleEl_OR__X__allMET_NJETSHIGH",false,era);
    initializeHistograms(a_EMu_OR__X__allMET_NJETSHIGH, "EMu_OR__X__allMET_NJETSHIGH",false,era);

    initializeHistograms(a_HLT_DoubleMu_OR_NJETSLOW, "HLT_DoubleMu_OR_NJETSLOW",false,era);
    initializeHistograms(a_HLT_DoubleEl_OR_NJETSLOW, "HLT_DoubleEl_OR_NJETSLOW",false,era);
    initializeHistograms(a_HLT_EMu_OR_NJETSLOW, "HLT_EMu_OR_NJETSLOW",false,era);
    initializeHistograms(a_DoubleMu_OR__X__allMET_NJETSLOW, "DoubleMu_OR__X__allMET_NJETSLOW",false,era);
    initializeHistograms(a_DoubleEl_OR__X__allMET_NJETSLOW, "DoubleEl_OR__X__allMET_NJETSLOW",false,era);
    initializeHistograms(a_EMu_OR__X__allMET_NJETSLOW, "EMu_OR__X__allMET_NJETSLOW",false,era);

    initializeHistograms(a_HLT_DoubleMu_OR_NPVHIGH, "HLT_DoubleMu_OR_NPVHIGH",false,era);
    initializeHistograms(a_HLT_DoubleEl_OR_NPVHIGH, "HLT_DoubleEl_OR_NPVHIGH",false,era);
    initializeHistograms(a_HLT_EMu_OR_NPVHIGH, "HLT_EMu_OR_NPVHIGH",false,era);
    initializeHistograms(a_DoubleMu_OR__X__allMET_NPVHIGH, "DoubleMu_OR__X__allMET_NPVHIGH",false,era);
    initializeHistograms(a_DoubleEl_OR__X__allMET_NPVHIGH, "DoubleEl_OR__X__allMET_NPVHIGH",false,era);
    initializeHistograms(a_EMu_OR__X__allMET_NPVHIGH, "EMu_OR__X__allMET_NPVHIGH",false,era);

    initializeHistograms(a_HLT_DoubleMu_OR_NPVLOW, "HLT_DoubleMu_OR_NPVLOW",false,era);
    initializeHistograms(a_HLT_DoubleEl_OR_NPVLOW, "HLT_DoubleEl_OR_NPVLOW",false,era);
    initializeHistograms(a_HLT_EMu_OR_NPVLOW, "HLT_EMu_OR_NPVLOW",false,era);
    initializeHistograms(a_DoubleMu_OR__X__allMET_NPVLOW, "DoubleMu_OR__X__allMET_NPVLOW",false,era);
    initializeHistograms(a_DoubleEl_OR__X__allMET_NPVLOW, "DoubleEl_OR__X__allMET_NPVLOW",false,era);
    initializeHistograms(a_EMu_OR__X__allMET_NPVLOW, "EMu_OR__X__allMET_NPVLOW",false,era);

    initializeHistograms(a_HLT_DoubleMu_OR_METHIGH, "HLT_DoubleMu_OR_METHIGH",false,era);
    initializeHistograms(a_HLT_DoubleEl_OR_METHIGH, "HLT_DoubleEl_OR_METHIGH",false,era);
    initializeHistograms(a_HLT_EMu_OR_METHIGH, "HLT_EMu_OR_METHIGH",false,era);
    initializeHistograms(a_DoubleMu_OR__X__allMET_METHIGH, "DoubleMu_OR__X__allMET_METHIGH",false,era);
    initializeHistograms(a_DoubleEl_OR__X__allMET_METHIGH, "DoubleEl_OR__X__allMET_METHIGH",false,era);
    initializeHistograms(a_EMu_OR__X__allMET_METHIGH, "EMu_OR__X__allMET_METHIGH",false,era);

    initializeHistograms(a_HLT_DoubleMu_OR_METLOW, "HLT_DoubleMu_OR_METLOW",false,era);
    initializeHistograms(a_HLT_DoubleEl_OR_METLOW, "HLT_DoubleEl_OR_METLOW",false,era);
    initializeHistograms(a_HLT_EMu_OR_METLOW, "HLT_EMu_OR_METLOW",false,era);
    initializeHistograms(a_DoubleMu_OR__X__allMET_METLOW, "DoubleMu_OR__X__allMET_METLOW",false,era);
    initializeHistograms(a_DoubleEl_OR__X__allMET_METLOW, "DoubleEl_OR__X__allMET_METLOW",false,era);
    initializeHistograms(a_EMu_OR__X__allMET_METLOW, "EMu_OR__X__allMET_METLOW",false,era);

	initializeHistograms(a_HLT_DoubleMu_OR_NMu2, "HLT_DoubleMu_OR_NMu2",false,era);
    initializeHistograms(a_HLT_DoubleEl_OR_NMu2, "HLT_DoubleEl_OR_NMu2",false,era);
    initializeHistograms(a_HLT_EMu_OR_NMu2, "HLT_EMu_OR_NMu2",false,era);
    initializeHistograms(a_DoubleMu_OR__X__allMET_NMu2, "DoubleMu_OR__X__allMET_NMu2",false,era);
    initializeHistograms(a_DoubleEl_OR__X__allMET_NMu2, "DoubleEl_OR__X__allMET_NMu2",false,era);
    initializeHistograms(a_EMu_OR__X__allMET_NMu2, "EMu_OR__X__allMET_NMu2",false,era);

	initializeHistograms(a_HLT_DoubleMu_OR_NMu3, "HLT_DoubleMu_OR_NMu3",false,era);
    initializeHistograms(a_HLT_DoubleEl_OR_NMu3, "HLT_DoubleEl_OR_NMu3",false,era);
    initializeHistograms(a_HLT_EMu_OR_NMu3, "HLT_EMu_OR_NMu3",false,era);
    initializeHistograms(a_DoubleMu_OR__X__allMET_NMu3, "DoubleMu_OR__X__allMET_NMu3",false,era);
    initializeHistograms(a_DoubleEl_OR__X__allMET_NMu3, "DoubleEl_OR__X__allMET_NMu3",false,era);
    initializeHistograms(a_EMu_OR__X__allMET_NMu3, "EMu_OR__X__allMET_NMu3",false,era);

	initializeHistograms(a_HLT_DoubleMu_OR_NMu4, "HLT_DoubleMu_OR_NMu4",false,era);
    initializeHistograms(a_HLT_DoubleEl_OR_NMu4, "HLT_DoubleEl_OR_NMu4",false,era);
    initializeHistograms(a_HLT_EMu_OR_NMu4, "HLT_EMu_OR_NMu4",false,era);
    initializeHistograms(a_DoubleMu_OR__X__allMET_NMu4, "DoubleMu_OR__X__allMET_NMu4",false,era);
    initializeHistograms(a_DoubleEl_OR__X__allMET_NMu4, "DoubleEl_OR__X__allMET_NMu4",false,era);
    initializeHistograms(a_EMu_OR__X__allMET_NMu4, "EMu_OR__X__allMET_NMu4",false,era);


	// *** 2. Set tree structure and variables to read
	eve=0;
	fChain->SetBranchAddress("events", &eve );
	lepTool.era_=era;
	lepTool.setFlags(isMC, p_passFile.c_str());
	jetMetTool.era_=era;

	long processed=0;
	// *** 3. Start looping!
	long t_entries = fChain->GetEntries();
	cout << "Chain entries: " << t_entries << endl;
	printProgBar(0.);
	int counter=0,counter_2 = 0,counter_3 = 0,counter_4 = 0,counter_5 = 0,counter_6 = 0,counter_7 = 0,counter_8 = 0,counter_9 = 0,counter_10 = 0,counter_11 = 0,counter_12 = 0; 
        for(int i = 0; i < t_entries; i++) {
		// cout<<"==============================="<<endl;
		// cout<<"evento "<<i<<":"<<endl;	
        // for(int i = 0; i < 3000000; i++) {

		// if ( t_entries > 100) {
		// 	if ((i+1)%(5*t_entries/100)==0)  printProgBar(100*i/t_entries +1);
		// }
		// if (i == t_entries-1) {printProgBar(100); cout << endl;}
		processed++;
		if(processed % 1000 == 0) {
			int progress = 100*(float)processed/t_entries;
			printProgBar(progress);
		}
    		fChain->GetEntry(i);
    		// ** 0. Set debug flags per event
    		//if ( !isTrigSF && ( eve->evt == 3280938 || eve->evt == 6895311 || eve->evt == 7772097 || eve->evt == 6896348 || eve->evt == 7984706 || eve->evt == 7247651 || eve->evt == 6896671))
      		//	isDebug = true;
    		//else
      		//	isDebug = false;
    		// ** I. Get objects
    		lepTool.Event(eve, isDebug, isTrigSF);
    		jetMetTool.Event(eve, lepTool, isDebug, isTrigSF);
    		// * B. logical OR of triggers
    		/* Charis : The following fill histogramms that are used for correlation calculations where we can extract information whether an event has passed the MET & DL/SL trigger parth, one of them or none */

		if (lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts) fill2DCorrHistograms(eve, a_HLT_DoubleEl_OR, "HLT_DoubleEl_OR", (lepTool.passSLtriggers_el || lepTool.passDLtriggers_el) , jetMetTool );
		if (lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts) fill2DCorrHistograms(eve, a_HLT_DoubleMu_OR, "HLT_DoubleMu_OR", (lepTool.passSLtriggers_mu || lepTool.passDLtriggers_mu), jetMetTool );
		if (lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts) fill2DCorrHistograms(eve, a_HLT_EMu_OR, "HLT_EMu_OR", (lepTool.passSLtriggers_el || lepTool.passSLtriggers_mu || lepTool.passDLtriggers_emu), jetMetTool );


		
		//PREENCHE OS HISTOGRAMAS QUE REPRESENTAM AQUELES QUE PASSARAM POR ALGUM TRIGGER DE MET
		// fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_allMET, "HLT_allMET", p_passFile.c_str(), true,false);
	  	if ( jetMetTool.passAllMETTriggers)fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_allMET, "HLT_allMET", p_passFile.c_str(), true,false);



		//CRIAÇÃO DO HISTOGRAMA COM OS PESOS AO QUADRADO, ISSO É FEITO MUDANDO A ULTIMA FLAG PRA TRUE
		//CASO 1: EVENTOS QUE NÃO PASSARAM E PASSARAM PELOS TRIGGERS DE DILEPTON, CANAL ElEL. Eventos que não passaram pelos cortes do triggers de dilepton ou dos triggers de MET 
   		if(lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts && jetMetTool.passAllMETTriggers){
		   if (!(lepTool.passSLtriggers_el || lepTool.passDLtriggers_el)){ 
			   fillEfficiencyHistograms(lepTool, jetMetTool, a_DoubleEl_OR__X__allMET_DenSum2Fail, "DoubleEl_OR__X__allMET_DenSum2Fail", p_passFile.c_str(),false,true);
			   fillEfficiencyHistograms(lepTool, jetMetTool, a_DoubleEl_OR__X__allMET_NumSum2Fail, "DoubleEl_OR__X__allMET_NumSum2Fail", p_passFile.c_str(),false,false);
			}
		   if (lepTool.passSLtriggers_el || lepTool.passDLtriggers_el){ 
				fillEfficiencyHistograms(lepTool, jetMetTool, a_DoubleEl_OR__X__allMET_DenSum2Win, "DoubleEl_OR__X__allMET_DenSum2Win", p_passFile.c_str(),false,true);
		   		fillEfficiencyHistograms(lepTool, jetMetTool, a_DoubleEl_OR__X__allMET_NumSum2Win, "DoubleEl_OR__X__allMET_NumSum2Win", p_passFile.c_str(),false,false);
		   }
		}
		//CASO 2: EVENTOS QUE NÃO PASSARAM E PASSARAM PELOS TRIGGERS DE DILEPTON, CANAL MuMu.
		if(lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts && jetMetTool.passAllMETTriggers){
			if (!(lepTool.passSLtriggers_mu || lepTool.passDLtriggers_mu)){
				fillEfficiencyHistograms(lepTool, jetMetTool, a_DoubleMu_OR__X__allMET_DenSum2Fail, "DoubleMu_OR__X__allMET_DenSum2Fail", p_passFile.c_str(),false,true);
				fillEfficiencyHistograms(lepTool, jetMetTool, a_DoubleMu_OR__X__allMET_NumSum2Fail, "DoubleMu_OR__X__allMET_NumSum2Fail", p_passFile.c_str(),false,false);
			}
			if ((lepTool.passSLtriggers_mu || lepTool.passDLtriggers_mu)){
				fillEfficiencyHistograms(lepTool, jetMetTool, a_DoubleMu_OR__X__allMET_DenSum2Win, "DoubleMu_OR__X__allMET_DenSum2Win", p_passFile.c_str(),false,true);
				fillEfficiencyHistograms(lepTool, jetMetTool, a_DoubleMu_OR__X__allMET_NumSum2Win, "DoubleMu_OR__X__allMET_NumSum2Win", p_passFile.c_str(),false,false);
			}

		}
		//CASO 3: EVENTOS QUE NÃO PASSARAM E PASSARAM PELOS TRIGGERS DE DILEPTON, CANAL ELMu.
		if (lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts && jetMetTool.passAllMETTriggers){
			if(!(lepTool.passSLtriggers_el || lepTool.passSLtriggers_mu || lepTool.passDLtriggers_emu)){
				fillEfficiencyHistograms(lepTool, jetMetTool, a_EMu_OR__X__allMET_DenSum2Fail, "EMu_OR__X__allMET_DenSum2Fail", p_passFile.c_str(),false,true);
				fillEfficiencyHistograms(lepTool, jetMetTool, a_EMu_OR__X__allMET_NumSum2Fail, "EMu_OR__X__allMET_NumSum2Fail", p_passFile.c_str(),false,false);
			}
			if((lepTool.passSLtriggers_el || lepTool.passSLtriggers_mu || lepTool.passDLtriggers_emu)){
				fillEfficiencyHistograms(lepTool, jetMetTool, a_EMu_OR__X__allMET_DenSum2Win, "EMu_OR__X__allMET_DenSum2Win", p_passFile.c_str(),false,true);
				fillEfficiencyHistograms(lepTool, jetMetTool, a_EMu_OR__X__allMET_NumSum2Win, "EMu_OR__X__allMET_NumSum2Win", p_passFile.c_str(),false,false);

			}
		}



			// if ( (lepTool.passSLtriggers_el || lepTool.passSLtriggers_mu || lepTool.passDLtriggers_emu)){counter++;} /////////////////
			// if (lepTool.passDLCuts_emu ){counter_1++;}
			// if (jetMetTool.passDLJetMetCuts ){counter_2++;}
			// if (lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts){counter_3++;}
			// if ((lepTool.passSLtriggers_mu || lepTool.passDLtriggers_mu) && lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts){counter_4++;}
    			// II. using logical OR of SL and DL triggers
				// Nominal
    			// dilepton, ee
    		if ((lepTool.passSLtriggers_el || lepTool.passDLtriggers_el) && lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts)fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_DoubleEl_OR, "HLT_DoubleEl_OR", p_passFile.c_str(),false,false);
    		if ((lepTool.passSLtriggers_el || lepTool.passDLtriggers_el) && lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_DoubleEl_OR__X__allMET, "DoubleEl_OR__X__allMET", p_passFile.c_str(),false,false);
    		// // dilepton, mumu
    		if ((lepTool.passSLtriggers_mu || lepTool.passDLtriggers_mu) && lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_DoubleMu_OR, "HLT_DoubleMu_OR", p_passFile.c_str(),false,false);
    		if ((lepTool.passSLtriggers_mu || lepTool.passDLtriggers_mu) && lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_DoubleMu_OR__X__allMET, "DoubleMu_OR__X__allMET", p_passFile.c_str(),false,false);
    		// // dilepton, emu
    		if ((lepTool.passSLtriggers_el || lepTool.passSLtriggers_mu || lepTool.passDLtriggers_emu) && lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_EMu_OR, "HLT_EMu_OR", p_passFile.c_str(),false,false);
    		if ((lepTool.passSLtriggers_el || lepTool.passSLtriggers_mu || lepTool.passDLtriggers_emu) && lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_EMu_OR__X__allMET, "EMu_OR__X__allMET", p_passFile.c_str(),false,false);

                // II. using logical OR of SL and DL triggers
                // NJets high region
                // dilepton, ee
                if ((lepTool.passSLtriggers_el || lepTool.passDLtriggers_el) && lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts && (jetMetTool.passNjetsCuts == 1) ) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_DoubleEl_OR_NJETSHIGH, "HLT_DoubleEl_OR_NJETSHIGH", p_passFile.c_str(),false,false);
                if ((lepTool.passSLtriggers_el || lepTool.passDLtriggers_el) && lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts && (jetMetTool.passNjetsCuts == 1) && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_DoubleEl_OR__X__allMET_NJETSHIGH, "DoubleEl_OR__X__allMET_NJETSHIGH", p_passFile.c_str(),false,false);
                // dilepton, mumu
                if ((lepTool.passSLtriggers_mu || lepTool.passDLtriggers_mu) && lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts && (jetMetTool.passNjetsCuts == 1) ) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_DoubleMu_OR_NJETSHIGH, "HLT_DoubleMu_OR_NJETSHIGH", p_passFile.c_str(),false,false);
                if ((lepTool.passSLtriggers_mu || lepTool.passDLtriggers_mu) && lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts && (jetMetTool.passNjetsCuts == 1) && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_DoubleMu_OR__X__allMET_NJETSHIGH, "DoubleMu_OR__X__allMET_NJETSHIGH", p_passFile.c_str(),false,false);
                // dilepton, emu
                if ((lepTool.passSLtriggers_el || lepTool.passSLtriggers_mu || lepTool.passDLtriggers_emu) && lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts && (jetMetTool.passNjetsCuts == 1) ) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_EMu_OR_NJETSHIGH, "HLT_EMu_OR_NJETSHIGH", p_passFile.c_str(),false,false);
                if ((lepTool.passSLtriggers_el || lepTool.passSLtriggers_mu || lepTool.passDLtriggers_emu) && lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts && (jetMetTool.passNjetsCuts == 1) && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_EMu_OR__X__allMET_NJETSHIGH, "EMu_OR__X__allMET_NJETSHIGH", p_passFile.c_str());
                // II. using logical OR of SL and DL triggers
                //NJets low region
                // dilepton, ee
                if ((lepTool.passSLtriggers_el || lepTool.passDLtriggers_el) && lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts && (jetMetTool.passNjetsCuts == 0) ) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_DoubleEl_OR_NJETSLOW, "HLT_DoubleEl_OR_NJETSLOW", p_passFile.c_str(),false,false);
                if ((lepTool.passSLtriggers_el || lepTool.passDLtriggers_el) && lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts && (jetMetTool.passNjetsCuts == 0 ) && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_DoubleEl_OR__X__allMET_NJETSLOW, "DoubleEl_OR__X__allMET_NJETSLOW", p_passFile.c_str(),false,false);
                // dilepton, mumu
                if ((lepTool.passSLtriggers_mu || lepTool.passDLtriggers_mu) && lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts && (jetMetTool.passNjetsCuts == 0 ) ) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_DoubleMu_OR_NJETSLOW, "HLT_DoubleMu_OR_NJETSLOW", p_passFile.c_str(),false,false);
                if ((lepTool.passSLtriggers_mu || lepTool.passDLtriggers_mu) && lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts && (jetMetTool.passNjetsCuts == 0) && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_DoubleMu_OR__X__allMET_NJETSLOW, "DoubleMu_OR__X__allMET_NJETSLOW", p_passFile.c_str(),false,false);
                // dilepton, emu
                if ((lepTool.passSLtriggers_el || lepTool.passSLtriggers_mu || lepTool.passDLtriggers_emu) && lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts && (jetMetTool.passNjetsCuts == 0 ) ) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_EMu_OR_NJETSLOW, "HLT_EMu_OR_NJETSLOW", p_passFile.c_str(),false,false);
                if ((lepTool.passSLtriggers_el || lepTool.passSLtriggers_mu || lepTool.passDLtriggers_emu) && lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts && (jetMetTool.passNjetsCuts  == 0 ) && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_EMu_OR__X__allMET_NJETSLOW, "EMu_OR__X__allMET_NJETSLOW", p_passFile.c_str(),false,false);


                // II. using logical OR of SL and DL triggers
                //NPV high region
                // dilepton, ee
                if ((lepTool.passSLtriggers_el || lepTool.passDLtriggers_el) && lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts && (jetMetTool.passNPVCuts == 1) ) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_DoubleEl_OR_NPVHIGH, "HLT_DoubleEl_OR_NPVHIGH", p_passFile.c_str(),false,false);
                if ((lepTool.passSLtriggers_el || lepTool.passDLtriggers_el) && lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts && (jetMetTool.passNPVCuts == 1) && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_DoubleEl_OR__X__allMET_NPVHIGH, "DoubleEl_OR__X__allMET_NPVHIGH", p_passFile.c_str(),false,false);
                // dilepton, mumu
                if ((lepTool.passSLtriggers_mu || lepTool.passDLtriggers_mu) && lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts && (jetMetTool.passNPVCuts == 1) ) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_DoubleMu_OR_NPVHIGH, "HLT_DoubleMu_OR_NPVHIGH", p_passFile.c_str(),false,false);
                if ((lepTool.passSLtriggers_mu || lepTool.passDLtriggers_mu) && lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts && (jetMetTool.passNPVCuts == 1) && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_DoubleMu_OR__X__allMET_NPVHIGH, "DoubleMu_OR__X__allMET_NPVHIGH", p_passFile.c_str(),false,false);
                // dilepton, emu
                if ((lepTool.passSLtriggers_el || lepTool.passSLtriggers_mu || lepTool.passDLtriggers_emu) && lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts && (jetMetTool.passNPVCuts == 1)) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_EMu_OR_NPVHIGH, "HLT_EMu_OR_NPVHIGH", p_passFile.c_str(),false,false);
                if ((lepTool.passSLtriggers_el || lepTool.passSLtriggers_mu || lepTool.passDLtriggers_emu) && lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts && (jetMetTool.passNPVCuts == 1) && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_EMu_OR__X__allMET_NPVHIGH, "EMu_OR__X__allMET_NPVHIGH", p_passFile.c_str(),false,false);
                // II. using logical OR of SL and DL triggers
                //NPV low region
                // dilepton, ee
                if ((lepTool.passSLtriggers_el || lepTool.passDLtriggers_el) && lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts && (jetMetTool.passNPVCuts == 0) ) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_DoubleEl_OR_NPVLOW, "HLT_DoubleEl_OR_NPVLOW", p_passFile.c_str(),false,false);
                if ((lepTool.passSLtriggers_el || lepTool.passDLtriggers_el) && lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts && (jetMetTool.passNPVCuts == 0) && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_DoubleEl_OR__X__allMET_NPVLOW, "DoubleEl_OR__X__allMET_NPVLOW", p_passFile.c_str(),false,false);
                // dilepton, mumu
                if ((lepTool.passSLtriggers_mu || lepTool.passDLtriggers_mu) && lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts && (jetMetTool.passNPVCuts == 0) ) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_DoubleMu_OR_NPVLOW, "HLT_DoubleMu_OR_NPVLOW", p_passFile.c_str(),false,false);
                if ((lepTool.passSLtriggers_mu || lepTool.passDLtriggers_mu) && lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts && (jetMetTool.passNPVCuts == 0) && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_DoubleMu_OR__X__allMET_NPVLOW, "DoubleMu_OR__X__allMET_NPVLOW", p_passFile.c_str(),false,false);
                // dilepton, emu
                if ((lepTool.passSLtriggers_el || lepTool.passSLtriggers_mu || lepTool.passDLtriggers_emu) && lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts && (jetMetTool.passNPVCuts == 0)) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_EMu_OR_NPVLOW, "HLT_EMu_OR_NPVLOW", p_passFile.c_str(),false,false);
                if ((lepTool.passSLtriggers_el || lepTool.passSLtriggers_mu || lepTool.passDLtriggers_emu) && lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts && (jetMetTool.passNPVCuts == 0) && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_EMu_OR__X__allMET_NPVLOW, "EMu_OR__X__allMET_NPVLOW", p_passFile.c_str(),false,false);


                // II. using logical OR of SL and DL triggers
                //MET high region
                // dilepton, ee
                if ((lepTool.passSLtriggers_el || lepTool.passDLtriggers_el) && lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts && ( jetMetTool.passMETCuts == 1) ) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_DoubleEl_OR_METHIGH, "HLT_DoubleEl_OR_METHIGH", p_passFile.c_str(),false,false);
                if ((lepTool.passSLtriggers_el || lepTool.passDLtriggers_el) && lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts && ( jetMetTool.passMETCuts == 1) && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_DoubleEl_OR__X__allMET_METHIGH, "DoubleEl_OR__X__allMET_METHIGH", p_passFile.c_str(),false,false);
                // dilepton, mumu
                if ((lepTool.passSLtriggers_mu || lepTool.passDLtriggers_mu) && lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts && ( jetMetTool.passMETCuts == 1)) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_DoubleMu_OR_METHIGH, "HLT_DoubleMu_OR_METHIGH", p_passFile.c_str(),false,false);
                if ((lepTool.passSLtriggers_mu || lepTool.passDLtriggers_mu) && lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts && ( jetMetTool.passMETCuts == 1) && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_DoubleMu_OR__X__allMET_METHIGH, "DoubleMu_OR__X__allMET_METHIGH", p_passFile.c_str(),false,false);
                // dilepton, emu
                if ((lepTool.passSLtriggers_el || lepTool.passSLtriggers_mu || lepTool.passDLtriggers_emu) && lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts && ( jetMetTool.passMETCuts == 1)) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_EMu_OR_METHIGH, "HLT_EMu_OR_METHIGH", p_passFile.c_str(),false,false);
                if ((lepTool.passSLtriggers_el || lepTool.passSLtriggers_mu || lepTool.passDLtriggers_emu) && lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts && ( jetMetTool.passMETCuts == 1) && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_EMu_OR__X__allMET_METHIGH, "EMu_OR__X__allMET_METHIGH", p_passFile.c_str(),false,false);
                // II. using logical OR of SL and DL triggers
                //MET low region
                // dilepton, ee
                if ((lepTool.passSLtriggers_el || lepTool.passDLtriggers_el) && lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts && ( jetMetTool.passMETCuts == 0) ) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_DoubleEl_OR_METLOW, "HLT_DoubleEl_OR_METLOW", p_passFile.c_str(),false,false);
                if ((lepTool.passSLtriggers_el || lepTool.passDLtriggers_el) && lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts && ( jetMetTool.passMETCuts == 0) && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_DoubleEl_OR__X__allMET_METLOW, "DoubleEl_OR__X__allMET_METLOW", p_passFile.c_str(),false,false);
                // dilepton, mumu
                if ((lepTool.passSLtriggers_mu || lepTool.passDLtriggers_mu) && lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts && ( jetMetTool.passMETCuts == 0)) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_DoubleMu_OR_METLOW, "HLT_DoubleMu_OR_METLOW", p_passFile.c_str(),false,false);
                if ((lepTool.passSLtriggers_mu || lepTool.passDLtriggers_mu) && lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts && ( jetMetTool.passMETCuts == 0) && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_DoubleMu_OR__X__allMET_METLOW, "DoubleMu_OR__X__allMET_METLOW", p_passFile.c_str(),false,false);
                // dilepton, emu
                if ((lepTool.passSLtriggers_el || lepTool.passSLtriggers_mu || lepTool.passDLtriggers_emu) && lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts && ( jetMetTool.passMETCuts == 0)) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_EMu_OR_METLOW, "HLT_EMu_OR_METLOW", p_passFile.c_str(),false,false);
                if ((lepTool.passSLtriggers_el || lepTool.passSLtriggers_mu || lepTool.passDLtriggers_emu) && lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts && ( jetMetTool.passMETCuts == 0) && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_EMu_OR__X__allMET_METLOW, "EMu_OR__X__allMET_METLOW", p_passFile.c_str(),false,false);



				// II. using logical OR of SL and DL triggers
                //Number of Muon = 2
				// std::cout<<"passMultiMuons:"<<lepTool.passMultiMuons<<endl;
                // dilepton, ee
                if ((lepTool.passSLtriggers_el || lepTool.passDLtriggers_el) && (lepTool.passMultiMuons == 2) && lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts  ) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_DoubleEl_OR_NMu2, "HLT_DoubleEl_OR_NMu2", p_passFile.c_str(),false,false);
                if ((lepTool.passSLtriggers_el || lepTool.passDLtriggers_el) && (lepTool.passMultiMuons == 2) && lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts  && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_DoubleEl_OR__X__allMET_NMu2, "DoubleEl_OR__X__allMET_NMu2", p_passFile.c_str(),false,false);
                // dilepton, mumu
                if ((lepTool.passSLtriggers_mu || lepTool.passDLtriggers_mu) && (lepTool.passMultiMuons == 2) && lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts ) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_DoubleMu_OR_NMu2, "HLT_DoubleMu_OR_NMu2", p_passFile.c_str(),false,false);
                if ((lepTool.passSLtriggers_mu || lepTool.passDLtriggers_mu) && (lepTool.passMultiMuons == 2) && lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts  && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_DoubleMu_OR__X__allMET_NMu2, "DoubleMu_OR__X__allMET_NMu2", p_passFile.c_str(),false,false);
                // dilepton, emu
                if ((lepTool.passSLtriggers_el || lepTool.passSLtriggers_mu || lepTool.passDLtriggers_emu) && (lepTool.passMultiMuons == 2) && lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts ) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_EMu_OR_NMu2, "HLT_EMu_OR_NMu2", p_passFile.c_str(),false,false);
                if ((lepTool.passSLtriggers_el || lepTool.passSLtriggers_mu || lepTool.passDLtriggers_emu) && (lepTool.passMultiMuons == 2) && lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts  && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_EMu_OR__X__allMET_NMu2, "EMu_OR__X__allMET_NMu2", p_passFile.c_str(),false,false);

				//Number of Muon = 3
				// std::cout<<"passMultiMuons:"<<lepTool.passMultiMuons<<endl;
                // dilepton, ee
                if ((lepTool.passSLtriggers_el || lepTool.passDLtriggers_el) && (lepTool.passMultiMuons == 2) && lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts  ) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_DoubleEl_OR_NMu3, "HLT_DoubleEl_OR_NMu3", p_passFile.c_str(),false,false);
                if ((lepTool.passSLtriggers_el || lepTool.passDLtriggers_el) && (lepTool.passMultiMuons == 2) && lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts  && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_DoubleEl_OR__X__allMET_NMu3, "DoubleEl_OR__X__allMET_NMu3", p_passFile.c_str(),false,false);
                // dilepton, mumu
                if ((lepTool.passSLtriggers_mu || lepTool.passDLtriggers_mu) && (lepTool.passMultiMuons == 2) && lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts ) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_DoubleMu_OR_NMu3, "HLT_DoubleMu_OR_NMu3", p_passFile.c_str(),false,false);
                if ((lepTool.passSLtriggers_mu || lepTool.passDLtriggers_mu) && (lepTool.passMultiMuons == 2) && lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts  && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_DoubleMu_OR__X__allMET_NMu3, "DoubleMu_OR__X__allMET_NMu3", p_passFile.c_str(),false,false);
                // dilepton, emu
                if ((lepTool.passSLtriggers_el || lepTool.passSLtriggers_mu || lepTool.passDLtriggers_emu) && (lepTool.passMultiMuons == 2) && lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts ) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_EMu_OR_NMu3, "HLT_EMu_OR_NMu3", p_passFile.c_str(),false,false);
                if ((lepTool.passSLtriggers_el || lepTool.passSLtriggers_mu || lepTool.passDLtriggers_emu) && (lepTool.passMultiMuons == 2) && lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts  && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_EMu_OR__X__allMET_NMu3, "EMu_OR__X__allMET_NMu3", p_passFile.c_str(),false,false);
 
 				//Number of Muon = 4
				// std::cout<<"passMultiMuons:"<<lepTool.passMultiMuons<<endl;
                // dilepton, ee
                if ((lepTool.passSLtriggers_el || lepTool.passDLtriggers_el) && (lepTool.passMultiMuons == 2) && lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts  ) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_DoubleEl_OR_NMu4, "HLT_DoubleEl_OR_NMu4", p_passFile.c_str(),false,false);
                if ((lepTool.passSLtriggers_el || lepTool.passDLtriggers_el) && (lepTool.passMultiMuons == 2) && lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts  && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_DoubleEl_OR__X__allMET_NMu4, "DoubleEl_OR__X__allMET_NMu4", p_passFile.c_str(),false,false);
                // dilepton, mumu
                if ((lepTool.passSLtriggers_mu || lepTool.passDLtriggers_mu) && (lepTool.passMultiMuons == 2) && lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts ) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_DoubleMu_OR_NMu4, "HLT_DoubleMu_OR_NMu4", p_passFile.c_str(),false,false);
                if ((lepTool.passSLtriggers_mu || lepTool.passDLtriggers_mu) && (lepTool.passMultiMuons == 2) && lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts  && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_DoubleMu_OR__X__allMET_NMu4, "DoubleMu_OR__X__allMET_NMu4", p_passFile.c_str(),false,false);
                // dilepton, emu
                if ((lepTool.passSLtriggers_el || lepTool.passSLtriggers_mu || lepTool.passDLtriggers_emu) && (lepTool.passMultiMuons == 2) && lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts ) fillEfficiencyHistograms(lepTool, jetMetTool, a_HLT_EMu_OR_NMu4, "HLT_EMu_OR_NMu4", p_passFile.c_str(),false,false);
                if ((lepTool.passSLtriggers_el || lepTool.passSLtriggers_mu || lepTool.passDLtriggers_emu) && (lepTool.passMultiMuons == 2) && lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts  && jetMetTool.passAllMETTriggers) fillEfficiencyHistograms(lepTool, jetMetTool, a_EMu_OR__X__allMET_NMu4, "EMu_OR__X__allMET_NMu4", p_passFile.c_str(),false,false);
 




		//CONTADORES, IGNORAR ESSA PARTES, SERVE SOMENTE PARA COMPARAÇÂO DE NUMERO DE ENTRADAS
		if ( jetMetTool.passAllMETTriggers){counter++;}
		if ((lepTool.passSLtriggers_el || lepTool.passDLtriggers_el) && lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts){counter_2++;}
		if ((lepTool.passSLtriggers_mu || lepTool.passDLtriggers_mu) && lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts){counter_3++;}
		if ((lepTool.passSLtriggers_el || lepTool.passSLtriggers_mu || lepTool.passDLtriggers_emu) && lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts){counter_4++;}
		if ((lepTool.passSLtriggers_el || lepTool.passDLtriggers_el) && lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts && jetMetTool.passAllMETTriggers){counter_5++;}
		if ((lepTool.passSLtriggers_mu || lepTool.passDLtriggers_mu) && lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts && jetMetTool.passAllMETTriggers){counter_6++;}
		if ((lepTool.passSLtriggers_el || lepTool.passSLtriggers_mu || lepTool.passDLtriggers_emu) && lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts && jetMetTool.passAllMETTriggers){counter_7++;}
	
		if (lepTool.passDLCuts_el && jetMetTool.passDLJetMetCuts){counter_8++;}
		if (lepTool.passDLCuts_mu && jetMetTool.passDLJetMetCuts){counter_9++;}
		if (lepTool.passDLCuts_emu && jetMetTool.passDLJetMetCuts){counter_10++;}
	
	}



	printProgBar(100);

  	cout<<"Eventos que ativaram 1 trigger de MET = "<<counter<<endl;
	cout<<"Eventos do canal ElEl = "<<counter_8<<endl;
  	cout<<"Eventos do canal ElEl que ativaram 1 trigger de LEP = "<<counter_2<<endl;
	cout<<"Eventos do canal ElEl que ativaram 1 trigger de LEP e de MET = "<<counter_5<<endl;
	cout<<"Eventos do canal MuMu = "<<counter_9<<endl;
	cout<<"Eventos do canal MuMu que ativaram 1 trigger de LEP = "<<counter_3<<endl;
	cout<<"Eventos do canal MuMu que ativaram 1 trigger de LEP e de MET = "<<counter_6<<endl;
	cout<<"Eventos do canal ElMu = "<<counter_10<<endl;
	cout<<"Eventos do canal ElMu que ativaram 1 trigger de LEP = "<<counter_4<<endl;
	cout<<"Eventos do canal ElMu que ativaram 1 trigger de LEP e de MET = "<<counter_7<<endl;

	  

   	// *** 4. Make plots
  	if( dumpFile) outfile->cd();

  	// plot1Dand2DHistograms( a_HLT_DoubleEl_OR, c0, "HLT_DoubleEl_OR");       //Só serve pra criar e salvar os histogramas la na pasta MC/HLTDoubleEl_OR (desativado pelo "printPlots")
  	// plot1Dand2DHistograms( a_HLT_DoubleMu_OR, c0, "HLT_DoubleMu_OR");		//Só serve pra criar e salvar os histogramas la nas pastas MC/HLTDoubleMu_OR (desativado pelo "printPlots")
  	// plot1Dand2DHistograms( a_HLT_EMu_OR, c0, "HLT_EMu_OR");					//Só serve pra criar e salvar os histogramas la nas pastas MC/EMu_OR (desativado pelo "printPlots")

	// plot1Dand2DHistograms( a_DoubleEl_OR__X__allMET, c0, "DoubleEl_OR__X__allMET");
	// plot1Dand2DHistograms( a_DoubleMu_OR__X__allMET, c0, "DoubleMu_OR__X__allMET");
	// plot1Dand2DHistograms(a_HLT_allMET,c0,"HLT_allMET_muStreamDL");
	// plot1Dand2DHistograms(a_HLT_allMET,c0,"HLT_allMET_elStreamDL");
 	// // ** C. 1D efficiencies

	makeEfficiencyHistograms( c0, a_DoubleMu_OR__X__allMET, "DoubleMu_OR__X__allMET", a_HLT_allMET, "HLT_allMET_muStreamDL");
	makeEfficiencyHistograms( c0, a_DoubleEl_OR__X__allMET, "DoubleEl_OR__X__allMET", a_HLT_allMET, "HLT_allMET_elStreamDL");
	makeEfficiencyHistograms( c0, a_EMu_OR__X__allMET, "EMu_OR__X__allMET", a_HLT_allMET, "HLT_allMET_emuStreamDL");

    makeEfficiencyHistograms( c0, a_DoubleMu_OR__X__allMET_NJETSHIGH, "DoubleMu_OR__X__allMET_NJETSHIGH", a_HLT_allMET, "HLT_allMET_muStreamDL_njetshigh");
    makeEfficiencyHistograms( c0, a_DoubleEl_OR__X__allMET_NJETSHIGH, "DoubleEl_OR__X__allMET_NJETSHIGH", a_HLT_allMET, "HLT_allMET_elStreamDL_njetshigh");
    makeEfficiencyHistograms( c0, a_EMu_OR__X__allMET_NJETSHIGH, "EMu_OR__X__allMET_NJETSHIGH", a_HLT_allMET, "HLT_allMET_emuStreamDL_njetshigh");
    makeEfficiencyHistograms( c0, a_DoubleMu_OR__X__allMET_NJETSLOW, "DoubleMu_OR__X__allMET_NJETSLOW", a_HLT_allMET, "HLT_allMET_muStreamDL_njetslow");
    makeEfficiencyHistograms( c0, a_DoubleEl_OR__X__allMET_NJETSLOW, "DoubleEl_OR__X__allMET_NJETSLOW", a_HLT_allMET, "HLT_allMET_elStreamDL_njetslow");
    makeEfficiencyHistograms( c0, a_EMu_OR__X__allMET_NJETSLOW, "EMu_OR__X__allMET_NJETSLOW", a_HLT_allMET, "HLT_allMET_emuStreamDL_njetslow");

    makeEfficiencyHistograms( c0, a_DoubleMu_OR__X__allMET_NPVHIGH, "DoubleMu_OR__X__allMET_NPVHIGH", a_HLT_allMET, "HLT_allMET_muStreamDL_npvhigh");
    makeEfficiencyHistograms( c0, a_DoubleEl_OR__X__allMET_NPVHIGH, "DoubleEl_OR__X__allMET_NPVHIGH", a_HLT_allMET, "HLT_allMET_elStreamDL_npvhigh");
    makeEfficiencyHistograms( c0, a_EMu_OR__X__allMET_NPVHIGH, "EMu_OR__X__allMET_NPVHIGH", a_HLT_allMET, "HLT_allMET_emuStreamDL_npvhigh");
    makeEfficiencyHistograms( c0, a_DoubleMu_OR__X__allMET_NPVLOW, "DoubleMu_OR__X__allMET_NPVLOW", a_HLT_allMET, "HLT_allMET_muStreamDL_npvlow");
    makeEfficiencyHistograms( c0, a_DoubleEl_OR__X__allMET_NPVLOW, "DoubleEl_OR__X__allMET_NPVLOW", a_HLT_allMET, "HLT_allMET_elStreamDL_npvlow");
    makeEfficiencyHistograms( c0, a_EMu_OR__X__allMET_NPVLOW, "EMu_OR__X__allMET_NPVLOW", a_HLT_allMET, "HLT_allMET_emuStreamDL_npvlow");

    makeEfficiencyHistograms( c0, a_DoubleMu_OR__X__allMET_METHIGH, "DoubleMu_OR__X__allMET_METHIGH", a_HLT_allMET, "HLT_allMET_muStreamDL_methigh");
    makeEfficiencyHistograms( c0, a_DoubleEl_OR__X__allMET_METHIGH, "DoubleEl_OR__X__allMET_METHIGH", a_HLT_allMET, "HLT_allMET_elStreamDL_methigh");
    makeEfficiencyHistograms( c0, a_EMu_OR__X__allMET_METHIGH, "EMu_OR__X__allMET_METHIGH", a_HLT_allMET, "HLT_allMET_emuStreamDL_methigh");
    makeEfficiencyHistograms( c0, a_DoubleMu_OR__X__allMET_METLOW, "DoubleMu_OR__X__allMET_METLOW", a_HLT_allMET, "HLT_allMET_muStreamDL_metlow");
    makeEfficiencyHistograms( c0, a_DoubleEl_OR__X__allMET_METLOW, "DoubleEl_OR__X__allMET_METLOW", a_HLT_allMET, "HLT_allMET_elStreamDL_metlow");
    makeEfficiencyHistograms( c0, a_EMu_OR__X__allMET_METLOW, "EMu_OR__X__allMET_METLOW", a_HLT_allMET, "HLT_allMET_emuStreamDL_metlow");

	//Add new regions N muon = 2
	makeEfficiencyHistograms( c0, a_DoubleMu_OR__X__allMET_NMu2, "DoubleMu_OR__X__allMET_NMu2", a_HLT_allMET, "HLT_allMET_muStreamDL_NMu2");
    makeEfficiencyHistograms( c0, a_DoubleEl_OR__X__allMET_NMu2, "DoubleEl_OR__X__allMET_NMu2", a_HLT_allMET, "HLT_allMET_elStreamDL_NMu2");
    makeEfficiencyHistograms( c0, a_EMu_OR__X__allMET_NMu2, "EMu_OR__X__allMET_NMu2", a_HLT_allMET, "HLT_allMET_emuStreamDL_NMu2");

	//Add new regions N muon = 3
	makeEfficiencyHistograms( c0, a_DoubleMu_OR__X__allMET_NMu3, "DoubleMu_OR__X__allMET_NMu3", a_HLT_allMET, "HLT_allMET_muStreamDL_NMu3");
    makeEfficiencyHistograms( c0, a_DoubleEl_OR__X__allMET_NMu3, "DoubleEl_OR__X__allMET_NMu3", a_HLT_allMET, "HLT_allMET_elStreamDL_NMu3");
    makeEfficiencyHistograms( c0, a_EMu_OR__X__allMET_NMu3, "EMu_OR__X__allMET_NMu3", a_HLT_allMET, "HLT_allMET_emuStreamDL_NMu3");

	//Add new regions N muon = 4
	makeEfficiencyHistograms( c0, a_DoubleMu_OR__X__allMET_NMu4, "DoubleMu_OR__X__allMET_NMu4", a_HLT_allMET, "HLT_allMET_muStreamDL_NMu4");
    makeEfficiencyHistograms( c0, a_DoubleEl_OR__X__allMET_NMu4, "DoubleEl_OR__X__allMET_NMu4", a_HLT_allMET, "HLT_allMET_elStreamDL_NMu4");
    makeEfficiencyHistograms( c0, a_EMu_OR__X__allMET_NMu4, "EMu_OR__X__allMET_NMu4", a_HLT_allMET, "HLT_allMET_emuStreamDL_NMu4");

	if (dumpFile){
    		outfile->Write();
		    outfile->cd();
    		TIter next(a_Efficiencies);
    		while ( TEfficiency *tEff = (TEfficiency*)next() )
      		tEff->Write();
  	}

	// delete c0;

  	return;
}


void printProgBar(const  int& progress )
{
	std::string progressBar = "[";
    for(int i = 0; i <= progress; i++){
        if(i%1 == 0) progressBar += "#";
    }
    for(int i = 0; i < 100 - progress; i++){
        if(i%1 == 0) progressBar += " ";
    }
    progressBar = progressBar + "] " + std::to_string(progress) + "% of Events processed";
    std::cout << "\r" << progressBar << std::flush;
    if(progress == 100) std::cout << std::endl;
}
