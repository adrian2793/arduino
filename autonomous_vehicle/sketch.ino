int engine1 = 10;
int engine2 = 5;

int input_pin1 = 9;
int input_pin2 = 8;

int input_pin3 = 7;
int input_pin4 = 6;

void engine_control(string pin, string engine_id, int mode, int speed) {
  digitalWrite(pin, mode);
  analogWrite(engine_id, speed);
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
  digitalWrite(input_pin1, HIGH);
  digitalWrite(input_pin2, LOW);
  analogWrite(engine1, 200); 
  digitalWrite(input_pin3, HIGH);
  digitalWrite(input_pin4, LOW);
  analogWrite(engine2, 200);
  delay(2000);
  digitalWrite(input_pin1, LOW);
  digitalWrite(input_pin2, HIGH);  
  digitalWrite(input_pin3, LOW);
  digitalWrite(input_pin4, HIGH); 
  delay(2000);
  digitalWrite(input_pin1, LOW);
  digitalWrite(input_pin2, LOW);  
  digitalWrite(input_pin3, LOW);
  digitalWrite(input_pin4, LOW);
  delay(2000);
}
