#ifndef _jetMetHandler_h
#define _jetMetHandler_h

#include <TH1.h>
#include <TH2.h>

#include <iostream>
#include <vector>
// #include "YggdrasilEventVars.h"
#include "EventVars.h"
#include "TLorentzVector.h"
//#include "leptonHandler.h"


#ifdef __MAKECINT__
#pragma link C++ class std::vector< TLorentzVector >+;
#endif

#if !defined(__CINT__) && !defined(__MAKECINT__)


#endif

class jetMetHandler{

   public:
      // Constructor(s) and destructor
      jetMetHandler();
      virtual ~jetMetHandler();

      // === Functions === //
      void test();
      // void Event(yggdrasilEventVars* eve, leptonHandler lep, bool passDebug, bool passTrigSF);
      void Event(EventVars* eve, leptonHandler lep, bool passDebug, bool passTrigSF);

      int era_ = 0;

      // === Variables === //
      bool passLeadingJetCuts;
      bool passDLJetMetCuts;
      bool passSLJetMetCuts;
      int passNjetsCuts;
      int passNPVCuts;
      int passMETCuts;

      int nPreCutJets;
      int nJets;
      int nBTags;
      float leadPt;
      float leadEta;
      float leadPhi;
      float subPt;
      float subEta;
      float subPhi;
      float MET;
      float MET_phi;
      float nPV;
      float PU_SF;
      float genweight;
      float evtWeight;
      float ttbarJetID;
      bool passOneMETTrigger;
      bool passAllMETTriggers;
      bool isDebug;
      bool isTrigSF;

      // === Variables === //
      TH1D* h_jet_cutflow;
      TH1D* h_jet_n;
      TH1D* h_btags_n;
      TH1D* h_met_passXtriggers;
      TH1D* h_met_passOnlyXtrigger;

   private:
      // === Functions === //
      void applyJetCuts();
      void applyMETCuts();
      void parseMETTriggerLogic();
      void parseMETTriggerLogic_2016();
      void parseMETTriggerLogic_2017();
      void parseMETTriggerLogic_2018();
      void setLeadSubleadIndices(int l, int& lead, int& sub);
      bool vetoLeptonJetOverlapRemoval(int j);


      // === Variables === //
      // yggdrasilEventVars* ev;
      EventVars* ev;
      leptonHandler lTool;
      int leadIndex;
      int subIndex;
      string metXTriggerBits;
      bool passDebug;
      bool passTrigSF;

}; // End of class prototype

#endif // _jetMetHandler_h
