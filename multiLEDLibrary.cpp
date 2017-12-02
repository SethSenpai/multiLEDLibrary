#include "multiLEDLibrary.h"
#include "Arduino.h"

mllib::mllib(int pin[], int length) {
	//make sure to use pwm ports here when using fade related functions
	_length = length;
	for (int i = 0; i < length; i++) {
		pinMode(pin[i], OUTPUT);
		digitalWrite(pin[i], LOW);
	}
	//assign new array to pointer
	if (_pinArray != 0) {
		delete[] _pinArray;
	}
	_pinArray = new int[length];

	for (int i = 0; i < length; i++) {
		_pinArray[i] = pin[i];
	}

	counter = 0;
}


//internal function to keep track of the led we're currently manipulating
void mllib::stepCounter() {
	if (counter == _length - 1) {
		counter = 0;
	}
	else {
		counter++;
	}
}

//simple blink snake pattern
void mllib::snakeMulti(int speed, bool on) {
	if ((milOld + speed) < millis()) {
		milOld = millis();
		//check if we're snaking an led off or an led on
		if (on == true) {
			for (int i = 0; i < _length; i++) {
				if (i != counter) {
					digitalWrite(_pinArray[i], LOW);
				}
				else {
					digitalWrite(_pinArray[i], HIGH);
				}
			}
			stepCounter();
		}
		else
		{
			for (int i = 0; i < _length; i++) {
				if (i != counter) {
					digitalWrite(_pinArray[i], HIGH);
				}
				else {
					digitalWrite(_pinArray[i], LOW);
				}
			}
			stepCounter();
		}
	}
}