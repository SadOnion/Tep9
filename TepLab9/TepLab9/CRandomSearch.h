#pragma once
#include "SolutionGenerator.h"
class CRandomSearch
{
private:
	const double DEFAULT_TIME = 10;
public:
	CMscnProblem Search(Solution& solution);
	CMscnProblem Search(Solution& solution,double timeInSec);
	void Search2();
};

