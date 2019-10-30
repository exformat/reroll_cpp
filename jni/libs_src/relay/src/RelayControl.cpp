#include "RelayControl.h"
#include "Arduino.h"

RelayControl::RelayControl(int pin){
	_pin = pin;
	_on = false;
	_switch = false;
	pinMode(_pin, OUTPUT);
}

void RelayControl::on(){
	if(!_on){
		digitalWrite(_pin, HIGH);
		_on = true;
	}
}

void RelayControl::off(){
	if(_on){
		digitalWrite(_pin, LOW);
		_on = false;
	}
}

void RelayControl::switch_relay(){
	if(_switch){
		digitalWrite(_pin, LOW);
		_switch = false;
	}
	else{
		digitalWrite(_pin, HIGH);
		_switch = true;
	}
}

boolean RelayControl::is_switch(){
	return _switch;
}
