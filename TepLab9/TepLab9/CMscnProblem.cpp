#include "CMscnProblem.h"
#include "Utils.h"
#include <iostream>
#include "CRandom.h"
#include "RandomSetter.h"

double CMscnProblem::CalculateTransportCost()
{
	double sum=0;
	
	for (int i = 0; i < suppliers.size(); i++)
	{
		sum+=suppliers.at(i)->TotalTransportCost();
	}
	for (int i = 0; i < factories.size(); i++)
	{
		sum+=factories.at(i)->TotalTransportCost();
	}
	for (int i = 0; i < warehouses.size(); i++)
	{
		sum+=warehouses.at(i)->TotalTransportCost();
	}
	
	return sum;
}

double CMscnProblem::CalculateContractCost()
{
	double sum=0;
	
	sum+= CalculateContractCostFrom(suppliers,factories.size());
	sum+= CalculateContractCostFrom(factories,warehouses.size());
	sum+= CalculateContractCostFrom(warehouses,shops.size());

	return sum;
}

double CMscnProblem::CalculateIncomeFromShops()
{
	double sum=0;
	for (int i = 0; i < warehouses.size(); i++)
	{
		for (int j = 0; j < shops.size(); j++)
		{
			sum+= warehouses.at(i)->GetResourceOrderedFrom(j)*shops.at(j)->income;
		}
	}
	return sum;
}

double CMscnProblem::CalculateContractCostFrom(std::vector<Supplier*> &costToCalculate,int outputSize)
{
	double sum=0;
	double innerSum=0;
	for (int i = 0; i < costToCalculate.size(); i++)
	{
		innerSum=0;
		for (int j = 0; j <  outputSize; j++)
		{
			innerSum+= costToCalculate.at(i)->GetResourceOrderedFrom(j);
		}
		sum+= Utils::Signum(innerSum)* costToCalculate.at(i)->GetContractCost();
	}
	return sum;
}



bool CMscnProblem::AssumptionsCorrect()
{
	for (int i = 0; i < suppliers.size(); i++)
	{
		if(suppliers.at(i)->CanProduceEnoughResources() == false) return false;
	}
	
	for (int i = 0; i < factories.size(); i++)
	{
		if(factories.at(i)->CanProduceEnoughResources() == false) return false;
	}

	

	for (int i = 0; i < warehouses.size(); i++)
	{
		if(warehouses.at(i)->CanProduceEnoughResources() == false) return false;
	}
	
	

	for (int j = 0; j < factories.size(); j++)
	{
		double sum=0;
		for (int i = 0; i < suppliers.size(); i++)
		{
			sum+=suppliers.at(i)->GetResourceOrderedFrom(j);
		}
		if(sum < factories.at(j)->TotalResourceOutput()) return false;
	}
	
	

	for (int j = 0; j < warehouses.size(); j++)
	{
		double sum=0;
		for (int i = 0; i < factories.size(); i++)
		{
			sum+=factories.at(i)->GetResourceOrderedFrom(j);
		}
		
		if(sum< warehouses.at(j)->TotalResourceOutput()) return false;
	}
	
	

	return true;
}

bool CMscnProblem::ConstrainsSatisfied(Solution& solution)
{
	
	int expectedSize = suppliers.size()*factories.size()+factories.size()*warehouses.size()+warehouses.size()*shops.size();
	if(solution.GetSize() != expectedSize) return false;
	double* tab = solution.GetSolution();
	for (int i = 0; i < expectedSize; i++)
	{
		if(tab[i] < 0) return false;
	}
	if (ApplySolution(solution.GetSolution()) == false) return false;
	return AssumptionsCorrect();
}

void CMscnProblem::ResizeSupplierVector(std::vector<Supplier*> &vec,int size)
{
	if(vec.size() < size)
	{
		for (int i = size; i <vec.size() ; i++)
		{
			delete vec.at(i);
		}
	}
	vec.resize(size);
}

