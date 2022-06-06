#include <iostream>
#include <math.h>
#include <cassert>
#include <cmath>
#include <bitset>
#include <string>

#include "FloatNumber.h"


void FloatNumber::setStandard(Standard s)
{
	this->s = s;
}

void FloatNumber::dec2float(double inputNumber)
{
	
	if (inputNumber == 0)
	{
		this->setResultToZero();
		this->sign = false;
		return;
	}

	std::vector<uint8_t> fracTab(s.getFraction()+1, 0);
	std::vector<uint8_t> expTab = generateBias();
	expTab.insert(expTab.begin(), 0);
	uint8_t carryFromAdd = 0, carryFromRot = 0, carryFromSubb = 0;
	bool denormalized = false;
	
	if (inputNumber < 0)
	{
		this->sign = 1;		//liczba ujemna
		inputNumber *= -1;
	}
	else
		this->sign = 0;		//liczba dodatnia

	long long int integerPart = floor(inputNumber);					//czesc calkowita liczby
	long double afterTheDecPoint = inputNumber - integerPart;	//czesc przecinkowa liczby
	long long tempNumber = integerPart;
	bool isInfinity;


	if (integerPart > 0)
	{
		//wyluskanie bitow mnoznika
		if (afterTheDecPoint != 0)
		{
			while (integerPart< (pow(2, ((s.getFraction() * 8) - 1))) && afterTheDecPoint>0)
			{
				integerPart <<= 1;
				afterTheDecPoint *= 2;
			
				if (afterTheDecPoint >= 1)
				{
					integerPart++;
					afterTheDecPoint -= 1;
				}
				decSevBytes(expTab);
			}
			tempNumber = integerPart;
		}

		//kodowanie bitow mnoznika
		while (tempNumber > 0 )
		{
			carryFromRot = 0;
			if (tempNumber % 2 == 1)
			{
				fracTab[0]+=0b10000000;
			}
			tempNumber /= 2;
		
			incSevBytes(expTab);
			rrcSevBytes(fracTab, carryFromRot);

			if (expTab[0]==1)
			{
				this->setResultToInfinity();
				return;
			}
		}
		decSevBytes(expTab);
		carryFromRot = 0;
		rlcSevBytes(fracTab, carryFromRot);
		carryFromRot = 0;
		rlcSevBytes(fracTab, carryFromRot);
	}
	else
	{
		while (afterTheDecPoint<1 && !denormalized)
		{

			afterTheDecPoint *= 2;
			decSevBytes(expTab);

			denormalized = true;
			for (auto i : expTab)
			{
				if (i > 0)
				{
					denormalized = false;
					break;
				}
			}
		}
		
		if (!denormalized)
			afterTheDecPoint--;
			
		for (int i = 0; i < (s.getFraction()+1) * 8 ; i++)
		{
			afterTheDecPoint *= 2;
			if (afterTheDecPoint > 1)
			{
				fracTab[s.getFraction()] += 1;
				afterTheDecPoint--;
			}
			carryFromRot = 0;
			rlcSevBytes(fracTab, carryFromRot);
		}
		carryFromRot = 0;
		rrcSevBytes(fracTab, carryFromRot);
	}

	expTab.erase(expTab.begin());
	fracTab.pop_back();


	uint8_t grsBits = fracTab[fracTab.size() - 1];

	if ((0b10000000 & grsBits) == 0b10000000){
		
		this->bitG = true;
	}

	if ((0b01000000 & grsBits) == 0b01000000)
		this->bitR = true;

	if (this->bitG)
		grsBits-= 0b10000000;
	if (this->bitR)
		grsBits-= 0b01000000;

	this->bitS = false;
	if (grsBits != 0)
	{
		this->bitS = true;
	}
	else if (tempNumber > 0 || afterTheDecPoint > 0)
	{
		this->bitS = true;
	}
	else
	{
		this->bitS = false;
	}

	for (auto i : expTab)
		this->floatNumberBits.push_back(i);

	for (auto i : fracTab)
		this->floatNumberBits.push_back(i);

	
	while (expTab.size() > 0)
		expTab.pop_back();

	while (fracTab.size() > 0)
		fracTab.pop_back();


}

