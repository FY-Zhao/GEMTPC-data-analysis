#ifndef MYSIGNAL_H
#define MYSIGNAL_H 1
class Signal:public TObject{
public:
    int cardNum;
	int meanADC;
	int triStart;
	int triStartNum;
	int localTime;
	int positionX;
	int positionY;
	int height;
	int sigmaXP;
	int sigmaXM;
	int sigmaYP;
	int sigmaYM;
	int rangeXP;
	int rangeXM;
	int rangeYP;
	int rangeYM;
	int peakIntegral_sigma;
	int peakIntegral_range;
	int event_tag;

private:
	double gravityCenterX;
	double gravityCenterY;

public:
    Signal(); 
	virtual ~Signal(); 

	void GetGravityCenter(double**);
	inline double GetGravityCenterX(){return gravityCenterX;}
	inline double GetGravityCenterY(){return gravityCenterY;}

	ClassDef(Signal,1);
};
#endif

