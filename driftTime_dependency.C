#include "TCanvas.h"
#include "string.h"

#if !defined(__CINT__) || defined (__MAKECINT__)
#include "mysignal.h"
#include "mysignal.cxx"
#else
#include "mysignal.cxx+"
#endif

void driftTime_dependency(const int argc=0, const string* argv=nullptr){
  TFile* f=nullptr;
  TTree* t=nullptr;
  if(argc==0) throw runtime_error("ERROR! Please Enter at least two files name as parameters");
  gStyle->SetOptFit(0001);
  TH2D *h1;
  TH2D *h2;
  TH2D *h3;
  TH2D *h4;
  Signal *signal1=0;
  double y1[argc],y2[argc],y3[argc],y4[argc];  
  double e1[argc],e2[argc],e3[argc],e4[argc];  
  double x[argc];
  for(int i=0;i<argc;i++){x[i]=i*100+200;}

  for(int i=0;i<argc;i++){
    string inputFilename="selected_signal_"+argv[i]+".root";
    f=new TFile(inputFilename.c_str());
	t=(TTree*)f->Get("selectedSignal");
	if(!t) throw runtime_error("ERROR! there's no such file or tree in this directory.");
	t->SetBranchAddress("signal",&signal1);
	int entries=t->GetEntries();
	cout<<"Entries: "<<entries<<endl;

	//fill 2D histogram
    h1=new TH2D("h1","card1",16,0,16,50,0,50);
    h2=new TH2D("h2","card2",16,0,16,50,0,50);
    h3=new TH2D("h3","card3",16,0,16,50,0,50);
    h4=new TH2D("h4","card4",16,0,16,50,0,50);

	for(int j=0;j<entries;j++){
	  t->GetEntry(j);
	  if(signal1->cardNum==1){                                                 
	    h1->Fill(signal1->GetGravityCenterX(),((signal1->GetGravityCenterY())-(signal1->triStart)));
	  }
	  else if(signal1->cardNum==2){                                            
	  h2->Fill(signal1->GetGravityCenterX(),((signal1->GetGravityCenterY())-(signal1->triStart)));
	  } 
	  else if(signal1->cardNum==3){                                            
	  h3->Fill(signal1->GetGravityCenterX(),((signal1->GetGravityCenterY())-(signal1->triStart)));
	  }
	  else if(signal1->cardNum==4){
	  h4->Fill(signal1->GetGravityCenterX(),((signal1->GetGravityCenterY())-(signal1->triStart)));
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
	TH1D* p1=h1->ProjectionY("p1",0,-1);
	p1->Fit("gaus","W");
	TF1* fit1=p1->GetFunction("gaus");
	double mean1=fit1->GetParameter(1);
	double sigma1=fit1->GetParameter(2);
	cout<<"1----------------"<<mean1<<"\t"<<sigma1<<"----------------"<<endl;
	y1[i]=mean1;
	e1[i]=sigma1;

	TH1D* p2=h2->ProjectionY("p2",0,-1);
	p2->Fit("gaus","W");
	TF1* fit2=p2->GetFunction("gaus");
	double mean2=fit2->GetParameter(1);
	double sigma2=fit2->GetParameter(2);
	cout<<"2----------------"<<mean2<<"\t"<<sigma2<<"----------------"<<endl;
	y2[i]=mean2;
	e2[i]=sigma2;

	TH1D* p3=h3->ProjectionY("p3",0,-1);
	p3->Fit("gaus","W");
	TF1* fit3=p3->GetFunction("gaus");
	double mean3=fit3->GetParameter(1);
	double sigma3=fit3->GetParameter(2);
	cout<<"3----------------"<<mean3<<"\t"<<sigma3<<"----------------"<<endl;
	y3[i]=mean3;
	e3[i]=sigma3;

	TH1D* p4=h4->ProjectionY("p4",0,-1);
	p4->Fit("gaus","W");
	TF1* fit4=p4->GetFunction("gaus");
	double mean4=fit4->GetParameter(1);
	double sigma4=fit4->GetParameter(2);
	cout<<"4----------------"<<mean4<<"\t"<<sigma4<<"----------------"<<endl;
	y4[i]=mean4;
	e4[i]=sigma4;

	delete h1;
	delete h2;
	delete h3;
	delete h4;
	delete p1;
	delete p2;
	delete p3;
	delete p4;
	/**
	//collect all points
    dataPoints1.push_back()
    dataPoints2.push_back()
    dataPoints3.push_back()
    dataPoints4.push_back()
	**/
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
  gr1->GetXaxis()->SetRangeUser(-0.5,5.5);
  gr1->Draw("AP");
  c1->cd(2);
  TGraphErrors *gr2=new TGraphErrors(argc,x,y2,0,e2);
  gr2->SetMarkerStyle(4);
  gr2->SetMarkerSize(1);
  gr2->SetTitle("stripe2");
  gr2->Fit("pol1");
  gr2->GetYaxis()->SetRangeUser(1,40);
  gr2->GetXaxis()->SetRangeUser(-0.5,5.5);
  gr2->Draw("AP");
  c1->cd(3);
  TGraphErrors *gr3=new TGraphErrors(argc,x,y3,0,e3);
  gr3->SetMarkerStyle(4);
  gr3->SetMarkerSize(1);
  gr3->SetTitle("stripe3");
  gr3->Fit("pol1");
  gr3->GetYaxis()->SetRangeUser(1,40);
  gr3->GetXaxis()->SetRangeUser(-0.5,5.5);
  gr3->Draw("AP");
  c1->cd(4);
  TGraphErrors *gr4=new TGraphErrors(argc,x,y4,0,e4);
  gr4->SetMarkerStyle(4);
  gr4->SetMarkerSize(1);
  gr4->SetTitle("stripe4");
  gr4->Fit("pol1");
  gr4->GetYaxis()->SetRangeUser(1,40);
  gr4->GetXaxis()->SetRangeUser(-0.5,5.5);
  gr4->Draw("AP");
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
