#include "CMscnProblem.h"
#include <iostream>
#include "Serializer.h"
int main()
{
	std::cout<< sizeof(CMscnProblem)<<std::endl;
    CMscnProblem problem(2,3,3,5);
	double supplierPowers[2] = {100,200};
	double factoryPowers[3] = {100,200};
	double warehousePowers[3] = {100,200};
	double shopPowers[5] = {100,200};

	problem.SetSupplierProductivePower(supplierPowers);
	problem.SetFactoryProductivePower(factoryPowers);
	problem.SetWarehouseProductivePower(warehousePowers);
	problem.SetShopProductivePower(shopPowers);

	// S->F cost
	problem.SetNewCostFromSupplierToFactory(100,0,0);
	problem.SetNewCostFromSupplierToFactory(200,0,1);
	problem.SetNewCostFromSupplierToFactory(300,0,2);
	problem.SetNewCostFromSupplierToFactory(400,1,0);
	problem.SetNewCostFromSupplierToFactory(500,1,1);
	problem.SetNewCostFromSupplierToFactory(200,1,2);
	// F->W cost
	problem.SetNewCostFromFactoryToWarehouse(300,0,0);
	problem.SetNewCostFromFactoryToWarehouse(200,0,1);
	problem.SetNewCostFromFactoryToWarehouse(100,0,2);
	problem.SetNewCostFromFactoryToWarehouse(500,1,0);
	problem.SetNewCostFromFactoryToWarehouse(200,1,1);
	problem.SetNewCostFromFactoryToWarehouse(100,1,2);
	problem.SetNewCostFromFactoryToWarehouse(500,2,0);
	problem.SetNewCostFromFactoryToWarehouse(300,2,1);
	problem.SetNewCostFromFactoryToWarehouse(200,2,2);

	// W->S cost
	problem.SetNewCostFromWarehouseToShop(100,0,0);
	problem.SetNewCostFromWarehouseToShop(100,0,1);
	problem.SetNewCostFromWarehouseToShop(100,0,2);
	problem.SetNewCostFromWarehouseToShop(100,0,3);
	problem.SetNewCostFromWarehouseToShop(100,0,4);

	problem.SetNewCostFromWarehouseToShop(100,1,0);
	problem.SetNewCostFromWarehouseToShop(200,1,1);
	problem.SetNewCostFromWarehouseToShop(500,1,2);
	problem.SetNewCostFromWarehouseToShop(200,1,3);
	problem.SetNewCostFromWarehouseToShop(600,1,4);

	problem.SetNewCostFromWarehouseToShop(100,2,0);
	problem.SetNewCostFromWarehouseToShop(200,2,1);
	problem.SetNewCostFromWarehouseToShop(300,2,2);
	problem.SetNewCostFromWarehouseToShop(500,2,3);
	problem.SetNewCostFromWarehouseToShop(3000,2,4);
	
	problem.SetShopsIncome(new double[5]{1000,1000,1000,1000,100});
	std::cout<<problem.GetQuality(new double[30]{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30});

	Serializer s("Data.data");
	s.Save(problem);

	CMscnProblem prob = s.Read();
	int x;
	std::cin>>x;
	std::cout<<std::endl<<prob.GetQuality(new double[30]{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30});
}