bool CMscnProblem::ApplySolution(double* sol)
{
	int index=0;
	bool minmaxCorrect = true;
		for (int i = 0; i < suppliers.size(); i++)
		{
			for (int j = 0; j < factories.size(); j++)
			{
				suppliers.at(i)->SetResourceOrderedFrom(j,sol[index]);
				if (suppliers.at(i)->GetMin(j) > sol[index] || suppliers.at(i)->GetMax(j) < sol[index]) minmaxCorrect = false;
				index++;
			}
		}
		
		for (int i = 0; i < factories.size(); i++)
		{
			for (int j = 0; j < warehouses.size(); j++)
			{
				factories.at(i)->SetResourceOrderedFrom(j,sol[index]);
				if (factories.at(i)->GetMin(j) > sol[index] || factories.at(i)->GetMax(j) < sol[index]) minmaxCorrect = false;
				index++;
			}
		}
		
		for (int i = 0; i < warehouses.size(); i++)
		{
			for (int j = 0; j < shops.size(); j++)
			{
				warehouses.at(i)->SetResourceOrderedFrom(j, sol[index]);
				if (warehouses.at(i)->GetMin(j) > sol[index] || warehouses.at(i)->GetMax(j) < sol[index]) minmaxCorrect = false;
				index++;
			}
		}
		return minmaxCorrect;
}

void CMscnProblem::FixSolution(double* solution)
{
	ApplySolution(solution);
	Vector4 sizes=Sizes();
		CRandom rand;
		int index=0;
		std::vector<double> factoriesInput(factories.size());
		std::vector<double> warehousesInput(warehouses.size());
		for (int i = 0; i < sizes.y; i++)
		{
			for (int j = 0; j < sizes.x; j++)
			{
				factoriesInput.at(i) = GetSupplier(j)->amountOfResourceOrdered.at(i);
			}
		}
		for (int i = 0; i < sizes.z; i++)
		{
			for (int j = 0; j < sizes.y; j++)
			{
				warehousesInput.at(i) = GetFactory(j)->amountOfResourceOrdered.at(i);
			}
		}


		for (int i = 0; i < sizes.x; i++)
		{
			double power = GetSupplier(i)->GetPower();
			for (int j = 0; j < sizes.y; j++)
			{
				double random = rand.Range(GetSupplier(i)->GetMin(j),GetSupplier(i)->GetMax(j));
				if(power-random <0)
				{
					
					double min =GetSupplier(i)->GetMin(j);
					if(power > min){
						random = rand.Range(GetSupplier(i)->GetMin(j),power);
					}else{
						random=0;
					}
					
				}
				solution[index++] = random;
				power-=random;

			}
		}
		for (int i = 0; i < sizes.y; i++)
		{
			double power = GetFactory(i)->GetPower();
			double input =factoriesInput.at(i);
			double upperBounds = power>input? input:power;
			for (int j = 0; j < sizes.z; j++)
			{
				input += GetSupplier(j)->amountOfResourceOrdered.at(i);
				double random = rand.Range(GetFactory(i)->GetMin(j),GetFactory(i)->GetMax(j));
				if(upperBounds-random <0)
				{
					
					double min =GetFactory(i)->GetMin(j);
					if(upperBounds > min){
						random = rand.Range(GetFactory(i)->GetMin(j),upperBounds);
					}else{
						random=0;
					}
					
				}
				solution[index++] = random;
				upperBounds-=random;

			}
		}
		for (int i = 0; i < sizes.z; i++)
		{
			double power = GetWarehouse(i)->GetPower();
			double input =warehousesInput.at(i);
			double upperBounds = power>input? input:power;
			for (int j = 0; j < sizes.r; j++)
			{
				double random = rand.Range(GetWarehouse(i)->GetMin(j),GetWarehouse(i)->GetMax(j));
				if(upperBounds-random <0)
				{
					
					double min =GetWarehouse(i)->GetMin(j);
					if(upperBounds > min){
						random = rand.Range(GetWarehouse(i)->GetMin(j),upperBounds);
					}else{
						random=0;
					}
					
				}
				solution[index++] = random;
				upperBounds-=random;

			}
		}
}



CMscnProblem::~CMscnProblem()
{
	for (int i = 0; i < suppliers.size();i++) {
		if(suppliers.at(i)!=NULL)
		delete suppliers.at(i);
	}
	for (int i = 0; i < factories.size(); i++) {
		if(factories.at(i)!=NULL)

		delete factories.at(i);
	}
	for (int i = 0; i < warehouses.size(); i++) {
		if (warehouses.at(i) != NULL)

		delete warehouses.at(i);
	}
	for (int i = 0; i < shops.size(); i++) {
		if (shops.at(i) != NULL)

		delete shops.at(i);
	}
}




