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
#include "include/EventVars.h"



//Tentando pegar informação dos arquivos nas pastas do TTTo2L2Nu_16_?_?, onde ? varia de 0 a 100
//void list_files(const char *dirname="/home/matheus/Desktop/TChain/TTTo2L2Nu_16_files", const char *ext="Tree.root") // https://root-forum.cern.ch/t/open-files-in-a-directory-with-a-for-loop/12471
//void list_files(TChain *ch1,const char *dirname="/home/matheus/Desktop/TChain/TTTo2L2Nu_16_files", const char *ext="Tree.root")
void list_files(vector<int> *ch1,const char *dirname="/home/matheus/Desktop/TChain/TTTo2L2Nu_16_files", const char *ext="Tree.root")

{
	int n = 9999;
    for(int i=0;i<n;i++){
        const char *d = "/home/matheus/Desktop/TChain/";
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
      					} else {     
						//ch1->Add("Tree.root");
                        ch1->push_back(i);
						f.Close();
						//cout <<c<<"Tree.root não falhou!"<<endl;
   						}
		         }
    		  }
   			}
    }
}


vector<int> index;
TChain ch1("selection"); 												   //Crio um Tchain chamado ch1, por onde vou adcionar todas as outras trees, usando o list_files
list_files(&index);														   //Pego os 100 tree.root separados entre as pastas e junto eles aqui na minha Tchain.

std::cout<<index.size()<<endl;


std::string str = "/home/matheus/Desktop/TChain/TTTo2L2Nu_16_files";
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






TFile *newfile= new TFile("/home/matheus/Desktop/TChain/MCttbar.root","recreate");                      //Crio um Arquivo com nome MCttbar
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
   Double_t        evtWeight_;
   Bool_t          HLT_IsoMu24_;
   Bool_t          HLT_IsoTkMu24_;
   Bool_t          HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_;
   Bool_t          HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_;
   Bool_t          HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_;
   Bool_t          HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_;
   Bool_t          HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_;
   Bool_t          HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_;
   Bool_t          HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_;
   Bool_t          HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_;
   Bool_t          HLT_Ele27_WPTight_Gsf_;
   Bool_t          HLT_Ele115_CaloIdVT_GsfTrkIdT_;
   Bool_t          HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_;
   Bool_t          HLT_PFMET300_;
   Bool_t          HLT_MET200_;
   Bool_t          HLT_PFHT300_PFMET110_;
   Bool_t          HLT_PFMET170_HBHECleaned_;
   Bool_t          HLT_PFMET120_PFMHT120_IDTight_;
   Bool_t          HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_;
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




   ch1.SetBranchAddress("evtWeight", &evtWeight_);
   ch1.SetBranchAddress("HLT_IsoMu24_", &HLT_IsoMu24_);                                                                    
   ch1.SetBranchAddress("HLT_IsoTkMu24_", &HLT_IsoTkMu24_);
   ch1.SetBranchAddress("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_);
   ch1.SetBranchAddress("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_", &HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_);
   ch1.SetBranchAddress("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_", &HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_);
   ch1.SetBranchAddress("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_", &HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_);
   ch1.SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_);
   ch1.SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_);
   ch1.SetBranchAddress("HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_", &HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_);
   ch1.SetBranchAddress("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_", &HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_);
   ch1.SetBranchAddress("HLT_Ele27_WPTight_Gsf_", &HLT_Ele27_WPTight_Gsf_);
   ch1.SetBranchAddress("HLT_Ele115_CaloIdVT_GsfTrkIdT_", &HLT_Ele115_CaloIdVT_GsfTrkIdT_);
   ch1.SetBranchAddress("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_", &HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_);


   ch1.SetBranchAddress("HLT_PFMET300_", &HLT_PFMET300_);
   ch1.SetBranchAddress("HLT_MET200_", &HLT_MET200_);
   ch1.SetBranchAddress("HLT_PFHT300_PFMET110_", &HLT_PFHT300_PFMET110_);
   ch1.SetBranchAddress("HLT_PFMET170_HBHECleaned_", &HLT_PFMET170_HBHECleaned_);
   ch1.SetBranchAddress("HLT_PFMET120_PFMHT120_IDTight_", &HLT_PFMET120_PFMHT120_IDTight_);
   ch1.SetBranchAddress("HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_", &HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_);
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



   Long64_t n = ch1.GetEntries();

   cout<<"Numero de eventos: "<<n<<endl;





