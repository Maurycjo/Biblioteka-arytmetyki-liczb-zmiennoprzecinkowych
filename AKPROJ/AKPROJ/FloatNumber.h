#pragma once
#include "Standart.h"
class FloatNumber
{
private:
	Standart s;
	bool* table;
	bool* grs;
	int size;

	bool* dec2binary(int number); //return binary
	bool* binary2float(bool* binary);//return float

public:
	FloatNumber(Standart s);
	void dec2float(int number);

	
};

