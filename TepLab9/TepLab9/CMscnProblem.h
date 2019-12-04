#pragma once

class CMscnProblem
{
	private:
		double** costFromSupplierToFactory;
		double** costFromFactoryToWarehouse;
		double** costFromWarehouseToShop;

		double** productCountFromSupplierToFactory;
		double** productCountFromFactoryToWarehouse;
		double** productCountFromWarehouseToShop;

		double* supplierContractCost;
		double* factoryContractCost;
		double* warehouseContractCost;

		double* supplierMaxProductivePower;
		double* factoryMaxProductivePower;
		double* warehouseMaxProductivePower;
		double* shopMaxProductivePower;
		
		double* incomeFromShop;

		int suppliers;
		int factories;
		int warehouses;
		int shops;

		double CalculateTransportCost();

		double CalculateContractCost();

		double CalculateIncomeFromShops();

		double SingleIncomeFromShop(int i, int j);

		double SingleTransportCostFromSupplierToFactory(int i,int j);
		double SingleTransportCostFromFactoryToWarehouse(int i,int j);
		double SingleTransportCostFromWarehouseToShop(int i,int j);



		void BadInput();

		bool AssumptionsCorrect();
		bool ConstrainsSatisfied(double* solution);
public:
	CMscnProblem();
	CMscnProblem(int supplierSize,int factorySize,int warehouseSize,int shopSize);
	double GetQuality(double* solution);

	void SetNewCostFromSupplierToFactory(double newValue,int i,int j);
	void SetNewCostFromFactoryToWarehouse(double newValue,int i,int j);
	void SetNewCostFromWarehouseToShop(double newValue,int i,int j);

	void SetNewCostFromSupplierToFactory(double** newCostArray);
	void SetNewCostFromFactoryToWarehouse(double** newCostArray);
	void SetNewCostFromWarehouseToShop(double** newCostArray);

	void SetSupplierProductivePower(int index,double power);
	void SetFactoryProductivePower(int index,double power);
	void SetWarehouseProductivePower(int index,double power);
	void SetShopProductivePower(int index,double power);

	void SetSupplierProductivePower(double* powers);
	void SetFactoryProductivePower(double* powers);
	void SetWarehouseProductivePower(double* powers);
	void SetShopProductivePower(double* powers);

	void SetShopsIncome(double* income);
	static double SingleTransportCost(double ** costFromTo, double ** productFromTo, int i, int j);
};


