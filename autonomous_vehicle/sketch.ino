#include <Servo_Motor_Module.h>
#include <DirectCurrent_Motor_Module.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd_port(0x27, 16, 2);
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
bool lcd_task_finished = false;
int time_since_last_run = 0;
int i;
int dot_1run;
int dot_2run = 0;
String board_language = "en";
String current_task = "1";
String current_task2 = "1";
int motor1_input1 = 0;
int motor1_input2 = 0;
int motor1_speed = 150;
int motor2_input1 = 0;
int motor2_input2 = 0;
int motor2_speed = 150;
int x = 1;
int calculated_distance = 0;
int sensor_config_max = 20;
int sensor_config_min = 20;
bool true22 = true;

void setup() {
  lcd_port.init();
  lcd_port.backlight();
  lcd_port.noCursor();
  lcd_port.leftToRight();
  lcd_port.noBlink();
  lcd_port.setCursor(0, 0);
  Serial.begin(9600);
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
  drive_right();
}

int calculate_2_wall_distance(int measure_value) {
  calculated_distance = measure_value;
  sensor_config_max = calculated_distance;
  sensor_config_min = calculated_distance;
  return true;
}

void drive_right() {
  dot_2run = 0;
  current_task = "Drive right";
  current_task2 = String(motor2_input1) + ", " + String(motor2_input2) + ", " + String(motor2_speed);
  dot_1run = dot_1run + 1;
  Serial.print("Speed1: ");
  Serial.println(motor1_speed);
  Serial.print("Speed2: ");
  Serial.println(motor2_speed);
  pos = pos + 1;
  if (pos == 30) {
    pos = 0;
  }
  servo1.move(pos);
  digitalWrite(sensor_output, 0);
  digitalWrite(sensor_output, 1);
  digitalWrite(sensor_output, 0);
  long time = pulseIn(sensor_input, 1);
  sensor_distance = (time / 2) * 0.03432;
  Serial.println(sensor_distance);
  if (sensor_distance < 20) {
      motor1_input1 = 0; // 1
      motor1_input2 = 1; // 0
      motor1_speed = motor1_speed - 10;
      if (motor1_speed < 0) {
        motor1_speed = 0;
      }
      motor2_input1 = 1; // 1
      motor2_input2 = 0; // 0
      motor2_speed = motor2_speed + 10;
      if (motor2_speed > 255) {
        motor2_speed = 255;
      }
      motor1.move(motor1_input1, motor1_input2, motor1_speed);
      motor2.move(motor2_input1, motor2_input2, motor2_speed);
      } else {
        motor1_input1 = 1;
        motor1_input2 = 0;
        motor1_speed = motor1_speed + 10;
         if (motor1_speed > 255) {
          motor1_speed = 255;
       }
        motor2_input1 = 1;
        motor2_input2 = 0;
        motor2_speed = motor2_speed - 10;
        if (motor2_speed < 0) {
          motor2_speed = 0;
       }
       motor1.move(motor1_input1, motor1_input2, motor1_speed);
        motor2.move(motor2_input1, motor2_input2, motor2_speed);
      }
    if (sensor_distance < 5) {
      motor1_input1 = 0;
      motor1_input2 = 1;
      motor1_speed = 0;
      motor2_input1 = 0;
      motor2_input2 = 1;
      motor2_speed = 0;
      motor1.move(motor1_input1, motor1_input2, motor1_speed);
      motor1.move(motor2_input1, motor2_input2, motor2_speed);
    }
    if (sensor_distance > 20 && sensor_distance != 3 && sensor_distance != 2 && sensor_distance != 1 && sensor_distance != 0) {
      motor1_input1 = 1;
      motor1_input2 = 0;
      motor1_speed = 255;
      motor2_input1 = 1;
      motor2_input2 = 0;
      motor2_speed = 255;
      motor1.move(motor1_input1, motor1_input2, motor1_speed);
      motor2.move(motor2_input1, motor2_input2, motor2_speed);
    }
    delay(5);
  }

