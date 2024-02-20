#include <Servo.h>
#include <DirectCurrent_Motor_Module.h>

DirectCurrent motor1 = { 12, 13, 8 };
DirectCurrent motor2 = { 10, 11, 9 };
Servo servo1;

int engine1 = 8;
int input_pin1 = 12;
int input_pin2 = 13;
int engine2 = 9;
int input_pin3 = 10;
int input_pin4 = 11;
int sensor_output = 7;
int sensor_input = 6;
long sensor_distance = 0;
int angle1 = 0;
int pos = 0;
int position_status = 0;
int degree = 0;

void setup() {
  Serial.begin(250000);
  pinMode(engine1, OUTPUT);
  pinMode(engine2, OUTPUT);
  pinMode(input_pin1, OUTPUT);
  pinMode(input_pin2, OUTPUT);
  pinMode(input_pin3, OUTPUT);
  pinMode(input_pin4, OUTPUT);
  pinMode(sensor_output, OUTPUT);
  pinMode(sensor_input, INPUT);
}

void loop() {
  if (degree > 15) {
    degree =- 1;
  } else {
    degree =+ 1;
  }
  // servo1.write(degree);
  pos = degree;
  if (pos > 60) {
    position_status = 1; // left
  }
  if (pos < 60) {
    position_status = 2;
  }
  delay(10);
  digitalWrite(sensor_output, 0);
  delay(5);
  digitalWrite(sensor_output, 1);
  delay(5);
  digitalWrite(sensor_output, 0);
  long time = pulseIn(sensor_input, 1);
  sensor_distance = (time / 2) * 0.03432;
  Serial.println(sensor_distance);
  if (sensor_distance < 20) {
    motor1.move(1, 0, 100);
    motor2.move(0, 1, 200);
  } else {
    motor1.move(1, 0, 100);
    motor2.move(1, 0, 100);
  }
}
