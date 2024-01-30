#include <Servo_Motor_Module.h>
#include <DirectCurrent_Motor_Module.h>

DirectCurrent motor1 = { 12, 13, 8 };
DirectCurrent motor2 = { 10, 11, 9 };
Servo2 servo1 = { 3 };

int engine1 = 8;
int input_pin1 = 12;
int input_pin2 = 13;
int engine2 = 9;
int input_pin3 = 10;
int input_pin4 = 11;
int sensor_output = 7;
int sensor_input = 6;
long sensor_distance = 0;
int angle1;

void setup() {
  Serial.begin(9600);
  servo1.attach();
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
  digitalWrite(sensor_output, 0);
  delay(5);
  digitalWrite(sensor_output, 1);
  delayMicroseconds(10);
  digitalWrite(sensor_output, 0);
  long time = pulseIn(sensor_input, 1);
  sensor_distance = (time / 2) * 0.03432;
  Serial.println(sensor_distance);
  if (sensor_distance < 20) {
    motor1.move(1,0,150);
    motor2.move(0,1,200);
  }
}
  if (sensor_distance < 100) {
    motor1.move(1, 0, 100);
  }
}
