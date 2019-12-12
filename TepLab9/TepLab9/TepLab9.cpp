#include "CMscnProblem.h"
#include <iostream>
#include "Serializer.h"
#include "Matrix.h"
#include "Tester.h"
#pragma warning(disable:4996)
int main()
{
	Tester test;
	test.LoadProblem("testing.txt").PrintInfo();

}



