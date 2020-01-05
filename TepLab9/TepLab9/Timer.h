#pragma once
#include <ctime>
class Timer
{
private:
	clock_t time;
public:
	void Start(){time=std::clock();}
	double TimeFromStart();
};

