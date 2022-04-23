#pragma once
#include "Standard.h"
#include <iterator>
#include <iostream>
#include <vector>
class FloatNumber
{
private:
	Standard s;
	std::vector<uint8_t> table;
	std::vector<uint8_t> grs;
	int size;
	
	

public:
	void setStandard(Standard s);
	void dec2float(float inputNumber);

	
};

