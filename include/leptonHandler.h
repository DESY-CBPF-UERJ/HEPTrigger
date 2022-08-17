#ifndef _leptonHandler_h
#define _leptonHandler_h

#include <TH1.h>
#include <TH2.h>
#include <TLorentzVector.h>

#include <iostream>
#include <vector>

// #include "YggdrasilEventVars.h"
#include "EventVars.h"


#ifdef __MAKECINT__
#pragma link C++ class std::vector< TLorentzVector >+;
#endif

#if !defined(__CINT__) && !defined(__MAKECINT__)


#endif

class leptonHandler{

   public:
      // Constructor(s) and destructor
      leptonHandler();
      virtual ~leptonHandler();

      int era_ = 0;

      // === Functions === //
      void test();
      void setFlags(bool passMC, string inputFile);
      // void Event(yggdrasilEventVars* eve, bool passDebug, bool passTrigSF);
      void Event(EventVars* eve, bool passDebug, bool passTrigSF);

      // === Variables === //
      bool passSLCuts_el;
      bool passSLCuts_mu;
      bool passDLCuts_el;
      bool passDLCuts_mu;
      bool passDLCuts_emu;
      bool passSLtriggers_el;
      bool passSLtriggers_mu;
      bool passDLtriggers_el;
      bool passDLtriggers_mu;
      bool passDLtriggers_emu;
      int nLeptons;
      int nMuons;
      int nElectrons;
      float leadPt_el;
      float leadEta_el;
      float leadCharge_el;
      float subPt_el;
      float subEta_el;
      float subCharge_el;
      float leadPt_mu;
      float leadEta_mu;
      float leadCharge_mu;
      float leadRelIso_mu;
      float leadRelIso_el;
      float subRelIso_mu;
      float subRelIso_el;
      float subPt_mu;
      float subEta_mu;
      float subCharge_mu;
      float mll;
      bool isMC;
      bool isDebug;
      bool isTrigSF;
      string dataPeriod;
      string dataStream;
      bool b_periodDep__HLT_IsoMu24_eta2p1;
      bool b_periodDep__doubleMu_noMass;
      bool b_periodDep__doubleMu_withMass;
      // int passMultiMuons;
      int MuonExtraNumber;
      int ElectronExtraNumber;
      int leadIndex_el;
      int subIndex_el;
      int leadIndex_mu;
      int subIndex_mu;
      float leadIDSF_el;
      float leadRecoIsoSF_el;
      float subIDSF_el;
      float subRecoIsoSF_el;
      float leadIDSF_mu;
      float leadRecoIsoSF_mu;
      float subIDSF_mu;
      float subRecoIsoSF_mu;

      // === Variables === //
      TH1D* h_mu_cutflow;
      TH1D* h_mu_event_cutflow;
      TH1D* h_mu_n;
      TH1D* h_el_cutflow;
      TH1D* h_el_event_cutflow;
      TH1D* h_el_n;

   private:
      // === Functions === //
      void applyMuonCuts();
      void applyElectronCuts();
      void checkHLTTriggers();
      void checkCategoryCuts();
      void setLeadSubleadIndices(int l, int& lead, int& sub);
      float calculateDileptonMass(int index_lead, int index_sub);

      // === Variables === //
      // yggdrasilEventVars* ev;
      EventVars* ev;
      bool passMC;
      bool passDebug;
      bool passTrigSF;

}; // End of class prototype




#endif // _leptonHandler_h
