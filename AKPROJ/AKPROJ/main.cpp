#include <iostream>
#include "FloatNumber.h"
#include "Standard.h"
#include <bitset>
#include <bit>
#include "ConsoleApp.h"



int main()
{

	std::string konwert = "0|011000";
	FloatNumber number;
	Standard s(1, 1);
	number.setStandard(s);
	number.string2float(konwert);
	number.displayNumberBinary();
	std::cout << std::endl;
	std::cout << "GRS: " << int(number.bitG) << int(number.bitR) << int(number.bitS) << std::endl;






	return 0;
}	
