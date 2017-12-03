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

	//lighting patterns
	void snakeMulti(int speed, bool on);
	void snakeFadeMulti(int speed, int step, bool on);
	void pingPongMulti(int speed, bool on);
	void pingPongFadeMulti(int speed, int step, bool on);
	void blinkRandomMulti(int speed, bool on);
	void breathRandomMulti(int speed, bool on);
	void snakePattern(int speed, bool on, int pattern[], int length);

private:
	//private functions
	void stepCounter();
	void stepPongCounter();

	//global variables
	unsigned long milOld;
	int counter;
	int* _pinArray = 0;
	int _length;
	int _tempStore[3];
};

#endif