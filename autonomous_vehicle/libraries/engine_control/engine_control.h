#include <engine_control_component.h>

void engine_control(int pin, int engine_id, int mode, int speed) {
  digitalWrite(pin, mode);
  if(speed == "") {
  } else {
    analogWrite(engine_id, speed);
  }
}

void setup() {
  pinMode(engine1, OUTPUT);    
  pinMode(engine2, OUTPUT);
  pinMode(input_pin1, OUTPUT);
  pinMode(input_pin2, OUTPUT);
  pinMode(input_pin3, OUTPUT);
  pinMode(input_pin4, OUTPUT);
}

void loop() {
  engine_control(9, 10, 1, 200);
  engine_control(8, 10, 0, 0);
}
