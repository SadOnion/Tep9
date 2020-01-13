#pragma once
#include <windows.h>
#include <cmath>
class Timer
{
private:
	LARGE_INTEGER startTime;
	LARGE_INTEGER frequency;
	const int precision = 1000;
public:
	Timer();
	void Start();
	double TimeFromStart();
};

