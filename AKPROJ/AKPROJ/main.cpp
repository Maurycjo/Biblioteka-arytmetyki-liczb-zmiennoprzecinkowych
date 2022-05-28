#include <iostream>
#include "FloatNumber.h"
#include "Standard.h"

#include <bitset>
#include <bit>

void test(double x, double y, Standard::roundType round_type)
{
	std::cout << "*\n";

	Standard s(1, 2, round_type);
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
	

	numberC.multiply(numberA, numberB, round_type);
	numberC.displayNumberBinary();
}

void test_addition(double x, double y, Standard::roundType round_type)
{

	std::cout << "*\n";

	Standard s(1, 3, round_type);
	FloatNumber number;
	number.setStandard(s);
	number.dec2float(double(x + y));

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

	std::cout << "**addition**\n";

	numberC.addition(numberA, numberB, round_type);
	std::cout<<std::endl;
	numberC.displayNumberBinary();
	// numberC.displayNumberBinary();
}

int main()
{

	/*
	RS  11  695.12,123.68
	RS  10  826953728.0 ,1,
	RS  01  48.65,2223.22354
	RS  00  0.2500019073486328125 ,1.1
	*/
	//69.16,89.456
	test_addition(86.12,-16.89,Standard::roundType::TO_NEAREST_TIES_AWAY_FROM_ZERO);
	// test(695.12,123.68,Standard::roundType::TO_NEAREST_TIES_AWAY_FROM_ZERO);
	// test(695.12,123.68,Standard::roundType::TO_NEAREST_TIES_TO_EVEN);
	// test(-695.12,123.68,Standard::roundType::TOWARD_MINUS_INF);
	//test(0.00000762453121 ,1.111111111, Standard::roundType::TOWARD_PLUS_INF);
	// test(695.12,123.68,Standard::roundType::TOWARD_ZERO);
	/*

	double test_numbers[4][2] = {{695.12, 123.68},  {48.65, 2223.22354}, {0.2500019073486328125 ,1.1}};
	for (auto i : test_numbers)
	{
		
		std::cout<<"zaokraglenie symetryczne do parzystej " << std::endl;
		test(i[0],i[1], Standard::roundType::TO_NEAREST_TIES_AWAY_FROM_ZERO);
		std::cout<<"zaokraglenie symetryczne to wiekszej wartosci bezzwzglednej " << std::endl;
		test(i[0],i[1], Standard::roundType::TO_NEAREST_TIES_TO_EVEN);
		std::cout<<"zaokraglenie do minus nieskonczonosci " << std::endl;
		test(i[0],i[1], Standard::roundType::TOWARD_MINUS_INF);
		std::cout<<"zaokraglenie do plus nieskonczonosci  " << std::endl;
		test(i[0],i[1], Standard::roundType::TOWARD_PLUS_INF);
		std::cout<<"zaokraglenie do zera (obciecie) " << std::endl;
		test(i[0],i[1], Standard::roundType::TOWARD_ZERO);
		
	}

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
