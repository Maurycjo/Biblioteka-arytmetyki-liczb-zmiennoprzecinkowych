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
	void addNumbers(roundType type, FloatNumber numberA, FloatNumber numberB, FloatNumber result);
	void subbNumbers(roundType type, FloatNumber numberA, FloatNumber numberB, FloatNumber result);
	void divNumbers(roundType type, FloatNumber numberA, FloatNumber numberB, FloatNumber result);
	void mulNumbers(roundType type, FloatNumber numberA, FloatNumber numberB, FloatNumber result);
	void enterNumbers(roundType type, FloatNumber &numberA, FloatNumber &numberB);
	void setRoundType(roundType& type, FloatNumber& numberA, FloatNumber& numberB, FloatNumber& result);
	void displayCurrentRoundType(roundType type);
public:

	ConsoleApp();

};