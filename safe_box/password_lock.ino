#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

int buzzerPin = 2;
int servoPin = 10;

// Represent the number of rows and columns of the keypad
const byte ROWS = 4;
const byte COLS = 3;

// Array that represents the keys on the keypad
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3};

char password[1][4] = {'4', '8', '2', '3'};
char passwordTyped[1][4] = {' ', ' ', ' ', ' '};
char check = ' ';
int counter = 0;

// Create keypad object
Keypad myKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo myServo;
int initialPos = 90;
int finalPos = 30;


void setup() {
  myServo.attach(servoPin);
  lcd.begin();
  lcd.clear();
  lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
  counter = 0;
  check = ' ';
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Senha:");

  while(counter != 4) {
    passwordTyped[0][counter] = myKeypad.getKey();
    if (passwordTyped[0][counter]) {
      if (passwordTyped[0][counter] == '#' and counter > 0) {
        lcd.setCursor(counter - 1, 1);
        lcd.print(' ');
        counter -= 1;
      } else if (passwordTyped[0][counter] == '*' or (passwordTyped[0][counter] == '#' && counter == 0)) {
        if (counter > 0) {
          counter -= 1;
        }
      } else {
        lcd.setCursor(counter, 1);
        lcd.print("*");
        counter += 1;
      }
     }
  }

  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);

  for (int i = 0; i < 4; i++) {
    if (passwordTyped[0][i] == password[0][i]) {
       if ((passwordTyped[0][i] == password[0][i]) and i == 3) {
         lcd.print("Senha correta");
         lcd.setCursor(0, 1);
         lcd.print("Porta aberta");
         tone(buzzerPin, 500);
         delay(300);
         tone(buzzerPin, 1000);
         delay(300);
         noTone(buzzerPin);
         myServo.write(finalPos);
         
         lcd.clear();
         lcd.setCursor(0, 0);
         lcd.print("Porta aberta");
         delay(1000);
         
         while (check != '*') {
          check = myKeypad.getKey();
         }

         lcd.clear();
         lcd.setCursor(0, 0);
         lcd.print("Porta fechando");
         delay(1500);
         myServo.write(initialPos);  
       }
    } else {
      lcd.print("Senha errada");
      lcd.setCursor(0, 1);
      lcd.print("Porta fechada");
      for(int n = 0; n < 5; n++) {
        tone(buzzerPin, 400);
        delay(50);
        tone(buzzerPin, 800);
        delay(50);  
      }
      noTone(buzzerPin);
      delay(2000);
      counter = 0;
      break;  
    }  
  }  
}
