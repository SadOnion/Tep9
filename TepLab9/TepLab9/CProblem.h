#pragma once
#include "ISolution.h"
class IProblem{
public:
	virtual double GetQuality(ISolution& solution)=0;
	virtual int CorrectSolutionSize()=0;
	virtual bool CorrectValue(double newVal,int index)=0;
	virtual double* CorrectRandomSolution()=0;
	virtual void GenerateInstance(unsigned int seed)=0;
};


