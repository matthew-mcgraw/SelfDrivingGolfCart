#define bPot A5
#define bFeed A3
#define bMaxPos 560
#define bMinPos 450
#define bPWMA 6 //motorshield pwm pins for brake
#define bPWMB 5
#define bEnable 12

// All pins & values for the gas actuator
#define gPot A2
#define gFeed A4
#define gMaxPos 300
#define gMinPos 900 
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
  int bLinVal = analogRead(bFeed);
  bPotVal = map(bPotVal, 0, 1023, bMinPos, bMaxPos);
  bLoc = bRange(bLinVal, bPotVal);


  if (bLinVal < bPotVal + 5 && bLinVal > bPotVal - 5) {
    bLoc = "In Range";
  }

  if (bLinVal > bPotVal + 5 || bLinVal < bPotVal - 5) {
    bLoc = "Not in Range";
  }

  while (bLinVal > bPotVal && bLoc == "Not in Range") {
    pushBrake();

    bPotVal = analogRead(bPot);
    bPotVal = map(bPotVal, 0, 1023, bMinPos, bMaxPos);
    bLinVal = analogRead(bFeed);

    if (bLinVal <= bPotVal) {
      stopBrake();
      bLoc = "In Range";
    }
  }

  while (bLinVal < bPotVal && bLoc == "Not in Range") {
    pullBrake();

    bPotVal = analogRead(bPot);
    bPotVal = map(bPotVal, 0, 1023, bMinPos, bMaxPos);
    bLinVal = analogRead(bFeed);

    if (bLinVal >= bPotVal) {
      stopBrake();
      bLoc = "In Range";
    }
  }


  int gPotVal = analogRead(gPot);
  int gLinVal = analogRead(gFeed);
  gPotVal = map(gPotVal, 0, 1023, gMinPos, gMaxPos);
  gLoc = gRange(gLinVal, gPotVal);


  if (gLinVal <= gPotVal + 10 && gLinVal >= gPotVal - 10) {
    gLoc = "In Range";
  }

  if (gLinVal > gPotVal + 10 || gLinVal < gPotVal - 10) {
    gLoc = "Not in Range";
  }

  //Serial.println(bPotVal);

  //Serial.println(gLinVal);

  if (bPotVal <= bMinPos + 10) {


    while (gLinVal > gPotVal && gLoc == "Not in Range") {
      pullGas();

      gPotVal = analogRead(gPot);
      gPotVal = map(gPotVal, 0, 1023, gMinPos, gMaxPos);
      gLinVal = analogRead(gFeed);

      if (gLinVal <= gPotVal) {
        stopGas();
        gLoc = "In Range";
      }
    }


    while (gLinVal < gPotVal && gLoc == "Not in Range") {
      pushGas();

      gPotVal = analogRead(gPot);
      gPotVal = map(gPotVal, 0, 1023, gMinPos, gMaxPos);
      gLinVal = analogRead(gFeed);

      if (gLinVal >= gPotVal) {
        stopGas();
        gLoc = "In Range";
      }
    }
  }

  else {
    if(gLinVal > gMaxPos) {
      pullGas();
    }
    else{
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
  if (bLinVal <= bPotVal + 10 && bLinVal >= bPotVal - 10) {
    bLoc = "In Range";
  }

  if (bLinVal > bPotVal + 10 || bLinVal < bPotVal - 10) {
    bLoc = "Not in Range";
  }

  return bLoc;
}

String gRange(int gLinVal, int gPotVal) {
  String gLoc = " ";
  if (gLinVal <= gPotVal + 10 && gLinVal >= gPotVal - 10) {
    gLoc = "In Range";
  }

  if (gLinVal > gPotVal + 10 || gLinVal < gPotVal - 10) {
    gLoc = "Not in Range";
  }

  return gLoc;
}
