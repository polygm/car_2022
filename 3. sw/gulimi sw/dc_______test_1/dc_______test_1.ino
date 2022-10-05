#include <SoftwareSerial.h>

SoftwareSerial SWserial(4,3);
int Dir1Pin_A = 9;
int Dir2Pin_A = 10;
int SpeedPin_A = 11;

void setup() {
  SWserial.begin(9600);
  
}

void loop() {
  if(SWserial.available()>0){

    int data = SWserial.read();

    if(data == 'f'){
       digitalWrite(Dir1Pin_A, HIGH);
  for(int i=0;i<80;i++) {
  digitalWrite(Dir2Pin_A, LOW);
  analogWrite(SpeedPin_A, i);
  delay(50);
    }
   }else if(data == 'b'){
    {
  digitalWrite(Dir1Pin_A, HIGH);
  for(int i=80;i<160;i++) {
  digitalWrite(Dir2Pin_A, LOW);
  analogWrite(SpeedPin_A, i);
  delay(50);
    }    
   }
 }else if(data == 'c'){
  {
  digitalWrite(Dir1Pin_A, HIGH);
  for(int i=160;i<240;i++) {
  digitalWrite(Dir2Pin_A, LOW);
  analogWrite(SpeedPin_A, i);
  delay(50);
   }
 }
}else if (data == 's'){
  analogWrite(SpeedPin_A,0);
}

  }
}
