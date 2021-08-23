#include "../include/jetMetHandler.h"


jetMetHandler::jetMetHandler()
{
	passLeadingJetCuts = false;
	passDLJetMetCuts = false;
	passSLJetMetCuts = false;
	passNjetsCuts = -1;
	passNPVCuts = -1;
	passMETCuts = -1;
	leadPt = -99;
	leadEta = -99;
	leadPhi = -99;
	subPt = -99;
	subEta = -99;
	subPhi = -99;
    era_ = 0;
	MET = -99;
	MET_phi = -99;
	nPV = -99;
	leadIndex = -99;
	subIndex = -99;
	nPreCutJets = 0;
	nJets = 0;
	nBTags = 0;
	ttbarJetID = -99;
	passOneMETTrigger = false;
	passAllMETTriggers = false;
	metXTriggerBits = "";
	PU_SF = 1.;
	genweight = 1.;
	evtWeight = 1.;

	// h_jet_cutflow  = new TH1D("h_jet_cutflow", "h_jet_cutflow", 4, 0, 4);
	// h_jet_n        = new TH1D("h_jet_n", "h_jet_n", 12, 0, 12);
	// h_met_passXtriggers = new TH1D("h_met_passXtriggers", "h_met_passXtriggers", 8, 0, 8);
	// h_met_passOnlyXtrigger = new TH1D("h_met_passOnlyXtrigger", "h_met_passOnlyXtrigger", 8, 0, 8);
}

jetMetHandler::~jetMetHandler() {}

void jetMetHandler::test()
{
	std::cout << "Test!" << endl;
}

void jetMetHandler::parseMETTriggerLogic()
{

	// store all trigger bits in single string
	ev->HLT_PFMET120_PFMHT120_IDTight ? metXTriggerBits.append("1") : metXTriggerBits.append("0");
	// ev->passHLT_PFMETTypeOne120_PFMHT120_IDTight_v_? metXTriggerBits.append("1") : metXTriggerBits.append("0");
	metXTriggerBits.append("0");
	ev->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ? metXTriggerBits.append("1") : metXTriggerBits.append("0");
	ev->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ? metXTriggerBits.append("1") : metXTriggerBits.append("0");
	ev->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ? metXTriggerBits.append("1") : metXTriggerBits.append("0");
	// ev->passHLT_CaloMET250_HBHECleaned_v_? metXTriggerBits.append("1") : metXTriggerBits.append("0");
	metXTriggerBits.append("0");
	ev->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ? metXTriggerBits.append("1") : metXTriggerBits.append("0");
	ev->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ? metXTriggerBits.append("1") : metXTriggerBits.append("0");

	// Fill plots
	// if ( metXTriggerBits.at(0) == '1' ) h_met_passXtriggers->Fill("PFMET120_PFMHT120_IDTight", 1);
	// if ( metXTriggerBits.at(1) == '1' ) h_met_passXtriggers->Fill("PFMETTypeOne120_PFMHT120_IDTight", 1);
	// if ( metXTriggerBits.at(2) == '1' ) h_met_passXtriggers->Fill("PFHT500_PFMET100_PFMHT100_IDTight", 1);
	// if ( metXTriggerBits.at(3) == '1' ) h_met_passXtriggers->Fill("PFHT700_PFMET85_PFMHT85_IDTight", 1);
	// if ( metXTriggerBits.at(4) == '1' ) h_met_passXtriggers->Fill("PFHT800_PFMET75_PFMHT75_IDTight", 1);
	// if ( metXTriggerBits.at(5) == '1' ) h_met_passXtriggers->Fill("CaloMET250_HBHECleaned", 1);
	// if ( metXTriggerBits.at(6) == '1' ) h_met_passXtriggers->Fill("PFMET250_HBHECleaned", 1);
	// if ( metXTriggerBits.at(7) == '1' ) h_met_passXtriggers->Fill("PFMET200_HBHE_BeamHaloCleaned", 1);

	// Fill plots
	// if ( metXTriggerBits.find("10000000") != string::npos ) h_met_passOnlyXtrigger->Fill("PFMET120_PFMHT120_IDTight", 1);
	// if ( metXTriggerBits.find("01000000") != string::npos ) h_met_passOnlyXtrigger->Fill("PFMETTypeOne120_PFMHT120_IDTight", 1);
	// if ( metXTriggerBits.find("00100000") != string::npos ) h_met_passOnlyXtrigger->Fill("PFHT500_PFMET100_PFMHT100_IDTight", 1);
	// if ( metXTriggerBits.find("00010000") != string::npos ) h_met_passOnlyXtrigger->Fill("PFHT700_PFMET85_PFMHT85_IDTight", 1);
	// if ( metXTriggerBits.find("00001000") != string::npos ) h_met_passOnlyXtrigger->Fill("PFHT800_PFMET75_PFMHT75_IDTight", 1);
	// if ( metXTriggerBits.find("00000100") != string::npos ) h_met_passOnlyXtrigger->Fill("CaloMET250_HBHECleaned", 1);
	// if ( metXTriggerBits.find("00000010") != string::npos ) h_met_passOnlyXtrigger->Fill("PFMET250_HBHECleaned", 1);
	// if ( metXTriggerBits.find("00000001") != string::npos ) h_met_passOnlyXtrigger->Fill("PFMET200_HBHE_BeamHaloCleaned", 1);

	// set boolean of passing desired X triggers
	passAllMETTriggers = metXTriggerBits.find('1') != string::npos ? true : false; // pass any X trigger
	passOneMETTrigger = metXTriggerBits.at(0) == '1' ? true : false; // pass PFMET120_PFMHT120_IDTight

}


