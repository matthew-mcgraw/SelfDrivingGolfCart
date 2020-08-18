# include <AccelStepper.h>

AccelStepper steerStep(1, 9, 8);

int initPos = 0; // Assuming that the wheels are straight in beginning
int upperB = 500;
int lowerB = -500;
int potPin = A3;

void setup() {
  Serial.begin(9600);
  steerStep.setMaxSpeed(200); //sets maximum speed the stepper can reach
  steerStep.setAcceleration(200); // sets stepper acceleration, equal to max speed so speed is constant
  Serial.println("Current Position is: " + String(steerStep.currentPosition()));
  delay(2000);
}


void loop() {
  int potValue = analogRead(potPin);
  //Might not need direction function from before
  int currPos = steerStep.currentPosition();

  int stepLoc = map(potValue, 0, 1000, lowerB, upperB);
  //Serial.println(String(currPos) + "   " + String(stepLoc));
  //Serial.println("Current Position: " + String(currPos));
  //Serial.println("Stepper Position: " + String(stepLoc));
  //Serial.println(abs(currPos-stepLoc));
  //delay(1000);
  if ( abs(currPos-stepLoc) < 50) {
    //steerStep.stop();
    //Serial.println("AT DESIRED POSITION");
    steerStep.setSpeed(0);
  }
  else {
    steerStep.moveTo(stepLoc);
    steerStep.run();
  }
}