CMscnProblem::CMscnProblem(CMscnProblem&& other)
{
	suppliers = other.suppliers;
	for (int i = 0; i < other.suppliers.size(); i++)
	{
		other.suppliers.at(i) = NULL;
	}
	factories = other.factories;
	for (int i = 0; i < other.factories.size(); i++)
	{
		other.factories.at(i) = NULL;
	}
	warehouses = other.warehouses;
	for (int i = 0; i < other.warehouses.size(); i++)
	{
		other.warehouses.at(i) = NULL;
	}
	shops = other.shops;
	for (int i = 0; i < other.shops.size(); i++)
	{
		other.shops.at(i) = NULL;
	}
}

CMscnProblem::CMscnProblem(int supplierSize, int factorySize, int warehouseSize, int shopSize)
{
	suppliers.resize(supplierSize);
	factories.resize(factorySize);
	warehouses.resize(warehouseSize);
	shops.resize(shopSize);

	for (int i = 0; i < supplierSize; i++)
	{
		suppliers.at(i) = new Supplier(factorySize);
	}
	for (int i = 0; i < factorySize; i++)
	{
		factories.at(i) = new Supplier(warehouseSize);
	}
	for (int i = 0; i < warehouseSize; i++)
	{
		warehouses.at(i) = new Supplier(shopSize);
	}
	for (int i = 0; i < shopSize; i++)
	{
		shops.at(i) = new Shop();
	}
	
}

CMscnProblem& CMscnProblem::operator=(CMscnProblem&& other)
{
	suppliers = other.suppliers;
	for (int i = 0; i < other.suppliers.size(); i++)
	{
		other.suppliers.at(i) = NULL;
	}
	factories = other.factories;
	for (int i = 0; i < other.factories.size(); i++)
	{
		other.factories.at(i) = NULL;
	}
	warehouses = other.warehouses;
	for (int i = 0; i < other.warehouses.size(); i++)
	{
		other.warehouses.at(i) = NULL;
	}
	shops = other.shops;
	for (int i = 0; i < other.shops.size(); i++)
	{
		other.shops.at(i) = NULL;
	}
	return *this;
}



void CMscnProblem::SetSuppliersSize(int size)
{
	int oldSize=suppliers.size();
	ResizeSupplierVector(suppliers,size);
	if(oldSize < size)
	{
		for (int i = oldSize; i < size; i++)
		{
			suppliers.at(i) = new Supplier(factories.size());
		}
	}

	
}

void CMscnProblem::SetFactoriesSize(int size)
{
	int oldSize=factories.size();
	ResizeSupplierVector(factories,size);
	if(oldSize < size)
	{
		for (int i = oldSize; i < size; i++)
		{
			factories.at(i) = new Supplier(warehouses.size());
		}
	}

	for (int i = 0; i < suppliers.size(); i++)
	{
		suppliers.at(i)->ResizeOutput(factories.size());
	}
	

}


void CMscnProblem::SetWarehousesSize(int size)
{
	int oldSize=warehouses.size();
	ResizeSupplierVector(warehouses,size);
	if(oldSize < size)
	{
		for (int i = oldSize; i < size; i++)
		{
			warehouses.at(i) = new Supplier(shops.size());
		}
	}
	
	for (int i = 0; i < factories.size(); i++)
	{
		factories.at(i)->ResizeOutput(warehouses.size());
	}

}

void CMscnProblem::SetShopsSize(int size)
{
	shops.resize(size);
	for (int i = 0; i < warehouses.size(); i++)
	{
		warehouses.at(i)->ResizeOutput(shops.size());
	}
}

