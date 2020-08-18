
int ForwardA = 8;
int ForwardB = 8;

int ReverseA = 8;
int ReverseB = 8;

void setup() {
  Serial.println(9600);
  pinMode(ForwardA, OUTPUT);
  pinMode(ForwardB, OUTPUT);

  pinMode(ReverseA, OUTPUT);
  pinMode(ReverseB, OUTPUT);

}

void loop() {

  // Forward Motion
  digitalWrite(ForwardA, HIGH);
  digitalWrite(ForwardB, HIGH);
  Serial.println(1);
  delay(3000);

  digitalWrite(ForwardA, LOW);
  digitalWrite(ForwardB, LOW);
  Serial.println(2);
  delay(3000);

  // Reverse Motion

  digitalWrite(ReverseA, HIGH);
  digitalWrite(ReverseB, HIGH);
  Serial.println(3);
  delay(3000);

  digitalWrite(ReverseA, LOW);
  digitalWrite(ReverseB, LOW);
  Serial.println(4);
  delay(3000);
  

}
