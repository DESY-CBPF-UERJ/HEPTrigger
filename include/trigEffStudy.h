// Author:  Ben Tannenwald
// Date:    Mar 1, 2018
// Purpose: Header for trigger efficiency code

#include <string>
#include <TH2.h>
#include <TFile.h>
#include <TObjArray.h>
// #include "YggdrasilEventVars.h"
#include "EventVars.h"
#include "leptonHandler.h"
#include "jetMetHandler.h"

// top level vars
std::string topDir, fileList, date;
bool printPlots, dumpFile, verbose, isMC, singleFile, isDebug, isTrigSF;

// user tools
// yggdrasilEventVars *eve;
EventVars *eve;
leptonHandler lepTool;
jetMetHandler jetMetTool;


// user file
TFile* outfile = new TFile();

// user vars
TObjArray* a_HLT_IsoMu27 = new TObjArray();
TObjArray* a_HLT_IsoMu24_eta2p1 = new TObjArray();
TObjArray* a_HLT_Ele35_WPTight_Gsf = new TObjArray();
TObjArray* a_HLT_PFMET120_PFMHT120_IDTight = new TObjArray();
TObjArray* a_HLT_PFHT250 = new TObjArray();
TObjArray* a_IsoMu27__X__PFMET120_PFMHT120_IDTight = new TObjArray();
TObjArray* a_Ele35_WPTight_Gsf__X__PFMET120_PFMHT120_IDTight = new TObjArray();

TObjArray* a_HLT_SingleMu = new TObjArray();
TObjArray* a_HLT_SingleEl = new TObjArray();
TObjArray* a_HLT_allMET = new TObjArray();
TObjArray* a_SingleMu__X__allMET = new TObjArray();
TObjArray* a_SingleEl__X__allMET = new TObjArray();

TObjArray* a_HLT_DoubleMu = new TObjArray();
TObjArray* a_HLT_DoubleEl = new TObjArray();
TObjArray* a_HLT_EMu = new TObjArray();
TObjArray* a_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ = new TObjArray();
TObjArray* a_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass8 = new TObjArray();
TObjArray* a_HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8 = new TObjArray();
TObjArray* a_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL = new TObjArray();
TObjArray* a_HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = new TObjArray();
TObjArray* a_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL = new TObjArray();
TObjArray* a_HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ = new TObjArray();
TObjArray* a_HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ = new TObjArray();
TObjArray* a_HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ = new TObjArray();

TObjArray* a_DoubleMu__X__allMET = new TObjArray();
TObjArray* a_DoubleEl__X__allMET = new TObjArray();
TObjArray* a_EMu__X__allMET = new TObjArray();

// TObjArray* a_HLT_DoubleMu_OR = new TObjArray();
// TObjArray* a_HLT_DoubleEl_OR = new TObjArray();
// TObjArray* a_HLT_EMu_OR = new TObjArray();
TObjArray* a_DoubleMu_OR__X__allMET = new TObjArray();
TObjArray* a_DoubleEl_OR__X__allMET = new TObjArray();
TObjArray* a_EMu_OR__X__allMET = new TObjArray();

// TObjArray* a_HLT_DoubleMu_OR_NJETSHIGH = new TObjArray();
// TObjArray* a_HLT_DoubleEl_OR_NJETSHIGH = new TObjArray();
// TObjArray* a_HLT_EMu_OR_NJETSHIGH = new TObjArray();
TObjArray* a_DoubleMu_OR__X__allMET_NJETSHIGH = new TObjArray();
TObjArray* a_DoubleEl_OR__X__allMET_NJETSHIGH = new TObjArray();
TObjArray* a_EMu_OR__X__allMET_NJETSHIGH = new TObjArray();

// TObjArray* a_HLT_DoubleMu_OR_NJETSLOW = new TObjArray();
// TObjArray* a_HLT_DoubleEl_OR_NJETSLOW = new TObjArray();
// TObjArray* a_HLT_EMu_OR_NJETSLOW = new TObjArray();
TObjArray* a_DoubleMu_OR__X__allMET_NJETSLOW = new TObjArray();
TObjArray* a_DoubleEl_OR__X__allMET_NJETSLOW = new TObjArray();
TObjArray* a_EMu_OR__X__allMET_NJETSLOW = new TObjArray();

// TObjArray* a_HLT_DoubleMu_OR_NPVHIGH = new TObjArray();
// TObjArray* a_HLT_DoubleEl_OR_NPVHIGH = new TObjArray();
// TObjArray* a_HLT_EMu_OR_NPVHIGH = new TObjArray();
TObjArray* a_DoubleMu_OR__X__allMET_NPVHIGH = new TObjArray();
TObjArray* a_DoubleEl_OR__X__allMET_NPVHIGH = new TObjArray();
TObjArray* a_EMu_OR__X__allMET_NPVHIGH = new TObjArray();

