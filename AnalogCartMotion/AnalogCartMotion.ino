int ForwardA = 8;
int ForwardB = 9;

int ReverseA = 10;
int ReverseB = 11;

void setup() {
  Serial.begin(9600);
  pinMode(ForwardA, OUTPUT);
  pinMode(ForwardB, OUTPUT);

  pinMode(ReverseA, OUTPUT);
  pinMode(ReverseB, OUTPUT);

}

void loop() {
  analogWrite(ForwardA, 51);
  analogWrite(ForwardB, 51);
  Serial.println(1);
  delay(1000);

  analogWrite(ForwardA, 102);
  analogWrite(ForwardB, 102);
  Serial.println(2);
  delay(1000);

  analogWrite(ForwardA, 153);
  analogWrite(ForwardB, 153);
  Serial.println(3);
  delay(1000);

  analogWrite(ForwardA, 204);
  analogWrite(ForwardB, 204);
  Serial.println(4);
  delay(1000);

  analogWrite(ForwardA, 255);
  analogWrite(ForwardB, 255);
  Serial.println(5);
  delay(1000);
  
  
}

