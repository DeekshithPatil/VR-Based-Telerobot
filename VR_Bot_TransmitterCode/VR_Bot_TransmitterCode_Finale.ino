/*Connections
 * NRF: Refer Google
 * Joystick:X-Axis->A0,Y-Axis->A1 and power connections
 * Gyroscope:X-Axis->A2,Y-axis->A3and power connections
 */


#include <SPI.h>
#include "RF24.h"
#define jx 0
#define jy 1
#define gx 2
#define gy 3

int x,y,a,b;

RF24 myRadio (7, 8);
byte addresses[][6] = {"1Node"};

struct Pack {
  int data1;
  int data2;
  int data3;
  int data4;
  
} packet;

void setup() {
  Serial.begin(115200);
  Serial.println(F("RF24/Simple Transmit data Test"));

  myRadio.begin();
  myRadio.setChannel(108);
  myRadio.setPALevel(RF24_PA_MIN);
  myRadio.openWritingPipe(addresses[0]);
}

void loop() {
  x = analogRead(jx);
  y = analogRead(jy);
  a = analogRead(gx);
  b = analogRead(gy);

packet.data1=map(x,0,1023,0,180);

//MAPPING X AXIS

 if(packet.data1<=70)
   packet.data1=0;

  else if(packet.data1>=110)
    packet.data1=180;

  else
    packet.data1=90;

 packet.data2=map(y,0,1023,0,180);  
 
//MAPPING Y AXIS
 
   if(packet.data2<=70)
    packet.data2=0;

    else if(packet.data2>=110)
      packet.data2=180;

    else
      packet.data2=90;

 packet.data3=map(a,270,420,0,180);

 packet.data4=map(b,270,420,0,180);
  
  myRadio.write(&packet, sizeof(packet));
    Serial.print(F("Data Transmitted jx= "));
    Serial.print(packet.data1);
    Serial.println();
    Serial.print(F("Data Transmitted jy= "));
    Serial.print(packet.data2);
    Serial.println();

    Serial.print(F("Data Transmitted gx= "));
    Serial.print(packet.data3);
    Serial.println();

    Serial.print(F("Data Transmitted gy= "));
    Serial.print(packet.data4);
    Serial.println();
  
  delay(100);
}
 


