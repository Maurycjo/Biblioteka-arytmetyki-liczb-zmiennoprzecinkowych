#include <iostream>
#include "FloatNumber.h"
#include "Standard.h"
#include <bitset>
#include <bit>
#include "ConsoleApp.h"

int main()
{

	
		




	//ConsoleApp consoleApp;


	long double testA = 124.75;
	long double testB = 112.75;
	long double result = long double(testA * testB);

	std::string testStrA = "0|01111110 |01000000 00000000";
	std::string testStrB = "0|01111111 |00100000 00000000";

	std::cout << result << std::endl;






	
	std::cout << "Program started\n";

	Standard s(1, 2);
	FloatNumber numberA, numberB;
	FloatNumber numberResult, divided;
	numberA.setStandard(s);
	numberB.setStandard(s);
	numberResult.setStandard(s);
	divided.setStandard(s);
	
	
	//numberA.string2float(testStrA);
	//numberB.string2float(testStrB);
	numberA.dec2float(testA);
	numberB.dec2float(testB);
	numberResult.dec2float(result);

	std::cout << "numberA: ";
	numberA.displayNumberBinary();
	std::cout << "numberB: ";
	numberB.displayNumberBinary();
	std::cout << "oczekiwany iloczyn\n";
	numberResult.displayNumberBinary();
	
	std::cout << "\nMULTIPLY\n";
	divided.multiply(numberA, numberB);
	divided.displayNumberBinary();

	std::cout << "\n";

	


	return 0;
}