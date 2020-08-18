#define pot A5
#define feedback A3
#define maxPos 560
#define minPos 425
#define PWMA 6
#define PWMB 5
#define enable 12
#define numReadings 10

int rawCurrPos = 0;
int currPos = 0;
int rawDest = 0;
int dest = 0;
int diff = 0;
int readings[numReadings];
int readIndex = 0;
int total = 0;


String loc = " ";

void setup() {
  Serial.begin(9600);
  pinMode(feedback, INPUT);
  pinMode(pot, INPUT);
  pinMode(enable, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  digitalWrite(enable, HIGH);
  //pinMode(10, OUTPUT); //Writing an output to send to gas pedal to release when brake is engaged
  //digitalWrite(10, LOW);

}

void loop() {
  //digitalWrite(10,LOW);

  int potValue = analogRead(pot);
  //Serial.println(potValue);
  potValue = map(potValue, 0, 1023, minPos, maxPos);
  int linPotValue = analogRead(feedback);



  if (linPotValue < potValue + 10 && linPotValue > potValue - 10) {
    loc = "In Range";
    //Serial.println(loc);
  }

  if (linPotValue > potValue + 10 || linPotValue < potValue - 10) {
    loc = "Not in Range";
    //Serial.println(loc);
  }



  while (linPotValue > potValue && loc == "Not in Range") {
    pushActuator();
    
    potValue = analogRead(pot);
    potValue = map(potValue, 0, 1023, minPos, maxPos);
    linPotValue = analogRead(feedback);

    Serial.println("Linear Pot Value = " + String(linPotValue) + ", " + String(potValue));
    if (linPotValue <= potValue) {
      stopActuator();
      loc = "In Range";
    }
  }


  while (linPotValue < potValue && loc == "Not in Range") {
    pullActuator();

    if (linPotValue > minPos) {
      digitalWrite(10, HIGH);
      Serial.println("BRAKING!!!");
    }

    potValue = analogRead(pot);
    potValue = map(potValue, 0, 1023, minPos, maxPos);
    linPotValue = analogRead(feedback);

    Serial.println("Linear Pot Value = " + String(linPotValue) + ", " + String(potValue));
    if (linPotValue >= potValue) {
      stopActuator();
      loc = "In Range";
    }

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
