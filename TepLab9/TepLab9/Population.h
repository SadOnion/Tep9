#pragma once
#include "Individual.h"

class Population
{
private:
	Individual* individuals;
	int size;
public:
	Population(int size){this->size=size;individuals=new Individual[size];}
	Population(int size,int geneSize);
	Individual& operator[] (int index){if(index>=0&&index<size)return individuals[index];}
	void SetIndividualsGeneSize(int size);
	int GetSize(){return size;}
};

