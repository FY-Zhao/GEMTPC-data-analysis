#include "mysignal.h"

Signal::Signal()
: gravityCenterX(0),
  gravityCenterY(0)
{}

Signal::~Signal()
{}

void Signal::GetGravityCenter(double** spectrum){
	for(int i=positionX-sigmaXM-1;i<=positionX+sigmaXP-1;i++){
	    for(int j=localTime-sigmaYM-1;j<=localTime+sigmaYP-1;j++){
		  gravityCenterX+=i*spectrum[i][j];
		  gravityCenterY+=j*spectrum[i][j];
		}
	}
	gravityCenterX=1+gravityCenterX/peakIntegral_sigma;
	gravityCenterY=1+gravityCenterY/peakIntegral_sigma;
}

