#include "CMscnProblem.h"
#include "Utils.h"
#include <iostream>

double CMscnProblem::CalculateTransportCost()
{
	double sum=0;
	sum+=Utils::DoubleSum(suppliers,factories,costFromSupplierToFactory,productCountFromSupplierToFactory);
	sum+=Utils::DoubleSum(factories,warehouses,costFromFactoryToWarehouse,productCountFromFactoryToWarehouse);
	sum+=Utils::DoubleSum(warehouses,shops,costFromWarehouseToShop,productCountFromWarehouseToShop);
	return sum;
}

double CMscnProblem::CalculateContractCost()
{
	double sum=0;
	sum+= Utils::DoubleSumSigma(suppliers,factories,productCountFromSupplierToFactory,supplierContractCost);
	sum+= Utils::DoubleSumSigma(factories,warehouses,productCountFromFactoryToWarehouse,factoryContractCost);
	sum+= Utils::DoubleSumSigma(warehouses,shops,productCountFromWarehouseToShop,warehouseContractCost);
	return sum;
}

double CMscnProblem::CalculateIncomeFromShops()
{
	double sum=0;
	sum= Utils::DoubleSum(warehouses,shops,productCountFromWarehouseToShop,incomeFromShop);
	return sum;
}

double CMscnProblem::SingleIncomeFromShop(int i, int j)
{
	return productCountFromWarehouseToShop[i][j]*incomeFromShop[j];
}

void CMscnProblem::SetShopsIncome(double* income)
{
	delete incomeFromShop;
	incomeFromShop = income;
}

double CMscnProblem::SingleTransportCost(double** costFromTo,double** productFromTo,int i,int j)
{
	return costFromTo[i][j]*productFromTo[i][j];
}
double CMscnProblem::SingleTransportCostFromSupplierToFactory(int i, int j)
{
	return costFromSupplierToFactory[i][j]*productCountFromSupplierToFactory[i][j];
}

double CMscnProblem::SingleTransportCostFromFactoryToWarehouse(int i, int j)
{
	return costFromFactoryToWarehouse[i][j]*productCountFromFactoryToWarehouse[i][j];
}

double CMscnProblem::SingleTransportCostFromWarehouseToShop(int i, int j)
{
	return costFromWarehouseToShop[i][j]*productCountFromWarehouseToShop[i][j];
}




bool CMscnProblem::AssumptionsCorrect()
{
	for (int i = 0; i < suppliers; i++)
	{
		double sum = Utils::Sum(factories,productCountFromSupplierToFactory[i]);
		if(sum > supplierMaxProductivePower[i]) return false;
	}

	for (int i = 0; i < factories; i++)
	{
		double sum = Utils::Sum(warehouses,productCountFromFactoryToWarehouse[i]);
		if(sum > factoryMaxProductivePower[i]) return false;
	}

	for (int i = 0; i < warehouses; i++)
	{
		double sum = Utils::Sum(shops,productCountFromWarehouseToShop[i]);
		if(sum > warehouseMaxProductivePower[i]) return false;
	}

	for (int i = 0; i < factories; i++)
	{
		if(Utils::Sum(suppliers,productCountFromSupplierToFactory[i]) < Utils::Sum(factories,productCountFromFactoryToWarehouse[i]))
		{
			return false;
		}

	}

	for (int i = 0; i < warehouses; i++)
	{
		if(Utils::Sum(factories,productCountFromFactoryToWarehouse[i]) < Utils::Sum(shops,productCountFromWarehouseToShop[i]))
		{
			return false;
		}

	}
	return true;
}

bool CMscnProblem::ConstrainsSatisfied(double* solution)
{
	return true;
}

CMscnProblem::CMscnProblem()
{
	suppliers = 1;
	factories=1;
	warehouses=1;
	shops=1;
}

