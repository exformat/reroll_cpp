#include "DriveControl.h"
#include "Arduino.h"

DriveControl::DriveControl(){}
DriveControl::DriveControl(int pin, int start_drive_value){
	_pin = pin;
	_srt_drv_val = start_drive_value;
	pinMode(_pin, OUTPUT);
}

void DriveControl::tick(){}
	
void DriveControl::stop_drive(){
	analogWrite(_pin, 0);
	_rpm = 0;
}

void DriveControl::start_drive(){
	analogWrite(_pin, 40);
	_rpm = 40;
}

void DriveControl::accel_drive(int accel){
	_rpm += accel;
	analogWrite(_pin, _rpm);
}

void DriveControl::smooth_start_drive(){}
void DriveControl::smooth_start_drive(int duration){}
void DriveControl::smooth_stop_drive(){}
void DriveControl::smooth_stop_drive(int duration){}
void DriveControl::smooth_accel_drive(int target_rpm, int duration){}

void DriveControl::set_pin(int pin){
	_pin = pin;
}

