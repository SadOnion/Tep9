#include "Timer.h"

Timer::Timer()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startTime);
}
void Timer::Start()
{
	QueryPerformanceCounter(&startTime);
}

double Timer::TimeFromStart()
{
	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);

	double timeFromStart =((double)now.QuadPart-startTime.QuadPart)/frequency.QuadPart;
	timeFromStart*=precision;
	timeFromStart = std::floor(timeFromStart);
	timeFromStart /= precision;
	return timeFromStart;
}
