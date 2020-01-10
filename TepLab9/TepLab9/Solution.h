#pragma once
#include "Vector4.h"
#include <iostream>
class Solution
{
private:
	double* solution;
	int size;
	int suppliersSize;
	int factoriesSize;
	int warehousesSize;
	int shopsSize;
public:
	~Solution() { delete solution; }
	Solution(Solution&& other);
	Solution(int supSize,int facSize,int warSize,int shopSize);
	Solution(Vector4& sizes);

	int GetSize(){return size;}
	int GetSuppliersSize() { return suppliersSize; }
	int GetFactoriesSize() { return factoriesSize; }
	int GetWarehousesSize() { return warehousesSize; }
	int GetShopsSize() { return shopsSize; }
	void Set(int index,double resourceOrdered);
	void Set(double* newSol, int size);
	double* const GetSolution(){return solution;}
	void Print();
	
	friend class SolutionGenerator;
};