void jetMetHandler::parseMETTriggerLogic_2017()
{

	// *** FROM CARMEN *** 07-01-18 --> triggers used in 2016 efficiency calculations
	//"HLT_PFHT300_PFMET110_v" "HLT_MET200_v" "HLT_PFMET300_v" "HLT_PFMET120_PFMHT120_IDTight_v" "HLT_PFMET170_HBHECleaned_v"

	// store all trigger bits in single string

	ev->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ? metXTriggerBits.append("1") : metXTriggerBits.append("0");
	ev->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ? metXTriggerBits.append("1") : metXTriggerBits.append("0");
	ev->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ? metXTriggerBits.append("1") : metXTriggerBits.append("0");
	ev->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ ? metXTriggerBits.append("1") : metXTriggerBits.append("0");
	ev->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ? metXTriggerBits.append("1") : metXTriggerBits.append("0");

	// Fill plots
	// if ( metXTriggerBits.at(0) == '1' ) h_met_passXtriggers->Fill("PFHT500_PFMET100_PFMHT100_IDTight", 1);
	// if ( metXTriggerBits.at(1) == '1' ) h_met_passXtriggers->Fill("PFHT700_PFMET85_PFMHT85_IDTight", 1);
	// if ( metXTriggerBits.at(2) == '1' ) h_met_passXtriggers->Fill("PFHT800_PFMET75_PFMHT75_IDTight", 1);
	// if ( metXTriggerBits.at(3) == '1' ) h_met_passXtriggers->Fill("PFMET120_PFMHT120_IDTight", 1);
	// if ( metXTriggerBits.at(4) == '1' ) h_met_passXtriggers->Fill("PFMET250_HBHECleaned", 1);

	// Fill plots
	// if ( metXTriggerBits.find("10000") != string::npos ) h_met_passOnlyXtrigger->Fill("PFHT500_PFMET100_PFMHT100_IDTight", 1);
	// if ( metXTriggerBits.find("01000") != string::npos ) h_met_passOnlyXtrigger->Fill("PFHT700_PFMET85_PFMHT85_IDTight", 1);
	// if ( metXTriggerBits.find("00100") != string::npos ) h_met_passOnlyXtrigger->Fill("PFHT800_PFMET75_PFMHT75_IDTight", 1);
	// if ( metXTriggerBits.find("00010") != string::npos ) h_met_passOnlyXtrigger->Fill("PFMET120_PFMHT120_IDTight", 1);
	// if ( metXTriggerBits.find("00001") != string::npos ) h_met_passOnlyXtrigger->Fill("PFMET250_HBHECleaned", 1);

	// set boolean of passing desired X triggers
	passAllMETTriggers = metXTriggerBits.find('1') != string::npos ? true : false; // pass any X trigger

	passOneMETTrigger = metXTriggerBits.at(3) == '1' ? true : false; // pass PFMET120_PFMHT120_IDTight

}


