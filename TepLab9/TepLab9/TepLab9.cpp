#include "CMscnProblem.h"
#include <iostream>
#include "Serializer.h"
#include "Matrix.h"
#include "Tester.h"
#pragma warning(disable:4996)

void ShowResults(Tester &test,std::string testFile)
{
	CMscnProblem p = test.LoadProblem(testFile+".txt");
	Solution s = test.LoadSolution(testFile+"S.txt");
	std::cout<<testFile<<"\n Quality:"<<p.GetQuality(s)<<" Constrains:"<<p.ConstrainsSatisfied(s)<<"\n";
}
void ShowResults(Tester &test,std::string testFile,double Q,bool C)
{
	CMscnProblem p = test.LoadProblem(testFile+".txt");
	Solution s = test.LoadSolution(testFile+"S.txt");
	std::cout<<testFile<<"\n Quality:"<<p.GetQuality(s)<<" Constrains:"<<p.ConstrainsSatisfied(s)<<"\n"<<"Expected Q:"<<Q<<" C:"<<C<<"\n";
}
int main()
{
	
	std::cout.setf(std::ios::boolalpha);
	std::string testFile = "TestData/baseTest";
	Tester test;
	
	ShowResults(test,testFile,62,true);
	testFile = "TestData/CalculatedTest";
	ShowResults(test,testFile,9580,true);
	testFile ="TestData/CalculatedTest1";
	ShowResults(test,testFile,-800,true);
	
	testFile ="TestData/CalculatedTest2";
	ShowResults(test,testFile,-650,false);
	
	testFile ="TestData/CalculatedTest3";
	ShowResults(test,testFile,245,false);
	testFile ="TestData/ZeroTest";
	ShowResults(test,testFile,0,true);
	testFile ="TestData/ZeroTest1";
	ShowResults(test,testFile,-3,false);
	testFile ="TestData/RandomTest1";
	ShowResults(test,testFile);
	testFile ="TestData/RandomTest2";
	ShowResults(test,testFile);
	testFile ="TestData/RandomTest3";
	ShowResults(test,testFile);
	testFile ="TestData/RandomTest4";
	ShowResults(test,testFile);
	
	test.CreateRandomTest();
}





