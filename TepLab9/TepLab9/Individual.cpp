#include "Individual.h"
#include <iostream>



Individual::Individual()
{
	size=DEFAULT_SIZE;
	genes = new double[DEFAULT_SIZE];
	for (int i = 0; i < size; i++)
	{
		genes[i]=0;
	}
}

Individual::Individual(double* genes,int size)
{
	this->genes = new double[size];
	for (int i = 0; i < size; i++)
	{
		this->genes[i] = genes[i];
	}
	this->size = size;
}

Individual::Individual(int geneSize)
{
	size=geneSize;
	genes = new double[size];
	for (int i = 0; i < size; i++)
	{
		genes[i]=0;
	}
}

Individual::Individual(const Individual& other)
{
	size = other.size;
	genes = new double[size];
	for (int i = 0; i < size; i++)
	{
		genes[i] = other.genes[i];
	}
}

bool Individual::Equals(Individual& ind)
{
	for (int i = 0; i < size; i++)
	{
		if(genes[i] != ind[i]) return false;
	}
	return true;
}
Individual Individual::operator=(const Individual& other)
{
	size = other.size;
	delete genes;
	genes = new double[size];
	for (int i = 0; i < size; i++)
	{
		genes[i] = other.genes[i];
	}
	return *this;
}

void Individual::Print()
{
	for (int i = 0; i < size; i++)
	{
		std::cout<<genes[i]<<" ; ";
	}
	std::cout<<"Size"<<size<<"\n";
}
