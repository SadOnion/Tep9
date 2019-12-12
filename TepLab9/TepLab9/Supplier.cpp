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

double Supplier::TotalTransportCost()
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




double Supplier::GetContractCost()
{
	return contractCost;
}

double Supplier::TransportCostToDestination(int j)
{
	return deliveryCost[j]*amountOfResourceOrdered[j];
}

void Supplier::ResizeOutput(int newSize)
{
	deliveryCost.resize(newSize);
	amountOfResourceOrdered.resize(newSize);
}
