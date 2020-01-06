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
		float delta_time;
		
		boolean smooth = false;
		float target_smoot_timer = 0;
		float smooth_timer = 0;
		float smooth_step = 0;
		int smoorh_pwm_step = 0;
		
		void smoothFunction();
	
	public:
		DriveControl();
		DriveControl(int pin, int start_pwm);
		void tick();
		void stop();
		void start();
		void accel(int pwm);
		void smooth_start();
		void smooth_start(int duration);
		void smoothStop();
		void smoothStop(int duration);
		void smooth_accel(int pwm, int duration);
		void set_pin(int pin);
		void set_start_pwm(int val);
};
#endif
