#include "DriveControl.h"
#include "GyverEncoder.h"
#include "RelayControl.h"
#include "GyverButton.h"
#include "HallSensor.h"

#define DRV_PIN   11
#define ENC_L_PIN 10
#define ENC_R_PIN 9
#define RL_PIN    12
#define BTN_STP   8
#define BTN_SRT   7
#define HALL_SNR  2

DriveControl drive(DRV_PIN, 30);
Encoder encoder(ENC_L_PIN, ENC_R_PIN, 4, TYPE1);
Relay relay(RL_PIN);
GButton btn_stp(BTN_STP);
GButton btn_srt(BTN_SRT);
HSensor sensor(HALL_SNR, TYPE2);

boolean work = false;

long tick_time = 0;
long old_tick_time = 0;
long delta_time = 0;
long delta_counter = 0;

int target = 0;
int material_counter = 0;
int step_counter = 0;
const int STEP = 25;
const int MAT_STEP = 200;

float mpm = 0;
const int time_step = 200;

void setup(){
	Serial.begin(9600);
	Serial.println("hello world!");
				
	attachInterrupt(digitalPinToInterrupt(HALL_SNR), sensor_tick, RISING);
				
	pinMode(13, OUTPUT);
	tick_time = millis();
}

void loop(){
	time_control();
	
	
	tick();
	//test();
	mpm_control();
	material_control();
	sensor_control();
	encoder_control();
	button_control();
}

void mpm_control(){
	if(delta_counter > time_step){
		//calc meter peer minut
		mpm = step_counter * STEP * (1000 / time_step) * 60 / 1000;
		step_counter = 0;
		delta_counter = 0;
	}
}

void time_control(){
	if(tick_time > old_tick_time){
		old_tick_time = tick_time;
		tick_time = millis();
		delta_time = tick_time - old_tick_time;
		delta_counter += delta_time;
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
	if(sensor.isTriggered()){
		material_counter += STEP;
		step_counter += STEP;
	}
}

void button_control(){
	if(btn_stp.isPress()){
		relay.off();
		drive.stop();
		work = false;
	}
	if(btn_srt.isPress()){
		relay.on();
		drive.start();
		work = true;
	}
}

void encoder_control(){
	if(work){
		if(encoder.isLeft()){
			Serial.println("accel incr.");
			drive.accel(1);
		}
		if(encoder.isRight()){
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

void sensor_tick(){
	sensor.tick();
}

void tick(){
	drive.tick();
	encoder.tick();
	btn_stp.tick();
	btn_srt.tick();
	//sensor.tick();
}

void test(){
		/* //test hall sensor in intrrupt
	if(sensor.isTriggered()){
		relay.switch_relay();
	}
				
	/* //test button
	if(btn.isPress()){
		relay.switch_relay();
	}
	if(btn.isRelease()){
		relay.switch_relay();
	}
				
	/* //test relay
	relay.off();		
	relay.switch_relay();
	if(relay.is_switch()){
		Serial.println("relay switch");
	}
	delay(500);
				
	/* //test encoder
	drive.tick();
	encoder.tick();
	if(encoder.isLeft()){
		Serial.println("left");
		digitalWrite(13, HIGH);
	}
	if(encoder.isRight()){
		Serial.println("right");
		digitalWrite(13, LOW);
	}
	*/
}

