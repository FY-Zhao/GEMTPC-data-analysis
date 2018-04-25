#include "TCanvas.h"

Long64_t x1[16];
Long64_t q1[16];
Long64_t z1[16];
Long64_t w1[16];
Long64_t x2[16];
Long64_t q2[16];
Long64_t z2[16];
Long64_t w2[16];

TCanvas *can1;
//TCanvas *c2;
string filename;
TH2D* h11=0;
TH2D* h12=0;
TH2D* h13=0;
TH2D* h14=0;
TH2D* h21=0;
TH2D* h22=0;
TH2D* h23=0;
TH2D* h24=0;
TTree* T1;
TTree* T2;
Long64_t indexMax1;
Long64_t indexMax2;
Long64_t N_entries1;
Long64_t N_entries2;
Long64_t bincontent[16];
//vector<int> HitX;
//vector<int> HitY;

/**
void getCuts(string a){
  ifstream inFile(a);
  if(!inFile){
    cout<<"ERROR: no such cut data file!"<<endl;
    return;
  }
  for(int i=0;i<32;++i){
    inFile>>meanX[i]>>sigmaX[i]>>MaxX[i]>>meanX[i+32]>>sigmaX[i+32]>>MaxX[i+32];
  }
}
**/

void UserInput(const char* command){
  if(h11){
    delete can1;
    delete h11;
    delete h12;
    delete h13;
    delete h14;
    delete h21;
    delete h22;
    delete h23;
    delete h24;

    can1=new TCanvas("can1","can1",1800,600);
    can1->Divide(8,1);
//    delete c2;
//    c2=new TCanvas("c2","c2",800,1000);
    Long64_t indexNum=atol(command);
    if(indexNum==0){cout<<"exiting"<<endl;gApplication->Terminate(0);}
    cout<<"Your input: "<<indexNum<<endl;

    Long64_t entryMin1=T1->GetEntryNumberWithIndex(indexNum);
    Long64_t entryMax1=((indexNum==indexMax1)?N_entries1:(T1->GetEntryNumberWithIndex(indexNum+1)));
    Long64_t yBins1=entryMax1-entryMin1;
    Long64_t entryMin2=T2->GetEntryNumberWithIndex(indexNum);
    Long64_t entryMax2=((indexNum==indexMax2)?N_entries2:(T2->GetEntryNumberWithIndex(indexNum+1)));
    Long64_t yBins2=entryMax2-entryMin2;

    cout<<"---------------------------------------"<<endl;
    cout<<entryMin1<<"\t"<<entryMax1<<"\t"<<yBins1<<endl;
    cout<<entryMin2<<"\t"<<entryMax2<<"\t"<<yBins2<<endl;
    cout<<"---------------------------------------"<<endl;
//    bool Judge1, Judge2, Signal;
    h11=new TH2D("h11","h11",16,0,16,yBins1,entryMin1,entryMax1-1);
    h12=new TH2D("h12","h12",16,0,16,yBins1,entryMin1,entryMax1-1);
    h13=new TH2D("h13","h13",16,0,16,yBins1,entryMin1,entryMax1-1);
    h14=new TH2D("h14","h14",16,0,16,yBins1,entryMin1,entryMax1-1);
    h21=new TH2D("h21","h21",16,0,16,yBins2,entryMin2,entryMax2-1);
    h22=new TH2D("h22","h22",16,0,16,yBins2,entryMin2,entryMax2-1);
    h23=new TH2D("h23","h23",16,0,16,yBins2,entryMin2,entryMax2-1);
    h24=new TH2D("h24","h24",16,0,16,yBins2,entryMin2,entryMax2-1);

    for(Long64_t j=entryMin1;j<entryMax1;++j){
      T1->GetEntry(j);
	  cout<<x1[0]<<endl;
      for(int i=0;i<16;++i){
//        bincontent[i]=x[i]-meanX[i];
        bincontent[i]=x1[i];
        h11->SetBinContent(i+1,j-entryMin1+1,bincontent[i]);
      }
      for(int i=0;i<16;++i){
        bincontent[i]=q1[i];
        h12->SetBinContent(i+1,j-entryMin1+1,bincontent[i]);
      }
      for(int i=0;i<16;++i){
        bincontent[i]=z1[i];
        h13->SetBinContent(i+1,j-entryMin1+1,bincontent[i]);
      }
      for(int i=0;i<16;++i){
        bincontent[i]=w1[i];
        h14->SetBinContent(i+1,j-entryMin1+1,bincontent[i]);
      }
/**
      for(int i=0;i<32;++i){
	JudgeX[i]=(bincontent[i]>MaxX[i]);
	Judge1+=JudgeX[i];
	if(JudgeX[i]==true)
	  if(find(HitX.begin(),HitX.end(),i+1)==HitX.end()) HitX.push_back(i+1);
	JudgeX[i]=false;
	JudgeY[i]=(bincontent[i+32]>MaxX[i+32]);
        Judge2+=JudgeY[i];
        if(JudgeY[i]==true) 
	  if(find(HitY.begin(),HitY.end(),i+1)==HitY.end()) HitY.push_back(i+1);
	JudgeY[i]=false;
      }
      Signal+=(Judge1*Judge2);
**/
    }
	cout<<endl;
    for(Long64_t j=entryMin2;j<entryMax2;++j){
      T2->GetEntry(j);
	  cout<<x2[0]<<endl;
      for(int i=0;i<16;++i){
//        bincontent[i]=x[i]-meanX[i];
        bincontent[i]=x2[i];
        h21->SetBinContent(i+1,j-entryMin2+1,bincontent[i]);
      }
      for(int i=0;i<16;++i){
        bincontent[i]=q2[i];
        h22->SetBinContent(i+1,j-entryMin2+1,bincontent[i]);
      }
      for(int i=0;i<16;++i){
        bincontent[i]=z2[i];
        h23->SetBinContent(i+1,j-entryMin2+1,bincontent[i]);
      }
      for(int i=0;i<16;++i){
        bincontent[i]=w2[i];
        h24->SetBinContent(i+1,j-entryMin2+1,bincontent[i]);
      }
    }

    gStyle->SetOptStat(kFALSE);
    can1->cd(3);
    h11->Draw("COLZ");
	can1->cd(4);
    h12->Draw("COLZ");
	can1->cd(5);
    h13->Draw("COLZ");
	can1->cd(6);
    h14->Draw("COLZ");
    can1->cd(1);
    h21->Draw("COLZ");
	can1->cd(2);
    h22->Draw("COLZ");
	can1->cd(7);
    h23->Draw("COLZ");
	can1->cd(8);
    h24->Draw("COLZ");

/**
    if(Signal){
      int nHitX=HitX.size();
      int nHitY=HitY.size();
      cout<<"There are "<<nHitX<<" wires hit:"<<endl;
      for(int i=0;i<nHitX;i++) cout<<HitX[i]<<"\t";
      cout<<endl; 
      cout<<"There are "<<nHitY<<" strips hit:"<<endl;
      for(int i=0;i<nHitY;i++) cout<<HitY[i]<<"\t";
      cout<<endl; 
      c2->Divide(1,2);
      vector<TH1D*> hx_tempt(nHitX);
      vector<TH1D*> hy_tempt(nHitY);
      THStack* hsX=new THStack("hsX","histogram stacks for wires");
      THStack* hsY=new THStack("hsY","histogram stacks for stripes");
      TLegend* legendX=new TLegend(0.7,0.7,0.9,0.9);
      TLegend* legendY=new TLegend(0.7,0.7,0.9,0.9);
      //c2->cd();
      c2->cd(1);
      char name1[10];
      for(int i=0;i<nHitX;i++){
	sprintf(name1,"wire%d",HitX[i]);
	hx_tempt[i]=h->ProjectionY(name1,HitX[i],HitX[i]);
	hx_tempt[i]->SetLineColor(2*i+2);
	hx_tempt[i]->SetLineWidth(2);
	//hx_tempt[i]->SetFillColor(2*i+2);
	//hx_tempt[i]->SetFillStyle(3000+i);
	hsX->Add(hx_tempt[i]);
        legendX->AddEntry(hx_tempt[i],name1,"l");
      }
      hsX->Draw();
      legendX->Draw("same");
      gPad->Modified();
      c2->Update();
      c2->cd(2); 
      char name2[10];
      for(int i=0;i<nHitY;i++){
	sprintf(name2,"stripe%d",HitY[i]);
	hy_tempt[i]=h->ProjectionY(name2,HitY[i]+32,HitY[i]+32);
	hy_tempt[i]->SetLineColor(2*i+2);
	hy_tempt[i]->SetLineWidth(2);
	//hy_tempt[i]->SetFillColor(2*i+2);
	//hy_tempt[i]->SetFillStyle(3000+i);
	hsY->Add(hy_tempt[i]);
        legendY->AddEntry(hy_tempt[i],name2,"l");
      }
      hsY->Draw();
      legendY->Draw("same");
      gPad->Modified();
      c2->Update();
      vector<TH1D*>().swap(hx_tempt);
      vector<TH1D*>().swap(hy_tempt);
    }

    HitX.clear();
    HitY.clear();
    Signal=false;
    Judge1=false;
    Judge2=false;
    cout<<"Please enter the events number between 2 and "<<indexMax<<" (Quit: 0): ";
  //  string PDFname=inputFile+".pdf";
  //  PDFfile=PDFname.c_str();
  //  h->SaveAs(PDFfile);
**/
  }
}

