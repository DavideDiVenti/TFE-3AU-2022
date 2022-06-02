/***************************************************************************
  This is a library for the Wisol 10 module 

  Designed to work with all kinds of WSSFM10R Breakout Boards

  This module use UART, 2 pins are required to interface.

  Written by Adrien Chapelet for IoThings
 ***************************************************************************/

#include "IO_WSSFM10.h"

//IO_WSSFM10 mySigfox(25, 26, true); //OK
IO_WSSFM10 mySigfox(17, 16, true); //OK

typedef struct {
  int counter;
  int ElegooA0;
  int BP1;
} Payload;

int counter=0;
  int BP1pin = 34;
  int ElegooA0 = 39;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
    pinMode(13, OUTPUT);
    pinMode(BP1pin, INPUT);
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
  p.counter = counter;
  p.ElegooA0 = analogRead(ElegooA0);
  p.BP1 = digitalRead(BP1pin);
  bool statusS = mySigfox.send(&p, sizeof(p));
  if (statusS) counter++;

  delay(60000);
  bool statusSR = mySigfox.sendReceive(&p, sizeof(p), sfResponse);
  if (statusSR) {
    for (uint8_t i= 0; i<26; ++i) {//RX= 01 02 03 04 05 06 07 08
      Serial.println(sfResponse[i]);
      counter++;
    }
  }
}
