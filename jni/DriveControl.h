#ifndef DriveControl_h
#define DriveControl_h

class DriveControl{
	private:
		int _pin;
	
	
	public:
		DriveControl();
		DriveControl(int);
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
