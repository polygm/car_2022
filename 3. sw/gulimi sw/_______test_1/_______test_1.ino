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
int Buzzcount = 0; //부저 울렸을 때 당시의 모터가 돌아간 횟수
int Buzzoffrotate = -3; //모터가 몇회 회전했을 때 부저를 꺼야하는지 정해주는 변수
int Buzzonrotate = 20; //모터가 몇회 회전했을 때 부저를 켜야하는지 정해주는 변수


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

  count = 0;
  Buzzcount = 0;
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

  count = 0;
  Buzzcount = 0;
  y == 2;
  digitalWrite(8, HIGH);
  delay(100);
  digitalWrite(8, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  break;

case 'b':

  count = 0;
  Buzzcount = 0;
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

case '1':

 Buzzoffrotate = -1;
 Buzzonrotate = 10;
 digitalWrite(8, HIGH);
 delay(100);
 digitalWrite(8, LOW);
 break;

case '2':

 Buzzoffrotate = -3;
 Buzzonrotate = 20;
 digitalWrite(8, HIGH);
 delay(100);
 digitalWrite(8, LOW);
break;

case '3':

 Buzzoffrotate = -6;
 Buzzonrotate = 40;
 digitalWrite(8, HIGH);
 delay(100);
 digitalWrite(8, LOW);
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
      Serial.println(Buzzcount);
      pre_count = count;
  }
  //만약 이전 카운트와 현재 카운트가 다를 경우 명령 실행
  
  if (count % Buzzonrotate == 0){
  Serial.println("Buzz");
  Buzz();
  Buzzcount = count;} 
  if (Buzzcount - count < Buzzoffrotate){
    Buzzoff();
    Buzzcount = 0;
  }
}

void Buzz() {
  digitalWrite(8, HIGH);
}

void Buzzoff() {
    digitalWrite(8, LOW);
}
