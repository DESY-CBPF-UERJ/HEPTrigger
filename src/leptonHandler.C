#include "../include/leptonHandler.h"


leptonHandler::leptonHandler()
{
    era_=0;
	passSLCuts_el = false;
	passSLCuts_mu = false;
	passDLCuts_el = false;
	passDLCuts_mu = false;
	passDLCuts_emu = false;
	passSLtriggers_el = false;
	passSLtriggers_mu = false;
	passDLtriggers_el = false;
	passDLtriggers_mu = false;
	passDLtriggers_emu = false;
	// passMultiMuons = -1;
	MuonExtraNumber = -99;
	ElectronExtraNumber = -99;
	nLeptons = 0;
	nMuons = 0;
	leadPt_mu = -99;
	leadEta_mu = -99;
	leadRelIso_mu = -99;
	leadIndex_mu = -99;
	subPt_mu = -99;
	subEta_mu = -99;
	subRelIso_mu = -99;
	subIndex_mu = -99;
	nElectrons = 0;
	leadPt_el = -99;
	leadEta_el = -99;
	leadIndex_el = -99;
	subPt_el = -99;
	subEta_el = -99;
	subRelIso_el = -99;
	subIndex_el = -99;
	leadCharge_el = -99;
	subCharge_el = -99;
	leadCharge_mu = -99;
	subCharge_mu = -99;
	leadIDSF_el = 1.;
	leadRecoIsoSF_el = 1.;
	subIDSF_el = 1.;
	subRecoIsoSF_el = 1.;
	leadIDSF_mu = 1.;
	leadRecoIsoSF_mu = 1.;
	subIDSF_mu = 1.;
	subRecoIsoSF_mu = 1.;

	mll = -99;

	isMC = false;
	dataPeriod = "";
	dataStream = "";
	b_periodDep__HLT_IsoMu24_eta2p1 = false;
	b_periodDep__doubleMu_noMass = false;
	b_periodDep__doubleMu_withMass = false;

}

leptonHandler::~leptonHandler() {}

void leptonHandler::test()
{
  	std::cout << "Test!" << endl;
}


void leptonHandler::setFlags(bool passMC, string inputFile)
{
	isMC = passMC;
	if (!isMC){
	// *** I. Period
    		if      (inputFile.find("Run2016B")  != string::npos) dataPeriod = "B";
    		else if (inputFile.find("Run2016C")  != string::npos) dataPeriod = "C";
    		else if (inputFile.find("Run2016D")  != string::npos) dataPeriod = "D";
    		else if (inputFile.find("Run2016E")  != string::npos) dataPeriod = "E";
    		else if (inputFile.find("Run2016F1") != string::npos) dataPeriod = "F1";
    		else if (inputFile.find("Run2016F2") != string::npos) dataPeriod = "F2";
    		else if (inputFile.find("Run2016G")  != string::npos) dataPeriod = "G";
    		else if (inputFile.find("Run2016H")  != string::npos) dataPeriod = "H";
			else if (inputFile.find("Run2016Full")  != string::npos) dataPeriod = "Full";

    		else if (inputFile.find("Run2017B") != string::npos) dataPeriod = "B";
    		else if (inputFile.find("Run2017C") != string::npos) dataPeriod = "C";
    		else if (inputFile.find("Run2017D") != string::npos) dataPeriod = "D";
    		else if (inputFile.find("Run2017E") != string::npos) dataPeriod = "E";
    		else if (inputFile.find("Run2017F") != string::npos) dataPeriod = "F";
			

    		else if (inputFile.find("Run2018A") != string::npos) dataPeriod = "A";
    		else if (inputFile.find("Run2017B") != string::npos) dataPeriod = "B";
    		else if (inputFile.find("Run2017C") != string::npos) dataPeriod = "C";
    		else if (inputFile.find("Run2017D") != string::npos) dataPeriod = "D";

    		else                                                 dataPeriod = "";

    		// *** II. Stream
    		if (inputFile.find("DoubleMu") != string::npos)      dataStream = "mumu";
    		else if (inputFile.find("DoubleEl") != string::npos) dataStream = "ee";
    		else if (inputFile.find("EMu") != string::npos)      dataStream = "emu";
    		else                                                 dataStream = "";
	}
}

