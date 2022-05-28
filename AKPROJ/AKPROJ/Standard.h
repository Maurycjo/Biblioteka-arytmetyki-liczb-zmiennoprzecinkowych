#pragma once

static class Standard
{
private:
	//domyslne wartosci dla mnoznika i wykladnika
	int exponent = 1; //wykladnk
	int fraction = 2; //mnoznik


public:
	void setStandart(int exp, int frac)
	{
		exponent = exp;
		fraction = frac;
	}
	Standard()
	{}
	Standard(int exp, int frac)
	{
		setStandart(exp, frac);
	}
	//zwraca liczbe bajtow wykladnika
	int getExponent()
	{
		return exponent;
	}
	//zwraca liczbe bajtow mnoznika
	int getFraction()
	{
		return fraction;
	}
};
