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

void setup() {
  lcd_port.init();
  lcd_port.backlight();
  lcd_port.setCursor(0, 0);
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
  dot_1run = dot_1run + 1;
  lcd_port.clear();
  switch (dot_2run) {
  case 0:
    lcd_port.setCursor(0, 0);
    lcd_port.print("Board Computer 1");
    lcd_port.setCursor(0, 1);
    lcd_port.print("Distance " + String(sensor_distance));
    dot_2run = 1;
    break;
  case 1:
    lcd_port.setCursor(0, 0);
    lcd_port.setCursor(0, 0);
    lcd_port.print("Board Computer 2");
    lcd_port.setCursor(0, 1);
    lcd_port.print("Cycles " + String(dot_1run));
    dot_2run = 2;
    break;
  case 2:
    lcd_port.setCursor(0, 0);
    lcd_port.setCursor(0, 0);
    lcd_port.print("Board Computer 3");
    lcd_port.setCursor(0, 1);
    lcd_port.print("Empty slot");
    dot_2run = 3;
    break;
  case 3:
    lcd_port.setCursor(0, 0);
    lcd_port.setCursor(0, 0);
    lcd_port.print("Board Computer 4");
    lcd_port.setCursor(0, 1);
    lcd_port.print("Empty slot");
    dot_2run = 0;
    break;
}
  int x = 1;
  for (i = 0; i > -1; i = i + x) {
    time_since_last_run = i;
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
