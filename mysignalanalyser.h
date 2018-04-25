#ifndef MYSIGNALANALYSER_H
#define MYSIGNALANALYSER_H 1

class Signal;

class SignalAnalyser:public TObject{
public:
	SignalAnalyser();
	virtual ~SignalAnalyser();

	double GetMeanValue(double**, int, int, double, double);
	double GetVarianceValue(double**, int, int, double, double, double);
	string readKeyword(string);
	void checkOverlap(Signal*, int, int, int, vector<Signal>&);

private:
};

#endif
