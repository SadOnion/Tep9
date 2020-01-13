#pragma once
class Individual
{
private:
	const int DEFAULT_SIZE=5;
	double* genes;
	int size;
public:
	Individual();
	Individual(double* genes,int size);
	Individual(int geneSize);
	Individual(const Individual& other);
	~Individual(){if(genes != nullptr){delete genes;}}
	double& operator[] (int index){if(index<size&&index>=0)return genes[index];}
	void ChangeGenesSize(int newSize){if(newSize>0){delete genes;genes=new double[newSize];size=newSize;}}
	bool Equals(Individual& ind);
	int GetSize(){return size;}
	double* GetGenes(){return genes;}
	Individual operator=(const Individual& other);
	void Print();
};