bool CMscnProblem::SaveProblem(std::string fileName)
{
	FILE* file = fopen(fileName.c_str(),"w");
	if(file == NULL) return false;
		fprintf(file,"%c ",'D');
		fprintf(file,"%i",suppliers.size());
		fprintf(file,"\n");

		fprintf(file,"%c ",'F');
		fprintf(file,"%i",factories.size());
		fprintf(file,"\n");

		fprintf(file,"%c ",'M');
		fprintf(file,"%i",warehouses.size());
		fprintf(file,"\n");

		fprintf(file,"%c ",'S');
		fprintf(file,"%i",shops.size());
		fprintf(file,"\n");
	
	
	
	// Powers
	fprintf(file,"%s","sd \n"); // sd
	for (int i = 0; i < suppliers.size(); i++)
	{
		//fprintf(file,"%g ",suppliers.at(i)->maxProductivePower);
		fprintf(file, "%g", suppliers.at(i)->maxProductivePower);
		fprintf(file, "%c", ';');
	}
	
	fprintf(file,"%s","\nsf \n"); // sf
	for (int i = 0; i < factories.size(); i++)
	{
		fprintf(file,"%g ",factories.at(i)->maxProductivePower);
	}
	fprintf(file,"%s","\nsm \n"); // sm
	for (int i = 0; i < warehouses.size(); i++)
	{
		fprintf(file,"%g ",warehouses.at(i)->maxProductivePower);
	}

	fprintf(file,"%s","\nss \n"); // ss
	for (int i = 0; i < shops.size(); i++)
	{
		fprintf(file,"%g ",shops.at(i)->maxProductivePower);
	}

	//TransportCost
	fprintf(file,"%s","\ncd \n"); // cd
	for (int i = 0; i < suppliers.size(); i++)
	{
		for (int j = 0; j < factories.size(); j++)
		{
			fprintf(file,"%g ",suppliers.at(i)->deliveryCost.at(j));
		}
	}

	fprintf(file,"%s","\ncf \n"); // cf
	for (int i = 0; i < factories.size(); i++)
	{
		for (int j = 0; j < warehouses.size(); j++)
		{
			fprintf(file,"%g ",factories.at(i)->deliveryCost.at(j));
		}
	}

	fprintf(file,"%s","\ncm \n"); // cm
	for (int i = 0; i < warehouses.size(); i++)
	{
		for (int j = 0; j < shops.size(); j++)
		{
			fprintf(file,"%g ",warehouses.at(i)->deliveryCost.at(j));
		}
	}

	// Contract Cost
	fprintf(file,"%s","\nud \n"); // ud
	for (int i = 0; i < suppliers.size(); i++)
	{
			fprintf(file,"%g ",suppliers.at(i)->contractCost);
	}

	fprintf(file,"%s","\nuf \n"); // uf
	for (int i = 0; i < factories.size(); i++)
	{
			fprintf(file,"%g ",factories.at(i)->contractCost);
	}

	fprintf(file,"%s","\num \n"); // um
	for (int i = 0; i < warehouses.size(); i++)
	{
			fprintf(file,"%g ",warehouses.at(i)->contractCost);
	}
	//Income
	fprintf(file,"%s","\np \n"); // p
	for (int i = 0; i < shops.size(); i++)
	{
			fprintf(file,"%g ",shops.at(i)->income);
	}
	//minmax 
	fprintf(file,"%s","\nxdminmax \n"); // xdminmax
	for (int i = 0; i < suppliers.size(); i++)
	{
		for (int j = 0; j < factories.size(); j++)
		{
			fprintf(file,"%g ",suppliers.at(i)->min.at(j));
			fprintf(file,"%g ",suppliers.at(i)->max.at(j));
		}
	}

	fprintf(file,"%s","\nxfminmax \n"); // xfminmax
	for (int i = 0; i < factories.size(); i++)
	{
		for (int j = 0; j < warehouses.size(); j++)
		{
			fprintf(file,"%g ",factories.at(i)->min.at(j));
			fprintf(file,"%g ",factories.at(i)->max.at(j));
		}
	}

	fprintf(file,"%s","\nxmminmax \n"); // xmminmax
	for (int i = 0; i < warehouses.size(); i++)
	{
		for (int j = 0; j < shops.size(); j++)
		{
			fprintf(file,"%g ",warehouses.at(i)->min.at(j));
			fprintf(file,"%g ",warehouses.at(i)->max.at(j));
		}
	}
	fclose(file);
	return true;
}

