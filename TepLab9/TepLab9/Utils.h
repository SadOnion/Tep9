#pragma once
#include "CMscnProblem.h"
#include <vector>

class Utils{

	typedef double (Supplier::*Func)(int,int);

public:
	static double DoubleSum(int sizeI,int sizeJ,double** costFromTo,double* income);
	static double DoubleSumSigma(int sizeI, int sizeJ, double** elem, double* mult);
	static double Sum(int size,double* arr);
	static double Signum(double x);
	static double Sum(std::vector<Supplier*> sup,double(Supplier::*f(int)));
	
};
