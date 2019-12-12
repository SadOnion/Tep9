#include "CMscnProblem.h"
#include "Utils.h"
#include <iostream>

double CMscnProblem::CalculateTransportCost()
{
	double sum=0;
	
	for (int i = 0; i < suppliers.size(); i++)
	{
		sum+=suppliers.at(i)->TotalTransportCost();
	}
	for (int i = 0; i < factories.size(); i++)
	{
		sum+=factories.at(i)->TotalTransportCost();
	}
	for (int i = 0; i < warehouses.size(); i++)
	{
		sum+=warehouses.at(i)->TotalTransportCost();
	}
	
	return sum;
}

double CMscnProblem::CalculateContractCost()
{
	double sum=0;
	
	sum+= CalculateContractCostFrom(suppliers,factories.size());
	sum+= CalculateContractCostFrom(factories,warehouses.size());
	sum+= CalculateContractCostFrom(warehouses,shops.size());

	return sum;
}

double CMscnProblem::CalculateIncomeFromShops()
{
	double sum=0;
	for (int i = 0; i < warehouses.size(); i++)
	{
		for (int j = 0; j < shops.size(); j++)
		{
			sum+= warehouses.at(i)->GetResourceOrderedFrom(j)*shops.at(j)->income;
		}
	}
	return sum;
}

double CMscnProblem::CalculateContractCostFrom(std::vector<Supplier*> costToCalculate,int outputSize)
{
	double sum=0;
	double innerSum=0;
	for (int i = 0; i < costToCalculate.size(); i++)
	{
		innerSum=0;
		for (int j = 0; j <  outputSize; j++)
		{
			innerSum+= costToCalculate.at(i)->GetResourceOrderedFrom(j);
		}
		sum+= Utils::Signum(innerSum)* costToCalculate.at(i)->GetContractCost();
	}
	return sum;
}



bool CMscnProblem::AssumptionsCorrect()
{
	for (int i = 0; i < suppliers.size(); i++)
	{
		if(suppliers.at(i)->CanProduceEnoughResources() == false) return false;
	}

	for (int i = 0; i < factories.size(); i++)
	{
		if(factories.at(i)->CanProduceEnoughResources() == false) return false;
	}

	for (int i = 0; i < warehouses.size(); i++)
	{
		if(warehouses.at(i)->CanProduceEnoughResources() == false) return false;
	}

	for (int j = 0; j < factories.size(); j++)
	{
		double sum=0;
		for (int i = 0; i < suppliers.size(); i++)
		{
			sum+=suppliers.at(i)->GetResourceOrderedFrom(j);
		}
		if(sum < factories.at(j)->TotalResourceOutput()) return false;
	}

	for (int j = 0; j < warehouses.size(); j++)
	{
		double sum=0;
		for (int i = 0; i < factories.size(); i++)
		{
			sum+=factories.at(i)->GetResourceOrderedFrom(j);
		}
		
		if(sum< warehouses.at(j)->TotalResourceOutput()) return false;
	}

	return true;
}

bool CMscnProblem::ConstrainsSatisfied(double* solution)
{
	return true;
}

void CMscnProblem::ResizeSupplierVector(std::vector<Supplier*> &vec,int size)
{
	if(vec.size() < size)
	{
		for (int i = size; i <vec.size() ; i++)
		{
			delete vec.at(i);
		}
	}
	vec.resize(size);
}


CMscnProblem::~CMscnProblem()
{
	// delete memory
}

CMscnProblem::CMscnProblem(int supplierSize, int factorySize, int warehouseSize, int shopSize)
{
	suppliers.resize(supplierSize);
	factories.resize(factorySize);
	warehouses.resize(warehouseSize);
	shops.resize(shopSize);

	for (int i = 0; i < supplierSize; i++)
	{
		suppliers.at(i) = new Supplier(factorySize);
	}
	for (int i = 0; i < factorySize; i++)
	{
		factories.at(i) = new Supplier(warehouseSize);
	}
	for (int i = 0; i < warehouseSize; i++)
	{
		warehouses.at(i) = new Supplier(shopSize);
	}
	for (int i = 0; i < shopSize; i++)
	{
		shops.at(i) = new Shop();
	}
	
}

