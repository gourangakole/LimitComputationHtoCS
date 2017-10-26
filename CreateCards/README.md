# Instructions to create datacards

--> 
Get ROOT-6:
 
root -l -b

.L makeHPlusDataCardWithLumi.C

makeHPlusDataCardWithLumi("mjj_kfit","","")

This will look for the input files in "inputFilePath"
and create "datacards for each higgs mass points" and a shapefile

