#include "CMscnProblem.h"
#include <iostream>
#include "Tester.h"
#include "CRandom.h"
#include <ctime>
#include "CRandomSearch.h"
#include "Timer.h"
#include "Individual.h"
#include "CDiffEvol.h"
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
void Tests() {
	std::cout.setf(std::ios::boolalpha);
	std::string testFile = "TestData/baseTest";
	Tester test;

	ShowResults(test, testFile, 62, true);
	testFile = "TestData/CalculatedTest";
	ShowResults(test, testFile, 9580, true);
	testFile = "TestData/CalculatedTest1";
	ShowResults(test, testFile, -800, true);
	testFile = "TestData/CalculatedTest2";
	ShowResults(test, testFile, -650, false);
	testFile = "TestData/CalculatedTest3";
	ShowResults(test, testFile, 245, false);
	testFile = "TestData/ZeroTest";
	ShowResults(test, testFile, 0, true);
	testFile = "TestData/ZeroTest1";
	ShowResults(test, testFile, -3, false);
	testFile = "TestData/RandomTest1";
	ShowResults(test, testFile);
	testFile = "TestData/RandomTest2";
	ShowResults(test, testFile);
	testFile = "TestData/RandomTest3";
	ShowResults(test, testFile);
	testFile = "TestData/RandomTest4";
	ShowResults(test, testFile);
	testFile = "TestData/Test";
	ShowResults(test, testFile, -3.14159e+06, true);
	test.CreateRandomTest();
}
void RandomSearch(){
	std::string testFile = "TestData/CalculatedTest3";
	Tester test;
	Solution s = test.LoadSolution(testFile + "S.txt");
	CRandomSearch rs;
	CMscnProblem prob = rs.Search(s,10);
	prob.PrintInfo();
	std::cout << "Q:" << prob.GetQuality(s);
}
int main()
{
	std::string testFile = "nt";
	Tester test;
	CMscnProblem problem = test.LoadProblem(testFile+".txt");

	CDiffEvol evol(problem,.5);
	Solution sol = evol.Search(30,400);
	sol.Print();
}





