#pragma once
#include <vector>
#include "CRandom.h"
#include "Supplier.h"
#include "Shop.h"
class RandomSetter
{
private:
	const double MIN_TRANSPORT_COST = 1;
	const double MAX_TRANSPORT_COST = 100;

	const double MIN_PRODUCTIVE_POWER = 1;
	const double MAX_PRODUCTIVE_POWER = 10000;

	const double MIN_CONTRACT_COST = 1;
	const double MAX_CONTRACT_COST = 100;

	const double MIN_INCOME = 1;
	const double MAX_INCOME = 100;

	const double MIN_MIN = 0;
	const double MIN_MAX = MIN_MIN+10;

	const double MAX_MIN = MIN_MAX+1;
	const double MAX_MAX = MAX_MIN+10;
public:
	void SetRandomPowers(const std::vector<Supplier*>& vec,  CRandom& rand);
	void SetRandomPowers(const std::vector<Shop*>& vec,  CRandom& rand);
	void SetRandomCotract(const std::vector<Supplier*>& vec,  CRandom& rand);
	void SetRandomIncome(const std::vector<Shop*> vec, CRandom& rand);
	template<typename T>
	void SetRandomMinMax(const std::vector<Supplier*> from, const std::vector<T> to, CRandom& rand);
	template<typename T>
	void SetRandomTransportCost(const std::vector<Supplier*> from, const std::vector<T> to, CRandom& rand);
};

template<typename T>
inline void RandomSetter::SetRandomTransportCost(const std::vector<Supplier*> from, const std::vector<T> to, CRandom& rand)
{
	for (int i = 0; i < from.size(); i++)
	{
		for (int j = 0; j < to.size(); j++)
		{
			from.at(i)->SetCostTo(j, rand.Range(MIN_TRANSPORT_COST, MAX_TRANSPORT_COST));
		}
	}
}
template<typename T>
inline void RandomSetter::SetRandomMinMax(const std::vector<Supplier*> from, const std::vector<T> to, CRandom& rand)
{
	for (int i = 0; i < from.size(); i++)
	{
		for (int j = 0; j < to.size(); j++)
		{
			
			from.at(i)->SetMinResource(j, rand.Range(MIN_MIN,MIN_MAX));
			from.at(i)->SetMaxResource(j, rand.Range(MAX_MIN,MAX_MAX));
		}
	}
}
