/*Multi LED library
* A library for non interupting lighting effects for single LED's
* Pim Ostendorf - 2017.11.24
*/

#ifndef multiLEDLibrary_h
#define multiLEDLibrary_h
#include "Arduino.h"

class sllib
{
public:
	//public variables and fucntions
	sllib(int pin);


private:
	int _pinArray[];

};

#endif