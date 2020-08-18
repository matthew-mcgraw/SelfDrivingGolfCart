#define pot A2
#define feedback A4
#define maxPos 750
#define minPos 600
#define PWMA 9
#define PWMB 3
#define enable 8


String loc = " ";

void setup() {
  Serial.begin(9600);
  pinMode(feedback, INPUT);
  pinMode(pot, INPUT);
  pinMode(enable, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  digitalWrite(enable, HIGH);
  
}

void loop() {

  
  int potValue = analogRead(pot);
  potValue = map(potValue, 0, 1023, minPos, maxPos);
  int linPotValue = analogRead(feedback);
  delay(50);

  loc = gRange(linPotValue, potValue);



  if (linPotValue <= potValue + 10 && linPotValue >= potValue - 10) {
    loc = "In Range";
    //Serial.println(loc);
  }
  
  if (linPotValue > potValue + 10 || linPotValue < potValue - 10) {
    loc = "Not in Range";
    //Serial.println(loc);
  }



  while (linPotValue > potValue && loc == "Not in Range") {
    pullActuator();

    potValue = analogRead(pot);
    potValue = map(potValue, 0, 1023, minPos, maxPos);
    linPotValue = analogRead(feedback);

    Serial.println(potValue);

    //Serial.println("Linear Pot Value = " + String(linPotValue) + ", " + String(potValue));
    if (linPotValue <= potValue) {
      stopActuator();
      loc = "In Range";
    }
    delay(50);
  }


  while (linPotValue < potValue && loc == "Not in Range") {
    pushActuator();

    potValue = analogRead(pot);
    potValue = map(potValue, 0, 1023, minPos, maxPos);
    linPotValue = analogRead(feedback);

    Serial.println(potValue);

    //Serial.println("Linear Pot Value = " + String(linPotValue) + ", " + String(potValue));
    if (linPotValue >= potValue) {
      stopActuator();
      loc = "In Range";
    }
    delay(50);

  }
}

void stopActuator() {
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
}

void pushActuator() {
  analogWrite(PWMB, 255);
  analogWrite(PWMA, 0);
}

void pullActuator() {
  analogWrite(PWMB, 0);
  analogWrite(PWMA, 255);
}


String gRange(int gLinVal, int gPotVal) {
  String gLoc = " ";
  if(gLinVal <= gPotVal + 20 && gLinVal >= gPotVal - 20) {
    gLoc = "In Range";
    //Serial.println(loc)
  }

  if(gLinVal > gPotVal + 20 || gLinVal < gPotVal - 20) {
    gLoc = "Not in Range";
    //Serial.println(loc);
  }

  return gLoc;  
}
