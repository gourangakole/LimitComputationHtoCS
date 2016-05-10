echo  "Calculating combined limit for mH150"
combineCards.py  datacard_ele_csbar_bbb__mH150.txt datacard_mu_csbar_bbb__mH150.txt  > comb_mH150.txt
text2workspace.py comb_mH150.txt -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o comb_mH150.root
combine comb_mH150.root -M Asymptotic --mass 150 --name ChargedHiggs_comb
