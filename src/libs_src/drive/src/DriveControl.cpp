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
	
void DriveControl::stop(){
	analogWrite(_pin, 0);
	_rpm = 0;
}

void DriveControl::start(){
	_rpm = _srt_drv_val;
	analogWrite(_pin, _rpm);
}

void DriveControl::accel(int accel){
	if(_rpm < MAX_RPM && _rpm > 0){
		_rpm += accel;
		analogWrite(_pin, _rpm);
	}
}

void DriveControl::smooth_start(){}
void DriveControl::smooth_start(int duration){}
void DriveControl::smooth_stop(){}
void DriveControl::smooth_stop(int duration){}
void DriveControl::smooth_accel(int target_rpm, int duration){}

void DriveControl::set_pin(int pin){
	_pin = pin;
}
void DriveControl::set_start_drive_value(int val){
	_srt_drv_val = val;
}

