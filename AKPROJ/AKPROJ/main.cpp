#include <iostream>
#include "FloatNumber.h"
#include "Standard.h"

#include <bitset>
#include <bit>


void test(double x, double y, Standard::roundType round_type){
	std::cout << "*\n";

	Standard s(1, 2,round_type);
	FloatNumber number;
	number.setStandard(s);
	number.dec2float(double(x * y));
	// number.displayNumberBinary();

	FloatNumber numberA, numberB, numberC;
	numberA.setStandard(s);
	numberB.setStandard(s);
	numberC.setStandard(s);

	numberA.dec2float(x);
	numberB.dec2float(y);

	std::cout << "numberA: ";
	numberA.displayNumberBinary();
	std::cout << "numberB: ";
	numberB.displayNumberBinary();

	std::cout << "\noczekiwana\n";
	number.displayNumberBinary();

	std::cout << "**multiply**\n";

	numberC.multiply(numberA, numberB,round_type);
	numberC.displayNumberBinary();


}

int main()
{
		/*
		RS  11  695.12,123.68
		RS  10
		RS  01
		RS  00
		*/

	//test(695.12,123.68,Standard::roundType::TO_NEAREST_TIES_AWAY_FROM_ZERO);
	test(695.12,123.68,Standard::roundType::TO_NEAREST_TIES_TO_EVEN);
	//test(-695.12,123.68,Standard::roundType::TOWARD_MINUS_INF);
	//test(695.12,123.68,Standard::roundType::TOWARD_PLUS_INF);
	//test(695.12,123.68,Standard::roundType::TOWARD_ZERO);



	/*
	double testA = 2.0;
	double testB = 1.0;

	std::cout << "*\n";

	Standard s(1, 3,Standard::roundType::TO_NEAREST_TIES_AWAY_FROM_ZERO);
	FloatNumber number;
	number.setStandard(s);
	number.dec2float(double(testA * testB));
	// number.displayNumberBinary();

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
	*/
	return 0;
}

