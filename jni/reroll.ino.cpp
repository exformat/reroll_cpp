#define CLK 11
#define DT 10
#define SW 3
#define DRV_PIN 9

#include "GyverEncoder.h" 
#include "DriveControl.h"

Encoder encoder(CLK, DT, SW, TYPE1);
DriveControl drive(DRV_PIN, 30);

void setup(){
	Serial.begin(9600);
	Serial.println("hi war");
	
	encoder.setTickMode(AUTO);
	drive.start_drive();
}

void loop(){
	if(encoder.isRight()){
		Serial.println("Right");
		drive.accel_drive(1);
	}
	if(enc1.isLeft()){
		Serial.println("Left");
		drive.accel_drive(-1);
	}
}
