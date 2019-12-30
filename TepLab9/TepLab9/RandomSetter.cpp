#include "RandomSetter.h"

void RandomSetter::SetRandomPowers(const std::vector<Supplier*>& vec, CRandom& rand)
{
	for (int i = 0; i < vec.size(); i++)
	{
		
		vec.at(i)->SetProductivePower(rand.Range(MIN_PRODUCTIVE_POWER, MAX_PRODUCTIVE_POWER));
	}
}
void RandomSetter::SetRandomPowers(const std::vector<Shop*>& vec, CRandom& rand)
{
	for (int i = 0; i < vec.size(); i++)
	{
		vec.at(i)->maxProductivePower = rand.Range(MIN_PRODUCTIVE_POWER, MAX_PRODUCTIVE_POWER);
	}
}

void RandomSetter::SetRandomCotract(const std::vector<Supplier*>& vec, CRandom& rand)
{
	for (int i = 0; i < vec.size(); i++)
	{
		vec.at(i)->SetContractCost(rand.Range(MIN_CONTRACT_COST, MAX_CONTRACT_COST));
	}
}

void RandomSetter::SetRandomIncome(const std::vector<Shop*> vec, CRandom& rand)
{
	for (int i = 0; i < vec.size(); i++)
	{
		vec.at(i)->income = rand.Range(MIN_INCOME, MAX_INCOME);
	}
}



