#include "TCanvas.h"

Long64_t x[16];
Long64_t y[16];
Long64_t z[16];
Long64_t w[16];

TCanvas *c1;
//TCanvas *c2;
string filename;
TH2D* h1=0;
TH2D* h2=0;
TH2D* h3=0;
TH2D* h4=0;
TTree* T;
Long64_t indexMax;
Long64_t N_entries;
Long64_t bincontent[16];
//vector<int> HitX;
//vector<int> HitY;
bool JudgeA[16]={false};
bool JudgeB[16]={false};
bool JudgeC[16]={false};
bool JudgeD[16]={false};

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
  if(h1){
    delete c1;
    delete h1;
    delete h2;
    delete h3;
    delete h4;
    c1=new TCanvas("c1","c1",1600,800);
    c1->Divide(4,1);
//    delete c2;
//    c2=new TCanvas("c2","c2",800,1000);
    Long64_t indexNum=atol(command);
    if(indexNum==0){cout<<"exiting"<<endl;gApplication->Terminate(0);}
    cout<<"Your input: "<<indexNum<<endl;

    Long64_t entryMin=T->GetEntryNumberWithIndex(indexNum);
    Long64_t entryMax=((indexNum==indexMax)?N_entries:(T->GetEntryNumberWithIndex(indexNum+1)));
    Long64_t yBins=entryMax-entryMin;
    cout<<"---------------------------------------"<<endl;
    cout<<entryMin<<"\t"<<entryMax<<"\t"<<yBins<<endl;
    cout<<"---------------------------------------"<<endl;
    bool Judge1, Judge2, Signal;
    h1=new TH2D("h1","h1",16,0,16,yBins,entryMin,entryMax-1);
    h2=new TH2D("h2","h2",16,0,16,yBins,entryMin,entryMax-1);
    h3=new TH2D("h3","h3",16,0,16,yBins,entryMin,entryMax-1);
    h4=new TH2D("h4","h4",16,0,16,yBins,entryMin,entryMax-1);
    for(Long64_t j=entryMin;j<entryMax;++j){
      T->GetEntry(j);
	  cout<<x[0]<<endl;
      for(int i=0;i<16;++i){
//        bincontent[i]=x[i]-meanX[i];
        bincontent[i]=x[i];
        h1->SetBinContent(i+1,j-entryMin+1,bincontent[i]);
      }
      for(int i=0;i<16;++i){
        bincontent[i]=y[i];
        h2->SetBinContent(i+1,j-entryMin+1,bincontent[i]);
      }
      for(int i=0;i<16;++i){
        bincontent[i]=z[i];
        h3->SetBinContent(i+1,j-entryMin+1,bincontent[i]);
      }
      for(int i=0;i<16;++i){
        bincontent[i]=w[i];
        h4->SetBinContent(i+1,j-entryMin+1,bincontent[i]);
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

    gStyle->SetOptStat(kFALSE);
    c1->cd(1);
    h1->Draw("COLZ");
    gPad->Modified();
    c1->Update();
	c1->cd(2);
    h2->Draw("COLZ");
    gPad->Modified();
    c1->Update();
	c1->cd(3);
    h3->Draw("COLZ");
    gPad->Modified();
    c1->Update();
	c1->cd(4);
    h4->Draw("COLZ");
    gPad->Modified();
    c1->Update();

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

void ADCoverview_noCut()
{
  string inputFile, inputPosfix1;
  TFile* file1;
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

  N_entries=T->GetEntries(); 
  cout<<"total entries: "<<N_entries<<endl;

//  string inputCutFile="cut_"+inputFile+".dat";
//  getCuts(inputCutFile);

  char temp1[10];
  char temp2[10];
  char temp3[10];
  char temp4[10];
  char a[10];
  char b[10];
  char c[10];
  char d[10];

  for(int i=0;i<16;++i){
    strcpy(a,"card1_");
    sprintf(temp1,"%d",i);
    strcat(a,temp1);
    T->SetBranchAddress(a,&x[i]);
    strcpy(b,"card2_");
    sprintf(temp2,"%d",i);
    strcat(b,temp2);
    T->SetBranchAddress(b,&y[i]);
    strcpy(c,"card3_");
    sprintf(temp3,"%d",i);
    strcat(c,temp3);
    T->SetBranchAddress(c,&z[i]);
    strcpy(d,"card4_");
    sprintf(temp4,"%d",i);
    strcat(d,temp4);
    T->SetBranchAddress(d,&w[i]);
  }

  Long64_t bunch_Num;
  TBranch *bunch=T->GetBranch("bunch");
  bunch->SetAddress(&bunch_Num);
  T->GetEntry(N_entries-1);
  indexMax=bunch_Num;//As I used bunch as index previously, here I use the last bunch to get the maximum index. 

  h1=new TH2D("h1","h1",100,0,100,100,0,100);
  h2=new TH2D("h2","h2",100,0,100,100,0,100);
  h3=new TH2D("h3","h3",100,0,100,100,0,100);
  h4=new TH2D("h4","h4",100,0,100,100,0,100);
  c1=new TCanvas("c1","c1",1400,800);
  c1->Draw();
  c1->cd(1);
  h1->Draw();
  c1->Update();
  c1->cd(2);
  h2->Draw();
  c1->Update();
  c1->cd(3);
  h3->Draw();
  c1->Update();
  c1->cd(4);
  h4->Draw();
  c1->Update();

//  c2=new TCanvas("c2","c2",800,1000);

  cout<<"Please enter the events number between 2 and "<<indexMax<<" (Quit: 0): "<<endl;
  gApplication->Connect("ReturnPressed(const char*)", 0, 0, "UserInput(const char*)");
}

