#include "HallSensor.h"
#include "Arduino.h"

HSensor::HSensor(){}
HSensor::HSensor(int pin){
	_PIN = pin;
	pinMode(pin, INPUT);
}
void HSensor::tick(){
	state_sensor = digitalRead(_PIN) == HIGH ? true: false; 
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
