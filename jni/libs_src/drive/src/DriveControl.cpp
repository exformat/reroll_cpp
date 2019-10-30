#include "DriveControl.h"
#include "Arduino.h"

DriveControl::DriveControl(){}
DriveControl::DriveControl(int pin, int start_drive_value){
	_pin = pin;
	_srt_drv_val = start_drive_value;
	
	pinMode(_pin, OUTPUT);
}

void DriveControl::tick(){
	tick_time = millis();
}
	
void DriveControl::stop_drive(){
	if(rpm > 0){
		analogWrite(_pin, 0);
		rpm = 0;
	}
}

void DriveControl::start_drive(){
	if(rpm == 0){
		rpm = _srt_drv_val;
		analogWrite(_pin, rpm);
	}
}

void DriveControl::accel_drive(int accel){
	if(rpm < MAX_RPM && rpm > 0){
		rpm += accel;
		analogWrite(_pin, rpm);
	}
}

void DriveControl::smooth_start_drive(){}
void DriveControl::smooth_start_drive(int duration){}
void DriveControl::smooth_stop_drive(){}
void DriveControl::smooth_stop_drive(int duration){}
void DriveControl::smooth_accel_drive(int target_rpm, int duration){}

void DriveControl::set_pin(int pin){
	_pin = pin;
}
void DriveControl::set_start_drive_value(int val){
	_srt_drv_val = val;
}

