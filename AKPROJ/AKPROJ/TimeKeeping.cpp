#include "TimeKeeping.h"
#include <fstream>
#include <ctime>
#include <Windows.h>
#include <iostream>
#include "FloatNumber.h"
#include "Standard.h"
#include "RandomGenerator.h"
#include <iomanip>


TimeKeeping::TimeKeeping()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
}


long long int TimeKeeping::read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

void TimeKeeping::getRandomNumber(FloatNumber& number)
{
	RandomGenerator random;
	float numberToConvert = random.generateRandomFloat(-10000, 10000);
	number.dec2float(numberToConvert);
}


void TimeKeeping::multiplyTime()
{
	Standard s(1, 1);
	file.open("timeKeep/mul.txt");

	for (int exp = 1; exp <= 4; exp++)
	{
		s.setExponent(exp);

		for (int frac = 1; frac <= 10; frac++)
		{
			s.setFraction(frac);


			file << "1/" << s.getExponent() << "/" << s.getFraction() << std::endl;

			for (int i = 0; i < 1000; i++)
			{
				FloatNumber numberA, numberB, result;
				numberA.setStandard(s);
				numberB.setStandard(s);
				getRandomNumber(numberA);
				getRandomNumber(numberB);
				start = read_QPC();
				result.multiply(numberA, numberB);
				elapsed = read_QPC() - start;
				//std::cout << std::fixed << std::setprecision(0) << (1000000.0 * elapsed) / frequency << std::endl; us
				//std::cout << std::setprecision(0) << (1000.0 * elapsed) / frequency << std::endl; ms
				file << std::fixed << std::setprecision(0) << (1000000.0 * elapsed) / frequency << std::endl;
			}
		}
	}
	file.close();
}


void TimeKeeping::divTime()
{
	Standard s(1, 1);
	file.open("timeKeep/div.txt");

	for (int exp = 1; exp <= 4; exp++)
	{
		s.setExponent(exp);
		for (int frac = 1; frac <= 10; frac++)
		{
			s.setFraction(frac);


			file << "1/" << s.getExponent() << "/" << s.getFraction() << std::endl;

			for (int i = 0; i < 1000; i++)
			{
				FloatNumber numberA, numberB, result;
				numberA.setStandard(s);
				numberB.setStandard(s);
				getRandomNumber(numberA);
				getRandomNumber(numberB);
				start = read_QPC();
				result.division(numberA, numberB);
				elapsed = read_QPC() - start;
				//std::cout << std::fixed << std::setprecision(0) << (1000000.0 * elapsed) / frequency << std::endl; us
				//std::cout << std::setprecision(0) << (1000.0 * elapsed) / frequency << std::endl; ms
				file << std::fixed << std::setprecision(0) << (1000000.0 * elapsed) / frequency << std::endl;
				//numberA.displayNumberBinary();
				//numberB.displayNumberBinary();
				//result.displayNumberBinary();
				//std::cout << std::endl;

			}
		}
	}
	file.close();
}


void TimeKeeping::addTime()
{
	Standard s(1, 1);
	file.open("timeKeep/add.txt");

	for (int exp = 1; exp <= 4; exp++)
	{
		s.setExponent(exp);

		for (int frac = 1; frac <= 10; frac++)
		{
			s.setFraction(frac);


			file << "1/" << s.getExponent() << "/" << s.getFraction() << std::endl;

			for (int i = 0; i < 1000; i++)
			{
				FloatNumber numberA, numberB, result;
				numberA.setStandard(s);
				numberB.setStandard(s);
				getRandomNumber(numberA);
				getRandomNumber(numberB);
				start = read_QPC();
				result.addition(numberA, numberB);
				elapsed = read_QPC() - start;
				//std::cout << std::fixed << std::setprecision(0) << (1000000.0 * elapsed) / frequency << std::endl; us
				//std::cout << std::setprecision(0) << (1000.0 * elapsed) / frequency << std::endl; ms
				file << std::fixed << std::setprecision(0) << (1000000.0 * elapsed) / frequency << std::endl;
			}
		}
	}
	file.close();
}