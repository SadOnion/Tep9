#include "Solution.h"


Solution::Solution(Solution&& other)
{
	solution = other.solution;
	other.solution = NULL;
	size = other.size;
	suppliersSize = other.suppliersSize;
	factoriesSize = other.factoriesSize;
	warehousesSize = other.warehousesSize;
	shopsSize = other.shopsSize;
}
Solution::Solution(int supSize, int facSize, int warSize, int shopSize)
{
	suppliersSize = supSize;
	factoriesSize = facSize;
	warehousesSize = warSize;
	shopsSize= shopSize;
	size = supSize*facSize+facSize*warSize+warSize*shopSize;
	solution = new double[size];
}

Solution::Solution(Vector4& sizes)
{
	suppliersSize = sizes.x;
	factoriesSize = sizes.y;
	warehousesSize = sizes.z;
	shopsSize= sizes.z;
	size = suppliersSize*factoriesSize+factoriesSize*warehousesSize+warehousesSize*shopsSize;
	solution = new double[size];
}

Solution::Solution(double* sol, int size)
{
	solution = new double[size];
	for (int i = 0; i < size; i++)
	{
		solution[i] = sol[i];
	}
	this->size=size;
}


void Solution::Set(int index, double resourceOrdered)
{
	solution[index] = resourceOrdered;
}

void Solution::Set(double* newSol,int size)
{
	delete solution;
	solution = new double[size];
	for (int i = 0; i < size; i++)
	{
		solution[i] = newSol[i];
	}
	
}

void Solution::Print()
{
	for (int i = 0; i < size; i++)
	{
		std::cout<<solution[i]<<" ";
	}
}


