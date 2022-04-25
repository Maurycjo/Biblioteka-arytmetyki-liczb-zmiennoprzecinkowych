#include <iostream>
#include "FloatNumber.h"
#include "Standard.h"

#include <bitset>
#include <bit>

int main()
{
	Standard s(1, 3);
	FloatNumber number;
	number.setStandard(s);
	//number.dec2float(1.000000011);
	//number.displayNumberBinary();

	
	uint8_t rotCarry = 0;
	uint8_t numA = 0b11110000, numB = 0b10000001;

	
	std::vector<uint8_t> test{ 0b00001111, 0b11001111, 0b00110001 };


	std::cout << "\nprzed przesunieciem\n";
	for(auto i: test)
	std::cout << std::bitset<8>(i) << " ";
	
	number.rrcSevBytes(test);
	
	std::cout << "\npo przesunieciu\n";
	for(auto i : test)
	std::cout << std::bitset<8>(i) << " ";
	//std::cout << std::bitset<8>(numA) << " \n";

	//std::cout << std::bitset<8>(rotCarry) << "\n";
	

	return 0;
}