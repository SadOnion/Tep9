#pragma once
#include "Supplier.h"
#include "Shop.h"
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

		double CalculateContractCostFrom(std::vector<Supplier*> costToCalculate,int outputSize);
		void BadInput();

		bool ConstrainsSatisfied(double* solution);
		void ResizeSupplierVector(std::vector<Supplier*> &vec,int size);
public:
	~CMscnProblem();
	CMscnProblem(int supplierSize,int factorySize,int warehouseSize,int shopSize);
	double GetQuality(double* solution);
	bool AssumptionsCorrect();

	void SetSuppliersSize(int size);
	void SetFactoriesSize(int size);
	void SetWarehousesSize(int size);
	void SetShopsSize(int size);


	Supplier* GetSupplier(int index){return suppliers.at(index);}
	Supplier* GetWarehouse(int index){return warehouses.at(index);}
	Supplier* GetFactory(int index){return factories.at(index);}
	Shop* GetShop(int index){return shops.at(index);}

};