// void jetMetHandler::parseMETTriggerLogic_v3(){
//
// 	// *** FROM CARMEN *** 07-01-18 --> triggers used in 2016 efficiency calculations
// 	//"HLT_PFHT300_PFMET110_v" "HLT_MET200_v" "HLT_PFMET300_v" "HLT_PFMET120_PFMHT120_IDTight_v" "HLT_PFMET170_HBHECleaned_v"
//
// 	// store all trigger bits in single string
//
// 	ev->passHLT_PFHT500_PFMET100_PFMHT100_IDTight_v_? metXTriggerBits.append("1") : metXTriggerBits.append("0");
// 	ev->passHLT_PFHT700_PFMET85_PFMHT85_IDTight_v_? metXTriggerBits.append("1") : metXTriggerBits.append("0");
// 	ev->passHLT_PFHT800_PFMET75_PFMHT75_IDTight_v_? metXTriggerBits.append("1") : metXTriggerBits.append("0");
// 	ev->passHLT_PFMET120_PFMHT120_IDTight_v_ ? metXTriggerBits.append("1") : metXTriggerBits.append("0");
// 	ev->passHLT_PFMET250_HBHECleaned_v_? metXTriggerBits.append("1") : metXTriggerBits.append("0");
// 	ev->passHLT_PFHT250_v_? metXTriggerBits.append("1") : metXTriggerBits.append("0");
//
// 	// Fill plots
// 	if ( metXTriggerBits.at(0) == '1' ) h_met_passXtriggers->Fill("PFHT500_PFMET100_PFMHT100_IDTight", 1);
// 	if ( metXTriggerBits.at(1) == '1' ) h_met_passXtriggers->Fill("PFHT700_PFMET85_PFMHT85_IDTight", 1);
// 	if ( metXTriggerBits.at(2) == '1' ) h_met_passXtriggers->Fill("PFHT800_PFMET75_PFMHT75_IDTight", 1);
// 	if ( metXTriggerBits.at(3) == '1' ) h_met_passXtriggers->Fill("PFMET120_PFMHT120_IDTight", 1);
// 	if ( metXTriggerBits.at(4) == '1' ) h_met_passXtriggers->Fill("PFMET250_HBHECleaned", 1);
// 	if ( metXTriggerBits.at(5) == '1' ) h_met_passXtriggers->Fill("PFHT250", 1);
//
// 	// Fill plots
// 	if ( metXTriggerBits.find("100000") != string::npos ) h_met_passOnlyXtrigger->Fill("PFHT500_PFMET100_PFMHT100_IDTight", 1);
// 	if ( metXTriggerBits.find("010000") != string::npos ) h_met_passOnlyXtrigger->Fill("PFHT700_PFMET85_PFMHT85_IDTight", 1);
// 	if ( metXTriggerBits.find("001000") != string::npos ) h_met_passOnlyXtrigger->Fill("PFHT800_PFMET75_PFMHT75_IDTight", 1);
// 	if ( metXTriggerBits.find("000100") != string::npos ) h_met_passOnlyXtrigger->Fill("PFMET120_PFMHT120_IDTight", 1);
// 	if ( metXTriggerBits.find("000010") != string::npos ) h_met_passOnlyXtrigger->Fill("PFMET250_HBHECleaned", 1);
// 	if ( metXTriggerBits.find("000001") != string::npos ) h_met_passOnlyXtrigger->Fill("PFH250", 1);
//
// 	// set boolean of passing desired X triggers
// 	passAllMETTriggers = metXTriggerBits.find('1') != string::npos ? true : false; // pass any X trigger
//
// 	passOneMETTrigger = metXTriggerBits.at(3) == '1' ? true : false; // pass PFMET120_PFMHT120_IDTight
// }

