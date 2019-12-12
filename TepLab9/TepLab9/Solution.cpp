#include "Solution.h"

Solution::Solution(int supSize, int facSize, int warSize, int shopSize)
{
	size = supSize+facSize+warSize;
	solution = new double[size];
}

void Solution::Set(int index, double resourceOrdered)
{
	solution[index] = resourceOrdered;
}
