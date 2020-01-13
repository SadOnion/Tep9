#include "CMscnProblem.h"
#include <iostream>
#include "Tester.h"
#include "CRandom.h"
#include <ctime>
#include "CRandomSearch.h"
#include "Timer.h"
#include "Individual.h"
#include "CDiffEvol.h"
#include <windows.h>
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
	std::string testFile = "TestData/CalculatedTest3.txt";
	Tester test;
	CMscnProblem cProblem = test.LoadProblem(testFile);
	CRandomSearch rs(&cProblem,2);
	ISolution* sol = rs.Search();
	
	std::cout << "Q:" << cProblem.GetQuality(*sol);
}
void Interfaces(){
	std::string testFile = "TestData/CalculatedTest1.txt";
	Tester test;
	CMscnProblem problem = test.LoadProblem(testFile);
	
	CDiffEvol evolution(new CMscnProblem(std::move(problem)),.35,.5,400,5);
	ISolution* s1 = evolution.Search();
	std::cout<< "Q1:"<<evolution.GetQuality();
}
int main()
{


	Timer timer;
	timer.Start();



	std::string testFile = "TestData/CalculatedTest3.txt";
	Tester test;
	CMscnProblem cProblem = test.LoadProblem(testFile);
	Solution sol(cProblem.CorrectRandomSolution(),cProblem.CorrectSolutionSize());
	cProblem.PrintInfo();
	sol.Print();
	std::cout<<cProblem.ConstrainsSatisfied(sol)<<"\n";
	cProblem.GetQualityAndFixSolution(sol);
	std::cout<<cProblem.ConstrainsSatisfied(sol)<<"\n";

	sol.Print();




	IProblem* problem = new CMscnProblem(std::move(cProblem));
	ISolution* solution;
	IOptimizer* optimizer = new CRandomSearch(problem,2);

	std::cout<<"T:"<<timer.TimeFromStart();

	solution = optimizer->Search();
	std::cout << "RandomSearch Quality:" << problem->GetQuality(*solution);
	delete optimizer;
	delete solution;
	optimizer = new CDiffEvol(problem,.25,.4,400,3.0);
	solution = optimizer->Search();
	std::cout << "DiffEvolution Quality:" << problem->GetQuality(*solution);

	std::cout<<"T:"<<timer.TimeFromStart();

	
}





