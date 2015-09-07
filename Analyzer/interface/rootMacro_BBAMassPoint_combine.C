#include <string.h>
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TKey.h"
#include "Riostream.h"

void rootMacro_BBAMassPoint_combine()
{
  gStyle->SetOptStat(kFALSE);

  TFile infa20("/afs/cern.ch/user/k/ktos/BBA/CMSSW_7_1_11_patch2/src/BBA/Analyzer/BSUB/BBA_a20_v2_JUN_15_v1/BBA_a20_v2_JUN_15_v1.root");
  TFile infa30("/afs/cern.ch/user/k/ktos/BBA/CMSSW_7_1_11_patch2/src/BBA/Analyzer/BSUB/BBA_a30_v2_JUN_11_v2/BBA_a30_v2_JUN_11_v2.root");
  TFile infa40("/afs/cern.ch/user/k/ktos/BBA/CMSSW_7_1_11_patch2/src/BBA/Analyzer/BSUB/BBA_a40_v2_JUN_15_v1/BBA_a40_v2_JUN_15_v1.root");
  TFile infa60("/afs/cern.ch/user/k/ktos/BBA/CMSSW_7_1_11_patch2/src/BBA/Analyzer/BSUB/BBA_a60_v2_JUN_11_v1/BBA_a60_v2_JUN_11_v1.root");
  TFile *outFile = new TFile("interface/combined_Histograms_for_BBAMassPoints_JUN_5.root", "RECREATE");

cout << "Files Created" << endl;

  TCanvas *CBPt20_ = (TCanvas*)infa20.Get("BPt");
  TCanvas *CBPt30_ = (TCanvas*)infa30.Get("BPt");
  TCanvas *CBPt40_ = (TCanvas*)infa40.Get("BPt");
  TCanvas *CBPt60_ = (TCanvas*)infa60.Get("BPt");

  TCanvas *CBMuPt20_ = (TCanvas*)infa20.Get("BMuPt");
  TCanvas *CBMuPt30_ = (TCanvas*)infa30.Get("BMuPt");
  TCanvas *CBMuPt40_ = (TCanvas*)infa40.Get("BMuPt");
  TCanvas *CBMuPt60_ = (TCanvas*)infa60.Get("BMuPt");

  TCanvas *CBPtBest20_ = (TCanvas*)infa20.Get("BPtMatch");
  TCanvas *CBPtBest30_ = (TCanvas*)infa30.Get("BPtMatch");
  TCanvas *CBPtBest40_ = (TCanvas*)infa40.Get("BPtMatch");
  TCanvas *CBPtBest60_ = (TCanvas*)infa60.Get("BPtMatch");

  TCanvas *CBPtHigh20_ = (TCanvas*)infa20.Get("BPtHigh");
  TCanvas *CBPtHigh30_ = (TCanvas*)infa30.Get("BPtHigh");
  TCanvas *CBPtHigh40_ = (TCanvas*)infa40.Get("BPtHigh");
  TCanvas *CBPtHigh60_ = (TCanvas*)infa60.Get("BPtHigh");

  TCanvas *CDiTauDR20_ = (TCanvas*)infa20.Get("DiTauDR");
  TCanvas *CDiTauDR30_ = (TCanvas*)infa30.Get("DiTauDR");
  TCanvas *CDiTauDR40_ = (TCanvas*)infa40.Get("DiTauDR");
  TCanvas *CDiTauDR60_ = (TCanvas*)infa60.Get("DiTauDR");

cout << "Got Canvases" << endl;

  TH1F* BPt20_ = (TH1F*)CBPt20_->GetPrimitive("BPt");
  TH1F* BPt30_ = (TH1F*)CBPt30_->GetPrimitive("BPt");
  TH1F* BPt40_ = (TH1F*)CBPt40_->GetPrimitive("BPt");
  TH1F* BPt60_ = (TH1F*)CBPt60_->GetPrimitive("BPt");

  TH1F* BMuPt20_ = (TH1F*)CBMuPt20_->GetPrimitive("BMuPt");
  TH1F* BMuPt30_ = (TH1F*)CBMuPt30_->GetPrimitive("BMuPt");
  TH1F* BMuPt40_ = (TH1F*)CBMuPt40_->GetPrimitive("BMuPt");
  TH1F* BMuPt60_ = (TH1F*)CBMuPt60_->GetPrimitive("BMuPt");

  TH1F* BPtBest20_ = (TH1F*)CBPtBest20_->GetPrimitive("BPtMatch");
  TH1F* BPtBest30_ = (TH1F*)CBPtBest30_->GetPrimitive("BPtMatch");
  TH1F* BPtBest40_ = (TH1F*)CBPtBest40_->GetPrimitive("BPtMatch");
  TH1F* BPtBest60_ = (TH1F*)CBPtBest60_->GetPrimitive("BPtMatch");

  TH1F* BPtHigh20_ = (TH1F*)CBPtHigh20_->GetPrimitive("BPtHigh");
  TH1F* BPtHigh30_ = (TH1F*)CBPtHigh30_->GetPrimitive("BPtHigh");
  TH1F* BPtHigh40_ = (TH1F*)CBPtHigh40_->GetPrimitive("BPtHigh");
  TH1F* BPtHigh60_ = (TH1F*)CBPtHigh60_->GetPrimitive("BPtHigh");

  TH1F* DiTauDR20_ = (TH1F*)CDiTauDR20_->GetPrimitive("DiTauDR");
  TH1F* DiTauDR30_ = (TH1F*)CDiTauDR30_->GetPrimitive("DiTauDR");
  TH1F* DiTauDR40_ = (TH1F*)CDiTauDR40_->GetPrimitive("DiTauDR");
  TH1F* DiTauDR60_ = (TH1F*)CDiTauDR60_->GetPrimitive("DiTauDR");

cout << "Histograms assigned." << endl; 

  TCanvas BPtALLCanvas("BPtALL","",600,600);
  TCanvas BMuPtALLCanvas("BMuPtALL","",600,600);
  TCanvas BPtBestALLCanvas("BPtBestALL","",600,600);
  TCanvas BPtHighALLCanvas("BPtHighALL","",600,600);
  TCanvas DiTauDRALLCanvas("DiTauDRALL","",600,600);

cout << "Canvases created" << endl;

  BPt20_->SetLineColor(kGray+3);
  BPt30_->SetLineColor(kBlue);
  BPt40_->SetLineColor(kRed);
  BPt60_->SetLineColor(kGreen+2);

  BMuPt20_->SetLineColor(kGray+3);
  BMuPt30_->SetLineColor(kBlue);
  BMuPt40_->SetLineColor(kRed);
  BMuPt60_->SetLineColor(kGreen+2);
  
  BPtBest20_->SetLineColor(kGray+3);
  BPtBest30_->SetLineColor(kBlue);
  BPtBest40_->SetLineColor(kRed);
  BPtBest60_->SetLineColor(kGreen+2);

  BPtHigh20_->SetLineColor(kGray+3);
  BPtHigh30_->SetLineColor(kBlue);
  BPtHigh40_->SetLineColor(kRed);
  BPtHigh60_->SetLineColor(kGreen+2);

  DiTauDR20_->SetLineColor(kGray+3);
  DiTauDR30_->SetLineColor(kBlue);
  DiTauDR40_->SetLineColor(kRed);
  DiTauDR60_->SetLineColor(kGreen+2);

cout << "Attributes set." << endl;  

  BPtALLCanvas.cd();
  BPt20_->DrawNormalized();
  BPt30_->DrawNormalized("SAME");
  BPt40_->DrawNormalized("SAME");
  BPt60_->DrawNormalized("SAME");
  legPt = new TLegend(0.1,0.7,0.48,0.9);
  legPt->AddEntry(BPt20_,"a20","f");
  legPt->AddEntry(BPt30_,"a30","f");
  legPt->AddEntry(BPt40_,"a40","f");
  legPt->AddEntry(BPt60_,"a60","f");
  legPt->Draw();

  BMuPtALLCanvas.cd();
  BMuPt20_->DrawNormalized();
  BMuPt30_->DrawNormalized("SAME");
  BMuPt40_->DrawNormalized("SAME");
  BMuPt60_->DrawNormalized("SAME");
  legEta = new TLegend(0.6,0.95,0.48,0.9);
  legEta->AddEntry(BMuPt20_,"a20","f");
  legEta->AddEntry(BMuPt30_,"a30","f");
  legEta->AddEntry(BMuPt40_,"a40","f");
  legEta->AddEntry(BMuPt60_,"a60","f");
  legEta->Draw();

  BPtBestALLCanvas.cd();
  BPtBest20_->DrawNormalized();
  BPtBest30_->DrawNormalized("SAME");
  BPtBest40_->DrawNormalized("SAME");
  BPtBest60_->DrawNormalized("SAME");
  legPhi = new TLegend(0.1,0.7,0.48,0.9);
  legPhi->AddEntry(BPtBest20_,"a20","f");
  legPhi->AddEntry(BPtBest30_,"a30","f");
  legPhi->AddEntry(BPtBest40_,"a40","f");
  legPhi->AddEntry(BPtBest60_,"a60","f");
  legPhi->Draw();

  BPtHighALLCanvas.cd();
  BPtHigh20_->DrawNormalized();
  BPtHigh30_->DrawNormalized("SAME");
  BPtHigh40_->DrawNormalized("SAME");
  BPtHigh60_->DrawNormalized("SAME");
  legPhi->Draw();

  DiTauDRALLCanvas.cd();
  DiTauDR60_->DrawNormalized();
  DiTauDR30_->DrawNormalized("SAME");
  DiTauDR40_->DrawNormalized("SAME");
  DiTauDR20_->DrawNormalized("SAME");
  legPhi->Draw();

cout << "Histograms Drawn" << endl;

  outFile->cd();
  BPtALLCanvas.Write();
  BMuPtALLCanvas.Write();
  BPtBestALLCanvas.Write();
  BPtHighALLCanvas.Write();
  DiTauDRALLCanvas.Write();
  outFile->Write();
  outFile->Close();

cout << "end" << endl;

}//rootMacro_BBA_combine
