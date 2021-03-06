#pragma once
#include "Standard.h"
#include <vector>
#include <string>


class FloatNumber
{
private:
	Standard s;																	//standard, przechowuje ile bajtow ma wykladnik i mnoznik
	roundType type = TOWARD_ZERO;												//schemat zaokraglania, domyslny przez obciecie
	bool sign;																	//znak liczby
	bool bitG = 0, bitR = 0, bitS = 0;											//bity GRS
	std::vector<uint8_t> floatNumberBits;										//vector liczby w standardzie
	void setResultToInfinity();													//ustawienie liczby w standardzie na nieskonczonosc
	void setResultToZero();														//ustawienie liczby w standardzie na 0
	void setResultToNaN();														//ustawienie liczby na NaN (Not a Number) kod NaN 11..11|00..01
	bool ifInfinity(FloatNumber number);										//sprawdzenie czy liczba jest nieskonczonoscia
	bool ifZero(FloatNumber number);											//sprawdzenie czy liczba jest zerem
	bool ifNaN(FloatNumber number);												//sprawdzenie czy liczba jest NaN
	bool ifOne(FloatNumber number);												//sprawdzenie czy liczba jest rowna 1
	uint8_t addTwoBytes(uint8_t byteA, uint8_t byteB, uint8_t& carry);			// dodanie dwoch bajtow z wykrywaniemm przeniesienia
	uint8_t subbTwoBytes(uint8_t minuend, uint8_t subtrahend, uint8_t& carry);	//odejmowanie dwoch bajtow
	void rlc(uint8_t& byte, uint8_t& rotCarry);									//rotacja w lewo z przeniesieniem 
	void rrc(uint8_t& byte, uint8_t& rotCarry);									//rotacja w prawo z przeniesieniem 
	void rlcSevBytes(std::vector<uint8_t>& number, uint8_t& carry);				//rotacja w lewo bitow w vektorze
	void rrcSevBytes(std::vector<uint8_t>& number, uint8_t& carry);				//rotacja w prawo bitow w vektorze
	void incSevBytes(std::vector<uint8_t>& number);								//inkrementacja bez przeniesienia vektora bajtow
	void decSevBytes(std::vector<uint8_t>& number);								//dekrementacja bez przeniesienia vektora bajtow
	std::vector<uint8_t> generateBias();										//generowanie obciazenia wykladnika
	void getGRS(std::vector<uint8_t> bytes);									//metoda ustawiajaca bity grs
	void prepGRS(std::vector<uint8_t>& bytes);									//Przygotowuje bity GRS do obliczen
public:
	void round(roundType type);													//zaokraglenia
	void setStandard(Standard s);												//ustawienie standardu
	void dec2float(double inputNumber);											//konwersja na liczbe FloatNumber
	void string2float(std::string inputNumber);										//konwersja ciagu bitow na liczbe w standardzie
	void displayNumberBinary();													//wyswietlenie liczby w formacie binarnym	
	void multiply(FloatNumber number1, FloatNumber number2);					//mnozenie liczb w standardzie
	void division(FloatNumber number1, FloatNumber number2);					//dzielenie liczb w standardzie
	~FloatNumber();																//zwalnianie FloatNumberBits
	void addition(FloatNumber number1, FloatNumber number2);					//dodawanie liczb w standardzie
	void signNegation();														//negacja znaku liczby
	void setRoundType(roundType type);											//ustawienie trybu zaokraglenia
	roundType getRoundType();													//zwrocenie tryby zaokraglenia;
	std::vector<uint8_t> get_bits_for_testing();								//do testow
	bool get_sign();
	void setRandomNumber();
	
	
};

