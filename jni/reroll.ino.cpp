//encoder pins
#define CLK 11
#define DT 10
#define SW 3

//drive control pins
#define DRIVE_PIN 9

//relay pins
#define RELAY_PIN 8

//button pins
#define START_PIN 7
#define STOP_PIN 6

//sensor pins
#define HALL_SENSOR_PIN 5

#include "GyverEncoder.h" 
#include "DriveControl.h"
#include "Relay.h"
#include "GyverButton.h"
#include "HallSensor.h"

Encoder encoder(CLK, DT, SW, TYPE1);
DriveControl drive(DRIVE_PIN, 30);
Relay relay(RELAY_PIN);
GButton btn_start(START_PIN);
GButton btn_stop(STOP_PIN);
HSensor h_sensor(HALL_SENSOR_PIN);

boolean drive_work = false;
int counter = 0;

void setup(){
	Serial.begin(9600);
	Serial.println("hi monkeycoder");
	
	attachInterrupt(
		digitalPinToInterrupt(
			HALL_SENSOR_PIN, h_sensor_read, RISING));
}

void loop(){
	tick();
	drive_control();
	
	if(h_sensor.isTriggered()){
		counter++;
	}
}

void h_sensor_read(){
	h_sensor.tick();
}

void drive_control(){
	if(drive_work){
		if(btn_stop.isPress()){
			Serial.println("stop drive");
			relay.off();
			drive.stop_drive();
		}
	}
	else{
		if(btn_start.isPress()){
			Serial.println("start drive");
			relay.on();
			drive.start_drive();
		}
	}
	
	if(encoder.isRight()){
		Serial.println("Right");
		drive.accel_drive(1);
	}
	if(enc1.isLeft()){
		Serial.println("Left");
		drive.accel_drive(-1);
	}
}

void tick(){
	encoder.tick();
	btn_start.tick();
	btn_stop.tick();
	drive.tick();
	//h_sensor.tick();
}
