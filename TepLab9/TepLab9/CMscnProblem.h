#pragma once
#include "Supplier.h"
#include "Shop.h"
#include "Solution.h"
#include <string>

#define BAD_SOLUTION 0.34041
#pragma warning(disable:4996)
class CMscnProblem
{
	private:
		std::vector<Supplier*> suppliers;
		std::vector<Supplier*> factories;
		std::vector<Supplier*> warehouses;

		std::vector<Shop*> shops;

		double CalculateTransportCost();

		double CalculateContractCost();

		double CalculateIncomeFromShops();

		double CalculateContractCostFrom(std::vector<Supplier*>& costToCalculate,int outputSize);
		

		bool AssumptionsCorrect();
		void ResizeSupplierVector(std::vector<Supplier*> &vec,int size);
		void ApplySolution(double* solution);
public:
	
	CMscnProblem(){}
	CMscnProblem(int supplierSize,int factorySize,int warehouseSize,int shopSize);
	double GetQuality(Solution solution);

	bool ConstrainsSatisfied(Solution solution);
	void SetSuppliersSize(int size);
	void SetFactoriesSize(int size);
	void SetWarehousesSize(int size);
	void SetShopsSize(int size);

	Supplier* GetSupplier(int index){return suppliers.at(index);}
	Supplier* GetWarehouse(int index){return warehouses.at(index);}
	Supplier* GetFactory(int index){return factories.at(index);}
	Shop* GetShop(int index){return shops.at(index);}

	bool SaveProblem(std::string fileName);
	void PrintInfo();
};


