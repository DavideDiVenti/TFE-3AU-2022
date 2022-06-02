// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <CAN.h>

char bufferCAN[9] = "Hello   ";
int myClock;
int myOldClock;

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("CAN Sender/Receiver");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
}

void loop() {
  /* =========== Receiver ========== */
  // try to parse packet
  int packetSize = CAN.parsePacket();

  if (packetSize) {
    // received a packet
    Serial.print("Received ");

    if (CAN.packetExtended()) {
      Serial.print("extended ");
    }

    if (CAN.packetRtr()) {
      // Remote transmission request, packet contains no data
      Serial.print("RTR00 ");
    }

    Serial.print("packet with id 0x");
    Serial.print(CAN.packetId(), HEX);

    if (CAN.packetRtr()) {
      Serial.print(" and requested length ");
      Serial.println(CAN.packetDlc());
    } else {
      Serial.print(" and length ");
      Serial.println(packetSize);

      // only print packet data for non-RTR packets
      while (CAN.available()) {
        Serial.print((char)CAN.read());
      }
      Serial.println();
    }

    Serial.println();
  }

  /* =========== Sender ========== */
  myClock = (millis()/1000)%2;
  if (myClock == 1 and myOldClock == 0){
    Serial.print("Sending packet ... ");

  CAN.beginPacket(0x12, CAN.packetDlc(), false); //RTR false
  for (int i = 0; i < 9; i++) {
    CAN.write(bufferCAN[i]); 
  }
  CAN.endPacket();

  Serial.println("done");

//  // send extended packet: id is 29 bits, packet can contain up to 8 bytes of data
//  Serial.print("Sending extended packet ... ");
//
//  CAN.beginPacket(0x12);
//  CAN.write('P');
//  CAN.write('l');
//  CAN.write('o');
//  CAN.write('p');
//  CAN.write(' ');
//  CAN.endPacket();
//
//  Serial.println("done");
  }
  myOldClock = myClock;
  // send packet: id is 11 bits, packet can contain up to 8 bytes of data
  delay(20);
}
