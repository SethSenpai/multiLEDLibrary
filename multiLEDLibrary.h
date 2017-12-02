/*Multi LED library
* A library for non interupting lighting effects for single LED's
* Pim Ostendorf - 2017.11.24
*/

#ifndef multiLEDLibrary_h
#define multiLEDLibrary_h
#include "Arduino.h"

class mllib
{
public:
	//public variables and fucntions
	mllib(int pin[] , int length);
	void snakeMulti(int speed, bool on);
	void snakeFadeMulti(int speed, int step, bool on);

private:
	//private functions
	void stepCounter();

	//global variables
	unsigned long milOld;
	int counter;
	int* _pinArray = 0;
	int _length;
	int _tempStore[3];
};

#endif