#pragma once
#include "Standard.h"
#include "FloatNumber.h"

class ConsoleApp
{
private:
	int numberInput = 1;	//1 dziesitenie, 2 binarnie
	int round = 0;			//schemat zaokraglanie

	
	Standard s;
	void choseOption();
	void displayCurrentStandard();
	void setStandard();
	void setNumberInput();
	void addNumbers(FloatNumber numberA, FloatNumber numberB, FloatNumber result);
	void subbNumbers(FloatNumber numberA, FloatNumber numberB, FloatNumber result);
	void divNumbers(FloatNumber numberA, FloatNumber numberB, FloatNumber result);
	void mulNumbers(FloatNumber numberA, FloatNumber numberB, FloatNumber result);
	void enterNumbers(FloatNumber &numberA, FloatNumber &numberB);
public:

	ConsoleApp();

};