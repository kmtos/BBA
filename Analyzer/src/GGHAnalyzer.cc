// -*- C++ -*-
//
// Package:    GGHAnalyzer
// Class:      GGHAnalyzer
// 
/**\class GGHAnalyzer GGHAnalyzer.cc Analyzer/src/GGHAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Kyle Martin Tos
//         Created:  Thu Feb 26 09:51:23 CET 2015
// $Id$
//
//


// system include files
#include <memory>
#include <string>
#include <sstream>
#include <math.h>

// user include files
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "HLTrigger/HLTanalyzers/interface/HLTInfo.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "HLTrigger/HLTcore/interface/HLTConfigData.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "BBA/VariousFunctions/interface/VariousFunctions.h"

#include "TFile.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TLegend.h"


using namespace std;
using namespace edm;
using namespace reco;
using namespace trigger;
//
//
//
// class declaration
//

class GGHAnalyzer : public edm::EDAnalyzer {
   public:
      explicit GGHAnalyzer(const edm::ParameterSet&);
      ~GGHAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      //delete memory
      void reset(const bool);
    
      // ----------member data ---------------------------
      //pointer to output file object
      TFile* out_;

      //name of output file
      std::string outFileName_;

      //gen particle tag
      edm::InputTag genParticleTag_;

      //Histograms
      TH1F* AEtaPart_;
      TH1F* APhiPart_;
      TH1F* AdRPart_;
      TH2F* A1EtaVsA2EtaPart_;
      TH1F* AdPhiPart_;
      TH2F* AdEtaVsAdPhiPart_;
      TH1F* TauPtPart_;
      TH1F* APtPart_;

      TH1F* TauPt1Part_;
      TH1F* TauPt2Part_;
      TH1F* TauPt3Part_;
      TH1F* TauPt4Part_;
      TH1F* TauPtHighPart_;
      TH1F* TauPtLowPart_;
      TH1F* TauDecayMode_;
      TH1F* TauPt_;
      TH1F* DiTauDR_; 
      TH1F* TauEta_;
      TH1F* TauPhi_;

      TH2F* DiTauDRVsAPt_;
      TH2F* DiTauDRVsAEta_;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
GGHAnalyzer::GGHAnalyzer(const edm::ParameterSet& iConfig):
  outFileName_(iConfig.getParameter<std::string>("outFileName")),
  genParticleTag_(iConfig.getParameter<edm::InputTag>("genParticleTag"))
{
  reset(false);    
}//GGHAnalyzer



GGHAnalyzer::~GGHAnalyzer()
{
  reset(true);
}


//
// member functions
//

// ------------ method called for each event  ------------
void GGHAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  //Get gen particle collection
  edm::Handle<reco::GenParticleCollection> pGenParticles;
  iEvent.getByLabel(genParticleTag_, pGenParticles);
  std::cout << "\n\nTHIS IS A NEW EVENT" << std::endl;

  //Cycling through all of the particles in each event
  for (reco::GenParticleCollection::const_iterator iGenParticle = pGenParticles->begin(); iGenParticle != pGenParticles->end(); ++iGenParticle)
  {
    reco::GenParticleRef a1Ref, a2Ref;
    reco::LeafCandidate::LorentzVector tau11P4, tau12P4, tau21P4, tau22P4, a1P4, a2P4;
    if(iGenParticle->pdgId() == 35 && iGenParticle->numberOfDaughters() == 2 && iGenParticle->daughter(0)->pdgId() == 36)
    {
      a1Ref = iGenParticle->daughterRef(0), a2Ref = iGenParticle->daughterRef(1);

      //This Gets the refs of the 4 taus and then gets the ref right before the main decay
      reco::GenParticleRef tau11Ref, tau12Ref, tau21Ref, tau22Ref;
      int tau11DecayMode = 5, tau12DecayMode = 5;
      int tau21DecayMode = 5, tau22DecayMode = 5;
      tau11Ref = VariousFunctions::findDaughterInDaughters(a1Ref, 15, false);
      tau12Ref = VariousFunctions::findDaughterInDaughters(a1Ref, -15, false);
      tau21Ref = VariousFunctions::findDaughterInDaughters(a2Ref, 15, false);
      tau22Ref = VariousFunctions::findDaughterInDaughters(a2Ref, -15, false);

      while(VariousFunctions::findIfInDaughters(tau11Ref, 15, true) )
        tau11Ref = VariousFunctions::findDaughterInDaughters(tau11Ref, 15, true);
      while(VariousFunctions::findIfInDaughters(tau12Ref, 15, true) )
        tau12Ref = VariousFunctions::findDaughterInDaughters(tau12Ref, 15, true);
      while(VariousFunctions::findIfInDaughters(tau21Ref, 15, true) )
        tau21Ref = VariousFunctions::findDaughterInDaughters(tau21Ref, 15, true);
      while(VariousFunctions::findIfInDaughters(tau22Ref, 15, true) )
        tau22Ref = VariousFunctions::findDaughterInDaughters(tau22Ref, 15, true);

      tau11DecayMode = VariousFunctions::tauDecayMode(tau11Ref);
      tau12DecayMode = VariousFunctions::tauDecayMode(tau12Ref);
      tau21DecayMode = VariousFunctions::tauDecayMode(tau21Ref);
      tau22DecayMode = VariousFunctions::tauDecayMode(tau22Ref);
      TauDecayMode_->Fill(tau11DecayMode-1);
      TauDecayMode_->Fill(tau12DecayMode-1);
      TauDecayMode_->Fill(tau21DecayMode-1);
      TauDecayMode_->Fill(tau22DecayMode-1);

      if(tau11DecayMode == 5)
      {
        for (unsigned int i=0; i< tau11Ref->numberOfDaughters(); i++)
          std::cout << "\ttau11Ref Daughter #" << i << " has pdgId= " << tau11Ref->daughter(i)->pdgId() << std::endl;
      }//fi tau11DecayMode == 5
      if(tau12DecayMode == 5)
      {
        for (unsigned int i=0; i< tau12Ref->numberOfDaughters(); i++)
          std::cout << "\ttau12Ref Daughter #" << i << " has pdgId= " << tau12Ref->daughter(i)->pdgId() << std::endl;
      }//fi tau12DecayMode == 5
      if(tau21DecayMode == 5)
      {
        for (unsigned int i=0; i< tau21Ref->numberOfDaughters(); i++)
          std::cout << "\ttau21Ref Daughter #" << i << " has pdgId= " << tau21Ref->daughter(i)->pdgId() << std::endl;
      }//fi tau21DecayMode == 5
      if(tau22DecayMode == 5)
      {
        for (unsigned int i=0; i< tau22Ref->numberOfDaughters(); i++)
          std::cout << "\ttau22Ref Daughter #" << i << " has pdgId= " << tau22Ref->daughter(i)->pdgId() << std::endl;
      }//fi tau22DecayMode == 5

      //Fill all the Particle Quantities before decay identificaton with unrealistic true values 
      double dEta = a1Ref->eta() - a2Ref->eta(), dPhi = reco::deltaPhi(a1Ref->phi(), a2Ref->phi() );
      double adR = sqrt( dPhi*dPhi + dEta*dEta);
//
//This plots the Particle Values, not the visible decay values
//
      AEtaPart_->Fill(a1Ref->eta() );
      AEtaPart_->Fill(a2Ref->eta() );
      APhiPart_->Fill(a1Ref->phi() );
      APhiPart_->Fill(a2Ref->phi() );
      AdRPart_->Fill(adR);
      A1EtaVsA2EtaPart_->Fill(a1Ref->eta(), a2Ref->eta() );
      AdPhiPart_->Fill(dPhi);
      AdEtaVsAdPhiPart_->Fill(dEta, dPhi);
      TauPtPart_->Fill(tau11Ref->pt() );
      TauPtPart_->Fill(tau21Ref->pt() );
      TauPtPart_->Fill(tau12Ref->pt() );
      TauPtPart_->Fill(tau22Ref->pt() );
      APtPart_->Fill(a1Ref->pt() );
      APtPart_->Fill(a2Ref->pt() );

      //This plots the High and low pt Tau for each a decay
      if (tau11Ref->pt() > tau12Ref->pt() )
      {
        TauPtHighPart_->Fill(tau11Ref->pt() );
        TauPtLowPart_->Fill(tau12Ref->pt() );
      }//if 11 > 12
      else
      {
        TauPtHighPart_->Fill(tau12Ref->pt() );
        TauPtLowPart_->Fill(tau11Ref->pt() );
      }//else 12 > 11
      if (tau21Ref->pt() > tau22Ref->pt() )
      {
        TauPtHighPart_->Fill(tau21Ref->pt() );
        TauPtLowPart_->Fill(tau22Ref->pt() );
      }//if 21 > 22
      else
      {
        TauPtHighPart_->Fill(tau22Ref->pt() );
        TauPtLowPart_->Fill(tau21Ref->pt() );
      }//else 22 > 21

      //This plots the Pt of the taus in the order of greatest to smallest
      double *ptOrder = VariousFunctions::orderFour(tau11Ref->pt(), tau12Ref->pt(), tau21Ref->pt(), tau22Ref->pt() );
      TauPt1Part_->Fill(ptOrder[0]);
      TauPt2Part_->Fill(ptOrder[1]);
      TauPt3Part_->Fill(ptOrder[2]);
      TauPt4Part_->Fill(ptOrder[3]);

//
// This is where I begin using the Visible values, not the true
//
      double taudr1 = VariousFunctions::getDiTauDR(tau11Ref, tau12Ref, true), taudr2 = VariousFunctions::getDiTauDR(tau21Ref, tau22Ref, true);
      reco::LeafCandidate::LorentzVector tau11P4 = VariousFunctions::sumTauP4(tau11Ref, tau11DecayMode, true), tau12P4 = VariousFunctions::sumTauP4(tau12Ref, tau12DecayMode, true);
      reco::LeafCandidate::LorentzVector tau21P4 = VariousFunctions::sumTauP4(tau21Ref, tau21DecayMode, true), tau22P4 = VariousFunctions::sumTauP4(tau22Ref, tau22DecayMode, true);
      if ( tau11DecayMode != 5 )
      {
        TauPt_->Fill(tau11P4.Pt() );
        TauEta_->Fill(tau11P4.Eta() );
        TauPhi_->Fill(tau11P4.Phi() );
      }//tau11DecayMode != 5
      if ( tau12DecayMode != 5 )
      { 
        TauPt_->Fill(tau12P4.Pt() );
        TauEta_->Fill(tau12P4.Eta() );
        TauPhi_->Fill(tau12P4.Phi() );        
      }//tau12DecayMode != 5
      if ( tau21DecayMode != 5 )
      { 
        TauPt_->Fill(tau21P4.Pt() );
        TauEta_->Fill(tau21P4.Eta() );
        TauPhi_->Fill(tau21P4.Phi() );        
      }//tau21DecayMode != 5
      if ( tau22DecayMode != 5 )
      { 
        TauPt_->Fill(tau22P4.Pt() );
        TauEta_->Fill(tau22P4.Eta() );
        TauPhi_->Fill(tau22P4.Phi() );        
      }//tau22DecayMode != 5
      if ( tau11DecayMode != 5 && tau12DecayMode != 5)
      { 
        DiTauDR_->Fill(taudr1);        
      }//tau11DecayMode != 5 && tau12DecayMode != 5
      if ( tau21DecayMode != 5 && tau22DecayMode != 5)
      { 
        DiTauDR_->Fill(taudr2);
      }//21DecayMode != 5 22DecayMode != 5
    }//if pdgId == 35
  }//for iGenDaughters


}//End GGHAnalyzer::analyze


// ------------ method called once each job just before starting event loop  ------------
void GGHAnalyzer::beginJob()
{
  //Open output file
  out_ = new TFile(outFileName_.c_str(), "RECREATE");

  //Book histograms
  AEtaPart_ = new TH1F("AEtaPart", "", 50, -10, 10);
  APhiPart_ = new TH1F("APhiPart", "", 50, -3.5, 3.5);
  AdRPart_  = new TH1F("AdRPart", "", 50, -.5, 10);
  A1EtaVsA2EtaPart_ = new TH2F("A1EtaVsA2EtaPart", "", 50, -8, 8, 50, -8, 8);
  AdPhiPart_ = new TH1F("AdPhiPart", "", 50, -3.5, 3.5);
  AdEtaVsAdPhiPart_ = new TH2F("AdEtaVsAdPhiPart" , "" , 50, -8, 8, 50, -3.5, 3.5);
  TauPtPart_ = new TH1F("TauPtPart", "", 100, -.5, 150);
  APtPart_ = new TH1F("APtPart", "", 100, -.5, 150);

  TauPt1Part_ = new TH1F("TauPt1Part", "", 50, 0, 100);
  TauPt2Part_ = new TH1F("TauPt2Part", "", 50, 0, 100);
  TauPt3Part_ = new TH1F("TauPt3Part", "", 50, 0, 100);
  TauPt4Part_ = new TH1F("TauPt4Part", "", 50, 0, 100);
  TauPtHighPart_ = new TH1F("TauPtHighPart", "", 50, 0, 100);
  TauPtLowPart_ = new TH1F("TauPtLowPart", "", 50, 0, 100);
  TauDecayMode_ = new TH1F("TauDecayMode", "", 7, -.5, 6.5);
  TauPt_ = new TH1F("TauPt", "", 50, 0, 100);
  DiTauDR_ = new TH1F("DiTauDR", "", 50, 0, 10);
  TauEta_ = new TH1F("TauEta", "", 50, -8, 8);
  TauPhi_ = new TH1F("TauPhi", "", 50, -3.2, 3.2);

  DiTauDRVsAPt_ = new TH2F("DiTauDRVsAPt", "", 50, 0.0, 10.0, 50, 0.0, 80.0);
  DiTauDRVsAEta_ = new TH2F("DiTauDRVsAEta", "", 50, 0.0, 10.0, 50, -6.0, 6.0);

  TauDecayMode_->GetXaxis()->SetBinLabel(1, "1-prong");
  TauDecayMode_->GetXaxis()->SetBinLabel(2, "1-prong + 1 #pi^{0}");
  TauDecayMode_->GetXaxis()->SetBinLabel(3, "1-prong + 2 #pi^{0}");
  TauDecayMode_->GetXaxis()->SetBinLabel(4, "3-prong");
  TauDecayMode_->GetXaxis()->SetBinLabel(5, "other");
  TauDecayMode_->GetXaxis()->SetBinLabel(6, "Electron");
  TauDecayMode_->GetXaxis()->SetBinLabel(7, "Muon");

  
}

// ------------ method called once each job just after ending the event loop  ------------
void GGHAnalyzer::endJob()
{

std::cout << "Making Canvases" << std::endl;
  //Make the Canvases
  TCanvas AEtaPartCanvas("AEtaPart","",600,600);
  TCanvas APhiPartCanvas("APhiPart","",600,600);
  TCanvas AdRPartCanvas("AdRPart","",600,600);
  TCanvas A1EtaVsA2EtaPartCanvas("A1EtaVsA2EtaPart","",600,600);
  TCanvas AdPhiPartCanvas("AdPhiPart","",600,600);
  TCanvas AdEtaVsAdPhiPartCanvas("AdEtaVsAdPhiPart","",600,600);
  TCanvas TauPtPartCanvas("TauPtPart","",600,600);
  TCanvas APtPartCanvas("APtPart","",600,600);

  TCanvas TauPt1PartCanvas("TauPt1Part", "", 600, 600);
  TCanvas TauPt2PartCanvas("TauPt2Part","",600,600);
  TCanvas TauPt3PartCanvas("TauPt3Part","",600,600);
  TCanvas TauPt4PartCanvas("TauPt4Part","",600,600);
  TCanvas TauPtHighPartCanvas("TauPtHighPart","",600,600);
  TCanvas TauPtLowPartCanvas("TauPtLowPart","",600,600);
  TCanvas TauDecayModeCanvas("TauDecayMode","",600,600);
  TCanvas TauPtCanvas("TauPt","",600,600);
  TCanvas DiTauDRCanvas("DiTauDR","",600,600);
  TCanvas TauEtaCanvas("TauEta","",600,600);
  TCanvas TauPhiCanvas("TauPhi","",600,600);

  TCanvas DiTauDRVsAPtCanvas("DiTauDRVsAPt","" ,600,600);
  TCanvas DiTauDRVsAEtaCanvas("DiTauDRVsAEta","" ,600,600);
  TCanvas ABDRVsAPtCanvas("ABDRVsAPt","",600,600);

  //Format the 1D plots and Draw (canvas, hist, grid, log y, log z, color, size, style, xAxisTitle, xTitleSize, xLabelSize, xTitleOffSet, yAxisTitle, yTitleSize, yLabelSize, yTitleOffset)
  VariousFunctions::formatAndDrawCanvasAndHist1D(AEtaPartCanvas, AEtaPart_, 1, 0, 0, kBlack, 0.7, 20, "#eta(A) true", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(APhiPartCanvas, APhiPart_, 1, 0, 0, kBlack, 0.7, 20, "#phi(A true)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(AdRPartCanvas, AdRPart_, 1, 0, 0, kBlack, 0.7, 20, "dR(A1 A2 true)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist2D(A1EtaVsA2EtaPartCanvas, A1EtaVsA2EtaPart_, 0, 0, 0, kBlack, 7, 20, "#eta(A1 true)", .04, .04, 1.1, "#eta(A2 true)", .04, .04, 1.6, "", .04, .04, 1.0);
  VariousFunctions::formatAndDrawCanvasAndHist1D(AdPhiPartCanvas, AdPhiPart_, 1, 0, 0, kBlack, 0.7, 20, "#Delta#phi(A1 A2 true)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist2D(AdEtaVsAdPhiPartCanvas, AdEtaVsAdPhiPart_, 0, 0, 0, kBlack, 7, 20, "#Delta#eta(A1 A2 true)", .04, .04, 1.1, "d#phi(A1 A2 true)", .04, .04, 1.6, "", .04, .04, 1.0);
  VariousFunctions::formatAndDrawCanvasAndHist1D(TauPtPartCanvas, TauPtPart_, 1, 0, 0, kBlack, 0.7, 20, "Pt(#tau true)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(APtPartCanvas, APtPart_, 1, 0, 0, kBlack, 0.7, 20, "Pt(a True)", .04, .04, 1, "", .04, .04, 1, false);

  VariousFunctions::formatAndDrawCanvasAndHist1D(TauPt1PartCanvas, TauPt1Part_, 1, 0, 0, kBlack, 0.7, 20, "Pt(#tau) 1st True", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(TauPt2PartCanvas, TauPt2Part_, 1, 0, 0, kBlack, 0.7, 20, "Pt(#tau) 2nd True", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(TauPt3PartCanvas, TauPt3Part_, 1, 0, 0, kBlack, 0.7, 20, "Pt(#tau) 3rd True", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(TauPt4PartCanvas, TauPt4Part_, 1, 0, 0, kBlack, 0.7, 20, "Pt(#tau) 4th True", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(TauPtHighPartCanvas, TauPtHighPart_, 1, 0, 0, kBlack, 0.7, 20, "Pt(#tau) High True", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(TauPtLowPartCanvas, TauPtLowPart_, 1, 0, 0, kBlack, 0.7, 20, "Pt(#tau) Low True", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(TauDecayModeCanvas, TauDecayMode_, 1, 0, 0, kBlack, 0.7, 20, "", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(TauPtCanvas, TauPt_, 1, 0, 0, kBlack, 0.7, 20, "Pt(#tau)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(DiTauDRCanvas, DiTauDR_, 1, 0, 0, kBlack, 0.7, 20, "dR(#tau #tau)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(TauEtaCanvas, TauEta_, 1, 0, 0, kBlack, 0.7, 20, "#eta(#tau)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(TauPhiCanvas, TauPhi_, 1, 0, 0, kBlack, 0.7, 20, "#phi(#tau)", .04, .04, 1, "", .04, .04, 1, false);

  //format the 2d plots and draw (canvas, hist, grid, log y, log z, color, size, style, xaxistitle, xtitlesize, xlabelsize, xtitleoffset, yaxistitle, ytitlesize, ylabelsize, ytitleoffset,
  			      // zAxisTitle, zTitleSize, zLabelSize, zTitleOffset)
  VariousFunctions::formatAndDrawCanvasAndHist2D(DiTauDRVsAPtCanvas, DiTauDRVsAPt_, 0, 0, 0, kBlack, 7, 20, "dR(#tau#tau)", .04, .04, 1.1, "Pt(a1)", .04, .04, 1.6, "", .04, .04, 1.0);
  VariousFunctions::formatAndDrawCanvasAndHist2D(DiTauDRVsAEtaCanvas, DiTauDRVsAEta_, 0, 0, 0, kBlack, 7, 20, "dR(#tau#tau)", .04, .04, 1.1, "#eta(a1)", .04, .04, 1.6, "", .04, .04, 1.0);

  //Write output file
  out_->cd();
  AEtaPartCanvas.Write();
  APhiPartCanvas.Write();
  AdRPartCanvas.Write();
  A1EtaVsA2EtaPartCanvas.Write();
  AdPhiPartCanvas.Write();
  AdEtaVsAdPhiPartCanvas.Write();
  TauPtPartCanvas.Write();
  APtPartCanvas.Write();

  TauPt1PartCanvas.Write();
  TauPt2PartCanvas.Write();
  TauPt3PartCanvas.Write();
  TauPt4PartCanvas.Write();
  TauPtHighPartCanvas.Write();
  TauPtLowPartCanvas.Write();
  TauDecayModeCanvas.Write();
  TauPtCanvas.Write();
  DiTauDRCanvas.Write();
  TauEtaCanvas.Write();
  TauPhiCanvas.Write();

  DiTauDRVsAPtCanvas.Write();
  DiTauDRVsAEtaCanvas.Write();
  out_->Write();
  out_->Close();
std::cout << "DONE" << std::endl;
}//EndJob

// ------------ method called when starting to processes a run  ------------
void GGHAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&) {}

// ------------ method called when ending the processing of a run  ------------
void GGHAnalyzer::endRun(edm::Run const&, edm::EventSetup const&) {}

// ------------ method called when starting to processes a luminosity block  ------------
void GGHAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {}

// ------------ method called when ending the processing of a luminosity block  ------------
void GGHAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {}

//Delete Memory
void GGHAnalyzer::reset(const bool doDelete)
{
  if ((doDelete) && (out_ != NULL)) delete out_;
  out_ = NULL;

  if ((doDelete) && (AEtaPart_ != NULL)) delete AEtaPart_;
  AEtaPart_ = NULL;
  if ((doDelete) && (APhiPart_ != NULL)) delete APhiPart_;
  APhiPart_ = NULL;
  if ((doDelete) && (AdRPart_ != NULL)) delete AdRPart_;
  AdRPart_ = NULL;
  if ((doDelete) && (A1EtaVsA2EtaPart_ != NULL)) delete A1EtaVsA2EtaPart_;
  A1EtaVsA2EtaPart_ = NULL;
  if ((doDelete) && (AdPhiPart_ != NULL)) delete AdPhiPart_;
  AdPhiPart_ = NULL;
  if ((doDelete) && (AdEtaVsAdPhiPart_ != NULL)) delete AdEtaVsAdPhiPart_;
  AdEtaVsAdPhiPart_ = NULL;
  if ((doDelete) && (TauPtPart_ != NULL)) delete TauPtPart_;
  TauPtPart_ = NULL;
  if ((doDelete) && (APtPart_ != NULL)) delete APtPart_;
  APtPart_ = NULL;


  if ((doDelete) && (TauPt1Part_ != NULL)) delete TauPt1Part_;
  TauPt1Part_ = NULL;
  if ((doDelete) && (TauPt2Part_ != NULL)) delete TauPt2Part_;
  TauPt2Part_ = NULL;
  if ((doDelete) && (TauPt3Part_ != NULL)) delete TauPt3Part_;
  TauPt3Part_ = NULL;
  if ((doDelete) && (TauPt4Part_ != NULL)) delete TauPt4Part_;
  TauPt4Part_ = NULL;  
  if ((doDelete) && (TauPtHighPart_ != NULL)) delete TauPtHighPart_;
  TauPtHighPart_ = NULL; 
  if ((doDelete) && (TauPtLowPart_ != NULL)) delete TauPtLowPart_;
  TauPtLowPart_ = NULL;
  if ((doDelete) && (TauDecayMode_ != NULL)) delete TauDecayMode_;
  TauDecayMode_ = NULL;
  if ((doDelete) && (TauPt_ != NULL)) delete TauPt_;
  TauPt_ = NULL;
  if ((doDelete) && (DiTauDR_ != NULL)) delete DiTauDR_;
  DiTauDR_ = NULL;
  if ((doDelete) && (TauEta_ != NULL)) delete TauEta_;
  TauEta_ = NULL;
  if ((doDelete) && (TauPhi_ != NULL)) delete TauPhi_;
  TauPhi_ = NULL;



  if ((doDelete) && (DiTauDRVsAPt_ != NULL)) delete  DiTauDRVsAPt_;
  DiTauDRVsAPt_ = NULL;
  if ((doDelete) && (DiTauDRVsAEta_ != NULL)) delete DiTauDRVsAEta_;
  DiTauDRVsAEta_ = NULL;
}//void GGHAnalyzer

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void GGHAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(GGHAnalyzer);
