#include "ExSensor.h"
#include "Arduino.h"

Sensor::Sensor(){}
Sensor::Sensor(int pin){
	_PIN = pin;
	pinMode(pin, INPUT);
}
Sensor::Sensor(int pin, boolean type){
	_PIN = pin;
	_TYPE = type;
	pinMode(pin, INPUT);
}


void Sensor::tick(){
	//if(_TYPE){
		state_sensor = digitalRead(_PIN) == HIGH ? true: false; 
	//}
	//else{
		//state_sensor = true;
	//}

}

boolean Sensor::isTriggered(){
	if(state_sensor){
		state_sensor = false;
		return true;
	}
	else{
		return false;
	}
}
