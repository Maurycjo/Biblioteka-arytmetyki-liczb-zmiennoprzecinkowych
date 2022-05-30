#include "ConsoleApp.h"
#include <iostream>
#include "Standard.h"



ConsoleApp::ConsoleApp()
{
	choseOption();
}

void::ConsoleApp::choseOption()
{

		int menuNumber = 1;
		roundType type = TOWARD_ZERO;

	while (menuNumber != 0)
	{
		FloatNumber numberA, numberB, result;
		numberA.setRoundType(type);
		numberB.setRoundType(type);
		result.setRoundType(type);


		std::cout << "Aplikacja wykorzystujaca biblioteke arytmetyki liczb zmiennoprzecinkowych" << std::endl << std::endl;
		std::cout << "(1) Zmien opcje podawania liczb, Obecnie: ";
		if (numberInput == 1)
			std::cout << "Dziesietnie" << std::endl;
		else
			std::cout << "Zmienny przecinek" << std::endl;
		std::cout << "(2) Zmien Standard, ";
		displayCurrentStandard();
		std::cout << "(3) Zmien schemat zaokraglania, Obecnie: ";
		displayCurrentRoundType(type);
		std::cout << "(4) Dodawanie" << std::endl;
		std::cout << "(5) Odejmowanie" << std::endl;
		std::cout << "(6) Mnozenie" << std::endl;
		std::cout << "(7) Dzielenie" << std::endl;
		std::cout << "(8) Wyczysc ekran" << std::endl;
		std::cout << "(0) Wyjscie" << std::endl;

		do
		{
			std::cin >> menuNumber;
			if (menuNumber < 0 || menuNumber>8)
			{
				std::cout << "Bledna operacja!" << std::endl;
				std::cout << "Wybierz: ";
			}

		} while (menuNumber < 0 || menuNumber>8);

		switch (menuNumber)
		{
		case 0:
			break;
		case 1:
			setNumberInput();
			break;
		case 2:
			setStandard();
			break;
		case 3:
			setRoundType(type, numberA, numberB, result);
			break;
		case 4:
			addNumbers(type, numberA, numberB, result);
			break;
		case 5:
			subbNumbers(type, numberA, numberB, result);
			break;
		case 6:
			mulNumbers(type, numberA, numberB, result);
			break;
		case 7:
			divNumbers(type, numberA, numberB, result);
			break;
		case 8:
			system("cls");
			break;
		}

	}
}

void::ConsoleApp::displayCurrentStandard()
{
	std::cout << "Obecnie: Bajty 1/" << s.getExponent() << "/" << s.getFraction() << std::endl;
}

void::ConsoleApp::setStandard()
{
	
	int exp, frac;

	std::cout << "Liczba bajtow wykladnika: ";
	std::cin >> exp;
	std::cout << "Liczba bajtow mnoznika: ";
	std::cin >> frac;
	s.setStandart(exp, frac);
	
}

void::ConsoleApp::setNumberInput()
{
	int menu;

	std::cout << "Obecnie: ";
	if (numberInput == 1)
		std::cout << "Dziesietnie" << std::endl;
	else
		std::cout << "Zmienny przecinek" << std::endl;
	std::cout << "(1) Dziesietnie" << std::endl;
	std::cout << "(2) Zmienny przecinek (podaj ciag bitow)" << std::endl;
	std::cout << "(0) Cofnij" << std::endl;

	std::cout << "Wybierz: ";
	do
	{
		std::cin >> menu;

		if (menu != 1 && menu != 2 && menu != 0)
		{
			std::cout << "Bledna operacja!" << std::endl;
			std::cout << "Wybierz: ";
		}

	} while (menu != 1 && menu != 2 && menu != 0);
	
	if (menu == 1)
	{
		numberInput = 1;
	}
	else if (menu == 2)
	{
		numberInput = 2;
	}

}

void::ConsoleApp::addNumbers(roundType type, FloatNumber numberA, FloatNumber numberB, FloatNumber result)
{
	std::cout << "Schemat zaokraglania: ";
	displayCurrentRoundType(type);
	enterNumbers(type, numberA, numberB);
	result.addition(numberA, numberB);	//to bedzie dodawanie nie mnozenie
	std::cout << "Suma:     ";
	result.displayNumberBinary();
}

