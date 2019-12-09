#include "Shop.h"
#include "Supplier.h"
Shop::Shop()
{
	income = DEFAULT_INCOME;
	maxProductivePower= DEFAULT_POWER;
}

Shop::Shop(double inc, double power)
{
	income=inc;
	maxProductivePower=power;
}
