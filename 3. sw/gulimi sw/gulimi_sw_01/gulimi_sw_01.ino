#include <SoftwareSerial.h>

SoftwareSerial bluetoothSerial(12,13);
int Dir1Pin_A = 9;
int Dir2Pin_A = 10;
int SpeedPin_A = 11;
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
pinMode(Dir1Pin_A, OUTPUT);
pinMode(Dir2Pin_A, OUTPUT);
pinMode(SpeedPin_A, OUTPUT);
count = 0;
pre_count = 0;
attachInterrupt(digitalPinToInterrupt(interruptPin), CountServoRotation, FALLING);
Serial.begin(9600);
Serial.println("start");
pinMode(8,OUTPUT);
y = 0;
} 

void loop() {

if(bluetoothSerial.available()>0){

int data = bluetoothSerial.read();

char cmd = bluetoothSerial.read();
switch (cmd) {

if(data == 'f'){

  count = 0;
  Buzzcount = 0;
  Buzzoffrotate = -1;
  Buzzonrotate = 10;
  digitalWrite(8, HIGH);
  delay(100);
  digitalWrite(8, LOW);
  digitalWrite(Dir1Pin_A, HIGH);
  for(int i=0;i<85;i++) {
  digitalWrite(Dir2Pin_A, LOW);
  analogWrite(SpeedPin_A, i);
  delay(50);
  }
}else if(data =='1'){

 Buzzoffrotate = -3;
 Buzzonrotate = 20;
 digitalWrite(8, HIGH);
 delay(100);
 digitalWrite(8, LOW);
 digitalWrite(Dir1Pin_A, HIGH);
 for(int i=80;i<160;i++) {
 digitalWrite(Dir2Pin_A, LOW);
 analogWrite(SpeedPin_A, i);
 delay(50);
 }
}else if(data == 2){
 Buzzoffrotate = -6;
 Buzzonrotate = 40;
 digitalWrite(Dir1Pin_A, HIGH);
 for(int i=160;i<240;i++) {
 digitalWrite(Dir2Pin_A, LOW);
 analogWrite(SpeedPin_A, i);
 delay(50);
 }
}else if(data == 'b'){

  count = 0;
  Buzzcount = 0;
  Buzzoffrotate = -1;
  Buzzonrotate = 10;
  digitalWrite(8, HIGH);
  delay(100);
  digitalWrite(8, LOW);
  digitalWrite(Dir1Pin_A, LOW);
  for(int i=0;i<85;i++) {
  digitalWrite(Dir2Pin_A, HIGH);
  analogWrite(SpeedPin_A, i);
  delay(30);
  }
}else if(data == 3){
 Buzzoffrotate = -3;
 Buzzonrotate = 20;
 digitalWrite(Dir1Pin_A, LOW);
 for(int i=85;i<170;i++) {
 digitalWrite(Dir2Pin_A, HIGH);
 analogWrite(SpeedPin_A, i);
 delay(50); 
 }
}else if(data == 4){
 Buzzoffrotate = -6;
 Buzzonrotate = 40;
 digitalWrite(Dir1Pin_A, LOW);
 for(int i=170;i<255;i++) {
 digitalWrite(Dir2Pin_A, HIGH);
 analogWrite(SpeedPin_A,i);
 delay(50);
 }

if (data == 's'){

  count = 0;
  Buzzcount = 0;
  y == 2;
  digitalWrite(8, HIGH);
  delay(100);
  digitalWrite(8, LOW);
  digitalWrite(Dir1Pin_A,LOW);
  digitalWrite(Dir2Pin_A,LOW);
  analogWrite(SpeedPin_A,0);
}else if(data == 'b'){

  count = 0;
  Buzzcount = 0;
  Buzzoffrotate = -1;
  Buzzonrotate = 10;
  digitalWrite(8, HIGH);
  delay(100);
  digitalWrite(8, LOW);
  digitalWrite(Dir1Pin_A, LOW);
  for(int i=0;i<85;i++) {
  digitalWrite(Dir2Pin_A, HIGH);
  analogWrite(SpeedPin_A, i);
  delay(30);
  }
}else if(data == 3){
 Buzzoffrotate = -3;
 Buzzonrotate = 20;
 digitalWrite(Dir1Pin_A, LOW);
 for(int i=85;i<170;i++) {
 digitalWrite(Dir2Pin_A, HIGH);
 analogWrite(SpeedPin_A, i);
 delay(50); 
 }
}else if(data == 4){
 Buzzoffrotate = -6;
 Buzzonrotate = 40;
 digitalWrite(Dir1Pin_A, LOW);
 for(int i=170;i<255;i++) {
 digitalWrite(Dir2Pin_A, HIGH);
 analogWrite(SpeedPin_A,i);
 delay(50);
 }
}


  }  
 }
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
