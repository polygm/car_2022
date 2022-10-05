#include <SoftwareSerial.h>

SoftwareSerial bluetoothSerial(12,13);
const int IN1 = 9;
const int IN2 = 10;
int x;
int small_x = 60; //모터 전류 최소값
int big_x = 255; //모터 전류 최대값
int speed_status; //속도 모드 상태값 
int power = 39 < power < 256;
const byte interruptPin = 2;
volatile int pre_count, count;
unsigned long skip_milli_time = 100; 
unsigned long cur_time = 0;
unsigned long pre_time = 0;
int Buzzcount = 0; //부저 울렸을 때 당시의 모터가 돌아간 횟수
int Buzzoffrotate = -3; //모터가 몇회 회전했을 때 부저를 꺼야하는지 정해주는 변수
int Buzzonrotate = 20; //모터가 몇회 회전했을 때 부저를 켜야하는지 정해주는 변수
int motor_status; //전후진상태값

void setup() {
bluetoothSerial.begin(9600);
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
count = 0;
pre_count = 0;
motor_status = 0;
attachInterrupt(digitalPinToInterrupt(interruptPin), CountServoRotation, FALLING);
Serial.begin(9600);
Serial.println("start");
pinMode(8,OUTPUT);
}

void loop() {

char cmd = bluetoothSerial.read();
switch (cmd) {

case 'f':

  count = 0;
  Buzzcount = 0;
  motor_status = 1;
  digitalWrite(8, HIGH);
  delay(100);
  digitalWrite(8, LOW);
  motor();
  break;

case 's':

  count = 0;
  Buzzcount = 0;
  motor_status = 0;
  digitalWrite(8, HIGH);
  delay(100);
  digitalWrite(8, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  break;

case 'b':

  count = 0;
  Buzzcount = 0;
  motor_status = 2;
  digitalWrite(8, HIGH);
  delay(100);
  digitalWrite(8, LOW);
  motor();
  break;

case '1':

 digitalWrite(8, HIGH);
 delay(100);
 digitalWrite(8, LOW);
 
 if(speed_status==0){
 Buzzoffrotate = -1;
 Buzzonrotate = 4;
 }
 else if(speed_status==1){
 Buzzoffrotate = -1;
 Buzzonrotate = 6;
 }
 else if(speed_status==2){
 Buzzoffrotate = -1;
 Buzzonrotate = 8;
 }
 
 break;

case '2':

 digitalWrite(8, HIGH);
 delay(100);
 digitalWrite(8, LOW);

  if(speed_status==0){
 Buzzoffrotate = -3;
 Buzzonrotate = 10;
 }
 else if(speed_status==1){
 Buzzoffrotate = -3;
 Buzzonrotate = 12;
 }
 else if(speed_status==2){
 Buzzoffrotate = -3;
 Buzzonrotate = 14;
 }
 
 break;

case '3':

 digitalWrite(8, HIGH);
 delay(100);
 digitalWrite(8, LOW);
   if(speed_status==0){
 Buzzoffrotate = -5;
 Buzzonrotate = 16;
 }
 else if(speed_status==1){
 Buzzoffrotate = -5;
 Buzzonrotate = 18;
 }
 else if(speed_status==2){
 Buzzoffrotate = -5;
 Buzzonrotate = 20;
 }
 break;

 

case '4':

 big_x = 100;
 speed_status = 0;
 digitalWrite(8, HIGH);
 delay(100);
 digitalWrite(8, LOW);
 motor();
 break;

case '5':

 big_x = 160;
 speed_status = 1;
 digitalWrite(8, HIGH);
 delay(100);
 digitalWrite(8, LOW);
 motor();
 break;

case '6':

 big_x = 255;
 speed_status = 2;
 digitalWrite(8, HIGH);
 delay(100);
 digitalWrite(8, LOW);
 motor();
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

void motor() {
  if( motor_status == 1 ){
    digitalWrite(IN1, LOW);
  for(x=small_x; x<big_x; x++) {
  analogWrite(IN2,x);
  delay(10);
  }
}

  else if( motor_status == 2 ){
    digitalWrite(IN2, LOW);
  for(x=small_x; x<big_x; x++) {
  analogWrite(IN1,x);
  delay(10);
}
}
 else {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  
 }
}
