#include "CRandomSearch.h"
#include <ctime>
#include <iostream>
#include "Timer.h"
CMscnProblem CRandomSearch::Search(Solution& solution)
{
	CMscnProblem bestProblem(solution.GetSuppliersSize(), solution.GetFactoriesSize(), solution.GetWarehousesSize(), solution.GetShopsSize());
	CMscnProblem newProb(solution.GetSuppliersSize(), solution.GetFactoriesSize(), solution.GetWarehousesSize(), solution.GetShopsSize());
	CRandom rand;
	bestProblem.GenerateInstance(rand.RandomSeed());
	Timer timer;
	timer.Start();
	int secCounter=0;
	std::cout << "Searching ";
	while (timer.TimeFromStart() < DEFAULT_TIME)
	{
		newProb.GenerateInstance(rand.RandomSeed());
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

void CRandomSearch::Search2()
{
	CMscnProblem problem(2, 2, 2, 2);
	CRandom rand;
	problem.GenerateInstance(rand.RandomSeed());
	Vector4 sizes = problem.Sizes();
	Solution bestSol(sizes);
	Solution tempSol(sizes);
	SolutionGenerator gen;
	gen.GenerateRandomSolution(problem,bestSol);
	int timeInSec = 2;
	Timer timer;
	timer.Start();
	bool bestOrNot = false;
	while (timer.TimeFromStart() < timeInSec)
	{
		
		if (!bestOrNot) {
			gen.GenerateRandomSolution(problem, tempSol);
			if (problem.GetQuality(bestSol) < problem.GetQuality(tempSol)) {
				bestOrNot = true;
			}
		}
		else {
			gen.GenerateRandomSolution(problem, bestSol);
			if (problem.GetQuality(bestSol) > problem.GetQuality(tempSol)) {
				bestOrNot = false;
			}
		}
	}
	if (bestOrNot) {
		std::cout << problem.GetQuality(tempSol);
	}
	else {
		std::cout << problem.GetQuality(bestSol);
	}
		
}


