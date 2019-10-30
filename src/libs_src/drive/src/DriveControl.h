#ifndef DriveControl_h
#define DriveControl_h
#include "Arduino.h"

#define MAX_RPM 255

class DriveControl{
	private:
		int _pin;
		int rpm = 0;
		int _srt_drv_val = 0;
		long tick_time = 0;
	
	public:
		DriveControl();
		DriveControl(int pin, int start_drive_value);
		void tick();
		void stop_drive();
		void start_drive();
		void accel_drive(int target_rpm);
		void smooth_start_drive();
		void smooth_start_drive(int duration);
		void smooth_stop_drive();
		void smooth_stop_drive(int duration);
		void smooth_accel_drive(int target_rpm, int duration);
		void set_pin(int pin);
		void set_start_drive_value(int val);
};
#endif
