#include "FloatNumber.h"
#include <iostream>
#include <math.h>
#include <format>
#include <cassert>
#include <cmath>
#include <iomanip>






void FloatNumber::setStandard(Standard s)
{
	this->s = s;
	size = s.getExponent() + s.getFraction() + 1;

}


void FloatNumber::dec2float(float inputNumber)
{

	std::vector<uint8_t> fracTab;						//vector mnoznika
	std::vector<uint8_t> expTab;						//vector wykladnika 

	uint8_t byte = 0b00000000;							//bajt do zapisu do vectora
	uint8_t byteIterator = 0b10000000;					//bajt do zwiekszania bajtu

	bool bitR= 0, bitS = 0;								//bity r i s do zaokraglania										//znak liczby
	int expLoad = pow(2, (s.getExponent()*8 - 1)) - 1;	//obciazenie wykladnika		
	int expMaxRange = pow(2, s.getExponent()*8)-2-expLoad;//maksymalna warosc wykladnika 
	int expMinRange = 1 - expLoad;						//min wartosc wykladnika
	bool denormalized = false;							//czy liczba zdenormalizowana



	if (inputNumber < 0)
	{
		this->sign = 1;		//liczba ujemna
		inputNumber *= -1;
	}
	else
		this->sign = 0;		//liczba dodatnia


	int number = inputNumber;							//czesc calkowita liczby
	float afterTheDecPoint = inputNumber - number;		//czesc przecinkowa liczby
	int decPlace = 0;									//miejsce przecinka, wykladnik
	int tempNumber = number;							//liczba pomocnicza
	int fracIterator = 0;								//iterator po mnozniku


	


	std::cout << "obciazenie: " << expLoad << "\n";
	std::cout << "<" << expMinRange << "; " << expMaxRange << ">\n";

	while (tempNumber > 0)
	{
		tempNumber /= 2;
		decPlace++;
	}

	//nieskonoczonosc 
	if (decPlace > expMaxRange)
	{
		for (int i = 0; i < s.getExponent(); i++)
		{
			this->floatNumberBits.push_back(0b11111111);
		}
		for (int i = s.getExponent(); i < s.getFraction() + s.getExponent(); i++)
		{
			this->floatNumberBits.push_back(0);
		}
		return;
	}

	if (decPlace > 0)
	{
		decPlace--;
		
		if (number / int(pow(2, decPlace)) == 1)
		{
			number = number - pow(2, decPlace);	
		}	

		//konwersja czesci calkowitej, tylko wtedy kiedy ta czesc calkowita istnieje
		for (int i = 0; i < decPlace; i++)
		{
		
			if(number/int(pow(2, decPlace-i-1))==1)
			{
				//std::cout << "tuatj\n";
				number = number - int(pow(2, decPlace-i-1));
				byte += byteIterator;
			}

			byteIterator>>= 1;

			if (byteIterator == 0b00000000)
			{
				fracTab.push_back(byte);
				byteIterator = 0b10000000;
				byte = 0;
			}
			fracIterator++;
		}
	}
	else //przypadek kiedy liczba <1, wtedy tez trzeba ustalic czy liczbe trzeba zdenormalizowac
	{

		//ustalenie miejsca przecinka
		while (afterTheDecPoint < 1)
		{
			afterTheDecPoint *= 2;
			decPlace--;
			if (decPlace == expMinRange)
			{
				denormalized = true;
			}
		}
	
		//pierwszy bit jest ukryty
		if(!denormalized)
		afterTheDecPoint -= 1;

	}
	//konwersja czesci przecinkowej
	while ((fracIterator < s.getFraction() * 8)&&afterTheDecPoint!=0)
	{
		afterTheDecPoint *= 2;
		if (afterTheDecPoint >= 1)
		{
			byte += byteIterator;
			afterTheDecPoint -= 1;
		}

		byteIterator >>= 1;

		if (byteIterator == 0)
		{
			fracTab.push_back(byte);
			byte = 0;
			byteIterator = 0b10000000;
		}
		fracIterator++;
	}

	if (fracIterator < s.getFraction()*8)
	{
		fracTab.push_back(byte);
		byte = 0;
	}
	while (fracTab.size() != s.getFraction())
	{
		fracTab.push_back(0);
	}


	//konwersja wykladnika
	byte = 0;
	byteIterator = 0b00000001;

	std::cout << "wykladnik: " << decPlace << std::endl;
	decPlace += expLoad;

	while (decPlace>0)
	{

		if (decPlace % 2 == 1)
		{
			byte += byteIterator;
		}

		byteIterator <<= 1;
		if (byteIterator == 0)
		{
			expTab.insert(expTab.begin(), byte);
			byte = 0;
			byteIterator = 0b00000001;

		}
		decPlace /= 2;
	}

	if (byteIterator != 1)
	{
		expTab.insert(expTab.begin(), byte);
	}
	while (expTab.size() != s.getExponent())
	{
		expTab.insert(expTab.begin(), 0);
	}


	this->floatNumberBits.reserve(expTab.size() + fracTab.size());
	this->floatNumberBits.insert(floatNumberBits.end(), expTab.begin(), expTab.end());
	this->floatNumberBits.insert(floatNumberBits.end(), fracTab.begin(), fracTab.end());

	/*
	for (auto i : expTab)
	{
		std::cout<<std::format("{:b}", i) << " ";
	}

	std::cout << "|";
	for (auto i : fracTab)
	{
		std::cout << std::setw(8) << std::format("{:b}", i) << " ";
	}
	*/



	
	if(denormalized)
	std::cout << "\ndenormalized"<< std::endl;
	std::cout << "\nvectorSize: " << fracTab.size() << std::endl;

	/*
	std::cout << "br: " << std::format("{:b}", byteIterator) << std::endl;
	byteIterator=byteIterator >> 1;
	std::cout << "ar: " << std::format("{:b}", byteIterator);
	*/
	//fracTab.push_back(0b10001111);
	//std::cout << std::format("{:b}", fracTab[0]);
	
}

void FloatNumber::displayNumberBinary()
{

	std::cout << sign << "|";

	for (int i = 0; i < s.getExponent(); i++)
	{
		std::cout << std::format("{:b}", this->floatNumberBits[i]) << " ";
	}
	std::cout << "|";
	for (int i = s.getExponent(); i < s.getFraction()+s.getExponent(); i++)
	{
		std::cout << std::format("{:b}", this->floatNumberBits[i]) << " ";
	}
	std::cout << std::endl;

}
