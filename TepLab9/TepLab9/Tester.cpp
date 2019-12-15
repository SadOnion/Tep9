#include "Tester.h"
#include <iostream>
#include <time.h>
#pragma warning(disable:4996)
CMscnProblem Tester::LoadProblem(std::string fileName)
{
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

Solution Tester::LoadSolution(std::string fileName)
{
	file = fopen(fileName.c_str(),"r");
	char str[10];
	int inum;
	float num;
	int suppliersSizes[4];
	for (int i = 0; i < 4; i++)
	{
		fscanf(file,"%s",str);
		fscanf(file,"%i",&inum);
		suppliersSizes[i] = inum;
	}

	Solution loadedSolution(suppliersSizes[0],suppliersSizes[1],suppliersSizes[2],suppliersSizes[3]);

	int index=0;
	fscanf(file,"%s",str); // xd
	for (int i = 0; i < suppliersSizes[0]; i++)
	{
		for (int j = 0; j < suppliersSizes[1]; j++)
		{
			fscanf(file,"%f",&num);
			loadedSolution.Set(index,num);
			index++;
		}
	}

	fscanf(file,"%s",str); // xf
	for (int i = 0; i < suppliersSizes[1]; i++)
	{
		for (int j = 0; j < suppliersSizes[2]; j++)
		{
			fscanf(file,"%f",&num);
			loadedSolution.Set(index,num);
			index++;
		}
	}

	fscanf(file,"%s",str); // xm
	for (int i = 0; i < suppliersSizes[2]; i++)
	{
		for (int j = 0; j < suppliersSizes[3]; j++)
		{
			fscanf(file,"%f",&num);
			loadedSolution.Set(index,num);
			index++;
		}
	}

	fclose(file);
	return loadedSolution;
}

void Tester::SaveProblem(CMscnProblem& problem)
{
	
}

void Tester::CreateRandomTest()
{
	srand (time(NULL));
	file = fopen("RandomTest.txt","w");
	char sups[4] ={'D','F','M','S'};
	int sizes[4];
	fprintf(file,"RandomTest: \nPlik problemu: \n");
	for (int i = 0; i < 4; i++)
	{
		int random = rand() % 5 + 1;
		sizes[i]=random;
		fprintf(file,"%c",sups[i]);
		fprintf(file," ");
		fprintf(file,"%i",random);
		fprintf(file,"\n");
	}
	
	
	// Powers
	fprintf(file,"%s","sd \n"); // sd
	for (int i = 0; i < sizes[0]; i++)
	{
		int random = rand() % 100 + 1;
		fprintf(file,"%i ",random);
	}
	
	fprintf(file,"%s","\nsf \n"); // sf
	for (int i = 0; i < sizes[1]; i++)
	{
		int random = rand() % 100 + 1;
		fprintf(file,"%i ",random);
	}
	fprintf(file,"%s","\nsm \n"); // sm
	for (int i = 0; i < sizes[2]; i++)
	{
		int random = rand() % 100 + 1;
		fprintf(file,"%i ",random);
	}

	fprintf(file,"%s","\nss \n"); // ss
	for (int i = 0; i < sizes[3]; i++)
	{
		int random = rand() % 100 + 1;
		fprintf(file,"%i ",random);
	}

	//TransportCost
	fprintf(file,"%s","\ncd \n"); // cd
	for (int i = 0; i < sizes[0]; i++)
	{
		for (int j = 0; j < sizes[1]; j++)
		{
			int random = rand() % 50 + 1;
			fprintf(file,"%i ",random);
		}
	}

	fprintf(file,"%s","\ncf \n"); // cf
	for (int i = 0; i < sizes[1]; i++)
	{
		for (int j = 0; j < sizes[2]; j++)
		{
			int random = rand() % 50 + 1;
			fprintf(file,"%i ",random);
		}
	}

	fprintf(file,"%s","\ncm \n"); // cm
	for (int i = 0; i < sizes[2]; i++)
	{
		for (int j = 0; j < sizes[3]; j++)
		{
			int random = rand() % 50 + 1;
			fprintf(file,"%i ",random);
		}
	}

	// Contract Cost
	fprintf(file,"%s","\nud \n"); // ud
	for (int i = 0; i < sizes[0]; i++)
	{
		int random = rand() % 100 + 1;
			fprintf(file,"%i ",random);
	}

	fprintf(file,"%s","\nuf \n"); // uf
	for (int i = 0; i < sizes[1]; i++)
	{
		int random = rand() % 100 + 1;
			fprintf(file,"%i ",random);
	}

	fprintf(file,"%s","\num \n"); // um
	for (int i = 0; i < sizes[2]; i++)
	{
		int random = rand() % 100 + 1;
			fprintf(file,"%i ",random);
	}
	//Income
	fprintf(file,"%s","\np \n"); // p
	for (int i = 0; i < sizes[3]; i++)
	{
		int random = rand() % 10 + 1;
			fprintf(file,"%i ",random);
	}
	//minmax 
	fprintf(file,"%s","\nxdminmax \n"); // xdminmax
	for (int i = 0; i < sizes[0]; i++)
	{
		for (int j = 0; j < sizes[1]; j++)
		{
			int random = rand() % 1000;
			fprintf(file,"%i ",random);
			random = rand() % 1000;
			fprintf(file,"%i ",random);
		}
	}

	fprintf(file,"%s","\nxfminmax \n"); // xfminmax
	for (int i = 0; i < sizes[1]; i++)
	{
		for (int j = 0; j < sizes[2]; j++)
		{
			int random = rand() % 1000;
			fprintf(file,"%i ",random);
			random = rand() % 1000;
			fprintf(file,"%i ",random);
		}
	}

	fprintf(file,"%s","\nxmminmax \n"); // xmminmax
	for (int i = 0; i < sizes[2]; i++)
	{
		for (int j = 0; j < sizes[3]; j++)
		{
			int random = rand() % 1000;
			fprintf(file,"%i ",random);
			random = rand() % 1000;
			fprintf(file,"%i ",random);
		}
	}

	///...Solution
	fprintf(file,"\n \nPlik rozwiazania: \n");
	for (int i = 0; i < 4; i++)
	{
		fprintf(file,"%c",sups[i]);
		fprintf(file," ");
		fprintf(file,"%i",sizes[i]);
		fprintf(file,"\n");
	}
	
	fprintf(file,"xd \n"); // xd
	for (int i = 0; i < sizes[0]; i++)
	{
		for (int j = 0; j < sizes[1]; j++)
		{
			int random = rand() % 10;
			fprintf(file,"%i ",random);
		}
	}

	fprintf(file,"\nxf \n"); // xf
	for (int i = 0; i < sizes[1]; i++)
	{
		for (int j = 0; j < sizes[2]; j++)
		{
			int random = rand() % 10;
			fprintf(file,"%i ",random);
		}
	}

	fprintf(file,"\nxm \n"); // xm
	for (int i = 0; i < sizes[2]; i++)
	{
		for (int j = 0; j < sizes[3]; j++)
		{
			int random = rand() % 10;
			fprintf(file,"%i ",random);
		}
	}
	fclose(file);
}
