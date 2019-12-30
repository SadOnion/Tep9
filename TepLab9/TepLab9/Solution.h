#pragma once
#include <cstddef>
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
	int GetSize(){return size;}
	int GetSuppliersSize() { return suppliersSize; }
	int GetFactoriesSize() { return factoriesSize; }
	int GetWarehousesSize() { return warehousesSize; }
	int GetShopsSize() { return shopsSize; }
	void Set(int index,double resourceOrdered);
	double* const GetSolution(){return solution;}
	void Print();
};

