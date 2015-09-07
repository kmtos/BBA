// -*- C++ -*-
//
// Package:    BBAAnalyzer
// Class:      BBAAnalyzer
// 
/**\class BBAAnalyzer BBAAnalyzer.cc Analyzer/src/BBAAnalyzer.cc

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

// user include files
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/Common/interface/Ref.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/JetReco/interface/GenJet.h"
#include "DataFormats/JetReco/interface/Jet.h"
#include "DataFormats/JetReco/interface/JetCollection.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/JetReco/interface/JetFloatAssociation.h"

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "HLTrigger/HLTanalyzers/interface/HLTInfo.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"
#include "HLTrigger/HLTcore/interface/HLTConfigData.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"
#include "SimDataFormats/JetMatching/interface/JetFlavour.h"
#include "SimDataFormats/JetMatching/interface/JetFlavourMatching.h"

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
// class declaration
//

class BBAAnalyzer : public edm::EDAnalyzer {
   public:
      typedef reco::JetFloatAssociation::Container JetBCEnergyRatioCollection;
      explicit BBAAnalyzer(const edm::ParameterSet&);
      ~BBAAnalyzer();

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

      //openning the jet output file
      ofstream jetOutput_;

      //name of output root file
      std::string outFileName_;

      //name of output jetOutput file
      std::string jetOutputFileName_;

      //gen particle tag
      edm::InputTag genParticleTag_;

      //gen jet tag
      edm::InputTag genJetTag_;

      //bRatio token tag
      edm::EDGetTokenT<JetBCEnergyRatioCollection> sourceBratioToken_;
      edm::Handle<JetBCEnergyRatioCollection>   theBratioValue;

      //cRatio token tag
      edm::EDGetTokenT<JetBCEnergyRatioCollection> sourceCratioToken_;
      edm::Handle<JetBCEnergyRatioCollection>   theCratioValue;

      //Histiograms
      TH1F* BPtCut_;
      TH1F* BPtMatchCut_;
      TH1F* TauPt_;

      TH1F* APt_;
      TH1F* DiTauDR_; 
      TH1F* BPtMatch_;
      TH1F* ABDR_;
      TH1F* TauMuPt_;
      TH1F* BPt_;
      TH1F* BPtHigh_;
      TH1F* BPtLow_;
      TH1F* DiBPt_;
      TH1F* DRbPartbRatio_;
      TH1F* PtDiffbPartbRatio_;
      TH1F* BMuPt_;
      TH1F* AMass_;

      TH2F* DiTauDRVsAPt_;
      TH2F* DiTauDRVsAEta_;
      TH2F* DiTauDRVsBPtLow_;
      TH2F* DiTauDRVsBPtHigh_;
      TH2F* DiTauDRVsBPtBestMatch_;
      TH2F* DiTauDRVsBPt2ndBestMatch_;
      TH2F* ABDRVsAPt_;
      TH2F* ABDRVsDiTauDR_;

      TH2F* SumBRatioVsBPartBRatiodR_;
      TH1F* BRatiosWithLargeDR_;

      TH1F* NEvents_;
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
BBAAnalyzer::BBAAnalyzer(const edm::ParameterSet& iConfig):
  outFileName_(iConfig.getParameter<std::string>("outFileName")),
  jetOutputFileName_(iConfig.getParameter<std::string>("jetOutputFileName")), 
  genParticleTag_(iConfig.getParameter<edm::InputTag>("genParticleTag")),
  genJetTag_(iConfig.getParameter<edm::InputTag>("genJetTag"))
{
  sourceBratioToken_  = consumes<JetBCEnergyRatioCollection>(iConfig.getParameter<InputTag> ("bRatioTag" ));
  sourceCratioToken_  = consumes<JetBCEnergyRatioCollection>(iConfig.getParameter<InputTag> ("cRatioTag" ));
  reset(false);    
}//BBAAnalyzer



BBAAnalyzer::~BBAAnalyzer()
{
  reset(true);
}


//
// member functions
//

// ------------ method called for each event  ------------
void BBAAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  //Get gen particle collection
  edm::Handle<reco::GenParticleCollection> pGenParticles;
  iEvent.getByLabel(genParticleTag_, pGenParticles);
  std::cout << "\nTHIS IS A NEW EVENT" << std::endl;
  NEvents_->Fill(0.01);
  
  //Get gen jet collection
  edm::Handle<reco::GenJetCollection> pGenJets;
  iEvent.getByLabel(genJetTag_, pGenJets);

  //Get BCRatio Collection
  iEvent.getByToken (sourceBratioToken_ , theBratioValue);
  iEvent.getByToken (sourceCratioToken_ , theCratioValue);

//
//  This selects the two jets with the largest bRatio: jet1, jet2
//
  double br1 = 0, br2 = 0, bcdiff1 = 0, bcdiff2 = 0;
  int Big1JetN=0, Big2JetN=0, i=0;

  if (theBratioValue->size() < 1)
    return ;
  JetBCEnergyRatioCollection::const_iterator initB = theBratioValue->begin();
  Jet *jet1 =  const_cast<Jet*>(&*(initB->first) ), *jet2 =  const_cast<Jet*>(&*(initB->first) );
  for (JetBCEnergyRatioCollection::const_iterator itB = theBratioValue->begin(); itB != theBratioValue->end(); itB++)
  {
    Jet *jetB = const_cast<Jet*>(&*(itB->first) );
    double cR = 0;
jetOutput_ << "\tJet #" << i << " has bRatio= " << itB->second << "\thas pt=" << jetB->et() << "\tphi=" << jetB->phi() << "\teta= " << jetB->eta() << std::endl;
    for (JetBCEnergyRatioCollection::const_iterator itC = theCratioValue->begin(); itC != theCratioValue->end(); itC++)
    {
      if(itB->first == itC->first)
        cR=itC->second;
    }//for
    if(itB->second > br1)
    {
      br2 = br1;
      bcdiff2 = bcdiff1;
      jet2= jet1 ;
      br1 = itB->second;
      jet1= jetB;
      bcdiff1 = itB->second - cR;
      Big2JetN = Big1JetN;
      Big1JetN = i;
    }//if
    else if(itB->second > br2 && itB->second != br1)
    {
      br2 = itB->second;
      jet2= jetB;
      bcdiff2 = itB->second - cR;
      Big2JetN = i;
    }//else

    i++;
  }//for

   jetOutput_ << "\tLargest bRatio= " << br1 << " is Jet #" << Big1JetN << " and has pt= " << jet1->et() << " and has eta=" << jet1->eta() << " and has phi= " << jet1->phi() << std::endl;
   jetOutput_ << "\tSecond Largest bRatio= " << br2 << " is Jet #" << Big2JetN << " and has pt= " << jet2->et() << " and has eta=" << jet2->eta() << " and has phi= " << jet2->phi() << std::endl;
  //Cycling through all of the particles in each event
  for (reco::GenParticleCollection::const_iterator iGenParticle = pGenParticles->begin(); iGenParticle != pGenParticles->end(); ++iGenParticle)
  {

//
//This Selects the taus and calculates their decay mode, their dR  and aVisibleP4
//
    reco::LeafCandidate::LorentzVector tau1P4, tau2P4, aP4;
    if(iGenParticle->pdgId() == 36 && iGenParticle->numberOfDaughters() == 2 && fabs(iGenParticle->daughter(0)->pdgId()) == 15) //Finds an A that decays to two taus
    {
      reco::GenParticleRef tau1Ref = iGenParticle->daughterRef(0);
      reco::GenParticleRef tau2Ref = iGenParticle->daughterRef(1);

      //This makes sure that the intermediate (not final state) taus are not used
      while(VariousFunctions::findIfInDaughters(tau1Ref, 15, true) || VariousFunctions::findIfInDaughters(tau2Ref, 15, true))
      {
        if(VariousFunctions::findIfInDaughters(tau1Ref, 15, true))
  	  tau1Ref = VariousFunctions::findDaughterInDaughters(tau1Ref, 15, true);
        if(VariousFunctions::findIfInDaughters(tau2Ref, 15, true))
          tau2Ref = VariousFunctions::findDaughterInDaughters(tau2Ref, 15, true);
      }//while

      //Below I calculate the various tau and a1 quantities
      int tau1DecayMode = VariousFunctions::tauDecayMode(tau1Ref), tau2DecayMode = VariousFunctions::tauDecayMode(tau2Ref);
      double diTauDR = VariousFunctions::getDiTauDR(tau1Ref, tau2Ref, true);
//
//This gets the bParticles that are sisters to the a
//
      reco::GenParticleRef mother = iGenParticle->motherRef(), bRef = iGenParticle->motherRef(), bbarRef = iGenParticle->motherRef();
      while(mother->pdgId() == 36)
	mother = mother->motherRef();
      for(unsigned int i=0; i < mother->numberOfDaughters(); i++)
      {
        reco::GenParticleRef child = mother->daughterRef(i);
std::cout << "\tmom pdgid=" << mother->pdgId() << "\tchild pdgid=" << child->pdgId() << std::endl;
	if(child->pdgId() == 5 )
	  bRef = child;
	if(child->pdgId() == -5 )
 	  bbarRef = child;
        if(child->pdgId() == 36)
	  AMass_->Fill(child->mass() );
      }//for

//
//This calculates the differences in the various pairings of bRef's and the jets with the largest bRatios
//

      jetOutput_ << "\tbRef: pdgId= " << bRef->pdgId() << "  pt= " << bRef->pt() << "  eta= " << bRef->eta() << "  phi= " << bRef->phi() << std::endl;
      jetOutput_ << "\tbbar: pdgId= " << bbarRef->pdgId() << "  pt= " << bbarRef->pt() << "  eta= " << bbarRef->eta() << "  phi= " << bbarRef->phi() << std::endl;
      jetOutput_ << "\tbjet1: \t pt= " << jet1->et() << "  eta=" << jet1->eta() << "  phi= " << jet1->phi() << std::endl;
      jetOutput_ << "\tbjet2: \t pt= " << jet2->et() << "  eta=" << jet2->eta() << "  phi= " << jet2->phi() << bcdiff2 << std::endl;

      double b1pt = fabs(jet1->et() - bRef->pt() ), bbar1pt = fabs(jet1->et() - bbarRef->pt() ), b2pt = fabs(jet2->et() - bRef->pt() ), bbar2pt = fabs(jet2->et() - bbarRef->pt() );
      double b1eta = fabs(jet1->eta() - bRef->eta() ), bbar1eta = fabs(jet1->eta() - bbarRef->eta() ), b2eta = fabs(jet2->eta() - bRef->eta() ), bbar2eta = fabs(jet2->eta() - bbarRef->eta() );
      double b1phi = fabs(jet1->phi() - bRef->phi() ), bbar1phi = fabs(jet1->phi() - bbarRef->phi() ), b2phi = fabs(jet2->phi() - bRef->phi() ), bbar2phi = fabs(jet2->phi() - bbarRef->phi() );    
      double b1dr = sqrt( b1eta*b1eta + b1phi*b1phi), bbar1dr = sqrt( bbar1eta*bbar1eta + bbar1phi*bbar1phi ), b2dr = sqrt( b2eta*b2eta + b2phi*b2phi), bbar2dr = sqrt( bbar2eta*bbar2eta + bbar2phi*bbar2phi );
      jetOutput_ << "\t b1pt=" << b1pt << "  bbar1pt=" << bbar1pt << "  b2pt=" << b2pt << "  bbar2pt=" << bbar2pt << std::endl;
      jetOutput_ << "\t b1dr=" << b1dr << "  bbar1dr=" << bbar1dr << "  b2dr=" << b2dr << "  bbar2dr=" << bbar2dr << std::endl;
      double dr1corr = 0, dr2corr = 0, pt1corr = 0, pt2corr = 0;

//
//This tries to Match the jets with the largest bRatio to the correct bRef by finding the smallest dR of the pairings
//
      if(b1dr >= b2dr)  //b2dr smaller
      {
        if(bbar1dr >= bbar2dr)  //bbar2dr smaller
	{
	  if(bbar2dr >= b2dr)  //b2dr smallest of 4
	  {
	    dr1corr = bbar1dr;
	    dr2corr = b2dr;
	    pt1corr = bbar1pt;
	    pt2corr = b2pt;	    
	  }//if bbar b
	  else  //bbar2dr smallest of 4
	  {
            dr1corr = b1dr;
            dr2corr = bbar2dr;
            pt1corr = b1pt;
            pt2corr = bbar2pt;
	  }
	}//if bbar
	else  //b2dr and bbar1dr are smallest and that's good
	{
          dr1corr = bbar1dr;
          dr2corr = b2dr;
          pt1corr = bbar1pt;
          pt2corr = b2pt;	  
	}//else
      }//if bar
      else  //b1dr smaller
      {      
        if(bbar2dr > bbar1dr)  //bbar1dr smaller
        {
          if(bbar1dr > b1dr)  //b1dr is smallest of 4
          {
            dr1corr = b1dr;
            dr2corr = bbar2dr;
            pt1corr = b1pt;
            pt2corr = bbar2pt;
          }//if bbar b
          else  //bbar1dr is smallest of 4
          {
            dr1corr = bbar1dr;
            dr2corr = b2dr;
            pt1corr = bbar1pt;
            pt2corr = b2pt;
          }
        }//if bbar
        else   // b1dr bbar2dr are smallest and that's good
        {
          dr1corr = b1dr;
          dr2corr = bbar2dr;
          pt1corr = b1pt;
          pt2corr = bbar2pt;
        }//else
      }//else

//
//This is the end of my calculations and is the start of the plotting. I select only tau_mu * tau_Had Events
//
      if( (tau2DecayMode == 7 && tau1DecayMode <=4) || (tau1DecayMode == 7 && tau2DecayMode <=4) )
      {
        if(br1 > .1 && br2 > .1) // This cut gets rid of the very poor pairings by not using any of the largest bRatio jets with a very low bRatio
	{
          SumBRatioVsBPartBRatiodR_->Fill(br1 + br2, dr1corr);
          SumBRatioVsBPartBRatiodR_->Fill(br1 + br2, dr2corr);
          DRbPartbRatio_->Fill(dr1corr);
          DRbPartbRatio_->Fill(dr2corr);
          PtDiffbPartbRatio_->Fill(pt1corr);
          PtDiffbPartbRatio_->Fill(pt2corr);
	  //The next two plots are for looking at the bRatios of jets that pass the bRatio > .1 cut and still have a large dR between it and it's matched bRef
 	  if(dr1corr > 1.5)
	    BRatiosWithLargeDR_->Fill(br1);
  	  if(dr2corr > 1.5)
            BRatiosWithLargeDR_->Fill(br2);
	  //The proceeding if statement selects events that have at least 1 good bRef matching, via small dR, and plots the Pt_b
          if(dr1corr < 1 || dr2corr < 1)
 	  {
	    if(dr1corr < 1)//Only Fills if a good b match
	      BPtMatch_->Fill(jet1->et() );
	    if(dr2corr < 1)//Only Fills itf a good b match
	      BPtMatch_->Fill(jet2->et() );
	    if( dr1corr > dr2corr)
	    {
	      DiTauDRVsBPtBestMatch_->Fill(diTauDR, jet2->et() );
              DiTauDRVsBPt2ndBestMatch_->Fill(diTauDR, jet1->et() );
            }//if dr1corr > dr2corr
            if( dr1corr < dr2corr)
	    {
              DiTauDRVsBPtBestMatch_->Fill(diTauDR, jet1->et() );
              DiTauDRVsBPt2ndBestMatch_->Fill(diTauDR, jet2->et() );
	    }//if dr1corr < dr2corr
            //This counts the number of events with at least 1 matched bRef with a single jet above the given values
            BPtMatchCut_->Fill(0);
            if(jet1->et() > 100 || jet2->et() > 100 )
              BPtMatchCut_->Fill(4);
            if(jet1->et() > 80 || jet2->et() > 80)
              BPtMatchCut_->Fill(3);
            if(jet1->et() > 60 || jet2->et() > 60)
              BPtMatchCut_->Fill(2);
            if(jet1->et() > 40 || jet2->et() > 40)
              BPtMatchCut_->Fill(1);
          }//if dr1corr < 1 || dr2corr < 1
	}//if br+ br2 > .05

        //This recursively searches the bRef for muons and plots their pt
        VariousFunctions::findAndPlotBMuons(bRef, 1, BMuPt_, false);
        VariousFunctions::findAndPlotBMuons(bbarRef, 1, BMuPt_, false);

        //This counts the events with a single jet above the given values
        BPtCut_->Fill(0);
        if(jet1->et() > 100 || jet2->et() > 100 )
          BPtCut_->Fill(4);
        if(jet1->et() > 80 || jet2->et() > 80)
          BPtCut_->Fill(3);
        if(jet1->et() > 60 || jet2->et() > 60)
          BPtCut_->Fill(2);
        if(jet1->et() > 40 || jet2->et() > 40)
          BPtCut_->Fill(1);

        //This plots the a, tau, and a-b comparison quantities
        tau1P4 = VariousFunctions::sumTauP4(tau1Ref, tau1DecayMode, true);
        TauPt_->Fill(tau1P4.Pt() );
        tau2P4 = VariousFunctions::sumTauP4(tau2Ref, tau2DecayMode, true);
        TauPt_->Fill(tau2P4.Pt() );
        double aB1DR = VariousFunctions::getABDR(jet1->eta(), jet1->phi(), tau1Ref, tau2Ref, true);
        double aB2DR = VariousFunctions::getABDR(jet2->eta(), jet2->phi(), tau1Ref, tau2Ref, true);
        aP4 = tau1P4 + tau2P4;
        APt_->Fill(aP4.Pt() );
        DiTauDR_->Fill(diTauDR);
        ABDR_->Fill(aB1DR);
        ABDR_->Fill(aB2DR);
        DiTauDRVsAPt_->Fill(diTauDR, aP4.Pt());
        DiTauDRVsAEta_->Fill(diTauDR, aP4.Eta() );
        if(jet1->et() > jet2->et() )
        {
          DiTauDRVsBPtLow_->Fill(diTauDR, jet2->et() );
          DiTauDRVsBPtHigh_->Fill(diTauDR, jet1->et() );
	  BPtHigh_->Fill(jet1->et() );
	  BPtLow_->Fill(jet2->et() );
        }//if jet1->et() > jet2->et()
        else
        {
          DiTauDRVsBPtLow_->Fill(diTauDR, jet1->et() );
          DiTauDRVsBPtHigh_->Fill(diTauDR, jet2->et() );
          BPtHigh_->Fill(jet2->et() );
          BPtLow_->Fill(jet1->et() );
        }//else
        ABDRVsAPt_->Fill(aB1DR, aP4.Pt());
        ABDRVsAPt_->Fill(aB2DR, aP4.Pt());
        ABDRVsDiTauDR_->Fill(aB1DR, diTauDR);
        ABDRVsDiTauDR_->Fill(aB2DR, diTauDR);
	if(tau1DecayMode == 7)
          TauMuPt_->Fill(tau1P4.Pt() );
	if(tau2DecayMode == 7)
          TauMuPt_->Fill(tau2P4.Pt() );
        BPt_->Fill(jet1->et() );
        BPt_->Fill(jet2->et() );
        DiBPt_->Fill(jet1->et() + jet2->et() );
        BPt_->Fill(jet1->et() );
        BPt_->Fill(jet2->et() );
        DiBPt_->Fill(jet1->et() + jet2->et() );

      }//Tau_mu+tau_had decay     

    }//if ID = 36 && 2 daughters and daughter pdg id  == 15
  }//for iGenDaughters

}//End BBAAnalyzer::analyze


// ------------ method called once each job just before starting event loop  ------------
void BBAAnalyzer::beginJob()
{
  std::cout << "Begin Job" << std::endl;

  //Open output file
  out_ = new TFile(outFileName_.c_str(), "RECREATE");
  jetOutput_.open (jetOutputFileName_.c_str());

  //Book histograms
  BPtCut_ = new TH1F("BPtCut", "", 5, -.5, 4.5);
  BPtMatchCut_ = new TH1F("BPtMatchCut", "", 5, -.5, 4.5);
  TauPt_ = new TH1F("TauPt", "", 50, 0, 50);

  APt_ = new TH1F("APt", "", 100, 0, 100);
  DiTauDR_ = new TH1F("DiTauDR", "", 48, 0, 12);
  BPtMatch_ = new TH1F("BPtMatch", "", 80, 0, 80);
  ABDR_ = new TH1F("ABDR", "", 100, 0, 15);
  TauMuPt_ = new TH1F("TauMuPt", "", 50, 0, 50);
  BPt_ = new TH1F("BPt", "", 80, 0, 80);
  BPtHigh_ = new TH1F("BPtHigh", "", 80, 0, 80);
  BPtLow_ = new TH1F("BPtLow", "", 80, 0, 80);
  DiBPt_ = new TH1F("DiBPt", "", 200, 0, 200);
  DRbPartbRatio_ = new TH1F("DRbPartbRatio", "", 50, 0, 10);
  PtDiffbPartbRatio_ = new TH1F("PtDiffbPartbRatio", "", 50, 0, 40);
  BMuPt_ = new TH1F("BMuPt", "", 80, 0, 40);
  AMass_ = new TH1F("AMass", "", 80, 0, 80);

  DiTauDRVsAPt_ = new TH2F("DiTauDRVsAPt", "", 50, 0.0, 10.0, 50, 0.0, 80.0);
  DiTauDRVsAEta_ = new TH2F("DiTauDRVsAEta", "", 50, 0.0, 10.0, 50, -8.0, 8.0);
  DiTauDRVsBPtLow_ = new TH2F("DiTauDRVsBPtLow", "", 50, 0.0, 10.0, 100, 0, 100.0);
  DiTauDRVsBPtHigh_ = new TH2F("DiTauDRVsBPtHigh", "", 50, 0.0, 10.0, 100, 0, 100.0);
  DiTauDRVsBPtBestMatch_ = new TH2F("DiTauDRVsBPtBestMatch", "", 50, 0.0, 10.0, 100, 0, 100.0);
  DiTauDRVsBPt2ndBestMatch_ = new TH2F("DiTauDRVsBPt2ndBestMatch", "", 50, 0.0, 10.0, 100, 0, 100.0);
  ABDRVsAPt_ = new TH2F("ABDRVsAPt", "", 50, 0, 15.0, 50, 0.0, 60.0);
  ABDRVsDiTauDR_ = new TH2F("ABDRVsDiTauDR", "", 50, 0, 15.0, 50, 0.0, 6.0);
 
  SumBRatioVsBPartBRatiodR_ = new TH2F("SumBRatioVsBPartBRatiodR", "", 50, 0, 2.0, 50, 0.0, 12.0);
  BRatiosWithLargeDR_ = new TH1F("BRatiosWithLargeDR", "", 50, 0, 1.0);

  NEvents_ = new TH1F("NEvents", "", 50, 0, 1.0);
 
  BPtCut_->GetXaxis()->SetBinLabel(1, "Total");
  BPtCut_->GetXaxis()->SetBinLabel(2, ">40");
  BPtCut_->GetXaxis()->SetBinLabel(3, ">60");
  BPtCut_->GetXaxis()->SetBinLabel(4, ">80");
  BPtCut_->GetXaxis()->SetBinLabel(5, ">100");

  BPtMatchCut_->GetXaxis()->SetBinLabel(1, "Total");
  BPtMatchCut_->GetXaxis()->SetBinLabel(2, ">40");
  BPtMatchCut_->GetXaxis()->SetBinLabel(3, ">60");
  BPtMatchCut_->GetXaxis()->SetBinLabel(4, ">80");
  BPtMatchCut_->GetXaxis()->SetBinLabel(5, ">100");
}

// ------------ method called once each job just after ending the event loop  ------------
void BBAAnalyzer::endJob()
{


  jetOutput_.close();

  for(int i=0; i<6; i++)
    cout << "BPtCut:  Bin #" << i << " has a count of " << BPtCut_->GetBinContent(i) << std::endl;
  for(int i=0; i<6; i++) 
    cout << "BPtMatchCut:  BIN #" << i << " has a count of " << BPtMatchCut_->GetBinContent(i) << std::endl;

  //Make the Canvases
  TCanvas BPtCutCanvas("BPtCut", "", 600, 600);
  TCanvas BPtMatchCutCanvas("BPtMatchCut", "", 600, 600);
  TCanvas TauPtCanvas("TauPt","",600,600);

  TCanvas APtCanvas("APt","",600,600);
  TCanvas DiTauDRCanvas("DiTauDR","",600,600);
  TCanvas BPtMatchCanvas("BPtMatch","",600,600);
  TCanvas ABDRCanvas("ABDR","",600,600);
  TCanvas TauMuPtCanvas("TauMuPt","",600,600);
  TCanvas BPtCanvas("BPt","",600,600);
  TCanvas BPtHighCanvas("BPtHigh","",600,600);
  TCanvas BPtLowCanvas("BPtLow","",600,600);
  TCanvas DiBPtCanvas("DiBPt","",600,600);
  TCanvas DRbPartbRatioCanvas("DRbPartbRatio","",600,600);
  TCanvas PtDiffbPartbRatioCanvas("PtDiffbPartbRatio","",600,600);
  TCanvas BMuPtCanvas("BMuPt","",600,600);
  TCanvas AMassCanvas("AMass","",600,600);

  TCanvas DiTauDRVsAPtCanvas("DiTauDRVsAPt","" ,600,600);
  TCanvas DiTauDRVsAEtaCanvas("DiTauDRVsAEta","" ,600,600);
  TCanvas DiTauDRVsBPtLowCanvas("DiTauDRVsBPtLow","" ,600,600);
  TCanvas DiTauDRVsBPtHighCanvas("DiTauDRVsBPtHigh","" ,600,600);
  TCanvas DiTauDRVsBPtBestMatchCanvas("DiTauDRVsBPtBestMatch","" ,600,600);
  TCanvas DiTauDRVsBPt2ndBestMatchCanvas("DiTauDRVsBPt2ndBestMatch","" ,600,600);
  TCanvas ABDRVsAPtCanvas("ABDRVsAPt","",600,600);
  TCanvas ABDRVsDiTauDRCanvas("ABDRVsDiTauDR","",600,600);

  TCanvas SumBRatioVsBPartBRatiodRCanvas("SumBRatioVsBPartBRatiodR","",600,600);
  TCanvas BRatiosWithLargeDRCanvas("BRatiosWithLargeDR","",600,600);

  TCanvas NEventsCanvas("NEvents","",600,600);
std::cout << "<----------------Declared Canvases-------------->" << std::endl;

  //Format the 1D plots and Draw (canvas, hist, grid, log y, log z, color, size, style, xAxisTitle, xTitleSize, xLabelSize, xTitleOffSet, yAxisTitle, yTitleSize, yLabelSize, yTitleOffset)
  VariousFunctions::formatAndDrawCanvasAndHist1D(BPtCutCanvas, BPtCut_, 1, 0, 0, kBlack, 0.7, 20, "", .04, .04, 1, "", .04, .04, 1, false); 
  VariousFunctions::formatAndDrawCanvasAndHist1D(BPtMatchCutCanvas, BPtMatchCut_, 1, 0, 0, kBlack, 0.7, 20, "", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(TauPtCanvas, TauPt_, 1, 0, 0, kBlack, 0.7, 20, "Pt(#tau)", .04, .04, 1, "", .04, .04, 1, false);

  VariousFunctions::formatAndDrawCanvasAndHist1D(APtCanvas, APt_, 1, 0, 0, kBlack, 0.7, 20, "Pt(A)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(DiTauDRCanvas, DiTauDR_, 1, 0, 0, kBlack, 0.7, 20, "dR(#tau #tau)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BPtMatchCanvas, BPtMatch_, 1, 0, 0, kBlack, 0.7, 20, "Pt(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(ABDRCanvas, ABDR_, 1, 0, 0, kBlack, 0.7, 20, "dR(ab)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(TauMuPtCanvas, TauMuPt_, 1, 0, 0, kBlack, 0.7, 20, "Pt(mu)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BPtCanvas, BPt_, 1, 0, 0, kBlack, 0.7, 20, "Pt(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BPtHighCanvas, BPtHigh_, 1, 0, 0, kBlack, 0.7, 20, "Pt(b High)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BPtLowCanvas, BPtLow_, 1, 0, 0, kBlack, 0.7, 20, "Pt(b Low)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(DiBPtCanvas, DiBPt_, 1, 0, 0, kBlack, 0.7, 20, "Pt(bb)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(DRbPartbRatioCanvas, DRbPartbRatio_, 1, 0, 0, kBlack, 0.7, 20, "dR(bjet bPart)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(PtDiffbPartbRatioCanvas, PtDiffbPartbRatio_, 1, 0, 0, kBlack, 0.7, 20, "#Delta Pt(bjet bPart)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BMuPtCanvas, BMuPt_, 1, 0, 0, kBlack, 0.7, 20, "Pt(#mu_{b})", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(AMassCanvas, AMass_, 1, 0, 0, kBlack, 0.7, 20, "M(a1)", .04, .04, 1, "", .04, .04, 1, false);

  //format the 2d plots and draw (canvas, hist, grid, log y, log z, color, size, style, xaxistitle, xtitlesize, xlabelsize, xtitleoffset, yaxistitle, ytitlesize, ylabelsize, ytitleoffset,
  			      // zAxisTitle, zTitleSize, zLabelSize, zTitleOffset)
  VariousFunctions::formatAndDrawCanvasAndHist2D(DiTauDRVsAPtCanvas, DiTauDRVsAPt_, 0, 0, 0, kBlack, 7, 20, "dR(#tau#tau)", .04, .04, 1.1, "Pt(A)", .04, .04, 1.6, "", .04, .04, 1.0);
  VariousFunctions::formatAndDrawCanvasAndHist2D(DiTauDRVsAEtaCanvas, DiTauDRVsAEta_, 0, 0, 0, kBlack, 7, 20, "dR(#tau#tau)", .04, .04, 1.1, "#eta(A)", .04, .04, 1.6, "", .04, .04, 1.0);
  VariousFunctions::formatAndDrawCanvasAndHist2D(DiTauDRVsBPtLowCanvas, DiTauDRVsBPtLow_, 0, 0, 0, kBlack, 7, 20, "dR(#tau#tau)", .04, .04, 1.1, "Pt(bLow)", .04, .04, 1.6, "", .04, .04, 1.0);
  VariousFunctions::formatAndDrawCanvasAndHist2D(DiTauDRVsBPtHighCanvas, DiTauDRVsBPtHigh_, 0, 0, 0, kBlack, 7, 20, "dR(#tau#tau)", .04, .04, 1.1, "Pt(bHigh)", .04, .04, 1.6, "", .04, .04, 1.0);
  VariousFunctions::formatAndDrawCanvasAndHist2D(DiTauDRVsBPtBestMatchCanvas, DiTauDRVsBPtBestMatch_, 0, 0, 0, kBlack, 7, 20, "dR(#tau#tau)", .04, .04, 1.1, "Pt(bHigh)", .04, .04, 1.6, "", .04, .04, 1.0);
  VariousFunctions::formatAndDrawCanvasAndHist2D(DiTauDRVsBPt2ndBestMatchCanvas, DiTauDRVsBPt2ndBestMatch_, 0, 0, 0, kBlack, 7, 20, "dR(#tau#tau)", .04, .04, 1.1, "Pt(bHigh)", .04, .04, 1.6, "", .04, .04, 1.0);
  VariousFunctions::formatAndDrawCanvasAndHist2D(ABDRVsAPtCanvas, ABDRVsAPt_, 0, 0, 0, kBlack, 7, 20, "dR(ab)", .04, .04, 1.1, "Pt(A)", .04, .04, 1.6, "", .04, .04, 1.0);
  VariousFunctions::formatAndDrawCanvasAndHist2D(ABDRVsDiTauDRCanvas, ABDRVsDiTauDR_, 0, 0, 0, kBlack, 7, 20, "dR(ab)", .04, .04, 1.1, "dR(#tau#tau)", .04, .04, 1.6, "", .04, .04, 1.0);

  VariousFunctions::formatAndDrawCanvasAndHist2D(SumBRatioVsBPartBRatiodRCanvas, SumBRatioVsBPartBRatiodR_, 0, 0, 0, kBlack, 7, 20, "bRatio Sum", .04, .04, 1.1, "dR(bPart bRatio)", .04, .04, 1.6, "", .04, .04, 1.0);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BRatiosWithLargeDRCanvas, BRatiosWithLargeDR_, 0, 0, 0, kBlack, 7, 20, "bRatio", .04, .04, 1.1,  "", .04, .04, 1.0, false);

  VariousFunctions::formatAndDrawCanvasAndHist1D(NEventsCanvas, NEvents_, 0, 0, 0, kBlack, 7, 20, "NEvents", .04, .04, 1.1,  "", .04, .04, 1.0, false);

std::cout << "<----------------Formatted Canvases and Histos-------------->" << std::endl;

  //Write output file
  out_->cd();
  BPtCutCanvas.Write();
  BPtMatchCutCanvas.Write();
  TauPtCanvas.Write();

  APtCanvas.Write();
  DiTauDRCanvas.Write();
  BPtMatchCanvas.Write();
  ABDRCanvas.Write();
  TauMuPtCanvas.Write();
  BPtCanvas.Write();
  BPtHighCanvas.Write();
  BPtLowCanvas.Write();
  DiBPtCanvas.Write();
  DRbPartbRatioCanvas.Write();
  PtDiffbPartbRatioCanvas.Write();
  BMuPtCanvas.Write();
  AMassCanvas.Write();

  DiTauDRVsAPtCanvas.Write();
  DiTauDRVsAEtaCanvas.Write();
  DiTauDRVsBPtLowCanvas.Write();
  DiTauDRVsBPtHighCanvas.Write();
  DiTauDRVsBPtBestMatchCanvas.Write();
  DiTauDRVsBPt2ndBestMatchCanvas.Write();
  ABDRVsAPtCanvas.Write();
  ABDRVsDiTauDRCanvas.Write();

  SumBRatioVsBPartBRatiodRCanvas.Write();
  BRatiosWithLargeDRCanvas.Write();

  NEventsCanvas.Write();

  out_->Write();
  out_->Close();
std::cout << "DONE" << std::endl;
}//EndJob

// ------------ method called when starting to processes a run  ------------
void BBAAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&) {}

// ------------ method called when ending the processing of a run  ------------
void BBAAnalyzer::endRun(edm::Run const&, edm::EventSetup const&) {}

// ------------ method called when starting to processes a luminosity block  ------------
void BBAAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {}

// ------------ method called when ending the processing of a luminosity block  ------------
void BBAAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) {}

//Delete Memory
void BBAAnalyzer::reset(const bool doDelete)
{
  if ((doDelete) && (out_ != NULL)) delete out_;
  out_ = NULL;
  if ((doDelete) && (BPtCut_ != NULL)) delete BPtCut_;
  BPtCut_ = NULL;
  if ((doDelete) && (BPtMatchCut_ != NULL)) delete BPtMatchCut_;
  BPtMatchCut_ = NULL;
  if ((doDelete) && (TauPt_ != NULL)) delete TauPt_;
  TauPt_ = NULL;

  if ((doDelete) && (APt_ != NULL)) delete APt_;
  APt_ = NULL;
  if ((doDelete) && (DiTauDR_ != NULL)) delete DiTauDR_;
  DiTauDR_ = NULL;
  if ((doDelete) && (BPtMatch_ != NULL)) delete BPtMatch_;
  BPtMatch_ = NULL;
  if ((doDelete) && (ABDR_ != NULL)) delete ABDR_;
  ABDR_ = NULL;
  if ((doDelete) && (TauMuPt_ != NULL)) delete TauMuPt_;
  TauMuPt_ = NULL;
  if ((doDelete) && (BPt_ != NULL)) delete BPt_;
  BPt_ = NULL;
  if ((doDelete) && (BPtHigh_ != NULL)) delete BPtHigh_;
  BPtHigh_ = NULL;
  if ((doDelete) && (BPtLow_ != NULL)) delete BPtLow_;
  BPtLow_ = NULL;
  if ((doDelete) && (DiBPt_ != NULL)) delete DiBPt_;
  DiBPt_ = NULL;
  if ((doDelete) && (DRbPartbRatio_ != NULL)) delete DRbPartbRatio_;
  DRbPartbRatio_ = NULL;
  if ((doDelete) && (PtDiffbPartbRatio_ != NULL)) delete PtDiffbPartbRatio_;
  PtDiffbPartbRatio_ = NULL;
  if ((doDelete) && (BMuPt_ != NULL)) delete BMuPt_;
  BMuPt_ = NULL;
  if ((doDelete) && (AMass_ != NULL)) delete AMass_;
  AMass_ = NULL;

  if ((doDelete) && (DiTauDRVsAPt_ != NULL)) delete  DiTauDRVsAPt_;
  DiTauDRVsAPt_ = NULL;
  if ((doDelete) && (DiTauDRVsAEta_ != NULL)) delete DiTauDRVsAEta_;
  DiTauDRVsAEta_ = NULL;
  if ((doDelete) && (DiTauDRVsBPtLow_ != NULL)) delete DiTauDRVsBPtLow_;
  DiTauDRVsBPtLow_ = NULL;
  if ((doDelete) && (DiTauDRVsBPtHigh_ != NULL)) delete DiTauDRVsBPtHigh_;
  DiTauDRVsBPtHigh_ = NULL;
  if ((doDelete) && (DiTauDRVsBPtBestMatch_ != NULL)) delete DiTauDRVsBPtBestMatch_;
  DiTauDRVsBPtBestMatch_ = NULL;
  if ((doDelete) && (DiTauDRVsBPt2ndBestMatch_ != NULL)) delete DiTauDRVsBPt2ndBestMatch_;
  DiTauDRVsBPt2ndBestMatch_ = NULL;
  if ((doDelete) && (ABDRVsAPt_ != NULL)) delete ABDRVsAPt_;
  ABDRVsAPt_ = NULL;
  if ((doDelete) && (ABDRVsDiTauDR_ != NULL)) delete ABDRVsDiTauDR_;
  ABDRVsDiTauDR_ = NULL;

  if ((doDelete) && (SumBRatioVsBPartBRatiodR_ != NULL)) delete SumBRatioVsBPartBRatiodR_;
  SumBRatioVsBPartBRatiodR_ = NULL;
  if ((doDelete) && (BRatiosWithLargeDR_ != NULL)) delete BRatiosWithLargeDR_;
  BRatiosWithLargeDR_ = NULL;

  if ((doDelete) && (NEvents_ != NULL)) delete NEvents_;
  NEvents_ = NULL;

}//void BBAAnalyzer

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void BBAAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(BBAAnalyzer);
