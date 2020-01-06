#include "DriveControl.h"
#include "Arduino.h"
#include <cmath>

using namespace std;

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
	delta_time = (tick_time - old_tick_time) / 1000;
	
	if(smooth){
		smoothFunction();
	}
}
	
void DriveControl::stop(){
	analogWrite(_pin, 0);
	_pwm = 0;
}

void DriveControl::start(){
	_pwm = _srt_drv_val;
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
	target_smoot_timer += delta_time;
	if(target_pwm > 0){
		smoorh_pwm_step = 1;
	}
	else{
		smoorh_pwm_step = -1;
	}
	if(smooth_timer > 0){
		if(target_smooth_timer >= smooth_step){
			accel(smoorh_pwm_step);
			target_smooth_timer = 0;
		}
	}
}


void DriveControl::smooth_start(){
	target_pwm = _start_pwm;
	smooth_timer = 2;
	smooth_step = target_pwm / (smooth_timer * 1000);
	smooth = true;
}

void DriveControl::smooth_start(int duration){
	target_pwm = _srt_drv_val;
	smooth_timer = duration;
	smooth_step = target_pwm / (smooth_timer * 1000);
	smooth = true;
}
void DriveControl::smooth_stop(){
	target_pwm = 0;
	smooth_timer = 2;
	smooth_step = target_pwm / (smooth_timer * 1000);
	smooth = true;
}
void DriveControl::smooth_stop(int duration){
	target_pwm = 0;
	smoorh_timer = duration;
	smooth_step = target_pwm / (smooth_timer * 1000);
	smooth = true;
}
void DriveControl::smooth_accel(int pwm, int duration){
	target_pwm = pwm;
	smootj_timer = duration;
	smooth_step = target_pwm / (smooth_timer * 1000);
	smooth = true;
}

void DriveControl::set_pin(int pin){
	_pin = pin;
}
void DriveControl::set_start_pwm(int pwm){
	_start_pwm = pwm;
}

