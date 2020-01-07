#include "DriveControl.h"
#include "GyverEncoder.h"
#include "RelayControl.h"
#include "GyverButton.h"

#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "LiquidCrystal_PCF8574.h"

#define HALL_SNR  2

#define ENC_CLK_PIN 4
#define ENC_DT_PIN  5
#define ENC_SW_PIN  6

#define BTN_SRT   7
#define BTN_STP   8

#define DRV_PIN   9
#define DRV2_PIN 10

#define UP_SNR_PIN 11
#define DN_SNR_PIN 12

DriveControl roll_drive(DRV_PIN, 30);
DriveControl punch_drive(DRV2_PIN, 30);

Encoder encoder(ENC_CLK_PIN, ENC_DT_PIN, ENC_SW_PIN, TYPE1);
//Relay relay(RL_PIN);
GButton btn_stp(BTN_STP);
GButton btn_srt(BTN_SRT);
GButton up_sensor(UP_SNR_PIN);
GButton dn_sensor(DN_SNR_PIN);

LiquidCrystal_I2C lcd(0x27, 16, 2);

boolean work = true;
volatile boolean sensor_trig = false;
long strg_time = 0;
long old_strg_time = 1;
long delta_strg = 1;

long tick_time = 0;
long old_tick_time = 1;
long delta_time = 0;

long lcd_time = 0;

int target = 3000;
float material_counter = 0;
float step_counter = 0;
const float STEP = 27.75f;
const int MAT_STEP = 200;

int rpm = 0;

volatile float mpm = 0;

String trg_str = "";
String mpm_str = "";

void setup() {

  Serial.begin(9600);
  Serial.println("hello, im iroller!");
  attachInterrupt(digitalPinToInterrupt(HALL_SNR), sensor_control, RISING);
  tick_time = millis();

  lcd.init();
  lcd.backlight();
  //lcd.setCursor(0, 0);
  //lcd.print("hello world");

}

void loop() {
  time_control();

  tick();
  mpm_control();
  print();



  material_control();
  encoder_control();
  //button_control();
}

void print() {

  lcd.setCursor(0, 0);
  lcd.print(mpm_str);
  lcd.setCursor(5, 0);
  lcd.print(rpm);
  lcd.setCursor(0, 1);
  lcd.print(trg_str);
  lcd.setCursor(5, 1);
  lcd.print(target);

  if (lcd_time > 1000) {
    // Serial.println(mpm);
    lcd_time = 0;



  }
  lcd_time += delta_time;
}



boolean brake = false;
void material_control() {
  if(target - material_counter <= 500 && !brake){
    roll_drive.smoothStop();
  }
  
  if (material_counter >= target) {
    //relay.off();
    roll_drive.stop();
    punch_drive.stop();
    work = false;
  }
}


void button_control() {
  if (btn_srt.isPress()) {
    if (work) {
      roll_drive.stop();
      punch_drive.stop();
      work = false;
    }
    else {
      roll_drive.start();
      punch_drive.start();
      work = true;
    }
  }
}


boolean target_setup = false;
void encoder_control() {
  if (!target_setup || work) {
    if (encoder.isRight() && rpm < 250) { //acceleration increment
      lcd.clear();
      rpm++;
      punch_drive.accel(1);
      Serial.println("accel incr.");
    }
    if (encoder.isLeft() && rpm > 0) { //acceleration decrement
      lcd.clear();
      rpm--;
      punch_drive.accel(-1);
      roll_drive.accel(-1);
      Serial.println("accel decr.");
    }
  }
  else {
    if (encoder.isRight()) {
      Serial.println("target incr.");
      lcd.clear();

      target += MAT_STEP;
    }
    if (encoder.isLeft() && target > MAT_STEP) {
      lcd.clear();
      target -= MAT_STEP;
      Serial.println("target decr.");
    }
  }
  if (encoder.isClick()) {
    target_setup = !target_setup;
    if (target_setup) {
      trg_str = "* trg: ";
      mpm_str = "  mpm: ";
    }
    else {
      trg_str = "  trg: ";
      mpm_str = "* mpm: ";
    }
  }
}

void drivesControl() {
  if (up_sensor.isPress()) {
    roll_drive.accel(-5);
  }
  if (dn_sensor.isPress()) {
    roll_drive.accel(5);
  }
}

void sensor_control() {
  if (!sensor_trig) {
    sensor_trig = true;
  }
}

void time_control() {
  tick_time = millis();

  if (tick_time > old_tick_time) {
    delta_time = tick_time - old_tick_time;
    old_tick_time = tick_time;
  }
}

void mpm_control() {
  //calculation of the time between sensor triggering
  if (sensor_trig) {
    material_counter += STEP;
    step_counter++;
    strg_time = tick_time;
    old_strg_time = tick_time;

    sensor_trig = false;
  }
  //calculation of meters per minute
  delta_strg = tick_time - old_strg_time;
  float f = delta_strg;
  mpm = STEP / (f / 1000 / 60) / 1000;
}

void tick() {
  roll_drive.tick();
  punch_drive.tick();

  encoder.tick();
  btn_stp.tick();
  btn_srt.tick();
}
