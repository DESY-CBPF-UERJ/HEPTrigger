#ifndef ttH_LeptonPlusJets_AnalysisCode_EventVars_h
#define ttH_LeptonPlusJets_AnalysisCode_EventVars_h
//
// Dependencies (#includes)
//
#include <iostream>
#include <vector>
#include "TLorentzVector.h"

#ifdef __MAKECINT__
#pragma link C++ class std::vector< TLorentzVector >+;
#endif

typedef std::vector<float> vfloat;
typedef std::vector<string> vstring;
typedef std::vector<bool> vbool;
typedef std::vector<int> vint;
typedef std::vector< TLorentzVector > vecTLorentzVector;

//
// Utility Class for Handling Event Variables
//

struct EventVars{


  //////////////////////////////////////////////////////////////////////////
  ///  Tree branches/leaves
  //////////////////////////////////////////////////////////////////////////

  explicit EventVars(){ };
 



  bool HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ;             ////
  bool HLT_Ele115_CaloIdVT_GsfTrkIdT;                         ////
  bool HLT_PFMET300 ;
  bool HLT_MET200 ;
  bool HLT_PFHT300_PFMET110;
  bool HLT_PFMET170_HBHECleaned;
  bool HLT_PFMET120_PFMHT120_IDTight ;
  bool HLT_PFMETNoMu120_PFMHTNoMu120_IDTight;


  bool HLT_Ele27_WPTight_Gsf;
  bool HLT_IsoTkMu24;
  bool HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL;
  bool HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ;
  bool HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ;


  bool HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL ;
  bool HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ ;
  bool HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL ;
  bool HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ ; 
  bool HLT_IsoMu24;
  bool HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL ;



   bool passMETFilters;
  
  double evtWeight;
   int run;
  int lumi;
  long evt;

  float   puSF;
  bool    GoodFirstPV;
  Int_t   numPVs;

  vint lepton_isMuon;
  vint lepton_charge;
  vint lepton_isTight;
  vfloat lepton_pt;
  vfloat lepton_eta;
  vfloat lepton_phi;
  vfloat lepton_e;
  //vint lepton_e;
  vfloat lepton_relIso;
  vfloat lepton_scEta;
  vfloat lepton_IDSF;
  vfloat lepton_recoIsoSF;
  vfloat lepton_energyCorr;

  float genweight;

  Float_t MET;
  Float_t MET_phi;
  Float_t MET_Type1xy;
  Float_t MET_Type1xy_phi;
  Float_t MET_Type1xy_sync;
  Float_t MET_Type1xy_phi_sync;

  vfloat jet_RegFactor_;

  vfloat jet_pt;
  vfloat jet_eta;
  vfloat jet_phi;
  vfloat jet_m;



  void initialize();

};


typedef std::vector<EventVars> vEventVars;


void EventVars::initialize(){



  

//Triggers do Eletron
  HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = false;                  ///
  HLT_Ele115_CaloIdVT_GsfTrkIdT = false;                              ///
  HLT_Ele27_WPTight_Gsf = false;
//TRiggers do Muon
  HLT_IsoTkMu24 =false;
  HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL = false;
  HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ = false;
  HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ = false;
//Triggers do MET
  HLT_PFMET300 = false;
  HLT_MET200 = false;
  HLT_PFHT300_PFMET110 = false;
  HLT_PFMET170_HBHECleaned = false;
  HLT_PFMET120_PFMHT120_IDTight = false;
  HLT_PFMETNoMu120_PFMHTNoMu120_IDTight = false;
//Triggers dos ElMu
  HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL = false ;
  HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = false;
  HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL = false;
  HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ = false; 
  HLT_IsoMu24 = false;
  HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL = false;

  //gSystem->cd("/home/matheus/Desktop/TChain/");
   passMETFilters = false;

//////////////////////////////////////////////////////
  evtWeight = 0;
////////////////////////////////////////////////////
   run  = -99;
  lumi = -99;
  evt = -99;

  GoodFirstPV = false;
  numPVs = -99;
  genweight = -999.;

  lepton_isMuon.clear();
  lepton_charge.clear();
  lepton_isTight.clear();
  lepton_pt.clear();
  lepton_eta.clear();
  lepton_phi.clear();
  lepton_e.clear();
  lepton_relIso.clear();
  lepton_scEta.clear();
  lepton_IDSF.clear();
  lepton_recoIsoSF.clear();

    MET = -99.9;
    MET_phi = -99.9;

    MET_Type1xy = -99.9;
    MET_Type1xy_phi = -99.9;

    MET_Type1xy_sync = -99.9;
    MET_Type1xy_phi_sync = -99.9;

    jet_pt .clear();
    jet_phi.clear();
    jet_eta.clear();
    jet_m.clear();
    jet_RegFactor_.clear();

  return;
}
#endif
