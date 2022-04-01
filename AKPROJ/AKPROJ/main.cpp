#include <iostream>
#include "FloatNumber.h"
#include "Standart.h"

using namespace std;

int main()
{
	Standart s(3, 4);
	FloatNumber num(s);

	int testNumber = 420;
	cout << testNumber << endl;

	num.dec2float(testNumber);

	

	return 0;
}