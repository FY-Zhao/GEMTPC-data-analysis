#ifdef MYSIGNAL_SECOND_RUN

#include "TCanvas.h"
#include "string.h"
#include "mysignal.h"
/**
double g1(double *x, double *par){
  return par[0]*exp(-0.5*TMath::Power((x[0]-par[1]),2)/TMath::Power(par[2],2))/TMath::sqrt(2*TMath::Pi()*TMath::Power(par[2],2));
}

double g2(double *x, double *par){
  return par[3]*exp(-0.5*TMath::Power((x[0]-par[4]),2)/TMath::Power(par[5],2))/TMath::sqrt(2*TMath::Pi()*TMath::Power(par[5],2));
}
**/
const int YBinNum=160;
const int YBinBegin=0;
const int YBinEnd=40;
const int expPeaks=2;
const int expSigma=1;
const double threshold=0.2;

void fitPeak_driftTime(bool secondRun=true, string filename=""){
  TFile* f=nullptr;
  TTree* t=nullptr;
  gStyle->SetOptFit(0001);
  TH2D *h1;
  TH2D *h2;
  TH2D *h3;
  TH2D *h4;
  Signal *signal1=0;
  TCanvas *c1=new TCanvas("c1","Drift Time vs. Source Height",1000,800);
  c1->Divide(2,2);

	string inputFilename="selected_signal_"+filename+".root";
    f=new TFile(inputFilename.c_str());
	t=(TTree*)f->Get("selectedSignal");
	if(!t) throw runtime_error("ERROR! there's no such file or tree in this directory.");
	//f=new TFile("signal_run37_3.root");
	//t=(TTree*)f->Get("TSignal");
	t->SetBranchAddress("signal",&signal1);
	int entries=t->GetEntries();
	cout<<"Entries: "<<entries<<endl;

	//fill 2D histogram
    h1=new TH2D("h1","strip1",16,0,16,YBinNum,YBinBegin,YBinEnd);
    h2=new TH2D("h2","strip2",16,0,16,YBinNum,YBinBegin,YBinEnd);
    h3=new TH2D("h3","strip3",16,0,16,YBinNum,YBinBegin,YBinEnd);
    h4=new TH2D("h4","strip4",16,0,16,YBinNum,YBinBegin,YBinEnd);

	for(int j=0;j<entries;j++){
	  t->GetEntry(j);
	  /**
	  if(signal1->cardNum==1){
	    h1->Fill(signal1->positionX,signal1->localTime);
	  }
	  else if(signal1->cardNum==2){
	    h2->Fill(signal1->positionX,signal1->localTime);
	  }
	  else if(signal1->cardNum==3){
	    h3->Fill(signal1->positionX,signal1->localTime);
	  }
	  else if(signal1->cardNum==4){
	    h4->Fill(signal1->positionX,signal1->localTime);
	  }
	  **/
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
	TH1D* p2=h2->ProjectionY("p2",0,-1);
	TH1D* p3=h3->ProjectionY("p3",0,-1);
	TH1D* p4=h4->ProjectionY("p4",0,-1);
	
	double source1[YBinNum],dest1[YBinNum];
	for(int i=0;i<YBinNum;i++){source1[i]=p1->GetBinContent(i+1);}
	double source2[YBinNum],dest2[YBinNum];
	for(int i=0;i<YBinNum;i++){source2[i]=p2->GetBinContent(i+1);}
	double source3[YBinNum],dest3[YBinNum];
	for(int i=0;i<YBinNum;i++){source3[i]=p3->GetBinContent(i+1);}
	double source4[YBinNum],dest4[YBinNum];
	for(int i=0;i<YBinNum;i++){source4[i]=p4->GetBinContent(i+1);}

    TSpectrum *s1=new TSpectrum(expPeaks);
	int nPeaks1=s1->SearchHighRes(source1,dest1,YBinNum,expSigma,threshold,false,3,false,10);
	cout<<nPeaks1<<endl;
    TSpectrum *s2=new TSpectrum(expPeaks);
	int nPeaks2=s2->SearchHighRes(source2,dest2,YBinNum,expSigma,threshold,false,3,false,10);
	cout<<nPeaks2<<endl;
    TSpectrum *s3=new TSpectrum(expPeaks);
	int nPeaks3=s3->SearchHighRes(source3,dest3,YBinNum,expSigma,threshold,false,3,false,10);
	cout<<nPeaks3<<endl;
    TSpectrum *s4=new TSpectrum(expPeaks);
	int nPeaks4=s4->SearchHighRes(source4,dest4,YBinNum,expSigma,threshold,false,3,false,10);
	cout<<nPeaks4<<endl;
	if((nPeaks1!=expPeaks)||(nPeaks2!=expPeaks)||(nPeaks3!=expPeaks)||(nPeaks4!=expPeaks))
	throw runtime_error("ERROR! There's at least one stripe that didn't record two peaks!");

	double firstPP=YBinEnd;
	double lastPP=YBinBegin;
	double *xPeaks1=s1->GetPositionX();
	double par1[3*expPeaks];
	for(int i=0;i<expPeaks;i++){
	  double xp=p1->GetXaxis()->GetBinCenter((int)xPeaks1[i]);
	  firstPP=(xp<firstPP)?xp:firstPP;
	  lastPP=(xp>lastPP)?xp:lastPP;
	  int bin=p1->GetXaxis()->FindBin(xp);
	  int yp=p1->GetBinContent(bin);
	  par1[3*i]=yp;
	  par1[3*i+1]=xp;
	  par1[3*i+2]=expSigma;
	}
	cout<<"+++++"<<firstPP<<"\t"<<lastPP<<"+++++"<<endl;
	double *xPeaks2=s2->GetPositionX();
	double par2[3*expPeaks];
	for(int i=0;i<expPeaks;i++){
	  double xp=p2->GetXaxis()->GetBinCenter((int)xPeaks2[i]);
	  int bin=p2->GetXaxis()->FindBin(xp);
	  int yp=p2->GetBinContent(bin);
	  par2[3*i]=yp;
	  par2[3*i+1]=xp;
	  par2[3*i+2]=expSigma;
	}
	double *xPeaks3=s3->GetPositionX();
	double par3[3*expPeaks];
	for(int i=0;i<expPeaks;i++){
	  double xp=p3->GetXaxis()->GetBinCenter((int)xPeaks3[i]);
	  int bin=p3->GetXaxis()->FindBin(xp);
	  int yp=p3->GetBinContent(bin);
	  par3[3*i]=yp;
	  par3[3*i+1]=xp;
	  par3[3*i+2]=expSigma;
	}
	double *xPeaks4=s4->GetPositionX();
	double par4[3*expPeaks];
	for(int i=0;i<expPeaks;i++){
	  double xp=p4->GetXaxis()->GetBinCenter((int)xPeaks4[i]);
	  int bin=p4->GetXaxis()->FindBin(xp);
	  int yp=p4->GetBinContent(bin);
	  par4[3*i]=yp;
	  par4[3*i+1]=xp;
	  par4[3*i+2]=expSigma;
	}

	int sPoint=((int)(firstPP-5)>YBinBegin)?(int)(firstPP-5):YBinBegin;
	int ePoint=((int)(lastPP+5)<YBinEnd)?(int)(lastPP+5):YBinEnd;
	TF1* total=new TF1("total","gaus(0)+gaus(3)",sPoint,ePoint);
	c1->cd(1);
	TVirtualFitter::Fitter(p1,3*expPeaks);
	total->SetParameters(par1);
	p1->Fit("total","WR");
	p1->Draw();
	c1->cd(2);
	TVirtualFitter::Fitter(p2,3*expPeaks);
	total->SetParameters(par2);
	p2->Fit("total","WR");
	p2->Draw();
	c1->cd(3);
	TVirtualFitter::Fitter(p3,3*expPeaks);
	total->SetParameters(par3);
	p3->Fit("total","WR");
	p3->Draw();
	c1->cd(4);
	TVirtualFitter::Fitter(p4,3*expPeaks);
	total->SetParameters(par4);
	p4->Fit("total","WR");
	p4->Draw();
	//double *xPeaks2=s2->GetPositionX();
	//double *xPeaks3=s3->GetPositionX();
	//double *xPeaks4=s4->GetPositionX();

/**
	c1->cd(1);
	p1->Fit(g1,"WR");
	p1->Fit(g2,"WR+");
	g1->GetParameters(&par[0]);
	g2->GetParameters(&par[3]);
	total->SetParameters(par);
	p1->Fit(total,"WR","",0,35);
	p1->Draw();

	c1->cd(2);
	p2->Fit(g1,"WR");
	p2->Fit(g2,"WR+");
	g1->GetParameters(&par[0]);
	g2->GetParameters(&par[3]);
	total->SetParameters(par);
	p2->Fit(total,"WR","",0,35);
	p2->Draw();

	c1->cd(3);
	p3->Fit(g1,"WR");
	p3->Fit(g2,"WR+");
	g1->GetParameters(&par[0]);
	g2->GetParameters(&par[3]);
	total->SetParameters(par);
	p3->Fit(total,"WR","",0,35);
	p3->Draw();

	c1->cd(4);
	p4->Fit(g1,"WR");
	p4->Fit(g2,"WR+");
	g1->GetParameters(&par[0]);
	g2->GetParameters(&par[3]);
	total->SetParameters(par);
	p4->Fit(total,"WR","",0,35);
	p4->Draw();
	**/
/**
	//collect all points
    dataPoints1.push_back()
    dataPoints2.push_back()
    dataPoints3.push_back()
    dataPoints4.push_back()
//	delete f;
  }


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

void fitPeak_driftTime(string filename=""){
  gROOT->ProcessLine(".L mysignal.cxx+");
#define MYSIGNAL_SECOND_RUN yes
  gROOT->ProcessLine("#include \"" __FILE__ "\"");
  gROOT->ProcessLine(Form("fitPeak_driftTime(true,\"%s\")",filename.c_str()));
}

#endif
