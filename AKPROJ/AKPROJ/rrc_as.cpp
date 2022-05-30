#include <iostream>

void rrc(uint8_t &byte, uint8_t &rotCarry)
{
	if (rotCarry == 0)
	{
		if (byte % 2 == 1)
		{
			rotCarry = 1;
		}
		else
			rotCarry = 0;

		byte >>= 1;
	}
	else
	{
		if (byte % 2 == 1)
		{
			rotCarry = 1;
		}
		else
			rotCarry = 0;

		byte >>= 1;
		byte += 0b10000000;
	}
}