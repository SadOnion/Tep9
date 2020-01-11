#include "Population.h"

Population::Population(int size, int geneSize)
{
	this->size=size;
	individuals=new Individual[size];
	SetIndividualsGeneSize(geneSize);
}

void Population::SetIndividualsGeneSize(int size)
{
	if(size>0){
		for (int i = 0; i < this->size; i++)
		{
			individuals[i].ChangeGenesSize(size);
		}
	}
}

void Population::Print()
{
	for (int i = 0; i < size; i++)
	{
		individuals[i].Print();
	}
}
