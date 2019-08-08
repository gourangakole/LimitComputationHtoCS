#include <cstdlib>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cstring>

#include "TMath.h"
#include "TFile.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TPluginManager.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h"
#include "TGraphPainter.h"
#include "TMultiGraph.h"
#include "TTree.h"
#include "TLatex.h"


using namespace std;

//TF1 *f1;
//TF2 *f2;

void twoDim_To_1D_project(){

  TCanvas *c1 = new TCanvas("c1","",5,30,650,600);
  c1->SetGrid(0,0);
  c1->SetFillStyle(4000);
  c1->SetFillColor(10);
  c1->SetTicky();
  c1->SetObjectStat(0);


  TF2 *f2_new = new TF2("f2_new", "((x+2)**2+(y-1)**2)",-5,5,-10,10); // -5<x<5; -10<y<10
  TF1 *f1_new = new TF1("f1_new","((x+2)**2+([0]-1)**2)",-5,5);

  // project to x plane (by setting y value to yval (e.g. y = 1) [remeber: (-2,+1) is the minimum points]
  f1_new->SetParameter(0,1); // setting [0] th parameter to "1" (equivalent y==1)
  f1_new->Draw();
  
  gPad->SaveAs("1D_projection.pdf"); 
  
  /*
  double xlim_min = 0.0;
  double xlim_max = 5.0;
  
  TF1 *f1 = new TF1("f1","-2*log(x)+2*x",xlim_min,xlim_max);
  double f_max = f1->GetMinimum();
  double f1_up = (f_max + f_max/2.0);
  double f1_down = (f_max - f_max/2.0);
  cout << "f_max: " << f_max << " " << "f1_up: " << " " << f1_up << " " << "f1_down: " << f1_down << endl;

  // interaction
  double x_0 = f1->GetX(f_max); // equivalent to mu_0
  cout << "x_0:  "<< x_0 << endl;
  double x_min = f1->GetX(f1_up,xlim_min,x_0);
  cout << "m_min: " << x_min << endl;
  double x_max = f1->GetX(f1_up,x_0,xlim_max);

  TLine *l1 = new TLine(x_min,f1_up,x_max,f1_up);
  l1->SetLineColor(kGreen);
  l1->SetLineWidth(2);

  TLine *l_cen = new TLine(x_0,0.0,x_0,f_max);
  l_cen->SetLineColor(kCyan);
  l_cen->SetLineWidth(2);
  l_cen->SetLineStyle(3);
  
  TLine *l_left = new TLine(x_min,0.0,x_min,f1_up);
  l_left->SetLineColor(kCyan);
  l_left->SetLineWidth(2);

  TLine *l_right = new TLine(x_max,0.0,x_max,f1_up);
  l_right->SetLineColor(kCyan);
  l_right->SetLineWidth(2);


  // text
  TPaveText *pl2 = new TPaveText(0.20,0.70,0.30,0.88, "brNDC");
  pl2->SetTextSize(0.04);
  pl2->SetFillColor(0);
  pl2->SetTextFont(132);
  pl2->SetBorderSize(0);
  pl2->SetTextAlign(11);
  //TLatex *   tex = new TLatex(0.17,0.78,"#hat{#mu} = 0.71 ^{#font[122]{+}0.48}_{#font[122]{-}0.43}");
  //  pl2->AddText(Form("#hat{#mu} = %.2f +%.2f -%.2f",x_0,x_min,x_max));// "#mu^{^}=",x_0.Data());

  TLatex *   tex = new TLatex(0.30,5.50,Form("#hat{#mu} = %.2f ^{#font[122]{+}%.2f}_{#font[122]{-}%.2f}",x_0,(x_max-x_0),(x_0-x_min))); 
  
  //TLatex *text_alpha = new TLatex(583, 150, "#color[2]{sparks}");

    
  f1->SetMinimum(0.0);
  f1->Draw();
  l1->Draw("SAME");
  l_cen->Draw("SAME");
  l_left->Draw("SAME");
  l_right->Draw("SAME");

  pl2->Draw();
  tex->Draw();
  gPad->SaveAs("mu_example.pdf");
  //  text_alpha->Draw();
  */
}


