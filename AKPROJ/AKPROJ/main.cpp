#include <iostream>
#include "FloatNumber.h"
#include "Standart.h"

using namespace std;

int main()
{
	Standart s(3, 4);
	FloatNumber num(s);
	num.dec2float(0.1875);


	

	return 0;
}