void jetMetHandler::parseMETTriggerLogic_2016(){

	// This is the MET trigger logic for the 2016 Trigger SF derivation

	ev->HLT_MET200? metXTriggerBits.append("1") : metXTriggerBits.append("0");
	ev->HLT_PFMET120_PFMHT120_IDTight? metXTriggerBits.append("1") : metXTriggerBits.append("0");
	ev->HLT_PFMET170_HBHECleaned? metXTriggerBits.append("1") : metXTriggerBits.append("0");
	ev->HLT_PFMET300 ? metXTriggerBits.append("1") : metXTriggerBits.append("0");
	ev->HLT_PFHT300_PFMET110? metXTriggerBits.append("1") : metXTriggerBits.append("0");
	//ev->passPFMET110_HLT_MET200_v_? metXTriggerBits.append("1") : metXTriggerBits.append("0");
	ev->HLT_PFMETNoMu120_PFMHTNoMu120_IDTight? metXTriggerBits.append("1") : metXTriggerBits.append("0");

	// Fill plots
	// if ( metXTriggerBits.at(0) == '1' ) h_met_passXtriggers->Fill("MET200", 1);
	// if ( metXTriggerBits.at(1) == '1' ) h_met_passXtriggers->Fill("PFMET120_PFMHT120_IDTight", 1);
	// if ( metXTriggerBits.at(2) == '1' ) h_met_passXtriggers->Fill("PFMET170_HBHECleaned", 1);
	// if ( metXTriggerBits.at(3) == '1' ) h_met_passXtriggers->Fill("PFMET300", 1);
	// if ( metXTriggerBits.at(4) == '1' ) h_met_passXtriggers->Fill("PFHT300_PFMET110", 1);
	// //if ( metXTriggerBits.at(5) == '1' ) h_met_passXtriggers->Fill("PFMET110_HLT_MET200", 1);
	// if ( metXTriggerBits.at(5) == '1' ) h_met_passXtriggers->Fill("PFMETNoMu120_PFMHTNoMu120_IDTight", 1);

	// Fill plots
	// if ( metXTriggerBits.find("100000") != string::npos ) h_met_passOnlyXtrigger->Fill("MET200", 1);
	// if ( metXTriggerBits.find("010000") != string::npos ) h_met_passOnlyXtrigger->Fill("PFMET120_PFMHT120_IDTight", 1);
	// if ( metXTriggerBits.find("001000") != string::npos ) h_met_passOnlyXtrigger->Fill("PFMET170_HBHECleaned", 1);
	// if ( metXTriggerBits.find("000100") != string::npos ) h_met_passOnlyXtrigger->Fill("PFMET300", 1);
	// if ( metXTriggerBits.find("000010") != string::npos ) h_met_passOnlyXtrigger->Fill("PFHT300_PFMET110", 1);
	// //if ( metXTriggerBits.find("0000010") != string::npos ) h_met_passOnlyXtrigger->Fill("PFMET110_HLT_MET200", 1);
	// if ( metXTriggerBits.find("000001") != string::npos ) h_met_passOnlyXtrigger->Fill("PFMETNoMu120_PFMHTNoMu120_IDTight", 1);

	// set boolean of passing desired X triggers
	passAllMETTriggers = metXTriggerBits.find('1') != string::npos ? true : false; // pass any X trigger

}