//  convertedTree->Branch("events",1,"&evtWeight/D");

	for(Int_t i=0;i<n;i++){
		ch1.GetEntry(i);
		
		//Preencho os triggers

        eve->HLT_Ele27_WPTight_Gsf = HLT_Ele27_WPTight_Gsf_;                                                                //Tem que implementar no EventVars
		eve->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_;                        ///
		eve->HLT_Ele115_CaloIdVT_GsfTrkIdT = HLT_Ele115_CaloIdVT_GsfTrkIdT_;                                                ///
     
     	eve->HLT_PFMET300 = HLT_PFMET300_;
     	eve->HLT_MET200 = HLT_MET200_;
     	eve->HLT_PFHT300_PFMET110 = HLT_PFHT300_PFMET110_;
     	eve->HLT_PFMET170_HBHECleaned = HLT_PFMET170_HBHECleaned_;
     	eve->HLT_PFMET120_PFMHT120_IDTight = HLT_PFMET120_PFMHT120_IDTight_;
     	eve->HLT_PFMETNoMu120_PFMHTNoMu120_IDTight = HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_;
		
        eve->puSF = 1.;
        eve->run = run_;
		eve->lumi = lumi_;
		eve->evt = evt_;
		eve->numPVs = numPVs_;
		eve->passMETFilters = PassMETFilters_;
		eve->GoodFirstPV = GoodFirstPV_;
        eve->genweight = 1.;
/////////////////////////////////////////////////////////////////////////////////////////////////////////
        eve->evtWeight = evtWeight_;
        eve->HLT_IsoMu24 = HLT_IsoMu24_;                                                                                               ///
        eve->HLT_IsoTkMu24 = HLT_IsoTkMu24_;                                                                                           //Tem que implementar no EventVars
        eve->HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL = HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_;                                                 //Tem que implementar no EventVars
        eve->HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ = HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_;                                               //Tem que implmentar no EventVars
        eve->HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ = HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_;                                           //Tem que implementar no EventVars

        eve->HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL = HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_;                                                     ///                                                   
        eve->HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL = HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_;                       ///
        eve->HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_;                 ///
        eve->HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL = HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_;                         ///
        eve->HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ = HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_;                   ///
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
                 //lepton_isTight_2.push_back(lepton_isTight_->at(i));
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



		convertedTree->Fill();
	}
newfile->Write();
newfile->Close();
}







// 
// TTree *t= new TTree("t","Eventos");
// Int_t NMuon,NMuonIso,NJet,NElectron,NElectronIso,NJetB,NJetTrue;
// Float_t Muon_Px[10],Muon_Py[10],Muon_Pz[10],Muon_Iso[10],Jet_Px[10],Jet_Py[10],Jet_Pz[10],Muon_E[10],Jet_E[10],EventWeight,PesoEven,MET_px,MET_py,RelIso,MuonPt,ValorMuonEta,ValorJetEta,ElectronPt,JetPt,Electron_Px[10],Electron_Py[10],Jet_btag[10],Electron_Iso[10],MissE;
// bool triggerIsoMu24,Jet_ID[10];
// TLorentzVector Muon,Jet;


// t->Branch("NMuonIso",&NMuonIso,"NMuonIso/I");
// t->Branch("NJetTrue",&NJetTrue,"NJetTrue/I");
// t->Branch("NJetB",&NJetB,"NJetB/I");
// t->Branch("MuonPt",&MuonPt,"MuonPt/F");
// t->Branch("ValorMuonEta",&ValorMuonEta,"ValorMuonEta/F");
// t->Branch("JetPt",&JetPt,"JetPt/F");
// t->Branch("ValorJetEta",&ValorJetEta,"ValorJetEta/F");
// t->Branch("MissE",&MissE,"MissE/F");
// t->Branch("PesoEven",&PesoEven,"PesoEven/F");