#pragma once
#include "CMscnProblem.h"

class Utils{

	typedef double (CMscnProblem::*Func(int,int));

public:
	static double DoubleSum(int sizeI,int sizeJ,double** costFromTo,double* income);
	static double DoubleSumSigma(int sizeI, int sizeJ, double** elem, double* mult);
	static double Sum(int size,double* arr);
	static double Signum(double x);
	
};