void FloatNumber::string2float(std::string inputNumber)
{

	uint8_t carry = 0;

	bitG = false;
	bitR = false;
	bitS = false;

	if (inputNumber[0] == '0')
	{
		this->sign = false;
	}
	else if (inputNumber[0] == '1')
	{
		this->sign = true;
	}

	for (int i = 0; i < (s.getExponent()) + (s.getFraction()); i++)
	{
		this->floatNumberBits.push_back(0);
	}

	int x = 1;
	for (int i = 1; i <= floatNumberBits.size() * 8; i++)
	{

		if (inputNumber[x] == '\0')
		{
			for (int j = i; j <= floatNumberBits.size() * 8; j++)
			{
				carry = 0;
				rlcSevBytes(floatNumberBits, carry);
			}

			return;
		}

		if (inputNumber[x] == '1')
		{
			carry = 0;
			rlcSevBytes(floatNumberBits, carry);
			incSevBytes(floatNumberBits);
		}
		else if (inputNumber[x] == '0')
		{

			carry = 0;
			rlcSevBytes(floatNumberBits, carry);
		}
		else if (inputNumber[x] == '|' || inputNumber[x] == ' ')
		{
			i--;

		}
		else if (inputNumber[x] != '1' && inputNumber[x] != '0')
		{
			setResultToNaN();
			return;
		}
		x++;
	}

	bitS = false;
	int k = 0;
	while (inputNumber[x] != '\0')
	{
		if (inputNumber[x] != ' ' && inputNumber[x] != '|' && inputNumber[x] != '1' && inputNumber[x] != '0')
		{
			setResultToNaN();
			return;

		}
		else if (inputNumber[x] == ' ' || inputNumber[x] == '|')
		{
			k--;

		}
		else if (k == 0)
		{
			if (inputNumber[x] == '1')
			{
				bitG = true;
			}
			else
				bitG = false;
		}
		else if (k == 1)
		{
			if (inputNumber[x] == '1')
			{
				bitR = true;
			}
			else
				bitR = false;
		}
		else if (k > 1)
		{
			if (inputNumber[x] == '1')
			{
				bitS = true;
				return;
			}
		}
		k++;
		x++;
	}

}

void FloatNumber::displayNumberBinary()
{

	std::cout << sign << "|";

	for (int i = 0; i < s.getExponent(); i++)
	{
		std::cout << std::bitset<8>(floatNumberBits[i]) << " ";
	}
	std::cout << "|";
	for (int i = s.getExponent(); i < s.getFraction() + s.getExponent(); i++)
	{
		std::cout << std::bitset<8>(floatNumberBits[i]) << " ";
	}
	std::cout << std::endl;
}

uint8_t FloatNumber::addTwoBytes(uint8_t byteA, uint8_t byteB, uint8_t &carry)
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

uint8_t FloatNumber::subbTwoBytes(uint8_t minuend, uint8_t subtrahend, uint8_t &carry) // odjemna, odjemnik
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

void FloatNumber::rlc(uint8_t &byte, uint8_t &rotCarry)
{
	if (uint8_t(byte << 1) < byte)
	{
		byte <<= 1;
		byte += rotCarry;
		rotCarry = 1;
	}
	else
	{
		byte <<= 1;
		byte += rotCarry;
		rotCarry = 0;
	}
}

void FloatNumber::rrc(uint8_t &byte, uint8_t &rotCarry)
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

void FloatNumber::rlcSevBytes(std::vector<uint8_t> &number, uint8_t &carry)
{
	for (int i = number.size() - 1; i >= 0; i--)
	{
		rlc(number[i], carry);
	}
}

void FloatNumber::rrcSevBytes(std::vector<uint8_t> &number, uint8_t &carry)
{
	for (auto &i : number)
	{
		rrc(i, carry);
	}
}

void FloatNumber::incSevBytes(std::vector<uint8_t> &number)
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

void FloatNumber::decSevBytes(std::vector<uint8_t> &number)
{
	for (int i = number.size() - 1; i >= 0; i--)
	{

		if (number[i] > 0)
		{
			number[i]--;
			return;
		}
		else
		{
			number[i] = 255;
		}
	}
}

std::vector<uint8_t> FloatNumber::generateBias()
{
	std::vector<uint8_t> bias{0b01111111};

	while (bias.size() < s.getExponent())
	{
		bias.push_back(255);
	}
	return bias;
}

void FloatNumber::setResultToInfinity()
{

	for (int i = 0; i < s.getExponent(); i++)
		this->floatNumberBits.push_back(255);

	for (int i = 0; i < s.getFraction(); i++)
		this->floatNumberBits.push_back(0);

	bitG = false;
	bitR = false;
	bitS = false;

	std::cout << "INFINITY\n";
}

