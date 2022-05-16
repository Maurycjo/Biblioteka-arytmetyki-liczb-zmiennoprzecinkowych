#pragma once
#include "Standard.h"
#include <iterator>
#include <iostream>
#include <vector>
class FloatNumber
{
private:
	Standard s;
	bool sign;
	bool Rbit;
	bool Sbit;
	bool Gbit;
	std::vector<uint8_t> floatNumberBits;										//vector liczby w standardzie
	void setResultToInfinity(std::vector<uint8_t>& number);								//ustawienie liczby w standardzie na nieskonczonosc
	uint8_t addTwoBytes(uint8_t byteA, uint8_t byteB, uint8_t& carry);			// dodanie dwoch bajtow z wykrywaniemm przeniesienia
	uint8_t subbTwoBytes(uint8_t minuend, uint8_t subtrahend, uint8_t& carry);	//odejmowanie dwoch bajtow
	void rlc(uint8_t& byte, uint8_t& rotCarry);									//rotacja w lewo z przeniesieniem 
	void rrc(uint8_t& byte, uint8_t& rotCarry);									//rotacja w prawo z przeniesieniem 
	void rlcSevBytes(std::vector<uint8_t>& number, uint8_t& carry);				//rotacja w lewo bitow w vektorze
	void rrcSevBytes(std::vector<uint8_t>& number, uint8_t& carry);				//rotacja w prawo bitow w vektorze
	void incSevBytes(std::vector<uint8_t>& number);								//inkrementacja bez przeniesienia vektora bajtow
	void decSevBytes(std::vector<uint8_t>& number);								//dekrementacja bez przeniesienia vektora bajtow
	std::vector<uint8_t> generateBias();										//generowanie obciazenia wykladnika
	void round(std::vector<uint8_t>& bytes, Standard::roundType round_type);
	void getGRS(std::vector<uint8_t> bytes);
	void prepGRS(std::vector<uint8_t>& bytes);									//Przygotowuje bity GRS do obliczen
public:

	void setStandard(Standard s);												//ustawienie standardu
	void dec2float(float inputNumber);											//konwersja na liczbe FloatNumber
	void displayNumberBinary();													//wyswietlenie liczby w formacie binarnym	
	void multiply(FloatNumber number1, FloatNumber number2, Standard::roundType round_type);				//mnozenie liczb w standardzie
	void addition(FloatNumber number1, FloatNumber number2, Standard::roundType round_type);				//dodawanie liczb w standardzie
	
};

