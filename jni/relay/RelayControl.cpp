#include "RelayControl.h"
#include "Arduino.h"

RelayControl::RelayControl(int pin){
	_pin = pin;
}
void RelayControl::switch_relay(){
	if(_switch){
		digitalWrite(_pin, HIGH);
		_switch = false;
	}
	else{
		digitalWrite(_pin, LOW);
		_switch = true;
	}
}
boolean RelayControl::is_switch(){
	return _switch;
}
