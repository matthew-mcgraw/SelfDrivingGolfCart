#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *Actuator = AFMS.getMotor(1); // getting the motor from the motor shield


#define potPin A1
#define linPotPin A0
#define maxPos 150
#define minPos 975

String loc = " ";

void setup() {
  Serial.begin(9600);
  AFMS.begin();
  Actuator->setSpeed(255); // Setting the motor speed in the linear actuator

}

void loop() {
  int potValue = analogRead(potPin);
  potValue = map(potValue, 0, 1023, 150, 975);
  int linPotValue = analogRead(linPotPin);
  Serial.println(String(potValue) + ", " + String(linPotValue));
  delay(200);

  if (linPotValue < potValue + 50 && linPotValue > potValue - 50) {
    loc = "In Range";
    Serial.println(loc);
  }
  
  if (linPotValue > potValue + 50 || linPotValue < potValue - 50) {
    loc = "Not in Range";
    Serial.println(loc);
  }



  while (linPotValue > potValue && loc == "Not in Range") {
    Actuator->run(FORWARD);

    potValue = analogRead(potPin);
    potValue = map(potValue, 0, 1023, 150, 975);
    linPotValue = analogRead(linPotPin);

    Serial.println("Linear Pot Value = " + String(linPotValue) + ", " + String(potValue));
    if (linPotValue <= potValue) {
      Actuator->run(RELEASE);
      loc = "In Range";
    }
    delay(200);
  }


  while (linPotValue < potValue && loc == "Not in Range") {
    Actuator->run(BACKWARD);

    potValue = analogRead(potPin);
    potValue = map(potValue, 0, 1023, 150, 975);
    linPotValue = analogRead(linPotPin);

    Serial.println("Linear Pot Value = " + String(linPotValue) + ", " + String(potValue));
    if (linPotValue >= potValue) {
      Actuator->run(RELEASE);
      loc = "In Range";
    }
    delay(200);

  }


}
