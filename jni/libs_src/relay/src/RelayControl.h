#ifndef RelayControl_h
#define RelayControl_h

#include "Arduino.h"

class RelayControl{
	private:
		int _pin;
		boolean _switch;
		boolean _on;
	
	public:
		RelayControl(int pin);
		void switch_relay();
		void on();
		void off();
		boolean is_switch();
};
#endif



