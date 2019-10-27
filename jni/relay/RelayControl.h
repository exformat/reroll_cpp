#ifndef RelayControl_h
#define RelayControl_h

#include "Arduino.h"


class Relay{
	private:
		int _pin;
		boolean _switch;
	
	public:
		Relay(int pin);
		void switch_relay();
		boolean is_switch();
};
#endif



