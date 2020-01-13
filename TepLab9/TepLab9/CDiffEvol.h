#pragma once
#include "CMscnProblem.h"
#include "Individual.h"
#include "Population.h"
#include "IOptimizer.h"
class CDiffEvol : public IOptimizer
{
private:
	const float DEFAULT_DIFF_WEIGHT = 0.5;
	const float DEFAULT_CROSS_PROBABILITY = 0.5;
	const float DEFAULT_TIME = 1;
	const float DEFAULT_POPULATION_SIZE = 100;

	IProblem* problem;
	float diffWeight;
	float timeInSec;
	int populationSize;
	int geneSize;
	float crossProbability;
	CRandom rand;
	double quality;
	Individual GetRandomIndividual();
	Individual GetRandomIndividualFromPopulation(Population& population);
	Solution GetBestSolution(Population& population);
	bool AreDifferent(Individual& ind1,Individual& ind2,Individual& ind3,Individual& ind4);
	void InitializePopulation(Population& pop,int size);
	bool CorrectGeneValue(double newVal,int index);
	double Fitness(Individual& individual);
public:
	CDiffEvol(IProblem* prob,float crossProb,float diffWeight,int populationSize,float timeInSec);
	double GetQuality(){return quality;}

	// Odziedziczono za poœrednictwem elementu IOptimizer
    ISolution* Search() override;
};

