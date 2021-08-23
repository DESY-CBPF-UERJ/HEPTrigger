#ifndef ttH_LeptonPlusJets_AnalysisCode_YggdrasilEventVars_h
#define ttH_LeptonPlusJets_AnalysisCode_YggdrasilEventVars_h
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

struct yggdrasilEventVars{


  //////////////////////////////////////////////////////////////////////////
  ///  Tree branches/leaves
  //////////////////////////////////////////////////////////////////////////

  explicit yggdrasilEventVars(){ };
  // Int_t   additionalJetEventId_;
  // Int_t   higgsDecayType_;
  // Int_t   ttbarDecayType_;

  // bool passHLT_Ele27_eta2p1_WP85_Gsf_HT200_v1_;

  // int to bool

  bool passHLT_IsoMu24_v_;
  bool passHLT_IsoTkMu24_v_;
  // bool passHLT_IsoMu20_eta2p1_v_;
  // bool passHLT_IsoMu24_eta2p1_v_;


  // bool passHLT_Ele32_eta2p1_WPTight_Gsf_v_;
  // bool passHLT_Ele27_eta2p1_WPTight_Gsf_v_;
  bool passHLT_Ele27_WPTight_Gsf_v;
  // bool passHLT_IsoMu22_v_;
  // bool passHLT_IsoTkMu22_v_;
  bool passHLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v_;

  // bool passHLT_Ele27_WP85_Gsf_v_;
  // bool passHLT_Ele27_eta2p1_WPLoose_Gsf_v_;
  // bool passHLT_Ele27_eta2p1_WP75_Gsf_v_;

  // bool passHLT_Ele27_eta2p1_WP85_Gsf_HT200_v_;
  // bool passHLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v_;

  bool passHLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v_;

  // bool passHLT_Mu30_TkMu11_v_;
  bool passHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v_;
  bool passHLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v_;
  bool passHLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v_;
  bool passHLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v_;
  bool passHLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v_;
  bool passHLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v_;


  // bool passHLT_Ele25WP60_SC4_Mass55_v_;

  /* bool passHLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v_; */
  /* bool passHLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v_; */
  /* bool passHLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v_; */
  bool passHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v_;
  bool passHLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v_;

  // bool passHLT_Ele28_eta2p1_WPTight_Gsf_HT150_v_;
  // bool passHLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned_v_;
  bool passHLT_Ele32_WPTight_Gsf_L1DoubleEG_v_;
  bool passHLT_Ele32_WPTight_Gsf_v_;
  // bool passHLT_Ele35_WPTight_Gsf_v_;
  // bool passHLT_Ele38_WPTight_Gsf_v_;
  bool passHLT_Ele40_WPTight_Gsf_v_;
  bool passHLT_IsoMu24_2p1_v_;
  bool passHLT_IsoMu27_v_;
  bool passHLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v_;
  bool passHLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v_;
  // bool passHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v_;
  bool passHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v_;
  bool passHLT_PFHT380_SixJet32_DoubleBTagCSV_p075_v_;
  bool passHLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2_v_;
  bool passHLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2_v_;
  bool passHLT_PFHT430_SixJet40_BTagCSV_p080_v_;
  bool passHLT_PFHT430_SixPFJet40_PFBTagCSV_1p5_v_;

  bool passMETFilters_;
  /*// MET Filters
  bool passMETFilter_Flag_goodVertices_v_;
  bool passMETFilter_Flag_globalTightHalo2016Filter_v_;
  bool passMETFilter_Flag_HBHENoiseFilter_v_;
  bool passMETFilter_Flag_HBHENoiseIsoFilter_v_;
  bool passMETFilter_Flag_EcalDeadCellTriggerPrimitiveFilter_v_;
  bool passMETFilter_Flag_BadPFMuonFilter_v_;
  bool passMETFilter_Flag_BadChargedCandidateFilter_v_;
  bool passMETFilter_Flag_ecalBadCalibFilter_v_;
  */

