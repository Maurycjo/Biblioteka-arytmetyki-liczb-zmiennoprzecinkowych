#pragma once
#include <fstream>
#include "FloatNumber.h"

class TimeKeeping
{

private:
	long long int frequency, start, elapsed;
	std::ofstream file;
public:
	TimeKeeping();
	long long read_QPC();
	void getRandomNumber(FloatNumber& number);
	void multiplyTime();
	void divTime();
	void addTime();


};