#include "DriveControl.h"
#include "GyverEncoder.h"
#include "Relay.h"
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
HSensor sensor(HALL_SNR);



void setup(){
	Serial.begin(9600);
	Serial.println("hello world!");
				
	attachInterrupt(digitalPinToInterrupt(HALL_SNR), sensor_tick, RISING);
				
	pinMode(13, OUTPUT);
}

void loop(){
	tick();
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

