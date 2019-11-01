#include "HallSensor.h"
#include "Arduino.h"

HSensor::HSensor(){}
HSensor::HSensor(int pin){
	_PIN = pin;
	pinMode(pin, INPUT);
}
HSensor::HSensor(int pin, boolean type){
	_PIN = pin;
	_TYPE = type;
	pinMode(pin, INPUT);
}


void HSensor::tick(){
	if(_TYPE){
		state_sensor = digitalRead(_PIN) == HIGH ? true: false; 
	}
	else{
		state_sensor = true;
	}

}

boolean HSensor::isTriggered(){
	if(state_sensor){
		state_sensor = false;
		return true;
	}
	else{
		return false;
	}
}
