#include <DirectCurrent-Motor-Module.h>

DirectCurrent motor1 = { 9, 8, 10 };
DirectCurrent motor2 = { 7, 6, 5 };

int engine1 = 10;
int input_pin1 = 9;
int input_pin2 = 8;
int engine2 = 5;
int input_pin3 = 7;
int input_pin4 = 6;
int sensor_output;
int sensor_input;
long sensor_distance = 0;

void setup() {
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
  motor1.move(motor1, 1, 0, 200);
  digitalWrite(signal_output, 0);
  delay(5);
  digitalWrite(signal_output, 1);
  delayMicroseconds(10);
  digitalWrite(signal_output, 0);
  long time = pulseIn(signal_echo, 1);
  distance = (time / 2) * 0.03432;
  delay(500);
  if (distance < 100) {
    
  }
}
