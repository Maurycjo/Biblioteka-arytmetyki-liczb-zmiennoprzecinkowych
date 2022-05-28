#include <iostream>
#include "FloatNumber.h"
#include "Standard.h"
#include <bitset>
#include <bit>
#include "ConsoleApp.h"

int main()
{

	std::string liczba = "0|10100000 |1110000|||1";
	Standard s(1, 1);

	FloatNumber stringNumber;
	stringNumber.setStandard(s);
	//std::cout << "podaj\n";
	//std::cin >> liczba;
	if (stringNumber.string2float(liczba))
		stringNumber.displayNumberBinary();
	else
		std::cout << "false";





	//ConsoleApp consoleApp;

	/*
	long double testA = 1230.17723;
	long double testB = 1455.12999995;
	long double result = long double(testA / testB);
	std::cout.precision(20);
	std::cout << long double(result) << std::endl;
	
	std::cout << "Program started\n";

	Standard s(1, 2);
	FloatNumber numberA, numberB;
	FloatNumber numberResult, divided;
	numberA.setStandard(s);
	numberB.setStandard(s);
	numberResult.setStandard(s);
	divided.setStandard(s);
	

	numberA.dec2float(testA);
	numberB.dec2float(testB);
	numberResult.dec2float(result);

	std::cout << "numberA\n";
	numberA.displayNumberBinary();
	std::cout << "numberB\n";
	numberB.displayNumberBinary();
	std::cout << "oczekiwany iloraz\n";
	numberResult.displayNumberBinary();
	numberResult.dec2float_alpha(result);
	numberResult.displayNumberBinary();
	std::cout << "DIVISION\n";
	divided.division(numberA, numberB);
	divided.displayNumberBinary();

	std::cout << "\n";

	*/


	return 0;
}