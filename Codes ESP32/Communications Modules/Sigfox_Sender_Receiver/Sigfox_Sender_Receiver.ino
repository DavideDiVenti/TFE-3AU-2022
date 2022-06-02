/***************************************************************************
  This is a library for the Wisol 10 module 

  Designed to work with all kinds of WSSFM10R Breakout Boards

  This module use UART, 2 pins are required to interface.

  Written by Adrien Chapelet for IoThings
 ***************************************************************************/

#include "IO_WSSFM10.h"

IO_WSSFM10 mySigfox(25, 26, true); //OK

typedef struct {
  int8_t counter;
  int8_t RV;
  int8_t ElegooA0;
  
} Payload;

int myLoopCounter=42;
  
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
    Serial.begin(115200);
    mySigfox.begin();
    delay(50);
    mySigfox.test();
    mySigfox.getID();
    mySigfox.getPAC();
    mySigfox.getTemp();

    //mySigfox.setPowerMode(1);
}
  
// the loop function runs over and over again forever
void loop() {  
  String sfResponse;
  Payload p;
  p.counter = (int8_t)myLoopCounter;
  p.RV = (int8_t)(analogRead(35)>>4); //0 - 256
  p.ElegooA0 = (int8_t)(analogRead(34)>>4);
  
  mySigfox.send((uint8_t*)&p, sizeof(p)); //-> custom format counter::int:8 rv::int:8 elegoo::int:8
  myLoopCounter--;
//  Serial.println("Sending...");
//  Serial.print("counter : ");
//  Serial.print(myLoopCounter);
//  Serial.print(" rv : ");
//  Serial.print(analogRead(35)>>4);
//  Serial.print(" elegoo : ");
//  Serial.println(analogRead(34)>>4);
  //Serial.println(String(p.RV));
  
  delay(60000);
//  bool statusSR = mySigfox.sendReceive(&p, sizeof(p), sfResponse);
//  if (statusSR) {
//    for (uint8_t i= 0; i<26; ++i) {//RX= 01 02 03 04 05 06 07 08
//      Serial.println(sfResponse[i]);
//      counter++;
//    }
//  }
}
