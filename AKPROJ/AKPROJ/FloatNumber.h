#pragma once
#include "Standart.h"
#include <iterator>
#include <iostream>
#include <vector>
class FloatNumber
{
private:
	Standart s;
	bool* table;
	bool* grs;
	int size;
	
	

public:
	FloatNumber(Standart s);
	~FloatNumber();
	void dec2float(float inputNumber);

	
};

