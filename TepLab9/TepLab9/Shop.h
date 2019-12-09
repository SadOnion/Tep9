#pragma once
class Shop
{
private:
	const double DEFAULT_INCOME=10;
	const double DEFAULT_POWER=1000;
public:
	double income;
	double maxProductivePower;
	Shop();
	Shop(double inc,double power);

};

