// -*- C++ -*-
//
// Package:    Wh1Analyzer
// Class:      Wh1Analyzer
// 
/**\class Wh1Analyzer Wh1Analyzer.cc Analyzer/src/Wh1Analyzer.cc

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

class Wh1Analyzer : public edm::EDAnalyzer {
   public:
      explicit Wh1Analyzer(const edm::ParameterSet&);
      ~Wh1Analyzer();

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
      TH1F* TauDecayLabeled_;
      TH1F* TauNDaughters_;
      TH1F* TauPtPho_;
      TH1F* TauPtPi_;
      TH1F* TauEta_;
      TH1F* MuonPt_;

      TH1F* APt_;
      TH1F* AEta_;
      TH1F* ATheta_;
      TH1F* DiTauDR_; 
      TH1F* DiADR_;

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
Wh1Analyzer::Wh1Analyzer(const edm::ParameterSet& iConfig):
  outFileName_(iConfig.getParameter<std::string>("outFileName")),
  genParticleTag_(iConfig.getParameter<edm::InputTag>("genParticleTag"))
{
  reset(false);    
}//Wh1Analyzer



Wh1Analyzer::~Wh1Analyzer()
{
  reset(true);
}


//
// member functions
//

// ------------ method called for each event  ------------
void Wh1Analyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  //Get gen particle collection
  edm::Handle<reco::GenParticleCollection> pGenParticles;
  iEvent.getByLabel(genParticleTag_, pGenParticles);
  std::cout << "\n\nTHIS IS A NEW EVENT" << std::endl;
  int check = 0;

  //Checks for a W decaying to a muon
  for (reco::GenParticleCollection::const_iterator iGenParticle = pGenParticles->begin(); iGenParticle != pGenParticles->end(); ++iGenParticle)
  {
    if(fabs(iGenParticle->pdgId()) == 13 && (iGenParticle->mother()->pdgId()) == 24)
    {
      check++;
      std::cout << "\tFound a Wmu." << std::endl;
    }//if pdgid == 13 and pdgid == 24
  }//for iGenParticle

  //Cycling through all of the particles in each event
  for (reco::GenParticleCollection::const_iterator iGenParticle = pGenParticles->begin(); iGenParticle != pGenParticles->end(); ++iGenParticle)
  {
    reco::GenParticleRef a1Ref, a2Ref;
    reco::LeafCandidate::LorentzVector tau11P4, tau12P4, tau21P4, tau22P4, a1P4, a2P4;
    if(iGenParticle->pdgId() == 35 && iGenParticle->numberOfDaughters() == 2 && iGenParticle->daughter(0)->pdgId() == 36 && check != 0)
    {
      std::cout << "Found a H and it has " << iGenParticle->numberOfDaughters() << " daughters." << std::endl;
      a1Ref = iGenParticle->daughterRef(0), a2Ref = iGenParticle->daughterRef(1);

      std::cout << "\tchild1 has pdgId= " << a1Ref->pdgId() << "and has " << a1Ref->numberOfDaughters() << " Daughters." <<  std::endl;
      for(unsigned int i=0; i < a1Ref->numberOfDaughters(); i++)
	std::cout << "\t\tchild1's daughter #" << i << " has a pdgId= " << a1Ref->daughter(i)->pdgId() << std::endl;

      std::cout << "\tchild2 has pdgId= " << a2Ref->pdgId() << "and has " << a2Ref->numberOfDaughters() << std::endl;
      for(unsigned int i=0; i < a2Ref->numberOfDaughters(); i++)
        std::cout << "\t\tchild2's daughter #" << i << " has a pdgId= " << a1Ref->daughter(i)->pdgId() << std::endl;;
 
      reco::GenParticleRef tau11Ref, tau12Ref, tau21Ref, tau22Ref;
      int tau11DecayMode = 5, tau12DecayMode = 5;
      int tau21DecayMode = 5, tau22DecayMode = 5;
      tau11Ref = VariousFunctions::findDaughterInDaughters(a1Ref, 15, false);
      tau12Ref = VariousFunctions::findDaughterInDaughters(a1Ref, -15, false);

      if(VariousFunctions::findIfInDaughters(tau11Ref, 15, true))
        tau11Ref = VariousFunctions::findDaughterInDaughters(tau11Ref, 15, true);
      if(VariousFunctions::findIfInDaughters(tau12Ref, 15, true))
        tau12Ref = VariousFunctions::findDaughterInDaughters(tau12Ref, 15, true);

      tau11DecayMode = VariousFunctions::tauDecayMode(tau11Ref), tau12DecayMode = VariousFunctions::tauDecayMode(tau12Ref);

      if(tau11DecayMode != 5)
      {
	tau11P4 = VariousFunctions::sumTauP4(tau11Ref, tau11DecayMode, false);
    	TauPtPi_->Fill(tau11P4.Pt() );
	tau11P4 = VariousFunctions::sumTauP4(tau11Ref, tau11DecayMode, true);
        TauPtPho_->Fill(tau11P4.Pt() );
  	TauEta_->Fill(tau11P4.Eta() );
      }//f tau11DecayMode != 5
      if(tau12DecayMode != 5)
      { 
	tau12P4 = VariousFunctions::sumTauP4(tau12Ref, tau12DecayMode, false);
        TauPtPi_->Fill(tau12P4.Pt() );
        tau12P4 = VariousFunctions::sumTauP4(tau12Ref, tau12DecayMode, true);
        TauPtPho_->Fill(tau12P4.Pt() );
        TauEta_->Fill(tau12P4.Eta() );
      }//if tau12DecayMode != 5
      if(tau11DecayMode != 5 && tau12DecayMode !=5)
        DiTauDR_->Fill(VariousFunctions::getDiTauDR(tau11Ref, tau12Ref, true));

      if(VariousFunctions::findIfInDaughters(a2Ref, 15, false))
      {
        tau21Ref = VariousFunctions::findDaughterInDaughters(a2Ref, 15, false);
        tau22Ref = VariousFunctions::findDaughterInDaughters(a2Ref, -15, false);

        if(VariousFunctions::findIfInDaughters(tau21Ref, 15, true))
          tau21Ref = VariousFunctions::findDaughterInDaughters(tau21Ref, 15, true);
        if(VariousFunctions::findIfInDaughters(tau22Ref, 15, true))
          tau22Ref = VariousFunctions::findDaughterInDaughters(tau22Ref, 15, true);

        tau21DecayMode = VariousFunctions::tauDecayMode(tau21Ref), tau22DecayMode = VariousFunctions::tauDecayMode(tau22Ref);
	if(tau21DecayMode != 5)
	{
	  tau21P4 = VariousFunctions::sumTauP4(tau21Ref, tau21DecayMode, false);
          TauPtPi_->Fill(tau21P4.Pt() );
          tau21P4 = VariousFunctions::sumTauP4(tau21Ref, tau21DecayMode, true);
          TauPtPho_->Fill(tau21P4.Pt() );
          TauEta_->Fill(tau21P4.Eta() );
	}//iftau21DecayMode != 5
	if(tau22DecayMode != 5)
	{
          tau22P4 = VariousFunctions::sumTauP4(tau22Ref, tau22DecayMode, false);
          TauPtPi_->Fill(tau22P4.Pt() );
	  std::cout << "\t\ttau22PtPi= " << tau22P4.Pt() << std::endl;
          tau22P4 = VariousFunctions::sumTauP4(tau22Ref, tau22DecayMode, true);
          TauPtPho_->Fill(tau22P4.Pt() );
	  std::cout << "\t\ttau22PtPho= " << tau22P4.Pt() << std::endl;
          TauEta_->Fill(tau22P4.Eta() );
	}//iftau22DecayMode ~= 5
	if(tau21DecayMode != 5 && tau22DecayMode !=5)
          DiTauDR_->Fill(VariousFunctions::getDiTauDR(tau21Ref, tau22Ref, true));	

      }//if decayMode != 5

      if(VariousFunctions::findIfInDaughters(a1Ref, 15, false) && VariousFunctions::findIfInDaughters(a2Ref, 15, false) && tau11DecayMode != 5 && tau22DecayMode != 5 && tau12DecayMode !=5 && tau21DecayMode !=5)
      {
	a1P4 = tau11P4 + tau12P4;
	a2P4 = tau21P4 + tau22P4;
	double a1Eta = a1P4.Eta(), a2Eta = a2P4.Eta(), a1Theta = a1P4.Theta(), a2Theta = a2P4.Theta();
        double diADR = sqrt( (a1Eta - a2Eta)*(a1Eta - a2Eta)  +  (a1Theta - a2Theta)*(a1Theta - a2Theta) );
	AEta_->Fill(a1Eta);
	AEta_->Fill(a2Eta);
	ATheta_->Fill(a1Theta);
	ATheta_->Fill(a2Theta);
        DiADR_->Fill(diADR);
        MuonPt_->Fill(iGenParticle->pt() );
      }//if 2 VariousFunctions::findIfInDaughters(a2Ref, 15, false)
    }//if pdgId == 35

  }//for iGenDaughters


}//End Wh1Analyzer::analyze


// ------------ method called once each job just before starting event loop  ------------
void Wh1Analyzer::beginJob()
{
  //Open output file
  out_ = new TFile(outFileName_.c_str(), "RECREATE");

  //Book histograms
  TauDecayLabeled_ = new TH1F("TauDecayLabeled", "", 7, 0, 7);
  TauNDaughters_ = new TH1F("TauNDaughters", "", 200, -100, 100);
  TauPtPho_ = new TH1F("TauPtPho", "", 50, 0, 50);
  TauPtPi_ = new TH1F("TauPtPi", "", 50, 0, 50);
  TauEta_ = new TH1F("TauEta", "", 50, -10, 10);
  MuonPt_ = new TH1F("MuonPt", "", 50, -10, 10);

  APt_ = new TH1F("AOt", "", 100, 0, 50);
  AEta_ = new TH1F("AEta", "", 50, -6, 6);
  ATheta_ = new TH1F("ATheta", "", 50, 0, 4);
  DiTauDR_ = new TH1F("DiTauDR", "", 50, 0, 10);
  DiADR_ = new TH1F("DiADR", "", 50, 0, 10);

  DiTauDRVsAPt_ = new TH2F("DiTauDRVsAPt", "", 50, 0.0, 10.0, 50, 0.0, 80.0);
  DiTauDRVsAEta_ = new TH2F("DiTauDRVsAEta", "", 50, 0.0, 10.0, 50, -6.0, 6.0);
  
  //Set Bin Labeles
  TauDecayLabeled_->GetXaxis()->SetBinLabel(1, "1-prong");
  TauDecayLabeled_->GetXaxis()->SetBinLabel(2, "1-prong + 1 #pi^{0}");
  TauDecayLabeled_->GetXaxis()->SetBinLabel(3, "1-prong + 2 #pi^{0}");
  TauDecayLabeled_->GetXaxis()->SetBinLabel(4, "3-prong");
  TauDecayLabeled_->GetXaxis()->SetBinLabel(5, "other");
  TauDecayLabeled_->GetXaxis()->SetBinLabel(6, "Electron");
  TauDecayLabeled_->GetXaxis()->SetBinLabel(7, "Muon");

}

// ------------ method called once each job just after ending the event loop  ------------
void Wh1Analyzer::endJob()
{

std::cout << "Making Canvases" << std::endl;
  //Make the Canvases
  TCanvas TauDecayLabeledCanvas("TauDecayLabeled", "", 600, 600);
  TCanvas TauNDaughtersCanvas("TauNDaughters","",600,600);
  TCanvas TauPtPhoCanvas("TauPtPho","",600,600);
  TCanvas TauPtPiCanvas("TauPtPi","",600,600);
  TCanvas TauEtaCanvas("TauEta","",600,600);
  TCanvas MuonPtCanvas("MuonPt","",600,600);

  TCanvas APtCanvas("APt","",600,600);
  TCanvas AEtaCanvas("AEta","",600,600);
  TCanvas AThetaCanvas("ATheta","",600,600);
  TCanvas DiTauDRCanvas("DiTauDR","",600,600);
  TCanvas DiADRCanvas("DiADR","",600,600);

  TCanvas DiTauDRVsAPtCanvas("DiTauDRVsAPt","" ,600,600);
  TCanvas DiTauDRVsAEtaCanvas("DiTauDRVsAEta","" ,600,600);
  TCanvas ABDRVsAPtCanvas("ABDRVsAPt","",600,600);

  //Format the 1D plots and Draw (canvas, hist, grid, log y, log z, color, size, style, xAxisTitle, xTitleSize, xLabelSize, xTitleOffSet, yAxisTitle, yTitleSize, yLabelSize, yTitleOffset)
  VariousFunctions::formatAndDrawCanvasAndHist1D(TauDecayLabeledCanvas, TauDecayLabeled_, 1, 0, 0, kBlack, 0.7, 20, "#tau Decays", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(TauNDaughtersCanvas, TauNDaughters_, 1, 0, 0, kBlack, 0.7, 20, "N #tau Daughters", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(TauPtPhoCanvas, TauPtPho_, 1, 0, 0, kBlack, 0.7, 20, "Visible #tau_{pt}", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(TauPtPiCanvas, TauPtPi_, 1, 0, 0, kBlack, 0.7, 20, "Visible #tau_{Pt}", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(TauEtaCanvas, TauEta_, 1, 0, 0, kBlack, 0.7, 20, "Visible #tau_{#eta}", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(MuonPtCanvas, MuonPt_, 1, 0, 0, kBlack, 0.7, 20, "Pt_{#mu}", .04, .04, 1, "", .04, .04, 1, false);

  VariousFunctions::formatAndDrawCanvasAndHist1D(APtCanvas, APt_, 1, 0, 0, kBlack, 0.7, 20, "A_{Pt}", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(AEtaCanvas, AEta_, 1, 0, 0, kBlack, 0.7, 20, "A_{#eta}", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(AThetaCanvas, ATheta_, 1, 0, 0, kBlack, 0.7, 20, "A_{#eta}", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(DiTauDRCanvas, DiTauDR_, 1, 0, 0, kBlack, 0.7, 20, "dR_{#tau #tau}", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(DiADRCanvas, DiADR_, 1, 0, 0, kBlack, 0.7, 20, "dR_{#tau #tau}", .04, .04, 1, "", .04, .04, 1, false);

  //format the 2d plots and draw (canvas, hist, grid, log y, log z, color, size, style, xaxistitle, xtitlesize, xlabelsize, xtitleoffset, yaxistitle, ytitlesize, ylabelsize, ytitleoffset,
  			      // zAxisTitle, zTitleSize, zLabelSize, zTitleOffset)
  VariousFunctions::formatAndDrawCanvasAndHist2D(DiTauDRVsAPtCanvas, DiTauDRVsAPt_, 0, 0, 0, kBlack, 7, 20, "dR_{#tau#tau}", .04, .04, 1.1, "A_{Pt}", .04, .04, 1.6, "", .04, .04, 1.0);
  VariousFunctions::formatAndDrawCanvasAndHist2D(DiTauDRVsAEtaCanvas, DiTauDRVsAEta_, 0, 0, 0, kBlack, 7, 20, "dR_{#tau#tau}", .04, .04, 1.1, "A_{#eta}", .04, .04, 1.6, "", .04, .04, 1.0);

  //Write output file
  out_->cd();
  TauDecayLabeledCanvas.Write();
  TauNDaughtersCanvas.Write();
  TauPtPhoCanvas.Write();
  TauPtPiCanvas.Write();
  TauEtaCanvas.Write();
  MuonPtCanvas.Write();
  APtCanvas.Write();
  AEtaCanvas.Write();
  AThetaCanvas.Write();
  DiTauDRCanvas.Write();
  DiADRCanvas.Write();

  DiTauDRVsAPtCanvas.Write();
  DiTauDRVsAEtaCanvas.Write();
  out_->Write();
  out_->Close();
std::cout << "DONE" << std::endl;
}//EndJob

// ------------ method called when starting to processes a run  ------------
void Wh1Analyzer::beginRun(edm::Run const&, edm::EventSetup const&) {}

// ------------ method called when ending the processing of a run  ------------
void Wh1Analyzer::endRun(edm::Run const&, edm::EventSetup const&) {}

// ------------ method called when starting to processes a luminosity block  ------------
void Wh1Analyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {}

// ------------ method called when ending the processing of a luminosity block  ------------
void Wh1Analyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {}

//Delete Memory
void Wh1Analyzer::reset(const bool doDelete)
{
  if ((doDelete) && (out_ != NULL)) delete out_;
  out_ = NULL;
  if ((doDelete) && (TauDecayLabeled_ != NULL)) delete TauDecayLabeled_;
  TauDecayLabeled_ = NULL;
  if ((doDelete) && (TauNDaughters_ != NULL)) delete TauNDaughters_;
  TauNDaughters_ = NULL;
  if ((doDelete) && (TauPtPho_ != NULL)) delete TauPtPho_;
  TauPtPho_ = NULL;
  if ((doDelete) && (TauPtPi_ != NULL)) delete TauPtPi_;
  TauPtPi_ = NULL;  
  if ((doDelete) && (TauEta_ != NULL)) delete TauEta_;
  TauEta_ = NULL; 
  if ((doDelete) && (MuonPt_ != NULL)) delete MuonPt_;
  MuonPt_ = NULL;

  if ((doDelete) && (APt_ != NULL)) delete APt_;
  APt_ = NULL;
  if ((doDelete) && (AEta_ != NULL)) delete AEta_;
  AEta_ = NULL;
  if ((doDelete) && (ATheta_ != NULL)) delete ATheta_;
  ATheta_ = NULL;
  if ((doDelete) && (DiTauDR_ != NULL)) delete DiTauDR_;
  DiTauDR_ = NULL;
  if ((doDelete) && (DiADR_ != NULL)) delete DiADR_;
  DiADR_ = NULL;

  if ((doDelete) && (DiTauDRVsAPt_ != NULL)) delete  DiTauDRVsAPt_;
  DiTauDRVsAPt_ = NULL;
  if ((doDelete) && (DiTauDRVsAEta_ != NULL)) delete DiTauDRVsAEta_;
  DiTauDRVsAEta_ = NULL;
}//void Wh1Analyzer

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void Wh1Analyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(Wh1Analyzer);
