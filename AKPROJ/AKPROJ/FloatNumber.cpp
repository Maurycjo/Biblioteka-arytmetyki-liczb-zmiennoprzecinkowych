#include "FloatNumber.h"
#include <iostream>
#include <math.h>
#include <format>
#include <cassert>
#include <cmath>






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


	bool normalized = false;
	int number = inputNumber;
	float afterTheDecPoint = inputNumber - number;
	int decPlace = 0;
	int tempNumber = number;
	int fracIterator = 0;				//iterator po mnozniku, jak przechodzi sie z liczby calkowitej do przecinkowej
	std::cout << "realNumber: "<<std::format("{:b}", number) << std::endl;


	while (tempNumber > 0)
	{
		tempNumber /= 2;
		decPlace++;
	}

	//std::cout << pow(2, decPlace - 2) << std:: endl;
	//std::cout << decPlace - 1 << std::endl;

	if (decPlace > 0)
	{
		normalized = true;
		decPlace--;

		//std::cout << std::format("{:b}", number / 2048) << std::endl;

		if (number / int(pow(2, decPlace)) == 1)
		{
			number = number - pow(2, decPlace);	
		}	
	}

	for (int i = 0; i < decPlace; i++)
	{
		
		//std::cout << "number: " << number << std::endl;
		//std::cout << std::format("{:b}", byteIterator)<<"\n";

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

	//std::cout << "fracIterator: " << fracIterator << std::endl;
	//std::cout << "loop: " <<s.getFraction()*8 << std::endl;
	//std::cout<<std::format("{:b}", byte) << std::endl;

	while ((fracIterator < s.getFraction() * 8)&&afterTheDecPoint!=0)
	{
		//std::cout << "i: " << fracIterator << " ";
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

	//std::cout << "fracIterator: " << fracIterator << std::endl;
	//std::cout << "s.getfrac: " << << std::endl;
	if (fracIterator < s.getFraction()*8)
	{
		std::cout << "halo";
		fracTab.push_back(byte);
		byte = 0;
	}
	while (fracTab.size() != s.getFraction())
	{
		fracTab.push_back(0);
	}


	



	for (auto i : fracTab)
	{
		std::cout << std::format("{:b}", i)<<" ";
	}


	std::cout << "\nvectorSize: " << fracTab.size();

	/*
	std::cout << "br: " << std::format("{:b}", byteIterator) << std::endl;
	byteIterator=byteIterator >> 1;
	std::cout << "ar: " << std::format("{:b}", byteIterator);
	*/

	

	//fracTab.push_back(0b10001111);
	//std::cout << std::format("{:b}", fracTab[0]);
	

		
}
