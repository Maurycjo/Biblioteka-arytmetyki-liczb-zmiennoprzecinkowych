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


	std::vector<int> a{1, 2, 3};
	std::vector<int> b{4, 5, 6, 7};
	std::vector<int> c;
	c.reserve(7);

	c.insert(c.end(), a.begin(), a.end());
	c.insert(c.end(), b.begin(), b.end());

	for (int i : c)
	{
		std::cout << i << " ";
	}




	

	
	FloatNumber numberA, numberB, numberC;
	numberA.setStandard(s);
	numberB.setStandard(s);
	numberC.setStandard(s);

	numberA.dec2float(113.5);
	numberB.dec2float(113.5);

	std::cout << "numberA: ";
	numberA.displayNumberBinary();
	std::cout << "numberB: ";
	numberB.displayNumberBinary();

	std::cout << "\noczekiwana\n";
	number.displayNumberBinary();

	std::cout << "**multiply**\n";

	numberC=numberC.multiply(numberA, numberB);
	numberC.displayNumberBinary();
	


	return 0;
}