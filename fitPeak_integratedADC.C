#ifdef MYSIGNAL_SECOND_RUN

#include "TCanvas.h"
#include "string.h"
#include "mysignal.h"

void fitPeak_integratedADC(bool secondRun=true, const double lowLimit=0, const double highLimit=2500, string filename=""){
  TFile* f=nullptr;
  TTree* t=nullptr;
//  if(argc==0) throw runtime_error("ERROR! Please Enter at least one file name as parameters");
  gStyle->SetOptFit(0001);
  TH1D *h1;
  TH1D *h2;
  TH1D *h3;
  TH1D *h4;

  Signal *signal1=0;

  h1=new TH1D("h1","strip1",100,lowLimit,highLimit);
  h2=new TH1D("h2","strip2",100,lowLimit,highLimit);
  h3=new TH1D("h3","strip3",100,lowLimit,highLimit);
  h4=new TH1D("h4","strip4",100,lowLimit,highLimit);

 // for(int i=0;i<argc;i++){
   // f=new TFile(argv[i].c_pecialtr());
  TCanvas *c1=new TCanvas("c1","Integrated ADC vs GEM Voltage",1000,800);
  c1->Divide(2,2);

	string inputFilename="selected_signal_"+filename+".root";
    f=new TFile(inputFilename.c_str());
	t=(TTree*)f->Get("selectedSignal");
	if(!t) throw runtime_error("ERROR! there's no such file or tree in this directory.");
	t->SetBranchAddress("signal",&signal1);
	int entries=t->GetEntries();

	for(int j=0;j<entries;j++){
	  t->GetEntry(j);
	  if(signal1->cardNum==1){
	    h1->Fill(signal1->peakIntegral_sigma);
	  }
	  else if(signal1->cardNum==2){
	    h2->Fill(signal1->peakIntegral_sigma);
	  }
	  else if(signal1->cardNum==3){
	    h3->Fill(signal1->peakIntegral_sigma);
	  }
	  else if(signal1->cardNum==4){
	    h4->Fill(signal1->peakIntegral_sigma);
	  }
	}
	/**
	c1->cd(1);
	h1->Draw("colz");
	c1->cd(2);
	h2->Draw("colz");
	c1->cd(3);
	h3->Draw("colz");
	c1->cd(4);
	h4->Draw("colz");
	**/

	//Project 2D histogram to 1D histogram, with only localTime information reserved. Fit 1D
	//histogram with Guass distribution, get mean value and sigma.
	c1->cd(1);
	h1->Fit("gaus","W");
	h1->Draw();
	TF1* fit1=h1->GetFunction("gaus");
	double mean1=fit1->GetParameter(1);
	double sigma1=fit1->GetParameter(2);
	cout<<"1----------------"<<mean1<<"\t"<<sigma1<<"----------------"<<endl;

	c1->cd(2);
	h2->Fit("gaus","W");
	h2->Draw();
	TF1* fit2=h2->GetFunction("gaus");
	double mean2=fit2->GetParameter(1);
	double sigma2=fit2->GetParameter(2);
	cout<<"2----------------"<<mean2<<"\t"<<sigma2<<"----------------"<<endl;

	c1->cd(3);
	h3->Fit("gaus","W");
	h3->Draw();
	TF1* fit3=h3->GetFunction("gaus");
	double mean3=fit3->GetParameter(1);
	double sigma3=fit3->GetParameter(2);
	cout<<"3----------------"<<mean3<<"\t"<<sigma3<<"----------------"<<endl;

	c1->cd(4);
	h4->Fit("gaus","W");
	h4->Draw();
	TF1* fit4=h4->GetFunction("gaus");
	double mean4=fit4->GetParameter(1);
	double sigma4=fit4->GetParameter(2);
	cout<<"4----------------"<<mean4<<"\t"<<sigma4<<"----------------"<<endl;

	/**
	//collect all points
	dataPoints1.push_back()
	dataPoints2.push_back()
	dataPoints3.push_back()
	dataPoints4.push_back()
//	delete f;
  }

  TCanvas *c1=new TCanvas("c1","Drift Time vs. Source Height",1000,800);
  c1->Divide(2,2);

  c1->cd(1);
  TGraphErrors *gr1=new TGraphErrors(argc,x,y1,0,e1);
  gr1->SetMarkerStyle(4);
  gr1->SetMarkerSize(1);
  gr1->SetTitle("stripe1");
  gr1->Fit("pol1");
  gr1->GetYaxis()->SetRangeUser(1,40);
  gr1->Draw("AP");
  c1->cd(2);
  TGraphErrors *gr2=new TGraphErrors(argc,x,y2,0,e2);
  gr2->SetMarkerStyle(4);
  gr2->SetMarkerSize(1);
  gr2->SetTitle("stripe2");
  gr2->Fit("pol1");
  gr2->GetYaxis()->SetRangeUser(1,40);
  gr2->Draw("AP");
  c1->cd(3);
  TGraphErrors *gr3=new TGraphErrors(argc,x,y3,0,e3);
  gr3->SetMarkerStyle(4);
  gr3->SetMarkerSize(1);
  gr3->SetTitle("stripe3");
  gr3->Fit("pol1");
  gr3->GetYaxis()->SetRangeUser(1,40);
  gr3->Draw("AP");
  c1->cd(4);
  TGraphErrors *gr4=new TGraphErrors(argc,x,y4,0,e4);
  gr4->SetMarkerStyle(4);
  gr4->SetMarkerSize(1);
  gr4->SetTitle("stripe4");
  gr4->Fit("pol1");
  gr4->GetYaxis()->SetRangeUser(1,40);
  gr4->Draw("AP");
	**/
  /**
  c1->cd(3);
  gr3->Draw();
  c1->cd(4);
  gr4->Draw();
  **/
  //Draw polylines from collected data points in 4 canvas, representing 4 readout pads respectively.
  /**
  
  **/
}

#else

void fitPeak_integratedADC(const double lowLimit=0, const double highLimit=2500, string filename=""){
  gROOT->ProcessLine(".L mysignal.cxx+");
#define MYSIGNAL_SECOND_RUN yes
  gROOT->ProcessLine("#include \"" __FILE__ "\"");
  gROOT->ProcessLine(Form("fitPeak_integratedADC(true,%f,%f,\"%s\")",lowLimit,highLimit,filename.c_str()));
}

#endif
