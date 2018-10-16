{
  gROOT->ProcessLine(".x initialrootfile.C "); //Creating initial root file
  gROOT->ProcessLine(".x initialcombofit.C"); //Fitting all the histograms
  gROOT->ProcessLine(".x forEtrue_Ecalcdata.C");//Managing data for E true and E calculated
  gROOT->ProcessLine(".x Etrue_vs_Ecalc_macro.C");//Plotting Etrue and Ecalculated
  gROOT->ProcessLine(".x finalcombofit.C");//Fitting all final histograms
  gROOT->ProcessLine(".x resolution.C");//Fitting sigma vs Energy
  
}
