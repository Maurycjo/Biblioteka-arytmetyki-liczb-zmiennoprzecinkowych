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



	std::vector<uint8_t> inc{ 0b00001111, 0b11111111, 0b11111100 };

	for (auto i : inc)
		std::cout << std::bitset<8>(i) << " ";
	std::cout << std::endl;

	number.incSevBytes(inc);

	for (auto i : inc)
		std::cout << std::bitset<8>(i) << " ";
	std::cout << std::endl;











	/*

	
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

	
	*/


	return 0;
}