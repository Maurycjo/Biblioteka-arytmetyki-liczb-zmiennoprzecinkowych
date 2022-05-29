#include <iostream>
#include "FloatNumber.h"
#include "Standard.h"
#include <bitset>
#include <bit>
#include "ConsoleApp.h"



int main()
{

	ConsoleApp consoleapp;


	Standard s(2, 2);
	FloatNumber number;
	number.setStandard(s);
	number.dec2float(2);

	if (number.ifOne(number))
		std::cout << "prawda\n";
	else
		std::cout << "nieprawda\n";

	number.displayNumberBinary();

	return 0;
}	