void FloatNumber::setResultToZero()
{
	this->sign = false;

	for (int i = 0; i < s.getExponent(); i++)
		this->floatNumberBits.push_back(0);

	for (int i = 0; i < s.getFraction(); i++)
		this->floatNumberBits.push_back(0);

	bitG = false;
	bitR = false;
	bitS = false;
}

void FloatNumber::setResultToNaN()
{

	while (this->floatNumberBits.size() > 0)
	{
		this->floatNumberBits.pop_back();
	}

	for (int i = 0; i < s.getExponent(); i++)
		this->floatNumberBits.push_back(255);

	for (int i = 0; i < s.getExponent() - 1; i++)
		this->floatNumberBits.push_back(0);

	this->floatNumberBits.push_back(1);

	bitG = false;
	bitR = false;
	bitS = false;
}

bool FloatNumber::ifInfinity(FloatNumber number)
{

	for (auto i : number.floatNumberBits)
	{
		if (i != 255)
			return false;
	}
	return true;
}

bool FloatNumber::ifZero(FloatNumber number)
{

	for (auto i : number.floatNumberBits)
	{
		if (i != 0)
			return false;
	}
	return true;
}

bool FloatNumber::ifNaN(FloatNumber number)
{

	for (int i = 0; i < s.getExponent(); i++)
	{
		if (i != 255)
			return false;
	}

	if (number.floatNumberBits[s.getExponent() + s.getFraction()] == 0)
		return false;

	return true;
}

bool FloatNumber::ifOne(FloatNumber number)
{

	if (number.floatNumberBits[0] != 0b01111111)
	{
		return false;
	}

	for (int i = 1; i < s.getExponent(); i++)
	{
		if (number.floatNumberBits[i] != 255)
		{
			return false;
		}
	}

	for (int i = s.getExponent(); i < s.getExponent() + s.getFraction(); i++)
	{
		if (number.floatNumberBits[i] != 0)
			return false;
	}

	return true;
}

