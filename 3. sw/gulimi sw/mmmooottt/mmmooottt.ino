#include <SoftwareSerial.h>

SoftwareSerial bluetoothSerial(12,13);
const int IN1 = 9;
const int IN2 = 10;
int x;
int y;
const byte interruptPin = 2;
volatile int pre_count, count;
unsigned long skip_milli_time = 100; 
unsigned long cur_time = 0;
unsigned long pre_time = 0;

void setup() {
bluetoothSerial.begin(9600);
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
count = 0;
pre_count = 0;
attachInterrupt(digitalPinToInterrupt(interruptPin), CountServoRotation, FALLING);
Serial.begin(9600);
Serial.println("start");
pinMode(8,OUTPUT);
y = 0;
} 

void loop() {


char cmd = bluetoothSerial.read();
switch (cmd) {

case 'f':
  
  y == 1;
  digitalWrite(8, HIGH);
  delay(100);
  digitalWrite(8, LOW);
  digitalWrite(IN1, LOW);
  for(x=0;x<255;x++) {
  analogWrite(IN2,x);
  delay(10);
  }
  break;

case 's':

  y == 2;
  digitalWrite(8, HIGH);
  delay(100);
  digitalWrite(8, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  break;

case 'b':

  y == 3;
  digitalWrite(8, HIGH);
  delay(100);
  digitalWrite(8, LOW);
  digitalWrite(IN2, LOW);
  for(x=0;x<255;x++) {
  analogWrite(IN1,x);
  delay(10);
  }
  break;

}  
}

void CountServoRotation() {
  cur_time = millis();
  if ( (cur_time - pre_time) > skip_milli_time ) {
    count++;
  }
  pre_time = millis();
  if (pre_count != count) {
      Serial.print("Rotation #:\t");
      Serial.println(count);
      pre_count = count;
  }
  if (count % 10 == 0){
  Serial.println("Buzz");
  Buzz();} 
}

void Buzz() {
  digitalWrite(8, HIGH);
  delay(2000);
  digitalWrite(8, LOW);
}
