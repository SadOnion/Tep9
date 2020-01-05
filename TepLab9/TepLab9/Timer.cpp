#include "Timer.h"

double Timer::TimeFromStart()
{
	clock_t now = std::clock();
	double timeFromStart = (double)(now-time)/CLOCKS_PER_SEC;
	return timeFromStart;
}
