#include <Servo.h>
#include <DirectCurrent_Motor_Module.h>
#define N 50

DirectCurrent motor1 = { 12, 13, 8 };
DirectCurrent motor2 = { 10, 11, 9 };
Servo servo1;

class AISwitch {
  public:
      float x[N];
      float y[N];
      float a;
      float b;
      float alpha;
      int train_model();
};

float x[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50};
float y[N] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80, 82, 84, 86, 88, 90, 92, 94, 96, 98, 100};
float a = 0;
float b = 0;
float alpha = 0.1;
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

int train_model() {
  while (true) {
    float error = 0;
    for (int i = 0; i < N; i++) {
      error += pow(y[i] - (a * x[i] + b), 2);
    }
    error /= N;
    Serial.println(b);
    if (error < 0.1) {
      break;
      return true;
    } else {
      return false;
    }
    float da = 0;
    float db = 0;
    for (int i = 0; i < N; i++) {
      da += -2 * x[i] * (y[i] - (a * x[i] + b));
      db += -2 * (y[i] - (a * x[i] + b));
    }
    da /= N;
    db /= N;
    a = a - alpha * da;
    b = b - alpha * db;
  }
}

float predict(float x) {
  return a * x + b;
}

void loop() {
  train_model();
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
  float distance2 = {sensor_distance};
  float x_new = {distance2};
  float y_new = predict(x_new);
  Serial.print("Output: ");
  Serial.println(y_new);
  if (sensor_distance < 20) {
    motor1.move(1, 0, 100);
    motor2.move(0, 1, 200);
  } else {
    motor1.move(1, 0, 100);
    motor2.move(1, 0, 100);
  }
}
