#ifndef RelayControl_h
#define RelayControl_h

#include "Arduino.h"

class RelayControl{
	private:
		int _pin;
		bool _switch;
		bool _on;
	
	public:
		RelayControl(int pin);
		void switch_relay();
		void on();
		void off();
		bool is_switch();
};
#endif



