#include <iostream>
#include <math.h>
#include <cmath>
#include <bitset>


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

	this->floatNumberBits.reserve(expTab.size() + fracTab.size());
	this->floatNumberBits.insert(floatNumberBits.end(), expTab.begin(), expTab.end());
	this->floatNumberBits.insert(floatNumberBits.end(), fracTab.begin(), fracTab.end());


}

void FloatNumber::dec2float_alpha(double inputNumber)
{

	//zero
	if (inputNumber == 0)
	{
		this->setResultToZero();
		this->sign = false;
		return;
	}


	std::vector<uint8_t> fracTab;						//vector mnoznika
	std::vector<uint8_t> expTab;						//vector wykladnika 

	uint8_t byte = 0b00000000;							//bajt do zapisu do vectora
	uint8_t byteIterator = 0b10000000;					//bajt do zwiekszania bajtu

	int expBias = pow(2, (s.getExponent()*8 - 1)) - 1;	//obciazenie wykladnika		
	int expMaxRange = pow(2, s.getExponent()*8)-2-expBias;//maksymalna warosc wykladnika 
	int expMinRange = 1 - expBias;						//min wartosc wykladnika
	bool denormalized = false;							//czy liczba zdenormalizowana

	if (inputNumber < 0)
	{
		this->sign = 1;		//liczba ujemna
		inputNumber *= -1;
	}
	else
		this->sign = 0;		//liczba dodatnia


	int number = inputNumber;							//czesc calkowita liczby
	float afterTheDecPoint = inputNumber - number;		//czesc przecinkowa liczby
	int decPlace = 0;									//miejsce przecinka, wykladnik
	int tempNumber = number;							//liczba pomocnicza
	int fracIterator = 0;								//iterator po mnozniku

	


	while (tempNumber > 0 && decPlace!=expMaxRange+1)
	{
		tempNumber /= 2;
		decPlace++;
	}

	//nieskonoczonosc 
	if (decPlace > expMaxRange)
	{
		this->setResultToInfinity();
		return;
	}

	if (decPlace > 0)
	{
		decPlace--;
		
		if (number / int(pow(2, decPlace)) == 1)
		{
			number = number - pow(2, decPlace);	
		}	

		//konwersja czesci calkowitej, tylko wtedy kiedy ta czesc calkowita istnieje
		for (int i = 0; i < decPlace; i++)
		{
		
			if(number/int(pow(2, decPlace-i-1))==1)
			{
				//std::cout << "tuatj\n";
				number = number - int(pow(2, decPlace-i-1));
				byte += byteIterator;
			}

			byteIterator>>= 1;

			if (byteIterator == 0b00000000)
			{
				fracTab.push_back(byte);
				byteIterator = 0b10000000;
				byte = 0;
			}
			fracIterator++;
		}
	}
	else //przypadek kiedy liczba <1, wtedy tez trzeba ustalic czy liczbe trzeba zdenormalizowac
	{
		
		//ustalenie miejsca przecinka
		while (afterTheDecPoint < 1)
		{
			afterTheDecPoint *= 2;
			decPlace--;
			if (decPlace == expMinRange)
			{
				denormalized = true;
				decPlace--;
				break;
			}
		}
	
		//pierwszy bit jest ukryty
		if(!denormalized)
		afterTheDecPoint -= 1;

	}
	//konwersja czesci przecinkowej
	while ((fracIterator < s.getFraction() * 8)&&afterTheDecPoint!=0)
	{
		afterTheDecPoint *= 2;
		if (afterTheDecPoint >= 1)
		{
			byte += byteIterator;
			afterTheDecPoint -= 1;
		}

		byteIterator >>= 1;

		if (byteIterator == 0)
		{
			fracTab.push_back(byte);
			byte = 0;
			byteIterator = 0b10000000;
		}
		fracIterator++;
	}

	if (fracIterator < s.getFraction()*8)
	{
		fracTab.push_back(byte);
		byte = 0;
	}
	while (fracTab.size() != s.getFraction())
	{
		fracTab.push_back(0);
	}


	//konwersja wykladnika
	byte = 0;
	byteIterator = 0b00000001;

	//std::cout << "wykladnik: " << decPlace << std::endl;


	if (decPlace > expMaxRange)
	{
		this->setResultToInfinity();
		return;
	}
	decPlace += expBias;

	while (decPlace>0)
	{

		if (decPlace % 2 == 1)
		{
			byte += byteIterator;
		}

		byteIterator <<= 1;
		if (byteIterator == 0)
		{
			expTab.insert(expTab.begin(), byte);
			byte = 0;
			byteIterator = 0b00000001;

		}
		decPlace /= 2;
	}

	if (byteIterator != 1)
	{
		expTab.insert(expTab.begin(), byte);
	}
	while (expTab.size() != s.getExponent())
	{
		expTab.insert(expTab.begin(), 0);
	}


	this->floatNumberBits.reserve(expTab.size() + fracTab.size());
	this->floatNumberBits.insert(floatNumberBits.end(), expTab.begin(), expTab.end());
	this->floatNumberBits.insert(floatNumberBits.end(), fracTab.begin(), fracTab.end());

	
	if(denormalized)
	std::cout << "\ndenormalized"<< std::endl;
	
}

