#include <Servo.h>

int servo = 7 ;
int trigger = 8;
int echo = 9;
int angle = 90;
int servoDelay = 2;
int sensorDelay = 10;
int openCloseDelay = 2000;
long duration = 0;
float distance = 0;

Servo myServo;

void setup() {
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  digitalWrite(servo, LOW);
  digitalWrite(trigger, LOW);

  myServo.attach(servo);
  myServo.write(angle);
}

void loop() {
  delay(sensorDelay);
  digitalWrite(trigger, HIGH);
  delay(sensorDelay);
  digitalWrite(trigger, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration * 0.034 / 2;
  Serial.println(distance);

  if (distance <= 50.0) {
    angle = 0;
    myServo.write(angle);
    delay(openCloseDelay);  
  } else {
    angle = 90;
    myServo.write(angle);
    delay(openCloseDelay);  
  }
}
