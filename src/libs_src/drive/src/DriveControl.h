#ifndef DriveControl_h
#define DriveControl_h
#include "Arduino.h"

#define MAX_RPM 255

class DriveControl{
	private:
		int _pin;
		int _rpm;
		int _srt_drv_val;
		long tick_time;
	
	public:
		DriveControl();
		DriveControl(int pin, int start_drive_value);
		void tick();
		void stop();
		void start();
		void accel(int target_rpm);
		void smooth_start();
		void smooth_start(int duration);
		void smooth_stop();
		void smooth_stop(int duration);
		void smooth_accel(int target_rpm, int duration);
		void set_pin(int pin);
		void set_start_drive_value(int val);
};
#endif
