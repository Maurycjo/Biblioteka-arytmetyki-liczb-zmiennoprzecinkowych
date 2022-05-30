#include <iostream>
#include <vector>






uint8_t subbTwoBytes(uint8_t minuend, uint8_t subtrahend, uint8_t &carry) // odjemna, odjemnik
{
	uint16_t mask = 0b0000000011111111; // maska do mlodszej czesci liczby
	uint16_t temp = 256 + minuend;
	uint8_t result;

	temp = temp - subtrahend - carry;

	if (temp < 256)
	{
		carry = 1;
	}
	else
		carry = 0;

	result = mask & temp;

	return result;
}