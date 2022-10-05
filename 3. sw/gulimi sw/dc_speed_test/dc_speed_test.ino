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
  digitalWrite(Dir2Pin_A, LOW);
  break;

case '1':

   digitalWrite(Dir1Pin_A, HIGH);
  for(int i=0;i<80;i++) {
  digitalWrite(Dir2Pin_A, LOW);
  analogWrite(SpeedPin_A, i);
  }
  break;

case '2':
  digitalWrite(Dir1Pin_A, HIGH);
  for(int i=80;i<160;i++) {
  digitalWrite(Dir2Pin_A, LOW);
  analogWrite(SpeedPin_A, i);
  }
  break;

case '3':
digitalWrite(Dir1Pin_A, HIGH);
  for(int i=160;i<240;i++) {
  digitalWrite(Dir2Pin_A, LOW);
  analogWrite(SpeedPin_A, i);
  }
  break;

case 's':
    analogWrite(SpeedPin_A,0);

   }
}