void FloatNumber::multiply(FloatNumber numberA, FloatNumber numberB)
{
	//M1 *2^E1* M2*2E2=(M1*M2)*2^(E1+E2)

	this->bitG = false;
	this->bitR = false;
	this->bitS = false;
	this->setStandard(numberA.s);

	//0*INFINITY
	if (ifZero(numberA) && ifInfinity(numberB) || ifInfinity(numberA) && ifZero(numberB))
	{
		this->setResultToNaN();
		this->sign = true;
		return;
	}
	//0*n
	if (ifZero(numberA) || ifZero(numberB))
	{
		this->setResultToZero();
		this->sign = false;
		return;
	}
	//sprawdzenie znaku ilorazu
	bool resultSign = true;
	if (numberA.sign == false && numberB.sign == false)
	{
		resultSign = false;
	}
	else if (numberA.sign == true && numberB.sign == true)
	{
		resultSign = false;
	}
	this->sign = resultSign;
	//n*INFINITY, INFINITY*INFINITY
	if (ifInfinity(numberA) || ifInfinity(numberB))
	{
		this->setResultToInfinity();
		return;
	}
	if (ifOne(numberA))
	{
		for (auto i : numberB.floatNumberBits)
		{
			this->floatNumberBits.push_back(i);
		}
		return;
	}
	if (ifOne(numberB))
	{
		for (auto i : numberA.floatNumberBits)
		{
			this->floatNumberBits.push_back(i);
		}
		return;
	}

	//mnozniki
	std::vector<uint8_t> fracA;
	std::vector<uint8_t> fracB;
	std::vector<uint8_t> fracResult(s.getFraction() * 2 + 1, 0);		//inicjalizacja zerami
	//wykladniki
	std::vector<uint8_t> exponentA;
	std::vector<uint8_t> exponentB;
	std::vector<uint8_t> exponentResult(s.getExponent() + 1, 0);		//jeden dodatkowy bajt buforujacy
	std::vector<uint8_t> exponentBias;								//obciazenie

	for (int i = 0; i < s.getExponent(); i++)
	{
		exponentA.push_back(numberA.floatNumberBits[i]);
		exponentB.push_back(numberB.floatNumberBits[i]);
	}
	exponentBias = generateBias();

	for (int i = s.getExponent(); i < (s.getExponent() + s.getFraction()); i++)
	{
		fracA.push_back(numberA.floatNumberBits[i]);
		fracB.push_back(numberB.floatNumberBits[i]);
	}

	uint8_t carryFromRl = 0, carryFromRr = 0, carryFromAdd = 0, carryFromSubb = 0; //bajty przeniesienia rotacji w lewo, rotacji w prawo, dodawanie bajtow, odejmowania

	//wytworzenie bajtow wykladnika
	for (int i = (s.getExponent() - 1); i >= 0; i--)
	{
		exponentResult[i + 1] = addTwoBytes(exponentA[i], exponentB[i], carryFromAdd);
	}
	exponentResult[0] += carryFromAdd;

	//mamy dwa obciazenia wiec jedno trzeba odjac
	for (int i = (s.getExponent() - 1); i >= 0; i--)
	{
		exponentResult[i + 1] = subbTwoBytes(exponentResult[i + 1], exponentBias[i], carryFromSubb);
	}
	exponentResult[0] -= carryFromSubb;

	if (exponentResult[0] > 0)
	{
		setResultToInfinity();
		return;
	}

	exponentResult.erase(exponentResult.begin());		//usuniecie bufora


	fracA.insert(fracA.begin(), 1);	//dodanie bajtow z bitem ukrytym
	fracB.insert(fracB.begin(), 1);

	for (int i = 0; i < s.getFraction(); i++)
	{
		fracA.insert(fracA.begin(), 0);		//do przeskalowywania tej liczby potrzebne dwa razy wiecej bajtow
	}

	//algortym realizujacy wytworzenie bajtow mnoznika wyniku
	bool ifFracBZero = false;
	while (!ifFracBZero)
	{
		carryFromRr = 0;
		rrcSevBytes(fracB, carryFromRr);

		if (carryFromRr == 1)
		{

			carryFromAdd = 0;
			for (int j = s.getFraction() * 2; j >= 0; j--)
			{
				fracResult[j] = addTwoBytes(fracResult[j], fracA[j], carryFromAdd);		//dodanie przeskalowanego iloczynu czesciowego to mnoznika wyniku
			}
		}
		carryFromRl = 0;
		rlcSevBytes(fracA, carryFromRl);

		ifFracBZero = true;

		for (auto i : fracB)
		{
			if (i != 0)
			{
				ifFracBZero = false;
				break;
			}
		}

	}

	carryFromRl = 0;
	carryFromRr = 0;
	carryFromAdd = 0;

	bool ifInfinity = false;

	//skalowanie w prawo, do wytworzenia postac 1,xxxx
	if (fracResult[0] > 0)
	{
		while (fracResult[0] != 1)
		{
			carryFromRl = 0;
			rrcSevBytes(fracResult, carryFromRr);
			incSevBytes(exponentResult);
		}
	}
	else
	{
		//skalowanie w lewo do wytworzenia postac 1,xxxx

		while (fracResult[0] != 1 && ifInfinity == false)
		{
			carryFromRl = 0;
			rlcSevBytes(fracResult, carryFromRl);
			decSevBytes(exponentResult);

			ifInfinity = true;
			for (auto i : exponentResult)
			{
				if (i != 255)
				{
					ifInfinity = false;
					break;
				}
			}
		}
	}

	if (ifInfinity)
	{
		setResultToInfinity();
		return;
	}

	uint8_t grsBits = fracResult[s.getFraction() + 1];

	if ((0b10000000 & grsBits) == 0b10000000)
		this->bitG = true;

	if ((0b01000000 & grsBits) == 0b01000000)
		this->bitR = true;

	if (this->bitG)
		fracResult[s.getFraction() + 1] -= 0b10000000;
	if (this->bitR)
		fracResult[s.getFraction() + 1] -= 0b01000000;

	this->bitS = false;
	for (int i = s.getFraction() + 1; i < fracResult.size(); i++)
	{
		if (fracResult[i] != 0)
		{
			this->bitS = true;
			break;
		}
	}

	fracResult.erase(fracResult.begin());

	for (auto i : exponentResult)
		this->floatNumberBits.push_back(i);

	for (auto i : fracResult)
		this->floatNumberBits.push_back(i);
}

