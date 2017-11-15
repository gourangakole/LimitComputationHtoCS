
  //get average of top pt-reweighting 
  TH1F* hsig_avgTop80 = (TH1F*)wh80->Get("base/SF_topPtWeights"); 
  double sig_avgTop80 = hsig_avgTop80->GetMean();
  double sf80 = 1;
  h_wh80_base->Scale(sf80/sig_avgTop80);
  h_wh80_JESPlus->Scale(sf80/sig_avgTop80);
  h_wh80_JESMinus->Scale(sf80/sig_avgTop80);
  h_wh80_JERPlus->Scale(sf80/sig_avgTop80);
  h_wh80_JERMinus->Scale(sf80/sig_avgTop80);
  h_wh80_METUCPlus->Scale(sf80/sig_avgTop80);
  h_wh80_METUCMinus->Scale(sf80/sig_avgTop80);
  h_wh80_bTagPlus->Scale(sf80/sig_avgTop80);
  h_wh80_bTagMinus->Scale(sf80/sig_avgTop80);


  //get average of top pt-reweighting 
  TH1F* hsig_avgTop90 = (TH1F*)wh90->Get("base/SF_topPtWeights"); 
  double sig_avgTop90 = hsig_avgTop90->GetMean();
  double sf90 = 1;
  h_wh90_base->Scale(sf90/sig_avgTop90);
  h_wh90_JESPlus->Scale(sf90/sig_avgTop90);
  h_wh90_JESMinus->Scale(sf90/sig_avgTop90);
  h_wh90_JERPlus->Scale(sf90/sig_avgTop90);
  h_wh90_JERMinus->Scale(sf90/sig_avgTop90);
  h_wh90_METUCPlus->Scale(sf90/sig_avgTop90);
  h_wh90_METUCMinus->Scale(sf90/sig_avgTop90);
  h_wh90_bTagPlus->Scale(sf90/sig_avgTop90);
  h_wh90_bTagMinus->Scale(sf90/sig_avgTop90);


  //get average of top pt-reweighting 
  TH1F* hsig_avgTop100 = (TH1F*)wh100->Get("base/SF_topPtWeights"); 
  double sig_avgTop100 = hsig_avgTop100->GetMean();
  double sf100 = 1;
  h_wh100_base->Scale(sf100/sig_avgTop100);
  h_wh100_JESPlus->Scale(sf100/sig_avgTop100);
  h_wh100_JESMinus->Scale(sf100/sig_avgTop100);
  h_wh100_JERPlus->Scale(sf100/sig_avgTop100);
  h_wh100_JERMinus->Scale(sf100/sig_avgTop100);
  h_wh100_METUCPlus->Scale(sf100/sig_avgTop100);
  h_wh100_METUCMinus->Scale(sf100/sig_avgTop100);
  h_wh100_bTagPlus->Scale(sf100/sig_avgTop100);
  h_wh100_bTagMinus->Scale(sf100/sig_avgTop100);


  //get average of top pt-reweighting 
  TH1F* hsig_avgTop120 = (TH1F*)wh120->Get("base/SF_topPtWeights"); 
  double sig_avgTop120 = hsig_avgTop120->GetMean();
  double sf120 = 1;
  h_wh120_base->Scale(sf120/sig_avgTop120);
  h_wh120_JESPlus->Scale(sf120/sig_avgTop120);
  h_wh120_JESMinus->Scale(sf120/sig_avgTop120);
  h_wh120_JERPlus->Scale(sf120/sig_avgTop120);
  h_wh120_JERMinus->Scale(sf120/sig_avgTop120);
  h_wh120_METUCPlus->Scale(sf120/sig_avgTop120);
  h_wh120_METUCMinus->Scale(sf120/sig_avgTop120);
  h_wh120_bTagPlus->Scale(sf120/sig_avgTop120);
  h_wh120_bTagMinus->Scale(sf120/sig_avgTop120);



  //get average of top pt-reweighting 
  TH1F* hsig_avgTop140 = (TH1F*)wh140->Get("base/SF_topPtWeights"); 
  double sig_avgTop140 = hsig_avgTop140->GetMean();
  double sf140 = 1;
  h_wh140_base->Scale(sf140/sig_avgTop140);
  h_wh140_JESPlus->Scale(sf140/sig_avgTop140);
  h_wh140_JESMinus->Scale(sf140/sig_avgTop140);
  h_wh140_JERPlus->Scale(sf140/sig_avgTop140);
  h_wh140_JERMinus->Scale(sf140/sig_avgTop140);
  h_wh140_METUCPlus->Scale(sf140/sig_avgTop140);
  h_wh140_METUCMinus->Scale(sf140/sig_avgTop140);
  h_wh140_bTagPlus->Scale(sf140/sig_avgTop140);
  h_wh140_bTagMinus->Scale(sf140/sig_avgTop140);


  //get average of top pt-reweighting 
  TH1F* hsig_avgTop150 = (TH1F*)wh150->Get("base/SF_topPtWeights"); 
  double sig_avgTop150 = hsig_avgTop150->GetMean();
  double sf150 = 1;
  h_wh150_base->Scale(sf150/sig_avgTop150);
  h_wh150_JESPlus->Scale(sf150/sig_avgTop150);
  h_wh150_JESMinus->Scale(sf150/sig_avgTop150);
  h_wh150_JERPlus->Scale(sf150/sig_avgTop150);
  h_wh150_JERMinus->Scale(sf150/sig_avgTop150);
  h_wh150_METUCPlus->Scale(sf150/sig_avgTop150);
  h_wh150_METUCMinus->Scale(sf150/sig_avgTop150);
  h_wh150_bTagPlus->Scale(sf150/sig_avgTop150);
  h_wh150_bTagMinus->Scale(sf150/sig_avgTop150);


  //get average of top pt-reweighting 
  TH1F* hsig_avgTop155 = (TH1F*)wh155->Get("base/SF_topPtWeights"); 
  double sig_avgTop155 = hsig_avgTop155->GetMean();
  double sf155 = 1;
  h_wh155_base->Scale(sf155/sig_avgTop155);
  h_wh155_JESPlus->Scale(sf155/sig_avgTop155);
  h_wh155_JESMinus->Scale(sf155/sig_avgTop155);
  h_wh155_JERPlus->Scale(sf155/sig_avgTop155);
  h_wh155_JERMinus->Scale(sf155/sig_avgTop155);
  h_wh155_METUCPlus->Scale(sf155/sig_avgTop155);
  h_wh155_METUCMinus->Scale(sf155/sig_avgTop155);
  h_wh155_bTagPlus->Scale(sf155/sig_avgTop155);
  h_wh155_bTagMinus->Scale(sf155/sig_avgTop155);


  //get average of top pt-reweighting 
  TH1F* hsig_avgTop160 = (TH1F*)wh160->Get("base/SF_topPtWeights"); 
  double sig_avgTop160 = hsig_avgTop160->GetMean();
  double sf160 = 1;
  h_wh160_base->Scale(sf160/sig_avgTop160);
  h_wh160_JESPlus->Scale(sf160/sig_avgTop160);
  h_wh160_JESMinus->Scale(sf160/sig_avgTop160);
  h_wh160_JERPlus->Scale(sf160/sig_avgTop160);
  h_wh160_JERMinus->Scale(sf160/sig_avgTop160);
  h_wh160_METUCPlus->Scale(sf160/sig_avgTop160);
  h_wh160_METUCMinus->Scale(sf160/sig_avgTop160);
  h_wh160_bTagPlus->Scale(sf160/sig_avgTop160);
  h_wh160_bTagMinus->Scale(sf160/sig_avgTop160);






