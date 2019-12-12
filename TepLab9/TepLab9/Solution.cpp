#include "Solution.h"
#include <iostream>
Solution::Solution(int supSize, int facSize, int warSize, int shopSize)
{
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
