#include <AccelStepper.h>
/*
 * The stepper motor is not able to detect its own position,
 * this will need to be fixed if we want the motor to be able 
 * to start from any position.
 * 
 * 
 */

AccelStepper steerStep(1, 9, 8);
int pos = 0; // This is assuming that the wheels are straight in the beginning
int upperBound = 500;
int lowerBound = -500;

void setup() {
  Serial.begin(9600);
  steerStep.setMaxSpeed(200); //Sets the maximum speed.
  steerStep.setAcceleration(100); // Sets the acceleration, (steps/sec)
    
}

void loop() {

  int currPos = 0;
  
/* This code gave speed issues for some reason, kept moving the same slow speed
  if (currPos == 0) {
    //delay(500);
    steerStep.moveTo(upperBound);
    
  }

  currPos = steerStep.currentPosition();
  if (currPos == upperBound) {
    //delay(500);
    steerStep.moveTo(lowerBound);
    
  }
  currPos = steerStep.currentPosition();
  if (currPos == lowerBound) {
    //delay(500);
    steerStep.moveTo(upperBound);
    
  }*/
  
  if(steerStep.currentPosition() == 0 || steerStep.currentPosition() == lowerBound) {
    steerStep.moveTo(upperBound);
  }

  if(steerStep.currentPosition() == upperBound) {
    steerStep.moveTo(lowerBound);
  }
  
  steerStep.run();
  
}


