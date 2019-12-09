#pragma once
#include <vector>

class Supplier
{
private:
	const double DEFAULT_PRODUCTIVE_POWER=1000;
	const double DEFAULT_CONTRACT_COST=1000;
	std::vector<double> deliveryCost;
	std::vector<double> amountOfResourceOrdered;
	double maxProductivePower;
	double contractCost;
public:
	bool CanProduceEnoughResources();
	Supplier(int outputSize);
	double& CostTo(int i);
	double TotalProductionCost();
	double TotalResourceOutput();
	double& ResourceOrderedFrom(int i);
	double GetContractCost();
	void ResizeOutput(int newSize);
};

