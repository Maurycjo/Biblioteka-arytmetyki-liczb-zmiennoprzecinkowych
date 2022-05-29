#include "ConsoleApp.h"
#include <iostream>



ConsoleApp::ConsoleApp()
{
	choseOption();
}


void::ConsoleApp::choseOption()
{
	int menuNumber = 1;
	std::cout << "Aplikacja wykorzystujaca biblioteke arytmetyki liczb zmiennoprzecinkowych" << std::endl << std::endl;
	std::cout << "(1) Zmien opcje podawania liczb, Obecnie: ";
	if (numberInput == 1)
		std::cout << "Dziesietnie" << std::endl;
	else
		std::cout << "Zmienny przecinek" << std::endl;
	std::cout << "(2) Zmien Standard, ";
	displayCurrentStandard();
	std::cout << "(3) Zmien schemat zaokraglania, Obecnie: ";
	std::cout << "Obciecie" << std::endl;
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
			std::cout << "SCHEMAT ZAOKROGALNIA\n";
			break;
		case 4:
			addNumbers();
			break;
		case 5:
			subbNumbers();
			break;
		case 6:
			mulNumbers();
			break;
		case 7:
			divNumbers();
			break;
		case 8:
			system("cls");
		}

		if(menuNumber!=0)
		choseOption();
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

void::ConsoleApp::addNumbers()
{
	std::cout << "Schemat zaokraglania: Obciecie" << std::endl;
	enterNumbers();
	result.addition(numberA, numberB);	//to bedzie dodawanie nie mnozenie
	std::cout << "Suma: ";
	result.displayNumberBinary();
}

void::ConsoleApp::subbNumbers()
{
	std::cout << "Schemat zaokraglania: Obciecie" << std::endl;
	enterNumbers();
	result.multiply(numberA, numberB);	//to bedzie odejmowanie nie mnozenie
	std::cout << "Roznica: ";
	result.displayNumberBinary();
}

void::ConsoleApp::mulNumbers()
{
	std::cout << "Schemat zaokraglania: Obciecie" << std::endl;
	enterNumbers();
	result.multiply(numberA, numberB);
	std::cout << "Iloczyn: ";
	result.displayNumberBinary();
}

void::ConsoleApp::divNumbers()
{
	std::cout << "Schemat zaokraglania: Obciecie" << std::endl;
	enterNumbers();
	result.division(numberA, numberB);
	std::cout << "Iloraz: ";
	result.displayNumberBinary();
}

void::ConsoleApp::enterNumbers()
{
	long double A, B;

	displayCurrentStandard();
	this->numberA.setStandard(this->s);
	this->numberB.setStandard(this->s);
	std::cout << "Podaj liczby ";
	if (numberInput == 1)
	{
		std::cout << "dziesietnie" << std::endl;
		std::cin >> A;
		std::cin >> B;
		this->numberA.dec2float(A);
		this->numberB.dec2float(B);
	}
	else
	{
		std::cout << "w zmiennym przecinku" << std::endl;
		/*
		
		metoda pobierajaca string bitow
		*/ 

	}

	std::cout << "Przekonwertowano" << std::endl;
	std::cout << "Liczba 1: ";
	numberA.displayNumberBinary();
	std::cout << "Liczba 2: ";
	numberB.displayNumberBinary();


}