CMscnProblem::CMscnProblem(int supplierSize, int factorySize, int warehouseSize, int shopSize)
{
	suppliers = supplierSize;
	factories=factorySize;
	warehouses=warehouseSize;
	shops=shopSize;

	costFromFactoryToWarehouse = new double*[factories];
	productCountFromFactoryToWarehouse = new double*[factories];
	for (int i = 0; i < factories; i++)
	{
		costFromFactoryToWarehouse[i] = new double[warehouses];
		productCountFromFactoryToWarehouse[i] = new double[warehouses];
	}

	costFromWarehouseToShop = new double*[warehouses];
	productCountFromWarehouseToShop = new double*[warehouses];
	for (int i = 0; i < warehouses; i++)
	{
		costFromWarehouseToShop[i] = new double[shops];
		productCountFromWarehouseToShop[i] = new double[shops];
	}

	costFromSupplierToFactory = new double*[suppliers];
	productCountFromSupplierToFactory = new double*[suppliers];
	for (int i = 0; i < suppliers; i++)
	{
		costFromSupplierToFactory[i] = new double[factories];
		productCountFromSupplierToFactory[i] = new double[factories];;
	}
	incomeFromShop = new double[shops];
	// to delete 
	supplierContractCost = new double[2]{100,100};
	factoryContractCost  =new double[3]{3,34100,100};
	warehouseContractCost = new double[3]{44,100,100};
	
}

double CMscnProblem::GetQuality(double* solution)
{
	
	if(ConstrainsSatisfied(solution))
	{
		for (int i = 0; i < suppliers; i++)
		{
			for (int j = 0; j < factories; j++)
			{
				productCountFromSupplierToFactory[i][j] = solution[i*suppliers+j];
			}
		}
		int index = suppliers*factories;
		for (int i = 0; i < factories; i++)
		{
			for (int j = 0; j < warehouses; j++)
			{
				productCountFromFactoryToWarehouse[i][j] = solution[index+i*factories+j];
			}
		}
		index = factories*warehouses;
		for (int i = 0; i < warehouses; i++)
		{
			for (int j = 0; j < shops; j++)
			{
				productCountFromWarehouseToShop[i][j] = solution[index +i*warehouses+j];
			}
		}
		std::cout<<costFromFactoryToWarehouse[1][1]<<std::endl;
		double quality = CalculateIncomeFromShops() - CalculateContractCost() - CalculateTransportCost();
		return quality;
	}
	return -9090;
}

void CMscnProblem::SetNewCostFromSupplierToFactory(double newValue, int i, int j)
{
	costFromSupplierToFactory[i][j] = newValue;
}

void CMscnProblem::SetNewCostFromFactoryToWarehouse(double newValue, int i, int j)
{
	costFromFactoryToWarehouse[i][j] = newValue;
}

void CMscnProblem::SetNewCostFromWarehouseToShop(double newValue, int i, int j)
{
	costFromWarehouseToShop[i][j] = newValue;
}

void CMscnProblem::SetNewCostFromSupplierToFactory(double** newCostArray)
{
	delete costFromSupplierToFactory;
	costFromSupplierToFactory = newCostArray;
}

void CMscnProblem::SetNewCostFromFactoryToWarehouse(double** newCostArray)
{
	delete costFromFactoryToWarehouse;
	costFromFactoryToWarehouse = newCostArray;
}

void CMscnProblem::SetNewCostFromWarehouseToShop(double** newCostArray)
{
	delete costFromWarehouseToShop;
	costFromWarehouseToShop = newCostArray;
}

void CMscnProblem::SetSupplierProductivePower(int index, double power)
{
	supplierMaxProductivePower[index]=power;
}

void CMscnProblem::SetFactoryProductivePower(int index, double power)
{
	factoryMaxProductivePower[index]=power;

}

void CMscnProblem::SetWarehouseProductivePower(int index, double power)
{
	warehouseMaxProductivePower[index]=power;

}

void CMscnProblem::SetShopProductivePower(int index, double power)
{
	shopMaxProductivePower[index]=power;

}

void CMscnProblem::SetSupplierProductivePower(double* powers)
{
	delete supplierMaxProductivePower;
	supplierMaxProductivePower = powers;
}

void CMscnProblem::SetFactoryProductivePower(double* powers)
{
	delete factoryMaxProductivePower;
	factoryMaxProductivePower=powers;
}

void CMscnProblem::SetWarehouseProductivePower(double* powers)
{
	delete warehouseMaxProductivePower;
	warehouseMaxProductivePower=powers;
}

void CMscnProblem::SetShopProductivePower(double* powers)
{
	delete shopMaxProductivePower;
	shopMaxProductivePower = powers;
}


