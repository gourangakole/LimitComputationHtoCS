echo "processing mH$1 in incl"
echo "combining the two cards "
combineCards.py  datacard_ele_csbar_bbb__mH$1.txt datacard_mu_csbar_bbb__mH$1.txt  > comb_mH$1.txt
echo "t2w"
text2workspace.py -m $1 -P HiggsAnalysis.CombinedLimit.ChargedHiggs:brChargedHiggs comb_mH$1.txt -o comb_mH$1.root -v9 >& t2w_$1_incl.log

echo "MLF"
mkdir -p MLF_$1_incl;
combine -M MaxLikelihoodFit --plots --saveShapes --saveWithUncertainties  --saveNormalizations --initFromBonly  --robustFit 1  -n MLF_$1_incl --setPhysicsModelParameterRanges BR=0.00,0.10 --out MLF_$1_incl comb_mH$1.root 

echo "diffNuis"
python ${CMSSW_BASE}/src/HiggsAnalysis/CombinedLimit/test/diffNuisances.py --all --poi=BR MLF_$1_incl/mlfitMLF_$1_incl.root  -g test3.root > MLF_$1_comb_incl_diffNuis.txt 

