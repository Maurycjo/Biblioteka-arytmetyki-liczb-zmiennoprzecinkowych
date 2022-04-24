#include <iostream>
#include "FloatNumber.h"
#include "Standard.h"


int main()
{
	Standard s(3, 4);
	FloatNumber number;
	number.setStandard(s);
	number.dec2float(14551.75);


	

	return 0;
}