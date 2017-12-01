#include "multiLEDLibrary.h"
#include "Arduino.h"

sllib::sllib(int pin) {
	//make sure to use pwm ports here
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
	Serial.begin(9600);
	_pinArray = pin;
}