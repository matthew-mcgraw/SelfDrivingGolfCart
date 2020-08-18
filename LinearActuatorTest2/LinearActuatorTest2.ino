#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *Actuator = AFMS.getMotor(1);


#define potPin A1
#define linPotPin A0
#define maxPos 150
#define minPos 975

int rotDirection = 1; // setting identification variable for FORWARD = 1 & BACKWARD = 0
void setup() {
  Serial.begin(9600);
  AFMS.begin();
  Actuator->setSpeed(255);
}

void loop() {
  int potValue = analogRead(potPin);
  int linPotValue = analogRead(linPotPin);
  //Serial.println(potValue);


  
  Serial.println("THIS IS A TEST");
  Serial.println(rotDirection);
  delay(1500);

  while (linPotValue > maxPos) {
    Actuator->run(FORWARD);
    linPotValue = analogRead(linPotPin);
    Serial.println("Linear Pot Value = " + String(linPotValue));
    if (linPotValue <= maxPos) {
      rotDirection = 0;
    }
  }

  Serial.println(rotDirection);
  delay(1500);


  while (linPotValue < minPos) {
    Actuator->run(BACKWARD);
    linPotValue = analogRead(linPotPin);
    Serial.println("Linear Pot Value = " + String(linPotValue));
    if (linPotValue >= minPos) {
      rotDirection = 1;
    }
  }


}



