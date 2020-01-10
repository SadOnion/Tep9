#include "SolutionGenerator.h"

void SolutionGenerator::GenerateRandomSolution(CMscnProblem& prob,Solution& sol)
{
	CRandom rand;
	int index = 0;
	for (int i = 0; i < sol.suppliersSize; i++)
	{
		for (int j = 0; j < sol.factoriesSize; j++)
		{
			sol.Set(index, rand.Range(prob.GetSupplier(i)->GetMin(j), prob.GetSupplier(i)->GetMax(j)));
			index++;
		}
	}
	for (int i = 0; i < sol.factoriesSize; i++)
	{
		for (int j = 0; j < sol.warehousesSize; j++)
		{
			sol.Set(index, rand.Range(prob.GetFactory(i)->GetMin(j), prob.GetFactory(i)->GetMax(j)));
			index++;
		}
	}
	for (int i = 0; i < sol.warehousesSize; i++)
	{
		for (int j = 0; j < sol.shopsSize; j++)
		{
			sol.Set(index, rand.Range(prob.GetWarehouse(i)->GetMin(j), prob.GetWarehouse(i)->GetMax(j)));
			index++;
		}
	}
	
}
