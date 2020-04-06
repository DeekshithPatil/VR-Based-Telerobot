#include "RF24.h"
#include<Servo.h>
RF24 myRadio (7, 8);
byte addresses[][6] = {"1Node"};

const int l1=4;
const int l2=5;
const int r1=2;
const int r2=3;


Servo v,h;

struct Pack {
  int joy_x;
  int joy_y;
  int gyro_x;
  int gyro_y;
  
} packet;

void setup() {
  Serial.begin(115200);
  Serial.println(F("RF24/Simple Receive data Test"));

  myRadio.begin();
  myRadio.setChannel(108);
  myRadio.setPALevel(RF24_PA_MIN);
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();

  
v.attach(10);
h.attach(6);
pinMode(A0,OUTPUT);
pinMode(l1,OUTPUT);
 pinMode(l2,OUTPUT);
 pinMode(r1,OUTPUT);
 pinMode(r2,OUTPUT);
 analogWrite(A0,195);
}


void loop() {
  analogWrite(A0,195);
 
  if ( myRadio.available())   {
    myRadio.read( &packet, sizeof(packet) );
   // long int sum=packet.data1+packet.data2+packet.data3+packet.data4;
    Serial.print("JX received = ");
    Serial.println(packet.joy_x);
    Serial.print("JY received = ");
    Serial.println(packet.joy_y);
    Serial.print("GX received = ");
    Serial.println(packet.gyro_x);
    Serial.print("GY received = ");
    Serial.println(packet.gyro_y);

     // MOTOR CONTROL

  if(packet.joy_x==90 && packet.joy_y==90)
    {
     digitalWrite(l1,LOW);
      digitalWrite(l2,LOW);
      digitalWrite(r1,LOW);
      digitalWrite(r2,LOW); 
    Serial.println("loop stOP");
    }

   else if(packet.joy_x==180 && packet.joy_y==90)
   {
      digitalWrite(l1,HIGH);
      digitalWrite(l2,LOW);
      digitalWrite(r1,HIGH);
      digitalWrite(r2,LOW);

      Serial.println("loop FORW");
   }

   else if(packet.joy_x==0 && packet.joy_y==90)
   {
      digitalWrite(l2,HIGH);
      digitalWrite(l1,LOW);
      digitalWrite(r2,HIGH);
      digitalWrite(r1,LOW);

      Serial.println("loop back");
   }

   else if(packet.joy_x==90 && packet.joy_y==0)
   {
      digitalWrite(l2,HIGH);
      digitalWrite(l1,LOW);
      digitalWrite(r1,HIGH);
      digitalWrite(r2,LOW);

      Serial.println("loop left");
   }

   else if(packet.joy_x==90 && packet.joy_y==180)
   {
      digitalWrite(l1,HIGH);
      digitalWrite(l2,LOW);
      digitalWrite(r2,HIGH);
      digitalWrite(r1,LOW);

      Serial.println("loop r8");
      
   }

   h.write(packet.gyro_x);
   v.write(packet.gyro_y);
   
 delay(100);   
    
 
  }
}
     