void FloatNumber::displayNumberBinary()
{

	std::cout << sign << "|";

	for (int i = 0; i < s.getExponent(); i++)
	{
		//std::cout << std::format("{:b}", this->floatNumberBits[i]) << " ";
		std::cout << std::bitset<8>(floatNumberBits[i]) << " ";
	}
	std::cout << "|";
	for (int i = s.getExponent(); i < s.getFraction()+s.getExponent(); i++)
	{
		//std::cout << std::format("{:b}", this->floatNumberBits[i]) << " ";
		std::cout << std::bitset<8>(floatNumberBits[i]) << " ";
	}
	std::cout << std::endl;

}

uint8_t FloatNumber::addTwoBytes(uint8_t byteA, uint8_t byteB, uint8_t& carry)
{
		uint16_t mask = 0b0000000011111111;		//maska do mlodszej czesci liczby

		uint16_t tempResult = byteA + byteB + carry;
		uint8_t result;

		if ((tempResult & mask) == tempResult)
		{
			carry = 0;	//brak przeniesienia
		}
		else
		{
			carry = 1;
		}
		result = tempResult;
		return result;
}

uint8_t FloatNumber::subbTwoBytes(uint8_t minuend, uint8_t subtrahend, uint8_t& carry)	//odjemna, odjemnik
{
	uint16_t mask = 0b0000000011111111;		//maska do mlodszej czesci liczby
	uint16_t temp = 256 + minuend;
	uint8_t result;

	temp = temp- subtrahend - carry;

	if (temp < 256)
	{
		carry = 1;
	}
	else
		carry = 0;

	result = mask & temp;

	return result;
}

void FloatNumber::rlc(uint8_t& byte, uint8_t& rotCarry)
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

void FloatNumber::rrc(uint8_t& byte, uint8_t& rotCarry)
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

void FloatNumber::rlcSevBytes(std::vector<uint8_t> &number, uint8_t& carry)
{
	for (int i = number.size() - 1; i >= 0; i--)
	{
		rlc(number[i], carry);
	}
}

void FloatNumber::rrcSevBytes(std::vector<uint8_t>& number, uint8_t& carry)
{
	for (auto &i : number)
	{
		rrc(i, carry);
	}
}

void FloatNumber::incSevBytes(std::vector<uint8_t>& number)
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

void FloatNumber::decSevBytes(std::vector<uint8_t>& number)
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
	std::vector<uint8_t> bias{ 0b01111111 };

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

	std::cout << "INFINITY\n";
}

void FloatNumber::setResultToZero()
{

	for (int i = 0; i < s.getExponent(); i++)
		this->floatNumberBits.push_back(0);
	

	for (int i = 0; i < s.getFraction(); i++)
		this->floatNumberBits.push_back(0);

}

void FloatNumber::setResultToNaN()
{
	for (int i = 0; i < s.getExponent(); i++)
		this->floatNumberBits.push_back(255);

	
	for (int i = 0; i < s.getExponent()-1; i++)
		this->floatNumberBits.push_back(0);

	this->floatNumberBits.push_back(1);

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

	for (int i=0;i<s.getExponent();i++)
	{
		if (i != 255)
			return false;
	}
	
	if (number.floatNumberBits[s.getExponent() + s.getFraction()] == 0)
		return false;

	return true;
}



void FloatNumber::setBitToRound(bool bitR, bool bitS)
{

	this->bitR = bitR;
	this->bitS = bitS;
}

void FloatNumber::clearBitsToRound()
{

	this->bitR = 0;
	this->bitS = 0;
}



void FloatNumber::round(RoundType currentRound)
{

	
	//fracTab.insert(fracTab.begin(), this->floatNumberBits.begin() + s.getExponent(), this->floatNumberBits.end());
	
	bool bitR, bitS;




	switch (currentRound)
	{
		case RoundType::TOWARD_ZERO:
		{

			clearBitsToRound();
			return;


		}
		case RoundType::TOWARD_PLUS_INF:
		{

			if (this->sign == true)
			{
				clearBitsToRound();
				return;
			}
			else
			{
				incSevBytes(this->floatNumberBits);
			}

		}
		case RoundType::TOWARD_MINUS_INF:
		{
			if (this->sign == false)
			{
				clearBitsToRound();
				return;
			}
			else
			{
				incSevBytes(this->floatNumberBits);
				
			}


		}
		case RoundType::TO_NEAREST_TIES_TO_EVEN:
		{



		}
		case RoundType::TO_NEAREST_TIES_AWAY_FROM_ZERO:
		{



		}

	}


}



