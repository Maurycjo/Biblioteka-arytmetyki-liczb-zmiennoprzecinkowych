#pragma once
static class Standart
{
private:
	//domyslne wartosci dla mnoznika i wykladnika
	int exponent = 3;
	int fraction = 4;
	int divIntegerNumber(int &number);

public:
	void setStandart(int exp, int frac)
	{
		exponent = exp;
		fraction = frac;
	}
	Standart()
	{}
	Standart(int exp, int frac)
	{
		setStandart(exp, frac);
	}
	int getExponent()
	{
		return exponent;
	}
	int getFraction()
	{
		return fraction;
	}


};