void CMscnProblem::PrintInfo()
{
	std::cout<<"Suppliers:"<<suppliers.size()<<"\n"<<"Factories:"<<factories.size()<<"\n"<<"Warehouses:"<<warehouses.size()<<"\n"<<"Shops:"<<shops.size()<<"\n";
	std::cout<<"Suppliers powers:";
	for (int i = 0; i < suppliers.size(); i++)
	{
		std::cout<<suppliers.at(i)->maxProductivePower<<"<->"<<suppliers.at(i)->contractCost<<" ";
	}
	std::cout<<"\n Factories powers:";
	for (int i = 0; i < factories.size(); i++)
	{
		std::cout<<factories.at(i)->maxProductivePower<<"<->"<<factories.at(i)->contractCost<<" ";
	}
	std::cout<<"\n Warehouses powers:";
	for (int i = 0; i < warehouses.size(); i++)
	{
		std::cout<<warehouses.at(i)->maxProductivePower<<"<->"<<warehouses.at(i)->contractCost<<" ";
	}
	std::cout<<"\n Shops powers:";
	for (int i = 0; i < shops.size(); i++)
	{
		std::cout<<shops.at(i)->maxProductivePower<<"<->"<<shops.at(i)->income<<" ";
	}
	std::cout<<"\n Suppliers Costs:";
	for (int i = 0; i < suppliers.size(); i++)
	{
		for (int j = 0; j < factories.size(); j++)
		{
			
			std::cout<<suppliers.at(i)->deliveryCost.at(j)<<" ";
		}
		std::cout<<std::endl;
	}
	std::cout<<"\n Factories Costs:";
	for (int i = 0; i < factories.size(); i++)
	{
		for (int j = 0; j < warehouses.size(); j++)
		{
			
			std::cout<<factories.at(i)->deliveryCost.at(j)<<" ";
		}
		std::cout<<std::endl;
	}
	std::cout<<"\n Warehouses Costs:";
	for (int i = 0; i < warehouses.size(); i++)
	{
		for (int j = 0; j < shops.size(); j++)
		{
			
			std::cout<<warehouses.at(i)->deliveryCost.at(j)<<" ";
		}
		std::cout<<std::endl;
	}

	for (int i = 0; i < suppliers.size(); i++)
	{
		for (int j = 0; j < factories.size(); j++)
		{

			std::cout<<"min:"<<GetSupplier(i)->GetMin(j)<<" ";
			std::cout<<"max:"<<GetSupplier(i)->GetMax(j)<<std::endl;
		}
	}
	std::cout<<std::endl;
	for (int i = 0; i < factories.size(); i++)
	{
		for (int j = 0; j < warehouses.size(); j++)
		{

			std::cout<<GetFactory(i)->GetMin(j)<<" ";
			std::cout<<GetFactory(i)->GetMax(j)<<std::endl;
		}
	}
	std::cout<<std::endl;

	for (int i = 0; i < warehouses.size(); i++)
	{
		for (int j = 0; j < shops.size(); j++)
		{

			std::cout<<GetWarehouse(i)->GetMin(j)<<" ";
			std::cout<<GetWarehouse(i)->GetMax(j)<<std::endl;
		}
	}
}

void CMscnProblem::GenerateInstance(unsigned int seed)
{
	CRandom rand(seed);
	RandomSetter setter;

	setter.SetRandomPowers(suppliers, rand);
	setter.SetRandomPowers(factories, rand);
	setter.SetRandomPowers(warehouses, rand);
	setter.SetRandomPowers(shops,rand);

	setter.SetRandomTransportCost(suppliers, factories, rand);
	setter.SetRandomTransportCost(factories, warehouses, rand);
	setter.SetRandomTransportCost(warehouses, shops, rand);

	setter.SetRandomCotract(suppliers, rand);
	setter.SetRandomCotract(factories, rand);
	setter.SetRandomCotract(warehouses, rand);

	setter.SetRandomIncome(shops, rand);
	
	setter.SetRandomMinMax(suppliers, factories, rand);
	setter.SetRandomMinMax(factories, warehouses, rand);
	setter.SetRandomMinMax(warehouses, shops, rand);
}
void CMscnProblem::Take(CMscnProblem& other) {
	suppliers = other.suppliers;
	for (int i = 0; i < other.suppliers.size(); i++)
	{
		other.suppliers.at(i) = new Supplier(other.factories.size());
	}
	factories = other.factories;
	for (int i = 0; i < other.factories.size(); i++)
	{
		other.factories.at(i) = new Supplier(other.warehouses.size());
	}
	warehouses = other.warehouses;
	for (int i = 0; i < other.warehouses.size(); i++)
	{
		other.warehouses.at(i) = new Supplier(other.shops.size());
	}
	shops = other.shops;
	for (int i = 0; i < other.shops.size(); i++)
	{
		other.shops.at(i) = new Shop();
	}
	
}

