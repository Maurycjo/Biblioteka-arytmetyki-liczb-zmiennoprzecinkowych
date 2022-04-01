#include "FloatNumber.h"




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




void FloatNumber::dec2float(int number)
{
	bool* expTab = new bool[s.getExponent()];
	bool* fracTab = new bool[s.getFraction()];
	bool hideBit = 0;

	int minRange = 0 - (2 ^ s.getExponent() - 1);
	int maxRange = 2 ^ s.getExponent() - 1;
	int currentPower = 0;
	int twoPow = 1;
	bool currentBit;
	while (twoPow < number)
	{
		twoPow *= 2;
	}
	twoPow /= 2;


	while (currentPower > minRange && currentPower < maxRange)
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






	}
	


		
}
