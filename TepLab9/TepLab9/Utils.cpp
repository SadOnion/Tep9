#include "Utils.h"
#include "CMscnProblem.h"

double Utils::DoubleSum(int sizeI, int sizeJ, double** costFromTo, double* income)
{
	double sum =0;
	for (int i = 0; i < sizeI; i++)
	{
		for (int j = 0; j < sizeJ; j++)
		{
			sum += costFromTo[i][j]*income[j];
		}
	}
	return sum;
}

double Utils::DoubleSumSigma(int sizeI, int sizeJ, double** elem,double* mult)
{
	double sum =0;
	for (int i = 0; i < sizeI; i++)
	{
		double innerSum=0;
		for (int j = 0; j < sizeJ; j++)
		{
			innerSum += elem[i][j];
		}
		if(innerSum > 0)
		{
			sum+=mult[i];
		}
	}
	return sum;
}

double Utils::Sum(int size, double* arr)
{
	double sum=0;
	for (int i = 0; i < size; i++)
	{
		sum+=arr[i];
	}
	return sum;
}

double Utils::Signum(double x)
{
	if(x>0) return 1;
	else return 0;
}

double Utils::Sum(std::vector<Supplier*> sup,double(Supplier::*f(int)))
{
	double sum=0;
	int size = sup.size();
	for (int i = 0; i < size; i++)
	{
		int deliverySize = sup.at(i)->deliveryCost.size();
		for (int j = 0; j < deliverySize; j++)
		{
			sum+= sup.at(i)->*f(j);
		}
	}
	return sum;
}




