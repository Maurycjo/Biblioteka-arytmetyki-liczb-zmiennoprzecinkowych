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

	std::vector<uint8_t> fracTab(s.getFraction()+2, 0);
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

	if ((0b10000000 & grsBits) == 0b10000000)
		this->bitG = true;

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

	std::cout << "GRS: " << int(bitG) << int(bitR) << int(bitS);

	std::cout << "temp" << tempNumber << std::endl;
	std::cout << "frac" << afterTheDecPoint<< std::endl;

	for (auto i : fracTab)
	{
		std::cout << std::bitset<8>(i) << " ";
	}
	std::cout << std::endl;




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

	// konwersja wykladnika
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

void FloatNumber::string2float(std::string inputNumber)
{

	uint8_t carry = 0;

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
	for (int i = 1; i <=floatNumberBits.size()*8; i++)
	{

		if (inputNumber[x] == '\0')
		{
			for (int j = i; j <= floatNumberBits.size()*8; j++)
			{
				carry = 0;
				rlcSevBytes(floatNumberBits, carry);
			}
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
		}
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

	while (this->floatNumberBits.size()>0)
	{
		this->floatNumberBits.pop_back();
	}

	for (int i = 0; i < s.getExponent(); i++)
		this->floatNumberBits.push_back(255);

	
	for (int i = 0; i < s.getExponent()-1; i++)
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

	for (int i=0;i<s.getExponent();i++)
	{
		if (i != 255)
			return false;
	}
	
	if (number.floatNumberBits[s.getExponent() + s.getFraction()] == 0)
		return false;

	return true;
}

void FloatNumber::multiply(FloatNumber numberA, FloatNumber numberB)
{
	//M1 *2^E1* M2*2E2=(M1*M2)*2^(E1+E2)

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

	//mnozniki
	std::vector<uint8_t> fracA;
	std::vector<uint8_t> fracB;
	std::vector<uint8_t> fracResult(s.getFraction() * 2 + 1, 0);		//inicjalizacja zerami
	fracA.reserve(s.getFraction());
	fracB.reserve(s.getFraction());
	fracA.insert(fracA.begin(), numberA.floatNumberBits.begin() + s.getExponent(), numberA.floatNumberBits.end());
	fracB.insert(fracB.begin(), numberB.floatNumberBits.begin() + s.getExponent(), numberB.floatNumberBits.end());
	//wykladniki
	std::vector<uint8_t> exponentA;
	std::vector<uint8_t> exponentB;
	std::vector<uint8_t> exponentResult(s.getExponent() + 1, 0);		//jeden dodatkowy bajt buforujacy
	std::vector<uint8_t> exponentBias;								//obciazenie
	exponentA.reserve(s.getExponent());
	exponentB.reserve(s.getExponent());
	exponentA.insert(exponentA.begin(), numberA.floatNumberBits.begin(), numberA.floatNumberBits.begin() + s.getExponent());
	exponentB.insert(exponentB.begin(), numberB.floatNumberBits.begin(), numberB.floatNumberBits.begin() + s.getExponent());
	exponentBias = generateBias();


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
		std::cout << "infinity\n";
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
	for (int i = 0; i < (s.getFraction() + 1) * 8; i++)
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

	while (fracResult.size() != s.getFraction())
	{
		fracResult.pop_back();

	}

	for (auto i : exponentResult)
		this->floatNumberBits.push_back(i);

	for (auto i : fracResult)
		this->floatNumberBits.push_back(i);

}

void FloatNumber::addition(FloatNumber numberA, FloatNumber numberB)
{
	bool sign = false;
	bool greaterB = false;
	bool greaterA = false;
	bool scaled = true;
	setStandard(numberA.s);
	// mnozniki
	std::vector<uint8_t> fracA;
	std::vector<uint8_t> fracB;
	std::vector<uint8_t> fractResult(s.getFraction() + 1, 0);
	fracA.reserve(s.getFraction());
	fracB.reserve(s.getFraction());
	fracA.insert(fracA.begin(), numberA.floatNumberBits.begin() + s.getExponent(), numberA.floatNumberBits.end());
	fracB.insert(fracB.begin(), numberB.floatNumberBits.begin() + s.getExponent(), numberB.floatNumberBits.end());

	// wykladniki
	std::vector<uint8_t> exponentA;
	std::vector<uint8_t> exponentB;
	std::vector<uint8_t> exponentBias;
	std::vector<uint8_t> exponentDiff(s.getExponent(), 0);
	std::vector<uint8_t> exponentResult;

	exponentA.reserve(s.getExponent());
	exponentB.reserve(s.getExponent());
	exponentA.insert(exponentA.begin(), numberA.floatNumberBits.begin(), numberA.floatNumberBits.begin() + s.getExponent());
	exponentB.insert(exponentB.begin(), numberB.floatNumberBits.begin(), numberB.floatNumberBits.begin() + s.getExponent());
	exponentBias = generateBias();

	fracB.insert(fracB.end(), 0); // przygotowanie bajtu aby trzymac w nim GRS
	fracA.insert(fracA.end(), 0);

	uint8_t carryFromSub = 0, carryFromRr = 0, carryFromAdd = 0, carryFromLr = 0;

	for (int i = 0; i < s.getExponent(); i++) // Sprawdz ktory wykladnik jest wiekszy
	{
		if (exponentA[i] > exponentB[i])
		{
			greaterA = true;
			exponentResult = exponentA;
			for (int i = (s.getExponent() - 1); i >= 0; i--)
			{
				exponentDiff[i] = subbTwoBytes(exponentA[i], exponentB[i], carryFromSub);
			}

			carryFromRr = 0;
			rrcSevBytes(fracB, carryFromRr);
			decSevBytes(exponentDiff);
			fracB[0] = fracB[0] | 0b10000000;

			while (exponentDiff[0] != 0) // przeskalowanie mnoznnika liczby z mniejszym wykladnikiem
			{
				carryFromRr = 0;
				rrcSevBytes(fracB, carryFromRr);
				decSevBytes(exponentDiff);
			}
			// getGRS(fracB);
			for (int i = 0; i < s.getFraction(); i++)
			{
				std::cout << "Skalowanie B : " << int(fracB[i]) << std::endl;
			}
		}
		else if (exponentA[i] < exponentB[i])
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
			fracA[0] = fracA[0] | 0b10000000; // ustalic czy w u2 czy nie

			while (exponentDiff[0] != 0)
			{
				carryFromRr = 0;
				rrcSevBytes(fracA, carryFromRr);
				decSevBytes(exponentDiff);
			}
			// getGRS(fracA);
			for (int i = 0; i < s.getFraction(); i++)
			{
				std::cout << "Skalowanie A : " << int(fracA[i]) << std::endl;
			}
		}
		else
		{
			exponentResult=exponentA;
			scaled = false;
		}

		std::cout << "A: " << int(exponentA[i]) << " B: " << int(exponentB[i]) << std::endl;
	}

	if (numberA.sign == numberB.sign)
	{ // obie liczby sa dodatnie
		// numberA.getGRS(fracA);
		// numberB.getGRS(fracB); // Tutaj bity maja byc juz przypisane do liczby!!!

		// numberA.prepGRS(fracA); // Jak zostanie naprawiona konwersja to odkomentowac
		// numberB.prepGRS(fracB);
		// std::cout << "Ostatni bajt: " << int(fracB[s.getFraction()]) << std::endl;

		// std::cout << "A GRS: " << numberA.Gbit << numberA.Rbit << numberA.Sbit << std::endl;
		// std::cout << "B GRS: " << numberB.Gbit << numberB.Rbit << numberB.Sbit << std::endl;
		// std::cout << "Ostatni bajt: " << int(fracA[s.getFraction()]) << std::endl;
		if (numberA.sign)
		{ // dodatnia i dodatnia daje dodatnia, ujemna i ujemna ujemna. Default dodatnia!
			sign = 1;
		}
		for (int i = (s.getFraction()) - 1; i >= 0; i--)
		{
			fractResult[i] = addTwoBytes(fracA[i], fracB[i], carryFromAdd);
			std::cout << "DODAJE: " << int(fracA[i]) << " " << int(fracB[i]) << std::endl;
		}

		if (exponentA == exponentB)
		{
			incSevBytes(exponentResult);
			carryFromRr = 0;
			rrcSevBytes(fractResult, carryFromRr);
			if (carryFromAdd)
			{
				fractResult[0] = fractResult[0] | 0b10000000;
			}
		}
		else if (carryFromAdd)
		{
			carryFromRr = 0;
			rrcSevBytes(fractResult, carryFromRr);
			incSevBytes(exponentResult);
		}
		std::cout<<"WYNIK: " ;
		for (int i = 0; i < s.getFraction(); i++)
		{
			std::cout << int(fractResult[i]) << " ";
		}
		std::cout<<std::endl;
	}
	else
	{ // Ujemna i dodatnia
		if (!greaterA && !greaterB)
		{ // Takie same wykladniki, sprawdz mnozniki (DOROBIC COS DLA ROWNYCH LICZB) TUTAJ FLAGI GREATERA GREATER B SIE ZMIENIA
			for (int i = 0; i < s.getFraction(); i++)
			{
				if (fracA[i] > fracB[i])
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
			if (!greaterA && !greaterB)
			{
				for (auto i : exponentResult)
				{
					this->floatNumberBits.push_back(i);
				}
				for (auto i : fractResult)
				{
					this->floatNumberBits.push_back(0);
				}
				this->sign = sign;
			}
		}

		// Jeden wykladnik jest wiekszy
		if (greaterA) // Zamien mniejsza liczbe na u2
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
			for (int i = 0; i < fracA.size(); i++)
			{
				std::cout << "SRAWDZENIE: " << int(fracA[i]) << std::endl;
			}
			sign = numberB.sign;
		}
		carryFromAdd = 0;
		for (int i = (s.getFraction()) - 1; i >= 0; i--)
		{
			fractResult[i] = addTwoBytes(fracA[i], fracB[i], carryFromAdd);
			std::cout << "DODAJE: " << int(fracA[i]) << " " << int(fracB[i]) << std::endl;
		}

		if (scaled && !carryFromAdd)
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
	/*
	1. Sprawdz znaki i wybierz tryb
	2. Przeskaluj wykładnik
		a) Znajdz mniejszy wykladnik
		b) Zmien go na rowny wiekszemu - przesun mnoznik w lewo
	3.
	*/

	for (auto i : exponentResult)
	{
		this->floatNumberBits.push_back(i);
	} // Tutaj dac wykladnik
	for (auto i : fractResult)
	{
		this->floatNumberBits.push_back(i);
	}
	this->sign = sign;
}

void FloatNumber::round(std::vector<uint8_t>& bytes, Standard::roundType round_type)
{
	uint8_t carryFromAdd = 0;

	switch (round_type)
	{
	case Standard::roundType::TO_NEAREST_TIES_AWAY_FROM_ZERO: // Zaokraglenie symetrycznie do parzystej
		if (!bitG && !bitR)
			break;
		else if (bitG)

			for (int i = (s.getFraction() - 1); i >= 0; i--) // Sprawdzam czy po inkrementacji nie zaokraglimy do nieskonczonosci
			{
				bytes[i] = addTwoBytes(bytes[i], 1, carryFromAdd);
				if (carryFromAdd == 0)
					break;
			}
		if (carryFromAdd)
			setResultToInfinity();

		break;
	case Standard::roundType::TO_NEAREST_TIES_TO_EVEN: // zaokraglenie symetryczne do wiekszej wartosci bezwzglednej
		if (!bitG && !bitR)
			break;

		else
			for (int i = (s.getFraction() - 1); i >= 0; i--) // Sprawdzam czy po inkrementacji nie zaokraglimy do nieskonczonosci
			{
				bytes[i] = addTwoBytes(bytes[i], 1, carryFromAdd);
				if (carryFromAdd == 0)
					break;
			}
		if (carryFromAdd)
			setResultToInfinity();
		break;

	case Standard::roundType::TOWARD_MINUS_INF:
		if (!bitG && !bitR)
			break;
		else if (sign)
			for (int i = (s.getFraction() - 1); i >= 0; i--) // Sprawdzam czy po inkrementacji nie zaokraglimy do nieskonczonosci
			{
				bytes[i] = addTwoBytes(bytes[i], 1, carryFromAdd);
				if (carryFromAdd == 0)
					break;
			}
		if (carryFromAdd)
			setResultToInfinity();
		else
			break;
		break;

	case Standard::roundType::TOWARD_PLUS_INF:
		if (!bitG && !bitR)
		{
			break;
		}
		else if (sign)
		{

			break;
		}
		else
		{
			for (int i = (s.getFraction() - 1); i >= 0; i--) // Sprawdzam czy po inkrementacji nie zaokraglimy do nieskonczonosci
			{
				bytes[i] = addTwoBytes(bytes[i], 1, carryFromAdd);
				if (carryFromAdd == 0)
					break;
			}
			if (carryFromAdd)
				setResultToInfinity();
		}

		break;

	case Standard::roundType::TOWARD_ZERO:
		break;
	default:
		std::cout << "Cos jest nie tak" << std::endl;
		break;
	}
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

void FloatNumber::division(FloatNumber divident, FloatNumber divisor)	//divident=dzielna, divisor=dzielnik
{
	// M1/M2*2^(E1-E2)

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


	//wykladniki
	std::vector<uint8_t> exponentDivident;	//wykladnik dzielnej
	std::vector<uint8_t> exponentDivisor;	//wykladnik dzielnika
	std::vector<uint8_t> exponentQuotient;	//wykladnik ilorazu

	exponentDivident.reserve(s.getExponent());
	exponentDivisor.reserve(s.getExponent());
	exponentDivident.insert(exponentDivident.begin(), divident.floatNumberBits.begin(), divident.floatNumberBits.begin() + s.getExponent());
	exponentDivisor.insert(exponentDivisor.begin(), divisor.floatNumberBits.begin(), divisor.floatNumberBits.begin() + s.getExponent());
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

	fracDivident.reserve(s.getFraction());
	fracDivisor.reserve(s.getFraction());
	fracDivident.insert(fracDivident.begin(), divident.floatNumberBits.begin() + s.getExponent(), divident.floatNumberBits.end());
	fracDivisor.insert(fracDivisor.begin(), divisor.floatNumberBits.begin() + s.getExponent(), divisor.floatNumberBits.end());
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
	for (int i = (s.getExponent()) * 2; i >= 0; i--)
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

	while (this->floatNumberBits.size() != 0)
	{
		this->floatNumberBits.pop_back();
	}

	this->bitG = false;
	this->bitR = false;
	this->bitS = false;

}

void FloatNumber::prepGRS(std::vector<uint8_t> &bytes)
{
	/*
	while (bytes.size() != s.getFraction() + 1) // zostawiam ostatni bajt zeby przechowac w nim GRS
	{
		bytes.pop_back();
	}
	*/
	// Testowanie usuwania
	bytes.resize(s.getFraction() + 1);
	bytes.pop_back();
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