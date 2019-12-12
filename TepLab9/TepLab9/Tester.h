#pragma once
#include <cstdio>
#include "CMscnProblem.h"
#include <string>
#include "Solution.h"
class Tester
{
	FILE* file;
public:
	CMscnProblem LoadProblem(std::string fileName);
	Solution LoadSolution(std::string fileName);
	
};

