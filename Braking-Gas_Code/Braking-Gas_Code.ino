// All pins & values for the brake actuator 
#define bPot A5
#define bFeed A3
#define bMaxPos 560
#define bMinPos 425
#define bPWMA 6 //motorshield pwm pins for brake
#define bPWMB 5 
#define bEnable 12

// All pins & values for the gas actuator
#define gPot A2
#define gFeed A4
#define gMaxPos 750
#define gMinPos 600
#define gPWMA 9
#define gPWMB 3
#define gEnable 8


String bLoc = " ";
String gLoc = " ";

bool braking;

void setup() {
  Serial.begin(9600);
  
  //initializing brake pins
  pinMode(bPot, INPUT);
  pinMode(bFeed, INPUT);
  pinMode(bPWMA, OUTPUT);
  pinMode(bPWMB, OUTPUT);
  pinMode(bEnable, OUTPUT);
  digitalWrite(bEnable, HIGH);

  //initializing gas pins
  pinMode(gPot, INPUT);
  pinMode(gFeed, INPUT);
  pinMode(gPWMA, OUTPUT);
  pinMode(gPWMB, OUTPUT);
  pinMode(gEnable, OUTPUT);
  digitalWrite(gEnable, HIGH);

}

void loop() {

  int bPotVal = analogRead(bPot);
  int gPotVal = analogRead(gPot);
  int bLinVal = analogRead(bFeed);
  int gLinVal = analogRead(gFeed);

  //Serial.println(bLinVal);

  bPotVal = map(bPotVal, 0, 1023, bMinPos, bMaxPos);
  gPotVal = map(gPotVal, 0, 1023, gMinPos, gMaxPos);

  bLoc = bRange(bLinVal, bPotVal);
  gLoc = gRange(gLinVal, gPotVal);  

  braking = isBraking(bPotVal, gLinVal);  
  Serial.println(braking);
  
  //Serial.println("Running");

  while(bLoc == "Not in Range") {
    if(bLinVal > bPotVal) {
      pushBrake();
    }
    if(bLinVal < bPotVal) {
      pullBrake();
    }

    //isBraking(bPotVal, gLinVal);

    bPotVal = analogRead(bPot);
    bPotVal = map(bPotVal, 0, 1023, bMinPos, bMaxPos);
    bLinVal = analogRead(bFeed);

    //Serial.println("Stuck1");

    bLoc = bRange(bLinVal, bPotVal);
    if(bLoc == "In Range") {
      stopBrake();
    }     
    //Serial.println("Stuck1");   
  } 

  
  bLoc = bRange(bLinVal, bPotVal);
  gLoc = gRange(gLinVal, gPotVal); 



  while(gLoc == "Not in Range" && braking == false) {
    if(gLinVal > gPotVal) {
      pullGas();
    }
    if(gLinVal < gPotVal) {
      pushGas();
    }

    gPotVal = analogRead(gPot);
    gPotVal = map(gPotVal, 0, 1023, gMinPos, gMaxPos);
    gLinVal = analogRead(gFeed);

    bPotVal = analogRead(bPot);
    bPotVal = map(bPotVal, 0, 1023, bMinPos, bMaxPos);

    gLoc = gRange(gLinVal, gPotVal);
    if(gLoc == "In Range") {
      stopGas();
    }    
  }

  
}

void stopBrake() {
  analogWrite(bPWMA, 0);
  analogWrite(bPWMB, 0);
}

void pushBrake() {
  analogWrite(bPWMB, 255);
  analogWrite(bPWMA, 0);
}

void pullBrake() {
  analogWrite(bPWMB, 0);
  analogWrite(bPWMA, 255);
}

void stopGas() {
  analogWrite(gPWMA, 0);
  analogWrite(gPWMB, 0);
}

void pushGas() {
  analogWrite(gPWMB, 255);
  analogWrite(gPWMA, 0);
}

void pullGas() {
  analogWrite(gPWMB, 0);
  analogWrite(gPWMA, 255);
}

String bRange(int bLinVal, int bPotVal) {
  String bLoc = " ";
  if(bLinVal <= bPotVal + 10 && bLinVal >= bPotVal - 10) {
    bLoc = "In Range";
  }

  if(bLinVal > bPotVal + 10 || bLinVal < bPotVal - 10) {
    bLoc = "Not in Range";
  }

  return bLoc;
}

String gRange(int gLinVal, int gPotVal) {
  String gLoc = " ";
  if(gLinVal <= gPotVal + 10 && gLinVal >= gPotVal - 10) {
    gLoc = "In Range";
  }

  if(gLinVal > gPotVal + 10 || gLinVal < gPotVal - 10) {
    gLoc = "Not in Range";
  }

  return gLoc;  
}

bool isBraking(int bPotVal, int gLinVal) {
  bPotVal = analogRead(bPot);
  bPotVal = map(bPotVal, 0, 1023, bMinPos, bMaxPos);
  if (bPotVal > bMinPos + 15) {
    braking = true; 
    Serial.println("here");
  }
  if (bPotVal <= bMinPos+15) {
    braking = false;
  }

  Serial.println(braking);

  gLinVal = analogRead(gFeed);

  while(braking = true && gLinVal > gMinPos+10) {
    pullGas();    
    gLinVal = analogRead(gFeed);
  }
  return braking;  
}