void leptonHandler::applyMuonCuts()
{
	

	//CORREÇÂO DO CODIGO-> Se tivessemos um evento com 1 lepton e 1 muon, ele automaticamente colocava o indeice deles de 0 e 1, quando deveria ser 0 e 0.

	
 	for (unsigned int l = 0; l < ev->lepton_pt.size(); l++) {

    		// Cut 0: is muon
    		if ( !(ev->lepton_isMuon[l] == 1) ) continue;
    		//h_mu_cutflow->Fill("Total Muons", 1);
    		//if (leadIndex_mu == -99)     h_mu_event_cutflow->Fill("Total Muons", 1);

    		// Cut 1: pT > 15 GeV --> use SL veto as threshold for counting muons. Apply higher pT cut later
    		// if ( !(ev->lepton_pt_[l] > 15) ) continue;
    	//	if ( !(ev->lepton_pt[l] > 20) ) continue;
    		//h_mu_cutflow->Fill("p_{T} > 15", 1);
    		//if (leadIndex_mu == -99)     h_mu_event_cutflow->Fill("p_{T} > 15", 1);

    		// Cut 2: |ETA| < 2.4
    	//	if ( !(abs(ev->lepton_eta[l]) < 2.4) ) continue;
    		//h_mu_cutflow->Fill("|#eta| < 2.4", 1);
    		//if (leadIndex_mu == -99)     h_mu_event_cutflow->Fill("|#eta| < 2.4", 1);

    		// Cut 3: tight ID
    	//	if ( !(ev->lepton_isTight[l] == 1) ) continue;
    		//h_mu_cutflow->Fill("Tight", 1);
    		//if (leadIndex_mu == -99)     h_mu_event_cutflow->Fill("Tight", 1);

    		// Cut 4: Isolation < 0.25
    		// if ( !(ev->lepton_relIso_[l] < 0.25) ) continue;
    	//	if ( !(ev->lepton_relIso[l] < 0.15) ) continue;
    		//h_mu_cutflow->Fill("Isolation < 0.25", 1);
    		//if (leadIndex_mu == -99)     h_mu_event_cutflow->Fill("Isolation < 0.25", 1);
    		nMuons++;
    		if (isDebug)
      			cout << "\n ev->evt = " << ev->evt << " and muon " << l << " has pt " << ev->lepton_pt[l] << " , eta " << ev->lepton_eta[l] << " , phi " << ev->lepton_phi[l] << " , iso " << ev->lepton_relIso[l] << " , isTight " << ev->lepton_isTight[l] << " , isMuon " << ev->lepton_isMuon[l] << " , charge " << ev->lepton_charge[l] << endl;

		// Cut 5: Trigger
    		//if ( ev->passHLT_IsoMu27_v_ && leadIndex_mu == -99)     h_mu_event_cutflow->Fill("Trigger", 1);


    		// set leading/subleading indices if appropriate
    		setLeadSubleadIndices(l, leadIndex_mu, subIndex_mu);
			// cout<<"Temos um Leadmuon, com indice:"<<leadIndex_mu<<endl;
			// cout<<"Temos um Submuon, com indice:"<<subIndex_mu<<endl;
			// cout<<"==========================================================="<<endl;
	} // loop over muons

  	// *** ?. Wrap-up
	//cout<<"leadIndex_mu = "<<leadIndex_mu<<endl;
	//cout<<"nmuons = "<< nMuons<<endl;
  	//h_mu_n->Fill( nMuons );
  	if (leadIndex_mu != -99){
    		leadPt_mu = ev->lepton_pt[leadIndex_mu];
    		leadEta_mu = ev->lepton_eta[leadIndex_mu];
    		leadRelIso_mu = ev->lepton_relIso[leadIndex_mu];
    		leadCharge_mu = ev->lepton_charge[leadIndex_mu];
    		leadIDSF_mu = ev->lepton_IDSF[leadIndex_mu] ;
    		leadRecoIsoSF_mu = ev->lepton_recoIsoSF[leadIndex_mu] ;
  	}
  	if (subIndex_mu != -99){
    		subPt_mu = ev->lepton_pt[subIndex_mu];
    		subEta_mu = ev->lepton_eta[subIndex_mu];
    		subRelIso_mu = ev->lepton_relIso[subIndex_mu];
    		subCharge_mu = ev->lepton_charge[subIndex_mu];
    		subIDSF_mu = ev->lepton_IDSF[subIndex_mu] ;
    		subRecoIsoSF_mu = ev->lepton_recoIsoSF[subIndex_mu] ;
  	}
  	if (nMuons > 0 && leadIndex_mu == -99)
    		cout << "applyMuonCuts: NAHHHH" << endl;

  	if (subPt_mu > leadPt_mu)
    		cout << "subPt_mu: " << subPt_mu << "\tleadPt_mu: " << leadPt_mu << endl;
}

