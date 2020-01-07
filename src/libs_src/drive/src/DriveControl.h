#ifndef DriveControl_h
#define DriveControl_h
#include "Arduino.h"

#define MAX_PWM 254

class DriveControl{
	private:
		int _pin;
		int _pwm;
		int target_pwm = 0;
		int _start_pwm;
		long tick_time;
		long old_tick_time;
        	long delta_time;
		
		bool smooth = false;
		long target_smooth_timer = 0;
        	long smooth_timer = 0;
        	long smooth_step = 0;
		int smooth_pwm_step = 0;
		
		void smoothFunction();
	
	public:
		DriveControl();
		DriveControl(int pin, int start_pwm);
		void tick();
		void stop();
		void start();
		void accel(int pwm);
		void smoothStart();
		void smoothStart(int duration);
		void smoothStop();
		void smoothStop(int duration);
		void smoothAccel(int pwm, int duration);
		void set_pin(int pin);
		void set_start_pwm(int val);
};
#endif
