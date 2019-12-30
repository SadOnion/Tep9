#pragma once
#include "CMscnProblem.h"
class CRandomSearch
{
private:
	const double DEFAULT_TIME = 10;
public:
	CMscnProblem Search(Solution& solution);
	CMscnProblem Search(Solution& solution,double timeInSec);
};

