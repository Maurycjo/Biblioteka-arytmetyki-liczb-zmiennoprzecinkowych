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

	std::vector<uint8_t> fracTab;		//vector mnoznika
	std::vector<uint8_t> expTab;		//vector wykladnika 

	uint8_t byte = 0b00000000;			//bajt do zapisu do vectora
	uint8_t byteIterator = 0b10000000;	//bajt do zwiekszania bajtu

	int expLoad = pow(2, (s.getExponent()*8 - 1)) - 1;
	int expMaxRange = pow(2, s.getExponent()*8)-2-expLoad;
	int expMinRange = 1 - expLoad;
	int expValue = 0;

	

	bool denormalized = false;
	int number = inputNumber;
	float afterTheDecPoint = inputNumber - number;
	int decPlace = 0;
	int tempNumber = number;
	int fracIterator = 0;				//iterator po mnozniku



	std::cout << "obciazenie: " << expLoad << "\n";
	std::cout << "<" << expMinRange << "; " << expMaxRange << ">\n";
	std::cout << "realNumber: "<<std::format("{:b}", number) << std::endl;


	while (tempNumber > 0)
	{
		tempNumber /= 2;
		decPlace++;
	}

	
	if (decPlace > expMaxRange)
	{
		std::cout << "infinity";
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



	for (auto i : expTab)
	{
		std::cout<<std::format("{:b}", i) << " ";
	}

	std::cout << "|";
	for (auto i : fracTab)
	{
		std::cout << std::setw(8) << std::format("{:b}", i) << " ";
	}




	//std::cout << "wykladnik: " << decPlace << std::endl;
	if(denormalized)
	std::cout << "\ndenormalized"<< std::endl;
	std::cout << "\nvectorSize: " << fracTab.size();

	/*
	std::cout << "br: " << std::format("{:b}", byteIterator) << std::endl;
	byteIterator=byteIterator >> 1;
	std::cout << "ar: " << std::format("{:b}", byteIterator);
	*/

	

	//fracTab.push_back(0b10001111);
	//std::cout << std::format("{:b}", fracTab[0]);
	

		
}
