#include "Relay.h"
#include "Arduino.h"

Relay::Relay(int pin){
	_pin = pin;
	_on = false;
	_switch = false;
	pinMode(_pin, OUTPUT);
}

void Relay::on(){
	if(!_on){
		digitalWrite(_pin, HIGH);
		_on = true;
	}
}

void Relay::off(){
	if(_on){
		digitalWrite(_pin, LOW);
		_on = false;
	}
}

void Relay::switch_relay(){
	if(_switch){
		digitalWrite(_pin, LOW);
		_switch = false;
	}
	else{
		digitalWrite(_pin, HIGH);
		_switch = true;
	}
}

boolean Relay::is_switch(){
	return _switch;
}
