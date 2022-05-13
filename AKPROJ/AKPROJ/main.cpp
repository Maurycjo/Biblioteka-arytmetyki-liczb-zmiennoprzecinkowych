#include <iostream>
#include "FloatNumber.h"
#include "Standard.h"

#include <bitset>
#include <bit>

int main()
{
	

	Standard s(1, 2);
	FloatNumber number;
	number.setStandard(s);
	number.dec2float(float(113.5 * 113.5));
	//number.displayNumberBinary();

















	
	FloatNumber numberA, numberB;
	numberA.setStandard(s);
	numberB.setStandard(s);

	numberA.dec2float(113.5);
	numberB.dec2float(113.5);

	std::cout << "numberA: ";
	numberA.displayNumberBinary();
	std::cout << "numberB: ";
	numberB.displayNumberBinary();

	std::cout << "**multiply**\n";

	number.multiply(numberA, numberB);

	std::cout << "\noczekiwana\n";
	number.displayNumberBinary();

	


	return 0;
}