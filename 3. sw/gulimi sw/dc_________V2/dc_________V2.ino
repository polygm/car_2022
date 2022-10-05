int Dir1Pin_A = 9;
int Dir2Pin_A = 10;
int SpeedPin_A = 11;

void setup() {
  pinMode(Dir1Pin_A, OUTPUT);
  pinMode(Dir2Pin_A, OUTPUT);
  pinMode(SpeedPin_A, OUTPUT);

  // put your setup code here, to run once:

}

void loop() {
  digitalWrite(Dir1Pin_A, HIGH);
  for(int i=0;i<255;i++) {
  digitalWrite(Dir2Pin_A, LOW);
  analogWrite(SpeedPin_A, i);
  delay(50);
 }

  digitalWrite(Dir1Pin_A, LOW);
  for(int i=255;i>0;i--) {
  digitalWrite(Dir2Pin_A, HIGH);
  analogWrite(SpeedPin_A, i);
  delay(50);
 }

 digitalWrite(Dir1Pin_A, LOW);
 for(int i=0;i<255;i++) {
 digitalWrite(Dir2Pin_A, HIGH);
 analogWrite(SpeedPin_A, i);
 delay(50);
 }

  digitalWrite(Dir1Pin_A, HIGH);
  for(int i=255;i>0;i--) {
  digitalWrite(Dir2Pin_A, LOW);
  analogWrite(SpeedPin_A, i);
  delay(50);
 }

}