void leptonHandler::applyElectronCuts()
{
  	//if (leadIndex == -99) return; // protection when no electron in event

  	// bool pass0 = false;
  	// bool pass1 = false;
  	// bool pass2 = false;
  	// bool pass3 = false;
  	// bool pass4 = false;
  	// bool pass5 = false;
  	// bool pass6 = false;
  	// bool pass7 = false;

  	for (unsigned int l = 0; l < ev->lepton_pt.size(); l++) {
	    	//if ( ev->lepton_pt_.size() == 0) continue ; // protection against events w/o leptons
	    	//if ( l > 0) continue ; // only for testing

	     	// Cut 0: Is electron
	    	if ( !(ev->lepton_isMuon[l] == 0) ) continue;
	    	//h_el_cutflow->Fill("Total Electrons", 1);
	    	//if (!pass0) h_el_event_cutflow->Fill("Total Electrons", 1);
	  //  	pass0 = true;

	    	// Cut 1: pT > 15 GeV
	    	// if ( !(ev->lepton_pt_[l] > 15) ) continue;
	  //  	if ( !(ev->lepton_pt[l] > 20) ) continue;
	    	//h_el_cutflow->Fill("p_{T} > 15", 1);
	    	//if (!pass1) h_el_event_cutflow->Fill("p_{T} > 15", 1);
	  //  	pass1 = true;

	    	// Cut 2: |ETA| < 2.4
	  //   	if ( !(abs(ev->lepton_eta[l]) < 2.4) ) continue;
	    	//h_el_cutflow->Fill("|#eta| < 2.4", 1);
	    	//if (!pass2) h_el_event_cutflow->Fill("|#eta| < 2.4", 1);
	  //  	pass2 = true;

	    	// Cut 3: Reject cluster |ETA| in crack ( < 1.4442, > 1.566 )
	  //  	if ( !(abs(ev->lepton_scEta[l]) < 1.4442 || abs(ev->lepton_scEta[l]) > 1.566) ) continue;
	    	//h_el_cutflow->Fill("Reject Crack Cluster #eta", 1);
	    	//if (!pass3) h_el_event_cutflow->Fill("Reject Crack Cluster #eta", 1);
	  //  	pass3 = true;

	    	// Cut 4: tight ID
	  //  	if ( !(ev->lepton_isTight[l] == 1) ) continue;
	    	//h_el_cutflow->Fill("Tight ID", 1);
	    	//if (!pass4) h_el_event_cutflow->Fill("Tight ID", 1);
	  //  	pass4 = true;

	    	if (isDebug)
	      		cout << "\n ev->evt = " << ev->evt << " and electron " << l << " has pt " << ev->lepton_pt[l] << " , eta " << ev->lepton_eta[l] << " , phi " << ev->lepton_phi[l] << " , iso " << ev->lepton_relIso[l] << " , isTight " << ev->lepton_isTight[l] << " , isMuon " << ev->lepton_isMuon[l] << " , charge " << ev->lepton_charge[l] << endl;

	    	// Trigger cuts
	    	// if ( ev->passHLT_Ele35_WPTight_Gsf_v_ ) {
	      	// 	//if (!pass5) h_el_event_cutflow->Fill("El Trigger", 1);
	      	// 	pass5 = true;
	    	// }
	    	// if ( ev->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ ) {
	      	// 	//if (!pass6) h_el_event_cutflow->Fill("MET Trigger", 1);
	      	// 	pass6 = true;
	    	// }
	    	// if ( ev->passHLT_Ele35_WPTight_Gsf_v_ && ev->passHLT_PFMET120_PFMHT120_IDTight_v_ ) {
	      	// 	//if (!pass7) h_el_event_cutflow->Fill("MET+Lep Trigger", 1);
	      	// 	pass7 = true;
	    	// }

	    	nElectrons++;

	    	//if (isDebug)
	    		//  cout << "\n ev->evt = " << ev->evt_ << " and electron " << l << " has pt " << ev->lepton_pt_[l] << " , eta " << ev->lepton_eta_[l] << " , phi " << ev->lepton_phi_[l] << " , iso " << ev->lepton_relIso_[l] << " , isTight " << ev->lepton_isTight_[l] << " , isMuon " << ev->lepton_isMuon_[l] << " , charge " << ev->lepton_charge_[l] << endl;


	    	// set leading/subleading indices if appropriate
	    	setLeadSubleadIndices(l, leadIndex_el, subIndex_el);
			// cout<<"Temos um Leadeletron, com indice:"<<leadIndex_el<<endl;
			// cout<<"Temos um Subeletron, com indice:"<<subIndex_el<<endl;
			// cout<<"==========================================================="<<endl;

  	} // loop over electrons

  	//h_el_n->Fill( nElectrons );
  	//if (nElectrons == 1) h_el_event_cutflow->Fill("==1 Electron", 1);
  	//if (nElectrons == 1 && ev->MET_[0] > 125 && ev->passHLT_PFMET120_PFMHT120_IDTight_v_) h_el_event_cutflow->Fill("==1 Electron RefTrig", 1);
  	//if (nElectrons == 1 && ev->MET_[0] > 125 && ev->passHLT_Ele35_WPTight_Gsf_v_ && ev->passHLT_PFMET120_PFMHT120_IDTight_v_) h_el_event_cutflow->Fill("==1 Electron AllTrig", 1);

  	if (leadIndex_el != -99){
  			leadPt_el = ev->lepton_pt[leadIndex_el];
    		leadEta_el = ev->lepton_eta[leadIndex_el];
    		leadRelIso_el = ev->lepton_relIso[leadIndex_el];
    		leadCharge_el = ev->lepton_charge[leadIndex_el];
    		leadIDSF_el = ev->lepton_IDSF[leadIndex_el] ;
    		leadRecoIsoSF_el = ev->lepton_recoIsoSF[leadIndex_el] ;
  	}

  	if (subIndex_el != -99){
    		subPt_el = ev->lepton_pt[subIndex_el];
    		subEta_el = ev->lepton_eta[subIndex_el];
    		subRelIso_el = ev->lepton_relIso[subIndex_el];
    		subCharge_el = ev->lepton_charge[subIndex_el];
    		subIDSF_el = ev->lepton_IDSF[subIndex_el] ;
    		subRecoIsoSF_el = ev->lepton_recoIsoSF[subIndex_el] ;
  	}

  	if (nElectrons > 0 && leadIndex_el == -99)
    		cout << "applyElectronCuts: NAHHHH" << endl;

	//cout<<"Opa "<<subPt_el<<endl;
  	if (subPt_el > leadPt_el)
    		cout << "subPt_el: " << subPt_el << "\tleadPt_el: " << leadPt_el << endl;
}


