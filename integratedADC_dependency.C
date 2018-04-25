#include "TCanvas.h"
#include "string.h"
#include "mysignal.h"
#include "mysignal.cxx"

/**
void GetLimits(TH1D* h1, double& lowLimit, double& highLimit){
  const int expPeaks=1;
  const int expSigma=1;
  const double threshold=0.2;
  int binNum=h1->GetNbinsX();
  double source[binNum],dest[binNum];
  for(int i=0;i<binNum;i++) source[i]=h1->GetBinContent(i+1);
  TSpectrum* s1=new TSpectrum(expPeaks);
  int nPeaks=s1->SearchHighRes(source,dest,binNum,expSigma,threshold,false,3,false,10);
  double* xPeaks=s1->GetPositionX();
}
**/

void integratedADC_dependency(const int argc=0,const string* argv=nullptr){
  TFile* f=nullptr;
  TTree* t=nullptr;
  if(argc==0) throw runtime_error("ERROR! Please Enter at least one file name as parameters");
  gStyle->SetOptFit(0001);
  TH1D *h1;
  TH1D *h2;
  TH1D *h3;
  TH1D *h4;

  Signal *signal1=0;
  const int nPoints=argc;
  double y1[nPoints],y2[nPoints],y3[nPoints],y4[nPoints];  
  double e1[nPoints],e2[nPoints],e3[nPoints],e4[nPoints];  
  //ATTENTION! User should set their own x coordinates
  double x[]={2,2.5,3,1.8};

  for(int i=0;i<nPoints;i++){
    string inputFilename="selected_signal_"+argv[i]+".root";
    f=new TFile(inputFilename.c_str());
	t=(TTree*)f->Get("selectedSignal");
	if(!t) throw runtime_error("ERROR! there's no such file or tree in this directory.");
	t->SetBranchAddress("signal",&signal1);
	int entries=t->GetEntries();
	cout<<"Entries: "<<entries<<endl;
	
	t->GetEntry(0);
	double lowLimit=0;
	double highLimit=4000;
	/**
	double lowLimit=signal1->peakIntegral_sigma;
	double highLimit=signal1->peakIntegral_sigma;
	for(int j=1;j<entries;j++){
	  t->GetEntry(j);
	  lowLimit=(lowLimit<(signal1->peakIntegral_sigma))?lowLimit:(signal1->peakIntegral_sigma);
	  highLimit=(highLimit>(signal1->peakIntegral_sigma))?highLimit:(signal1->peakIntegral_sigma);
	}
	cout<<lowLimit<<"\t"<<highLimit<<endl;
	**/

	//fill 2D histogram
    h1=new TH1D("h1","strip1",100,lowLimit,highLimit);
    h2=new TH1D("h2","strip2",100,lowLimit,highLimit);
    h3=new TH1D("h3","strip3",100,lowLimit,highLimit);
    h4=new TH1D("h4","strip4",100,lowLimit,highLimit);

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

	//Project 2D histogram to 1D histogram, with only localTime information reserved. Fit 1D
	//histogram with Guass distribution, get mean value and sigma.
	h1->Fit("gaus","W");
	TF1* fit1=h1->GetFunction("gaus");
	double mean1=fit1->GetParameter(1);
	double sigma1=fit1->GetParameter(2);
	cout<<"1----------------"<<mean1<<"\t"<<sigma1<<"----------------"<<endl;
	y1[i]=mean1;
	e1[i]=sigma1;

	h2->Fit("gaus","W");
	TF1* fit2=h2->GetFunction("gaus");
	double mean2=fit2->GetParameter(1);
	double sigma2=fit2->GetParameter(2);
	cout<<"2----------------"<<mean2<<"\t"<<sigma2<<"----------------"<<endl;
	y2[i]=mean2;
	e2[i]=sigma2;

	h3->Fit("gaus","W");
	TF1* fit3=h3->GetFunction("gaus");
	double mean3=fit3->GetParameter(1);
	double sigma3=fit3->GetParameter(2);
	cout<<"3----------------"<<mean3<<"\t"<<sigma3<<"----------------"<<endl;
	y3[i]=mean3;
	e3[i]=sigma3;

	h4->Fit("gaus","W");
	TF1* fit4=h4->GetFunction("gaus");
	double mean4=fit4->GetParameter(1);
	double sigma4=fit4->GetParameter(2);
	cout<<"4----------------"<<mean4<<"\t"<<sigma4<<"----------------"<<endl;
	y4[i]=mean4;
	e4[i]=sigma4;

 	delete h1;
	delete h2;
	delete h3;
	delete h4;
  }

  TCanvas *c1=new TCanvas("c1","Integrated ADC vs. Drift Votage",1000,800);
  c1->Divide(2,2);

  c1->cd(1);
  TGraphErrors *gr1=new TGraphErrors(nPoints,x,y1,0,e1);
  gr1->SetMarkerStyle(4);
  gr1->SetMarkerSize(1);
  gr1->SetTitle("stripe1");
  gr1->Fit("pol1");
//  gr1->GetYaxis()->SetRangeUser(0,2000);
  gr1->Draw("AP");
  c1->cd(2);
  TGraphErrors *gr2=new TGraphErrors(nPoints,x,y2,0,e2);
  gr2->SetMarkerStyle(4);
  gr2->SetMarkerSize(1);
  gr2->SetTitle("stripe2");
  gr2->Fit("pol1");
//  gr2->GetYaxis()->SetRangeUser(0,2000);
  gr2->Draw("AP");
  c1->cd(3);
  TGraphErrors *gr3=new TGraphErrors(nPoints,x,y3,0,e3);
  gr3->SetMarkerStyle(4);
  gr3->SetMarkerSize(1);
  gr3->SetTitle("stripe3");
  gr3->Fit("pol1");
//  gr3->GetYaxis()->SetRangeUser(0,2000);
  gr3->Draw("AP");
  c1->cd(4);
  TGraphErrors *gr4=new TGraphErrors(nPoints,x,y4,0,e4);
  gr4->SetMarkerStyle(4);
  gr4->SetMarkerSize(1);
  gr4->SetTitle("stripe4");
  gr4->Fit("pol1");
//  gr4->GetYaxis()->SetRangeUser(0,2000);
  gr4->Draw("AP");

  //Draw relative resolution dependency over variables.
  TCanvas* c2=new TCanvas("c2","Raletive E Resolution vs. GEM Voltage for Run 24 to 28",1000,800);	
  gStyle->SetOptFit(0000);
  c2->Divide(2,2);

  double py1[nPoints];
  double py2[nPoints];
  double py3[nPoints];
  double py4[nPoints];
  for(int i=0;i<nPoints;i++){
    py1[i]=e1[i]/y1[i];
    py2[i]=e2[i]/y2[i];
    py3[i]=e3[i]/y3[i];
    py4[i]=e4[i]/y4[i];
  }

  c2->cd(1);
  TGraph* g1_c2=new TGraph(nPoints,x,py1);
  g1_c2->SetTitle("strip1");
  g1_c2->SetMarkerStyle(4);
  g1_c2->SetMarkerSize(1);
//  g1_c2->Fit("pol1","","",200,220);
  g1_c2->Fit("pol1");
  g1_c2->GetYaxis()->SetTitle("Relative Resolution [#sigma/#mu]");
  g1_c2->GetYaxis()->SetTitleSize(0.05);
  g1_c2->GetYaxis()->SetTitleOffset(0.9);
  g1_c2->GetXaxis()->SetTitle("Drift Voltage [V]");
  g1_c2->GetXaxis()->SetTitleSize(0.05);
  g1_c2->GetXaxis()->SetTitleOffset(0.8);
  g1_c2->Draw("AP");

  c2->cd(2);
  TGraph* g2_c2=new TGraph(nPoints,x,py2);
  g2_c2->SetTitle("strip2");
  g2_c2->SetMarkerStyle(4);
  g2_c2->SetMarkerSize(1);
//  g2_c2->Fit("pol1","","",200,220);
  g2_c2->Fit("pol1");
  g2_c2->Draw("AP");

  c2->cd(3);
  TGraph* g3_c2=new TGraph(nPoints,x,py3);
  g3_c2->SetTitle("strip3");
  g3_c2->SetMarkerStyle(4);
  g3_c2->SetMarkerSize(1);
//  g3_c2->Fit("pol1","","",200,220);
  g3_c2->Fit("pol1");
  g3_c2->Draw("AP");

  c2->cd(4);
  TGraph* g4_c2=new TGraph(nPoints,x,py4);
  g4_c2->SetTitle("strip4");
  g4_c2->SetMarkerStyle(4);
  g4_c2->SetMarkerSize(1);
//  g4_c2->Fit("pol1","","",200,220);
  g4_c2->Fit("pol1");
  g4_c2->Draw("AP");

}

