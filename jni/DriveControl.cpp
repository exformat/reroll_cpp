#include "DriveControl.h"

DriveControl::DriveControl(){}
DriveControl::DriveControl(int pin){
	_pin = ;
}

void DriveControl::tick(){}
	
void DriveControl::stop_drive(){}
void DriveControl::start_drive(){}
void DriveControl::accel_drive(int accel){}
void DriveControl::smooth_start_drive(){}
void DriveControl::smooth_start_drive(int duration){}
void DriveControl::smooth_stop_drive(){}
void DriveControl::smooth_stop_drive(int duration){}
void DriveControl::smooth_accel_drive(int target_rpm, int duration){}
void DriveControl::set_pin(int pin){
	_pin = pin;
}

