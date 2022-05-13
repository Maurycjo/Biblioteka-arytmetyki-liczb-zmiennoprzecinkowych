#include <iostream>
#include "FloatNumber.h"
#include "Standard.h"

#include <bitset>
#include <bit>

int main()
{

	double testA =16.123;
	double testB = 4231.14;
	


	std::cout << "*\n";

	Standard s(1, 2);
	FloatNumber number;
	number.setStandard(s);
	number.dec2float(double(testA*testB));
	//number.displayNumberBinary();



	
	FloatNumber numberA, numberB, numberC;
	numberA.setStandard(s);
	numberB.setStandard(s);
	numberC.setStandard(s);

	numberA.dec2float(testA);
	numberB.dec2float(testB);

	std::cout << "numberA: ";
	numberA.displayNumberBinary();
	std::cout << "numberB: ";
	numberB.displayNumberBinary();

	std::cout << "\noczekiwana\n";
	number.displayNumberBinary();

	std::cout << "**multiply**\n";

	numberC.multiply(numberA, numberB);
	numberC.displayNumberBinary();



	return 0;
}