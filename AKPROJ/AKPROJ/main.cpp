#include <iostream>
#include "FloatNumber.h"
#include "Standard.h"
#include <bitset>
#include <bit>

int main()
{

	double testA = 9123424323999.9900129;
	double testB = 0.000000000121243;
	double result = testA * testB;
	
	
	std::cout << "Program started\n";


	



	
	
	Standard s(1, 3);
	//FloatNumber number;
	//number.setStandard(s);
	//number.dec2float(result);
	//number.displayNumberBinary();

	

	
	FloatNumber numberA, numberB, numberC, numberD;
	numberA.setStandard(s);
	numberB.setStandard(s);
	numberC.setStandard(s);
	numberD.setStandard(s);

	numberC.dec2float(result);


	std::cout << "numberA\n";
	numberA.dec2float(testA);
	numberA.displayNumberBinary();

	std::cout << "numberB\n";
	numberB.dec2float(testB);
	numberB.displayNumberBinary();

	std::cout << "\noczekiwana\n";
	numberC.displayNumberBinary();

	std::cout << "**multiply**\n";

	numberD.multiply(numberA, numberB);
	numberD.displayNumberBinary();
	


	return 0;
}