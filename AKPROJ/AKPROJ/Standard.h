#pragma once

static class Standard
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
	Standard()
	{}
	Standard(int exp, int frac)
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

	enum roundType
	{
		TOWARD_ZERO,					//zaokraglenie przez obciecie, do zera
		TOWARD_PLUS_INF,				//zaokraglenie do plus nieskonczonosci
		TOWARD_MINUS_INF,				//zaokraglenie do minus nieskonczonosci
		TO_NEAREST_TIES_TO_EVEN,		//zaokraglenie symetryczne to wiekszej wartosci bezzwzglednej
		TO_NEAREST_TIES_AWAY_FROM_ZERO	//zaokraglenie symetryczne do parzystej
	};


};
