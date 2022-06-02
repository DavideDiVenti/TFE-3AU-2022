#include <SPI.h>
#include <LoRa.h>
#include <OneWire.h> 
#include <DallasTemperature.h>

//Configutation frd PIN : 3AU board multi-fontion
#define ss 0
#define rst 14
#define dio0 2

int TEMPpin = 25; // DS18B20 Temperature Sensor 1 Wire
char charTEMP[15];
OneWire oneWire(TEMPpin);
DallasTemperature sensors(&oneWire);

int LDRpin = 39;
char charLDR[15];
char charBP2[10];
int BP2pin = 35;
int LED2pin = 32;
char charLED2[15];
int myClock;
int myOldClock;
int counter;
int presentBP2;
int pastBP2;
void setup() {
  //initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Receiver");
  pinMode(LED2pin, OUTPUT);
  pinMode(BP2pin, INPUT);
  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  
  //replace the LoRa.begin(---E-) argument with your location's frequency 
  //433E6 for Asia
  //866E6 for Europe
  //915E6 for North America
  while (!LoRa.begin(866E6)) {
    Serial.println(".");
    delay(500);
  }
   // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
  sensors.begin();
  
}

void SendLoRa(char *payload){
  LoRa.beginPacket();
  LoRa.print(payload);
  LoRa.endPacket();
}

void loop() {
  // try to parse packet
  String LoRaData;
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.print("Received packet : ");
    while (LoRa.available()) {
      LoRaData = LoRa.readString();
      Serial.print(LoRaData); 
    }
    if (LoRaData == "temp"){
      sprintf(charTEMP, "Temperature : %0.2f°C", sensors.getTempCByIndex(0));
      //sprintf(charTEMP, "Temp : %u°C", counter);
      SendLoRa(charTEMP); 
      Serial.println("Sending Packet: " + String(charTEMP));
      //counter++;
    }
    else if (LoRaData == "lum"){
      sprintf(charLDR, "Brightness : %u", analogRead(LDRpin));
      SendLoRa(charLDR); 
      Serial.println("Sending Packet: " + String(charLDR));
    }
    else if (LoRaData == "on"){
      sprintf(charLED2, "LED2 : ON");
      SendLoRa(charLED2); 
      digitalWrite(LED2pin, HIGH);
      Serial.println("Sending Packet: " + String(charLED2));
    }
    else if (LoRaData == "off"){
      sprintf(charLED2, "LED2 : OFF");
      SendLoRa(charLED2); 
      digitalWrite(LED2pin, LOW);
      Serial.println("Sending Packet: " + String(charLED2));
    }
  }

//  myClock = (millis()/1000)%2;
//  if ((myClock == 1) and (myOldClock == 0)){
//    sensors.requestTemperatures();
//    sprintf(charLDR, "LIGHT  : %u", analogRead(LDRpin));
//    sprintf(charTEMP, "TEMP  : %0.2f", sensors.getTempCByIndex(0));
//    sprintf(charBP2, "BP2: %1u", digitalRead(BP2pin));
//    Serial.println(charLDR);
//    Serial.println(charTEMP);
//    Serial.println(charBP2);
//  }
//  myOldClock = myClock;

  presentBP2 = digitalRead(BP2pin);
  if (presentBP2 == 1 and pastBP2 == 0){
    SendLoRa("BP2");
    Serial.println("BP2 pushed !");
  }
  pastBP2 = presentBP2;
  
}
