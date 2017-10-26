echo  "Calculating limit for mH$1"
#combineCards.py  datacard_ele_csbar_bbb__mH150.txt datacard_mu_csbar_bbb__mH150.txt  > comb_mH150.txt
text2workspace.py datacard_mu_csbar__mH$1.txt -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs -o comb_mH$1.root
combine comb_mH$1.root -M Asymptotic --mass $1 --name ChargedHiggs_mu
