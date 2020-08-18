#include <AccelStepper.h>

AccelStepper stepper(1, 9, 8);
int pos = 225;

void setup() {
  Serial.begin(9600);
  stepper.setMaxSpeed(3000);
  stepper.setAcceleration(1000);
  
}

void loop() {
  if(stepper.distanceToGo() == 0)
  {
    Serial.println(stepper.distanceToGo());
    delay(100);
    pos = -pos;
    stepper.moveTo(pos);
  }
  Serial.println(stepper.distanceToGo());
  stepper.run();
}
