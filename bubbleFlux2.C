void bubbleFlux2(){
  
  gROOT->Reset();
  
  TString pstit;
  pstit = "bubbleFlux2";
  
  // Define style here 
  // General parameters
  gStyle->SetOptDate(0);     gStyle->SetOptTitle(0);
  gStyle->SetStatColor(10);  gStyle->SetStatH(0.2);
  gStyle->SetStatW(0.3);     gStyle->SetOptStat(0); 
  
  // Canvas parameters
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameBorderSize(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetCanvasColor(0);
  
  // Pads parameters 
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
  gStyle->SetTitleYOffset(0.8);
  gStyle->SetTitleYSize(0.10);
  
  // X axis lin, Y axis log  
  gStyle->SetOptLogx(0);
  gStyle->SetOptLogy(1);
    
  gROOT->ForceStyle();  

  // TFile
  
  char runfile1[100];
  sprintf(runfile1,"outT400.root");
  TFile *f1 = new TFile("outT400.root");
  
  // Fill Histograms
  
  TTree *bubble = (TTree *)f1->Get("bubble");
  TH1F *hS1  = new TH1F("hS1", "hS1",900,0.0,9.0); // Radiator Gamma
  TH1F *hS2  = new TH1F("hS2", "hS2",900,0.0,9.0); // Bubble Cell Gamma
  bubble->Draw("kinE>>hS1","detId==1 && pid==22","");
  bubble->Draw("kinE>>hS2","detId==2 && pid==22","");
 
  // Quick Numbers  

  Double_t Ng = hS2->GetEntries();

  cout << "Total number of gammas in glass cell = " << Ng  << endl;

  Double_t Ig = hS2->Integral(390,400); // Integrate over last 100 KeV

  cout << "Total number of gammas in last 100 KeV = " << Ig << endl;

  // Canvas
  
  TCanvas *g1 = new TCanvas("g1","Bubble Bremsstrahlung Spectrum",40,40,700,500);
  
  g1->SetGrid();

  hS1->SetMinimum(1.0e+0);
  hS1->SetMaximum(1.0e+8);

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
  TString tit1 ="Histogram";
  hS1->GetYaxis()->SetTitle(tit1.Data());
  
  // hS1 Gamma's out of radiator
  
  hS1->SetLineColor(kBlue);
  hS1->SetLineWidth(2.0);
  hS1->SetLineStyle(20);
  hS1->Draw("");

  // hs2 Gamma's in the bubble cell

  hS2->SetLineColor(kRed);
  hS2->SetLineWidth(2.0);
  hS2->SetLineStyle(20);
  hS2->Draw("same");

  // Legend
  
  TLegend *leg = new TLegend(0.6489971,0.6995798,0.8997135,0.9012605,NULL,"brNDC");
  leg->SetFillColor(0);
  leg->SetShadowColor(0);
  leg->AddEntry(hS1,"Radiator ","L");
  leg->AddEntry(hS2,"Glass Cell ","L");
  leg->Draw();
  leg->SetHeader("T_{e} = 4.00 MeV");
  leg->Draw();
  
  // Save as gif
   
   g1->cd();
   pstit += ".gif";
   g1->Print(pstit.Data());

}