int CMscnProblem::CorrectSolutionSize()
{
	return suppliers.size()*factories.size()+factories.size()*warehouses.size()+warehouses.size()*shops.size();
}

bool CMscnProblem::CorrectValue(double newVal, int index)
{
	Vector4 sizes = Sizes();
	int sf = sizes.x*sizes.y;
	int fw = sf+sizes.y*sizes.z;
	if(index < sf)
	{
		double min = GetSupplier((int)std::floorf(index/sizes.y))->GetMin(index%(int)sizes.y);
		double max = GetSupplier((int)std::floorf(index/sizes.y))->GetMax(index%(int)sizes.y);
		if(newVal>=min && newVal<=max)return true;
		return false;
	}else if(index < fw){
		double min = GetFactory((int)std::floorf(index-sf)/sizes.z)->GetMin(index%(int)sizes.z);
		double max = GetFactory((int)std::floorf(index-sf)/sizes.z)->GetMax(index%(int)sizes.z);
		if(newVal>=min && newVal<=max)return true;
		return false;
	}else
	{
		double min = GetWarehouse((int)std::floorf(index-fw)/sizes.r)->GetMin(index%(int)sizes.r);
		double max = GetWarehouse((int)std::floorf(index-fw)/sizes.r)->GetMax(index%(int)sizes.r);
		if(newVal>=min && newVal<=max)return true;
		return false;
	}
	return false;
}

double* CMscnProblem::CorrectRandomSolution()
{
	Vector4 sizes = Sizes();
	CRandom rand;
	double* individual = new double[CorrectSolutionSize()];
	int index=0;
	for (int i = 0; i < sizes.x; i++)
	{
		double power = GetSupplier(i)->GetPower();
		for (int j = 0; j < sizes.y; j++)
		{
			double random = rand.Range(GetSupplier(i)->GetMin(j),GetSupplier(i)->GetMax(j));
			if(power-random <0)
			{
				
				double min =GetSupplier(i)->GetMin(j);
				if(power > min){
					random = rand.Range(GetSupplier(i)->GetMin(j),power);
				}else{break;}
				
			}
			individual[index++] = random;
			power-=random;
			if(power<0)break;

		}
	}
	for (int i = 0; i < sizes.y; i++)
	{
		double power = GetFactory(i)->GetPower();
		for (int j = 0; j < sizes.z; j++)
		{

			double random = rand.Range(GetFactory(i)->GetMin(j),GetFactory(i)->GetMax(j));
			if(power-random <0)
			{
				double min =GetFactory(i)->GetMin(j);
				if(power > min){
					random = rand.Range(GetFactory(i)->GetMin(j),power);
				}else{break;}
				
				
			}
			individual[index++] = random;
			power-=random;
			if(power<0)break;
		}
	}
	for (int i = 0; i < sizes.z; i++)
	{
		double power = GetWarehouse(i)->GetPower();
		for (int j = 0; j < sizes.r; j++)
		{

			double random = rand.Range(GetWarehouse(i)->GetMin(j),GetWarehouse(i)->GetMax(j));
			if(power-random <0)
			{
				double min =GetWarehouse(i)->GetMin(j);
				if(power > min){
					random = rand.Range(GetWarehouse(i)->GetMin(j),power);
				}else{break;}
				
			}
			individual[index++] = random;
			power-=random;
			if(power<0)break;

		}
	}
	return individual;
}

Vector4 CMscnProblem::Sizes()
{
	return Vector4(suppliers.size(),factories.size(),warehouses.size(),shops.size());
}

double CMscnProblem::GetQualityAndFixSolution(ISolution& solution)
{
	Solution sol(solution.GetSolution(),solution.GetSize());
	if(!ConstrainsSatisfied(sol)){
		
		FixSolution(solution.GetSolution());
	}
	ApplySolution(solution.GetSolution());
	return GetQuality(solution);
}

double CMscnProblem::GetQuality(ISolution& solution)
{
	int expectedSize = CorrectSolutionSize();
	
	if(solution.GetSize() == expectedSize)
	{
		ApplySolution(solution.GetSolution());
		double quality = CalculateIncomeFromShops() - CalculateContractCost() - CalculateTransportCost();
		return quality;
	}
	
	return BAD_SOLUTION;
}










