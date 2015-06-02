#include <string.h>
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TKey.h"
#include "Riostream.h"

void rootMacro_P68_combine()
{
  gStyle->SetOptStat(kFALSE);

  TFile fileP8("/afs/cern.ch/user/k/ktos/BBA/CMSSW_7_1_11_patch2/src/BBA/Analyzer/BSUB/ggH_a9_10K_Events_v1_ReqTauPlots_MAY_28_v1/ggH_a9_10K_Events_v1_ReqTauPlots_MAY_28_v1.root");
  TFile fileP6("/afs/cern.ch/user/k/ktos/CMSSW_5_3_11/src/ggH/Analyzer/BSUB/ggH_P6_ReqTauPlots_MAY_25_findIfInDaughterCheck.root");
  TFile *outFile = new TFile("interface/combined_Histograms_for_P6_P8_MAY_25.root", "RECREATE");

cout << "Files Created" << endl;

  TCanvas *CAPtPartP6_  = (TCanvas*)fileP6.Get("APtPart");
  TCanvas *CAEtaPartP6_  = (TCanvas*)fileP6.Get("AEtaPart");
  TCanvas *CAPhiPartP6_ = (TCanvas*)fileP6.Get("APhiPart");
  TCanvas *CAdRPartP6_  = (TCanvas*)fileP6.Get("AdRPart");
  TCanvas *CAdPhiPartP6_ = (TCanvas*)fileP6.Get("AdPhiPart");
  TCanvas *CTauPtPartP6_ = (TCanvas*)fileP6.Get("TauPtPart");
  TCanvas *CTauPt1PartP6_ = (TCanvas*)fileP6.Get("TauPt1Part");
  TCanvas *CTauPt2PartP6_ = (TCanvas*)fileP6.Get("TauPt2Part");
  TCanvas *CTauPt3PartP6_ = (TCanvas*)fileP6.Get("TauPt3Part");
  TCanvas *CTauPt4PartP6_ = (TCanvas*)fileP6.Get("TauPt4Part");
  TCanvas *CTauPtHighPartP6_ = (TCanvas*)fileP6.Get("TauPtHighPart");
  TCanvas *CTauPtLowPartP6_ = (TCanvas*)fileP6.Get("TauPtLowPart");

  TCanvas *CTauDecayModeP6_ = (TCanvas*)fileP6.Get("TauDecayMode");
  TCanvas *CTauPtP6_ = (TCanvas*)fileP6.Get("TauPt");
  TCanvas *CDiTauDRP6_ = (TCanvas*)fileP6.Get("DiTauDR");
  TCanvas *CTauEtaP6_ = (TCanvas*)fileP6.Get("TauEta");
  TCanvas *CTauPhiP6_ = (TCanvas*)fileP6.Get("TauPhi");

  TCanvas *CAPtPartP8_  = (TCanvas*)fileP8.Get("APtPart");
  TCanvas *CAEtaPartP8_ = (TCanvas*)fileP8.Get("AEtaPart");
  TCanvas *CAPhiPartP8_ = (TCanvas*)fileP8.Get("APhiPart");
  TCanvas *CAdRPartP8_ = (TCanvas*)fileP8.Get("AdRPart");
  TCanvas *CAdPhiPartP8_ = (TCanvas*)fileP8.Get("AdPhiPart");
  TCanvas *CTauPtPartP8_ = (TCanvas*)fileP8.Get("TauPtPart");
  TCanvas *CTauPt1PartP8_ = (TCanvas*)fileP8.Get("TauPt1Part");
  TCanvas *CTauPt2PartP8_ = (TCanvas*)fileP8.Get("TauPt2Part");
  TCanvas *CTauPt3PartP8_ = (TCanvas*)fileP8.Get("TauPt3Part");
  TCanvas *CTauPt4PartP8_ = (TCanvas*)fileP8.Get("TauPt4Part");
  TCanvas *CTauPtHighPartP8_ = (TCanvas*)fileP8.Get("TauPtHighPart");
  TCanvas *CTauPtLowPartP8_ = (TCanvas*)fileP8.Get("TauPtLowPart");

  TCanvas *CTauDecayModeP8_ = (TCanvas*)fileP8.Get("TauDecayMode");
  TCanvas *CTauPtP8_ = (TCanvas*)fileP8.Get("TauPt");
  TCanvas *CDiTauDRP8_ = (TCanvas*)fileP8.Get("DiTauDR");
  TCanvas *CTauEtaP8_ = (TCanvas*)fileP8.Get("TauEta");
  TCanvas *CTauPhiP8_ = (TCanvas*)fileP8.Get("TauPhi");

cout << "Got Canvases" << endl;
 
  TH1F* APtPartP6_ = (TH1F*)CAPtPartP6_->GetPrimitive("APtPart");
  TH1F* AEtaPartP6_ = (TH1F*)CAEtaPartP6_->GetPrimitive("AEtaPart");
  TH1F* APhiPartP6_ = (TH1F*)CAPhiPartP6_->GetPrimitive("APhiPart");
  TH1F* AdRPartP6_  = (TH1F*)CAdRPartP6_->GetPrimitive("AdRPart");
  TH1F* AdPhiPartP6_ = (TH1F*)CAdPhiPartP6_->GetPrimitive("AdPhiPart");
  TH1F* TauPtPartP6_ = (TH1F*)CTauPtPartP6_->GetPrimitive("TauPtPart");
  TH1F* TauPt1PartP6_ = (TH1F*)CTauPt1PartP6_->GetPrimitive("TauPt1Part");
  TH1F* TauPt2PartP6_ = (TH1F*)CTauPt2PartP6_->GetPrimitive("TauPt2Part");
  TH1F* TauPt3PartP6_ = (TH1F*)CTauPt3PartP6_->GetPrimitive("TauPt3Part");
  TH1F* TauPt4PartP6_ = (TH1F*)CTauPt4PartP6_->GetPrimitive("TauPt4Part");
  TH1F* TauPtHighPartP6_ = (TH1F*)CTauPtHighPartP6_->GetPrimitive("TauPtHighPart");
  TH1F* TauPtLowPartP6_ = (TH1F*)CTauPtLowPartP6_->GetPrimitive("TauPtLowPart");
  
  TH1F* TauDecayModeP6_ = (TH1F*)CTauDecayModeP6_->GetPrimitive("TauDecayMode");
  TH1F* TauPtP6_ = (TH1F*)CTauPtP6_->GetPrimitive("TauPt");
  TH1F* DiTauDRP6_ = (TH1F*)CDiTauDRP6_->GetPrimitive("DiTauDR");
  TH1F* TauEtaP6_ = (TH1F*)CTauEtaP6_->GetPrimitive("TauEta");
  TH1F* TauPhiP6_ = (TH1F*)CTauPhiP6_->GetPrimitive("TauPhi");


  TH1F* APtPartP8_ = (TH1F*)CAPtPartP8_->GetPrimitive("APtPart");
  TH1F* AEtaPartP8_ = (TH1F*)CAEtaPartP8_->GetPrimitive("AEtaPart");
  TH1F* APhiPartP8_ = (TH1F*)CAPhiPartP8_->GetPrimitive("APhiPart");
  TH1F* AdRPartP8_  = (TH1F*)CAdRPartP8_->GetPrimitive("AdRPart");
  TH1F* AdPhiPartP8_ = (TH1F*)CAdPhiPartP8_->GetPrimitive("AdPhiPart");
  TH1F* TauPtPartP8_ = (TH1F*)CTauPtPartP8_->GetPrimitive("TauPtPart");
  TH1F* TauPt1PartP8_ = (TH1F*)CTauPt1PartP8_->GetPrimitive("TauPt1Part");
  TH1F* TauPt2PartP8_ = (TH1F*)CTauPt2PartP8_->GetPrimitive("TauPt2Part");
  TH1F* TauPt3PartP8_ = (TH1F*)CTauPt3PartP8_->GetPrimitive("TauPt3Part");
  TH1F* TauPt4PartP8_ = (TH1F*)CTauPt4PartP8_->GetPrimitive("TauPt4Part");
  TH1F* TauPtHighPartP8_ = (TH1F*)CTauPtHighPartP8_->GetPrimitive("TauPtHighPart");
  TH1F* TauPtLowPartP8_ = (TH1F*)CTauPtLowPartP8_->GetPrimitive("TauPtLowPart");
  
  TH1F* TauDecayModeP8_ = (TH1F*)CTauDecayModeP8_->GetPrimitive("TauDecayMode");
  TH1F* TauPtP8_ = (TH1F*)CTauPtP8_->GetPrimitive("TauPt");
  TH1F* DiTauDRP8_ = (TH1F*)CDiTauDRP8_->GetPrimitive("DiTauDR");
  TH1F* TauEtaP8_ = (TH1F*)CTauEtaP8_->GetPrimitive("TauEta");
  TH1F* TauPhiP8_ = (TH1F*)CTauPhiP8_->GetPrimitive("TauPhi");

cout << "Histograms assigned." << endl; 

  TCanvas APtPartBOTHCanvas("APtPartBOTH","",600,600);
  TCanvas AEtaPartBOTHCanvas("AEtaPartBOTH","",600,600);
  TCanvas APhiPartBOTHCanvas("APhiPartBOTH","",600,600);
  TCanvas AdRPartBOTHCanvas("AdRPartBOTH","",600,600);
  TCanvas AdPhiPartBOTHCanvas("AdPhiPartBOTH","",600,600);
  TCanvas TauPtPartBOTHCanvas("TauPtPartBOTH","",600,600);
  TCanvas TauPt1PartBOTHCanvas("TauPt1PartBOTH","",600,600);
  TCanvas TauPt2PartBOTHCanvas("TauPt2PartBOTH","",600,600);
  TCanvas TauPt3PartBOTHCanvas("TauPt3PartBOTH","",600,600);
  TCanvas TauPt4PartBOTHCanvas("TauPt4PartBOTH","",600,600);
  TCanvas TauPtHighPartBOTHCanvas("TauPtHighPartBOTH","",600,600);
  TCanvas TauPtLowPartBOTHCanvas("TauPtLowPartBOTH","",600,600);

  TCanvas TauDecayModeBOTHCanvas("TauDecayModeBOTH","",600,600);
  TCanvas TauPtBOTHCanvas("TauPtBOTH","",600,600);
  TCanvas DiTauDRBOTHCanvas("DiTauDRBOTH","",600,600);
  TCanvas TauEtaBOTHCanvas("TauEtaBOTH","",600,600);
  TCanvas TauPhiBOTHCanvas("TauPhiBOTH","",600,600);

cout << "Canvases created" << endl;

  APtPartP8_->SetLineColor(kRed);
  AEtaPartP8_->SetLineColor(kRed);
  APhiPartP8_->SetLineColor(kRed);
  AdRPartP8_->SetLineColor(kRed);
  AdPhiPartP8_->SetLineColor(kRed);
  TauPtPartP8_->SetLineColor(kRed);
  TauPt1PartP8_->SetLineColor(kRed); 
  TauPt2PartP8_->SetLineColor(kRed);
  TauPt3PartP8_->SetLineColor(kRed);
  TauPt4PartP8_->SetLineColor(kRed);
  TauPtHighPartP8_->SetLineColor(kRed);
  TauPtLowPartP8_->SetLineColor(kRed);

  TauDecayModeP8_->SetLineColor(kRed);
  TauPtP8_->SetLineColor(kRed);
  DiTauDRP8_->SetLineColor(kRed);
  TauEtaP8_->SetLineColor(kRed);
  TauPhiP8_->SetLineColor(kRed);

  APtPartP6_->SetLineColor(kBlue);
  AEtaPartP6_->SetLineColor(kBlue);
  APhiPartP6_->SetLineColor(kBlue);
  AdRPartP6_->SetLineColor(kBlue);
  AdPhiPartP6_->SetLineColor(kBlue);
  TauPtPartP6_->SetLineColor(kBlue);
  TauPt1PartP6_->SetLineColor(kBlue);
  TauPt2PartP6_->SetLineColor(kBlue);
  TauPt3PartP6_->SetLineColor(kBlue);
  TauPt4PartP6_->SetLineColor(kBlue);
  TauPtHighPartP6_->SetLineColor(kBlue);
  TauPtLowPartP6_->SetLineColor(kBlue);

  TauDecayModeP6_->SetLineColor(kBlue);
  TauPtP6_->SetLineColor(kBlue);
  DiTauDRP6_->SetLineColor(kBlue);
  TauEtaP6_->SetLineColor(kBlue);
  TauPhiP6_->SetLineColor(kBlue);



cout << "Attributes set." << endl;  

  APtPartBOTHCanvas.cd();
  APtPartP8_->DrawNormalized();
  APtPartP6_->DrawNormalized("SAME");
  legPt = new TLegend(0.7, 0.7, 0.9,0.9);
  legPt->AddEntry(APtPartP8_,"Pythia 8","f");
  legPt->AddEntry(APtPartP6_,"Pythia 6","f");
  legPt->Draw();

  AEtaPartBOTHCanvas.cd();
  AEtaPartP6_->DrawNormalized();
  AEtaPartP8_->DrawNormalized("SAME");
  legPt->Draw();

  APhiPartBOTHCanvas.cd();
  APhiPartP6_->DrawNormalized();
  APhiPartP8_->DrawNormalized("SAME");
  legPt->Draw();

  AdRPartBOTHCanvas.cd();
  AdRPartP6_->DrawNormalized();
  AdRPartP8_->DrawNormalized("SAME");
  legPt->Draw();

  AdPhiPartBOTHCanvas.cd();
  AdPhiPartP6_->DrawNormalized();
  AdPhiPartP8_->DrawNormalized("SAME");
  legPt->Draw();

  TauPtPartBOTHCanvas.cd();
  TauPtPartP8_->DrawNormalized();
  TauPtPartP6_->DrawNormalized("SAME");
  legPt->Draw();

  TauPt1PartBOTHCanvas.cd();
  TauPt1PartP8_->DrawNormalized();
  TauPt1PartP6_->DrawNormalized("SAME");
  legPt->Draw();

  TauPt2PartBOTHCanvas.cd();
  TauPt2PartP8_->DrawNormalized();
  TauPt2PartP6_->DrawNormalized("SAME");
  legPt->Draw();

  TauPt3PartBOTHCanvas.cd();
  TauPt3PartP8_->DrawNormalized();
  TauPt3PartP6_->DrawNormalized("SAME");
  legPt->Draw();

  TauPt4PartBOTHCanvas.cd();
  TauPt4PartP8_->DrawNormalized();
  TauPt4PartP6_->DrawNormalized("SAME");
  legPt->Draw();

  TauPtHighPartBOTHCanvas.cd();
  TauPtHighPartP8_->DrawNormalized();
  TauPtHighPartP6_->DrawNormalized("SAME");
  legPt->Draw();

  TauPtLowPartBOTHCanvas.cd();
  TauPtLowPartP8_->DrawNormalized();
  TauPtLowPartP6_->DrawNormalized("SAME");
  legPt->Draw();

  TauDecayModeBOTHCanvas.cd();
  TauDecayModeP8_->DrawNormalized();
  TauDecayModeP6_->DrawNormalized("SAME");
  legPt->Draw();

  TauPtBOTHCanvas.cd();
  TauPtP6_->DrawNormalized();
  TauPtP8_->DrawNormalized("SAME");
  legPt->Draw();

  DiTauDRBOTHCanvas.cd();
  DiTauDRP8_->DrawNormalized();
  DiTauDRP6_->DrawNormalized("SAME");
  legPt->Draw();

  TauEtaBOTHCanvas.cd();
  TauEtaP6_->DrawNormalized();
  TauEtaP8_->DrawNormalized("SAME");
  legPt->Draw();

  TauPhiBOTHCanvas.cd();
  TauPhiP8_->DrawNormalized();
  TauPhiP6_->DrawNormalized("SAME");
  legPt->Draw();


cout << "Histograms Drawn" << endl;

  outFile->cd();
  APtPartBOTHCanvas.Write();
  AEtaPartBOTHCanvas.Write();
  APhiPartBOTHCanvas.Write();
  AdRPartBOTHCanvas.Write();
  AdPhiPartBOTHCanvas.Write();
  TauPtPartBOTHCanvas.Write();
  TauPt1PartBOTHCanvas.Write();
  TauPt2PartBOTHCanvas.Write();
  TauPt3PartBOTHCanvas.Write();
  TauPt4PartBOTHCanvas.Write();
  TauPtHighPartBOTHCanvas.Write();
  TauPtLowPartBOTHCanvas.Write();

  TauDecayModeBOTHCanvas.Write();
  TauPtBOTHCanvas.Write();
  DiTauDRBOTHCanvas.Write();
  TauEtaBOTHCanvas.Write();
  TauPhiBOTHCanvas.Write();
  outFile->Write();
  outFile->Close();

cout << "end" << endl;

cout << "PYTHIA6" << endl;
for(int i=1; i<10; i++)
  std::cout << "\tBin #" << i << " has " << TauDecayModeP6_->GetBinContent(i) << " counts." << std::endl;

cout << "PYTHIA8" << endl;
for(int i=1; i<10; i++) 
  std::cout << "\tBin #" << i << " has " << TauDecayModeP8_->GetBinContent(i) << " counts." << std::endl;

}//rootMacro_P68_combine
