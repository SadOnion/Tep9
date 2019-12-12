#pragma once
#include <vector>

class Supplier
{
private:
	const double DEFAULT_PRODUCTIVE_POWER=1000;
	const double DEFAULT_CONTRACT_COST=1000;
	std::vector<double> deliveryCost;
	std::vector<double> amountOfResourceOrdered;
	std::vector<double> min;
	std::vector<double> max;
	double maxProductivePower;
	double contractCost;
public:
	bool CanProduceEnoughResources();
	Supplier(int outputSize);
	void SetCostTo(int index,double cost){ deliveryCost.at(index) = cost;}
	void SetResourceOrderedFrom(int index,double resource){amountOfResourceOrdered.at(index) = resource;}
	void SetProductivePower(double power){maxProductivePower = power;}
	void SetContractCost(double cost){contractCost = cost;}
	void SetMinResource(int index,double minim){min.at(index)=minim;}
	void SetMaxResource(int index,double maxim){min.at(index)=maxim;}
	double GetCostTo(int index,double cost){return deliveryCost.at(index);}
	double GetResourceOrderedFrom(int index){return amountOfResourceOrdered.at(index);}
	double TotalTransportCost();
	double TotalResourceOutput();
	double GetContractCost();
	double TransportCostToDestination(int j);
	void ResizeOutput(int newSize);
	friend class CMscnProblem;
};

