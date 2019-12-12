#include "Tester.h"
#pragma warning(disable:4996)
CMscnProblem Tester::LoadProblem(std::string fileName)
{/*
	char* buffer;
	long lSize;
	
	fseek (file , 0 , SEEK_END);
	lSize = ftell (file);
	rewind (file);
	buffer = new char[sizeof(char)*lSize];
	fread(buffer,1,lSize,file);*/
	file = fopen(fileName.c_str(),"r");
	int index = 0;
	char str[10];
	float num;
	int inum;
	int suppliersSizes[4];
	for (int i = 0; i < 4; i++)
	{
		fscanf(file,"%s",str);
		fscanf(file,"%i",&inum);
		suppliersSizes[i] = inum;
	}
	CMscnProblem loadedProblem(suppliersSizes[0],suppliersSizes[1],suppliersSizes[2],suppliersSizes[3]);
	// Powers
	fscanf(file,"%s",str); // sd
	for (int i = 0; i < suppliersSizes[0]; i++)
	{
		fscanf(file,"%f",&num);
		loadedProblem.GetSupplier(i)->SetProductivePower(num);
	}
	
	fscanf(file,"%s",str); // sf
	for (int i = 0; i < suppliersSizes[1]; i++)
	{
		fscanf(file,"%f",&num);
		loadedProblem.GetFactory(i)->SetProductivePower(num);
	}
	fscanf(file,"%s",str); // sm
	for (int i = 0; i < suppliersSizes[2]; i++)
	{
		fscanf(file,"%f",&num);
		loadedProblem.GetWarehouse(i)->SetProductivePower(num);
	}

	fscanf(file,"%s",str); // ss
	for (int i = 0; i < suppliersSizes[3]; i++)
	{
		fscanf(file,"%f",&num);
		loadedProblem.GetShop(i)->maxProductivePower=num;
	}

	//TransportCost
	fscanf(file,"%s",str); // cd
	for (int i = 0; i < suppliersSizes[0]; i++)
	{
		for (int j = 0; j < suppliersSizes[1]; j++)
		{
			fscanf(file,"%f",&num);
			loadedProblem.GetSupplier(i)->SetCostTo(j,num);
		}
	}

	fscanf(file,"%s",str); // cf
	for (int i = 0; i < suppliersSizes[1]; i++)
	{
		for (int j = 0; j < suppliersSizes[2]; j++)
		{
			fscanf(file,"%f",&num);
			loadedProblem.GetFactory(i)->SetCostTo(j,num);
		}
	}

	fscanf(file,"%s",str); // cm
	for (int i = 0; i < suppliersSizes[2]; i++)
	{
		for (int j = 0; j < suppliersSizes[3]; j++)
		{
			fscanf(file,"%f",&num);
			loadedProblem.GetWarehouse(i)->SetCostTo(j,num);
		}
	}

	// Contract Cost
	fscanf(file,"%s",str); // ud
	for (int i = 0; i < suppliersSizes[0]; i++)
	{
		fscanf(file,"%f",&num);
		loadedProblem.GetSupplier(i)->SetContractCost(num);
	}

	fscanf(file,"%s",str); // uf
	for (int i = 0; i < suppliersSizes[1]; i++)
	{
		fscanf(file,"%f",&num);
		loadedProblem.GetFactory(i)->SetContractCost(num);
	}

	fscanf(file,"%s",str); // um
	for (int i = 0; i < suppliersSizes[2]; i++)
	{
		fscanf(file,"%f",&num);
		loadedProblem.GetWarehouse(i)->SetContractCost(num);
	}
	//Income
	fscanf(file,"%s",str); // p
	for (int i = 0; i < suppliersSizes[3]; i++)
	{
		fscanf(file,"%f",&num);
		loadedProblem.GetShop(i)->income = num;
	}
	//minmax 
	fscanf(file,"%s",str); // xdminmax
	for (int i = 0; i < suppliersSizes[0]; i++)
	{
		for (int j = 0; j < suppliersSizes[1]; j++)
		{
			fscanf(file,"%f",&num);
			loadedProblem.GetSupplier(i)->SetMinResource(j,num);
			fscanf(file,"%f",&num);
			loadedProblem.GetSupplier(i)->SetMaxResource(j,num);
		}
	}

	fscanf(file,"%s",str); // xfminmax
	for (int i = 0; i < suppliersSizes[1]; i++)
	{
		for (int j = 0; j < suppliersSizes[2]; j++)
		{
			fscanf(file,"%f",&num);
			loadedProblem.GetFactory(i)->SetMinResource(j,num);
			fscanf(file,"%f",&num);
			loadedProblem.GetFactory(i)->SetMaxResource(j,num);
		}
	}

	fscanf(file,"%s",str); // xmminmax
	for (int i = 0; i < suppliersSizes[2]; i++)
	{
		for (int j = 0; j < suppliersSizes[3]; j++)
		{
			fscanf(file,"%f",&num);
			loadedProblem.GetWarehouse(i)->SetMinResource(j,num);
			fscanf(file,"%f",&num);
			loadedProblem.GetWarehouse(i)->SetMaxResource(j,num);
		}
	}
	fclose(file);
	return loadedProblem;
}
