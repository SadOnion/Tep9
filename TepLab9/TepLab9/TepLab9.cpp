#include "CMscnProblem.h"
#include <iostream>
#include "Serializer.h"
#include "Matrix.h"
int main()
{
	CMscnProblem problem(2,3,3,5);
	problem.SetCostFromFactoryTo(0,0,1);
	problem.SetCostFromFactoryTo(0,1,1);
	problem.SetCostFromFactoryTo(0,2,1);

	problem.SetCostFromFactoryTo(1,0,1);
	problem.SetCostFromFactoryTo(1,1,1);
	problem.SetCostFromFactoryTo(1,2,1);

	problem.SetCostFromSupplierTo(0,0,1);
	problem.SetCostFromWarehouseTo(0,0,1);
	
	std::cout<< problem.GetQuality(new double[30]{1,2,3,4,5,6,7,8,9,10,0,0,0,0,0,0,17,18,19,20,21,22,23,24,25,26,27,28,29,30});
	

	CMscnProblem fuck(1,1,1,1);

	fuck.GetSupplier(0)->SetProductivePower(100);
	fuck.GetSupplier(0)->SetCostTo(0,3);
	fuck.GetSupplier(0)->SetContractCost(10);

	fuck.GetFactory(0)->SetProductivePower(50);
	fuck.GetFactory(0)->SetCostTo(0,4);
	fuck.GetFactory(0)->SetContractCost(10);

	fuck.GetWarehouse(0)->SetProductivePower(10.5);
	fuck.GetWarehouse(0)->SetCostTo(0,1);
	fuck.GetWarehouse(0)->SetContractCost(10);

	fuck.GetShop(0)->maxProductivePower = 100;
	fuck.GetShop(0)->income = 100;

	std::cout<<"\n to jest powinno byc:"<<fuck.GetQuality(new double[3]{1,1,1});
	


}



