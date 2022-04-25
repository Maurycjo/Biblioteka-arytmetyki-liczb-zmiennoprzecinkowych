#include <iostream>
#include "FloatNumber.h"
#include "Standard.h"


int main()
{
	Standard s(1, 3);
	FloatNumber number;
	number.setStandard(s);
	number.dec2float(1.0000000000000000000000000000000000000001);
	number.displayNumberBinary();


	

	return 0;
}