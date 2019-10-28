#include "DriveControl.h" 
#include "RelayControl.h" 
#include "Encoder.h" 
#include "GyverButton.h" 

int relay_pin = 12; 
int drive_control_pin = 11; 
int start_drive_value = 30; 
int enc_pin_left = 10; 
int enc_pin_right = 9; 
int enc_pin_clk = 8; 
int btn_start_pin = 7; 
int btn_stop_pin = 6; 

Encoder encoder(enc_pin_clk, enc_pin_left, enc_pin_right, true, true); 
RelayControl relay(relay_pin); 
DriveControl drive_control(drive_control_pin, start_drive_value); 
GButton btn_start(btn_start_pin, HIGH_PULL, NORM_OPEN);
GButton btn_stop(btn_stop_pin, HIGH_PULL, NORM_OPEN);
void setup(){ 	 } 
void loop(){ 	
				encoder.tick(); 
				btn_start.tick(); 	
				btn_stop.tick(); 	 
				enc_drive_control(); 	
				btn_drive_control(); 
} 
void btn_drive_control(){ 	
				if(btn_start.isPress()){
								drive_control.start_drive(); 	
				} 	
				if(btn_stop.isPress()){
								drive_control.stop_drive(); 
				} 
} 
void enc_drive_control(){ 	
				if(encoder.isTurn()){ 		
								if(encoder.isLeft()){
												drive_control.accel_drive(-1); 		
								} 		
								if(encoder.isRight()){
								    drive_control.accel_drive(1); 		
								} 	
				} 
}