void FloatNumber::addition(FloatNumber numberA, FloatNumber numberB)
{
	bool sign = false;
	bool greaterB = false; // pomocnicze flagi
	bool greaterA = false;
	bool scaled = true;
	setStandard(numberA.s);
	// mnozniki
	std::vector<uint8_t> fracA;
	std::vector<uint8_t> fracB;
	std::vector<uint8_t> fractResult(s.getFraction() + 1, 0);

	// wykladniki
	std::vector<uint8_t> exponentA;
	std::vector<uint8_t> exponentB;
	std::vector<uint8_t> exponentBias;
	std::vector<uint8_t> exponentDiff(s.getExponent(), 0);
	std::vector<uint8_t> exponentResult;

	for (int i = 0; i < s.getExponent(); i++)
	{
		exponentA.push_back(numberA.floatNumberBits[i]);
		exponentB.push_back(numberB.floatNumberBits[i]);
	}

	for (int i = s.getExponent(); i < (s.getExponent() + s.getFraction()); i++)
	{
		fracA.push_back(numberA.floatNumberBits[i]);
		fracB.push_back(numberB.floatNumberBits[i]);
	}

	fracB.push_back(0); // przygotowanie bajtu aby trzymac w nim GRS
	fracA.push_back(0);
	numberA.prepGRS(fracA); // Wstawienie GRS na ostatni bajt
	numberB.prepGRS(fracB);

	uint8_t carryFromSub = 0, carryFromRr = 0, carryFromAdd = 0, carryFromLr = 0;

	for (int i = 0; i < s.getExponent(); i++) // Znalezienie większego wykładnika
	{
		if (exponentA[i] > exponentB[i])
		{
			greaterA = true;
			exponentResult = exponentA;						 // Wyjściowym wykladnikiem bedzie ten wiekszy
			for (int i = (s.getExponent() - 1); i >= 0; i--) // obliczanie roznicy miedzy 2 wykladnikami
			{
				exponentDiff[i] = subbTwoBytes(exponentA[i], exponentB[i], carryFromSub);
			}
			carryFromRr = 0;
			rrcSevBytes(fracB, carryFromRr); // Pierwsze skalowanie mnoznika
			decSevBytes(exponentDiff);
			fracB[0] = fracB[0] | 0b10000000; // wprowadzenie ukrytego bitu do mnoznika

			for (int i = 0; i < s.getExponent(); i++) // skalowanie mnoznika liczby
			{
				while (exponentDiff[i] != 0)
				{
					carryFromRr = 0;
					rrcSevBytes(fracB, carryFromRr);
					decSevBytes(exponentDiff);
				}
			}

			getGRS(fracB);	// ustawienie nowych bitow GRS po skalowaniu
			prepGRS(fracB); // ustawienie bitow grs na koncu mnoznika, potrzebne do dodawania
			break;
		}
		else if (exponentA[i] < exponentB[i]) // ten sam kodco wyzej tylko dla expB>expA
		{
			greaterB = true;
			exponentResult = exponentB;
			for (int i = (s.getExponent() - 1); i >= 0; i--)
			{
				exponentDiff[i] = subbTwoBytes(exponentB[i], exponentA[i], carryFromSub);
			}

			carryFromRr = 0;
			rrcSevBytes(fracA, carryFromRr);
			decSevBytes(exponentDiff);
			fracA[0] = fracA[0] | 0b10000000;

			for (int i = 0; i < s.getExponent(); i++)
			{
				while (exponentDiff[i] != 0)
				{
					carryFromRr = 0;
					rrcSevBytes(fracB, carryFromRr);
					decSevBytes(exponentDiff);
				}
			}
			getGRS(fracA);
			prepGRS(fracA);
			break;
		}
		else
		{
			// warunek w przypadku wielu wykladnikow
			if (i == s.getExponent() - 1)
			{
				exponentResult = exponentA;
				scaled = false;
			}
		}
	}

	if (numberA.sign == numberB.sign) // liczby maja takie same znaki, nie musimy zamieniac na u2
	{
		for (int i = (s.getFraction()); i >= 0; i--)
		{
			fractResult[i] = addTwoBytes(fracA[i], fracB[i], carryFromAdd);	//dodawanie bajtow od najmniej znaczacego
		}
		/*
		jesli wykladniki sa takie same to znaczy ze zawsze bedzie trzeba skalowac mnoznik,
		bo obie liczby posiadaja bit ukryty rowny 1
		*/
		if (exponentA == exponentB)
		{
			incSevBytes(exponentResult);
			carryFromRr = 0;
			rrcSevBytes(fractResult, carryFromRr);
			if (carryFromAdd) // jesli dodatkowo nastapilo przeniesienie z mnoznika to 1 bit po przeksalowaniu bedzie rowny 1
			{
				fractResult[0] = fractResult[0] | 0b10000000;
			}
		}
		/*
		Jesli ktorys z wykladnikow byl wiekszy, to znaczy ze trzeba bylo skalowac.
		Bit ukryty ednej liczby bedzie wtedy rowny 0.
		Jesli z mnoznika nie wystapil nadmiar, to liczby nie trzeba skalowac.
		W przeciwnym wypadku nalezy przeskalowac o jedno miejsce.
		*/
		else if (carryFromAdd)
		{
			carryFromRr = 0;
			rrcSevBytes(fractResult, carryFromRr);
			incSevBytes(exponentResult);
		}
	}
	else // Liczby maja rozne znaki i sa rozpatrowane w tym warunku
	{
		// Szukamy liczby wiekszej. Jesli wykladniki byly rowne to sprawdzamy mnozniki
		if (!greaterA && !greaterB)
		{
			for (int i = 0; i < s.getFraction(); i++)
			{
				// po znalezieniu wiekszego mnoznika, ustawiamy flagi wiekszej liczby
				if (int(fracA[i]) > int(fracB[i]))
				{
					greaterA = true;
					break;
				}
				else if (fracA[i] < fracB[i])
				{
					greaterB = true;
					break;
				}
			}
			if (!greaterA && !greaterB) // Jesli liczby byly takie same to ustawiamy 0
			{
				for (auto i : exponentResult)
				{
					this->floatNumberBits.push_back(0);
				}
				for (auto i : fractResult)
				{
					this->floatNumberBits.push_back(0);
				}
				this->sign = sign;
				return;
			}
		}


		if (greaterA) // Konwersja mniejszej liczby co do wartosci bezwzglednej na system u2
		{
			for (int i = 0; i < fracB.size(); i++)
			{
				fracB[i] = ~fracB[i];
			}
			incSevBytes(fracB);
			sign = numberA.sign;
		}
		else
		{
			for (int i = 0; i < fracA.size(); i++)
			{
				fracA[i] = ~fracA[i];
			}
			incSevBytes(fracA);
			sign = numberB.sign;
		}
		carryFromAdd = 0;
		for (int i = (s.getFraction()); i >= 0; i--)
		{
			fractResult[i] = addTwoBytes(fracA[i], fracB[i], carryFromAdd);
		}

		/*
		scaled -> Ktoras z liczb miala wiekszy wykladnik i mniejsza trzeba bylo skalowac
		carryFromAdd-> przeniesienie w dodawaniu mnoznikow
		!scaled && carryFromAdd -> (1)0.xxxx + (0)1.xxxx + carry = (0)0.xxxx TRZEBA SKALOWAC W LEWO
		scaled && !carryFromAdd -> (1)1.xxxx + (0)1.xxxx = (0)0.xxxx TRZEBA SKALOWAC W LEWO
		*/
		if ((!scaled && carryFromAdd) || (scaled && !carryFromAdd))
		{ // skalowanie w lewo do momentu 1.xxxx
			fractResult.insert(fractResult.begin(), 0);
			while (fractResult[0] != 1)
			{
				carryFromLr = 0;
				rlcSevBytes(fractResult, carryFromLr);
				decSevBytes(exponentResult);
			}
			fractResult.erase(fractResult.begin());
		}
	}


	getGRS(fractResult);
	fractResult.pop_back();

	for (auto i : exponentResult)
	{

		this->floatNumberBits.push_back(i);
	}
	for (auto i : fractResult)
	{
		this->floatNumberBits.push_back(i);
	}
	this->sign = sign;
	fracA.erase(fracA.begin(), fracA.end());
	fracB.erase(fracB.begin(), fracB.end());
}