void FloatNumber::multiply(FloatNumber numberA, FloatNumber numberB)
{
	//M1 *2^E1* M2*2E2=(M1*M2)*2^(E1+E2)

	this->setStandard(numberA.s);

	//0*INFINITY
	if (ifZero(numberA) && ifInfinity(numberB)||ifInfinity(numberA)&&ifZero(numberB))
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
	else if (numberA.sign == true&& numberB.sign == true)
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

	//mnozniki
	std::vector<uint8_t> fracA;
	std::vector<uint8_t> fracB;
	std::vector<uint8_t> fracResult(s.getFraction() * 2+1, 0);		//inicjalizacja zerami
	fracA.reserve(s.getFraction());
	fracB.reserve(s.getFraction());	
	fracA.insert(fracA.begin(), numberA.floatNumberBits.begin() + s.getExponent(), numberA.floatNumberBits.end());
	fracB.insert(fracB.begin(), numberB.floatNumberBits.begin() + s.getExponent(), numberB.floatNumberBits.end());
	//wykladniki
	std::vector<uint8_t> exponentA;
	std::vector<uint8_t> exponentB;
	std::vector<uint8_t> exponentResult(s.getExponent()+1, 0);		//jeden dodatkowy bajt buforujacy
	std::vector<uint8_t> exponentBias;								//obciazenie
	exponentA.reserve(s.getExponent());
	exponentB.reserve(s.getExponent());
	exponentA.insert(exponentA.begin(), numberA.floatNumberBits.begin(), numberA.floatNumberBits.begin() + s.getExponent());
	exponentB.insert(exponentB.begin(), numberB.floatNumberBits.begin(), numberB.floatNumberBits.begin() + s.getExponent());
	exponentBias = generateBias();

	
	uint8_t carryFromRl = 0, carryFromRr = 0, carryFromAdd = 0, carryFromSubb = 0; //bajty przeniesienia rotacji w lewo, rotacji w prawo, dodawanie bajtow, odejmowania

	//wytworzenie bajtow wykladnika
	for (int i = (s.getExponent()-1); i >= 0; i--)
	{
		exponentResult[i+1] = addTwoBytes(exponentA[i], exponentB[i], carryFromAdd);
	}
	exponentResult[0] += carryFromAdd;
	
	//mamy dwa obciazenia wiec jedno trzeba odjac
	for (int i = (s.getExponent()-1); i >= 0; i--)
	{
		exponentResult[i+1] = subbTwoBytes(exponentResult[i+1], exponentBias[i], carryFromSubb);
	}
	exponentResult[0] -= carryFromSubb;

	if (exponentResult[0] > 0)
	{
		std::cout << "infinity\n";
		setResultToInfinity();
		return;
	}

	exponentResult.erase(exponentResult.begin());		//usuniecie bufora


	//tymaczasowo przyjmuje ze liczby nie sa zdenormalizowane(do zmiany!!!)

	fracA.insert(fracA.begin(), 1);	//dodanie bajtow z bitem ukrytym
	fracB.insert(fracB.begin(), 1);

	for (int i = 0; i < s.getFraction(); i++)
	{
		fracA.insert(fracA.begin(), 0);		//do przeskalowywania tej liczby potrzebne dwa razy wiecej bajtow
	}

	//algortym realizujacy wytworzenie bajtow mnoznika wyniku
	for (int i = 0; i < (s.getFraction()+1) * 8; i++)
	{
		carryFromRr = 0;
		rrcSevBytes(fracB, carryFromRr);

		if (carryFromRr == 1)
		{
			carryFromAdd = 0;
			for (int j = s.getFraction()*2; j>=0; j--)
			{
				fracResult[j] = addTwoBytes(fracResult[j], fracA[j], carryFromAdd);		//dodanie przeskalowanego iloczynu czesciowego to mnoznika wyniku
			}
		}
		carryFromRl = 0;
		rlcSevBytes(fracA, carryFromRl);
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



	/*
	tu bedzie wywolanie metedy zaokraglajacej GRS
	*/

	fracResult.erase(fracResult.begin());

	while (fracResult.size() != s.getFraction())
	{
		fracResult.pop_back();

	}
	
	for (auto i : exponentResult)
		this->floatNumberBits.push_back(i);

	for (auto i : fracResult)
		this->floatNumberBits.push_back(i);

}