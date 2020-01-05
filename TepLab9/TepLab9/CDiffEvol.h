#pragma once
#include "CMscnProblem.h"
#include "Individual.h"
#include "Population.h"
class CDiffEvol
{
private:
	const float DEFAULT_DIFF_WEIGHT = 1.0;
	const float DEFAULT_CROSS_PROBABILITY = 0.5;

	float diffWeight;
	CMscnProblem problem;
	int geneSize;
	float crossProbability;
	CRandom rand;

	Individual GetRandomIndividual();
	Solution GetBestSolution(Population& population);
	bool AreDifferent(Individual& ind1,Individual& ind2,Individual& ind3,Individual& ind4);
	void InitializePopulation(Population& pop,int size);
	bool CorrectGeneValue(double newVal,int index);
public:
	CDiffEvol(CMscnProblem& prob,float crossProb);
	void SetNewProblem(CMscnProblem& prob){problem.Take(prob);geneSize=problem.CorrectSolutionSize();}
	Solution Search(double timeInSec, int populationSize);
	double Fitness(Individual& individual);
};

