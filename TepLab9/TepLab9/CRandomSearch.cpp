#include "CRandomSearch.h"
#include <ctime>
#include <iostream>
#include "Timer.h"
CRandomSearch::CRandomSearch(IProblem* problem)
{
	this->problem = problem;
	searchDuration=DEFAULT_TIME;
}
CRandomSearch::CRandomSearch(IProblem* problem, double timeInSec)
{
	this->problem = problem;
	searchDuration=timeInSec;
}
/*
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
*/
ISolution* CRandomSearch::Search()
{
	
	CRandom rand;
	problem->GenerateInstance(rand.RandomSeed());
	int size = problem->CorrectSolutionSize();
	Solution bestSol(problem->CorrectRandomSolution(),size);
	Solution tempSol(problem->CorrectRandomSolution(),size);

	Timer timer;
	timer.Start();
	
	while (timer.TimeFromStart() < searchDuration)
	{
		if(problem->GetQuality(bestSol) < problem->GetQuality(tempSol))
		{
			bestSol.Set(tempSol.GetSolution(),size);
		}	
		tempSol.Set(problem->CorrectRandomSolution(),size);
	}
	return new Solution(std::move(bestSol));
}



