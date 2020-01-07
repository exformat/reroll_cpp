#ifndef ExSensor_h
#define ExSensor_h
#include "Arduino.h"

#define TYPE1 1 //use outside interrupts
#define TYPE2 0 //use in interrupts

class Sensor{
	private:
		boolean state_sensor;
		int _PIN;
		boolean _TYPE;
		
	public:
		Sensor();
		Sensor(int pin);
		Sensor(int pin, boolean type);
		void tick();
		boolean isTriggered();
};
#endif