void::ConsoleApp::subbNumbers(roundType type, FloatNumber numberA, FloatNumber numberB, FloatNumber result)
{
	std::cout << "Schemat zaokraglania: ";
	displayCurrentRoundType(type);
	enterNumbers(type, numberA, numberB);
	numberB.signNegation();
	result.addition(numberA, numberB);	//to bedzie odejmowanie nie mnozenie
	std::cout << "Roznica:  ";
	result.displayNumberBinary();
}

void::ConsoleApp::mulNumbers(roundType type, FloatNumber numberA, FloatNumber numberB, FloatNumber result)
{
	std::cout << "Schemat zaokraglania: ";
	displayCurrentRoundType(type);
	enterNumbers(type, numberA, numberB);
	result.multiply(numberA, numberB);
	std::cout << "Iloczyn:  ";
	result.displayNumberBinary();
}

void::ConsoleApp::divNumbers(roundType type, FloatNumber numberA, FloatNumber numberB, FloatNumber result)
{
	std::cout << "Schemat zaokraglania: ";
	displayCurrentRoundType(type);
	enterNumbers(type, numberA, numberB);
	result.division(numberA, numberB);
	std::cout << "Iloraz:   ";
	result.displayNumberBinary();
}

void::ConsoleApp::enterNumbers(roundType type, FloatNumber& numberA, FloatNumber& numberB)
{
	long double A, B;
	std::string strA, strB;

	displayCurrentStandard();
	numberA.setStandard(this->s);
	numberB.setStandard(this->s);
	std::cout << "Podaj liczby ";
	if (numberInput == 1)
	{
		std::cout << "dziesietnie" << std::endl;
		std::cin >> A;
		std::cin >> B;
		numberA.dec2float(A);
		numberB.dec2float(B);
	}
	else
	{
		std::cout << "w zmiennym przecinku" << std::endl;
		std::cin >> A;
		std::cin >> B;
		numberA.string2float(strA);
		numberB.string2float(strB);
	
			
	}

	std::cout << "Przekonwertowano" << std::endl;
	std::cout << "Liczba 1: ";
	numberA.displayNumberBinary();
	std::cout << "Liczba 2: ";
	numberB.displayNumberBinary();


}

void::ConsoleApp::setRoundType(roundType &type, FloatNumber& numberA, FloatNumber& numberB, FloatNumber& result)
{
	int tempType;


	std::cout << "Schemat zaokraglania" << std::endl;
	std::cout << "(1) Zaokraglenie przez obciecie" << std::endl;
	std::cout << "(2) Zaokraglenie do + nieskonczonosci" << std::endl;
	std::cout << "(3) Zaokraglenie do - nieskonczonosci" << std::endl;
	std::cout << "(4) Zaokraglenie symetryczne do wiekszej wartosci bezwzglednej" << std::endl;
	std::cout << "(5) Zaokraglenie symetryczne do przystej" << std::endl;
	std::cout << "Wybierz: ";

	do
	{
		std::cin >> tempType;

		if (tempType < 1 || tempType>5)
		{
			std::cout << "Bledna operacja!" << std::endl;
			std::cout << "Wybierz: ";

		}

	} while (tempType < 1 || tempType>5);

	type = static_cast<roundType>(tempType);
	
}

void::ConsoleApp::displayCurrentRoundType(roundType type)
{


	switch (type)
	{
	case TOWARD_ZERO:
		std::cout << "Zaokraglenie przez obciecie" << std::endl;
		break;
	case TOWARD_PLUS_INF:
		std::cout << "Zaokraglenie do + nieskonczonosci" << std::endl;
		break;
	case TOWARD_MINUS_INF:
		std::cout << "Zaokraglenie do - nieskonczonosci" << std::endl;
		break;
	case TO_NEAREST_TIES_TO_EVEN:
		std::cout << "Zaokraglenie symetryczne do wiekszej wartosci bezwzglednej" << std::endl;
		break;
	case TO_NEAREST_TIES_AWAY_FROM_ZERO:
		std::cout << "Zaokraglenie symetryczne do przystej" << std::endl;
		break;
	}
}