void FloatNumber::round(roundType type)
{
	bitS = (bitR || bitS);
	bitR = bitG;

	if (bitR == 0 && bitS == 0)
		return;

	switch (type)
	{

	case TOWARD_ZERO:
		return;
	case TOWARD_PLUS_INF:
		if (((bitR == 1 || bitS == 1) && (this->sign == false)))
		{
			incSevBytes(this->floatNumberBits);
		}
		return;
	case TOWARD_MINUS_INF:
		if ((bitR == 1 || bitS == 1) && this->sign == true)
		{
			incSevBytes(this->floatNumberBits);
		}
		return;

	case TO_NEAREST_TIES_TO_EVEN:

		if (bitR == true && bitS == true)
		{
			incSevBytes(this->floatNumberBits);
		}
		else if (bitR == true && bitS == false)
		{
			incSevBytes(this->floatNumberBits);
		}
		return;

	case TO_NEAREST_TIES_AWAY_FROM_ZERO:

		if (bitR == true && bitS == true)
		{
			incSevBytes(this->floatNumberBits);
		}
		else if (bitR == true && bitS == false && ((this->floatNumberBits.back()) % 2) == 1)
		{
			incSevBytes(this->floatNumberBits);
		}
		return;
	}
}

void FloatNumber::division(FloatNumber divident, FloatNumber divisor)	//divident=dzielna, divisor=dzielnik
{
	// M1/M2*2^(E1-E2)
	this->bitG = false;
	this->bitR = false;
	this->bitS = false;
	this->setStandard(divident.s);

	// 0/0
	if (ifZero(divident) && ifZero(divisor))
	{
		setResultToNaN();
		return;
	}
	// INF/INF
	if (ifInfinity(divident) && ifInfinity(divisor))
	{
		setResultToNaN();
		return;
	}
	// 0/0
	if (ifZero(divident) && ifZero(divisor))
	{
		setResultToNaN();
		return;
	}
	// n/INF
	if (ifInfinity(divisor))
	{
		setResultToZero();
		return;
	}
	if (((divident.sign) && (divisor.sign)) || (!(divident.sign) && !(divisor.sign)))
		this->sign = false;
	else
		this->sign = true;
	// n/0
	if (ifZero(divisor))
	{
		setResultToInfinity();
		return;
	}
	if (ifOne(divisor))
	{
		for (auto i : divident.floatNumberBits)
			this->floatNumberBits.push_back(i);
		return;
	}

	//wykladniki
	std::vector<uint8_t> exponentDivident;	//wykladnik dzielnej
	std::vector<uint8_t> exponentDivisor;	//wykladnik dzielnika
	std::vector<uint8_t> exponentQuotient;	//wykladnik ilorazu

	for (int i = 0; i < s.getExponent(); i++)
	{
		exponentDivident.push_back(divident.floatNumberBits[i]);
		exponentDivisor.push_back(divisor.floatNumberBits[i]);
	}

	exponentQuotient = generateBias();
	exponentQuotient.insert(exponentQuotient.begin(), 0b00000010);

	uint8_t carry = 0;
	uint8_t carryFromRot = 0;
	bool ifInfinity;

	//algorytm obliczajacy wykladnik
	for (int i = s.getExponent() - 1; i >= 0; i--)
	{
		exponentQuotient[i + 1] = addTwoBytes(exponentQuotient[i + 1], exponentDivident[i], carry);
	}
	exponentQuotient[0] += carry;

	carry = 0;
	for (int i = s.getExponent() - 1; i >= 0; i--)
	{
		exponentQuotient[i + 1] = subbTwoBytes(exponentQuotient[i + 1], exponentDivisor[i], carry);
	}
	exponentQuotient[0] -= carry;

	if ((0b00000010 & exponentQuotient[0]) != 0b00000010)
	{
		std::cout << "ZDENORMALIZOWANE\n";
		setResultToZero();
		return;
	}
	if ((0b00000001 & exponentQuotient[0]) == 0b00000001)
	{
		//nieskonczonosc
		setResultToInfinity();
		return;
	}
	exponentQuotient.erase(exponentQuotient.begin());
	ifInfinity = true;

	for (auto i : exponentQuotient)
	{
		if (i != 255)
		{
			ifInfinity = false;
			break;
		}
	}
	if (ifInfinity)
	{
		setResultToInfinity();
		return;
	}
	//ta czesc kodu wykona sie kiedy liczba przed ewentualna normalizacja nie bedzie nieskonczonoscia i nie bedzie zdenormalizowana 
	//mnozniki
	std::vector<uint8_t> fracDivident;		//mnoznik dzielnej
	std::vector<uint8_t> fracDivisor;		//mnoznik dzielnika 
	std::vector<uint8_t> fracQuotient(s.getFraction() + 1);

	for (int i = s.getExponent(); i < (s.getExponent() + s.getFraction()); i++)
	{
		fracDivident.push_back(divident.floatNumberBits[i]);
		fracDivisor.push_back(divisor.floatNumberBits[i]);
	}
	fracDivisor.insert(fracDivisor.begin(), 1);		//bajt z bitem ukrytym
	fracDivident.insert(fracDivident.begin(), 1);

	//bajty na bufor
	for (int i = 0; i < (s.getFraction()); i++)
	{
		fracDivisor.push_back(0);
		fracDivident.push_back(0);
	}
	//wytworzenie bitu ukrytego
	carry = 0;
	for (int i = (s.getFraction()) * 2; i >= 0; i--)
	{
		fracDivident[i] = subbTwoBytes(fracDivident[i], fracDivisor[i], carry);
	}
	if (fracDivident[0] == 255)
	{
		decSevBytes(exponentQuotient);
	}
	else
	{
		incSevBytes(fracQuotient);
	}
	bool ifZero;

	while (fracQuotient[0] == 0)
	{
		ifZero = true;
		for (auto x : fracDivident)
			if (x != 0)
			{
				ifZero = false;
				break;
			}
		if (ifZero)
			break;

		carryFromRot = 0;
		rlcSevBytes(fracQuotient, carryFromRot);
		carryFromRot = 0;
		rrcSevBytes(fracDivisor, carryFromRot);		//skalowanie

		if (fracDivident[0] == 255)
		{
			carry = 0;
			for (int j = (s.getFraction()) * 2; j >= 0; j--)
			{
				fracDivident[j] = addTwoBytes(fracDivident[j], fracDivisor[j], carry); //dodawanie
			}
		}
		else
		{
			carry = 0;
			for (int j = (s.getFraction()) * 2; j >= 0; j--)
			{
				fracDivident[j] = subbTwoBytes(fracDivident[j], fracDivisor[j], carry); //odejmowanie
			}
		}
		if (fracDivident[0] != 255)
		{
			incSevBytes(fracQuotient);
		}

	}
	//bity GR
	for (int i = 0; i < 2; i++)
	{
		carryFromRot = 0;
		rrcSevBytes(fracDivisor, carryFromRot);		//skalowanie

		if (fracDivident[0] == 255)
		{
			carry = 0;
			for (int j = (s.getFraction()) * 2; j >= 0; j--)
			{
				fracDivident[j] = addTwoBytes(fracDivident[j], fracDivisor[j], carry); //dodawanie
			}
		}
		else
		{
			carry = 0;
			for (int j = (s.getFraction()) * 2; j >= 0; j--)
			{
				fracDivident[j] = subbTwoBytes(fracDivident[j], fracDivisor[j], carry); //odejmowanie
			}
		}
		if (fracDivident[0] != 255)
		{

			if (i == 0)
			{
				this->bitG = true;
			}
			else if (i == 1)
			{
				this->bitR = true;
			}
		}
	}

	//bitS sprawdzany czy reszta zdzielenia jest nie zerowa
	bitS = false;
	for (auto i : fracDivident)
	{
		if (i != 0)
		{
			this->bitS = true;
			break;
		}

	}
	fracQuotient.erase(fracQuotient.begin());

	for (auto i : exponentQuotient)
		this->floatNumberBits.push_back(i);

	for (auto i : fracQuotient)
		this->floatNumberBits.push_back(i);
}

