#pragma once

class Standard
{
public:

	enum  roundType
	{
		TOWARD_ZERO,					//zaokraglenie przez obciecie, do zera
		TOWARD_PLUS_INF,				//zaokraglenie do plus nieskonczonosci
		TOWARD_MINUS_INF,				//zaokraglenie do minus nieskonczonosci
		TO_NEAREST_TIES_TO_EVEN,		//zaokraglenie symetryczne to wiekszej wartosci bezzwzglednej
		TO_NEAREST_TIES_AWAY_FROM_ZERO	//zaokraglenie symetryczne do parzystej
	};	


	void setStandart(int exp, int frac, roundType round_type)
	{
		exponent = exp;
		fraction = frac;
		round_type = round_type;
	}
	Standard()
	{}
	Standard(int exp, int frac, roundType round_type)
	{
		setStandart(exp, frac, round_type);
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
	roundType getRoundType(){
		return round_type;
	}



	private:
	//domyslne wartosci dla mnoznika i wykladnika
	int exponent = 3; //wykladnk
	int fraction = 4; //mnoznik
	roundType round_type = roundType::TOWARD_MINUS_INF; //obciecie domyslnie







};
