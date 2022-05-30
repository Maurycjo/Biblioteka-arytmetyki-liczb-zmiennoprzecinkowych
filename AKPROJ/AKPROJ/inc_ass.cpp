#include <iostream>
#include <vector>


void incSevBytes(std::vector<uint8_t> &number)
{
	for (int i = number.size() - 1; i >= 0; i--)
	{
		if (uint8_t(number[i] + 1) > number[i])
		{
			number[i]++;
			return;
		}
		else
		{
			number[i]++;
		}
	}
}