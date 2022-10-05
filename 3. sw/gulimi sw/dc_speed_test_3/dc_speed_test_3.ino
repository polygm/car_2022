#include <SoftwareSerial.h>

SoftwareSerial bluetoothSerial(12,13);
int Dir1Pin_A = 9;
int Dir2Pin_A = 10;
int SpeedPin_A = 11;

void setup() {
bluetoothSerial.begin(9600);
pinMode(Dir1Pin_A, OUTPUT);
pinMode(Dir2Pin_A, OUTPUT);
pinMode(SpeedPin_A, OUTPUT);
}

void loop() {

char cmd = bluetoothSerial.read();
switch (cmd) {

case 'f':

  digitalWrite(Dir1Pin_A, HIGH);
  for(int i=0;i<85;i++) {
  digitalWrite(Dir2Pin_A, LOW);
  analogWrite(SpeedPin_A, i);
  delay(50);
  }
  break;

case '1':

  digitalWrite(Dir1Pin_A, HIGH);
  for(int i=85;i<170;i++) {
  digitalWrite(Dir2Pin_A, LOW);
  analogWrite(SpeedPin_A, i);
  delay(50);
  }
  break;

case '2':
  digitalWrite(Dir1Pin_A, HIGH);
  for(int i=170;i<255;i++) {
  digitalWrite(Dir2Pin_A, LOW);
  analogWrite(SpeedPin_A, i);
  delay(50);
  }
  break;

case 's':
    analogWrite(SpeedPin_A,0);

   }
}
