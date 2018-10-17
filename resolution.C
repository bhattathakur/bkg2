{
  //Data file containing final errors and parameters
  char  dataafile[]="DATA/bkg2finalEnergyerror.dat";//A,mean,sigma,error in A,error in mean, error in sigma,N
  char pdfresoluton[]="PLOTS/bkg2resolutionplot.pdf"; //pdf file to save the plot
  const   char* finalresults="DATA/bkg2results_from_resolution.dat";//stores the results obtained form the resolution plot
  const  char* savingtoroot="ROOTFILES/bkg2resolution.root";// saves the plot in the root file
  ifstream inputres(dataafile);
  if(inputres.is_open())
    {
	cout<<"successfully opend the file "<<dataafile<<endl;
    }
  else
    {
	cout<<"Unable to open the file "<<dataafile<<endl;
    }
  
  c=new TCanvas();
  c->SetGrid();
  c->SetFillColor(29);
  TGraphErrors *expgraph=new TGraphErrors(dataafile,"%*lg%lg%lg%*lg%lg%lg%*lg","");//A,mean,sigma,error in A,error in mean, error in sigma,N
  expgraph->SetTitle("Energy Resolution plot;E(eV);(#sigma);");
  expgraph->SetMarkerColor(4);
  expgraph->SetMarkerStyle(21);
  expgraph->SetLineColor(9);
  expgraph->SetLineWidth(2);
  expgraph->Draw("AP");
  expgraph->Fit("pol1");
  expgraph->GetFunction("pol1")->SetLineStyle(2);
  expgraph->GetFunction("pol1")->SetParName(0,"Intercept(p_{0})");
  expgraph->GetFunction("pol1")->SetParName(1,"Slope(p_{1})");

  c->GetFrame()->SetFillColor(21);
  c->GetFrame()->SetBorderSize(12);
  gStyle->SetStatX(0.9);
  gStyle->SetStatY(0.92);
  gStyle->SetOptFit();
  c->Update();

  //Legend
  auto leg=new TLegend(0.1,0.8,0.3,0.9);//x1,y1,x2,y2
  leg->AddEntry(expgraph->GetFunction("pol1"),"#sigma=p_{0}+p_{1}E","l");
  leg->AddEntry(expgraph,"Graph with error bars","lep");//line,errorbars,polymarker
  gStyle->SetLegendFont(12);
  gStyle->SetLegendFillColor(7);
  leg->Draw();

  c->SaveAs(pdfresoluton);//Using as the pdf file for the plot
  const int E=1332;
  cout<<fixed<<setprecision(8);
  const double slope=expgraph->GetFunction("pol1")->GetParameter(1);
  const double slope_error=expgraph->GetFunction("pol1")->GetParError(1);
  cout<<"slope = "<<slope<<endl;
  cout<<"slope error = "<<slope_error<<endl;
  const double intercept=expgraph->GetFunction("pol1")->GetParameter(0);
  const double intercept_error=expgraph->GetFunction("pol1")->GetParError(0);
  cout<<"intercept = "<<intercept<<endl;
  cout<<"intercept error = "<<intercept_error<<endl;
  double sig=slope*E+intercept;
  double FWHM=2.355*sig;
  cout<<fixed<<setprecision(3);
  cout<<"Corresponding to E = 1332 keV for (Co-60)): "<<endl;
  cout<<"sigma = "<<sig<<endl;
  cout<<"FWHM  = "<<FWHM<<endl;
  /////////////////////Storing the Error and parameter error in a file////////////////////
  ofstream resolution_error(finalresults);
  if(resolution_error.is_open())
    {
	resolution_error<<setw(12)<<slope<<setw(12)<<slope_error<<setw(12)<<intercept<<setw(12)<<intercept_error<<endl;
	cout<<"Successfully stored the m, dm , b and db in the file "<<finalresults<<endl;
    }
  else cout<<"Unable to open the file "<<finalresults<<endl;
  /* auto legg=new TLegend(0.8,0.2,0.95,0.4);
  legg->AddEntry("#sigma =2.4 ");
  legg->Draw();*/
		     
}
