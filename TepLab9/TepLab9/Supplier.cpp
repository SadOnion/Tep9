#include "Supplier.h"

bool Supplier::CanProduceEnoughResources()
{
	return TotalResourceOutput() <= maxProductivePower;
}

Supplier::Supplier(int outputSize)
{
	maxProductivePower=DEFAULT_PRODUCTIVE_POWER;
	contractCost=DEFAULT_CONTRACT_COST;

	deliveryCost.resize(outputSize);
	amountOfResourceOrdered.resize(outputSize);
}

double& Supplier::CostTo(int i)
{
	if(i>deliveryCost.size()) return deliveryCost.at(0); //  ?
	return deliveryCost.at(i);
}

double Supplier::TotalProductionCost()
{
	double sum =0;
	for (int i = 0;  i < deliveryCost.size();  i++)
	{
		sum+=deliveryCost.at(i)*amountOfResourceOrdered.at(i);
	}
	return sum;
}

double Supplier::TotalResourceOutput()
{
	double sum=0;
	for (int i = 0; i < amountOfResourceOrdered.size(); i++)
	{
		sum+= amountOfResourceOrdered.at(i);
	}
	return sum;
}


double& Supplier::ResourceOrderedFrom(int i)
{
	return amountOfResourceOrdered.at(i);
}

double Supplier::GetContractCost()
{
	return contractCost;
}

void Supplier::ResizeOutput(int newSize)
{
	deliveryCost.resize(newSize);
	amountOfResourceOrdered.resize(newSize);
}
