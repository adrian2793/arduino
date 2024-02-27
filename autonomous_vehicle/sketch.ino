#include <Servo_Motor_Module.h>
#include <DirectCurrent_Motor_Module.h>

DirectCurrent motor1 = { 12, 13, 8 };
DirectCurrent motor2 = { 10, 11, 9 };
Servo2 servo1;

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
bool move_left = false;
bool move_right = false;

void setup() {
  Serial.begin(250000);
  servo1.attach(3);
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
  int x = 1;
  for (int i = 0; i > -1; i = i + x) {
    servo1.move(i);
    digitalWrite(sensor_output, 0);
    digitalWrite(sensor_output, 1);
    digitalWrite(sensor_output, 0);
    long time = pulseIn(sensor_input, 1);
    sensor_distance = (time / 2) * 0.03432;
    Serial.println(sensor_distance);
    if (sensor_distance < 20) {
      if (position_status = 2 && sensor_distance != 3 && sensor_distance != 2 && sensor_distance != 1 && sensor_distance != 0){
        motor1.move(1, 0, 100);
        motor2.move(0, 1, 200);
        } else if (position_status = 1 && sensor_distance != 3 && sensor_distance != 2 && sensor_distance != 1 && sensor_distance != 0) {
          motor1.move(0, 1, 100);
          motor2.move(1, 0, 200);
        }
      } else if (sensor_distance < 3) {
        motor1.move(0, 1, 200);
        motor1.move(0, 1, 200);
      }
      if (sensor_distance > 20 && sensor_distance != 3 && sensor_distance != 2 && sensor_distance != 1 && sensor_distance != 0) {
        motor1.move(1, 0, 100);
        motor2.move(1, 0, 100);
      }
      if (i == 90) {
        x = -1;
        i = 0;
        servo1.move(-90);
      }
      delay(5);
      pos = degree;
      if (pos < 90) {
      position_status = 2; // right
      }
      if (pos > 89) {
      position_status = 1; // left
      }
    }
  }
