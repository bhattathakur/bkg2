{
  //Data File contaiing estimated energy and true energy
  const char * input1="DATA/bkg2initialEnergyerror.dat"; //estimated energy from the fit parameters
  const  char * input2="DATA/tabulated_energy.dat"; //true energy calculated from nudat2
  const char * output="DATA/bkg2E_estandE_true.dat";//storing the data manipulated from input1 and input2
  ifstream file1(input1);
  ifstream file2(input2);
  if(file1.is_open())
    {
	cout<<input1<< " successfully opened"<<endl;
    }
  else
    {
	cout<<"failed to open"<< input1<<endl;
	return 0;
    }
  if(file2.is_open())
    {
	cout<<input2<< " successfully opened"<<endl;
    }
  else
    {
	cout<<"failed to open"<< input2<<endl;
	return 0;
    }
  double amplitude,mean,sigma,errorAmp,errorMean,errorSigma,N;  //input1
  double trueE,errorE; //input2
  //Open file to store the required data:
  ofstream file3(output);
  if(file3.is_open())
    {
	while(1)
	  {
	    file1>>amplitude>>mean>>sigma>>errorAmp>>errorMean>>errorSigma>>N;
	    file2>>trueE>>errorE;
	    if(!file1.good()|| !file2.good())break;
	    // cout<<setw(10)<<mean<<setw(10)<<trueE<<setw(10)<<errorMean<<setw(10)<<errorE<<endl;
	    file3<<setw(10)<<mean<<setw(10)<<trueE<<setw(10)<<errorMean<<setw(10)<<errorE<<endl;
	  }
	cout<<"successfully stored the E-Calc,E-true and erros in the file "<<output<<endl;
    }
  else
    {
	cout<<"Unable to open file "<<output<<endl;
	return 0;
    }
}
