#pragma once
#include "ISolution.h"
class IOptimizer{
public:
	virtual ISolution* Search()=0;
};