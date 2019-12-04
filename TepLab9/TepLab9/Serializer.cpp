#include "Serializer.h"
#include <iostream>
#pragma warning(disable : 4996)f
Serializer::Serializer(std::string fileName)
{
	this->fileName=fileName;
}

void Serializer::Save(CMscnProblem obj)
{
	file = fopen(fileName.c_str(),"w+");
	int result = fprintf(file,(char*)&obj);
	std::cout <<"res:"<<result;
	fclose(file);
}

CMscnProblem& Serializer::Read()
{
	file = fopen(fileName.c_str(),"r");
	CMscnProblem* p = new CMscnProblem(2,3,3,5);
	
	fread(p,sizeof(CMscnProblem),1,file);
	fclose(file);
	return  *p;
}
