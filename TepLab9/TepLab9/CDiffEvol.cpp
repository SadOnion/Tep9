#include "CDiffEvol.h"
#include "Timer.h"

#include "Vector4.h"
#include "Solution.h"
Individual CDiffEvol::GetRandomIndividual()
{
	Individual individual(geneSize);
	Vector4 sizes = problem.Sizes();
	int index=0;
	for (int i = 0; i < sizes.x; i++)
	{
		double power = problem.GetSupplier(i)->GetPower();
		for (int j = 0; j < sizes.y; j++)
		{
			double random = rand.Range(problem.GetSupplier(i)->GetMin(j),problem.GetSupplier(i)->GetMax(j));
			if(power-random <0&& power >0)
			{
				random = rand.Range(problem.GetSupplier(i)->GetMin(j),power);
				
			}
			individual[index++] = random;
			power-=random;
			if(power<0)break;

		}
	}
	for (int i = 0; i < sizes.y; i++)
	{
		double power = problem.GetFactory(i)->GetPower();
		for (int j = 0; j < sizes.z; j++)
		{

			double random = rand.Range(problem.GetFactory(i)->GetMin(j),problem.GetFactory(i)->GetMax(j));
			if(power-random <0 && power >0)
			{
				random = rand.Range(problem.GetFactory(i)->GetMin(j),power);
				
			}
			individual[index++] = random;
			power-=random;
			if(power<0)break;
		}
	}
	for (int i = 0; i < sizes.z; i++)
	{
		double power = problem.GetWarehouse(i)->GetPower();
		for (int j = 0; j < sizes.r; j++)
		{

			double random = rand.Range(problem.GetWarehouse(i)->GetMin(j),problem.GetWarehouse(i)->GetMax(j));
			if(power-random <0&& power >0)
			{
				random = rand.Range(problem.GetWarehouse(i)->GetMin(j),power);
				
			}
			individual[index++] = random;
			power-=random;
			if(power<0)break;

		}
	}
	return individual;
}

Individual CDiffEvol::GetRandomIndividualFromPopulation(Population& population)
{
	int randomIndex = rand.Range(0,population.GetSize()-1);
	return population[randomIndex];
}

Solution CDiffEvol::GetBestSolution(Population& population)
{
	Vector4 vec = problem.Sizes();
	Solution sol(vec);
	sol.Set(population[0].GetGenes(),geneSize);
	double best=problem.GetQuality(sol);
	int bestIndex=0;
	for (int i = 1; i < population.GetSize(); i++)
	{
		sol.Set(population[i].GetGenes(),geneSize);
		double next = problem.GetQuality(sol);
		
		if(next > best){
		best = next;
		bestIndex = i;
		}
	}
	if(bestIndex!=0)sol.Set(population[bestIndex].GetGenes(),geneSize);
	std::cout<<"Q:"<<problem.GetQuality(sol)<<"\n";
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
	Vector4 sizes = problem.Sizes();
	int sf = sizes.x*sizes.y;
	int fw = sf+sizes.y*sizes.z;
	if(index < sf)
	{
		double min = problem.GetSupplier((int)std::floorf(index/sizes.y))->GetMin(index%(int)sizes.y);
		double max = problem.GetSupplier((int)std::floorf(index/sizes.y))->GetMax(index%(int)sizes.y);
		if(newVal>=min && newVal<=max)return true;
		return false;
	}else if(index < fw){
		double min = problem.GetFactory((int)std::floorf(index-sf)/sizes.z)->GetMin(index%(int)sizes.z);
		double max = problem.GetFactory((int)std::floorf(index-sf)/sizes.z)->GetMax(index%(int)sizes.z);
		if(newVal>=min && newVal<=max)return true;
		return false;
	}else
	{
		double min = problem.GetWarehouse((int)std::floorf(index-fw)/sizes.r)->GetMin(index%(int)sizes.r);
		double max = problem.GetWarehouse((int)std::floorf(index-fw)/sizes.r)->GetMax(index%(int)sizes.r);
		if(newVal>=min && newVal<=max)return true;
		return false;
	}
	return false;
	
}

CDiffEvol::CDiffEvol(CMscnProblem& prob, float crossProb)
{
	SetNewProblem(prob);
	
	if(crossProb>=0 && crossProb<=1)
	{
		crossProbability=crossProb;
	}else
	{
		crossProbability=DEFAULT_CROSS_PROBABILITY;
	}
	diffWeight=DEFAULT_DIFF_WEIGHT;
	quality=0;
}





Solution CDiffEvol::Search(double timeInSec,int populationSize)
{
	
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
	quality = problem.GetQuality(solution);
	return std::move(solution);
}

double CDiffEvol::Fitness(Individual& individual)
{
	Vector4 vec = problem.Sizes();
	Solution sol(vec);
	sol.Set(individual.GetGenes(),geneSize);
	
	return problem.GetQuality(sol);
}
