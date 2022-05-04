#include <IRremote.hpp>

int IRreceptor = 4;
int redLeds = 5;
int blueLeds = 6;
int yellowLeds = 7;

int counter = 1;
int delayTime = 300;
int delayShortTime = 50; 
void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IRreceptor);
  pinMode(redLeds, OUTPUT);
  pinMode(blueLeds, OUTPUT);
  pinMode(yellowLeds, OUTPUT);
  pinMode(IRreceptor, INPUT);
}

void loop() {  
  turnOffLeds();
  if (counter == 1) {
    turnOffLeds();
    while (counter == 1) {
      IrReader();
      digitalWrite(redLeds, HIGH);
      delay(delayTime);
      digitalWrite(redLeds, LOW);
      digitalWrite(blueLeds, HIGH);
      delay(delayTime);
      digitalWrite(blueLeds, LOW);
      digitalWrite(yellowLeds, HIGH);
      delay(delayTime);
      digitalWrite(yellowLeds, LOW);  
    }
  } else if (counter == 2) {
    turnOffLeds();
    while (counter == 2) {
      IrReader();
      for (int i = 0; i < 4; i++) {
        digitalWrite(redLeds, HIGH);
        delay(delayShortTime);
        digitalWrite(redLeds, LOW);
        delay(delayShortTime);  
      }

      IrReader();
      for (int i = 0; i < 4; i++) {
        digitalWrite(blueLeds, HIGH);
        delay(delayShortTime);
        digitalWrite(blueLeds, LOW);
        delay(delayShortTime);  
      }

      IrReader();
      for (int i = 0; i < 4; i++) {
        digitalWrite(yellowLeds, HIGH);
        delay(delayShortTime);
        digitalWrite(yellowLeds, LOW);
        delay(delayShortTime);  
      }
    }
  } else if (counter == 3) {
    turnOffLeds();
    while (counter == 3) {
      digitalWrite(redLeds, HIGH);
      digitalWrite(blueLeds, HIGH);
      digitalWrite(yellowLeds, HIGH);
      IrReader();  
    }  
  } else if (counter == 4) {
    turnOffLeds();
    while (counter == 4) {
      IrReader();
      for (int i = 0; i < 3; i++) {
        digitalWrite(redLeds, HIGH);
        digitalWrite(blueLeds, HIGH);
        delay(delayTime);
        digitalWrite(redLeds, LOW);
        digitalWrite(blueLeds, LOW);
        digitalWrite(yellowLeds, HIGH);
        delay(delayTime);
        digitalWrite(yellowLeds, LOW);
        IrReader();
      }

      IrReader();
      for (int i = 0; i < 9; i++) {
        digitalWrite(redLeds, HIGH);
        delay(delayShortTime);
        digitalWrite(redLeds, LOW);
        digitalWrite(blueLeds, HIGH);
        delay(delayShortTime);
        digitalWrite(blueLeds, LOW);
        digitalWrite(yellowLeds, HIGH);
        delay(delayShortTime);
        digitalWrite(yellowLeds, LOW);
        delay(delayShortTime);
        IrReader();
      }
    }  
  }
}

void turnOffLeds() {
  digitalWrite(redLeds, LOW);
  digitalWrite(blueLeds, LOW);
  digitalWrite(yellowLeds, LOW);  
}

void IrReader() {
  if (IrReceiver.decode()) {
    Serial.print("Button: ");
    Serial.println(IrReceiver.decodedIRData.command);
    if (IrReceiver.decodedIRData.command == 22) {
      counter = 1;  
    } else if (IrReceiver.decodedIRData.command == 25) {
      counter = 2;
    } else if (IrReceiver.decodedIRData.command == 13) {
      counter = 3;     
    } else if (IrReceiver.decodedIRData.command == 12) {
      counter = 4;  
    }
  }
  IrReceiver.resume();
}