FloatNumber::~FloatNumber()
{

	while (floatNumberBits.size() > 0)
	{
		this->floatNumberBits.pop_back();
	}

	this->bitG = false;
	this->bitR = false;
	this->bitS = false;
}

void FloatNumber::signNegation()
{
	this->sign = !(this->sign);
}

void FloatNumber::setRoundType(roundType type)
{

	this->type = type;

}

roundType FloatNumber::getRoundType()
{
	return type;
}

void FloatNumber::getGRS(std::vector<uint8_t> bytes)
{
	uint8_t byte = bytes[s.getFraction()];

	bitG = byte & 0b10000000;
	bitR = byte & 0b01000000;
	bitS = byte & 0b00111111;

	if (!bitS)
	{
		for (int i = s.getFraction() + 1; i < bytes.size(); i++)
		{
			bitS = bytes[i];
			if (bitS);
			break;
		}
	}
}

void FloatNumber::prepGRS(std::vector<uint8_t>& bytes)
{

	uint8_t byte = bytes[s.getFraction()];
	byte = 0b00000000;

	if (bitG)
		byte = byte | 0b10000000;
	if (bitR)
		byte = byte | 0b01000000;
	if (bitS)
		byte = byte | 0b00100000;

	bytes[s.getFraction()] = byte;
}

std::vector<uint8_t> FloatNumber::get_bits_for_testing()
{
	return floatNumberBits;
}
bool FloatNumber::get_sign()
{
	return sign;
}

void FloatNumber::setRandomNumber()
{





}