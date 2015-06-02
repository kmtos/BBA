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

      //name of output file
      std::string outFileName_;

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
      TH1F* AMPart_;
      TH1F* BPtCut_;
      TH1F* BRatioCut_;
      TH1F* TauPt_;
      TH1F* TauEta_;

      TH1F* BPt7575_;
      TH1F* BPt5050_;
      TH1F* BPt3333_;
      TH1F* BPt2525_;
      TH1F* BPt7550_;
      TH1F* BPt7525_;
      TH1F* BPt5025_;
      TH1F* BPt3325_;

      TH1F* BEta7575_;
      TH1F* BEta5050_;
      TH1F* BEta3333_;
      TH1F* BEta2525_;
      TH1F* BEta7550_;
      TH1F* BEta7525_;
      TH1F* BEta5025_;
      TH1F* BEta3325_;

      TH1F* BPhi7575_;
      TH1F* BPhi5050_;
      TH1F* BPhi3333_;
      TH1F* BPhi2525_;
      TH1F* BPhi7550_;
      TH1F* BPhi7525_;
      TH1F* BPhi5025_;
      TH1F* BPhi3325_;

      TH1F* BdR7575_;
      TH1F* BdR5050_;
      TH1F* BdR3333_;
      TH1F* BdR2525_;
      TH1F* BdR7550_;
      TH1F* BdR7525_;
      TH1F* BdR5025_;
      TH1F* BdR3325_;


      TH1F* APt_;
      TH1F* AEta_;
      TH1F* DiTauDR_; 
      TH1F* BPt_;
      TH1F* BEta_;
      TH1F* BPhi_;
      TH1F* ABDR_;
      TH1F* MuPtOfTauMuTauHad_;
      TH1F* BPtTauMuTauHad_;
      TH1F* DiBPtTauMuTauHad_;
      TH1F* BRatio_;
      TH1F* DRbPartbRatio_;
      TH1F* PtDiffbPartbRatio_;
      TH1F* BMuPt_;

      TH2F* DiTauDRVsAPt_;
      TH2F* DiTauDRVsAEta_;
      TH2F* DiTauDRVsBPtLow_;
      TH2F* DiTauDRVsBPtHigh_;
      TH2F* ABDRVsAPt_;
      TH2F* ABDRVsDiTauDR_;


      TH2F* SumBRatioVsBPartBRatiodR_;
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

  JetBCEnergyRatioCollection::const_iterator initB = theBratioValue->begin();
  Jet *jet1 =  const_cast<Jet*>(&*(initB->first) ), *jet2 =  const_cast<Jet*>(&*(initB->first) );
  for (JetBCEnergyRatioCollection::const_iterator itB = theBratioValue->begin(); itB != theBratioValue->end(); itB++)
  {
    Jet *jetB = const_cast<Jet*>(&*(itB->first) );
    double cR = 0;
std::cout << "\tJet #" << i << " has bRatio= " << itB->second << "\thas pt=" << jetB->et() << "\tphi=" << jetB->phi() << "\teta= " << jetB->eta() << std::endl;
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

   std::cout << "\tLargest bRatio= " << br1 << " is Jet #" << Big1JetN << " and has pt= " << jet1->et() << " and has eta=" << jet1->eta() << " and has phi= " << jet1->phi() << std::endl;
   std::cout << "\tSecond Largest bRatio= " << br2 << " is Jet #" << Big2JetN << " and has pt= " << jet2->et() << " and has eta=" << jet2->eta() << " and has phi= " << jet2->phi() << std::endl;

  //Cycling through all of the particles in each event
  for (reco::GenParticleCollection::const_iterator iGenParticle = pGenParticles->begin(); iGenParticle != pGenParticles->end(); ++iGenParticle)
  {

//
//This Next bit is the Tau Analysis Part
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
      reco::LeafCandidate::LorentzVector aP4 = VariousFunctions::sumTauP4(tau1Ref, tau1DecayMode, true) + VariousFunctions::sumTauP4(tau2Ref, tau2DecayMode, true);
      double diTauDR = VariousFunctions::getDiTauDR(tau1Ref, tau2Ref, true), aBDR = 0, aBbarDR = 0;
//
//This gets the bParticles
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
      }//for

      std::cout << "\tbRef: pdgId= " << bRef->pdgId() << "  pt= " << bRef->pt() << "  eta= " << bRef->eta() << "  phi= " << bRef->phi() << std::endl;
      std::cout << "\tbbar: pdgId= " << bbarRef->pdgId() << "  pt= " << bbarRef->pt() << "  eta= " << bbarRef->eta() << "  phi= " << bbarRef->phi() << std::endl;
      std::cout << "\tbjet1: \t pt= " << jet1->et() << "  eta=" << jet1->eta() << "  phi= " << jet1->phi() << std::endl;
      std::cout << "\tbjet2: \t pt= " << jet2->et() << "  eta=" << jet2->eta() << "  phi= " << jet2->phi() << bcdiff2 << std::endl;

      //this calculates the many different delta phi, eta, r, pt between the 2 jets with highest bRatio and the 2 bParticles
      double b1pt = fabs(jet1->et() - bRef->pt() ), bbar1pt = fabs(jet1->et() - bbarRef->pt() ), b2pt = fabs(jet2->et() - bRef->pt() ), bbar2pt = fabs(jet2->et() - bbarRef->pt() );
      double b1eta = fabs(jet1->eta() - bRef->eta() ), bbar1eta = fabs(jet1->eta() - bbarRef->eta() ), b2eta = fabs(jet2->eta() - bRef->eta() ), bbar2eta = fabs(jet2->eta() - bbarRef->eta() );
      double b1phi = fabs(jet1->phi() - bRef->phi() ), bbar1phi = fabs(jet1->phi() - bbarRef->phi() ), b2phi = fabs(jet2->phi() - bRef->phi() ), bbar2phi = fabs(jet2->phi() - bbarRef->phi() );    
      double b1dr = sqrt( b1eta*b1eta + b1phi*b1phi), bbar1dr = sqrt( bbar1eta*bbar1eta + bbar1phi*bbar1phi ), b2dr = sqrt( b2eta*b2eta + b2phi*b2phi), bbar2dr = sqrt( bbar2eta*bbar2eta + bbar2phi*bbar2phi );
      std::cout << "\t b1pt=" << b1pt << "  bbar1pt=" << bbar1pt << "  b2pt=" << b2pt << "  bbar2pt=" << bbar2pt << std::endl;
      std::cout << "\t b1dr=" << b1dr << "  bbar1dr=" << bbar1dr << "  b2dr=" << b2dr << "  bbar2dr=" << bbar2dr << std::endl;
      double dr1corr = 0, dr2corr = 0, pt1corr = 0, pt2corr = 0;

      if(b1dr > b2dr)  //b2dr smaller
      {
        if(bbar1dr > bbar2dr)  //bbar2dr smaller
	{
	  if(bbar2dr > b2dr)  //b2dr smallest of 4
	  {
	    dr1corr = b2dr;
	    dr2corr = bbar1dr;
	    pt1corr = b2pt;
	    pt2corr = bbar1pt;	    
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
          dr1corr = b2dr;
          dr2corr = bbar1dr;
          pt1corr = b2pt;
          pt2corr = bbar1pt;	  
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
            dr1corr = b2dr;
            dr2corr = bbar1dr;
            pt1corr = b2pt;
            pt2corr = bbar1pt;
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
//This is the end of my calculations and is the start of the plotting
//
      if( (tau2DecayMode == 7 && tau1DecayMode <=4) || (tau1DecayMode == 7 && tau2DecayMode <=4) )
      {
        BRatioCut_->Fill(0);
        if(br1 > .75 && br2 > .75 )
        {
          BRatioCut_->Fill(1);
          BPt7575_->Fill(jet1->et() );
          BEta7575_->Fill(jet1->eta() );
          BPhi7575_->Fill(jet1->phi() );
   	  BdR7575_->Fill(dr1corr);
          BPt7575_->Fill(jet2->et() );
          BEta7575_->Fill(jet2->eta() );
          BPhi7575_->Fill(jet2->phi() );
	  BdR7575_->Fill(dr2corr);
        }
        if(br1 > .5 && br2 > .5 )
        {
          BRatioCut_->Fill(2);
          BPt5050_->Fill(jet1->et() );
          BEta5050_->Fill(jet1->eta() );
          BPhi5050_->Fill(jet1->phi() );
	  BdR5050_->Fill(dr1corr);
          BPt5050_->Fill(jet2->et() );
          BEta5050_->Fill(jet2->eta() );
          BPhi5050_->Fill(jet2->phi() );
	  BdR5050_->Fill(dr2corr);
        }
        if(br1 > .33 && br2 > .33 )
        {
          BRatioCut_->Fill(3);
          BPt3333_->Fill(jet1->et() );
          BEta3333_->Fill(jet1->eta() );
          BPhi3333_->Fill(jet1->phi() );
	  BdR3333_->Fill(dr1corr);
          BPt3333_->Fill(jet2->et() );
          BEta3333_->Fill(jet2->eta() );
          BPhi3333_->Fill(jet2->phi() );
	  BdR3333_->Fill(dr2corr);
        }
        if(br1 > .25 && br2 > .25 )
        {
          BRatioCut_->Fill(4);
          BPt2525_->Fill(jet1->et() );
          BEta2525_->Fill(jet1->eta() );
          BPhi2525_->Fill(jet1->phi() );
	  BdR2525_->Fill(dr1corr);
          BPt2525_->Fill(jet2->et() );
          BEta2525_->Fill(jet2->eta() );
          BPhi2525_->Fill(jet2->phi() );
	  BdR2525_->Fill(dr2corr);
        }
        if( (br1 > .75 && br2 > .5 ) || (br1 > .5 && br2 > .75 ) )
        {
          BRatioCut_->Fill(5);
          BPt7550_->Fill(jet1->et() );
          BEta7550_->Fill(jet1->eta() );
          BPhi7550_->Fill(jet1->phi() );
	  BdR7550_->Fill(dr1corr);
          BPt7550_->Fill(jet2->et() );
          BEta7550_->Fill(jet2->eta() );
          BPhi7550_->Fill(jet2->phi() );
   	  BdR7550_->Fill(dr2corr);
        }
        if( (br1 > .25 && br2 > .75 ) || (br1 > .75 && br2 > .25 ) )
        {
          BRatioCut_->Fill(6);
          BPt7525_->Fill(jet1->et() );
          BEta7525_->Fill(jet1->eta() );
          BPhi7525_->Fill(jet1->phi() );
	  BdR7525_->Fill(dr1corr);
          BPt7525_->Fill(jet2->et() );
          BEta7525_->Fill(jet2->eta() );
          BPhi7525_->Fill(jet2->phi() );
	  BdR7525_->Fill(dr2corr);
        }
        if( (br1 > .25 && br2 > .5 ) || (br1 > .5 && br2 > .25 ) )
        {
          BRatioCut_->Fill(7);
          BPt5025_->Fill(jet1->et() );
          BEta5025_->Fill(jet1->eta() );
          BPhi5025_->Fill(jet1->phi() );
	  BdR5025_->Fill(dr1corr);
          BPt5025_->Fill(jet2->et() );
          BEta5025_->Fill(jet2->eta() );
          BPhi5025_->Fill(jet2->phi() );
	  BdR5025_->Fill(dr2corr);
        }
        if( (br1 > .25 && br2 > .33 ) || (br1 > .33 && br2 > .25 ) )
        {
          BRatioCut_->Fill(8);
          BPt3325_->Fill(jet1->et() );
          BEta3325_->Fill(jet1->eta() );
          BPhi3325_->Fill(jet1->phi() );
	  BdR3325_->Fill(dr1corr);
          BPt3325_->Fill(jet2->et() );
          BEta3325_->Fill(jet2->eta() );
          BPhi3325_->Fill(jet2->phi() );
	  BdR3325_->Fill(dr2corr);
        }
        BPt_->Fill(jet1->et() );
        BPt_->Fill(jet2->et() );
        BEta_->Fill(jet1->eta() );
        BEta_->Fill(jet2->eta() );
        BPhi_->Fill(jet1->phi() );
        BPhi_->Fill(jet2->phi() );
        BRatio_->Fill(br1);
        BRatio_->Fill(br2);
        if(br1 + br2 > 1.15)
	{
          SumBRatioVsBPartBRatiodR_->Fill(br1 + br2, dr1corr);
          SumBRatioVsBPartBRatiodR_->Fill(br1 + br2, dr2corr);
          DRbPartbRatio_->Fill(dr1corr);
          DRbPartbRatio_->Fill(dr2corr);
          PtDiffbPartbRatio_->Fill(pt1corr);
          PtDiffbPartbRatio_->Fill(pt2corr);
	}//if br+ br2 > .05

          //This looks for a "b" in their refs to get final decay bit. It also looks for the b muon along the way. 
        while(VariousFunctions::findIfInDaughters(bRef, 5, true) || VariousFunctions::findIfInDaughters(bbarRef, 5, true))
        {
          for(unsigned int i=0; i<bRef->numberOfDaughters(); i++)
            std::cout << "\t\tbRef child #" << i << " has pdgid= " << bRef->daughter(i)->pdgId() << std::endl;
          for(unsigned int i=0; i<bbarRef->numberOfDaughters(); i++)
            std::cout << "\t\tbbarRef child #" << i << " has pdgid= " << bbarRef->daughter(i)->pdgId() << std::endl;

          //Looks for muons along the way
          if(VariousFunctions::findIfInDaughters(bRef, 13, true))
          {
            reco::GenParticleRef bMuRef = VariousFunctions::findDaughterInDaughters(bRef, 13, true);
            BMuPt_->Fill(bMuRef->pt() );
          }//findIfInDaughters(bRef, 13, true)
          if(VariousFunctions::findIfInDaughters(bbarRef, 13, true))
          {
            reco::GenParticleRef bbarMuRef = VariousFunctions::findDaughterInDaughters(bbarRef, 13, true);
            BMuPt_->Fill(bbarMuRef->pt() );
          }//findIfInDaughters(bRef, 13, true)

          //assigns "b" daughter to bRef
          if(VariousFunctions::findIfInDaughters(bRef, 5, true))
            bRef = VariousFunctions::findDaughterInDaughters(bRef, 5, true);
          if(VariousFunctions::findIfInDaughters(bbarRef, 5, true))
            bbarRef = VariousFunctions::findDaughterInDaughters(bbarRef, 5, true);
        }//while

       for(unsigned int i=0; i<bRef->numberOfDaughters(); i++)
         std::cout << "\t\t\nbRef child #" << i << "has pdgid= " << bRef->daughter(i)->pdgId() << std::endl;
       for(unsigned int i=0; i<bbarRef->numberOfDaughters(); i++)
         std::cout << "\t\tbbarRef child #" << i << "has pdgid= " << bbarRef->daughter(i)->pdgId() << std::endl;

        //Looks for muon in final b decay
        if(VariousFunctions::findIfInDaughters(bRef, 13, true))
        {
          reco::GenParticleRef bMuRef = VariousFunctions::findDaughterInDaughters(bRef, 13, true);
          BMuPt_->Fill(bMuRef->pt() );
        }//findIfInDaughters(bRef, 13, true)
        if(VariousFunctions::findIfInDaughters(bbarRef, 13, true))
        {
          reco::GenParticleRef bbarMuRef = VariousFunctions::findDaughterInDaughters(bbarRef, 13, true);
          BMuPt_->Fill(bbarMuRef->pt() );
        }//if

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
        TauEta_->Fill(tau1P4.Eta() );
        tau2P4 = VariousFunctions::sumTauP4(tau2Ref, tau2DecayMode, true);
        TauPt_->Fill(tau2P4.Pt() );
        TauEta_->Fill(tau2P4.Eta() );
        aBDR = VariousFunctions::getABDR(jet1->eta(), jet1->phi(), tau1Ref, tau2Ref, true);
        aBbarDR = VariousFunctions::getABDR(jet2->eta(), jet2->phi(), tau1Ref, tau2Ref, true);
        aP4 = tau1P4 +tau2P4;
        APt_->Fill(aP4.Pt() );
        AEta_->Fill(aP4.Eta() );
        DiTauDR_->Fill(diTauDR);
        ABDR_->Fill(aBDR);
        ABDR_->Fill(aBbarDR);
        DiTauDRVsAPt_->Fill(diTauDR, aP4.Pt());
        DiTauDRVsAEta_->Fill(diTauDR, aP4.Eta() );
        if(jet1->et() > jet2->et() )
        {
          DiTauDRVsBPtLow_->Fill(diTauDR, jet1->et() );
          DiTauDRVsBPtHigh_->Fill(diTauDR, jet2->et() );
        }//if bP4.Pt() > bbarP4.Pt()
        else
        {
          DiTauDRVsBPtLow_->Fill(diTauDR, jet2->et() );
          DiTauDRVsBPtHigh_->Fill(diTauDR, jet2->et() );
        }//else
        ABDRVsAPt_->Fill(aBDR, aP4.Pt());
        ABDRVsAPt_->Fill(aBbarDR, aP4.Pt());
        ABDRVsDiTauDR_->Fill(aBDR, diTauDR);
        AMPart_->Fill(iGenParticle->mass() );
        if(tau2DecayMode == 7 && tau1DecayMode <= 4)
        { 
          MuPtOfTauMuTauHad_->Fill(tau2P4.Pt() );
          BPtTauMuTauHad_->Fill(jet1->et() );
          BPtTauMuTauHad_->Fill(jet2->et() );
          DiBPtTauMuTauHad_->Fill(jet1->et() + jet2->et() );
        }//if
        if(tau2DecayMode <= 4 && tau1DecayMode == 7)
        {
          MuPtOfTauMuTauHad_->Fill(tau1P4.Pt() );
          BPtTauMuTauHad_->Fill(jet1->et() );
          BPtTauMuTauHad_->Fill(jet2->et() );
          DiBPtTauMuTauHad_->Fill(jet1->et() + jet2->et() );
        }//if


      }//Tau_mu+tau_had decay     

    }//if ID = 36 && 2 daughters and daughter pdg id  == 15
  }//for iGenDaughters

}//End BBAAnalyzer::analyze


// ------------ method called once each job just before starting event loop  ------------
void BBAAnalyzer::beginJob()
{
  //Open output file
  out_ = new TFile(outFileName_.c_str(), "RECREATE");

  //Book histograms
  AMPart_ = new TH1F("AMPart", "", 101, -.5, 100.5);
  BPtCut_ = new TH1F("BPtCut", "", 5, -.5, 4.5);
  BRatioCut_ = new TH1F("BRatioCut", "", 9, -.5, 8.5);
  TauPt_ = new TH1F("TauPt", "", 50, 0, 50);
  TauEta_ = new TH1F("TauEta", "", 50, -10, 10);

  BPt7575_ = new TH1F("BPt7575", "", 50 , 0, 40);
  BPt5050_ = new TH1F("BPt5050", "", 50 , 0, 40);
  BPt3333_ = new TH1F("BPt3333", "", 50 , 0, 40);
  BPt2525_ = new TH1F("BPt2525", "", 50 , 0, 40);
  BPt7550_ = new TH1F("BPt7550", "", 50 , 0, 40);
  BPt7525_ = new TH1F("BPt7525", "", 50 , 0, 40);
  BPt5025_ = new TH1F("BPt5025", "", 50 , 0, 40);
  BPt3325_ = new TH1F("BPt3325", "", 50 , 0, 40);

  BEta7575_ = new TH1F("BEta7575", "", 50 , -8, 8);
  BEta5050_ = new TH1F("BEta5050", "", 50 , -8, 8);
  BEta3333_ = new TH1F("BEta3333", "", 50 , -8, 8);
  BEta2525_ = new TH1F("BEta2525", "", 50 , -8, 8);
  BEta7550_ = new TH1F("BEta7550", "", 50 , -8, 8);
  BEta7525_ = new TH1F("BEta7525", "", 50 , -8, 8);
  BEta5025_ = new TH1F("BEta5025", "", 50 , -8, 8);
  BEta3325_ = new TH1F("BEta3325", "", 50 , -8, 8);

  BPhi7575_ = new TH1F("BPhi7575", "", 50 , -3.5, 3.5);
  BPhi5050_ = new TH1F("BPhi5050", "", 50 , -3.5, 3.5);
  BPhi3333_ = new TH1F("BPhi3333", "", 50 , -3.5, 3.5);
  BPhi2525_ = new TH1F("BPhi2525", "", 50 , -3.5, 3.5);
  BPhi7550_ = new TH1F("BPhi7550", "", 50 , -3.5, 3.5);
  BPhi7525_ = new TH1F("BPhi7525", "", 50 , -3.5, 3.5);
  BPhi5025_ = new TH1F("BPhi5025", "", 50 , -3.5, 3.5);
  BPhi3325_ = new TH1F("BPhi3325", "", 50 , -3.5, 3.5);

  BdR7575_ = new TH1F("BdR7575", "", 50 , 0, 15);
  BdR5050_ = new TH1F("BdR5050", "", 50 , 0, 15);
  BdR3333_ = new TH1F("BdR3333", "", 50 , 0, 15);
  BdR2525_ = new TH1F("BdR2525", "", 50 , 0, 15);
  BdR7550_ = new TH1F("BdR7550", "", 50 , 0, 15);
  BdR7525_ = new TH1F("BdR7525", "", 50 , 0, 15);
  BdR5025_ = new TH1F("BdR5025", "", 50 , 0, 15);
  BdR3325_ = new TH1F("BdR3325", "", 50 , 0, 15);


  APt_ = new TH1F("APt", "", 100, 0, 100);
  AEta_ = new TH1F("AEta", "", 50, -6, 6);
  DiTauDR_ = new TH1F("DiTauDR", "", 50, 0, 20);
  BPt_ = new TH1F("BPt", "", 50, 0, 40);
  BEta_ = new TH1F("BEta", "", 50, -7, 7);
  BPhi_ = new TH1F("BPhi", "", 50, -3.2, 3.2);
  ABDR_ = new TH1F("ABDR", "", 100, -1, 20);
  MuPtOfTauMuTauHad_ = new TH1F("MuPtOfTauMuTauHad", "", 50, 0, 50);
  BPtTauMuTauHad_ = new TH1F("BPtTauMuTauHad", "", 50, 0, 50);
  DiBPtTauMuTauHad_ = new TH1F("DiBPtTauMuTauHad", "", 50, 0, 100);
  BRatio_ = new TH1F("BRatio", "", 51, 0, 1);
  DRbPartbRatio_ = new TH1F("DRbPartbRatio", "", 51, 0, 10);
  PtDiffbPartbRatio_ = new TH1F("PtDiffbPartbRatio", "", 51, 0, 40);
  BMuPt_ = new TH1F("BMuPt", "", 51, 0, 40);

  DiTauDRVsAPt_ = new TH2F("DiTauDRVsAPt", "", 50, 0.0, 10.0, 50, 0.0, 80.0);
  DiTauDRVsAEta_ = new TH2F("DiTauDRVsAEta", "", 50, 0.0, 10.0, 50, -8.0, 8.0);
  DiTauDRVsBPtLow_ = new TH2F("DiTauDRVsBPtLow", "", 50, 0.0, 10.0, 100, 0, 100.0);
  DiTauDRVsBPtHigh_ = new TH2F("DiTauDRVsBPtHigh", "", 50, 0.0, 10.0, 100, 0, 100.0);
  ABDRVsAPt_ = new TH2F("ABDRVsAPt", "", 50, -1.0, 15.0, 50, 0.0, 30.0);
  ABDRVsDiTauDR_ = new TH2F("ABDRVsDiTauDR", "", 50, -1.0, 15.0, 50, 0.0, 6.0);
 
  SumBRatioVsBPartBRatiodR_ = new TH2F("SumBRatioVsBPartBRatiodR", "", 50, 0, 2.0, 50, 0.0, 12.0);
 
  BPtCut_->GetXaxis()->SetBinLabel(1, "Total");
  BPtCut_->GetXaxis()->SetBinLabel(2, ">40");
  BPtCut_->GetXaxis()->SetBinLabel(3, ">60");
  BPtCut_->GetXaxis()->SetBinLabel(4, ">80");
  BPtCut_->GetXaxis()->SetBinLabel(5, ">100");

  BRatioCut_->GetXaxis()->SetBinLabel(1, "Total");
  BRatioCut_->GetXaxis()->SetBinLabel(2, ".75 .75");
  BRatioCut_->GetXaxis()->SetBinLabel(3, ".5 .5");
  BRatioCut_->GetXaxis()->SetBinLabel(4, ".33 .33");
  BRatioCut_->GetXaxis()->SetBinLabel(5, ".25 .25");
  BRatioCut_->GetXaxis()->SetBinLabel(6, ".75 .5");
  BRatioCut_->GetXaxis()->SetBinLabel(7, ".75 .25");
  BRatioCut_->GetXaxis()->SetBinLabel(8, ".5 .25");
  BRatioCut_->GetXaxis()->SetBinLabel(9, ".33 .25");
}

// ------------ method called once each job just after ending the event loop  ------------
void BBAAnalyzer::endJob()
{

for(int i=0; i<10; i++)
  std::cout << "Bin #" << i << " has " << BRatioCut_->GetBinContent(i) << " counts." << std::endl;

  //Make the Canvases
  TCanvas AMPartCanvas("AMPart", "", 600, 600);
  TCanvas BPtCutCanvas("BPtCut", "", 600, 600);
  TCanvas BRatioCutCanvas("BRatioCut", "", 600, 600);
  TCanvas TauPtCanvas("TauPt","",600,600);
  TCanvas TauEtaCanvas("TauEta","",600,600);

  TCanvas BPt7575Canvas("BPt7575","",600,600);
  TCanvas BPt5050Canvas("BPt5050","",600,600);
  TCanvas BPt3333Canvas("BPt3333","",600,600);
  TCanvas BPt2525Canvas("BPt2525","",600,600);
  TCanvas BPt7550Canvas("BPt7550","",600,600);
  TCanvas BPt7525Canvas("BPt7525","",600,600);
  TCanvas BPt5025Canvas("BPt5025","",600,600);
  TCanvas BPt3325Canvas("BPt3325","",600,600);

  TCanvas BEta7575Canvas("BEta7575","",600,600);
  TCanvas BEta5050Canvas("BEta5050","",600,600);
  TCanvas BEta3333Canvas("BEta3333","",600,600);
  TCanvas BEta2525Canvas("BEta2525","",600,600);
  TCanvas BEta7550Canvas("BEta7550","",600,600);
  TCanvas BEta7525Canvas("BEta7525","",600,600);
  TCanvas BEta5025Canvas("BEta5025","",600,600);
  TCanvas BEta3325Canvas("BEta3325","",600,600);

  TCanvas BPhi7575Canvas("BPhi7575","",600,600);
  TCanvas BPhi5050Canvas("BPhi5050","",600,600);
  TCanvas BPhi3333Canvas("BPhi3333","",600,600);
  TCanvas BPhi2525Canvas("BPhi2525","",600,600);
  TCanvas BPhi7550Canvas("BPhi7550","",600,600);
  TCanvas BPhi7525Canvas("BPhi7525","",600,600);
  TCanvas BPhi5025Canvas("BPhi5025","",600,600);
  TCanvas BPhi3325Canvas("BPhi3325","",600,600);

  TCanvas BdR7575Canvas("BdR7575","",600,600);
  TCanvas BdR5050Canvas("BdR5050","",600,600);
  TCanvas BdR3333Canvas("BdR3333","",600,600);
  TCanvas BdR2525Canvas("BdR2525","",600,600);
  TCanvas BdR7550Canvas("BdR7550","",600,600);
  TCanvas BdR7525Canvas("BdR7525","",600,600);
  TCanvas BdR5025Canvas("BdR5025","",600,600);
  TCanvas BdR3325Canvas("BdR3325","",600,600);


  TCanvas APtCanvas("APt","",600,600);
  TCanvas AEtaCanvas("AEta","",600,600);
  TCanvas DiTauDRCanvas("DiTauDR","",600,600);
  TCanvas BPtCanvas("BPt","",600,600);
  TCanvas BEtaCanvas("BEta","",600,600);
  TCanvas BPhiCanvas("BPhi","",600,600);
  TCanvas ABDRCanvas("ABDR","",600,600);
  TCanvas MuPtOfTauMuTauHadCanvas("MuPtOfTauMuTauHad","",600,600);
  TCanvas BPtTauMuTauHadCanvas("BPtTauMuTauHad","",600,600);
  TCanvas DiBPtTauMuTauHadCanvas("DiBPtTauMuTauHad","",600,600);
  TCanvas BRatioCanvas("BRatio","",600,600);
  TCanvas DRbPartbRatioCanvas("DRbPartbRatio","",600,600);
  TCanvas PtDiffbPartbRatioCanvas("PtDiffbPartbRatio","",600,600);
  TCanvas BMuPtCanvas("BMuPt","",600,600);

  TCanvas DiTauDRVsAPtCanvas("DiTauDRVsAPt","" ,600,600);
  TCanvas DiTauDRVsAEtaCanvas("DiTauDRVsAEta","" ,600,600);
  TCanvas DiTauDRVsBPtLowCanvas("DiTauDRVsBPtLow","" ,600,600);
  TCanvas DiTauDRVsBPtHighCanvas("DiTauDRVsBPtHigh","" ,600,600);
  TCanvas ABDRVsAPtCanvas("ABDRVsAPt","",600,600);
  TCanvas ABDRVsDiTauDRCanvas("ABDRVsDiTauDR","",600,600);

  TCanvas SumBRatioVsBPartBRatiodRCanvas("SumBRatioVsBPartBRatiodR","",600,600);

std::cout << "<----------------Declared Canvases-------------->" << std::endl;

  //Format the 1D plots and Draw (canvas, hist, grid, log y, log z, color, size, style, xAxisTitle, xTitleSize, xLabelSize, xTitleOffSet, yAxisTitle, yTitleSize, yLabelSize, yTitleOffset)
  VariousFunctions::formatAndDrawCanvasAndHist1D(AMPartCanvas, AMPart_, 1, 0, 0, kBlack, 0.7, 20, "M(a1)", .04, .04, 1, "", .04, .04, 1, false);  
  VariousFunctions::formatAndDrawCanvasAndHist1D(BPtCutCanvas, BPtCut_, 1, 0, 0, kBlack, 0.7, 20, "", .04, .04, 1, "", .04, .04, 1, false); 
  VariousFunctions::formatAndDrawCanvasAndHist1D(BRatioCutCanvas, BRatioCut_, 1, 0, 0, kBlack, 0.7, 20, "", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(TauPtCanvas, TauPt_, 1, 0, 0, kBlack, 0.7, 20, "Pt(#tau)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(TauEtaCanvas, TauEta_, 1, 0, 0, kBlack, 0.7, 20, "#eta(#tau)", .04, .04, 1, "", .04, .04, 1, false);

  VariousFunctions::formatAndDrawCanvasAndHist1D(BPt7575Canvas, BPt7575_, 1, 0, 0, kBlack, 0.7, 20, "Pt(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BPt5050Canvas, BPt5050_, 1, 0, 0, kBlack, 0.7, 20, "Pt(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BPt3333Canvas, BPt3333_, 1, 0, 0, kBlack, 0.7, 20, "Pt(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BPt2525Canvas, BPt2525_, 1, 0, 0, kBlack, 0.7, 20, "Pt(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BPt7550Canvas, BPt7550_, 1, 0, 0, kBlack, 0.7, 20, "Pt(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BPt7525Canvas, BPt7525_, 1, 0, 0, kBlack, 0.7, 20, "Pt(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BPt5025Canvas, BPt5025_, 1, 0, 0, kBlack, 0.7, 20, "Pt(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BPt3325Canvas, BPt3325_, 1, 0, 0, kBlack, 0.7, 20, "Pt(b)", .04, .04, 1, "", .04, .04, 1, false);

  VariousFunctions::formatAndDrawCanvasAndHist1D(BEta7575Canvas, BEta7575_, 1, 0, 0, kBlack, 0.7, 20, "Eta(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BEta5050Canvas, BEta5050_, 1, 0, 0, kBlack, 0.7, 20, "Eta(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BEta3333Canvas, BEta3333_, 1, 0, 0, kBlack, 0.7, 20, "Eta(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BEta2525Canvas, BEta2525_, 1, 0, 0, kBlack, 0.7, 20, "Eta(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BEta7550Canvas, BEta7550_, 1, 0, 0, kBlack, 0.7, 20, "Eta(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BEta7525Canvas, BEta7525_, 1, 0, 0, kBlack, 0.7, 20, "Eta(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BEta5025Canvas, BEta5025_, 1, 0, 0, kBlack, 0.7, 20, "Eta(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BEta3325Canvas, BEta3325_, 1, 0, 0, kBlack, 0.7, 20, "Eta(b)", .04, .04, 1, "", .04, .04, 1, false);

  VariousFunctions::formatAndDrawCanvasAndHist1D(BPhi7575Canvas, BPhi7575_, 1, 0, 0, kBlack, 0.7, 20, "Phi(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BPhi5050Canvas, BPhi5050_, 1, 0, 0, kBlack, 0.7, 20, "Phi(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BPhi3333Canvas, BPhi3333_, 1, 0, 0, kBlack, 0.7, 20, "Phi(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BPhi2525Canvas, BPhi2525_, 1, 0, 0, kBlack, 0.7, 20, "Phi(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BPhi7550Canvas, BPhi7550_, 1, 0, 0, kBlack, 0.7, 20, "Phi(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BPhi7525Canvas, BPhi7525_, 1, 0, 0, kBlack, 0.7, 20, "Phi(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BPhi5025Canvas, BPhi5025_, 1, 0, 0, kBlack, 0.7, 20, "Phi(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BPhi3325Canvas, BPhi3325_, 1, 0, 0, kBlack, 0.7, 20, "Phi(b)", .04, .04, 1, "", .04, .04, 1, false);

  VariousFunctions::formatAndDrawCanvasAndHist1D(BdR7575Canvas, BdR7575_, 1, 0, 0, kBlack, 0.7, 20, "dR(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BdR5050Canvas, BdR5050_, 1, 0, 0, kBlack, 0.7, 20, "dR(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BdR3333Canvas, BdR3333_, 1, 0, 0, kBlack, 0.7, 20, "dR(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BdR2525Canvas, BdR2525_, 1, 0, 0, kBlack, 0.7, 20, "dR(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BdR7550Canvas, BdR7550_, 1, 0, 0, kBlack, 0.7, 20, "dR(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BdR7525Canvas, BdR7525_, 1, 0, 0, kBlack, 0.7, 20, "dR(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BdR5025Canvas, BdR5025_, 1, 0, 0, kBlack, 0.7, 20, "dR(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BdR3325Canvas, BdR3325_, 1, 0, 0, kBlack, 0.7, 20, "dR(b)", .04, .04, 1, "", .04, .04, 1, false);

  VariousFunctions::formatAndDrawCanvasAndHist1D(APtCanvas, APt_, 1, 0, 0, kBlack, 0.7, 20, "Pt(A)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(AEtaCanvas,AEta_, 1, 0, 0, kBlack, 0.7, 20, "#eta(A)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(DiTauDRCanvas, DiTauDR_, 1, 0, 0, kBlack, 0.7, 20, "dR(#tau #tau)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BPtCanvas, BPt_, 1, 0, 0, kBlack, 0.7, 20, "Pt(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BEtaCanvas, BEta_, 1, 0, 0, kBlack, 0.7, 20, "#eta(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BPhiCanvas, BPhi_, 1, 0, 0, kBlack, 0.7, 20, "#phi(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(ABDRCanvas, ABDR_, 1, 0, 0, kBlack, 0.7, 20, "dR(ab)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(MuPtOfTauMuTauHadCanvas, MuPtOfTauMuTauHad_, 1, 0, 0, kBlack, 0.7, 20, "Pt(mu)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BPtTauMuTauHadCanvas, BPtTauMuTauHad_, 1, 0, 0, kBlack, 0.7, 20, "Pt(b)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(DiBPtTauMuTauHadCanvas, DiBPtTauMuTauHad_, 1, 0, 0, kBlack, 0.7, 20, "Pt(bb)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BRatioCanvas, BRatio_, 1, 0, 0, kBlack, 0.7, 20, "bRatio", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(DRbPartbRatioCanvas, DRbPartbRatio_, 1, 0, 0, kBlack, 0.7, 20, "dR(bjet bPart)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(PtDiffbPartbRatioCanvas, PtDiffbPartbRatio_, 1, 0, 0, kBlack, 0.7, 20, "#Delta Pt(bjet bPart)", .04, .04, 1, "", .04, .04, 1, false);
  VariousFunctions::formatAndDrawCanvasAndHist1D(BMuPtCanvas, BMuPt_, 1, 0, 0, kBlack, 0.7, 20, "Pt(#mu_{b})", .04, .04, 1, "", .04, .04, 1, false);

  //format the 2d plots and draw (canvas, hist, grid, log y, log z, color, size, style, xaxistitle, xtitlesize, xlabelsize, xtitleoffset, yaxistitle, ytitlesize, ylabelsize, ytitleoffset,
  			      // zAxisTitle, zTitleSize, zLabelSize, zTitleOffset)
  VariousFunctions::formatAndDrawCanvasAndHist2D(DiTauDRVsAPtCanvas, DiTauDRVsAPt_, 0, 0, 0, kBlack, 7, 20, "dR(#tau#tau)", .04, .04, 1.1, "Pt(A)", .04, .04, 1.6, "", .04, .04, 1.0);
  VariousFunctions::formatAndDrawCanvasAndHist2D(DiTauDRVsAEtaCanvas, DiTauDRVsAEta_, 0, 0, 0, kBlack, 7, 20, "dR(#tau#tau)", .04, .04, 1.1, "#eta(A)", .04, .04, 1.6, "", .04, .04, 1.0);
  VariousFunctions::formatAndDrawCanvasAndHist2D(DiTauDRVsBPtLowCanvas, DiTauDRVsBPtLow_, 0, 0, 0, kBlack, 7, 20, "dR(#tau#tau)", .04, .04, 1.1, "Pt(bLow)", .04, .04, 1.6, "", .04, .04, 1.0);
  VariousFunctions::formatAndDrawCanvasAndHist2D(DiTauDRVsBPtHighCanvas, DiTauDRVsBPtHigh_, 0, 0, 0, kBlack, 7, 20, "dR(#tau#tau)", .04, .04, 1.1, "Pt(bHigh)", .04, .04, 1.6, "", .04, .04, 1.0);
  VariousFunctions::formatAndDrawCanvasAndHist2D(ABDRVsAPtCanvas, ABDRVsAPt_, 0, 0, 0, kBlack, 7, 20, "dR(ab)", .04, .04, 1.1, "Pt(A)", .04, .04, 1.6, "", .04, .04, 1.0);
  VariousFunctions::formatAndDrawCanvasAndHist2D(ABDRVsDiTauDRCanvas, ABDRVsDiTauDR_, 0, 0, 0, kBlack, 7, 20, "dR(ab)", .04, .04, 1.1, "dR(#tau#tau)", .04, .04, 1.6, "", .04, .04, 1.0);

  VariousFunctions::formatAndDrawCanvasAndHist2D(SumBRatioVsBPartBRatiodRCanvas, SumBRatioVsBPartBRatiodR_, 0, 0, 0, kBlack, 7, 20, "bRatio Sum", .04, .04, 1.1, "dR(bPart bRatio)", .04, .04, 1.6, "", .04, .04, 1.0);

std::cout << "<----------------Formatted Canvases and Histos-------------->" << std::endl;

  //Write output file
  out_->cd();
  AMPartCanvas.Write();
  BPtCutCanvas.Write();
  BRatioCutCanvas.Write();
  TauPtCanvas.Write();
  TauEtaCanvas.Write();

  BPt7575Canvas.Write();
  BPt5050Canvas.Write();
  BPt3333Canvas.Write();
  BPt2525Canvas.Write();
  BPt7550Canvas.Write();
  BPt7525Canvas.Write();
  BPt5025Canvas.Write();
  BPt3325Canvas.Write();

  BEta7575Canvas.Write();
  BEta5050Canvas.Write();
  BEta3333Canvas.Write();
  BEta2525Canvas.Write();
  BEta7550Canvas.Write();
  BEta7525Canvas.Write();
  BEta5025Canvas.Write();
  BEta3325Canvas.Write();

  BPhi7575Canvas.Write();
  BPhi5050Canvas.Write();
  BPhi3333Canvas.Write();
  BPhi2525Canvas.Write();
  BPhi7550Canvas.Write();
  BPhi7525Canvas.Write();
  BPhi5025Canvas.Write();
  BPhi3325Canvas.Write();

  BdR7575Canvas.Write();
  BdR5050Canvas.Write();
  BdR3333Canvas.Write();
  BdR2525Canvas.Write();
  BdR7550Canvas.Write();
  BdR7525Canvas.Write();
  BdR5025Canvas.Write();
  BdR3325Canvas.Write();

  APtCanvas.Write();
  AEtaCanvas.Write();
  DiTauDRCanvas.Write();
  BPtCanvas.Write();
  BEtaCanvas.Write();
  BPhiCanvas.Write();
  ABDRCanvas.Write();
  MuPtOfTauMuTauHadCanvas.Write();
  BPtTauMuTauHadCanvas.Write();
  DiBPtTauMuTauHadCanvas.Write();
  BRatioCanvas.Write();
  DRbPartbRatioCanvas.Write();
  PtDiffbPartbRatioCanvas.Write();
  BMuPtCanvas.Write();

  DiTauDRVsAPtCanvas.Write();
  DiTauDRVsAEtaCanvas.Write();
  DiTauDRVsBPtLowCanvas.Write();
  DiTauDRVsBPtHighCanvas.Write();
  ABDRVsAPtCanvas.Write();
  ABDRVsDiTauDRCanvas.Write();

  SumBRatioVsBPartBRatiodRCanvas.Write();

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
  if ((doDelete) && (AMPart_ != NULL)) delete AMPart_;
  AMPart_ = NULL;
  if ((doDelete) && (BPtCut_ != NULL)) delete BPtCut_;
  BPtCut_ = NULL;
  if ((doDelete) && (BRatioCut_ != NULL)) delete BRatioCut_;
  BRatioCut_ = NULL;
  if ((doDelete) && (TauPt_ != NULL)) delete TauPt_;
  TauPt_ = NULL;
  if ((doDelete) && (TauEta_ != NULL)) delete TauEta_;
  TauEta_ = NULL;

  if ((doDelete) && (BPt7575_ != NULL)) delete BPt7575_;
  BPt7575_ = NULL;
  if ((doDelete) && (BPt5050_ != NULL)) delete BPt5050_;
  BPt5050_ = NULL;
  if ((doDelete) && (BPt3333_ != NULL)) delete BPt3333_;
  BPt3333_ = NULL;
  if ((doDelete) && (BPt2525_ != NULL)) delete BPt2525_;
  BPt2525_ = NULL;
  if ((doDelete) && (BPt7550_ != NULL)) delete BPt7550_;
  BPt7550_ = NULL;
  if ((doDelete) && (BPt7525_ != NULL)) delete BPt7525_;
  BPt7525_ = NULL;
  if ((doDelete) && (BPt5025_ != NULL)) delete BPt5025_;
  BPt5025_ = NULL;
  if ((doDelete) && (BPt3325_ != NULL)) delete BPt3325_;
  BPt3325_ = NULL;

  if ((doDelete) && (BEta7575_ != NULL)) delete BEta7575_;
  BEta7575_ = NULL;
  if ((doDelete) && (BEta5050_ != NULL)) delete BEta5050_;
  BEta5050_ = NULL;
  if ((doDelete) && (BEta3333_ != NULL)) delete BEta3333_;
  BEta3333_ = NULL;
  if ((doDelete) && (BEta2525_ != NULL)) delete BEta2525_;
  BEta2525_ = NULL;
  if ((doDelete) && (BEta7550_ != NULL)) delete BEta7550_;
  BEta7550_ = NULL;
  if ((doDelete) && (BEta7525_ != NULL)) delete BEta7525_;
  BEta7525_ = NULL;
  if ((doDelete) && (BEta5025_ != NULL)) delete BEta5025_;
  BEta5025_ = NULL;
  if ((doDelete) && (BEta3325_ != NULL)) delete BEta3325_;
  BEta3325_ = NULL;

  if ((doDelete) && (BPhi7575_ != NULL)) delete BPhi7575_;
  BPhi7575_ = NULL;
  if ((doDelete) && (BPhi5050_ != NULL)) delete BPhi5050_;
  BPhi5050_ = NULL;
  if ((doDelete) && (BPhi3333_ != NULL)) delete BPhi3333_;
  BPhi3333_ = NULL;
  if ((doDelete) && (BPhi2525_ != NULL)) delete BPhi2525_;
  BPhi2525_ = NULL;
  if ((doDelete) && (BPhi7550_ != NULL)) delete BPhi7550_;
  BPhi7550_ = NULL;
  if ((doDelete) && (BPhi7525_ != NULL)) delete BPhi7525_;
  BPhi7525_ = NULL;
  if ((doDelete) && (BPhi5025_ != NULL)) delete BPhi5025_;
  BPhi5025_ = NULL;
  if ((doDelete) && (BPhi3325_ != NULL)) delete BPhi3325_;
  BPhi3325_ = NULL;


 if ((doDelete) && (BdR7575_ != NULL)) delete BdR7575_;
 BdR7575_ = NULL; 
 if ((doDelete) && (BdR5050_ != NULL)) delete BdR5050_;
 BdR5050_ = NULL; 
 if ((doDelete) && (BdR3333_ != NULL)) delete BdR3333_;
 BdR3333_ = NULL; 
 if ((doDelete) && (BdR2525_ != NULL)) delete BdR2525_;
 BdR2525_ = NULL; 
 if ((doDelete) && (BdR7550_ != NULL)) delete BdR7550_;
 BdR7550_ = NULL; 
 if ((doDelete) && (BdR7525_ != NULL)) delete BdR7525_;
 BdR7525_ = NULL; 
 if ((doDelete) && (BdR5025_ != NULL)) delete BdR5025_;
 BdR5025_ = NULL; 
 if ((doDelete) && (BdR3325_ != NULL)) delete BdR3325_;
 BdR3325_ = NULL;

  if ((doDelete) && (APt_ != NULL)) delete APt_;
  APt_ = NULL;
  if ((doDelete) && (AEta_ != NULL)) delete AEta_;
  AEta_ = NULL;
  if ((doDelete) && (DiTauDR_ != NULL)) delete DiTauDR_;
  DiTauDR_ = NULL;
  if ((doDelete) && (BPt_ != NULL)) delete BPt_;
  BPt_ = NULL;
  if ((doDelete) && (BEta_ != NULL)) delete BEta_;
  BEta_ = NULL;
  if ((doDelete) && (BPhi_ != NULL)) delete BPhi_;
  BPhi_ = NULL;
  if ((doDelete) && (ABDR_ != NULL)) delete ABDR_;
  ABDR_ = NULL;
  if ((doDelete) && (MuPtOfTauMuTauHad_ != NULL)) delete MuPtOfTauMuTauHad_;
  MuPtOfTauMuTauHad_ = NULL;
  if ((doDelete) && (BPtTauMuTauHad_ != NULL)) delete BPtTauMuTauHad_;
  BPtTauMuTauHad_ = NULL;
  if ((doDelete) && (DiBPtTauMuTauHad_ != NULL)) delete DiBPtTauMuTauHad_;
  DiBPtTauMuTauHad_ = NULL;
  if ((doDelete) && (BRatio_ != NULL)) delete BRatio_;
  BRatio_ = NULL;
  if ((doDelete) && (DRbPartbRatio_ != NULL)) delete DRbPartbRatio_;
  DRbPartbRatio_ = NULL;
  if ((doDelete) && (PtDiffbPartbRatio_ != NULL)) delete PtDiffbPartbRatio_;
  PtDiffbPartbRatio_ = NULL;
  if ((doDelete) && (BMuPt_ != NULL)) delete BMuPt_;
  BMuPt_ = NULL;

  if ((doDelete) && (DiTauDRVsAPt_ != NULL)) delete  DiTauDRVsAPt_;
  DiTauDRVsAPt_ = NULL;
  if ((doDelete) && (DiTauDRVsAEta_ != NULL)) delete DiTauDRVsAEta_;
  DiTauDRVsAEta_ = NULL;
  if ((doDelete) && (ABDRVsAPt_ != NULL)) delete ABDRVsAPt_;
  ABDRVsAPt_ = NULL;
  if ((doDelete) && (ABDRVsDiTauDR_ != NULL)) delete ABDRVsDiTauDR_;
  ABDRVsDiTauDR_ = NULL;

  if ((doDelete) && (SumBRatioVsBPartBRatiodR_ != NULL)) delete SumBRatioVsBPartBRatiodR_;
  SumBRatioVsBPartBRatiodR_ = NULL;
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
