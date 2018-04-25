#ifdef MYSIGNAL_SECOND_RUN

#include "mysignal.h"
void signalSelection(bool secondRun=true, string argv=""){
  Signal* mySignal=new Signal();
  Signal* signal1=0;

  string inputFile, inputPosfix1;
  TFile* file1;
  TTree* T;
  do{
    if(argv==""){
      cout<<"Please enter the correct input file's name without postfix (Quit: exit): ";
      cin>>argv;
      if(argv=="exit") {cout<<"exiting"<<endl;gApplication->Terminate(0);}
	}
  }while(!T);
	inputFile=argv;
    cout<<inputFile<<endl;
    inputPosfix1=inputFile+".root";
    const char* inputTFile=inputPosfix1.c_str();
    file1=new TFile(inputTFile,"update");
    T=(TTree*)file1->Get("TSignal");
	if(!T) throw runtime_error("WRONG INPUT!");
	T->SetBranchAddress("signal",&signal1);
  int N_entries=T->GetEntries();
  cout<<"total entries: "<<N_entries<<endl;

  string outputFile="selected_"+inputFile+".root";
  const char* outputTFile=outputFile.c_str();
  TFile* file2=new TFile(outputTFile,"recreate");
  TTree* TSignal=new TTree("selectedSignal","selectedSignal");
  TSignal->Branch("signal","Signal",&mySignal,16000,99);

  T->GetEntry(0);
  int event_tag0=signal1->event_tag;
  int cardNum0=signal1->cardNum;
  vector<vector<Signal>> eventSignal;
  vector<Signal> cardSignal;
  cardSignal.push_back(*signal1);
  for(int i=1;i<N_entries;i++){
    T->GetEntry(i);
	if(signal1->event_tag==event_tag0){
	  if(signal1->cardNum==cardNum0){
	    cardSignal.push_back(*signal1);
	  }
	  else{
	    cardNum0=signal1->cardNum;
	    if(cardSignal.size()==1){
		  eventSignal.push_back(cardSignal);
		}
//		vector<Signal*>().swap(cardSignal);
		cardSignal.clear();
		cardSignal.push_back(*signal1);
	  }
	}
	else{
	  if(cardSignal.size()==1)eventSignal.push_back(cardSignal);
	  int Nsignals=eventSignal.size();
	  if(Nsignals>=2){
		cout<<"------"<<"Event: "<<eventSignal[0][0].event_tag<<"------"<<endl;
   	    for(int i=0;i<Nsignals;i++){
	      mySignal=&eventSignal[i][0];
		  cout<<"**"<<mySignal->event_tag<<"\t"<<mySignal->cardNum<<"**"<<endl;
		  TSignal->Fill();
	    }
	  }
//	  vector<vector<Signal*>>().swap(eventSignal);
	  eventSignal.clear();
//	  vector<Signal*>().swap(cardSignal);
	  cardSignal.clear();
	  event_tag0=signal1->event_tag;
	  cardNum0=signal1->cardNum;
      cardSignal.push_back(*signal1);
	}
  }

  TSignal->Write();
  file2->Write("",TObject::kOverwrite);
  file2->Close();
}

#else

void signalSelection(string argv=""){
  gROOT->ProcessLine(".L /home/fengchu/20170621/imptest/mysignal.cxx+");
  gROOT->ProcessLine("#define MYSIGNAL_SECOND_RUN yes");
  gROOT->ProcessLine("#include \"" __FILE__ "\"");
  gROOT->ProcessLine(Form("signalSelection(true,\"%s\")",argv.c_str()));
}

#endif
