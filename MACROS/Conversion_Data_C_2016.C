{
#include<math.h>
#include<TMath.h>
#include <TLorentzVector.h>
#include <TChain.h>
#include<fstream>
#include<TTree.h>
#include<TFile.h>
#include <iostream>
#include <fstream>
#include "TSystem.h"
#include "../include/EventVars.h"



//Tentando pegar informação dos arquivos nas pastas do TTTo2L2Nu_16_?_?, onde ? varia de 0 a 100
//void list_files(const char *dirname="/home/matheus/Desktop/TChain/TTTo2L2Nu_16_files", const char *ext="Tree.root") // https://root-forum.cern.ch/t/open-files-in-a-directory-with-a-for-loop/12471
//void list_files(TChain *ch1,const char *dirname="/home/matheus/Desktop/TChain/TTTo2L2Nu_16_files", const char *ext="Tree.root")
void list_files(vector<int> *ch1,const char *dirname,double & DATA_LUMI,double & DATA_LUMI_UNC, double &PROC_XSEC, double & SUM_GEN_WGT, const char *ext="Tree.root")
{
	int n = 9999;
    for(int i=0;i<n;i++){
        const char *d = "/home/matheus/cernbox/HHDM/DESY/";
	   	std::string str = dirname;   												//Pego o nome do dirname
		std::string str_2;          												//Declaro uma string que vai ser usada como argumento do TSystemDirectory dir
		char numstr[20];															//Declaro o char que vai pegar o indice do _0_0,1_1 e etc.
	    sprintf (numstr,"_%d_%d/",i,i);												//Preencho ele com esse valor
		str_2 = str+numstr;															//Crio a nova string que vai ser usada.
		//cout<<"Diretorio que está entrando: "<<str_2<<endl;
		const char *c = str_2.c_str();   											//Transformo ela em um const Char para que passa ser usada no TSystemDirectory dir
	 	TSystemDirectory dir(c, c);
   		TList *files = dir.GetListOfFiles();
   		if (files) {
    		  TSystemFile *file;
   		  	  TString fname;
   		   	  TIter next(files);
   		   	  while ((file=(TSystemFile*)next())) {
   		      	fname = file->GetName();
   		      	if (!file->IsDirectory() && fname.EndsWith(ext)) {
   		        	//cout << fname.Data() << endl;
					gSystem->cd(c);
					//SABER SE UM ARQUIVO.ROOT esta corrompido https://root.cern/manual/storing_root_objects/
					TFile f("Tree.root");
   					if (f.IsZombie() || f.GetNkeys() == 0 ) {      					//Se o file.root não tiver keys (não foi salvo corretamente) então não salve o diretorio. https://root-forum.cern.ch/t/checking-for-file-with-no-keys/1005   
						cout<<"Arquivo "<<c<<"Tree.root falhou!"<<endl;					
      					//exit(-1);
      				} 
                    else {     
						//ch1.Add("Tree.root");
                        ch1->push_back(i);
						f.Close();
                        FILE *file;
                        file = fopen("cutflow.txt","r");

                        if(file == NULL){
                            printf("Gilson ou você fez besteira! O arquivo root não teve cutflow!");
                        }
                        float Luminosidade = 0;
                        char frase[500];
                        int contador = 0;
                        while (fgets(frase,500,file) != NULL){
                            if ( (7<contador) & (contador< 12) ){
                                //DATA_LUMI
                                if (contador == 8){
                                    int len = strlen(frase); //só pra dar melhor performance
                                    frase[strlen(frase) - 7] = '\0';
                                    int posicao = 12; //lumminosity tem 10 caracteries  
                                    int final = sizeof(frase) - posicao;
                                    char parte[final];
                                    memcpy(parte, &frase[posicao], final);
                                    //printf("%s \n",parte);
                                    DATA_LUMI =  strtod(parte,NULL);
                                    //std::cout<<"luminosidade: "<<luminosidade<<endl;
                                    //printf("%s \n",frase);  
                                }
                                //PROC_XSEC
                                if (contador == 9){
                                    int len = strlen(frase); //só pra dar melhor performance
                                    frase[strlen(frase) - 3] = '\0';
                                    int posicao = 19; //lumminosity tem 10 caracteries  
                                    int final = sizeof(frase) - posicao;
                                    char parte[final];
                                    memcpy(parte, &frase[posicao], final);
                                    //printf("%s \n",parte);
                                    DATA_LUMI_UNC =  strtod(parte,NULL);
                                    //std::cout<<"lumi. Uncertainty:  "<<lumi_uncer<<endl;
                                    //printf("%s \n",frase);  
                                }
                                //PROC_XSEC
                                if (contador == 10){
                                    int len = strlen(frase); //só pra dar melhor performance
                                    frase[strlen(frase) - 4] = '\0';
                                    int posicao = 15; //lumminosity tem 10 caracteries  
                                    int final = sizeof(frase) - posicao;
                                    char parte[final];
                                    memcpy(parte, &frase[posicao], final);
                                    //printf("%s \n",parte);
                                    PROC_XSEC =  strtod(parte,NULL);
                                    //std::cout<<"Cross Section:  "<<cross_sec<<endl;
                                    //printf("%s \n",frase);  
                                }
                                if (contador ==11){
                                    int len = strlen(frase); //só pra dar melhor performance
                                    frase[strlen(frase) - 1] = '\0';
                                    int posicao = 19; //lumminosity tem 10 caracteries  
                                    int final = sizeof(frase) - posicao;
                                    char parte[final];
                                    memcpy(parte, &frase[posicao], final);
                                    //printf("%s \n",parte);
                                    double sum_weight =  strtod(parte,NULL);
                                    SUM_GEN_WGT += sum_weight;
                                    //printf("Printf: valor transformado em double %f \n",sum_weight);
                                    // double d_sum_weight = sum_weight*sum_weight;
                                    // std::cout<<"Valor do sum_weight puxado direto:  "<<sum_weight<<endl;
                                    // std::cout<<"valor da mutiplicação do sum_weight  "<<sum_weight*sum_weight<<endl;
                                    // printf("Printf: valor da mutiplicação em double %f \n",sum_weight*sum_weight);
                                    // printf("Printf: valor da mutiplicação em double da nova variavel %f \n",d_sum_weight);
                                    //std::cout<<"sum_weight: \n  "<<sum_weight<<endl;
                                    //std::cout<<"Sum Weight*: \n "<<sum_weight*sum_weight<<endl;
                                    //printf("%s \n",frase);  
                                }
                                //printf("%s",frase);
                            }
                            contador = contador +1;
                        }
                        fclose(file);
						//cout <<c<<"Tree.root não falhou!"<<endl;
   					}
		        }
    		}
   		}
    }
}

    double DATA_LUMI = 0;
    double DATA_LUMI_UNC = 0;
    double PROC_XSEC = 0;
    double SUM_GEN_WGT = 0;
    vector<int> index;
    //const char dirname[75] = "/home/matheus/Desktop/TChain/TTTo2L2Nu_16_files";
    const char dirname[75] = "/home/matheus/cernbox/HHDM/DESY/Data_MET_C_16_files";
    //const char dirname[75] = "/home/matheus/Desktop/TChain/Data_MET_G_16_files";
    //const char dirname[75] = "/home/matheus/Desktop/TChain/Data_MET_H_16_files";
    
    TChain ch1("selection"); 												   //Crio um Tchain chamado ch1, por onde vou adcionar todas as outras trees, usando o list_files
    list_files(&index,dirname,DATA_LUMI,DATA_LUMI_UNC,PROC_XSEC,SUM_GEN_WGT);														   //Pego os 100 tree.root separados entre as pastas e junto eles aqui na minha Tchain.

    double ajuste_no_peso = (PROC_XSEC/SUM_GEN_WGT) * DATA_LUMI; 
    std::cout<<"Ajuste que deve ser aplicado no evtweight dessa amostra: "<<ajuste_no_peso<<endl;
    std::cout<<index.size()<<endl;

    std::string str = dirname;
    std::string str_2;
    for(int i = 0;i<index.size();i++){
        //char numstr[40];
        int  u = index.at(i);	
        // std::cout<<"oi"<<endl;														//Declaro o char que vai pegar o indice do _0_0,1_1 e etc.
        char numstr[20];
        sprintf (numstr,"_%d_%d/Tree.root",u,u);
        str_2 = str+numstr;
        //str_2 = 
        //sprintf (numstr,"/home/matheus/Desktop/TChain/TTTo2L2Nu_16_files_%d_%d/",u,u);												//Preencho ele com esse valor
	    // str_2 = numstr;
        ch1.Add(str_2.c_str());

    
}






//TFile *newfile= new TFile("/home/matheus/Desktop/TChain/MCttbar.root","recreate");                      //Crio um Arquivo com nome MCttbar
TFile *newfile= new TFile("/home/matheus/Desktop/tt-triggerEfficiency-DL/datasets/2016/Run2016C.root","recreate");                      //Crio um Arquivo com nome Data_F
//TFile *newfile= new TFile("/home/matheus/Desktop/TChain/Data_G.root","recreate");                      //Crio um Arquivo com nome Data_G
//TFile *newfile= new TFile("/home/matheus/Desktop/TChain/Data_H.root","recreate");                      //Crio um Arquivo com nome Data_H
// TDirectory* cdttTreeMaker=newfile->mkdir("ttTreeMaker");				   //Crio uma pasta dentro dele chamada "ttTreeMaker"
// cdttTreeMaker->cd();													   //Entro dentro da pasta dele
TTree *convertedTree = new TTree("convertedTree","convertedTree");		   //Crio uma tree dentro dele chamado convertedTree 
//TBranch *my_new_branch = convertedTree->AddBranch("events");
 EventVars *eve;														   //Declaro o objeto eve, uma vez que não quero ter que escrever cada objeto na mão
 eve=0;																	   //???????????????????????????????/
 //Event *events = new Event();
 convertedTree->Branch("events", &eve);			                           //Criando um branch chamado "events", onde nele se encontra as variaveis, OBRIGATORIO O USO DE DICIONARIO https://root.cern/doc/v610/tree4_8C_source.html
//bool HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
//convertedTree->Branch("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ",&HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ,"HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ/B");

//convertedTree->Branch("events", "HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ, 8000, 1);			   //Criando um branch chamado "events", onde nele se encontra as variaveis



  // Declaration of leaf types
   Double_t        evtWeight;
   Double_t        Lep_leading_pt;
   Double_t        Lep_leading_eta;
   Double_t        Lep_subleading_pt;
   Double_t        Lep_subleading_eta;
   Bool_t          Lep_triggers;
   Bool_t          Met_triggers;
   Int_t           RecoLepID;
   Int_t           Njets;
   Bool_t          HLT_IsoMu24;
   Bool_t          HLT_IsoTkMu24;
   Bool_t          HLT_Mu50;
   Bool_t          HLT_IsoMu27;
   Bool_t          HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ;
   Bool_t          HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ;
   Bool_t          HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL;
   Bool_t          HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL;
   Bool_t          HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8;
   Bool_t          HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8;
   Bool_t          HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ;
   Bool_t          HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
   Bool_t          HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL;
   Bool_t          HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL;
   Bool_t          HLT_Ele27_WPTight_Gsf;
   Bool_t          HLT_Ele115_CaloIdVT_GsfTrkIdT;
   Bool_t          HLT_Ele32_WPTight_Gsf;
   Bool_t          HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;
   Bool_t          HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL;
   Bool_t          HLT_DoubleEle33_CaloIdL_MW;
   Bool_t          HLT_PFMET300;
   Bool_t          HLT_MET200;
   Bool_t          HLT_PFHT300_PFMET110;
   Bool_t          HLT_PFMET170_HBHECleaned;
   Bool_t          HLT_PFMET120_PFMHT120_IDTight;
   Bool_t          HLT_PFMETNoMu120_PFMHTNoMu120_IDTight;
   Bool_t          HLT_PFMET200_HBHECleaned;
   Bool_t          HLT_PFMET200_HBHE_BeamHaloCleaned;
   Bool_t          HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned;
   Bool_t          HLT_PFMET120_PFMHT120_IDTight_PFHT60;
   Bool_t          HLT_PFHT500_PFMET100_PFMHT100_IDTight;
   Bool_t          HLT_PFHT700_PFMET85_PFMHT85_IDTight;
   Bool_t          HLT_PFHT800_PFMET75_PFMHT75_IDTight;
   Bool_t          HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60;
   UInt_t          run_;
   UInt_t          lumi_;
   ULong64_t       evt_;
   Int_t           numPVs_;
   Float_t         puSF_;
   Bool_t          PassMETFilters_;
   Bool_t          GoodFirstPV_;
   Float_t         genWeight_;
   vector<float>   *jet_pt_;
   vector<float>   *jet_eta_;
   vector<float>   *jet_phi_;
   vector<float>   *jet_m_;
   vector<float>   *jet_regFactor;
   vector<float>   *lepton_pt_;
   vector<float>   *lepton_eta_;
   vector<float>   *lepton_phi_;
   vector<int>     *lepton_e_;
   vector<float>   *lepton_scEta_;
   vector<int>     *lepton_isMuon_;
   vector<int>     *lepton_isTight_;
   vector<int>     *lepton_charge_;
   vector<float>   *lepton_relIso;
   vector<float>   *lepton_IDSF_;
   vector<float>   *lepton_recoIsoSF_;
   vector<float>   *lepton_energyCorr_;
   Float_t         MET_;
   Float_t         MET_phi_;
   Float_t         MET_Type1xy_;
   Float_t         MET_Type1xy_phi_;
   Float_t         MET_Type1xy_sync_;
   Float_t         MET_Type1xy_phi_sync_;
   vector<float>   *lepton_mu0_pt;
   vector<float>   *lepton_mu0_eta;
   vector<float>   *lepton_mu1_pt;
   vector<float>   *lepton_mu1_eta;
   vector<float>   *lepton_el0_pt;
   vector<float>   *lepton_el0_eta;
   vector<float>   *lepton_el1_pt;
   vector<float>   *lepton_el1_eta;




   ch1.SetBranchAddress("evtWeight", &evtWeight);
   ch1.SetBranchAddress("Lep_leading_pt", &Lep_leading_pt);
   ch1.SetBranchAddress("Lep_leading_eta", &Lep_leading_eta);
   ch1.SetBranchAddress("Lep_subleading_pt", &Lep_subleading_pt);
   ch1.SetBranchAddress("Lep_subleading_eta", &Lep_subleading_eta);
   ch1.SetBranchAddress("Lep_triggers", &Lep_triggers);
   ch1.SetBranchAddress("Met_triggers", &Met_triggers);
   ch1.SetBranchAddress("RecoLepID", &RecoLepID);
   ch1.SetBranchAddress("Njets", &Njets);
   ch1.SetBranchAddress("HLT_IsoMu24", &HLT_IsoMu24);
   ch1.SetBranchAddress("HLT_IsoTkMu24", &HLT_IsoTkMu24);
   ch1.SetBranchAddress("HLT_Mu50", &HLT_Mu50);
   ch1.SetBranchAddress("HLT_IsoMu27", &HLT_IsoMu27);
   ch1.SetBranchAddress("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ);
   ch1.SetBranchAddress("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ", &HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ);
   ch1.SetBranchAddress("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL);
   ch1.SetBranchAddress("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL", &HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL);
   ch1.SetBranchAddress("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8);
   ch1.SetBranchAddress("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8);
   ch1.SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ);
   ch1.SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);
   ch1.SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL);
   ch1.SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL);
   ch1.SetBranchAddress("HLT_Ele27_WPTight_Gsf", &HLT_Ele27_WPTight_Gsf);
   ch1.SetBranchAddress("HLT_Ele115_CaloIdVT_GsfTrkIdT", &HLT_Ele115_CaloIdVT_GsfTrkIdT);
   ch1.SetBranchAddress("HLT_Ele32_WPTight_Gsf", &HLT_Ele32_WPTight_Gsf);
   ch1.SetBranchAddress("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ", &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ);
   ch1.SetBranchAddress("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL", &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL);
   ch1.SetBranchAddress("HLT_DoubleEle33_CaloIdL_MW", &HLT_DoubleEle33_CaloIdL_MW);
   ch1.SetBranchAddress("HLT_PFMET300", &HLT_PFMET300);
   ch1.SetBranchAddress("HLT_MET200", &HLT_MET200);
   ch1.SetBranchAddress("HLT_PFHT300_PFMET110", &HLT_PFHT300_PFMET110);
   ch1.SetBranchAddress("HLT_PFMET170_HBHECleaned", &HLT_PFMET170_HBHECleaned);
   ch1.SetBranchAddress("HLT_PFMET120_PFMHT120_IDTight", &HLT_PFMET120_PFMHT120_IDTight);
   ch1.SetBranchAddress("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight", &HLT_PFMETNoMu120_PFMHTNoMu120_IDTight);
   ch1.SetBranchAddress("HLT_PFMET200_HBHECleaned", &HLT_PFMET200_HBHECleaned);
   ch1.SetBranchAddress("HLT_PFMET200_HBHE_BeamHaloCleaned", &HLT_PFMET200_HBHE_BeamHaloCleaned);
   ch1.SetBranchAddress("HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned", &HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned);
   ch1.SetBranchAddress("HLT_PFMET120_PFMHT120_IDTight_PFHT60", &HLT_PFMET120_PFMHT120_IDTight_PFHT60);
   ch1.SetBranchAddress("HLT_PFHT500_PFMET100_PFMHT100_IDTight", &HLT_PFHT500_PFMET100_PFMHT100_IDTight);
   ch1.SetBranchAddress("HLT_PFHT700_PFMET85_PFMHT85_IDTight", &HLT_PFHT700_PFMET85_PFMHT85_IDTight);
   ch1.SetBranchAddress("HLT_PFHT800_PFMET75_PFMHT75_IDTight", &HLT_PFHT800_PFMET75_PFMHT75_IDTight);
   ch1.SetBranchAddress("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60", &HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60);
   ch1.SetBranchAddress("run_", &run_);
   ch1.SetBranchAddress("lumi_", &lumi_);
   ch1.SetBranchAddress("evt_", &evt_);
   ch1.SetBranchAddress("numPVs_", &numPVs_);
   ch1.SetBranchAddress("puSF_", &puSF_);
   ch1.SetBranchAddress("PassMETFilters_", &PassMETFilters_);
   ch1.SetBranchAddress("GoodFirstPV_", &GoodFirstPV_);
   ch1.SetBranchAddress("genWeight_", &genWeight_);
   ch1.SetBranchAddress("jet_pt_", &jet_pt_);
   ch1.SetBranchAddress("jet_eta_", &jet_eta_);
   ch1.SetBranchAddress("jet_phi_", &jet_phi_);
   ch1.SetBranchAddress("jet_m_", &jet_m_);
   ch1.SetBranchAddress("jet_regFactor", &jet_regFactor);
   ch1.SetBranchAddress("lepton_pt_", &lepton_pt_);
   ch1.SetBranchAddress("lepton_eta_", &lepton_eta_);
   ch1.SetBranchAddress("lepton_phi_", &lepton_phi_);
   ch1.SetBranchAddress("lepton_e_", &lepton_e_);
   ch1.SetBranchAddress("lepton_scEta_", &lepton_scEta_);
   ch1.SetBranchAddress("lepton_isMuon_", &lepton_isMuon_);
   ch1.SetBranchAddress("lepton_isTight_", &lepton_isTight_);
   ch1.SetBranchAddress("lepton_charge_", &lepton_charge_);
   ch1.SetBranchAddress("lepton_relIso", &lepton_relIso);
   ch1.SetBranchAddress("lepton_IDSF_", &lepton_IDSF_);
   ch1.SetBranchAddress("lepton_recoIsoSF_", &lepton_recoIsoSF_);
   ch1.SetBranchAddress("lepton_energyCorr_", &lepton_energyCorr_);
   ch1.SetBranchAddress("MET_", &MET_);
   ch1.SetBranchAddress("MET_phi_", &MET_phi_);
   ch1.SetBranchAddress("MET_Type1xy_", &MET_Type1xy_);
   ch1.SetBranchAddress("MET_Type1xy_phi_", &MET_Type1xy_phi_);
   ch1.SetBranchAddress("MET_Type1xy_sync_", &MET_Type1xy_sync_);
   ch1.SetBranchAddress("MET_Type1xy_phi_sync_", &MET_Type1xy_phi_sync_);
   ch1.SetBranchAddress("lepton_mu0_pt", &lepton_mu0_pt);
   ch1.SetBranchAddress("lepton_mu0_eta", &lepton_mu0_eta);
   ch1.SetBranchAddress("lepton_mu1_pt", &lepton_mu1_pt);
   ch1.SetBranchAddress("lepton_mu1_eta", &lepton_mu1_eta);
   ch1.SetBranchAddress("lepton_el0_pt", &lepton_el0_pt);
   ch1.SetBranchAddress("lepton_el0_eta", &lepton_el0_eta);
   ch1.SetBranchAddress("lepton_el1_pt", &lepton_el1_pt);
   ch1.SetBranchAddress("lepton_el1_eta", &lepton_el1_eta);


   Long64_t n = ch1.GetEntries();

   cout<<"Numero de eventos: "<<n<<endl;





//  convertedTree->Branch("events",1,"&evtWeight/D");

	for(Int_t i=0;i<n;i++){
		ch1.GetEntry(i);
		
        if (RecoLepID == 11 || RecoLepID == 13 || RecoLepID == 1113 || RecoLepID == 1311){
            eve->puSF = 1.;
            eve->run = run_;
		    eve->lumi = lumi_;
		    eve->evt = evt_;
		    eve->numPVs = numPVs_;
		    eve->passMETFilters = PassMETFilters_;
		    eve->GoodFirstPV = GoodFirstPV_;
            eve->genweight = 1.;
/////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (PROC_XSEC==0){
                eve->evtWeight = evtWeight;    
            }
            else{
                eve->evtWeight = evtWeight*ajuste_no_peso;
            }
            
            eve->Lep_triggers = Lep_triggers;
            eve->Met_triggers = Met_triggers;
            eve->RecoLepID = RecoLepID;
            
            eve->HLT_IsoMu24_= HLT_IsoMu24; 
            eve->HLT_IsoTkMu24_= HLT_IsoTkMu24; 
            eve->HLT_Mu50_= HLT_Mu50; 
            eve->HLT_IsoMu27_= HLT_IsoMu27; 
            eve->HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_= HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ; 
            eve->HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_= HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ; 
            eve->HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_= HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL; 
            eve->HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_= HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL; 
            eve->HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_= HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8; 
            eve->HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_= HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8; 
            eve->HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_= HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ; 
            eve->HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_= HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ; 
            eve->HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_= HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL; 
            eve->HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_= HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL; 
            eve->HLT_Ele27_WPTight_Gsf_= HLT_Ele27_WPTight_Gsf; 
            eve->HLT_Ele115_CaloIdVT_GsfTrkIdT_= HLT_Ele115_CaloIdVT_GsfTrkIdT; 
            eve->HLT_Ele32_WPTight_Gsf_= HLT_Ele32_WPTight_Gsf; 
            eve->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_= HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ; 
            eve->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_= HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL; 
            eve->HLT_DoubleEle33_CaloIdL_MW_= HLT_DoubleEle33_CaloIdL_MW; 
            eve->HLT_PFMET300_= HLT_PFMET300; 
            eve->HLT_MET200_= HLT_MET200; 
            eve->HLT_PFHT300_PFMET110_= HLT_PFHT300_PFMET110; 
            eve->HLT_PFMET170_HBHECleaned_= HLT_PFMET170_HBHECleaned; 
            eve->HLT_PFMET120_PFMHT120_IDTight_= HLT_PFMET120_PFMHT120_IDTight; 
            eve->HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_= HLT_PFMETNoMu120_PFMHTNoMu120_IDTight; 
            eve->HLT_PFMET200_HBHECleaned_= HLT_PFMET200_HBHECleaned; 
            eve->HLT_PFMET200_HBHE_BeamHaloCleaned_= HLT_PFMET200_HBHE_BeamHaloCleaned; 
            eve->HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned_= HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned; 
            eve->HLT_PFMET120_PFMHT120_IDTight_PFHT60_= HLT_PFMET120_PFMHT120_IDTight_PFHT60; 
            eve->HLT_PFHT500_PFMET100_PFMHT100_IDTight_= HLT_PFHT500_PFMET100_PFMHT100_IDTight; 
            eve->HLT_PFHT700_PFMET85_PFMHT85_IDTight_= HLT_PFHT700_PFMET85_PFMHT85_IDTight; 
            eve->HLT_PFHT800_PFMET75_PFMHT75_IDTight_= HLT_PFHT800_PFMET75_PFMHT75_IDTight; 
            eve->HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60_= HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60; 
/////////////////////////////////////////////////////////////////////////////////////////////////////////
            eve->MET  		= MET_;
		    eve->MET_phi  	= MET_phi_;
		    eve->MET_Type1xy  		= MET_Type1xy_;
		    eve->MET_Type1xy_phi  	= MET_Type1xy_phi_;
		    eve->MET_Type1xy_sync  		= MET_Type1xy_sync_;
		    eve->MET_Type1xy_phi_sync  	= MET_Type1xy_phi_sync_;


            vfloat jet_pt_2;
			vfloat jet_eta_2;
			vfloat jet_phi_2;
			vfloat jet_m_2;
			vfloat jet_regFactor_2;

			jet_pt_2.clear();
			jet_eta_2.clear();
			jet_phi_2.clear();
			jet_m_2.clear();
			jet_regFactor_2.clear();

            for(int i=0;i<jet_pt_->size();i++){
                jet_pt_2.push_back(jet_pt_->at(i));
                jet_eta_2.push_back(jet_eta_->at(i));
                jet_phi_2.push_back(jet_phi_->at(i));
                jet_m_2.push_back(jet_m_->at(i));
                jet_regFactor_2.push_back(jet_regFactor->at(i));
            }

            eve->jet_pt  	= jet_pt_2;
			eve->jet_eta  	= jet_eta_2;
			eve->jet_phi  	= jet_phi_2;
			eve->jet_m  	= jet_m_2;
			eve->jet_RegFactor_ = jet_regFactor_2;



            vfloat lepton_pt_2;
	 	    vfloat lepton_eta_2;
	  	    vfloat lepton_phi_2;
	  	    vfloat lepton_e_2;
            vfloat lepton_scEta_2;
	  	    vfloat lepton_IDSF_2;
		    vfloat lepton_recoIsoSF_2;
		    vfloat lepton_relIso_2;
		    vfloat lepton_energyCorr_2;


            vint lepton_charge_2;
            vint lepton_isMuon_2;
            vint lepton_isTight_2;
        

            lepton_pt_2.clear();
	        lepton_eta_2.clear();
	        lepton_phi_2.clear();
	        lepton_e_2.clear();
		    lepton_scEta_2.clear();
	        lepton_IDSF_2.clear();
	        lepton_recoIsoSF_2.clear();
	        lepton_relIso_2.clear();
	        lepton_charge_2.clear();
	        lepton_isMuon_2.clear();
	        lepton_isTight_2.clear();
	        lepton_energyCorr_2.clear();

            
            for(int i=0;i<lepton_pt_->size();i++){
                lepton_pt_2.push_back(lepton_pt_->at(i));
                lepton_eta_2.push_back(lepton_eta_->at(i));
                lepton_phi_2.push_back(lepton_phi_->at(i));
                lepton_e_2.push_back(lepton_e_->at(i));
                lepton_scEta_2.push_back(lepton_scEta_->at(i));
                lepton_IDSF_2.push_back(lepton_IDSF_->at(i));
                lepton_recoIsoSF_2.push_back(lepton_recoIsoSF_->at(i));
                lepton_relIso_2.push_back(lepton_relIso->at(i));
                
                lepton_charge_2.push_back(lepton_charge_->at(i));
                lepton_isMuon_2.push_back(lepton_isMuon_->at(i));
                lepton_isTight_2.push_back(1);
                //  //lepton_isTight_2.push_back(lepton_isTight_->at(i));
                lepton_energyCorr_2.push_back(lepton_energyCorr_->at(i));

                }

        eve->lepton_pt         = lepton_pt_2;
	    eve->lepton_eta        = lepton_eta_2;
	    eve->lepton_phi        = lepton_phi_2;
	    eve->lepton_e          = lepton_e_2;
	    eve->lepton_scEta      = lepton_scEta_2;
	    eve->lepton_isMuon     = lepton_isMuon_2;
	    eve->lepton_isTight    = lepton_isTight_2;
	    eve->lepton_charge     = lepton_charge_2;
	    eve->lepton_relIso     = lepton_relIso_2;
	    eve->lepton_IDSF       = lepton_IDSF_2;
	    eve->lepton_recoIsoSF  = lepton_recoIsoSF_2;
	    eve->lepton_energyCorr  = lepton_energyCorr_2;

        }

		convertedTree->Fill();
	}
newfile->Write();
newfile->Close();
}
