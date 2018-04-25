void DatatoROOT(){
  long int bunch=0;
  long int Nlines=0;
  long int Nbunches=0;
  long int record_tag=0;
  long int bunch_tag=0;
  int trigger=0;
//  long int x[32], y[32];
  long int card1[16],card2[16],card3[16],card4[16];

  string inputFile,inputTitle;
  ifstream dataIn;
  string outputFile;
  TFile *f;
  do{
    cout<<"Please enter the input file's name without postfix(Quit: exit):";
    cin>>inputFile;
    if(inputFile=="exit"){cout<<"exiting"<<endl;return;}
    inputTitle=inputFile+".dat";
    cout<<inputTitle<<endl;
    dataIn.open(inputTitle);
    outputFile=inputFile+".root";
    const char* outputTitle=outputFile.c_str();
    f= new TFile(outputTitle,"recreate");
  }while(!dataIn);

  TTree* T=new TTree("ADCrecord","ADCrecord");
  T->Branch("bunch",&bunch,"bunch/L");
  T->Branch("bunch_tag",&bunch_tag,"bunch_tag/L");
  T->Branch("record_tag",&record_tag,"record_tag/L");
  T->Branch("trigger",&trigger,"trigger/I");
  char temp1[10];
  char temp2[10];
  char temp3[10];
  char temp4[10];
  char a[10];
  char b[10];
  char c[10];
  char d[10];
  char aL[30],bL[30],cL[30],dL[30];
  for(int i=0;i<16;++i){
    strcpy(a,"card1_");
    sprintf(temp1,"%d",i);
	strcat(a,temp1);
	strcpy(aL,a);
	strcat(aL,"/L");
//	cout<<a<<"\t"<<aL<<endl;
	T->Branch(a,&card1[i],aL);
	memset(aL,0,30);
  }
  for(int i=0;i<16;++i){
    strcpy(b,"card2_");
    sprintf(temp2,"%d",i);
	strcat(b,temp2);
	strcpy(bL,b);
	strcat(bL,"/L");
//	cout<<b<<"\t"<<bL<<endl;
	T->Branch(b,&card2[i],bL);
	memset(bL,0,30);
  }
  for(int i=0;i<16;++i){
    strcpy(c,"card3_");
    sprintf(temp3,"%d",i);
	strcat(c,temp3);
	strcpy(cL,c);
	strcat(cL,"/L");
//	cout<<c<<"\t"<<cL<<endl;
	T->Branch(c,&card3[i],cL);
	memset(cL,0,30);
  }
  for(int i=0;i<16;++i){
    strcpy(d,"card4_");
    sprintf(temp4,"%d",i);
	strcat(d,temp4);
	strcpy(dL,d);
	strcat(dL,"/L");
//	cout<<d<<"\t"<<dL<<endl;
	T->Branch(d,&card4[i],dL);
	memset(dL,0,30);
  }
  /**
  T->Branch("x0",&x[0],"x0/L");
  T->Branch("x1",&x[1],"x1/L");
  T->Branch("x2",&x[2],"x2/L");
  T->Branch("x3",&x[3],"x3/L");
  T->Branch("x4",&x[4],"x4/L");
  T->Branch("x5",&x[5],"x5/L");
  T->Branch("x6",&x[6],"x6/L");
  T->Branch("x7",&x[7],"x7/L");
  T->Branch("x8",&x[8],"x8/L");
  T->Branch("x9",&x[9],"x9/L");
  T->Branch("x10",&x[10],"x10/L");
  T->Branch("x11",&x[11],"x11/L");
  T->Branch("x12",&x[12],"x12/L");
  T->Branch("x13",&x[13],"x13/L");
  T->Branch("x14",&x[14],"x14/L");
  T->Branch("x15",&x[15],"x15/L");
  T->Branch("x16",&x[16],"x16/L");
  T->Branch("x17",&x[17],"x17/L");
  T->Branch("x18",&x[18],"x18/L");
  T->Branch("x19",&x[19],"x19/L");
  T->Branch("x20",&x[20],"x20/L");
  T->Branch("x21",&x[21],"x21/L");
  T->Branch("x22",&x[22],"x22/L");
  T->Branch("x23",&x[23],"x23/L");
  T->Branch("x24",&x[24],"x24/L");
  T->Branch("x25",&x[25],"x25/L");
  T->Branch("x26",&x[26],"x26/L");
  T->Branch("x27",&x[27],"x27/L");
  T->Branch("x28",&x[28],"x28/L");
  T->Branch("x29",&x[29],"x29/L");
  T->Branch("x30",&x[30],"x30/L");
  T->Branch("x31",&x[31],"x31/L");
  T->Branch("y0",&y[0],"y0/L");
  T->Branch("y1",&y[1],"y1/L");
  T->Branch("y2",&y[2],"y2/L");
  T->Branch("y3",&y[3],"y3/L");
  T->Branch("y4",&y[4],"y4/L");
  T->Branch("y5",&y[5],"y5/L");
  T->Branch("y6",&y[6],"y6/L");
  T->Branch("y7",&y[7],"y7/L");
  T->Branch("y8",&y[8],"y8/L");
  T->Branch("y9",&y[9],"y9/L");
  T->Branch("y10",&y[10],"y10/L");
  T->Branch("y11",&y[11],"y11/L");
  T->Branch("y12",&y[12],"y12/L");
  T->Branch("y13",&y[13],"y13/L");
  T->Branch("y14",&y[14],"y14/L");
  T->Branch("y15",&y[15],"y15/L");
  T->Branch("y16",&y[16],"y16/L");
  T->Branch("y17",&y[17],"y17/L");
  T->Branch("y18",&y[18],"y18/L");
  T->Branch("y19",&y[19],"y19/L");
  T->Branch("y20",&y[20],"y20/L");
  T->Branch("y21",&y[21],"y21/L");
  T->Branch("y22",&y[22],"y22/L");
  T->Branch("y23",&y[23],"y23/L");
  T->Branch("y24",&y[24],"y24/L");
  T->Branch("y25",&y[25],"y25/L");
  T->Branch("y26",&y[26],"y26/L");
  T->Branch("y27",&y[27],"y27/L");
  T->Branch("y28",&y[28],"y28/L");
  T->Branch("y29",&y[29],"y29/L");
  T->Branch("y30",&y[30],"y30/L");
  T->Branch("y31",&y[31],"y31/L");
  **/

  string line;
  long int adc=0, columns=0;
  vector<long int> record; 
  istringstream iss;
  if(dataIn){
    while(getline(dataIn, line)){
      iss.clear();
      iss.str(line);
      while(iss>>adc){record.push_back(adc);}
      columns=record.size();
      if(columns==3){
		++Nbunches;
		if(Nbunches%100==0) cout<<"Reading bunches: "<<Nbunches<<"\r"<<endl;
        bunch=record[0];
        bunch_tag=record[1];
      }
      else if(columns==66){
        record_tag=record[0];
        trigger=record[1];
        for(int i=0;i<16;++i){
   	    card1[i]=record[2*i+2];
	    card2[i]=record[2*i+3];
	    card3[i]=record[2*i+34];
	    card4[i]=record[2*i+35];
        }  
	    ++Nlines;
	    if(Nbunches>2) T->Fill();	
      }
      record.clear();
    }
    T->BuildIndex("bunch","record_tag");
    cout<<"There are "<<Nlines<<" lines"<<endl;
  }
  else cout<<"No such input file"<<endl;
  f->Write("",TObject::kOverwrite);
  f->Close();
}
