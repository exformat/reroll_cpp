#include "DriveControl.h"
#include "GyverEncoder.h"
#include "RelayControl.h"
#include "GyverButton.h"

#define DRV_PIN   11
#define ENC_L_PIN 4
#define ENC_R_PIN 5
#define RL_PIN    12
#define BTN_STP   8
#define BTN_SRT   7
#define HALL_SNR  2

DriveControl drive(DRV_PIN, 30);
Encoder encoder(ENC_L_PIN, ENC_R_PIN, 6, TYPE2);
Relay relay(RL_PIN);
GButton btn_stp(BTN_STP);
GButton btn_srt(BTN_SRT);

boolean work = false;
volatile boolean sensor_trig = false;
long strg_time = 0;
long old_strg_time = 1;
long delta_strg = 1;

long tick_time = 0;
long old_tick_time = 1;
long delta_time = 0;

int target = 0;
float material_counter = 0;
float step_counter = 0;
const int STEP = 25;
const int MAT_STEP = 200;

float mpm = 0;

void setup(){
	Serial.begin(9600);
	Serial.println("hello, im iroller!");
	attachInterrupt(digitalPinToInterrupt(HALL_SNR), sensor_control, RISING);
	tick_time = millis();
}

void loop(){
	time_control();

	//tick();
	//mpm_control();
	//material_control();
	//encoder_control();
	//button_control();
}

void mpm_control(){
	//calculation of the time between sensor triggering
	if(sensor_trig){
        material_counter += STEP;
        step_counter++;

        old_strg_time = strg_time;
        strg_time = tick_time;
        delta_strg = strg_time - old_strg_time;
        trg = false;
    }
	//calculation of meters per minute
    float f = delta_trg;
    mpm = STEP / (f / 1000 / 60) / 1000;
}

void time_control(){
    tick_time = millis();
    
	if(tick_time > old_tick_time){
		delta_time = tick_time - old_tick_time;
		old_tick_time = tick_time;
	}
}

void material_control(){
	if(material_counter >= target){
		relay.off();
		drive.stop();
		work = false;
	}
}

void sensor_control(){
	if(!sensor_trig){
		sensor_trig = true;
    }
}

void button_control(){
	if(btn_srt.isPress()){
        if(work){
			drive.stop();
			work = false;
        }
        else{
			drive.start();
			work = true;
        }
	}
}

void encoder_control(){
	if(work){
		if(encoder.isRight()){
			Serial.println("accel incr.");
			drive.accel(1);
		}
		if(encoder.isLeft()){
			Serial.println("accel decr.");
			drive.accel(-1);
		}
	}
	else{
		if(encoder.isLeft()){
			Serial.println("target incr.");
			target += MAT_STEP;
		}
		if(encoder.isRight() && target > MAT_STEP){
			Serial.println("target decr.");
			target -= MAT_STEP;
		}
	}
}

void tick(){
	drive.tick();
	encoder.tick();
	btn_stp.tick();
	btn_srt.tick();
}

