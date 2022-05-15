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

	numberC.multiply(numberA, numberB);
	numberC.displayNumberBinary();


}

int main()
{

	/*
		Liczby do przetestowania zaokraglen:
		RS 11  3.5
		RS 10  3
		RS 01  2.5
		RS 00  2
	*/

	//RS 00
	/*
	std::cout << "=========================" << std::endl;
	test(1,2,Standard::roundType::TO_NEAREST_TIES_AWAY_FROM_ZERO);
	std::cout << "=========================" << std::endl;
	test(1,2,Standard::roundType::TO_NEAREST_TIES_TO_EVEN);
	std::cout << "=========================" << std::endl;
	test(1,2,Standard::roundType::TOWARD_MINUS_INF);
	std::cout << "=========================" << std::endl;
	test(1,2,Standard::roundType::TOWARD_PLUS_INF);
	std::cout << "=========================" << std::endl;
	test(1,2,Standard::roundType::TOWARD_ZERO);
	std::cout << "=========================" << std::endl;
	*/
	
	//RS 01
	std::cout << "=========================" << std::endl;
	test(69.4568,85.5123,Standard::roundType::TO_NEAREST_TIES_AWAY_FROM_ZERO);
	std::cout << "=========================" << std::endl;
	test(69.4568,85.5123,Standard::roundType::TO_NEAREST_TIES_TO_EVEN);
	std::cout << "=========================" << std::endl;
	test(69.4568,85.5123,Standard::roundType::TOWARD_MINUS_INF);
	std::cout << "=========================" << std::endl;
	test(69.4568,85.5123,Standard::roundType::TOWARD_PLUS_INF);
	std::cout << "=========================" << std::endl;
	test(69.4568,85.5123,Standard::roundType::TOWARD_ZERO);
	std::cout << "=========================" << std::endl;	
	//RS10
	//test(1,3,Standard::roundType::TO_NEAREST_TIES_AWAY_FROM_ZERO);
	//test(1,3,Standard::roundType::TO_NEAREST_TIES_TO_EVEN);
	//test(1,3,Standard::roundType::TOWARD_MINUS_INF);
	//test(1,3,Standard::roundType::TOWARD_PLUS_INF);
	//test(1,3,Standard::roundType::TOWARD_ZERO);

	//RS 11
	//test(1,3.5,Standard::roundType::TO_NEAREST_TIES_AWAY_FROM_ZERO);
	//test(1,3.5,Standard::roundType::TO_NEAREST_TIES_TO_EVEN);
	//test(1,3.5,Standard::roundType::TOWARD_MINUS_INF);
	//test(1,3.5,Standard::roundType::TOWARD_PLUS_INF);
	//test(1,3.5,Standard::roundType::TOWARD_ZERO);

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

