#include "FloatNumber.h"
#include <iostream>
#include <math.h>




FloatNumber::FloatNumber(Standart s)
{
	this->s = s;
	size = 1 + s.getExponent() + s.getFraction();
	table = new bool[size];
	grs = new bool[3];
}
FloatNumber::~FloatNumber()
{
	delete[] table;
	delete[] grs;
}


/*
1 przypadek konczy konwersje na liczbie calkowitej
2 przypadek dopisuje cyfry do mnoznika z ulamka
3 przypadek wartosc przed przecinkiem 0 i leci cyfry z samego ulamka
4 leci tak dobrze z tego ulamka ze trza zdenormalizowac
*/
void FloatNumber::dec2float(float inputNumber)
{
	if (inputNumber < 0)
	{ 
		table[0] = 1;
		inputNumber *= -1;
	}
	else
		table[0] = 0;


	int number = inputNumber;						//czesc calkowita liczby
	float frac = inputNumber - float(number);		//czesc ulamkowa liczby

	
	b
	bool* expTab = new bool[s.getExponent()];		//tablica bitow wykladnika
	bool* fracTab = new bool[s.getFraction()+1];	//tablica bitow mnoznika z bitem ukrytym
	
	int minRange = 1 - pow(2, s.getExponent()) - 1;	//najmniejszy mozliwy wykladnik	
	int maxRange = pow(2, s.getExponent()) - 1;		//najwiekszy mozliwy wykladnik
	int currentPower = 0;							//aktualny wykladnik
	int twoPow = 1;									//do odejmowania przy konwersji
	bool currentBit;								//aktualny bit w konwersji
	int fracIterator = 0;							//iterator po tablicy wykladnikow
	bool bitR, bitS;								//bity R i S do zaokraglania

	











	

		
}
