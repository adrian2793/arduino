#include <DirectCurrent-Motor-Module.h>

int engine1 = 10;
int input_pin1 = 9;
int input_pin2 = 8;
int engine2 = 5;
int input_pin3 = 7;
int input_pin4 = 6;

void setup() {
  pinMode(engine1, OUTPUT);    
  pinMode(engine2, OUTPUT);
  pinMode(input_pin1, OUTPUT);
  pinMode(input_pin2, OUTPUT);
  pinMode(input_pin3, OUTPUT);
  pinMode(input_pin4, OUTPUT);
  DirectCurrent motor1 = { 9, 8, 10 };
  DirectCurrent motor2 = { 7, 6, 5 };
}