void leptonHandler::setLeadSubleadIndices(int l, int& lead, int& sub)
{
	// *** 0. Temporary variables
  	float leadPt = (lead == -99) ? -99 : ev->lepton_pt[lead];
  	float subPt  = (sub == -99) ? -99  : ev->lepton_pt[sub];

  	// *** 1. Set leading lepton if appropriate
  	if (ev->lepton_pt[l] > leadPt) {

    	// ** A. If already have first good lepton, set old lead lepton to sub
    		if (leadPt != -99){
      			sub = lead;
    		}
    		// ** B. set new leading lepton to leading
    		lead = l;
  	}
  	else if (ev->lepton_pt[l] < leadPt && ev->lepton_pt[l] > subPt) {

  		// ** C. New lepton not greater than leading but greater than sub
  		sub = l;
  	}
}

void leptonHandler::checkCategoryCuts()
{
  	
	
	// ###   SL mu   ###
  	if (nMuons == 1 && nElectrons==0){
    		// passSLCuts_mu = true;
    		passSLCuts_mu = true && ev->GoodFirstPV && ev-> passMETFilters;
  	}
  	// ###   SL el   ###
  	if (nElectrons == 1 && nMuons == 0)
    		// passSLCuts_el = true;
    		passSLCuts_el = true && ev->GoodFirstPV && ev-> passMETFilters;

  	// ###   DL mumu   ###
  	// if ( (nMuons==2 && nElectrons==0) && leadPt_mu >= 25 && subPt_mu >= 15){
  	if ( (nMuons==2 && nElectrons==0)){
    		//mll = calculateDileptonMass(leadIndex_mu, subIndex_mu);
    		// if (mll > 20 && (mll < 76 || mll > 106) && leadCharge_mu*subCharge_mu == -1 && (isMC || (!isMC && (dataStream=="" || dataStream=="mumu")) ) )
    	//	if (leadCharge_mu*subCharge_mu == -1 && (isMC || (!isMC && (dataStream=="" || dataStream=="mumu")) ) )
			if (leadCharge_mu*subCharge_mu == -1)
      			 //passDLCuts_mu = true;
      			 passDLCuts_mu = true && (ev->RecoLepID==13) ; //&& ev->GoodFirstPV && ev-> passMETFilters;
				 MuonExtraNumber = nMuons - 2;
				 ElectronExtraNumber = nElectrons -0;
	}

  	// ###   DL ee   ###
  	// VERSÃO ANTERIOR: if ( (nMuons==0 && nElectrons==2) && leadPt_el >= 25 && subPt_el >= 20){
  	if ( nMuons==0 && nElectrons==2){
    		//mll = calculateDileptonMass(leadIndex_el, subIndex_el);

    		//VERSÃO ANTERIOR: if (mll > 20 && leadCharge_el*subCharge_el == -1 && (isMC || (!isMC && (dataStream=="" || dataStream=="ee")) ) )
    	//	if (leadCharge_el*subCharge_el == -1 && (isMC || (!isMC && (dataStream=="" || dataStream=="ee")) ) )
			if (leadCharge_el*subCharge_el == -1)
      			 //passDLCuts_el = true;
      			passDLCuts_el = true && (ev->RecoLepID==11); //&& ev->GoodFirstPV && ev-> passMETFilters;
				MuonExtraNumber = nMuons - 0;
				ElectronExtraNumber = nElectrons - 2;
	}


  	// ###   DL emu   ###
  	// if ( (nMuons==1 && nElectrons==1) && ((leadPt_mu >= 25 && leadPt_el >= 15) || (leadPt_el >= 25 && leadPt_mu >= 15)) ){
  	if ( (nMuons==1 && nElectrons==1) ){
    		//mll = calculateDileptonMass(leadIndex_mu, leadIndex_el);
    		if(isDebug)
      			cout << "Event " << ev->evt << " , leadCharge_mu " << leadCharge_mu << " , leadCharge_el " << leadCharge_el << endl;
    	//	if (leadCharge_mu*leadCharge_el == -1 && (isMC || (!isMC && (dataStream=="" || dataStream=="emu")) ) )
			if (leadCharge_mu*leadCharge_el == -1 )
      			//passDLCuts_emu = true;
      			passDLCuts_emu = true && (ev->RecoLepID==1311 || ev->RecoLepID==1113);// && ev->GoodFirstPV && ev-> passMETFilters;
				MuonExtraNumber = nMuons - 1;
				ElectronExtraNumber = nElectrons -1;
  	}




}

