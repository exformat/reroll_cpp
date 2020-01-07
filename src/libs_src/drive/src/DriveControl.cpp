#include "DriveControl.h"
#include "Arduino.h"

DriveControl::DriveControl(){}
DriveControl::DriveControl(int pin, int start_pwm){
	_pin = pin;
	_start_pwm = start_pwm;
	old_tick_time = 0;
	tick_time = 0;
	delta_time = 0;
	pinMode(_pin, OUTPUT);
}

void DriveControl::tick(){
	old_tick_time = tick_time;
	tick_time = millis();
	delta_time = tick_time - old_tick_time;
	
	if(smooth){
		smoothFunction();
	}
}
	
void DriveControl::stop(){
	analogWrite(_pin, 0);
	_pwm = 0;
}

void DriveControl::start(){
	_pwm = _start_pwm;
	analogWrite(_pin, _pwm);
}

void DriveControl::accel(int pwm){
	if(_pwm < MAX_PWM && _pwm > 0){
		_pwm += pwm;
		analogWrite(_pin, _pwm);
	}
}

void DriveControl::smoothFunction(){
	smooth_timer -= delta_time;
	target_smooth_timer += delta_time;
	if(target_pwm > _pwm){
		smooth_pwm_step = 1;
	}
	else{
		smooth_pwm_step = -1;
	}
	if(smooth_timer > 0){
		if(target_smooth_timer >= smooth_step){
			accel(smooth_pwm_step);
			target_smooth_timer = 0;
		}
	}
}


void DriveControl::smoothStart(){
	target_pwm = _start_pwm;
	smooth_timer = 2000;
	smooth_step = target_pwm / (smooth_timer * 1000);
	smooth = true;
}

void DriveControl::smoothStart(int duration){
	target_pwm = _start_pwm;
	smooth_timer = duration * 1000;
	smooth_step = target_pwm / (smooth_timer * 1000);
	smooth = true;
}
void DriveControl::smoothStop(){
	target_pwm = 0;
	smooth_timer = 2000;
	smooth_step = target_pwm / (smooth_timer * 1000);
	smooth = true;
}
void DriveControl::smoothStop(int duration){
	target_pwm = 0;
	smooth_timer = duration * 1000;
	smooth_step = target_pwm / (smooth_timer * 1000);
	smooth = true;
}
void DriveControl::smoothAccel(int pwm, int duration){
	target_pwm = pwm;
	smooth_timer = duration * 1000;
	smooth_step = target_pwm / (smooth_timer * 1000);
	smooth = true;
}

void DriveControl::set_pin(int pin){
	_pin = pin;
}
void DriveControl::set_start_pwm(int pwm){
	_start_pwm = pwm;
}