  // 2017 MET triggers
  bool passHLT_PFHT500_PFMET100_PFMHT100_IDTight_v_;
  // bool passHLT_PFHT500_PFMET110_PFMHT110_IDTight_v_;
  bool passHLT_PFHT700_PFMET85_PFMHT85_IDTight_v_;
  // bool passHLT_PFHT700_PFMET95_PFMHT95_IDTight_v_;
  bool passHLT_PFHT800_PFMET75_PFMHT75_IDTight_v_;
  // bool passHLT_PFHT800_PFMET85_PFMHT85_IDTight_v_;
  // bool passHLT_PFMET110_PFMHT110_IDTight_v_;
  bool passHLT_PFMET120_PFMHT120_IDTight_v_;
  // bool passHLT_PFMET130_PFMHT130_IDTight_v_;
  // bool passHLT_PFMET140_PFMHT140_IDTight_v_;
  // bool passHLT_PFMETTypeOne110_PFMHT110_IDTight_v_;
  // bool passHLT_PFMETTypeOne120_PFMHT120_IDTight_v_;
  // bool passHLT_PFMETTypeOne130_PFMHT130_IDTight_v_;
  // bool passHLT_PFMETTypeOne140_PFMHT140_IDTight_v_;
  // bool passHLT_DiJet110_35_Mjj650_PFMET110_v_;
  // bool passHLT_DiJet110_35_Mjj650_PFMET120_v_;
  // bool passHLT_DiJet110_35_Mjj650_PFMET130_v_;
  // bool passHLT_TripleJet110_35_35_Mjj650_PFMET110_v_;
  // bool passHLT_TripleJet110_35_35_Mjj650_PFMET120_v_;
  // bool passHLT_TripleJet110_35_35_Mjj650_PFMET130_v_;
  // bool passHLT_MET105_IsoTrk50_v_;
  // bool passHLT_MET120_IsoTrk50_v_;
  bool passHLT_PFMET120_PFMHT120_IDTight_PFHT60_v_;
  // bool passHLT_PFMETTypeOne120_PFMHT120_IDTight_PFHT60_v_;
  // bool passHLT_PFMET100_PFMHT100_IDTight_CaloBTagCSV_3p1_v_;
  // bool passHLT_PFMET110_PFMHT110_IDTight_CaloBTagCSV_3p1_v_;
  // bool passHLT_PFMET120_PFMHT120_IDTight_CaloBTagCSV_3p1_v_;
  // bool passHLT_PFMET130_PFMHT130_IDTight_CaloBTagCSV_3p1_v_;
  // bool passHLT_PFMET140_PFMHT140_IDTight_CaloBTagCSV_3p1_v_;
  // bool passHLT_CaloMET100_HBHECleaned_v_;
  // bool passHLT_CaloMET250_HBHECleaned_v_;
  // bool passHLT_CaloMET300_HBHECleaned_v_;
  // bool passHLT_CaloMET350_HBHECleaned_v_;
  // bool passHLT_CaloMET70_HBHECleaned_v_;
  // bool passHLT_CaloMET80_HBHECleaned_v_;
  // bool passHLT_CaloMET90_HBHECleaned_v_;
  bool passHLT_PFMET200_HBHE_BeamHaloCleaned_v_;
  // bool passHLT_PFMET200_HBHECleaned_v_;
  bool passHLT_PFMET250_HBHECleaned_v_;
  // bool passHLT_PFMET300_HBHECleaned_v_;
  bool passHLT_PFMETTypeOne200_HBHE_BeamHaloCleaned_v_;
  // bool passHLT_PFMET100_PFMHT100_IDTight_PFHT60_v_;
  // bool passHLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60_v_;
  // bool passHLT_PFHT250_v_;
  bool passHLT_PFMETNoMu120_PFMHTNoMu120_IDTight_v_;
  bool passHLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60_v_;
  bool passHLT_MET200_v_;
  bool passHLT_PFMET170_HBHECleaned_v_;
  bool passHLT_PFMET300_v_;
  bool passHLT_PFHT300_PFMET110_v_;
  // bool passHLT_PFHT_300_v_;
  // bool passPFMET110_HLT_MET200_v_;

  int run_;
  int lumi_;
  long evt_;

  float   puSF_;
  bool    GoodFirstPV_;
  Int_t   numPVs_;

  vint lepton_isMuon_;
  vint lepton_charge_;
  vint lepton_isTight_;
  vfloat lepton_pt_;
  vfloat lepton_eta_;
  vfloat lepton_phi_;
  vfloat lepton_e_;
  vfloat lepton_relIso_;
  vfloat lepton_scEta_;
  vfloat lepton_IDSF_;
  vfloat lepton_recoIsoSF_;
  vfloat lepton_energyCorr_;

