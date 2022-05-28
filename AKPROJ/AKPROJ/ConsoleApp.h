#pragma once
#include "Standard.h"
#include "FloatNumber.h"

class ConsoleApp
{
private:
	int numberInput = 1;	//1 dziesitenie, 2 binarnie
	int round = 0;			//schemat zaokraglanie

	FloatNumber numberA, numberB, result;
	Standard s;
	void choseOption();
	void displayCurrentStandard();
	void setStandard();
	void setNumberInput();
	void addNumbers();
	void subbNumbers();
	void divNumbers();
	void mulNumbers();
	void enterNumbers();
public:

	ConsoleApp();

};