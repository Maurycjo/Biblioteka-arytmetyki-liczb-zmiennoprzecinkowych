#pragma once
#include "Standard.h"
#include <iterator>
#include <iostream>
#include <vector>
class FloatNumber
{
private:
	Standard s;
	bool sign;
	std::vector<uint8_t> floatNumberBits;							//vector liczby w standardzie
	uint8_t addTwoBytes(uint8_t byteA, uint8_t byteB, uint8_t& carry); // dodanie dwoch bajtow z wykrywaniemm przeniesienia
	void rlc(uint8_t &byte, uint8_t &rotCarry);						//rotacja w lewo z przeniesieniem 

public:

	void rrc(uint8_t& byte, uint8_t& rotCarry);						//rotacja w prawo z przeniesieniem 
	void rlcSevBytes(std::vector<uint8_t> &number);
	void rrcSevBytes(std::vector<uint8_t>& number);

	void setStandard(Standard s);
	void dec2float(float inputNumber);
	void displayNumberBinary();										//wyswietlenie liczby w formacie binarnym
	FloatNumber multiply(FloatNumber number1, FloatNumber number2);
	
};

