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


void twoDim_To_1D_project()
{
  TF2 *f2= new TF2("f2","(-(8.83+x*0.2169+y*0.8139)+(10*log(8.83+x*0.2169+y*0.8139))-(10*log(10))+10-(6.342+x*0.05957+y*2.5286)+(6*log(6.342+x*0.05957+y*2.5286))-(6*log(6))+6)",-20,50,-2.,2.);
  TF2 *f2_= new TF2("f2_","(((-8.83-x*0.2169)+(10*log(8.83+x*0.2169))-(10*log(10))+10)+((-6.34195-y*2.529)+(6*log(6.34195+y*2.529))-(6*log(6))+6))",-20,50,-2.5,3);
  //f2->Draw();

  Double_t co=-0.1;
  Double_t coh=2;
  /*
  cout<<"GetMaximum=  "<<f2->GetMaximum()<<endl;
  cout<<"GetMaximumXY=  "<<f2->GetMaximumXY(co,coh)<<endl;
  std::cout << "GetMaximumXY = " << f2->GetMaximumXY(co, coh) << " at ( " << co << " , " << coh << " )" << std::endl;
  */
  //gkole
  cout << "gkole start: " << endl;
  cout<<"GetMaximum=  "<<f2_->GetMaximum()<<endl;
  cout<<"GetMaximumXY=  "<<f2_->GetMaximumXY(co,coh)<<endl;
  std::cout << "GetMaximumXY = " << f2_->GetMaximumXY(co, coh) << " at ( " << co << " , " << coh << " )" << std::endl;
  cout << "gkole end: " << endl;

  Double_t maximum = f2->GetMaximum();
  double contours[2];
  contours[0] = (maximum-2);
  contours[1] = (maximum-0.5);
  int colors[2] = {1,1};
  //likelihood_2d_->SetPalette(2,colors);
  f2->SetContour(2,contours);

  Double_t maximum_ = f2_->GetMaximum();
  double contours_[2];
  contours_[0] = (maximum_-2);
  contours_[1] = (maximum_-0.5);
  int colors_[2] = {1,1};
  //likelihood_2d_->SetPalette(2,colors);
  f2_->SetContour(2,contours_);

  
  // 1d projection
  TF1 *f21_= new TF1("f21_","(((-8.83-x*0.2169)+(10*log(8.83+x*0.2169))-(10*log(10))+10)+((-6.34195-[0]*2.529)+(6*log(6.34195+[0]*2.529))-(6*log(6))+6))",-20.0,50.0);
  
  f21_->SetParameter(0,-0.135263);
  cout << "f21_->GetMaximum(): " << f21_->GetMaximum() << endl;

  double horizontal_val = f21_->GetMaximum()-0.5;
  cout << "horizontal_val:" << horizontal_val << endl;

  //TF1 *f210_ = new TF1("f210_","horizontal_val.c_str()",-20,50);
  TF1 *f210_ = new TF1("f210_","-0.5000",-20,50);
  f210_->SetLineColor(kGreen);
 
  TLatex *tex = new TLatex(10,5.50,"2D function");
  TCanvas* c=new TCanvas("c","c",1000,1000);
  c->Divide(1,2); // 1 column, 2 row
  c->cd(1);
  f2_->Draw("cont1");
  c->cd(2);
  f21_->Draw("");
  f210_->Draw("SAME");
  tex->Draw();
  
}
