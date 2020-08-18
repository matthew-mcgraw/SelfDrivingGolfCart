#define pot A5
#define feedback A4
#define maxPos 470
#define minPos 650
#define PWMA 11
#define PWMB 3
#define enable 8
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
  
}

void loop() {

  int linPotValue = analogRead(feedback);

  Serial.println("Step 1: " + String(linPotValue));
  while (linPotValue > 500) {
    pullActuator();
    linPotValue = analogRead(feedback);
    Serial.println(String(linPotValue));
  }
  delay(1000);
  Serial.println("Step 2: " + String(linPotValue));

  while(linPotValue < 700) {
    pushActuator();
    linPotValue = analogRead(feedback);
    Serial.println(String(linPotValue));
  }
  delay(1000);

  Serial.println("Step 3: " + String(linPotValue));

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
