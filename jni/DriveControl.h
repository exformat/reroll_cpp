#ifndef DriveControl_h
#define DriveControl_h
#include "Arduino.h"

class DriveControl{
	private:
		int _pin;
		int _rpm = 0;
		int _srt_drv_val = 0;
	
	public:
		DriveControl();
		DriveControl(int, int);
		void tick();
		void stop_drive();
		void start_drive();
		void accel_drive(int);
		void smooth_start_drive();
		void smooth_start_drive(int);
		void smooth_stop_drive();
		void smooth_stop_drive(int);
		void smooth_accel_drive(int, int);
		void set_pin(int);
};
#endif