void drive_autonomous() {
  motor1_speed = 150;
  motor2_speed = 150;
  x = 1;
  dot_2run = 0;
  current_task = "1{" + String(motor1_input1) + ", " + String(motor1_input2) + ", " + String(motor1_speed) + "}";
  current_task2 = "2{" + String(motor2_input1) + ", " + String(motor2_input2) + ", " + String(motor2_speed)+ "}";
  dot_1run = dot_1run + 1;
  lcd_port.clear();
  lcd_port.setCursor(0, 0);
  lcd_port.print(current_task);
  lcd_port.setCursor(0, 1);
  lcd_port.print(current_task2);
  for (i = 0; i > -1; i = i + x) {
    Serial.print("Speed1: ");
    Serial.println(motor1_speed);
    Serial.print("Speed2: ");
    Serial.println(motor2_speed);
    pos = i;
    if (pos > 55) {
      position_status = 2; // left
      Serial.print("Position: ");
      Serial.println(position_status);
    }
    else {
      position_status = 1; // right
      Serial.print("Position: ");
      Serial.println(position_status);
    }
    servo1.move(i);
    digitalWrite(sensor_output, 0);
    digitalWrite(sensor_output, 1);
    digitalWrite(sensor_output, 0);
    long time = pulseIn(sensor_input, 1);
    sensor_distance = (time / 2) * 0.03432;
    Serial.println(sensor_distance);
    if (true22 == true) {
    if (sensor_distance < sensor_config_max) {
      if (position_status = 2 && sensor_distance != 3 && sensor_distance != 2 && sensor_distance != 1 && sensor_distance != 0){
        motor1_input1 = 1;
        motor1_input2 = 0;
        motor1_speed = motor1_speed - 10;
        motor2_input1 = 1;
        motor2_input2 = 0;
        motor2_speed = motor2_speed + 10;
        motor1.move(motor1_input1, motor1_input2, motor1_speed);
        motor2.move(motor2_input1, motor2_input2, motor2_speed);
      }
      if (position_status = 1 && sensor_distance != 3 && sensor_distance != 2 && sensor_distance != 1 && sensor_distance != 0) {
          motor1_input1 = 1;
          motor1_input2 = 0;
          motor1_speed = motor1_speed + 10;
          motor2_input1 = 1;
          motor2_input2 = 0;
          motor2_speed = motor2_speed - 10;
          motor1.move(motor1_input1, motor1_input2, motor1_speed);
          motor2.move(motor2_input1, motor2_input2, motor2_speed);
      }
      }
      if (sensor_distance < 3) {
        motor1_input1 = 0;
        motor1_input2 = 1;
        motor1_speed = 0;
        motor2_input1 = 0;
        motor2_input2 = 1;
        motor2_speed = 0;
        motor1.move(motor1_input1, motor1_input2, motor1_speed);
        motor1.move(motor2_input1, motor2_input2, motor2_speed);
      }
      if (sensor_distance > sensor_config_max && sensor_distance != 3 && sensor_distance != 2 && sensor_distance != 1 && sensor_distance != 0) {
        motor1_input1 = 1;
        motor1_input2 = 0;
        motor1_speed = 100;
        motor2_input1 = 1;
        motor2_input2 = 0;
        motor2_speed = 100;
        motor1.move(motor1_input1, motor1_input2, motor1_speed);
        motor2.move(motor2_input1, motor2_input2, motor2_speed);
      }
      if (i == 110) {
        x = -1;
      }
      delay(5);
    } else {
      motor1_input1 = 1;
      motor1_input2 = 0;
      motor1_speed = 85;
      motor2_input1 = 1;
      motor2_input2 = 0;
      motor2_speed = 85;
      motor1.move(motor1_input1, motor1_input2, motor1_speed);
      motor2.move(motor2_input1, motor2_input2, motor2_speed);
    }
  }
  }
