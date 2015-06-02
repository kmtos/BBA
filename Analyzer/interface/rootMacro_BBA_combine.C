#include <string.h>
#include "TChain.h"
#include "TFile.h"
#include "TH1.h"
#include "TTree.h"
#include "TKey.h"
#include "Riostream.h"

void rootMacro_BBA_combine()
{
  gStyle->SetOptStat(kFALSE);

  TFile infile("/afs/cern.ch/user/k/ktos/BBA/CMSSW_7_1_11_patch2/src/BBA/Analyzer/BSUB/BBA_a30_v2_bRatSumVsdR_MAY_18_v2/BBA_a30_v2_bRatSumVsdR_MAY_18_v2.root");
  TFile *outFile = new TFile("interface/combined_Histograms_for_BBA_MAY_18.root", "RECREATE");

cout << "Files Created" << endl;

  TCanvas *CPt_ = (TCanvas*)infile.Get("BPt");
  TCanvas *CEta_ = (TCanvas*)infile.Get("BEta");
  TCanvas *CPhi_ = (TCanvas*)infile.Get("BPhi");
  TCanvas *CDRbPartbRatio_ = (TCanvas*)infile.Get("DRbPartbRatio");

  TCanvas *CPt7575_ = (TCanvas*)infile.Get("BPt7575");
  TCanvas *CPt5050_ = (TCanvas*)infile.Get("BPt5050");
  TCanvas *CPt3333_ = (TCanvas*)infile.Get("BPt3333");
  TCanvas *CPt2525_ = (TCanvas*)infile.Get("BPt2525");
  TCanvas *CPt7550_ = (TCanvas*)infile.Get("BPt7550");
  TCanvas *CPt7525_ = (TCanvas*)infile.Get("BPt7525");
  TCanvas *CPt5025_ = (TCanvas*)infile.Get("BPt5025");
  TCanvas *CPt3325_ = (TCanvas*)infile.Get("BPt3325");

  TCanvas *CEta7575_ = (TCanvas*)infile.Get("BEta7575");
  TCanvas *CEta5050_ = (TCanvas*)infile.Get("BEta5050");
  TCanvas *CEta3333_ = (TCanvas*)infile.Get("BEta3333");
  TCanvas *CEta2525_ = (TCanvas*)infile.Get("BEta2525");
  TCanvas *CEta7550_ = (TCanvas*)infile.Get("BEta7550");
  TCanvas *CEta7525_ = (TCanvas*)infile.Get("BEta7525");
  TCanvas *CEta5025_ = (TCanvas*)infile.Get("BEta5025");
  TCanvas *CEta3325_ = (TCanvas*)infile.Get("BEta3325");

  TCanvas *CPhi7575_ = (TCanvas*)infile.Get("BPhi7575");
  TCanvas *CPhi5050_ = (TCanvas*)infile.Get("BPhi5050");
  TCanvas *CPhi3333_ = (TCanvas*)infile.Get("BPhi3333");
  TCanvas *CPhi2525_ = (TCanvas*)infile.Get("BPhi2525");
  TCanvas *CPhi7550_ = (TCanvas*)infile.Get("BPhi7550");
  TCanvas *CPhi7525_ = (TCanvas*)infile.Get("BPhi7525");
  TCanvas *CPhi5025_ = (TCanvas*)infile.Get("BPhi5025");
  TCanvas *CPhi3325_ = (TCanvas*)infile.Get("BPhi3325");

  TCanvas *CdR7575_ = (TCanvas*)infile.Get("BdR7575");
  TCanvas *CdR5050_ = (TCanvas*)infile.Get("BdR5050");
  TCanvas *CdR3333_ = (TCanvas*)infile.Get("BdR3333");
  TCanvas *CdR2525_ = (TCanvas*)infile.Get("BdR2525");
  TCanvas *CdR7550_ = (TCanvas*)infile.Get("BdR7550");
  TCanvas *CdR7525_ = (TCanvas*)infile.Get("BdR7525");
  TCanvas *CdR5025_ = (TCanvas*)infile.Get("BdR5025");
  TCanvas *CdR3325_ = (TCanvas*)infile.Get("BdR3325");

cout << "Got Canvases" << endl;

  TH1F* BPt_ = (TH1F*)CPt_->GetPrimitive("BPt");
  TH1F* BEta_ = (TH1F*)CEta_->GetPrimitive("BEta");
  TH1F* BPhi_ = (TH1F*)CPhi_->GetPrimitive("BPhi");
  TH1F* DRbPartbRatio_ = (TH1F*)CDRbPartbRatio_->GetPrimitive("DRbPartbRatio");
 
  TH1F* BPt7575_ = (TH1F*)CPt7575_->GetPrimitive("BPt7575");
  TH1F* BPt5050_ = (TH1F*)CPt5050_->GetPrimitive("BPt5050");
  TH1F* BPt3333_ = (TH1F*)CPt3333_->GetPrimitive("BPt3333");
  TH1F* BPt2525_ = (TH1F*)CPt2525_->GetPrimitive("BPt2525");
  TH1F* BPt7550_ = (TH1F*)CPt7550_->GetPrimitive("BPt7550");
  TH1F* BPt7525_ = (TH1F*)CPt7525_->GetPrimitive("BPt7525");
  TH1F* BPt5025_ = (TH1F*)CPt5025_->GetPrimitive("BPt5025");
  TH1F* BPt3325_ = (TH1F*)CPt3325_->GetPrimitive("BPt3325");

  TH1F* BEta7575_ = (TH1F*)CEta7575_->GetPrimitive("BEta7575");
  TH1F* BEta5050_ = (TH1F*)CEta5050_->GetPrimitive("BEta5050");
  TH1F* BEta3333_ = (TH1F*)CEta3333_->GetPrimitive("BEta3333");
  TH1F* BEta2525_ = (TH1F*)CEta2525_->GetPrimitive("BEta2525");
  TH1F* BEta7550_ = (TH1F*)CEta7550_->GetPrimitive("BEta7550");
  TH1F* BEta7525_ = (TH1F*)CEta7525_->GetPrimitive("BEta7525");
  TH1F* BEta5025_ = (TH1F*)CEta5025_->GetPrimitive("BEta5025");
  TH1F* BEta3325_ = (TH1F*)CEta3325_->GetPrimitive("BEta3325");

  TH1F* BPhi7575_ = (TH1F*)CPhi7575_->GetPrimitive("BPhi7575");
  TH1F* BPhi5050_ = (TH1F*)CPhi5050_->GetPrimitive("BPhi5050");
  TH1F* BPhi3333_ = (TH1F*)CPhi3333_->GetPrimitive("BPhi3333");
  TH1F* BPhi2525_ = (TH1F*)CPhi2525_->GetPrimitive("BPhi2525");
  TH1F* BPhi7550_ = (TH1F*)CPhi7550_->GetPrimitive("BPhi7550");
  TH1F* BPhi7525_ = (TH1F*)CPhi7525_->GetPrimitive("BPhi7525");
  TH1F* BPhi5025_ = (TH1F*)CPhi5025_->GetPrimitive("BPhi5025");
  TH1F* BPhi3325_ = (TH1F*)CPhi3325_->GetPrimitive("BPhi3325");

  TH1F* BdR7575_ = (TH1F*)CdR7575_->GetPrimitive("BdR7575");
  TH1F* BdR5050_ = (TH1F*)CdR5050_->GetPrimitive("BdR5050");
  TH1F* BdR3333_ = (TH1F*)CdR3333_->GetPrimitive("BdR3333");
  TH1F* BdR2525_ = (TH1F*)CdR2525_->GetPrimitive("BdR2525");
  TH1F* BdR7550_ = (TH1F*)CdR7550_->GetPrimitive("BdR7550");
  TH1F* BdR7525_ = (TH1F*)CdR7525_->GetPrimitive("BdR7525");
  TH1F* BdR5025_ = (TH1F*)CdR5025_->GetPrimitive("BdR5025");
  TH1F* BdR3325_ = (TH1F*)CdR3325_->GetPrimitive("BdR3325");

cout << "Histograms assigned." << endl; 

  TCanvas BPtALLCanvas("BPtALL","",600,600);
  TCanvas BEtaALLCanvas("BEtaALL","",600,600);
  TCanvas BPhiALLCanvas("BPhiMALL","",600,600);
  TCanvas BdRALLCanvas("BdRMALL","",600,600);

cout << "Canvases created" << endl;

  BPt_->SetLineColor(1);
  BPt7575_->SetLineColor(kGray+1);
  BPt5050_->SetLineColor(kBlue+2);
  BPt3333_->SetLineColor(3);
  BPt2525_->SetLineColor(4);
  BPt7550_->SetLineColor(kOrange);
  BPt7525_->SetLineColor(kMagenta-4);
  BPt5025_->SetLineColor(8);
  BPt3325_->SetLineColor(kMagenta+2);

  BEta_->SetLineColor(1);
  BEta7575_->SetLineColor(kGray+1);
  BEta5050_->SetLineColor(kBlue+2);
  BEta3333_->SetLineColor(3);
  BEta2525_->SetLineColor(4);
  BEta7550_->SetLineColor(kOrange);
  BEta7525_->SetLineColor(kMagenta-4);
  BEta5025_->SetLineColor(8);
  BEta3325_->SetLineColor(kMagenta+2);
  
  BPhi_->SetLineColor(1);
  BPhi7575_->SetLineColor(kGray+1);
  BPhi5050_->SetLineColor(kBlue+2);
  BPhi3333_->SetLineColor(3);
  BPhi2525_->SetLineColor(4);
  BPhi7550_->SetLineColor(kOrange);
  BPhi7525_->SetLineColor(kMagenta-4);
  BPhi5025_->SetLineColor(8);
  BPhi3325_->SetLineColor(kMagenta+2);

  DRbPartbRatio_->SetLineColor(1);
  BdR7575_->SetLineColor(kGray+1);
  BdR5050_->SetLineColor(kBlue+2);
  BdR3333_->SetLineColor(3);
  BdR2525_->SetLineColor(4);
  BdR7550_->SetLineColor(kOrange);
  BdR7525_->SetLineColor(kMagenta-4);
  BdR5025_->SetLineColor(8);
  BdR3325_->SetLineColor(kMagenta+2);

cout << "Attributes set." << endl;  

  BPtALLCanvas.cd();
  BPt2525_->DrawNormalized();
  BPt7575_->DrawNormalized("SAME");
  BPt5050_->DrawNormalized("SAME");
  BPt3333_->DrawNormalized("SAME");
  BPt_->DrawNormalized("SAME");
  BPt7550_->DrawNormalized("SAME");
  BPt7525_->DrawNormalized("SAME");
  BPt5025_->DrawNormalized("SAME");
  BPt3325_->DrawNormalized("SAME");
  legPt = new TLegend(0.1,0.7,0.48,0.9);
  legPt->AddEntry(BPt_,"Total","f");
  legPt->AddEntry(BPt7575_,".75 .75","f");
  legPt->AddEntry(BPt5050_,".50 .50","f");
  legPt->AddEntry(BPt3333_,".33 .33","f");
  legPt->AddEntry(BPt2525_,".25 .25","f");
  legPt->AddEntry(BPt7550_,".75 .50","f");
  legPt->AddEntry(BPt7525_,".75 .25","f");
  legPt->AddEntry(BPt5025_,".50 .25","f");
  legPt->AddEntry(BPt3325_,".33 .25","f");
  legPt->Draw();

  BEtaALLCanvas.cd();
  BEta7575_->DrawNormalized();
  BEta_->DrawNormalized("SAME");
  BEta5050_->DrawNormalized("SAME");
  BEta3333_->DrawNormalized("SAME");
  BEta2525_->DrawNormalized("SAME");
  BEta7550_->DrawNormalized("SAME");
  BEta7525_->DrawNormalized("SAME");
  BEta5025_->DrawNormalized("SAME");
  BEta3325_->DrawNormalized("SAME");
  legEta = new TLegend(0.6,0.95,0.48,0.9);
  legEta->AddEntry(BEta_,"Total","f");
  legEta->AddEntry(BEta7575_,".75 .75","f");
  legEta->AddEntry(BEta5050_,".50 .50","f");
  legEta->AddEntry(BEta3333_,".33 .33","f");
  legEta->AddEntry(BEta2525_,".25 .25","f");
  legEta->AddEntry(BEta7550_,".75 .50","f");
  legEta->AddEntry(BEta7525_,".75 .25","f");
  legEta->AddEntry(BEta5025_,".50 .25","f");
  legEta->AddEntry(BEta3325_,".33 .25","f");
  legEta->Draw();

  BPhiALLCanvas.cd();
  BPhi7575_->DrawNormalized();
  BPhi_->DrawNormalized("SAME");
  BPhi5050_->DrawNormalized("SAME");
  BPhi3333_->DrawNormalized("SAME");
  BPhi2525_->DrawNormalized("SAME");
  BPhi7550_->DrawNormalized("SAME");
  BPhi7525_->DrawNormalized("SAME");
  BPhi5025_->DrawNormalized("SAME");
  BPhi3325_->DrawNormalized("SAME");
  legPhi = new TLegend(0.1,0.7,0.48,0.9);
  legPhi->AddEntry(BPhi_,"Total","f");
  legPhi->AddEntry(BPhi7575_,".75 .75","f");
  legPhi->AddEntry(BPhi5050_,".50 .50","f");
  legPhi->AddEntry(BPhi3333_,".33 .33","f");
  legPhi->AddEntry(BPhi2525_,".25 .25","f");
  legPhi->AddEntry(BPhi7550_,".75 .50","f");
  legPhi->AddEntry(BPhi7525_,".75 .25","f");
  legPhi->AddEntry(BPhi5025_,".50 .25","f");
  legPhi->AddEntry(BPhi3325_,".33 .25","f");
  legPhi->Draw();

  BdRALLCanvas.cd();
  BdR7575_->DrawNormalized();
  DRbPartbRatio_->DrawNormalized("SAME");
  BdR5050_->DrawNormalized("SAME");
  BdR3333_->DrawNormalized("SAME");
  BdR2525_->DrawNormalized("SAME");
  BdR7550_->DrawNormalized("SAME");
  BdR7525_->DrawNormalized("SAME");
  BdR5025_->DrawNormalized("SAME");
  BdR3325_->DrawNormalized("SAME");
  legdR = new TLegend(0.1,0.7,0.48,0.9);
  legEta->AddEntry(DRbPartbRatio_,"Total","f");
  legdR->AddEntry(BdR7575_,".75 .75","f");
  legdR->AddEntry(BdR5050_,".50 .50","f");
  legdR->AddEntry(BdR3333_,".33 .33","f");
  legdR->AddEntry(BdR2525_,".25 .25","f");
  legdR->AddEntry(BdR7550_,".75 .50","f");
  legdR->AddEntry(BdR7525_,".75 .25","f");
  legdR->AddEntry(BdR5025_,".50 .25","f");
  legdR->AddEntry(BdR3325_,".33 .25","f");
  legdR->Draw();

cout << "Histograms Drawn" << endl;

  outFile->cd();
  BPtALLCanvas.Write();
  BEtaALLCanvas.Write();
  BPhiALLCanvas.Write();
  BdRALLCanvas.Write();
  outFile->Write();
  outFile->Close();

cout << "end" << endl;

}//rootMacro_BBA_combine
