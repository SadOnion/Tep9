#pragma once
class Solution
{
private:
	double* solution;
	int size;
public:
	Solution(int supSize,int facSize,int warSize,int shopSize);
	int GetSize(){return size;}
	void Set(int index,double resourceOrdered);
	double* const GetSolution(){return solution;}
	void Print();
};