void ADCoverview_allPads()
{
//  string inputFile, inputPosfix1;
  TFile* file1=new TFile("run19_1.root");
  TFile* file2=new TFile("run19_2.root");
  T1=(TTree*)file1->Get("ADCrecord");
  T2=(TTree*)file2->Get("ADCrecord");
  /**
  do{
    cout<<"Please enter the correct input file's name without postfix (Quit: exit): ";
    cin>>inputFile;
    if(inputFile=="exit") {cout<<"exiting"<<endl;gApplication->Terminate(0);}
    cout<<inputFile<<endl;
    inputPosfix1=inputFile+".root";
    const char* inputTFile=inputPosfix1.c_str();
    file1=new TFile(inputTFile,"update");
    T=(TTree*)file1->Get("ADCrecord");
  }while(!T);
  **/

  N_entries1=T1->GetEntries(); 
  N_entries2=T2->GetEntries(); 
  cout<<"total entries for file 1: "<<N_entries1<<endl;
  cout<<"total entries for file 2: "<<N_entries2<<endl;

//  string inputCutFile="cut_"+inputFile+".dat";
//  getCuts(inputCutFile);

  char temp11[10];
  char temp12[10];
  char temp13[10];
  char temp14[10];
  char a1[10];
  char b1[10];
  char c1[10];
  char d1[10];
  char temp21[10];
  char temp22[10];
  char temp23[10];
  char temp24[10];
  char a2[10];
  char b2[10];
  char c2[10];
  char d2[10];

  for(int i=0;i<16;++i){
    strcpy(a1,"card1_");
    sprintf(temp11,"%d",i);
    strcat(a1,temp11);
    T1->SetBranchAddress(a1,&x1[i]);
    strcpy(b1,"card2_");
    sprintf(temp12,"%d",i);
    strcat(b1,temp12);
    T1->SetBranchAddress(b1,&q1[i]);
    strcpy(c1,"card3_");
    sprintf(temp13,"%d",i);
    strcat(c1,temp13);
    T1->SetBranchAddress(c1,&z1[i]);
    strcpy(d1,"card4_");
    sprintf(temp14,"%d",i);
    strcat(d1,temp14);
    T1->SetBranchAddress(d1,&w1[i]);
  }
  for(int i=0;i<16;++i){
    strcpy(a2,"card1_");
    sprintf(temp21,"%d",i);
    strcat(a2,temp21);
    T2->SetBranchAddress(a2,&x2[i]);
    strcpy(b2,"card2_");
    sprintf(temp22,"%d",i);
    strcat(b2,temp22);
    T2->SetBranchAddress(b2,&q2[i]);
    strcpy(c2,"card3_");
    sprintf(temp23,"%d",i);
    strcat(c2,temp23);
    T2->SetBranchAddress(c2,&z2[i]);
    strcpy(d2,"card4_");
    sprintf(temp24,"%d",i);
    strcat(d2,temp24);
    T2->SetBranchAddress(d2,&w2[i]);
  }

  Long64_t bunch_Num1;
  TBranch *bunch1=T1->GetBranch("bunch");
  bunch1->SetAddress(&bunch_Num1);
  T1->GetEntry(N_entries1-1);
  indexMax1=bunch_Num1;//As I used bunch as index previously, here I use the last bunch to get the maximum index. 
  Long64_t bunch_Num2;
  TBranch *bunch2=T2->GetBranch("bunch");
  bunch2->SetAddress(&bunch_Num2);
  T2->GetEntry(N_entries2-1);
  indexMax2=bunch_Num2;//As I used bunch as index previously, here I use the last bunch to get the maximum index. 

  h11=new TH2D("h11","h11",100,0,100,100,0,100);
  h12=new TH2D("h12","h12",100,0,100,100,0,100);
  h13=new TH2D("h13","h13",100,0,100,100,0,100);
  h14=new TH2D("h14","h14",100,0,100,100,0,100);
  h21=new TH2D("h21","h21",100,0,100,100,0,100);
  h22=new TH2D("h22","h22",100,0,100,100,0,100);
  h23=new TH2D("h23","h23",100,0,100,100,0,100);
  h24=new TH2D("h24","h24",100,0,100,100,0,100);

  can1=new TCanvas("can1","can1",1400,800);
  can1->Draw();
  can1->cd(3);
  h11->Draw();
  can1->cd(4);
  h12->Draw();
  can1->cd(5);
  h13->Draw();
  can1->cd(6);
  h14->Draw();
  can1->cd(1);
  h21->Draw();
  can1->cd(2);
  h22->Draw();
  can1->cd(7);
  h23->Draw();
  can1->cd(8);
  h24->Draw();


//  c2=new TCanvas("c2","c2",800,1000);

  int indexMax=(indexMax1<indexMax2)?indexMax1:indexMax2;
  cout<<"Please enter the events number between 2 and "<<indexMax<<" (Quit: 0): "<<endl;
  gApplication->Connect("ReturnPressed(const char*)", 0, 0, "UserInput(const char*)");
}

