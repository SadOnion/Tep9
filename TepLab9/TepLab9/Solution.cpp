#include "Solution.h"
#include <iostream>
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

void Solution::Set(int index, double resourceOrdered)
{
	solution[index] = resourceOrdered;
}

void Solution::Print()
{
	for (int i = 0; i < size; i++)
	{
		std::cout<<solution[i]<<" ";
	}
}