float leptonHandler::calculateDileptonMass(int index_lead, int index_sub)
{
  	// TLorentzVector *l1 = new TLorentzVector();
  	// TLorentzVector *l2 = new TLorentzVector();
  	TLorentzVector l1 = TLorentzVector(0.,0.,0.,0.);
  	TLorentzVector l2 = TLorentzVector(0.,0.,0.,0.);
  	// l1->SetPtEtaPhiE( ev->lepton_pt_[index_lead], ev->lepton_eta_[index_lead], ev->lepton_phi_[index_lead], ev->lepton_e_[index_lead] );
  	// l2->SetPtEtaPhiE( ev->lepton_pt_[index_sub], ev->lepton_eta_[index_sub], ev->lepton_phi_[index_sub], ev->lepton_e_[index_sub] );
  	l1.SetPtEtaPhiE( ev->lepton_pt[index_lead], ev->lepton_eta[index_lead], ev->lepton_phi[index_lead], ev->lepton_e[index_lead] );
  	l2.SetPtEtaPhiE( ev->lepton_pt[index_sub], ev->lepton_eta[index_sub], ev->lepton_phi[index_sub], ev->lepton_e[index_sub] );

  	// TLorentzVector *ll = new TLorentzVector();
  	// *ll = *l1 + *l2;
  	// return ll->M();
  	TLorentzVector ll = TLorentzVector(0.,0.,0.,0.);
  	ll = l1 + l2;
  	return ll.M();
}


