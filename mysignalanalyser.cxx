#include "mysignalanalyser.h"
#include "mysignal.h"
#include "TMath.h"
#include <stdexcept>

SignalAnalyser::SignalAnalyser()
{}

SignalAnalyser::~SignalAnalyser()
{}

double SignalAnalyser::GetMeanValue(double**spectrum, int n, int m, double pedestal, double threshold){
  double meanValue=0;
  int temp=0;
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
	  if(TMath::Abs(spectrum[i][j]-pedestal)<threshold) meanValue+=spectrum[i][j];
	  else temp++;
	}
  }
  return meanValue/(n*m-temp);
}

double SignalAnalyser::GetVarianceValue(double** spectrum, int n, int m, double mean, double pedestal, double threshold){
  double varianceValue=0;
  int temp=0;
  for(int i=0;i<n;i++){
    for(int j=0;j<m;j++){
	  if(TMath::Abs(spectrum[i][j]-pedestal)<threshold) varianceValue+=(spectrum[i][j]*spectrum[i][j]+mean*mean-2*mean*spectrum[i][j]);
	  else temp++;
	}
  }
  return TMath::Sqrt(varianceValue/(n*m-temp));
}

string SignalAnalyser::readKeyword(string s1){
  vector<char> temp;
  string keyWord;
  for(string::size_type i=0;i!=s1.size();){
    while(s1[i]!='_'&&s1[i]!='.'&&i!=s1.size()){temp.push_back(s1[i]);i++;}
	if(temp[temp.size()-1]=='V') {keyWord.assign(temp.begin(),temp.end()); return keyWord;}
	else i++;
	temp.clear();
  }
  throw runtime_error("ERROR! There is no keyword 'V' in the file name!");
}

void SignalAnalyser::checkOverlap(Signal* a, int N, int baseMin, int baseMax, vector<Signal> &vectSignal){
  vector<int> base;
  int min,max;
  for(int j=baseMin;j<baseMax;j++){base.push_back(0);}
  for(int i=0;i<N;i++){
    min=-a[i].sigmaYM+a[i].positionY;
    max=a[i].sigmaYP+a[i].positionY;
//    cout<<min<<"\t"<<max<<"\t"<<a[i].height<<endl;
    for(int j=min-baseMin;j<=max-baseMin;j++){
	base[j]=base[j]+1;
    }
  }
//  for(int j=0;j<baseMax-baseMin;j++){cout<<j+baseMin<<"\t"<<base[j]<<endl;}
  for(int i=0;i<N;i++){
    bool noOverlap=true;
    min=-a[i].sigmaYM+a[i].positionY;
    max=a[i].sigmaYP+a[i].positionY;
    for (int j=min-baseMin;j<=max-baseMin;j++) noOverlap*=(base[j]==1);
    if(noOverlap) vectSignal.push_back(a[i]);
//    cout<<"Hit positionY: "<<a[i].positionY<<endl;
  }
}
