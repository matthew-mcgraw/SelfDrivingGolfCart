#include <AccelStepper.h>

const int sPR = 200; //sPR - steps per revolution, change to fit the number of steps per revolution for your motor

//define analog inputs for hall effect sensors below
int RHE = A0;
int FHE = A1;

//define inputs for user defined forward-reverse descriptions 
int F_button = 5;
int R_button = 6;

//initialize the stepper library on pins 8 through 11
Stepper stepper(sPR, 8,9,10,11)

//
void setup() {
  stepper.setSpeed(60);
  Serial.begin(9600);

  // place initializing sequence below, 
}

void loop() {

  

  int movF = digitalRead(F_button);
  int movR = digitalRead(R_button);
  

}

String currPos() {
  
  
}
