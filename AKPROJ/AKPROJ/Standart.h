#pragma once
static class Standart
{
private:
	//domyslne wartosci dla mnoznika i wykladnika
	int exponent = 3; //wykladnk
	int fraction = 4; //mnoznik
	

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
	//zwraca liczbe bitow wykladnika
	int getExponent()
	{
		return exponent;
	}
	//zwraca liczbe bitow mnoznika
	int getFraction()
	{
		return fraction;
	}


};

