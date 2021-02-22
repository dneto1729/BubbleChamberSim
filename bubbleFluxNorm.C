// usage in root 
// root[#] .x bubbleFluxNorm.C(Te, Ne0, "InputFile"")
// Te is electron energy in MeV, Ne0 is the number of electrons simulated in Geant4 and InputFile
// is the root file you want to run the macro over. Input file should be formated outT###.root. 
// This does the normalized histograms (norm to 1 uA per s)

#include <iostream> // add
#include <iomanip> //add
#include <sstream> //add

void bubbleFluxNorm(Double_t Te, Double_t Ne0, string RFile){
  
  cout << std::setprecision(2) << fixed << "T_e = " << Te << " MeV" << endl; // Double check energy
  cout << std::setprecision(4) << scientific << "Number of electrons from Geant 4 =" << Ne0 << endl; // Double check number of electrons
  cout << "Root file is = " << RFile << endl; // Double check file to run

  gROOT->Reset();

  // Setup some strings for a legend entry and output gif filename
  std::stringstream Te_stream;
  Te_stream << std::fixed << std::setprecision(2) << Te;
  string energy = Te_stream.str();

  TString pstit;
  pstit = "bubbleFluxNorm_";
  string pstit_id = RFile.substr (0,7);
  pstit += pstit_id;  
  
 #define MAX_nentries 900;
  
  // define style here 
  // general parameters
  gStyle->SetOptDate(0);     gStyle->SetOptTitle(0);
  gStyle->SetStatColor(10);  gStyle->SetStatH(0.2);
  gStyle->SetStatW(0.3);     gStyle->SetOptStat(0); 
  
  // canvas parameters
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameBorderSize(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetCanvasColor(0);
  
  //
  
  // pads parameters
  // gStyle->SetPadColor(39); 
  gStyle->SetPadColor(0); 
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadBorderSize(0);
  gStyle->SetPadBottomMargin(0.18);
  gStyle->SetPadRightMargin(0.10);
  gStyle->SetPadLeftMargin(0.14);
  gStyle->SetLabelSize(0.04,"x");
  gStyle->SetLabelSize(0.04,"y");
  gStyle->SetTitleXSize(0.08);
  gStyle->SetPaperSize(10,12);
  
  gStyle->SetOptLogx(0);
  gStyle->SetOptLogy(1);
  
  // gStyle->SetNdivisions(505);
  
  gStyle->SetTitleYOffset(0.8);
  gStyle->SetTitleYSize(0.10);
  gROOT->ForceStyle();  

  //
  
 // Double_t Ne0 = 1.0e+07;  // Number of Electrons in Geant4
  Double_t Ib = 1.0; // Beam current
  Double_t e = 1.602e-19; // C
  Double_t Ne = Ib * 1.0e-6/e; // Number of Electron per 1 uC
  
  //// Geant4 Bresstrahlung Spectrum (Ne0)
  
  Double_t scale = Ne/Ne0; // Scale from Ne0 electrons to 1 uA per s
  
  // TFile
  
  char runfile1[100];
  sprintf(runfile1,"RFile");
  TFile *f1 = new TFile(RFile.c_str());
//  f1 = new TFile(runfile1);
//  TFile *f1 = TFile::Open("out.root");
  
  TTree *bubble = (TTree *)f1->Get("bubble");
  TH1F *hS1  = new TH1F("hS1", "hS1",900,0.0,9.0); // Radiator Gamma
  TH1F *hS2  = new TH1F("hS2", "hS2",900,0.0,9.0); // Bubble Cell Gamma

  bubble->Draw("kinE>>hS1","detId==1 && pid==22","");
  hS1->Scale(scale); 

  bubble->Draw("kinE>>hS2","detId==2 && pid==22","");
  hS2->Scale(scale); 

  ////  

  Double_t Ng = hS2->GetEntries() * scale;

  cout << "Total number of gammas in glass cell = " << Ng << " per microA per s" << endl;

  //// Canvas
  
  TCanvas *g1 = new TCanvas("g1","Bubble Bremsstrahlung Spectrum",40,40,700,500);
  
  g1->SetGrid();
  hS1->SetMinimum(1.0e+0);
  hS1->SetMaximum(1.0e+12);
  
  // X axis

  hS1->GetXaxis()->CenterTitle();
  hS1->GetXaxis()->SetTitleOffset(1.2);
  hS1->GetXaxis()->SetTitleSize(0.06);
  TString tit = "Photon Energy (MeV)";
  hS1->GetXaxis()->SetTitle(tit.Data());
  
  // Y axis

  hS1->GetYaxis()->CenterTitle();
  hS1->GetYaxis()->SetTitleOffset(1.0);
  hS1->GetYaxis()->SetTitleSize(0.06);
  TString tit1 ="n_{#gamma} /(#muA s 0.01 MeV)";
  hS1->GetYaxis()->SetTitle(tit1.Data());
  
  // hS1 Gamma's out of radiator

  hS1->SetLineColor(kBlue);
  hS1->SetLineWidth(2.0);
  hS1->SetLineStyle(20);
  hS1->Draw("");

  // hS2 Gamma's in the bubble cell

  hS2->SetLineColor(kRed);
  hS2->SetLineWidth(2.0);
  hS2->SetLineStyle(20);
  hS2->Draw("same");

  //// Legend
  
  TString HeaderName;
  HeaderName = "T_{e} = ";
  HeaderName += energy += " MeV";

  TLegend *leg = new TLegend(0.6489971,0.6995798,0.8997135,0.9012605,NULL,"brNDC");
  leg->SetFillColor(0);
  leg->SetShadowColor(0);
  leg->AddEntry(hS1,"Radiator ","L");
  leg->AddEntry(hS2,"Glass Cell ","L");
  leg->Draw();
  leg->SetHeader(HeaderName);
  leg->Draw();
  
  // Save as gif
  
   g1->cd();
   pstit += ".gif";
   g1->Print(pstit.Data());
   
}