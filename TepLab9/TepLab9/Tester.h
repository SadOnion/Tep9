#pragma once
#include <cstdio>
#include "CMscnProblem.h"
#include <string>
#include "Solution.h"
#include <time.h>
class Tester
{
	FILE* file;
public:
	CMscnProblem LoadProblem(std::string fileName);
	Solution LoadSolution(std::string fileName);
	void SaveProblem(CMscnProblem &problem);
	void CreateRandomTest();
};

