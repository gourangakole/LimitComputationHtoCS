#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <algorithm> 

void makeHPlusDataCardWithLumi(TString histname="mjj_kfit", string cat_name = "", string lumi_cat = "lumiA")
//void makeHPlusDataCardWithLumi(TString histname="mjj_kfit", string cat_name = "cat1", string lumi_cat = "lumiA")
{
  // Luminosity measured by pixelLumicalc
  
  double lumiB = 5090899672;
  double lumiC = 2348989796; 
  double lumiD = 4208427684;
  double lumiE = 4008867013;
  double lumiF = 3105455587;
  double lumiG = 7425047006;
  double lumiH = 8074187927 + 216594264;
  
  double scale_factor = 0.0;
  
  if(lumi_cat.find("lumiB")!=string::npos) scale_factor = lumiB;
  else if(lumi_cat.find("lumiC")!=string::npos) scale_factor = lumiC;
  else if(lumi_cat.find("lumiD")!=string::npos) scale_factor = lumiD;
  else if(lumi_cat.find("lumiE")!=string::npos) scale_factor = lumiE;
  else if(lumi_cat.find("lumiF")!=string::npos) scale_factor = lumiF;
  else if(lumi_cat.find("lumiG")!=string::npos) scale_factor = lumiG;
  else if(lumi_cat.find("lumiH")!=string::npos) scale_factor = lumiH;
  else scale_factor = lumiB + lumiC + lumiD +lumiE +lumiF + lumiG+ lumiH;
  cout << "Lumi: " << scale_factor << endl;
  
  double totLumi = (lumiB + lumiC + lumiD +lumiE +lumiF + lumiG+ lumiH)/pow(10,9);
  cout << "totLumi" << totLumi << endl; 

  // if lumi weight is applied the pass only scale_factor = 1
  scale_factor = 1.0; 
  
  cout << "Final scalefactor: " << scale_factor << endl;

  /*
  TFile *f;
  if(cat_name.find("cat")!=string::npos)
    f = new TFile(Form("HplusResJECShapes_%s.root",cat_name.c_str()), "READ");
  else f = new TFile("HplusResJECShapes.root", "READ");

  TH1F *h_data_diff = (f->Get("ResJES_rel_scale"))->Clone("h_data_diff"); // dataJEC dif histogram for muon
  */

  TFile* fout;
  if(cat_name.find("cat")!=string::npos)
    fout = new TFile(Form("HplusShapes_%s.root", cat_name.c_str()), "RECREATE");
  else fout = new TFile("HplusShapes.root", "RECREATE");
  
  cout << "datacards preparation: " << Form("ohhhh_%4s", cat_name.c_str()) << endl;
  
  TString inputFilePath("$PWD/stack_20171104_Mu_sys/");
  //TString inputFilePath("/afs/cern.ch/user/r/rverma/public/stack_20171013_Mu_sys_new/");

  cout << "inputpath:  " << inputFilePath << endl;
  TFile* fttbar = TFile::Open(inputFilePath+"all_TTJetsP.root", "READ");  // all_TTJetsP.root and all_TTJetsM (P stand for Powheg and M = Madgraph)
  if(fttbar == 0) return;
  if(fttbar->IsZombie()){fttbar->Close(); return;}

  cout << "tt~ file opened:" << endl; 
  /*
  TFile* fttbar_scaleup = TFile::Open(inputFilePath+"ttbar_scaleup_ele_selection.root", "READ");
  if(fttbar_scaleup == 0) return;
  if(fttbar_scaleup->IsZombie()){fttbar_scaleup->Close(); return;}

  TFile* fttbar_scaledown = TFile::Open(inputFilePath+"ttbar_scaledown_ele_selection.root", "READ");
  if(fttbar_scaledown == 0) return;
  if(fttbar_scaledown->IsZombie()){fttbar_scaledown->Close(); return;}
  
  
  TFile* fttbar_matchingup = TFile::Open(inputFilePath+"ttbar_matchingup_ele_selection.root", "READ");
  if(fttbar_matchingup == 0) return;
  if(fttbar_matchingup->IsZombie()){fttbar_matchingup->Close(); return;}

  TFile* fttbar_matchingdown = TFile::Open(inputFilePath+"ttbar_matchingdown_ele_selection.root", "READ");
  if(fttbar_matchingdown == 0) return;
  if(fttbar_matchingdown->IsZombie()){fttbar_matchingdown->Close(); return;}
  */

  fout->cd();
  TH1F* ttbar = (TH1F*)(fttbar->Get("base/Iso/KinFit/"+histname))->Clone("ttbar");
  
  TH1F* ttbar_topPtweight = (TH1F*)(fttbar->Get("base/SF_topPtWeights"))->Clone("ttbar_topPtweight"); // get top pt weight
  ttbar->SetName("ttbar");
  ttbar->Scale(scale_factor/ttbar_topPtweight->GetMean()); // apply avg top pt weight
  ttbar->Write("ttbar");

  TH1F* ttbar_JESUp = (TH1F*)(fttbar->Get("JESPlus/Iso/KinFit/"+histname))->Clone("ttbar_JESUp"); 
  ttbar_JESUp->SetName("ttbar_JESUp");
  ttbar_JESUp->Scale(scale_factor/ttbar_topPtweight->GetMean()); 
  ttbar_JESUp->Write("ttbar_JESUp");
  TH1F* ttbar_JESDown = (TH1F*)(fttbar->Get("JESMinus/Iso/KinFit/"+histname))->Clone("ttbar_JESDown");  
  ttbar_JESDown->SetName("ttbar_JESDown");
  ttbar_JESDown->Scale(scale_factor/ttbar_topPtweight->GetMean());  
  ttbar_JESDown->Write("ttbar_JESDown");

  TH1F* ttbar_JERUp = (TH1F*)(fttbar->Get("JERPlus/Iso/KinFit/"+histname))->Clone("ttbar_JERUp");
  ttbar_JERUp->SetName("ttbar_JERUp");
  ttbar_JERUp->Scale(scale_factor/ttbar_topPtweight->GetMean());
  ttbar_JERUp->Write("ttbar_JERUp");
  TH1F* ttbar_JERDown = (TH1F*)(fttbar->Get("JERMinus/Iso/KinFit/"+histname))->Clone("ttbar_JERDown");
  ttbar_JERDown->SetName("ttbar_JERDown");
  ttbar_JERDown->Scale(scale_factor/ttbar_topPtweight->GetMean());
  ttbar_JERDown->Write("ttbar_JERDown");

  //// ---------- Edited this part ------------------
  TH1F* ttbar_topPtUp = (TH1F*)(fttbar->Get("TopPtPlus/Iso/KinFit/"+histname))->Clone("ttbar_topPtUp");
  ttbar_topPtUp->SetName("ttbar_topPtUp");
  TH1F* ttbar_topPtweightPlus = (TH1F*)(fttbar->Get("TopPtPlus/SF_topPtWeights"))->Clone("ttbar_topPtweightPlus");
  ttbar_topPtUp->Scale(scale_factor/ttbar_topPtweightPlus->GetBinContent(2));
  ttbar_topPtUp->Write("ttbar_topPtUp");

  TH1F* ttbar_topPtDown = (TH1F*)(fttbar->Get("TopPtMinus/Iso/KinFit/"+histname))->Clone("ttbar_topPtDown");
  ttbar_topPtDown->SetName("ttbar_topPtDown");
  TH1F* ttbar_topPtweightMinus = (TH1F*)(fttbar->Get("TopPtMinus/SF_topPtWeights"))->Clone("ttbar_topPtweightMinus");
  ttbar_topPtDown->Scale(scale_factor/ttbar_topPtweightMinus->GetBinContent(2));
  ttbar_topPtDown->Write("ttbar_topPtDown");
  /// ---------------------------------------------
  
  
  TH1F* ttbar_bTagUp = (TH1F*)(fttbar->Get("bTagPlus/Iso/KinFit/"+histname))->Clone("ttbar_bTagUp");  
  ttbar_bTagUp->Scale(scale_factor/ttbar_topPtweight->GetMean());  
  TH1F* ttbar_bTagDown = (TH1F*)(fttbar->Get("bTagMinus/Iso/KinFit/"+histname))->Clone("ttbar_bTagDown");   
  ttbar_bTagDown->Scale(scale_factor/ttbar_topPtweight->GetMean());   
  /*
  TH1F* ttbar_ResJESUp = (TH1F*)ttbar->Clone("ttbar_ResJESUp");
  ttbar_ResJESUp->Reset();
  for(int i = 1; i<ttbar->GetNbinsX(); i++){
    ttbar_ResJESUp->SetBinContent(i, ttbar->GetBinContent(i)*(1+h_data_diff->GetBinContent(i)));
  }
  ttbar_ResJESUp->Write("ttbar_ResJESUp");

  TH1F* ttbar_ResJESDown = (TH1F*)ttbar->Clone("ttbar_ResJESDown");
  ttbar_ResJESDown->Reset();
  for(int i = 1; i<ttbar->GetNbinsX(); i++){
    ttbar_ResJESDown->SetBinContent(i, ttbar->GetBinContent(i)*(1-h_data_diff->GetBinContent(i)));
  }
  ttbar_ResJESDown->Write("ttbar_ResJESDown");
  */
    
  /*
  // adding scale up/down systematics
  TH1F* ttbar_scaleup = (fttbar_scaleup->Get("base/"+histname))->Clone("ttbar_scaleup");
  TH1F* ttbar_scaleup_topPtweight = (fttbar_scaleup->Get("base/AvTopPtWeight"))->Clone("ttbar_scaleup_topPtweight");
  //  ttbar_scaleup->Scale(scale_factor/ttbar_scaleup_topPtweight->GetBinContent(2)); // apply avg top pt weight
  ttbar_scaleup->Scale(ttbar->Integral()/ttbar_scaleup->Integral());
  ttbar_scaleup->Write("ttbar_scaleUp");

  TH1F* ttbar_scaledown = (fttbar_scaledown->Get("base/"+histname))->Clone("ttbar_scaledown");
  TH1F* ttbar_scaledown_topPtweight = (fttbar_scaledown->Get("base/AvTopPtWeight"))->Clone("ttbar_scaledown_topPtweight");
  //  ttbar_scaledown->Scale(scale_factor/ttbar_scaledown_topPtweight->GetBinContent(2)); // apply avg top pt weight
  ttbar_scaledown->Scale(ttbar->Integral()/ttbar_scaledown->Integral());
  ttbar_scaledown->Write("ttbar_scaleDown");

  // adding matching up/down systematics
  TH1F* ttbar_matchingup = (fttbar_matchingup->Get("base/"+histname))->Clone("ttbar_matchingup");
  TH1F* ttbar_matchingup_topPtweight = (fttbar_matchingup->Get("base/AvTopPtWeight"))->Clone("ttbar_matchingup_topPtweight");
  //  ttbar_matchingup->Scale(scale_factor/ttbar_matchingup_topPtweight->GetBinContent(2)); // apply avg top pt weight
  ttbar_matchingup->Scale(ttbar->Integral()/ttbar_matchingup->Integral());
  ttbar_matchingup->Write("ttbar_matchingUp");

  TH1F* ttbar_matchingdown = (fttbar_matchingdown->Get("base/"+histname))->Clone("ttbar_matchingdown");
  TH1F* ttbar_matchingdown_topPtweight = (fttbar_matchingdown->Get("base/AvTopPtWeight"))->Clone("ttbar_matchingdown_topPtweight");
  //  ttbar_matchingdown->Scale(scale_factor/ttbar_matchingdown_topPtweight->GetBinContent(2)); // apply avg top pt weight
  ttbar_matchingdown->Scale(ttbar->Integral()/ttbar_matchingdown->Integral());
  ttbar_matchingdown->Write("ttbar_matchingDown");
  */
  
  TH1F* ttll = (TH1F*)ttbar->Clone("ttll"); 
  ttll->Scale(0);
  //ttll->Scale(scale_factor); 
  ttll->Write(); 
  TH1F* ttll_JESUp = (TH1F*)ttbar_JESUp->Clone("ttll_JESUp");  
  ttll_JESUp->Scale(0);
  //ttll_JESUp->Scale(scale_factor);  
  ttll_JESUp->Write(); 
  TH1F* ttll_JESDown = (TH1F*)ttbar_JESDown->Clone("ttll_JESDown");   
  ttll_JESDown->Scale(0);
  //ttll_JESDown->Scale(scale_factor);   
  ttll_JESDown->Write(); 

  ////////////
  // W+Jets
  ///////////
  
  TFile* fwjet = TFile::Open(inputFilePath+"all_WJets.root", "READ"); 
  if(fwjet == 0) return; 
  if(fwjet->IsZombie()){fwjet->Close(); return;} 

  fout->cd();
  TH1F* wjet = (TH1F*)(fwjet->Get("base/Iso/KinFit/"+histname))->Clone("wjet"); 
  wjet->Scale(scale_factor); 
  wjet->Write(); 
  // JES shape
  TH1F* wjet_JESUp = (TH1F*)(fwjet->Get("JESPlus/Iso/KinFit/"+histname))->Clone("wjet_JESUp");  
  wjet_JESUp->Scale(scale_factor);  
  wjet_JESUp->Write(); 
  TH1F* wjet_JESDown = (TH1F*)(fwjet->Get("JESMinus/Iso/KinFit/"+histname))->Clone("wjet_JESDown");   
  wjet_JESDown->Scale(scale_factor);   
  wjet_JESDown->Write();
  // JER shape
  TH1F* wjet_JERUp = (TH1F*)(fwjet->Get("JERPlus/Iso/KinFit/"+histname))->Clone("wjet_JERUp");
  wjet_JERUp->Scale(scale_factor);
  wjet_JERUp->Write();
  TH1F* wjet_JERDown = (TH1F*)(fwjet->Get("JERMinus/Iso/KinFit/"+histname))->Clone("wjet_JERDown");
  wjet_JERDown->Scale(scale_factor);
  wjet_JERDown->Write();

  TH1F* wjet_bTagUp = (TH1F*)(fwjet->Get("bTagPlus/Iso/KinFit/"+histname))->Clone("wjet_bTagUp");   
  wjet_bTagUp->Scale(scale_factor);   
  TH1F* wjet_bTagDown = (TH1F*)(fwjet->Get("bTagMinus/Iso/KinFit/"+histname))->Clone("wjet_bTagDown");    
  wjet_bTagDown->Scale(scale_factor);
  
  /*
  TH1F* wjet_ResJESUp = (TH1F*)wjet->Clone("wjet_ResJESUp");
  wjet_ResJESUp->Reset();
  for(int i = 1; i< wjet->GetNbinsX(); i++){
    wjet_ResJESUp->SetBinContent(i, wjet->GetBinContent(i)*(1+h_data_diff->GetBinContent(i)));
  }
  wjet_ResJESUp->Write("wjet_ResJESUp");

  TH1F* wjet_ResJESDown = (TH1F*)wjet->Clone("wjet_ResJESDown");
  wjet_ResJESDown->Reset();
  for(int i = 1; i< wjet->GetNbinsX(); i++){
    wjet_ResJESDown->SetBinContent(i, wjet->GetBinContent(i)*(1-h_data_diff->GetBinContent(i)));
  }
  wjet_ResJESDown->Write("wjet_ResJESDown");
  */

  ////////////
  // Z+Jets
  ///////////
  
  TFile* fzjet = TFile::Open(inputFilePath+"all_DY.root", "READ"); 
  if(fzjet == 0) return; 
  if(fzjet->IsZombie()){fzjet->Close(); return;} 

  fout->cd();
  TH1F* zjet = (TH1F*)(fzjet->Get("base/Iso/KinFit/"+histname))->Clone("zjet"); 
  zjet->Scale(scale_factor); 
  zjet->Write();
  // JES shape
  TH1F* zjet_JESUp = (TH1F*)(fzjet->Get("JESPlus/Iso/KinFit/"+histname))->Clone("zjet_JESUp");  
  zjet_JESUp->Scale(scale_factor);  
  zjet_JESUp->Write(); 
  TH1F* zjet_JESDown = (TH1F*)(fzjet->Get("JESMinus/Iso/KinFit/"+histname))->Clone("zjet_JESDown");   
  zjet_JESDown->Scale(scale_factor);
  
  // carefull
  /*
  if(zjet_JESDown->Integral()<=0){
    zjet_JESDown->Add(zjet, 0.01/zjet->Integral());
  }
  */
  zjet_JESDown->Write();
  // JER shape
  TH1F* zjet_JERUp = (TH1F*)(fzjet->Get("JERPlus/Iso/KinFit/"+histname))->Clone("zjet_JERUp");
  zjet_JERUp->Scale(scale_factor);
  zjet_JERUp->Write();
  TH1F* zjet_JERDown = (TH1F*)(fzjet->Get("JERMinus/Iso/KinFit/"+histname))->Clone("zjet_JERDown");
  zjet_JERDown->Scale(scale_factor);
  zjet_JERDown->Write();

  TH1F* zjet_bTagUp = (TH1F*)(fzjet->Get("bTagPlus/Iso/KinFit/"+histname))->Clone("zjet_bTagUp");   
  zjet_bTagUp->Scale(scale_factor);   
  TH1F* zjet_bTagDown = (TH1F*)(fzjet->Get("bTagMinus/Iso/KinFit/"+histname))->Clone("zjet_bTagDown");    
  zjet_bTagDown->Scale(scale_factor);    
  /*
  TH1F* zjet_ResJESUp = (TH1F*)zjet->Clone("zjet_ResJESUp");
  zjet_ResJESUp->Reset();
  for(int i = 1; i< zjet->GetNbinsX(); i++){
    zjet_ResJESUp->SetBinContent(i, zjet->GetBinContent(i)*(1+h_data_diff->GetBinContent(i)));
  }
  zjet_ResJESUp->Write("zjet_ResJESUp");

  TH1F* zjet_ResJESDown = (TH1F*)zjet->Clone("zjet_ResJESDown");
  zjet_ResJESDown->Reset();
  for(int i = 1; i< zjet->GetNbinsX(); i++){
    zjet_ResJESDown->SetBinContent(i, zjet->GetBinContent(i)*(1-h_data_diff->GetBinContent(i)));
  }
  zjet_ResJESDown->Write("zjet_ResJESDown");
  */

  ////////////
  // SingleTop
  ///////////

  TFile* fstop = TFile::Open(inputFilePath+"all_ST.root", "READ"); 
  if(fstop == 0) return; 
  if(fstop->IsZombie()){fstop->Close(); return;} 
 
  fout->cd();
  TH1F* stop = (TH1F*)(fstop->Get("base/Iso/KinFit/"+histname))->Clone("stop"); 
  stop->Scale(scale_factor); 
  stop->Write();
  // JES shape
  TH1F* stop_JESUp = (TH1F*)(fstop->Get("JESPlus/Iso/KinFit/"+histname))->Clone("stop_JESUp");  
  stop_JESUp->Scale(scale_factor);  
  stop_JESUp->Write(); 
  TH1F* stop_JESDown = (TH1F*)(fstop->Get("JESMinus/Iso/KinFit/"+histname))->Clone("stop_JESDown");   
  stop_JESDown->Scale(scale_factor);   
  stop_JESDown->Write(); 
  // JER shape
  TH1F* stop_JERUp = (TH1F*)(fstop->Get("JERPlus/Iso/KinFit/"+histname))->Clone("stop_JERUp");
  stop_JERUp->Scale(scale_factor);
  stop_JERUp->Write();
  TH1F* stop_JERDown = (TH1F*)(fstop->Get("JERMinus/Iso/KinFit/"+histname))->Clone("stop_JERDown");
  stop_JERDown->Scale(scale_factor);
  stop_JERDown->Write();

  TH1F* stop_bTagUp = (TH1F*)(fstop->Get("bTagPlus/Iso/KinFit/"+histname))->Clone("stop_bTagUp");   
  stop_bTagUp->Scale(scale_factor);   
  TH1F* stop_bTagDown = (TH1F*)(fstop->Get("bTagMinus/Iso/KinFit/"+histname))->Clone("stop_bTagDown");    
  stop_bTagDown->Scale(scale_factor);    

  /*
  TH1F* stop_ResJESUp = (TH1F*)stop->Clone("stop_ResJESUp");
  stop_ResJESUp->Reset();
  for(int i = 1; i< stop->GetNbinsX(); i++){
    stop_ResJESUp->SetBinContent(i, stop->GetBinContent(i)*(1+h_data_diff->GetBinContent(i)));
  }
  stop_ResJESUp->Write("stop_ResJESUp");

  TH1F* stop_ResJESDown = (TH1F*)stop->Clone("stop_ResJESDown");
  stop_ResJESDown->Reset();
  for(int i = 1; i< stop->GetNbinsX(); i++){
    stop_ResJESDown->SetBinContent(i, stop->GetBinContent(i)*(1-h_data_diff->GetBinContent(i)));
  }
  stop_ResJESDown->Write("stop_ResJESDown");
  */

  ////////////
  // Dibosons
  ///////////
  
  TFile* fdiboson = TFile::Open(inputFilePath+"all_VV.root", "READ"); 
  if(fdiboson == 0) return; 
  if(fdiboson->IsZombie()){fdiboson->Close(); return;} 

  fout->cd();
  TH1F* diboson = (TH1F*)(fdiboson->Get("base/Iso/KinFit/"+histname))->Clone("diboson"); 
  diboson->Scale(scale_factor); 
  diboson->Write(); 
  // JES shape
  TH1F* diboson_JESUp = (TH1F*)(fdiboson->Get("JESPlus/Iso/KinFit/"+histname))->Clone("diboson_JESUp");  
  diboson_JESUp->Scale(scale_factor);  
  diboson_JESUp->Write(); 
  TH1F* diboson_JESDown = (TH1F*)(fdiboson->Get("JESMinus/Iso/KinFit/"+histname))->Clone("diboson_JESDown");   
  diboson_JESDown->Scale(scale_factor);   
  diboson_JESDown->Write(); 
  // JER shape
  TH1F* diboson_JERUp = (TH1F*)(fdiboson->Get("JERPlus/Iso/KinFit/"+histname))->Clone("diboson_JERUp");
  diboson_JERUp->Scale(scale_factor);
  diboson_JERUp->Write();
  TH1F* diboson_JERDown = (TH1F*)(fdiboson->Get("JERMinus/Iso/KinFit/"+histname))->Clone("diboson_JERDown");
  diboson_JERDown->Scale(scale_factor);
  diboson_JERDown->Write();

  TH1F* diboson_bTagUp = (TH1F*)(fdiboson->Get("bTagPlus/Iso/KinFit/"+histname))->Clone("diboson_bTagUp");   
  diboson_bTagUp->Scale(scale_factor);   
  TH1F* diboson_bTagDown = (TH1F*)(fdiboson->Get("bTagMinus/Iso/KinFit/"+histname))->Clone("diboson_bTagDown");    
  diboson_bTagDown->Scale(scale_factor);    
  
  /*
  TH1F* diboson_ResJESUp = (TH1F*)diboson->Clone("diboson_ResJESUp");
  diboson_ResJESUp->Reset();
  for(int i = 1; i< diboson->GetNbinsX(); i++){
    diboson_ResJESUp->SetBinContent(i, diboson->GetBinContent(i)*(1+h_data_diff->GetBinContent(i)));
  }
  diboson_ResJESUp->Write("diboson_ResJESUp");

  TH1F* diboson_ResJESDown = (TH1F*)diboson->Clone("diboson_ResJESDown");
  diboson_ResJESDown->Reset();
  for(int i = 1; i< diboson->GetNbinsX(); i++){
    diboson_ResJESDown->SetBinContent(i, diboson->GetBinContent(i)*(1-h_data_diff->GetBinContent(i)));
  }
  diboson_ResJESDown->Write("diboson_ResJESDown");
  */
  
  ////////////
  // QCD (FIXME with data-driven)
  ///////////

  TFile* fqcd = TFile::Open(inputFilePath+"all_QCD.root", "READ"); 
  if(fqcd == 0) return; 
  if(fqcd->IsZombie()){fqcd->Close(); return;} 
 
  fout->cd();
  //// ---------- Edited this part ------------------
  //TFile* fqcd_dataDriven = TFile::Open(inputFilePath+"all_QCD_dd.root", "READ"); 
  TFile* fqcd_dataDriven = new TFile(inputFilePath+"all_QCD_dd.root"); 
  if(fqcd == 0) return; 
  if(fqcd->IsZombie()){fqcd->Close(); return;} 
  TH1F* qcd = (TH1F*)(fqcd_dataDriven->Get("QCD_from_Data"))->Clone("qcd");
  ///// ----------------------------------------------
  
  qcd->Scale(scale_factor); 
  qcd->Write();
  // JES shape
  TH1F* qcd_JESUp = (TH1F*)(fqcd->Get("JESPlus/Iso/KinFit/"+histname))->Clone("qcd_JESUp");  
  qcd_JESUp->Scale(scale_factor);  
  qcd_JESUp->Write(); 
  TH1F* qcd_JESDown = (TH1F*)(fqcd->Get("JESMinus/Iso/KinFit/"+histname))->Clone("qcd_JESDown");   
  qcd_JESDown->Scale(scale_factor);   
  qcd_JESDown->Write(); 
  // JER shape
  TH1F* qcd_JERUp = (TH1F*)(fqcd->Get("JERPlus/Iso/KinFit/"+histname))->Clone("qcd_JERUp");
  qcd_JERUp->Scale(scale_factor);
  qcd_JERUp->Write();
  TH1F* qcd_JERDown = (TH1F*)(fqcd->Get("JERMinus/Iso/KinFit/"+histname))->Clone("qcd_JERDown");
  qcd_JERDown->Scale(scale_factor);
  qcd_JERDown->Write();

  TH1F* qcd_bTagUp = (TH1F*)(fqcd->Get("bTagPlus/Iso/KinFit/"+histname))->Clone("qcd_bTagUp");   
  qcd_bTagUp->Scale(scale_factor);   
  TH1F* qcd_bTagDown = (TH1F*)(fqcd->Get("bTagMinus/Iso/KinFit/"+histname))->Clone("qcd_bTagDown");    
  qcd_bTagDown->Scale(scale_factor);    
  
  /*
  TH1F* qcd_ResJESUp = (TH1F*)qcd->Clone("qcd_ResJESUp");
  qcd_ResJESUp->Reset();
  for(int i = 1; i< qcd->GetNbinsX(); i++){
    qcd_ResJESUp->SetBinContent(i, qcd->GetBinContent(i)*(1+h_data_diff->GetBinContent(i)));
  }
  qcd_ResJESUp->Write("qcd_ResJESUp");

  TH1F* qcd_ResJESDown = (TH1F*)qcd->Clone("qcd_ResJESDown");
  qcd_ResJESDown->Reset();
  for(int i = 1; i< qcd->GetNbinsX(); i++){
    qcd_ResJESDown->SetBinContent(i, qcd->GetBinContent(i)*(1-h_data_diff->GetBinContent(i)));
  }
  qcd_ResJESDown->Write("qcd_ResJESDown");
  */
  
  // FIXME
  TFile* fdata = TFile::Open(inputFilePath+"all_muData.root", "READ");;

  /*
  if(lumi_cat.find("lumiA")!=string::npos) TFile* fdata = TFile::Open(inputFilePath+"data_2012A_ele_selection.root", "READ");
  else if(lumi_cat.find("lumiB")!=string::npos) TFile* fdata = TFile::Open(inputFilePath+"data_2012B_ele_selection.root", "READ");
  else if(lumi_cat.find("lumiC")!=string::npos) TFile* fdata = TFile::Open(inputFilePath+"data_2012C_ele_selection.root", "READ");
  else if(lumi_cat.find("lumiD")!=string::npos) TFile* fdata = TFile::Open(inputFilePath+"data_2012D_ele_selection.root", "READ");
  else  TFile* fdata = TFile::Open(inputFilePath+"all_muData.root", "READ");
  */
  
  if(fdata == 0) return;
  if(fdata->IsZombie()){fdata->Close(); return;}
  fout->cd();
  TH1F* data_obs = (TH1F*)(fdata->Get("base/Iso/KinFit/"+histname))->Clone("data_obs");
  data_obs->Write("data_obs");

  /*  
  fout->cd();
  TH1F* data_obs = (TH1F*)ttbar->Clone("data_obs");
  data_obs->Reset();
  data_obs->Add(ttbar);
  data_obs->Add(wjet);
  data_obs->Add(zjet);
  data_obs->Add(stop);
  data_obs->Add(diboson);
  data_obs->Write("data_obs");
  */

  vector<int>massPoints;
  massPoints.push_back(80);
  massPoints.push_back(90);
  massPoints.push_back(100);
  massPoints.push_back(120);
  massPoints.push_back(140);
  massPoints.push_back(150);
  massPoints.push_back(155);
  massPoints.push_back(160);

  for(int i = 0; i < massPoints.size(); i++){
    cout<<" mass point "<<massPoints[i]<<endl;
    TFile* fwh = TFile::Open(inputFilePath+Form("all_Hplus%d.root", massPoints[i]), "READ");
    if(fwh == 0) return;
    if(fwh->IsZombie()){fwh->Close(); return;}
 
    fout->cd();
    TH1F* wh = (TH1F*)(fwh->Get("base/Iso/KinFit/"+histname))->Clone(); 
    //    TH1F* wh_temp = (TH1F*)(fwh->Get("base/"+histname))->Clone();
    TH1F* wh_topPtweight = (TH1F*)(fwh->Get("base/SF_topPtWeights"))->Clone(); // get top pt weight in WH
    wh->Scale(scale_factor/wh_topPtweight->GetMean()); // apply avg top pt weight
    wh->SetName(Form("WH%d",massPoints[i]));
    wh->Write(Form("WH%d",massPoints[i])); 
    /*
    TH1F* wh_ResJESUp = (TH1F*)(fwh->Get("base/"+histname))->Clone();
    wh_ResJESUp->Reset();
    for(int ibin = 1; ibin < wh->GetNbinsX(); ibin++){
      wh_ResJESUp->SetBinContent(ibin, wh->GetBinContent(ibin)*(1+h_data_diff->GetBinContent(ibin)));
    }
    wh_ResJESUp->SetName(Form("WH%d_ResJESUp",massPoints[i]));
    wh_ResJESUp->Write(Form("WH%d_ResJESUp",massPoints[i]));

    TH1F* wh_ResJESDown = (TH1F*)wh->Clone("wh_ResJESDown");
    wh_ResJESDown->Reset();
    for(int ibin = 1; ibin<wh->GetNbinsX(); ibin++){
      wh_ResJESDown->SetBinContent(ibin, wh->GetBinContent(ibin)*(1-h_data_diff->GetBinContent(ibin)));
    }
    wh_ResJESDown->SetName(Form("WH%d_ResJESDown",massPoints[i]));
    wh_ResJESDown->Write(Form("WH%d_ResJESDown",massPoints[i]));
    */

    TH1F* wh_JESUp = (TH1F*)(fwh->Get("JESPlus/Iso/KinFit/"+histname))->Clone();  
    wh_JESUp->SetName(Form("WH%d_JESUp",massPoints[i]));
    wh_JESUp->Scale(scale_factor/wh_topPtweight->GetMean());  
    wh_JESUp->Write(Form("WH%d_JESUp",massPoints[i])); 

    TH1F* wh_JESDown = (TH1F*)(fwh->Get("JESMinus/Iso/KinFit/"+histname))->Clone();
    wh_JESDown->SetName(Form("WH%d_JESDown",massPoints[i]));
    wh_JESDown->Scale(scale_factor/wh_topPtweight->GetMean());   
    wh_JESDown->Write(Form("WH%d_JESDown",massPoints[i])); 

    TH1F* wh_JERUp = (TH1F*)(fwh->Get("JERPlus/Iso/KinFit/"+histname))->Clone();
    wh_JERUp->SetName(Form("WH%d_JERUp",massPoints[i]));
    wh_JERUp->Scale(scale_factor/wh_topPtweight->GetMean());
    wh_JERUp->Write(Form("WH%d_JERUp",massPoints[i]));

    TH1F* wh_JERDown = (TH1F*)(fwh->Get("JERMinus/Iso/KinFit/"+histname))->Clone();
    wh_JERDown->SetName(Form("WH%d_JERDown",massPoints[i]));
    wh_JERDown->Scale(scale_factor/wh_topPtweight->GetMean());
    wh_JERDown->Write(Form("WH%d_JERDown",massPoints[i]));
    
    // FIXME
    //// ---------- Edited this part ------------------
    TH1F* wh_topPtUp = (TH1F*)(fwh->Get("TopPtPlus/Iso/KinFit/"+histname))->Clone();
    wh_topPtUp->SetName(Form("WH%d_topPtUp",massPoints[i]));
    TH1F* wh_topPtweightPlus = (TH1F*)(fwh->Get("TopPtPlus/SF_topPtWeights"))->Clone();
    wh_topPtUp->Scale(scale_factor/wh_topPtweightPlus->GetBinContent(2));
    wh_topPtUp->Write(Form("WH%d_topPtUp",massPoints[i]));
    
    TH1F* wh_topPtDown = (TH1F*)(fwh->Get("TopPtMinus/Iso/KinFit/"+histname))->Clone();
    wh_topPtDown->SetName(Form("WH%d_topPtDown",massPoints[i]));
    TH1F* wh_topPtweightMinus = (TH1F*)(fwh->Get("TopPtMinus/SF_topPtWeights"))->Clone();
    wh_topPtDown->Scale(scale_factor/wh_topPtweightMinus->GetBinContent(2));
    wh_topPtDown->Write(Form("WH%d_topPtDown",massPoints[i]));
    //--------------------------------------------------------

    TH1F* wh_bTagUp = (TH1F*)(fwh->Get("bTagPlus/Iso/KinFit/"+histname))->Clone(Form("WH%d_bTagUp",massPoints[i]));   
    wh_bTagUp->Scale(scale_factor/wh_topPtweight->GetMean());   

    TH1F* wh_bTagDown = (TH1F*)(fwh->Get("bTagMinus/Iso/KinFit/"+histname))->Clone(Form("WH%d_bTagDown",massPoints[i])); 
    wh_bTagDown->Scale(scale_factor/wh_topPtweight->GetMean());    
    
    //Temporary arrangement for HH, not fully correct
    double hh_Yield = 0;
    TH1F* hh = (TH1F*)wh->Clone();
    hh->Scale(hh_Yield/hh->Integral());
    hh->SetName(Form("HH%d",massPoints[i])); 
    hh->Write(Form("HH%d",massPoints[i]));  

    /*        
    TH1F* hh_ResJESUp = wh_ResJESUp->Clone();
    hh_ResJESUp->Scale(hh_Yield/hh_ResJESUp->Integral());
    hh_ResJESUp->SetName(Form("HH%d_ResJECUp",massPoints[i]));
    hh_ResJESUp->Write(Form("HH%d_ResJECUp",massPoints[i]));

    TH1F* hh_ResJESDown = wh_ResJESDown->Clone();
    hh_ResJESDown->Scale(hh_Yield/hh_ResJESDown->Integral());
    hh_ResJESDown->SetName(Form("HH%d_ResJECDown",massPoints[i]));
    hh_ResJESDown->Write(Form("HH%d_ResJECDown",massPoints[i]));
    */

    TH1F* hh_JESUp = (TH1F*)wh_JESUp->Clone();
    hh_JESUp->Scale(hh_Yield/hh_JESUp->Integral());
    hh_JESUp->SetName(Form("HH%d_JESUp",massPoints[i])); 
    hh_JESUp->Write(Form("HH%d_JESUp",massPoints[i]));  
    TH1F* hh_JESDown = (TH1F*)wh_JESDown->Clone();
    hh_JESDown->Scale(hh_Yield/hh_JESDown->Integral());
    hh_JESDown->SetName(Form("HH%d_JESDown",massPoints[i])); 
    hh_JESDown->Write(Form("HH%d_JESDown",massPoints[i]));  

    TH1F* hh_JERUp = (TH1F*)wh_JERUp->Clone();
    hh_JERUp->Scale(hh_Yield/hh_JERUp->Integral());
    hh_JERUp->SetName(Form("HH%d_JERUp",massPoints[i]));
    hh_JERUp->Write(Form("HH%d_JERUp",massPoints[i]));
    TH1F* hh_JERDown = (TH1F*)wh_JERDown->Clone();
    hh_JERDown->Scale(hh_Yield/hh_JERDown->Integral());
    hh_JERDown->SetName(Form("HH%d_JERDown",massPoints[i]));
    hh_JERDown->Write(Form("HH%d_JERDown",massPoints[i]));

    // FIXME
    /*
    TH1F* hh_topPtUp = (TH1F*)wh_topPtUp->Clone();
    hh_topPtUp->Scale(hh_Yield/wh_topPtUp->Integral());
    hh_topPtUp->SetName(Form("HH%d_topPtUp",massPoints[i]));
    hh_topPtUp->Write(Form("HH%d_topPtUp",massPoints[i]));

    TH1F* hh_topPtDown = (TH1F*)wh_topPtDown->Clone();
    hh_topPtDown->Scale(hh_Yield/wh_topPtDown->Integral());
    hh_topPtDown->SetName(Form("HH%d_topPtDown",massPoints[i]));
    hh_topPtDown->Write(Form("HH%d_topPtDown",massPoints[i]));
    */

    TH1F* hh_bTagUp = (TH1F*)wh_bTagUp->Clone(Form("HH%d_bTagUp",massPoints[i])); 
    hh_bTagUp->Scale(hh_Yield/hh_bTagUp->Integral()); 
    TH1F* hh_bTagDown = (TH1F*)wh_bTagDown->Clone(Form("HH%d_bTagDown",massPoints[i])); 
    hh_bTagDown->Scale(hh_Yield/hh_bTagDown->Integral()); 

    /*
    //This should be used when files are available
    TFile* fhh = TFile::Open(inputFilePath+Form("hh_M_%d_ele_selection.root", massPoints[i]), "READ"); 
    if(fhh == 0) return; 
    if(fhh->IsZombie()){fhh->Close(); return;} 
    
    fout->cd(); 
    TH1F* hh = (fhh->Get("base/"+histname))->Clone();  
    hh->SetName(Form("HH%d",massPoints[i])); 
    hh->Scale(scale_factor);  
    hh->Write(Form("HH%d",massPoints[i]));  
    TH1F* hh_JESUp = (fhh->Get("JESPlus/"+histname))->Clone();   
    hh_JESUp->SetName(Form("HH%d_JESUp",massPoints[i])); 
    hh_JESUp->Scale(scale_factor);   
    hh_JESUp->Write(Form("HH%d_JESUp",massPoints[i]));  
    TH1F* hh_JESDown = (fhh->Get("JESMinus/"+histname))->Clone(); 
    hh_JESDown->SetName(Form("HH%d_JESDown",massPoints[i])); 
    hh_JESDown->Scale(scale_factor);    
    hh_JESDown->Write(Form("HH%d_JESDown",massPoints[i]));  
    TH1F* hh_bTagUp = (fhh->Get("bTagPlus/"+histname))->Clone(Form("HH%d_bTagUp",massPoints[i]));    
    hh_bTagUp->Scale(scale_factor);    
    TH1F* hh_bTagDown = (fhh->Get("bTagMinus/"+histname))->Clone(Form("HH%d_bTagDown",massPoints[i]));  
    hh_bTagDown->Scale(scale_factor);     
    */

    //Make Data card for each mass
    ifstream in;
    char* c = new char[1000];
    //in.open("template/datacard_csbar.txt");
    if(cat_name.find("cat")!=string::npos)
      in.open(Form("template/datacard_csbar_%s.txt", cat_name.c_str()));
    else in.open("template/datacard_csbar.txt");
    
    ofstream out(Form("datacard_mu_csbar_%s_mH%d.txt", cat_name.c_str(), massPoints[i]));
    out.precision(8);

    time_t secs=time(0);
    tm *t=localtime(&secs);
    while (in.good())
      {
	in.getline(c,1000,'\n');
	if (in.good()){
	  string line(c);
	  if(line.find("Date")!=string::npos){
	    string day = string(Form("%d",t->tm_mday));
	    string month = string(Form("%d",t->tm_mon+1));
	    string year = string(Form("%d",t->tm_year+1900));
	    line.replace( line.find("XXX") , 3 , day+"/"+month+"/"+year);
	    out << line << endl;
	  }
	  else if(line.find("Description")!=string::npos){
	    line.replace( line.find("YYY") , 3 , string(Form("%d", massPoints[i])) );
	    line.replace( line.find("ZZZ") , 3 , string(Form("%f", totLumi)) ); 
	    out << line << endl;
	  }
	  else if(line.find("shapes")!=string::npos){
	    if(cat_name.find("cat")!=string::npos)
	      line.replace( line.find("XXX") , 3 , string(Form("HplusShapes_%s", cat_name.c_str()))  );
	    else
	      line.replace( line.find("XXX") , 3 , string("HplusShapes")  );
	    out << line << endl;
	  }
	  else if(line.find("Observation")!=string::npos){
	    line.replace( line.find("XXX") , 3 , string(Form("%.0f", data_obs->Integral()) )  );
	    out << line << endl;
	  }
	  else if(line.find("process")!=string::npos && line.find("WH")!=string::npos){
	    line.replace( line.find("XXX") , 3 , string(Form("%d", massPoints[i])) );
	    line.replace( line.find("YYY") , 3 , string(Form("%d", massPoints[i])) );
	    out << line << endl;
	  }
	  else if(line.find("rate")!=string::npos){
	    string rate = "rate               ";  
	    string space = "     ";
	    out << rate ;
	    out << space << hh->Integral()
		<< space << wh->Integral()
		<< space << ttbar->Integral()
		<< space << ttll->Integral()
		<< space << wjet->Integral()
		<< space << zjet->Integral()
		<< space << stop->Integral()
		<< space << diboson->Integral()
		<< space << qcd->Integral()
	        << endl;
	    //	<< space << "Projected event rates"<<endl;
	  }
	  else if(line.find("CMS_eff_b")!=string::npos){
	    float bTagUnc_hh = (hh->Integral() > 0) ? 1 + (max(fabs(hh_bTagUp->Integral() - hh->Integral()), fabs(hh->Integral() - hh_bTagDown->Integral()))/hh->Integral()) : 1.00;
	    line.replace( line.find("XXXX") , 4 , string(Form("%.2f", bTagUnc_hh)) );
	    	    
	    float bTagUnc_wh = (wh->Integral() > 0) ? 1 + (max(fabs(wh_bTagUp->Integral() - wh->Integral()), fabs(wh->Integral() - wh_bTagDown->Integral()))/wh->Integral()) : 1.00; 
            line.replace( line.find("YYYY") , 4 , string(Form("%.2f", bTagUnc_wh)) ); 

	    float bTagUnc_ttbar = (ttbar->Integral() > 0) ? 1 + (max(fabs(ttbar_bTagUp->Integral() - ttbar->Integral()), fabs(ttbar->Integral() - ttbar_bTagDown->Integral()))/ttbar->Integral()) : 1.00; 
            line.replace( line.find("ZZZZ") , 4 , string(Form("%.2f", bTagUnc_ttbar)) ); 

	    float bTagUnc_stop = (stop->Integral() > 0) ? 1 + (max(fabs(stop_bTagUp->Integral() - stop->Integral()), fabs(stop->Integral() - stop_bTagDown->Integral()))/stop->Integral()) : 1.00; 
            line.replace( line.find("KKKK") , 4 , string(Form("%.2f", bTagUnc_stop)) ); 

	    out << line << endl;
	  }
	  else if(line.find("CMS_mistag_b")!=string::npos){
	    float bTagUnc_wjet = (wjet->Integral() > 0) ? 1 + (max(fabs(wjet_bTagUp->Integral() - wjet->Integral()), fabs(wjet->Integral() - wjet_bTagDown->Integral()))/wjet->Integral()) : 1.00; 
            line.replace( line.find("XXXX") , 4 , string(Form("%.2f", bTagUnc_wjet)) ); 

	    float bTagUnc_zjet = (zjet->Integral() > 0) ? 1 + (max(fabs(zjet_bTagUp->Integral() - zjet->Integral()), fabs(zjet->Integral() - zjet_bTagDown->Integral()))/zjet->Integral()) : 1.00; 
            line.replace( line.find("YYYY") , 4 , string(Form("%.2f", bTagUnc_zjet)) ); 

	    float bTagUnc_diboson = (diboson->Integral() > 0) ? 1 + (max(fabs(diboson_bTagUp->Integral() - diboson->Integral()), fabs(diboson->Integral() - diboson_bTagDown->Integral()))/diboson->Integral()) : 1.00; 
            line.replace( line.find("KKKK") , 4 , string(Form("%.2f", bTagUnc_diboson)) ); 

	    out << line << endl;
	  }
	  else if(line.find("CMS_stat_hh")!=string::npos){
	    Double_t sError = 0;
	    Double_t norm = hh->IntegralAndError(1, hh->GetNbinsX(), sError);
	    float statUnc_hh = (norm > 0) ? 1 + (fabs(sError)/norm) : 1.00; 
            line.replace( line.find("XXXX") , 4 , string(Form("%.2f", statUnc_hh)) ); 
	    out << line << endl;
	  }
	  else if(line.find("CMS_stat_wh")!=string::npos){ 
            Double_t sError = 0; 
            Double_t norm = wh->IntegralAndError(1, wh->GetNbinsX(), sError); 
            float statUnc_wh = (norm > 0) ? 1 + (fabs(sError)/norm) : 1.00;  
            line.replace( line.find("XXXX") , 4 , string(Form("%.2f", statUnc_wh)) );  
	    out << line << endl;
          } 
	  else if(line.find("CMS_stat_tt")!=string::npos){  
            Double_t sError = 0;  
            Double_t norm = ttbar->IntegralAndError(1, ttbar->GetNbinsX(), sError);  
            float statUnc_ttbar = (norm > 0) ? 1 + (fabs(sError)/norm) : 1.00;   
            line.replace( line.find("XXXX") , 4 , string(Form("%.2f", statUnc_ttbar)) );   
	    out << line << endl;
          }  
	  else if(line.find("CMS_stat_wjet")!=string::npos){  
            Double_t sError = 0;  
            Double_t norm = wjet->IntegralAndError(1, wjet->GetNbinsX(), sError);  
            float statUnc_wjet = (norm > 0) ? 1 + (fabs(sError)/norm) : 1.00;   
            line.replace( line.find("XXXX") , 4 , string(Form("%.2f", statUnc_wjet)) );   
	    out << line << endl;
          }  
	  /*
	  else if(line.find("CMS_stat_zjet")!=string::npos){ 
            Double_t sError = 0; 
            Double_t norm = zjet->IntegralAndError(1, zjet->GetNbinsX(), sError); 
            float statUnc_zjet = (norm > 0) ? 1 + (fabs(sError)/norm) : 1.00;  
            line.replace( line.find("XXXX") , 4 , string(Form("%.2f", statUnc_zjet)) );  
            out << line << endl; 
          } 
	  */
	  else if(line.find("CMS_stat_stop")!=string::npos){ 
            Double_t sError = 0; 
            Double_t norm = stop->IntegralAndError(1, stop->GetNbinsX(), sError); 
            float statUnc_stop = (norm > 0) ? 1 + (fabs(sError)/norm) : 1.00;  
            line.replace( line.find("XXXX") , 4 , string(Form("%.2f", statUnc_stop)) );  
            out << line << endl; 
          } 
	  /*
	  else if(line.find("CMS_stat_vv")!=string::npos){  
            Double_t sError = 0;  
            Double_t norm = diboson->IntegralAndError(1, diboson->GetNbinsX(), sError);  
            float statUnc_diboson = (norm > 0) ? 1 + (fabs(sError)/norm) : 1.00;   
            line.replace( line.find("XXXX") , 4 , string(Form("%.2f", statUnc_diboson)) );   
            out << line << endl;  
          }
	  */
	  else{ //default without changes
	    out << line << endl;
	  }
	}
	else{
	  out << c << endl;
	}
      }
	
    out.close();
    in.close();
  }
  fout->Close();
}