void jetMetHandler::parseMETTriggerLogic_2018(){

	// This is the MET trigger logic for the 2018 Trigger SF derivation

	ev->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ? metXTriggerBits.append("1") : metXTriggerBits.append("0");
	ev->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ ? metXTriggerBits.append("1") : metXTriggerBits.append("0");
	ev->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ? metXTriggerBits.append("1") : metXTriggerBits.append("0");
	ev->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ? metXTriggerBits.append("1") : metXTriggerBits.append("0");
	ev->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ? metXTriggerBits.append("1") : metXTriggerBits.append("0");
	ev->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ? metXTriggerBits.append("1") : metXTriggerBits.append("0");
	ev->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ? metXTriggerBits.append("1") : metXTriggerBits.append("0");
	ev->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ? metXTriggerBits.append("1") : metXTriggerBits.append("0");
	ev->HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ? metXTriggerBits.append("1") : metXTriggerBits.append("0");

	// Fill plots
	// if ( metXTriggerBits.at(0) == '1' ) h_met_passXtriggers->Fill("PFMET120_PFMHT120_IDTight", 1);
	// if ( metXTriggerBits.at(1) == '1' ) h_met_passXtriggers->Fill("PFMET200_HBHE_BeamHaloCleaned", 1);
	// if ( metXTriggerBits.at(2) == '1' ) h_met_passXtriggers->Fill("PFMETTypeOne200_HBHE_BeamHaloCleaned", 1);
	// if ( metXTriggerBits.at(3) == '1' ) h_met_passXtriggers->Fill("PFMETNoMu120_PFMHTNoMu120_IDTight", 1);
	// if ( metXTriggerBits.at(4) == '1' ) h_met_passXtriggers->Fill("PFMET120_PFMHT120_IDTight_PFHT60", 1);
	// if ( metXTriggerBits.at(5) == '1' ) h_met_passXtriggers->Fill("PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60", 1);
	// if ( metXTriggerBits.at(6) == '1' ) h_met_passXtriggers->Fill("PFHT500_PFMET100_PFMHT100_IDTight", 1);
	// if ( metXTriggerBits.at(7) == '1' ) h_met_passXtriggers->Fill("PFHT700_PFMET85_PFMHT85_IDTight", 1);
	// if ( metXTriggerBits.at(8) == '1' ) h_met_passXtriggers->Fill("PFHT800_PFMET75_PFMHT75_IDTight", 1);


	// Fill plots
	// if ( metXTriggerBits.find("100000000") != string::npos ) h_met_passOnlyXtrigger->Fill("PFMET120_PFMHT120_IDTight", 1);
	// if ( metXTriggerBits.find("010000000") != string::npos ) h_met_passOnlyXtrigger->Fill("PFMET200_HBHE_BeamHaloCleaned", 1);
	// if ( metXTriggerBits.find("001000000") != string::npos ) h_met_passOnlyXtrigger->Fill("PFMETTypeOne200_HBHE_BeamHaloCleaned", 1);
	// if ( metXTriggerBits.find("000100000") != string::npos ) h_met_passOnlyXtrigger->Fill("PFMETNoMu120_PFMHTNoMu120_IDTight", 1);
	// if ( metXTriggerBits.find("000010000") != string::npos ) h_met_passOnlyXtrigger->Fill("PFMET120_PFMHT120_IDTight_PFHT60", 1);
	// if ( metXTriggerBits.find("000001000") != string::npos ) h_met_passOnlyXtrigger->Fill("PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60", 1);
	// if ( metXTriggerBits.find("000000100") != string::npos ) h_met_passOnlyXtrigger->Fill("PFHT500_PFMET100_PFMHT100_IDTight", 1);
	// if ( metXTriggerBits.find("000000010") != string::npos ) h_met_passOnlyXtrigger->Fill("PFHT700_PFMET85_PFMHT85_IDTight", 1);
	// if ( metXTriggerBits.find("000000001") != string::npos ) h_met_passOnlyXtrigger->Fill("PFHT800_PFMET75_PFMHT75_IDTight", 1);


	// set boolean of passing desired X triggers
	passAllMETTriggers = metXTriggerBits.find('1') != string::npos ? true : false; // pass any X trigger

}
void jetMetHandler::applyMETCuts()
{

    if(era_==2016){
        parseMETTriggerLogic_2016();
    }
    if(era_==2017){
        parseMETTriggerLogic_2017();
    }
    if(era_==2018){
        parseMETTriggerLogic_2018();
    }

	// set MET publically accessible MET
	MET = ev->MET_Type1xy_sync;
	MET_phi = ev->MET_Type1xy_phi_sync;

	PU_SF = ev->puSF;
	genweight = ev->genweight;
	evtWeight = ev->evtWeight;


}

