#pragma once
#include <random>
class CRandom
{
private:
	bool seeded;
	std::random_device rd;  
	std::mt19937 gen;
public:
	CRandom();
	CRandom(unsigned int seed);
	int Range(int min,int max);
	double Range(double min,double max);
	double Range(double min,double max,int precision);
};

