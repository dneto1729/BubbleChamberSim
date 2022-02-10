// Make 2x2 canvas which shows contour plot, surface plot, 1D vx histogram and
// 1D vy histogram. This is for gamma rays that reach the bubble cell
// (detId = 2). "InputFile" is the root file you want to run the macro on. 
// usage in root 
// root[#] .x beamBubblePosPlots.C("InputFile")

#include <iostream>
#include <iomanip>
#include <sstream>

#include "TFile.h"
#include "TString.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"


int beamBubblePosPlots(string RFile){
    gStyle->SetOptStat("emr");
    //
    TFile *f1 = new TFile(RFile.c_str());
    //
    TString pstit;
    pstit = "BeamPos_";
    string pstit_id = RFile.substr (0,7);
    pstit += pstit_id; 

    //
    TTree *bubble = (TTree *)f1->Get("bubble"); // Brem gamma rays
    //
    TCanvas *c1 = new TCanvas("c1","Bubble Bremsstrahlung Position",1200,800);
    c1->Divide(2,2,0.01,0.01);
    // Setup histograms
    TH1D *h1x = new TH1D("h1x","Gamma pos x",72,-18.0,18.0);
    TH1D *h1y = new TH1D("h1y","Gamma pos y",72,-18.0,18.0);
    TH2D *h2c = new TH2D("h2c","",
        72, -18.0, 18.0,
        72, -18.0, 18.0);
    TH2D *h2s = new TH2D("h2s","",
        72, -18.0, 18.0,
        72, -18.0, 18.0);
    // Draw 1D Histograms
    c1->cd(3);
    bubble->Draw("vx>>h1x","detId==2 && pid==22","");
    h1x->GetXaxis()->SetTitle("x pos (mm)");
    c1->cd(4);
    bubble->Draw("vy>>h1y","detId==2 && pid==22","");
    h1y->GetXaxis()->SetTitle("y pos (mm)");
    // Draw 2D Histograms
    c1->cd(1);
    bubble->Draw("vy:vx>>h2c","detId==2 && pid==22","cont4z");
    h2c->GetXaxis()->SetTitle("x pos (mm)");
    h2c->GetYaxis()->SetTitle("y pos (mm)");
    c1->cd(2);
    bubble->Draw("vy:vx>>h2s","detId==2 && pid==22","surf3z");
    h2s->GetXaxis()->SetTitle("x pos (mm)");
    h2s->GetYaxis()->SetTitle("y pos (mm)");

    // Save as png
    pstit += ".gif";
    c1->Print(pstit.Data());

    return 0;

}