// TObjArray* a_HLT_DoubleMu_OR_NPVLOW = new TObjArray();
// TObjArray* a_HLT_DoubleEl_OR_NPVLOW = new TObjArray();
// TObjArray* a_HLT_EMu_OR_NPVLOW = new TObjArray();
TObjArray* a_DoubleMu_OR__X__allMET_NPVLOW = new TObjArray();
TObjArray* a_DoubleEl_OR__X__allMET_NPVLOW = new TObjArray();
TObjArray* a_EMu_OR__X__allMET_NPVLOW = new TObjArray();

// TObjArray* a_HLT_DoubleMu_OR_METHIGH = new TObjArray();
// TObjArray* a_HLT_DoubleEl_OR_METHIGH = new TObjArray();
// TObjArray* a_HLT_EMu_OR_METHIGH = new TObjArray();
TObjArray* a_DoubleMu_OR__X__allMET_METHIGH = new TObjArray();
TObjArray* a_DoubleEl_OR__X__allMET_METHIGH = new TObjArray();
TObjArray* a_EMu_OR__X__allMET_METHIGH = new TObjArray();

// TObjArray* a_HLT_DoubleMu_OR_METLOW = new TObjArray();
// TObjArray* a_HLT_DoubleEl_OR_METLOW = new TObjArray();
// TObjArray* a_HLT_EMu_OR_METLOW = new TObjArray();
TObjArray* a_DoubleMu_OR__X__allMET_METLOW = new TObjArray();
TObjArray* a_DoubleEl_OR__X__allMET_METLOW = new TObjArray();
TObjArray* a_EMu_OR__X__allMET_METLOW = new TObjArray();

// TObjArray* a_HLT_DoubleMu_OR_ExNumMu0 = new TObjArray();
// TObjArray* a_HLT_DoubleEl_OR_ExNumMu0 = new TObjArray();
// TObjArray* a_HLT_EMu_OR_ExNumMu0 = new TObjArray();
TObjArray* a_DoubleMu_OR__X__allMET_ExNumMu0 = new TObjArray();
TObjArray* a_DoubleEl_OR__X__allMET_ExNumMu0 = new TObjArray();
TObjArray* a_EMu_OR__X__allMET_ExNumMu0 = new TObjArray();

// TObjArray* a_HLT_DoubleMu_OR_ExNumMu1 = new TObjArray();
// TObjArray* a_HLT_DoubleEl_OR_ExNumMu1 = new TObjArray();
// TObjArray* a_HLT_EMu_OR_ExNumMu1 = new TObjArray();
TObjArray* a_DoubleMu_OR__X__allMET_ExNumMu1 = new TObjArray();
TObjArray* a_DoubleEl_OR__X__allMET_ExNumMu1 = new TObjArray();
TObjArray* a_EMu_OR__X__allMET_ExNumMu1 = new TObjArray();

// TObjArray* a_HLT_DoubleMu_OR_ExNumMu2 = new TObjArray();
// TObjArray* a_HLT_DoubleEl_OR_ExNumMu2 = new TObjArray();
// TObjArray* a_HLT_EMu_OR_ExNumMu2 = new TObjArray();
TObjArray* a_DoubleMu_OR__X__allMET_ExNumMu2 = new TObjArray();
TObjArray* a_DoubleEl_OR__X__allMET_ExNumMu2 = new TObjArray();
TObjArray* a_EMu_OR__X__allMET_ExNumMu2 = new TObjArray();


// TObjArray* a_HLT_DoubleMu_OR_ExNumEl0 = new TObjArray();
// TObjArray* a_HLT_DoubleEl_OR_ExNumEl0 = new TObjArray();
// TObjArray* a_HLT_EMu_OR_ExNumEl0 = new TObjArray();
TObjArray* a_DoubleMu_OR__X__allMET_ExNumEl0 = new TObjArray();
TObjArray* a_DoubleEl_OR__X__allMET_ExNumEl0 = new TObjArray();
TObjArray* a_EMu_OR__X__allMET_ExNumEl0 = new TObjArray();

// TObjArray* a_HLT_DoubleMu_OR_ExNumEl1 = new TObjArray();
// TObjArray* a_HLT_DoubleEl_OR_ExNumEl1 = new TObjArray();
// TObjArray* a_HLT_EMu_OR_ExNumEl1 = new TObjArray();
TObjArray* a_DoubleMu_OR__X__allMET_ExNumEl1 = new TObjArray();
TObjArray* a_DoubleEl_OR__X__allMET_ExNumEl1 = new TObjArray();
TObjArray* a_EMu_OR__X__allMET_ExNumEl1 = new TObjArray();

// TObjArray* a_HLT_DoubleMu_OR_ExNumEl2 = new TObjArray();
// TObjArray* a_HLT_DoubleEl_OR_ExNumEl2 = new TObjArray();
// TObjArray* a_HLT_EMu_OR_ExNumEl2 = new TObjArray();
TObjArray* a_DoubleMu_OR__X__allMET_ExNumEl2 = new TObjArray();
TObjArray* a_DoubleEl_OR__X__allMET_ExNumEl2 = new TObjArray();
TObjArray* a_EMu_OR__X__allMET_ExNumEl2 = new TObjArray();

