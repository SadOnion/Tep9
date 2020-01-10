#include "CRandom.h"
#include <cmath>

CRandom::CRandom()
{
	seeded=false;
}

CRandom::CRandom(unsigned int seed)
{
	gen.seed(seed);
	seeded=true;
}

int CRandom::Range(int min, int max)
{
	std::uniform_int_distribution<> dis(min, max);
	if(!seeded) gen.seed(rd());
	return dis(gen);
    
}

double CRandom::Range(double min, double max)
{
    if(!seeded) gen.seed(rd());
    std::uniform_real_distribution<> dis(min, max);
	float value = (int)(dis(gen) * 10 + .5); 
    return (float)value / 10; 
	
}

double CRandom::Range(double min, double max, int precision)
{
	int prec = std::pow(10,precision);
    if(!seeded) gen.seed(rd());
    std::uniform_real_distribution<> dis(min, max);
	float value = (int)(dis(gen) * prec + .5); 
    return (float)value / prec; 
	
}

int CRandom::RandomSeed()
{
	return rd();
}