void jetMetHandler::applyJetCuts()
{

	for (unsigned int j = 0; j < ev->jet_pt.size(); j++){

		if (isDebug)
			cout << "\n ev->evt = " << ev->evt << " and jet " << j << " has pt " << ev->jet_pt[j] << " , eta " << ev->jet_eta[j] << " , phi " << ev->jet_phi[j] <<endl;

		// h_jet_cutflow->Fill("Jet", 1);
		// Cut 1: pT > 30 GeV
		//if( !(ev->jet_pt[j] > 30.) ) continue;
		// h_jet_cutflow->Fill("p_{T} > 30", 1);

		// Cut 2: |ETA| < 2.4
		//if( !(abs(ev->jet_eta[j]) < 2.4) ) continue;
		// h_jet_cutflow->Fill("|#eta| < 2.4", 1);

		// Cut 3: Lepton overlap removal (R=0.4)
		//if ( vetoLeptonJetOverlapRemoval(j) ) continue;
		// h_jet_cutflow->Fill("dR(l, j) > 0.4", 1);


		nJets++;

		if (isDebug)
			cout << "\n ev->evt = " << ev->evt << " and jet " << j << " has pt " << ev->jet_pt[j] << " , eta " << ev->jet_eta[j] << " , phi " << ev->jet_phi[j] <<endl;
		// set leading/subleading indices if appropriate
		setLeadSubleadIndices(j, leadIndex, subIndex);
	}


  	// *** ?. Wrap-up
  	// h_jet_n->Fill( nJets );
  	if (leadIndex != -99){
    		leadPt      = ev->jet_pt[leadIndex];
    		leadEta     = ev->jet_eta[leadIndex];
    		leadPhi     = ev->jet_phi[leadIndex];
  	}
  	if (subIndex != -99){
    		subPt      = ev->jet_pt[subIndex];
    		subEta     = ev->jet_eta[subIndex];
    		subPhi     = ev->jet_phi[subIndex];
  	}
	if(nJets>0){  
  	//if (leadPt > 30 && subPt > 30) {
    		passLeadingJetCuts = true;
    		// if (nJets >= 2 && nBTags >= 1 && ( ((lTool.passDLCuts_mu || lTool.passDLCuts_el) && MET>40) || (lTool.passDLCuts_emu) )) passDLJetMetCuts = true;
    		// if (nJets >= 2 && ( ((lTool.passDLCuts_mu || lTool.passDLCuts_el) && MET>40) || (lTool.passDLCuts_emu) )) passDLJetMetCuts = true;
    		// if (nJets >= 2 && ( ((lTool.passDLCuts_mu || lTool.passDLCuts_el) && MET>30) || (lTool.passDLCuts_emu) )) passDLJetMetCuts = true;
    		// if (nJets >= 2 && ( ((lTool.passDLCuts_mu || lTool.passDLCuts_el)) || (lTool.passDLCuts_emu) )) passDLJetMetCuts = true;
    		// if (( ((lTool.passDLCuts_mu || lTool.passDLCuts_el)) || (lTool.passDLCuts_emu) )) passDLJetMetCuts = true;
    		//if (( ((lTool.passDLCuts_mu || lTool.passDLCuts_el)) || (lTool.passDLCuts_emu) )) passDLJetMetCuts = true && ev->GoodFirstPV && ev-> passMETFilters;;
    		// if (nJets >= 4 && nBTags >= 2 && MET > 20) passSLJetMetCuts = true;
    		if (nJets >= 4 && MET > 20) passSLJetMetCuts = true;
  	}

  	// ** Secondary true condition if running in trigSF mode
  	// if ( isTrigSF && ( ((lTool.passDLCuts_mu || lTool.passDLCuts_el) && MET>40.) || (lTool.passDLCuts_emu) )) {
  	// if ( isTrigSF && ( ((lTool.passDLCuts_mu || lTool.passDLCuts_el) && MET>30.) || (lTool.passDLCuts_emu) )) {
  	if ( isTrigSF && ( (lTool.passDLCuts_mu || lTool.passDLCuts_el) || (lTool.passDLCuts_emu) )) {
	       passDLJetMetCuts = true;
	    //passDLJetMetCuts = true && ev->GoodFirstPV && ev-> passMETFilters;;
        	if( nJets >=3 ) passNjetsCuts = 1;
        	if( nJets <3 ) passNjetsCuts = 0;
        	if( nPV >=30 ) passNPVCuts = 1;
        	if( nPV <30 ) passNPVCuts = 0;
        	if( MET >=150 ) passMETCuts = 1;
        	if( MET <150 ) passMETCuts = 0;
	}
}

void jetMetHandler::Event(EventVars* eve, leptonHandler lep, bool passDebug, bool passTrigSF)
{
	// *** 1. Intialize some things
	ev = eve;
	lTool = lep;
	isDebug = passDebug;
	isTrigSF = passTrigSF;
	passLeadingJetCuts = false;
	passDLJetMetCuts = false;
	passSLJetMetCuts = false;
    passNjetsCuts = -1;
    passNPVCuts = -1;
    passMETCuts = -1;
	nPreCutJets = ev->jet_pt.size();
	nJets = 0;
	nBTags = 0;
	ttbarJetID = -99;
	leadIndex = -1;
	subIndex = -1;
	leadPt = -99;
	leadEta = -99;
	leadPhi = -99;
	subPt = -99;
	subEta = -99;
	subPhi = -99;
	MET = -99;
	MET_phi = -99;
	nPV = ev->numPVs;
	passOneMETTrigger = false;
	passAllMETTriggers = false;
	metXTriggerBits = "";

	// *** 2. Start handling business! (or at least jets and MET)
	applyMETCuts();
	if (nPreCutJets > 0 ) {
		applyJetCuts();
  	}
}