TObjArray* a_DoubleMu_OR__X__allMET_DeltaRZone0 = new TObjArray();
TObjArray* a_DoubleEl_OR__X__allMET_DeltaRZone0 = new TObjArray();
TObjArray* a_EMu_OR__X__allMET_DeltaRZone0 = new TObjArray();

TObjArray* a_DoubleMu_OR__X__allMET_DeltaRZone1 = new TObjArray();
TObjArray* a_DoubleEl_OR__X__allMET_DeltaRZone1 = new TObjArray();
TObjArray* a_EMu_OR__X__allMET_DeltaRZone1 = new TObjArray();

TObjArray* a_DoubleMu_OR__X__allMET_DeltaRZone2 = new TObjArray();
TObjArray* a_DoubleEl_OR__X__allMET_DeltaRZone2 = new TObjArray();
TObjArray* a_EMu_OR__X__allMET_DeltaRZone2 = new TObjArray();

TObjArray* a_DoubleMu_OR__X__allMET_DeltaRZone3 = new TObjArray();
TObjArray* a_DoubleEl_OR__X__allMET_DeltaRZone3 = new TObjArray();
TObjArray* a_EMu_OR__X__allMET_DeltaRZone3 = new TObjArray();







//Canal Mumu
TObjArray* a_DoubleMu_OR__X__allMET_NumSum2Fail = new TObjArray();   //Objeto que representa o numerador do N_eff dos eventos que falharam.
TObjArray* a_DoubleMu_OR__X__allMET_DenSum2Fail = new TObjArray();   //Objeto que representa o denominador do N_eff dos eventos que falharam.
TObjArray* a_DoubleMu_OR__X__allMET_NumSum2Win = new TObjArray();   //Objeto que representa o numerador do N_eff dos eventos que passaram.
TObjArray* a_DoubleMu_OR__X__allMET_DenSum2Win = new TObjArray();   //Objeto que representa o denominador do N_eff dos eventos que passaram.
//Canal ElMu
TObjArray* a_EMu_OR__X__allMET_NumSum2Fail = new TObjArray();   //Objeto que representa o numerador do N_eff dos eventos que falharam.
TObjArray* a_EMu_OR__X__allMET_DenSum2Fail = new TObjArray();   //Objeto que representa o denominador do N_eff dos eventos que falharam.
TObjArray* a_EMu_OR__X__allMET_NumSum2Win = new TObjArray();   //Objeto que representa o numerador do N_eff dos eventos que passaram.
TObjArray* a_EMu_OR__X__allMET_DenSum2Win = new TObjArray();   //Objeto que representa o denominador do N_eff dos eventos que passaram.

//Canal ELEL
TObjArray* a_DoubleEl_OR__X__allMET_NumSum2Fail = new TObjArray();   //Objeto que representa o numerador do N_eff dos eventos que falharam.
TObjArray* a_DoubleEl_OR__X__allMET_DenSum2Fail = new TObjArray();   //Objeto que representa o denominador do N_eff dos eventos que falharam.
TObjArray* a_DoubleEl_OR__X__allMET_NumSum2Win = new TObjArray();   //Objeto que representa o numerador do N_eff dos eventos que passaram.
TObjArray* a_DoubleEl_OR__X__allMET_DenSum2Win = new TObjArray();   //Objeto que representa o denominador do N_eff dos eventos que passaram.










TObjArray* a_Efficiencies = new TObjArray();

std::vector <std::string> metTriggers =
  {
    "HLT_MET200",                                          //
    "HLT_PFMET300",                                        //
    "HLT_PFHT300_PFMET110",                                //
    "HLT_PFMET170_HBHECleaned",                             //
    //"HLT_PFHTPFMET170_HBHECleaned",
   
    // "HLT_PFHT500_PFMET100_PFMHT100_IDTight",
    // "HLT_PFHT700_PFMET85_PFMHT85_IDTight",
    // "HLT_PFHT800_PFMET75_PFMHT75_IDTight",
    // "HLT_PFMET250_HBHECleaned",
    // "HLT_PFMET200_HBHE_BeamHaloCleaned",
    // "HLT_PFMETTypeOne200_HBHE_BeamHaloCleaned",
    "HLT_PFMET120_PFMHT120_IDTight",                       //
    "HLT_PFMETNoMu120_PFMHTNoMu120_IDTight",               //
    // "HLT_PFMETNoMu120_PFMHTNoMu120_IDTight_PFHT60",
    // "HLT_PFMET120_PFMHT120_IDTight_PFHT60",
    // "HLT_CaloMET250_HBHECleaned",
    // "HLT_PFMET110_HLT_MET200",
    // "HLT_PFHT250",
    "HLT_allMET"
 };

// Lepton Triggers
// Single Muon: HLT_IsoMu27
// Single Electron: HLT_Ele35_WPTight_Gsf
