#include "FloatNumber.h"
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;


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


	bool* fracTab = new bool[s.getFraction()+1];
	bool* expTab = new bool[s.getExponent()];


	int number = inputNumber;						//czesc calkowita liczby
	float frac = inputNumber - float(number);		//czesc ulamkowa liczby

	
	

	int minRange = 1 - pow(2, s.getExponent()) - 1;	//najmniejszy mozliwy wykladnik	
	int maxRange = pow(2, s.getExponent()) - 1;		//najwiekszy mozliwy wykladnik
	int mask = pow(2, s.getExponent()) - 1 -		//maska wykladnika
	pow(2, (s.getExponent() - 1));
	int currentPower = 0;							//aktualny wykladnik
	int twoPow = 1;									//do odejmowania przy konwersji
	bool currentBit;								//aktualny bit w konwersji
	int fracIterator = 0;							//iterator po tablicy wykladnikow
	bool bitR,bitS;								//bity R i S do zaokraglania
	int decPlace = 0;							//aktualne miejsce przecinka 

	


	//ustalenie njawiekszej potegi dwojki mniejszej od czesci calkowitej liczby
	while (twoPow <= number)
	{
		
		twoPow *= 2;
	}
	twoPow /= 2;




	//zamiana czesci calkowitej na liczbe wynikowa
	while (twoPow>0)
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

		if (fracIterator > s.getFraction())
		{
			
			if (fracIterator == (s.getFraction()) + 1)
				bitR = currentBit;
			if (fracIterator == (s.getFraction()) + 2)
			{
				if (currentBit == 1)
				{
					bitS = 1;
				}
				else if (number != 0)
					bitS = 1;
				else
					bitS = 0;
			}
			currentPower++;
		}
		else
		{
			fracTab[fracIterator] = currentBit;
		}
		if (fracIterator == s.getFraction())
		{
			decPlace = fracIterator;
		}
			fracIterator++;
	}
	
	
	

	
	while (fracIterator <= (s.getFraction() + 2))
	{
		
		frac *= 2;
		if (frac > 1)
		{
			frac -= 1;
			currentBit = 1;
		}
		else
		{
			currentBit = 0;
		}


		if (fracIterator == (s.getFraction()) + 1)
			bitR = currentBit;
		if (fracIterator == (s.getFraction()) + 2)
		{
			if (currentBit == 1)
			{
				bitS = 1;
			}
			else if (frac != 0)
				bitS = 1;
			else
				bitS = 0;
		}


		fracTab[fracIterator] = currentBit;
		fracIterator++;
	}

	for (int i = 0; i <= s.getFraction(); i++)
	{
		cout << fracTab[i] << " ";
	}
	cout << "RS" << bitR << bitS;


	currentPower += decPlace;
	cout << "\npotega: "<<currentPower;



	

		
}
