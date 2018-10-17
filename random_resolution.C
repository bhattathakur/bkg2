{
  const char * errors_fromresolution="DATA/bkg2results_from_resolution.dat";
  const char * saving_random="PLOT/bkg2randompd.pdf";

  const int ENERGY=1332;
  const int TRIALS=pow(10,6);
  double m,dm,b,db;

  //Creating the canvas
  TCanvas *can=new TCanvas();

  //Defining the histogram to will with random numbers
  TH1F *  ranhis=new TH1F("ranhis","Histogram filled with Random resolution values",TRIALS/25,0.94,1.1);

  //Checking if the input file is open
  ifstream inputfromran(errors_fromresolution);
  if(inputfromran.is_open())
    {
	cout<<"Successfully opened "<< errors_fromresolution<<endl;

	//Reading the histogram
	while(1)
	  {
	    inputfromran>>m>>dm>>b>>db;
	    if(!inputfromran.good())break;
	  }
	  
	for(int i=0;i<TRIALS;i++)
	  {
	    double random_slope=gRandom->Gaus(m,dm);
	    cout<<random_slope<<endl;
	    double random_intercept=gRandom->Gaus(b,db);
	    cout<<random_intercept<<endl;
	    double random_sigma=random_slope*ENERGY+random_intercept;
	    cout<< random_sigma<<endl;
	    ranhis->Fill(random_sigma);
	    
	  }
	ranhis->GetXaxis()->SetTitle("#sigma=m_{random}#times1332+b_{random}");
	ranhis->GetYaxis()->SetTitle("Counts");
	ranhis->Draw();
	ranhis->Fit("gaus");
	gStyle->SetOptFit(1111);
	can->Update();
	
	
    }
  else
    {
	cout<<"Unable to open "<<errors_fromresolution<<endl;
	return 0;
    }
}
