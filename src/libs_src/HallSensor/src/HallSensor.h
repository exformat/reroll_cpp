#ifndef HallSensor_h
#define HallSensor_h
#include "Arduino.h"

#define TYPE1 1 //use outside interrupts
#define TYPE2 0 //use in interrupts

class HSensor{
	private:
		boolean state_sensor;
		int _PIN;
		boolean _TYPE;
		
	public:
		HSensor();
		HSensor(int pin);
		HSensor(int pin, boolean type);
		void tick();
		boolean isTriggered();
};


#endif
