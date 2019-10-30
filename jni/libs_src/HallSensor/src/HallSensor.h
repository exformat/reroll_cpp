#ifndef
#include "Arduino.h"

class HSensor{
	private:
		boolean state_sensor = false;
		int _PIN = 0;
		
	public:
		void HSensor();
		void HSrnsor(int pin);
		void tick();
		boolean isTriggered();
}


#endif
