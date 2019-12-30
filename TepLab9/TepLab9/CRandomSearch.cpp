#include "CRandomSearch.h"
#include <ctime>
#include <iostream>
CMscnProblem CRandomSearch::Search(Solution& solution)
{
	CMscnProblem bestProblem(solution.GetSuppliersSize(), solution.GetFactoriesSize(), solution.GetWarehousesSize(), solution.GetShopsSize());
	CMscnProblem newProb(solution.GetSuppliersSize(), solution.GetFactoriesSize(), solution.GetWarehousesSize(), solution.GetShopsSize());
	std::random_device rd;
	bestProblem.GenerateInstance(rd());
	int start = std::clock();
	int time = start;
	int second = start;
	std::cout << "Searching ";
	while ((double)(time - start) / CLOCKS_PER_SEC < DEFAULT_TIME)
	{
		newProb.GenerateInstance(rd());
		if (bestProblem.GetQuality(solution) < newProb.GetQuality(solution))
		{
			bestProblem.Take(newProb);
		}
		time = std::clock();
		if ((double)(time - second) / CLOCKS_PER_SEC >= 1) {
			std::cout << ". ";
			second = std::clock();
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
	int start = std::clock();
	int time = start;
	int second = start;
	std::cout << "Searching ";
	while ((double)(time - start) / CLOCKS_PER_SEC < timeInSec)
	{
		newProb.GenerateInstance(rd());
		if (bestProblem.GetQuality(solution) < newProb.GetQuality(solution))
		{
			bestProblem.Take(newProb);
		}
		time = std::clock();
		if ((double)(time - second) / CLOCKS_PER_SEC >= 1) {
			std::cout << ". ";
			second = std::clock();
		}
	}




	return std::move(bestProblem);
}
