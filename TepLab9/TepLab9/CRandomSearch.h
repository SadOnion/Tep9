#pragma once
#include "SolutionGenerator.h"
#include "IOptimizer.h"
class CRandomSearch : public IOptimizer
{
private:
	const double DEFAULT_TIME = 10;
	IProblem* problem;
	double searchDuration;
public:
	CRandomSearch(IProblem* problem);
	CRandomSearch(IProblem* problem,double timeInSec);
	 // Odziedziczono za poœrednictwem elementu IOptimizer
	 virtual ISolution* Search() override;
};

