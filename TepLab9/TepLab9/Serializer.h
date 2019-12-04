#pragma once
#include <stdio.h>
#include <string>
#include "CMscnProblem.h"
class Serializer
{
private:
	std::string fileName;
	FILE* file;
public:
	Serializer(std::string fileName);
	void Save(CMscnProblem obj);
	CMscnProblem& Read();
};

