#define SMT_SRT = 2
#define SMT_STP = 2

class DriveControl{
	private:
		int pin;
	
	
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
