#include "CRandomSearch.h"
#include <ctime>
#include <iostream>
#include "Timer.h"
CMscnProblem CRandomSearch::Search(Solution& solution)
{
	CMscnProblem bestProblem(solution.GetSuppliersSize(), solution.GetFactoriesSize(), solution.GetWarehousesSize(), solution.GetShopsSize());
	CMscnProblem newProb(solution.GetSuppliersSize(), solution.GetFactoriesSize(), solution.GetWarehousesSize(), solution.GetShopsSize());
	std::random_device rd;
	bestProblem.GenerateInstance(rd());
	Timer timer;
	timer.Start();
	int secCounter=0;
	std::cout << "Searching ";
	while (timer.TimeFromStart() < DEFAULT_TIME)
	{
		newProb.GenerateInstance(rd());
		if (bestProblem.GetQuality(solution) < newProb.GetQuality(solution))
		{
			bestProblem.Take(newProb);
		}
		
		if (timer.TimeFromStart()-secCounter >= 1) {
			std::cout << ". ";
			secCounter++;
		}
	}
	
		
		

	return std::move(bestProblem);
}

CMscnProblem CRandomSearch::Search(Solution& solution, double timeInSec)
{
	CMscnProblem bestProblem(solution.GetSuppliersSize(), solution.GetFactoriesSize(), solution.GetWarehousesSize(), solution.GetShopsSize());
	CMscnProblem newProb(solution.GetSuppliersSize(), solution.GetFactoriesSize(), solution.GetWarehousesSize(), solution.GetShopsSize());
	std::random_device rd;
	bestProblem.GenerateInstance(rd());
	Timer timer;
	timer.Start();
	int secCounter=0;
	std::cout << "Searching ";
	while (timer.TimeFromStart() < timeInSec)
	{
		newProb.GenerateInstance(rd());
		if (bestProblem.GetQuality(solution) < newProb.GetQuality(solution))
		{
			bestProblem.Take(newProb);
		}
		
		if (timer.TimeFromStart()-secCounter >= 1) {
			std::cout << ". ";
			secCounter++;
		}
	}




	return std::move(bestProblem);
}
