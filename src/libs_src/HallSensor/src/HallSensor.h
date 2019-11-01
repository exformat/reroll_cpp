#ifndef HallSensor_h
#define HallSensor_h
#include "Arduino.h"

class HSensor{
	private:
		boolean state_sensor;
		int _PIN;
		
	public:
		HSensor();
		HSensor(int pin);
		void tick();
		boolean isTriggered();
};


#endif
