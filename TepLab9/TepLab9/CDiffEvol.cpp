#include "CDiffEvol.h"
#include "Timer.h"

#include "Vector4.h"
#include "Solution.h"
Individual CDiffEvol::GetRandomIndividual()
{
	double* randomSolution = problem->CorrectRandomSolution();
	int size = problem->CorrectSolutionSize();
	Individual individual(randomSolution,size);
	delete randomSolution;
	return individual;
}

Individual CDiffEvol::GetRandomIndividualFromPopulation(Population& population)
{
	int randomIndex = rand.Range(0,population.GetSize()-1);
	return population[randomIndex];
}

Solution CDiffEvol::GetBestSolution(Population& population)
{
	Solution sol(population[0].GetGenes(),geneSize);
	double best=problem->GetQuality(sol);
	int bestIndex=0;
	for (int i = 1; i < population.GetSize(); i++)
	{
		sol.Set(population[i].GetGenes(),geneSize);
		double next = problem->GetQuality(sol);
		
		if(next > best){
		best = next;
		bestIndex = i;
		}
	}
	if(bestIndex!=0)sol.Set(population[bestIndex].GetGenes(),geneSize);
	return std::move(sol);
}

bool CDiffEvol::AreDifferent(Individual& ind1, Individual& ind2, Individual& ind3, Individual& ind4)
{
	return !ind1.Equals(ind2) || !ind1.Equals(ind3) || !ind1.Equals(ind4) || !ind2.Equals(ind3) || !ind2.Equals(ind4) || !ind3.Equals(ind4);
}

void CDiffEvol::InitializePopulation(Population& pop,int size)
{
	for (int i = 0; i < size; i++)
	{
		pop[i] = GetRandomIndividual();
	}
}

bool CDiffEvol::CorrectGeneValue(double newVal,int index)
{
	
	return problem->CorrectValue(newVal,index);
	
}



ISolution* CDiffEvol::Search()
{
	
	if(diffWeight<0 || diffWeight>1) diffWeight=DEFAULT_DIFF_WEIGHT;
	Population population(populationSize,geneSize);
	InitializePopulation(population,populationSize);
	Timer timer;
	timer.Start();
	std::cout<<"Searching for best Solution: ";
	int secCounter =0;
	while(timer.TimeFromStart() < timeInSec)
	{
		for (int i = 0; i < populationSize; i++)
		{
			
			Individual indNew(geneSize);
			
			Individual baseInd = GetRandomIndividualFromPopulation(population);
			Individual addInd0 = GetRandomIndividualFromPopulation(population);	
			Individual addInd1 = GetRandomIndividualFromPopulation(population);
			
			if(AreDifferent(population[i],baseInd,addInd0,addInd1))
			{
				for (int geneOffset = 0; geneOffset < geneSize; geneOffset++)
				{
					if(rand.Range(0.0,1.0) <= crossProbability)
					{
						double newVal = baseInd[geneOffset] + diffWeight*(addInd0[geneOffset]-addInd1[geneOffset]);

						if(CorrectGeneValue(newVal,geneOffset))indNew[geneOffset] = newVal;
						else
						{
							indNew[geneOffset] = population[i][geneOffset];
						}
					}else
					{
						indNew[geneOffset] = population[i][geneOffset];
					}
				}
				if(Fitness(indNew) >= Fitness(population[i]))
				{
					
					population[i] = indNew;
					
				}
			}
			
		}
		if(timer.TimeFromStart() - secCounter >=1)
		{
			std::cout<< " . ";
			secCounter++;
		}
		
		
	}
	Solution solution = GetBestSolution(population);
	quality = problem->GetQuality(solution);
	return new Solution(std::move(solution));
}

double CDiffEvol::Fitness(Individual& individual)
{
	int size= problem->CorrectSolutionSize();
	Solution sol(new double[size],size);
	sol.Set(individual.GetGenes(),geneSize);
	
	return problem->GetQuality(sol);
}

CDiffEvol::CDiffEvol(IProblem* prob, float crossProb, float diffWeight, int populationSize, float timeInSec)
{
	problem = prob;
	geneSize = problem->CorrectSolutionSize();
	if(diffWeight>=0 && diffWeight<=1){
		this->diffWeight=diffWeight;
	}else{
		this->diffWeight=DEFAULT_DIFF_WEIGHT;
	}
	this->populationSize=populationSize;
	this->timeInSec=timeInSec;
	if(crossProb>=0 && crossProb<=1)
	{
		crossProbability=crossProb;
	}else
	{
		crossProbability=DEFAULT_CROSS_PROBABILITY;
	}
	quality=0;
}
