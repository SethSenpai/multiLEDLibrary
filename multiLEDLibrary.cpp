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
	_tempStore[0] = 255;
	_tempStore[1] = 127;
	_tempStore[2] = 0;
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

void mllib::stepPongCounter() {
	bool i;
	if (counter == _length - 1) {
		i = false;
	}
	if (counter == 0) {
		i = true;
	}
	if (i) {
		counter++;
	}
	else {
		counter--;
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

void mllib::snakeFadeMulti(int speed, int step, bool on) {
	if ((milOld + speed) < millis()) {
		milOld = millis();
		if (on == true) {
			for (int i = 0; i < _length; i++) {
				int prev;
				int next;
				if (counter - 1 < 0) {
					prev = _length;
				}
				else {
					prev = counter - 1;
				}

				if (counter + 1 > _length) {
					next = 0;
				}
				else {
					next = counter + 1;
				}

				if (i == prev) {
					_tempStore[0] -= step;
					analogWrite(_pinArray[prev], _tempStore[0]);
				}
				else if (i == next) {
					_tempStore[2] += step;
					analogWrite(_pinArray[next], _tempStore[2]);
				}
				else if (i == counter) {
					_tempStore[1] += step;
					analogWrite(_pinArray[i], _tempStore[1]);
					//tempstore needs to be pulled forward instead of pushed back
					if (_tempStore[1] > 255) {
						stepCounter();
						_tempStore[0] = 255;
						_tempStore[1] = _tempStore[2];
						_tempStore[2] = 0;
					}
				}
				else {
					digitalWrite(_pinArray[i], LOW);
				}
			}
		}
	}
}

//needs to be checked
void mllib::pingPongMulti(int speed, bool on) {
	if ((milOld + speed) < millis()) {
		milOld = millis();
		if (on) {
			for (int i = 0; i < _length; i++) {
				if (counter == i) {
					digitalWrite(_pinArray[i], HIGH);
				}
				else {
					digitalWrite(_pinArray[i], LOW);
				}
			}
			stepPongCounter();
		}
		else {
			for (int i = 0; i < _length; i++) {
				if (counter == i) {
					digitalWrite(_pinArray[i], LOW);
				}
				else {
					digitalWrite(_pinArray[i], HIGH);
				}
			}
			stepPongCounter();
		}
	}
}

//needs to be checked
void mllib::blinkRandomMulti(int speed, bool on) {
	if ((milOld + speed) < millis()) {
		milOld = millis();
	}
}