void jetMetHandler::setLeadSubleadIndices(int l, int& lead, int& sub)
{
	// *** 0. Temporary variables
	double d_leadPt = (lead == -99) ? -99 : ev->jet_pt[lead];
  	double d_subPt  = (sub == -99) ? -99  : ev->jet_pt[sub];

  	// *** 1. Set leading lepton if appropriate
  	if (ev->jet_pt[l] > d_leadPt) {
    	// ** A. If already have first good jet, set old lead lepton to sub
    		if (d_leadPt != -99){
      			sub = lead;
    		}
    	// ** B. set new leading jet to leading
    		lead = l;
  	}
  	else if (ev->jet_pt[l] < d_leadPt && ev->jet_pt[l] > d_subPt) {
    	// ** C. New lepton not greater than leading but greater than sub
    		sub = l;
  	}
}

bool jetMetHandler::vetoLeptonJetOverlapRemoval(int j)
{
	double OverlapCut = 0.4;

  	// TLorentzVector *v_lead = new TLorentzVector();
  	// TLorentzVector *v_sub  = new TLorentzVector();
  	// TLorentzVector *v_jet  = new TLorentzVector();
  	TLorentzVector v_lead = TLorentzVector(0.,0.,0.,0.);
  	TLorentzVector v_sub  = TLorentzVector(0.,0.,0.,0.);
  	TLorentzVector v_jet  = TLorentzVector(0.,0.,0.,0.);

  	int i_lead = -99;
  	int i_sub = -99;
        double deltaR_j_lead = 9999;
        double deltaR_j_sub = 9999;


  	if (lTool.passDLCuts_mu) {
    		i_lead = lTool.leadIndex_mu;
    		i_sub  = lTool.subIndex_mu;
  	}
  	if (lTool.passDLCuts_el) {
    		i_lead = lTool.leadIndex_el;
    		i_sub  = lTool.subIndex_el;
  	}
  	if (lTool.passDLCuts_emu) { // take leading index from each lepton category, internal i_* name misleading in this case for i_sub
    		i_lead = lTool.leadIndex_el;
    		i_sub  = lTool.leadIndex_mu;
  	}

        if(i_lead !=-99 && i_sub !=-99){

                // v_lead->SetPtEtaPhiE( ev->lepton_pt_[i_lead], ev->lepton_eta_[i_lead], ev->lepton_phi_[i_lead], ev->lepton_e_[i_lead] );
                // v_sub->SetPtEtaPhiE( ev->lepton_pt_[i_sub], ev->lepton_eta_[i_sub], ev->lepton_phi_[i_sub], ev->lepton_e_[i_sub] );
                // v_jet->SetPtEtaPhiM( ev->jet_pt_[j], ev->jet_eta_[j], ev->jet_phi_[j], ev->jet_m_[j] );
                v_lead.SetPtEtaPhiE( ev->lepton_pt[i_lead], ev->lepton_eta[i_lead], ev->lepton_phi[i_lead], ev->lepton_e[i_lead] );
                v_sub.SetPtEtaPhiE( ev->lepton_pt[i_sub], ev->lepton_eta[i_sub], ev->lepton_phi[i_sub], ev->lepton_e[i_sub] );
                v_jet.SetPtEtaPhiM( ev->jet_pt[j], ev->jet_eta[j], ev->jet_phi[j], ev->jet_m[j] );

                // deltaR_j_lead = v_lead->DeltaR(*v_jet);
                // deltaR_j_sub  = v_sub->DeltaR(*v_jet);
                deltaR_j_lead = v_lead.DeltaR(v_jet);
                deltaR_j_sub  = v_sub.DeltaR(v_jet);
        }

	//cout<<"hey you"<<endl;

  	if( deltaR_j_lead < OverlapCut || deltaR_j_sub < OverlapCut)
    		return true;
  	else
    		return false;
  	return false;
}
