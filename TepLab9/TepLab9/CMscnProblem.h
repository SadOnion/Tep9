#pragma once
#include "Supplier.h"
#include "Shop.h"
#include "Solution.h"
#include <string>
#include "CRandom.h"
#include "CProblem.h"

#define BAD_SOLUTION 0.34041
#pragma warning(disable:4996)
class CMscnProblem : public IProblem
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
		bool ApplySolution(double* solution);
		void FixSolution(double* solution);
		
public:
	~CMscnProblem();
	CMscnProblem(){}
	CMscnProblem(CMscnProblem&& other);
	CMscnProblem(int supplierSize,int factorySize,int warehouseSize,int shopSize);
	CMscnProblem& operator=(CMscnProblem&& other);
	
	bool ConstrainsSatisfied(Solution& solution);
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
	void Take(CMscnProblem& other);

	
	Vector4 Sizes();




	
	double GetQualityAndFixSolution(ISolution& solution);
	// Odziedziczono za poœrednictwem elementu IProblem
	 double GetQuality(ISolution& solution) override;

	 int CorrectSolutionSize() override;

	void GenerateInstance(unsigned int seed);

	
	 bool CorrectValue(double newVal, int index) override;


	
	double* CorrectRandomSolution() override;

};


