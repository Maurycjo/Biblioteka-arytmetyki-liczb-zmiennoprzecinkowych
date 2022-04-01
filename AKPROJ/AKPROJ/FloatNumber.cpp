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

	
	bool* expTab = new bool[s.getExponent()+1];		//tablica bitow mnoznika z bitem ukrytym
	bool* fracTab = new bool[s.getFraction()];		//tablica bitow wykladnika
	
	int minRange = 0 - (2 ^ s.getExponent() - 1);	//najmniejszy mozliwy wykladnik
	//int maxRange = 2 ^ (s.getExponent()) - 1;		//najwiekszy mozliwy wykladnik
	int maxRange = pow(2, s.getExponent()) - 1;
	int currentPower = 0;							//aktualny wykladnik
	int twoPow = 1;									//do odejmowania przy konwersji
	bool currentBit;								//aktualny bit w konwersji
	int exponIterator = 0;							//iterator po tablicy wykladnikow
	bool bitR, bitS;								//bity R i S do zaokraglania

	//ustalenie njawiekszej potegi dwojki mniejszej od czesci calkowitej liczby
	while (twoPow < number)
	{
		twoPow *= 2;
	}
	twoPow /= 2;

	

	//zamiana czesci calkowitej na liczbe wynikowa
	while (number>0&&currentPower<=maxRange)
	{

		//konwersja zrealizowana przez odejmowanie poteg dwojki
		if (twoPow <= number)
		{
			number -= twoPow;
			currentBit = 1;
		}
		else
		{
			currentBit = 0;
		}
		twoPow /= 2;

		//jezeli przekroczymy zakres dokladnosci mnoznika, zwiekszamy wykladnik
		if (exponIterator >= s.getExponent())
		{
			currentPower += 1;
			if (currentPower == 1) bitR = currentBit;
			if (currentPower == 2 && number != 0) bitS = 1;
			else if (number == 0 && currentBit == 1) bitS = 1;

		}
		else
		{
		expTab[exponIterator] = currentBit;
		exponIterator++;

		}
		std::cout << currentBit << " ";
		
	}
	std::cout << "wykladnik: " << currentPower << "\n";
	std::cout << "\n";

		
}
