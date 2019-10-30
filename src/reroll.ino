#define CLK 11 
#define DT 10
#define SW 3
#define drv 9

#include "GyverEncoder.h" 
#include "DriveControl.h"

Encoder enc(CLK, DT, SW, TYPE1); 
DriveControl drive(drv, 30);

void setup(){
	Serial.begin(9600);
	Serial.println("hi war");
	enc.setTickMode(AUTO);
	drive.start_drive();
}

void loop(){
	if(enc.isRight()){
		Serial.println("Right");
		drive.accel_drive(1);
	}
	if (enc.isLeft()){
		Serial.println("Left");
		drive.accel_drive(-1);
	}
}
