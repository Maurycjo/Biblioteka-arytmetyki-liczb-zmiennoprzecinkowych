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
	std::vector<uint8_t> floatNumberBits;
	


	int size;
	
	

public:
	void setStandard(Standard s);
	void dec2float(float inputNumber);
	void displayNumberBinary();

	
};