void leptonHandler::checkHLTTriggers()
{


	////// 	2017 Trigger Logic 	///////////////////////////////////////
    if(era_==2017){

       	//cout<<"In HLT loop dataperiod = "<<dataPeriod<<endl;  // For Debugging
      	b_periodDep__HLT_IsoMu24_eta2p1   = isMC || (!isMC && (dataPeriod == "A" || dataPeriod == "B" || dataPeriod == "C" || dataPeriod == "D") ) ? true : false; // should be true if MC || if is data and period is A, B, C, or D
      	b_periodDep__doubleMu_noMass   = isMC || (!isMC && (dataPeriod == "A" || dataPeriod == "B") ) ? true : false; // should be true if MC || if sample is data and period is A or B
      	b_periodDep__doubleMu_withMass = isMC || (!isMC && (dataPeriod == "C" || dataPeriod == "D" || dataPeriod == "E" || dataPeriod == "F") ) ? true : false; // should be true if MC || if sample is data and period is C, D, E, or F

      	// muon triggers
      	// passSLtriggers_mu = ev->passHLT_IsoMu27_v_ || (ev->passHLT_IsoMu24_eta2p1_v_ && b_periodDep__HLT_IsoMu24_eta2p1) ? true : false;
      	passSLtriggers_mu = (ev->HLT_IsoMu27_ || ev->HLT_Mu50_)  ? true : false;

    	//passDLtriggers_mu = (ev->passHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v_ && b_periodDep__doubleMu_noMass) || ((ev->passHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v_ || ev->passHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v_) && b_periodDep__doubleMu_withMass) ? true : false; 	//Charis -- I tried this test - to remove the mass8 trigger - not reffered to in the AN
     	passDLtriggers_mu = ev->HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_ ? true : false; // && b_periodDep__doubleMu_noMass) || ( ev->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_ && b_periodDep__doubleMu_withMass) ? true : false;

      	// electron triggers
      	// passSLtriggers_el = ev->passHLT_Ele32_WPTight_Gsf_L1DoubleEG_v_ || (ev->passHLT_Ele28_eta2p1_WPTight_Gsf_HT150_v_ && !isTrigSF) ? true : false;
      	passSLtriggers_el = false; //ev->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_ ? true : false;
      	//passSLtriggers_el = ev->passHLT_Ele35_WPTight_Gsf_v_ || (ev->passHLT_Ele28_eta2p1_WPTight_Gsf_HT150_v_ ) ? true : false;
      	passDLtriggers_el = ev->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_ || ev->HLT_DoubleEle33_CaloIdL_MW_ ? true : false;


      	//if (passDLtriggers_el)
      	//  cout << "HEY! You're part of it!! (DLtriggers_el)" << endl;

      	passDLtriggers_emu = ev->HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_ || ev->HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_ ? true : false;

      	//if (passDLtriggers_emu)
      	//  cout << "HEY! You're part of it!! (DLtriggers_emu)" << endl;

    }
	////// 	2016 Trigger Logic 	///////////////////////////////////////

    if(era_==2016){

		if(dataPeriod == "Full"){
			passSLtriggers_mu = (ev->Lep_triggers) ? true : false;
			passDLtriggers_mu = (ev->Lep_triggers) ? true : false;
			passSLtriggers_el = (ev->Lep_triggers) ? true : false;
			passDLtriggers_el = (ev->Lep_triggers) ? true : false;
			passDLtriggers_emu = (ev->Lep_triggers) ? true : false;
		}

      	passSLtriggers_mu = (ev->HLT_IsoMu24_ || ev->HLT_IsoTkMu24_ || ev-> HLT_Mu50_) ? true : false;
    	passDLtriggers_mu = ( ( (ev->HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_  || ev->HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_ ) && (dataPeriod != "H" ) ) 
								|| ( (ev->HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_  || ev->HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_ ) && (dataPeriod == "H" ) ) ) ? true : false;

      	passSLtriggers_el = ( ev->HLT_Ele27_WPTight_Gsf_ || ev->HLT_Ele115_CaloIdVT_GsfTrkIdT_ ) ? true : false; //HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ
      	passDLtriggers_el = ( ev->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_  ) ? true : false;


      	passDLtriggers_emu = ( ((ev->HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_ || ev->HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_) && (dataPeriod != "H" ))
                                || ((ev->HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_ || ev->HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_) && (dataPeriod == "H" ))
                                );
    }
	///////////////////////////////////////////////////////////////////////

	////// 	2018 Trigger Logic 	///////////////////////////////////////
    if(era_==2018){

      	passSLtriggers_mu = (ev->HLT_IsoMu24_ || ev->HLT_Mu50_) ? true : false;
    	// passDLtriggers_mu = ((ev->passHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v_ ) || (ev->passHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v_ )) ? true : false;
    	passDLtriggers_mu = ((ev->HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_ )) ? true : false;

      	// passSLtriggers_el = ( ev->passHLT_Ele35_WPTight_Gsf_v_ || ev->passHLT_Ele32_WPTight_Gsf_v_ ) ? true : false;
      	passSLtriggers_el = ( ev->HLT_Ele115_CaloIdVT_GsfTrkIdT_ || ev->HLT_Ele32_WPTight_Gsf_ ) ? true : false;
      	passDLtriggers_el = ( ev->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_) ? true : false;

     	passDLtriggers_emu = ( (ev->HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_ ) || (ev->HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_) ); // (ev->HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_ )

    }
	///////////////////////////////////////////////////////////////////////

}

