#include <iostream>


uint8_t addTwoBytes(uint8_t byteA, uint8_t byteB, uint8_t &carry)
{
	uint16_t mask = 0b0000000011111111; // maska do mlodszej czesci liczby

	uint16_t tempResult = byteA + byteB + carry;
	uint8_t result;

	if ((tempResult & mask) == tempResult)
	{
		carry = 0; // brak przeniesienia
	}
	else
	{
		carry = 1;
	}
	result = tempResult;
	return result;
}