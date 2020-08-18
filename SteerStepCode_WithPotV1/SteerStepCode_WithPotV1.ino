/*
 * The stepper motor is not able to detect its own position,
 * this will need to be fixed if we want the motor to be able 
 * to start from any position.
 * 
 * THIS CODE WORKS WELL FOR OUR APPLICATION!
 * 
 * 
 */

#include <AccelStepper.h>

AccelStepper steerStep(1,9,8);
int initPos = 0; // Assuming that the wheels are straight in beginning
int upperB = 500;
int lowerB = -500;
int potPin = A3;

void setup() {
  Serial.begin(9600);
  steerStep.setMaxSpeed(150); //sets the maximum speed the stepper can reach
  steerStep.setAcceleration(150); //sets the stepper acceleration in steps/sec
  Serial.println("Current Position is: " + String(steerStep.currentPosition()));
  delay(2500);
}

void loop() {
  int potValue = analogRead(potPin);
  String dir = potDirection(potValue); // calling the function to find which way to steer
  //Serial.println(dir); // printing direction to steer

  // ** DO NOT PRINT WHEN MOVING STEPPER, WILL SLOW DOWN MOTOR DRASTICALLY **

  if(dir == "RIGHT") {
    steerStep.moveTo(upperB);
    //Serial.println("TURNING RIGHT"); 
    
  }

  if(dir == "LEFT") {
    steerStep.moveTo(lowerB); 
    //Serial.println("TURNING LEFT");
  }

  if(dir == "NOT TURNING") {
    steerStep.moveTo(initPos);
    //Serial.println(dir);
  }

  steerStep.run();
  
}


// Function that associates the location of the potentiometer with
// which way to steer, can create as different file eventually


String potDirection(int x) {
  String dir;
  if(x >= 0 && x <= 400) {
    dir = "LEFT";
  }
  else if(x <=1023 && x >= 624) {
    dir = "RIGHT";
  }
  else {
    dir = "NOT TURNING";
  }
  return dir;
  
}