void leptonHandler::Event(EventVars* eve, bool passDebug, bool passTrigSF)
{
  	// *** 1. Intialize some things
  	ev = eve;
  	isDebug = passDebug;
  	isTrigSF = passTrigSF;
  	passSLCuts_el = false;
  	passSLCuts_mu = false;
  	passDLCuts_el = false;
  	passDLCuts_mu = false;
  	passDLCuts_emu = false;
  	nLeptons = ev->lepton_pt.size();
  	nMuons = 0;
  	leadPt_mu = -99;
  	leadEta_mu = -99;
  	leadRelIso_mu = -99;
  	leadIndex_mu = -99;
  	subPt_mu = -99;
  	subEta_mu = -99;
  	subRelIso_mu = -99;
  	subIndex_mu = -99;
  	nElectrons = 0;
  	leadPt_el = -99;
  	leadEta_el = -99;
  	leadIndex_el = -99;
  	subPt_el = -99;
  	subEta_el = -99;
  	subRelIso_el = -99;
  	subIndex_el = -99;
  	leadCharge_el = -99;
  	subCharge_el = -99;
  	leadCharge_mu = -99;
  	subCharge_mu = -99;
  	leadIDSF_el = 1.;
  	leadRecoIsoSF_el = 1.;
  	subIDSF_el = 1.;
  	subRecoIsoSF_el = 1.;
  	leadIDSF_mu = 1.;
  	leadRecoIsoSF_mu = 1.;
  	subIDSF_mu = 1.;
  	subRecoIsoSF_mu = 1.;
  	mll = -99;

  	b_periodDep__HLT_IsoMu24_eta2p1 = false;
  	b_periodDep__doubleMu_noMass = false;
  	b_periodDep__doubleMu_withMass = false;

  	//h_mu_cutflow->Fill("Event", 1);

  	// *** 2. Check trigger
  	checkHLTTriggers();

  	// *** 3. Start handling business! (or at least muons)
  	if (nLeptons > 0 ) {
    		// ** A. Apply object selection
    		applyMuonCuts();
    		applyElectronCuts();
    		// ** B. Check what category an event falls into: el/mu, SL/DL
    		checkCategoryCuts();
  	}
}