  float genweight_;

  Float_t MET_;
  Float_t MET_phi_;
  Float_t MET_Type1xy_;
  Float_t MET_Type1xy_phi_;
  Float_t MET_Type1xy_sync_;
  Float_t MET_Type1xy_phi_sync_;

  vfloat jet_RegFactor_;

  vfloat jet_pt_;
  vfloat jet_eta_;
  vfloat jet_phi_;
  vfloat jet_m_;



  void initialize();

};


typedef std::vector<yggdrasilEventVars> vyggdrasilEventVars;


void yggdrasilEventVars::initialize(){

  // passHLT_Ele27_eta2p1_WP85_Gsf_HT200_v1_ = -99;

  passHLT_IsoMu24_v_ = false;
  passHLT_IsoTkMu24_v_ = false;
  // passHLT_IsoMu20_eta2p1_v_ = -99;
  // passHLT_IsoMu24_eta2p1_v_ = -99;


  // passHLT_Ele32_eta2p1_WPTight_Gsf_v_ = -99;
  // passHLT_Ele27_eta2p1_WPTight_Gsf_v_ = -99;
  // passHLT_IsoMu22_v_ = -99;
  // passHLT_IsoTkMu22_v_ = -99;
  passHLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v_ = false;

  // passHLT_Ele27_WP85_Gsf_v_ = -99;
  passHLT_Ele27_WPTight_Gsf_v = false;
  // passHLT_Ele27_eta2p1_WPLoose_Gsf_v_ = -99;
  // passHLT_Ele27_eta2p1_WP75_Gsf_v_ = -99;

  // passHLT_Ele27_eta2p1_WP85_Gsf_HT200_v_ = -99;
  // passHLT_Ele27_eta2p1_WPLoose_Gsf_HT200_v_ = -99;

  passHLT_Ele32_WPTight_Gsf_v_ = false;
  // passHLT_Ele35_WPTight_Gsf_v_ = -99;
  // passHLT_Ele38_WPTight_Gsf_v_ = -99;
  passHLT_Ele40_WPTight_Gsf_v_ = false;
  // passHLT_Ele28_eta2p1_WPTight_Gsf_HT150_v_  = -99;;
  // passHLT_Ele30_eta2p1_WPTight_Gsf_CentralPFJet35_EleCleaned_v_ = -99;
  passHLT_Ele32_WPTight_Gsf_L1DoubleEG_v_ = false;

  passHLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v_ = false;
  passHLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v_ = false;

  // passHLT_Mu30_TkMu11_v_ = -99;
  passHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_v_ = false;
  passHLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v_ = false;
  passHLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v_ = false;
  passHLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v_ = false;
  passHLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v_ = false;
  passHLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_v_ = false;
  // passHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8_v_ = -99;
  passHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v_ = false;

  // passHLT_Ele25WP60_SC4_Mass55_v_ = -99;

  /* passHLT_Ele17_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_v_ = -99; */
  /* passHLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_v_ = -99; */
  /* passHLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL_v_ = -99; */
  passHLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_v_ = false;
  passHLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ_v_ = false;

  // 5-15-18 [BBT]: add 2017 MET branhces
  passHLT_PFHT500_PFMET100_PFMHT100_IDTight_v_ = false;
  // passHLT_PFHT500_PFMET110_PFMHT110_IDTight_v_ = -99;
  passHLT_PFHT700_PFMET85_PFMHT85_IDTight_v_ = false;
  // passHLT_PFHT700_PFMET95_PFMHT95_IDTight_v_ = -99;
  passHLT_PFHT800_PFMET75_PFMHT75_IDTight_v_ = false;
  // passHLT_PFHT800_PFMET85_PFMHT85_IDTight_v_ = -99;
  // passHLT_PFMET110_PFMHT110_IDTight_v_ = -99;
  passHLT_PFMET120_PFMHT120_IDTight_v_ = false;
  // passHLT_PFMET130_PFMHT130_IDTight_v_ = -99;
  // passHLT_PFMET140_PFMHT140_IDTight_v_ = -99;
  // passHLT_PFMETTypeOne110_PFMHT110_IDTight_v_ = -99;
  // passHLT_PFMETTypeOne120_PFMHT120_IDTight_v_ = -99;
  // passHLT_PFMETTypeOne130_PFMHT130_IDTight_v_ = -99;
  // passHLT_PFMETTypeOne140_PFMHT140_IDTight_v_ = -99;
  // passHLT_DiJet110_35_Mjj650_PFMET110_v_ = -99;
  // passHLT_DiJet110_35_Mjj650_PFMET120_v_ = -99;
  // passHLT_DiJet110_35_Mjj650_PFMET130_v_ = -99;
  // passHLT_TripleJet110_35_35_Mjj650_PFMET110_v_ = -99;
  // passHLT_TripleJet110_35_35_Mjj650_PFMET120_v_ = -99;
  // passHLT_TripleJet110_35_35_Mjj650_PFMET130_v_ = -99;
  // passHLT_MET105_IsoTrk50_v_ = -99;
  // passHLT_MET120_IsoTrk50_v_ = -99;
  passHLT_PFMET120_PFMHT120_IDTight_PFHT60_v_ = false;
  // passHLT_PFMETTypeOne120_PFMHT120_IDTight_PFHT60_v_ = -99;
  // passHLT_PFMET100_PFMHT100_IDTight_CaloBTagCSV_3p1_v_ = -99;
  // passHLT_PFMET110_PFMHT110_IDTight_CaloBTagCSV_3p1_v_ = -99;
  // passHLT_PFMET120_PFMHT120_IDTight_CaloBTagCSV_3p1_v_ = -99;
  // passHLT_PFMET130_PFMHT130_IDTight_CaloBTagCSV_3p1_v_ = -99;
  // passHLT_PFMET140_PFMHT140_IDTight_CaloBTagCSV_3p1_v_ = -99;
  // passHLT_CaloMET100_HBHECleaned_v_ = -99;
  // passHLT_CaloMET250_HBHECleaned_v_ = -99;
  // passHLT_CaloMET300_HBHECleaned_v_ = -99;
  // passHLT_CaloMET350_HBHECleaned_v_ = -99;
  // passHLT_CaloMET70_HBHECleaned_v_ = -99;
  // passHLT_CaloMET80_HBHECleaned_v_ = -99;
  // passHLT_CaloMET90_HBHECleaned_v_ = -99;
  passHLT_PFMET200_HBHE_BeamHaloCleaned_v_ = false;
  // passHLT_PFMET200_HBHECleaned_v_ = -99;
  passHLT_PFMET250_HBHECleaned_v_ = false;
  // passHLT_PFMET300_HBHECleaned_v_ = -99;
  passHLT_PFMETTypeOne200_HBHE_BeamHaloCleaned_v_ = false;
  // passHLT_PFMET100_PFMHT100_IDTight_PFHT60_v_ = -99;
  // passHLT_PFMETTypeOne100_PFMHT100_IDTight_PFHT60_v_ = -99;
  // passHLT_PFHT250_v_ = -99;
  passHLT_PFMETNoMu120_PFMHTNoMu120_IDTight_v_ = false;
  passHLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60_v_ = false;
  passHLT_MET200_v_ = false;
  passHLT_PFMET170_HBHECleaned_v_ = false;
  passHLT_PFMET300_v_  = false;
  passHLT_PFHT300_PFMET110_v_ = false;
  // passHLT_PFHT_300_v_  = -99;
  // passPFMET110_HLT_MET200_v_ = -99;

  passMETFilters_ = false;

  run_  = -99;
  lumi_ = -99;
  evt_ = -99;

  GoodFirstPV_ = false;
  numPVs_ = -99;
  genweight_ = -999.;

  lepton_isMuon_.clear();
  lepton_charge_.clear();
  lepton_isTight_.clear();
  lepton_pt_.clear();
  lepton_eta_.clear();
  lepton_phi_.clear();
  lepton_e_.clear();
  lepton_relIso_.clear();
  lepton_scEta_.clear();
  lepton_IDSF_.clear();
  lepton_recoIsoSF_.clear();

    MET_ = -99.9;
    MET_phi_ = -99.9;

    MET_Type1xy_ = -99.9;
    MET_Type1xy_phi_ = -99.9;

    MET_Type1xy_sync_ = -99.9;
    MET_Type1xy_phi_sync_ = -99.9;

    jet_pt_ .clear();
    jet_phi_.clear();
    jet_eta_.clear();
    jet_m_.clear();
    jet_RegFactor_.clear();

  return;
}
#endif
