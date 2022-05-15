#include <iostream>
#include "FloatNumber.h"
#include "Standard.h"
#include <bitset>
#include <bit>

int main()
{

	double testA = 9999999.99999999999999999999999999;
	double testB = 1234.123;
	double result = testA * testB;
	
	
	std::cout << "Program started\n";


	



	
	
	Standard s(1, 3);
	//FloatNumber number;
	//number.setStandard(s);
	//number.dec2float(result);
	//number.displayNumberBinary();

	

	
	FloatNumber numberA, numberB, numberC;
	numberA.setStandard(s);
	numberB.setStandard(s);
	numberC.setStandard(s);

	std::cout << "numberA\n";
	numberA.dec2float_2(testA);

	std::cout << "numberNew: ";
	numberA.displayNumberBinary();

	std::cout << "numberB\n";
	numberB.dec2float(testA);

	std::cout << "numberOld: ";
	numberB.displayNumberBinary();
	/*
	std::cout << "\noczekiwana\n";
	number.displayNumberBinary();

	std::cout << "**multiply**\n";

	numberC.multiply(numberA, numberB);
	numberC.displayNumberBinary();
	*/


	return 0;
}