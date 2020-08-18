#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);



#define potVal A1
#define linVal A0

int ena = 11;
int in1 = 6;
int in2 = 7;
int pwmOutput = 51;



void setup() {
  Serial.begin(9600);
  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

  AFMS.begin();

  // Set initial rotation direction
  

}

void loop() {
  digitalWrite(in2, LOW);
  digitalWrite(in1, HIGH);
  digitalWrite(ena, HIGH);

  myMotor->setSpeed(255);
  myMotor->run(FORWARD);
  delay(10000);

  myMotor->run(BACKWARD);
  delay(10000);



  /*
  int potValue = analogRead(potVal);
  int linValue = analogRead(linVal);

  Serial.println("Pot Value = " + potValue);
  Serial.println("Lin Value = " + linValue);

  while (linValue < potValue) {
    analogWrite(ena, pwmOutput);
    digitalWrite(in2, LOW);
    digitalWrite(in1, HIGH);

    potValue = analogRead(potVal);
    linValue = analogRead(linVal);
  }
*/
  

}
