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
 
    int RecoLepID;

    int nMuon;
    int nElectron;

    bool Lep_triggers;
    bool Met_triggers;
    bool HLT_IsoMu24_ ;
    bool HLT_IsoTkMu24_;
    bool HLT_Mu50_;
    bool HLT_IsoMu27_;
    bool HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_;
    bool HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_;
    bool HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_;
    bool HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_;
    bool HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_;
    bool HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_;
    bool HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_;
    bool HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_;
    bool HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_;
    bool HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_;
    bool HLT_Ele27_WPTight_Gsf_;
    bool HLT_Ele115_CaloIdVT_GsfTrkIdT_;
    bool HLT_Ele32_WPTight_Gsf_;
    bool HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_;
    bool HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_;
    bool HLT_DoubleEle33_CaloIdL_MW_;
    bool HLT_PFMET300_;
    bool HLT_MET200_;
    bool HLT_PFHT300_PFMET110_;
    bool HLT_PFMET170_HBHECleaned_;
    bool HLT_PFMET120_PFMHT120_IDTight_;
    bool HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_;
    bool HLT_PFMET200_HBHECleaned_;
    bool HLT_PFMET200_HBHE_BeamHaloCleaned_;
    bool HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned_;
    bool HLT_PFMET120_PFMHT120_IDTight_PFHT60_;
    bool HLT_PFHT500_PFMET100_PFMHT100_IDTight_;
    bool HLT_PFHT700_PFMET85_PFMHT85_IDTight_;
    bool HLT_PFHT800_PFMET75_PFMHT75_IDTight_;
    bool HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60_;




   bool passMETFilters;
  
  double evtWeight;
   int run;
  int lumi;
  long evt;


  float LepLep_deltaR;
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

    RecoLepID = 0;
    nMuon = 0;
    nElectron = 0;

    Lep_triggers = false;
    Met_triggers = false;
    HLT_IsoMu24_ = false; 
    HLT_IsoTkMu24_= false; 
    HLT_Mu50_= false; 
    HLT_IsoMu27_= false; 
    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_= false; 
    HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_= false; 
    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_= false; 
    HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_= false; 
    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_= false; 
    HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_= false; 
    HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_= false; 
    HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_= false; 
    HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_= false; 
    HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_= false; 
    HLT_Ele27_WPTight_Gsf_= false; 
    HLT_Ele115_CaloIdVT_GsfTrkIdT_= false; 
    HLT_Ele32_WPTight_Gsf_= false; 
    HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_= false; 
    HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_= false; 
    HLT_DoubleEle33_CaloIdL_MW_= false; 
    HLT_PFMET300_= false; 
    HLT_MET200_= false; 
    HLT_PFHT300_PFMET110_= false; 
    HLT_PFMET170_HBHECleaned_= false; 
    HLT_PFMET120_PFMHT120_IDTight_= false; 
    HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_= false; 
    HLT_PFMET200_HBHECleaned_= false; 
    HLT_PFMET200_HBHE_BeamHaloCleaned_= false; 
    HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned_= false; 
    HLT_PFMET120_PFMHT120_IDTight_PFHT60_= false; 
    HLT_PFHT500_PFMET100_PFMHT100_IDTight_= false; 
    HLT_PFHT700_PFMET85_PFMHT85_IDTight_= false; 
    HLT_PFHT800_PFMET75_PFMHT75_IDTight_= false; 
    HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60_= false; 

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

  LepLep_deltaR = -1;

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
