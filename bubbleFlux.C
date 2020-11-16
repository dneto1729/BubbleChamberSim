void bubbleFlux(){
  
  gROOT->Reset();
  
#define MAX_nentries 900;
  
  TString pstit;
  pstit = "bubbleFlux";
  
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
  
  Double_t Ne0 = 1.0e+07;  // Number of Electrons in Geant4
  Double_t Ib = 1.0; // Beam current
  Double_t e = 1.602e-19; // C
  Double_t Ne = Ib * 1.0e-6/e; // Number of Electron per 1 uC
  
  //// Geant4 Bresstrahlung Spectrum (Ne0)
  
  Double_t scale = Ne/Ne0; // Scale from Ne0 electrons to 1 uA per s
  
  //
  
  char runfile1[100];
  sprintf(runfile1,"out.root");
  f1 = new TFile(runfile1);
  
  TTree *bubble = (TTree*)f1->Get("bubble");
  TH1F* hS1  = new TH1F("hS1", "hS1",MAX_nentries,0.0,9.0);
  TH1F* hS2  = new TH1F("hS2", "hS2",MAX_nentries,0.0,9.0);
  bubble->Draw("kinE>>hS1","detId==1&&pid==22","");
  hS1->Scale(scale); 

  bubble->Draw("kinE>>hS2","detId==2&&pid==22","");
  hS2->Scale(scale); 

  ////  

  Double_t Ng = hS2->GetEntries() * scale;

  cout << "Total number of gammas in glass cell = " << Ng << " per microA per s" << endl;

  ////
  
  TCanvas *g1 = new TCanvas("g1","Bubble Bremsstrahlung Spectrum",40,40,700,500);
  
  g1->SetGrid();
  
  hS1->SetMinimum(1.0e+0);
  hS1->SetMaximum(1.0e+12);
  
  hS1->GetXaxis()->CenterTitle();
  hS1->GetXaxis()->SetTitleOffset(1.2);
  hS1->GetXaxis()->SetTitleSize(0.06);
  TString tit = "Photon Energy (MeV)";
  hS1->GetXaxis()->SetTitle(tit.Data());
  
  hS1->GetYaxis()->CenterTitle();
  hS1->GetYaxis()->SetTitleOffset(1.0);
  hS1->GetYaxis()->SetTitleSize(0.06);
  TString tit ="n_{#gamma} /(#muA s 0.01 MeV)";
  hS1->GetYaxis()->SetTitle(tit.Data());
  
  hS1->SetLineColor(kBlue);
  hS1->SetLineWidth(2.0);
  hS1->SetLineStyle(20);
  hS1->Draw("");

  //

  hS2->SetLineColor(kRed);
  hS2->SetLineWidth(2.0);
  hS2->SetLineStyle(20);
  hS2->Draw("same");

  ////
  
  leg = new TLegend(0.2,0.25,0.45,0.45);
  leg->SetFillColor(0);
  leg->SetShadowColor(0);
  leg->AddEntry(hS1,"Radiator ","L");
  leg->AddEntry(hS2,"Glass Cell ","L");
  leg->Draw();
  leg->SetHeader("T_{e} = 8.0 MeV");
  leg->Draw();
  
  //
  
   g1->cd();
   pstit += ".gif";
   g1->Print(pstit.Data());
   
}
