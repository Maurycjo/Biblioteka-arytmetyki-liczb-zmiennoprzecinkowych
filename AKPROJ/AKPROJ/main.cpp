#include <iostream>
#include "FloatNumber.h"
#include "Standard.h"
#include <bitset>
#include <bit>
#include "ConsoleApp.h"



int main()
{

	//ConsoleApp consoleapp;


	Standard s(1, 1);
	FloatNumber number;
	number.setStandard(s);
	number.dec2float(1246816875.152152);
	number.displayNumberBinary();

	return 0;
}	
