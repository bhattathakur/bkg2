{
  //Files for storing data file
  const char * filename="ROOTFILES/bkg2initial.root"; //access the original histogram
  const char * allhistogramsfile="ROOTFILES/initial_allhistogram.root"; //Dave the histogram
  char  file_estimated_parameters[]="DATA/bkg2initialestimates.dat"; //file storing the estimated parameters for fit
  char  outputfile[] ="DATA/bkg2initialEnergyerror.dat";
  char initialcanvaspdf[]="PLOT/bkg2initialcanvas.pdf";
  const  int peakNo=23;
  const  int column=6;
  int row=peakNo/column+1;
  
  //Defining the array to read the paramertes
  double firstParameter[peakNo]={};
  double secondParameter[peakNo]={};
  double thirdParameter[peakNo]={};
  double firstLimit[peakNo]={};
  double secondLimit[peakNo]={};

  //Checking if data file with estimated parameters are opened
  ifstream datafile(file_estimated_parameters); //File containing the estimated fit parameters
  if(datafile.is_open())
	{
	  cout<<" File reading for estimated parameters is done successfully from the file "<<file_estimated_parameters<<endl;
	  int peakCount=0;
	  while(peakCount<=peakNo)
		{
		  datafile>>firstParameter[peakCount]>>secondParameter[peakCount]>>thirdParameter[peakCount]>>firstLimit[peakCount]>>secondLimit[peakCount];
		  peakCount++;
		}
	  datafile.close();
	}
  else
	{
	  cout<<"Error in reading the file"<<file_estimated_parameters<<"  for estimated paramters"<<endl;
	  return 0;
	}

  //Creating the canvas and rootfile to store different histograms 
  TCanvas *c1 = new TCanvas("c1","Histogram",500,700);
  c1->SetGrid();
  c1->Divide(column,row);
  TFile *filee=new TFile(allhistogramsfile,"RECREATE");
  //checking if Tfile is opened scuccessfully
  if(filee->IsOpen())cout<<"Successfully created a file "<<allhistogramsfile<< " to store all histograms with fit"<<endl;
  else
    {
	cout<<"Unable to open the file "<<allhistogramsfile<< endl;
	return 0;
    }
  //array for histogram and functions
  TF1 * f[peakNo];
  TH1F * h[peakNo];

  //Checking if TFiles is opened successfully
  TFile *MyFile = new TFile(filename,"READ");
  if(MyFile->IsOpen())cout<<filename<<" file opened successfully\n";
  TH1F *his = (TH1F*)MyFile->Get("histo"); //histo is the name of histogram stored in MyFile
  
  for(int i=0;i<peakNo;i++)
    {
      f[i]=new TF1(Form("f%d",i),"[0]*TMath::Gaus(x,[1],[2],1)+pol0(3)*(x<[1])+pol0(4)*(x>=[1])");
      f[i]->SetParNames("A","#mu","#sigma","a1","b1");
      f[i]->SetParameters(firstParameter[i],secondParameter[i],thirdParameter[i],0,0);
	cout<<endl;
	cout<<"########################  Peak "<<(i+1)<<"  #########################     "<<endl;
	cout<<endl;
      c1->cd(i+1);
	h[i]=(TH1F*)his->Clone(Form("h%d",i+1));
      h[i]->GetXaxis()->SetTitle("Energy(keV)");
      h[i]->GetXaxis()->CenterTitle();
      h[i]->GetYaxis()->SetTitle("Counts/Channel");
      h[i]->GetYaxis()->CenterTitle();
      h[i]->Fit(f[i],"rem+","",firstLimit[i],secondLimit[i]);
	gStyle->SetOptStat("n");//Name of histogram
	h[i]->Draw();
   	h[i]->Sumw2();
	TPaveStats* stat =(TPaveStats*)h[i]->FindObject("stats");
	stat->SetOptFit(1111);
	// Set stat options
	gStyle->SetStatY(0.9);                
	// Set y-position (fraction of pad size)
	gStyle->SetStatX(0.9);                
	// Set x-position (fraction of pad size)
	gStyle->SetStatW(0.2);                
	// Set width of stat-box (fraction of pad size)
	gStyle->SetStatH(0.4);                
	// Set height of stat-box (fraction of pad size)
	c1->Update();
	c1->Modified();
     	filee->cd();
	//c->SaveAs(initialcanvaspdf);
	h[i]->Write();
    }
  
  // filename.close();
  //delete filename;
  ///////%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%/////////////////////////////////////

  
 ofstream myfile(outputfile);
 const double binWidth=his->GetBinWidth(1);
 if(myfile.is_open())
 {
   cout<<"Creating the file with A,eA,u,eu,6,e6,N"<<endl;
  myfile<<fixed<<setprecision(2);
     for(int i=0;i<peakNo;i++)
       {
         myfile<<setw(10)<< f[i]->GetParameter(0)<<setw(12)<<f[i]->GetParameter(1)<<setw(12)<<f[i]->GetParameter(2)<<setw(12)<<f[i]->GetParError(0)
			   <<setw(12)<<f[i]->GetParError(1)<<setw(12)<<f[i]->GetParError(2)<<setw(12)<<f[i]->GetParameter(0)/binWidth<<endl;
       }
     cout<<"successfully stored output data in the file "<<outputfile<<endl;
     myfile.close();
 }
 else cout<<"unable to open the file "<<outputfile <<endl;
 //Closing the root file
 //xdelete  filename;
 // filename.close();
 delete  MyFile;
 }