double CMscnProblem::GetQuality(double* solution)
{
	
	if(ConstrainsSatisfied(solution))
	{
		for (int i = 0; i < suppliers.size(); i++)
		{
			for (int j = 0; j < factories.size(); j++)
			{
				suppliers.at(i)->SetResourceOrderedFrom(j,solution[i*suppliers.size()+j]);
			}
		}
		int index = suppliers.size()*factories.size();
		for (int i = 0; i < factories.size(); i++)
		{
			for (int j = 0; j < warehouses.size(); j++)
			{
				factories.at(i)->SetResourceOrderedFrom(j,solution[index+i*factories.size()+j]);
			}
		}
		index = factories.size()*warehouses.size();
		for (int i = 0; i < warehouses.size(); i++)
		{
			for (int j = 0; j < shops.size(); j++)
			{
				warehouses.at(i)->SetResourceOrderedFrom(j, solution[index +i*warehouses.size()+j]);
			}
		}
		
		double quality = CalculateIncomeFromShops() - CalculateContractCost() - CalculateTransportCost();
		return quality;
	}
	return -9090;
}

void CMscnProblem::SetSuppliersSize(int size)
{
	int oldSize=suppliers.size();
	ResizeSupplierVector(suppliers,size);
	if(oldSize < size)
	{
		for (int i = oldSize; i < size; i++)
		{
			suppliers.at(i) = new Supplier(factories.size());
		}
	}

	
}

void CMscnProblem::SetFactoriesSize(int size)
{
	int oldSize=factories.size();
	ResizeSupplierVector(factories,size);
	if(oldSize < size)
	{
		for (int i = oldSize; i < size; i++)
		{
			factories.at(i) = new Supplier(warehouses.size());
		}
	}

	for (int i = 0; i < suppliers.size(); i++)
	{
		suppliers.at(i)->ResizeOutput(factories.size());
	}
	

}


void CMscnProblem::SetWarehousesSize(int size)
{
	int oldSize=warehouses.size();
	ResizeSupplierVector(warehouses,size);
	if(oldSize < size)
	{
		for (int i = oldSize; i < size; i++)
		{
			warehouses.at(i) = new Supplier(shops.size());
		}
	}
	
	for (int i = 0; i < factories.size(); i++)
	{
		factories.at(i)->ResizeOutput(warehouses.size());
	}

}

void CMscnProblem::SetShopsSize(int size)
{
	shops.resize(size);
	for (int i = 0; i < warehouses.size(); i++)
	{
		warehouses.at(i)->ResizeOutput(shops.size());
	}
}

void CMscnProblem::PrintInfo()
{
	std::cout<<"Suppliers:"<<suppliers.size()<<"\n"<<"Factories:"<<factories.size()<<"\n"<<"Warehouses:"<<warehouses.size()<<"\n"<<"Shops:"<<shops.size()<<"\n";
	std::cout<<"Suppliers powers:";
	for (int i = 0; i < suppliers.size(); i++)
	{
		std::cout<<suppliers.at(i)->maxProductivePower<<"<->"<<suppliers.at(i)->contractCost<<" ";
	}
	std::cout<<"\n Factories powers:";
	for (int i = 0; i < factories.size(); i++)
	{
		std::cout<<factories.at(i)->maxProductivePower<<"<->"<<factories.at(i)->contractCost<<" ";
	}
	std::cout<<"\n Warehouses powers:";
	for (int i = 0; i < warehouses.size(); i++)
	{
		std::cout<<warehouses.at(i)->maxProductivePower<<"<->"<<warehouses.at(i)->contractCost<<" ";
	}
	std::cout<<"\n Shops powers:";
	for (int i = 0; i < shops.size(); i++)
	{
		std::cout<<shops.at(i)->maxProductivePower<<"<->"<<shops.at(i)->income<<" ";
	}
	std::cout<<"\n Suppliers Costs:";
	for (int i = 0; i < suppliers.size(); i++)
	{
		for (int j = 0; j < factories.size(); j++)
		{
			
			std::cout<<suppliers.at(i)->deliveryCost.at(j)<<" ";
		}
		std::cout<<std::endl;
	}
	std::cout<<"\n Factories Costs:";
	for (int i = 0; i < factories.size(); i++)
	{
		for (int j = 0; j < warehouses.size(); j++)
		{
			
			std::cout<<factories.at(i)->deliveryCost.at(j)<<" ";
		}
		std::cout<<std::endl;
	}
	std::cout<<"\n Warehouses Costs:";
	for (int i = 0; i < warehouses.size(); i++)
	{
		for (int j = 0; j < shops.size(); j++)
		{
			
			std::cout<<warehouses.at(i)->deliveryCost.at(j)<<" ";
		}
		std::cout<<std::endl;
	}
}




