#include "SerialTransfer.h"

int myClock;
int myOldClock;
int ESensorA0pin = 39;
int BP2pin = 35;
int LED2pin = 32;
int Buzzerpin = 2;
//XBee
SerialTransfer myTransfer;
struct STRUCT {
  int ESensorA0;
  int Buzzer;
  bool LED2;
  bool BP2;
} myXBeeBuffer;


void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);
  myTransfer.begin(Serial2);
  pinMode(BP2pin, INPUT);
  pinMode(LED2pin, OUTPUT);

  ledcSetup(0, 2000, 8);
  ledcAttachPin(Buzzerpin, 0);
}

void loop() {
  if (myTransfer.available()){
    uint16_t recSize = 0;    
    recSize = myTransfer.rxObj(myXBeeBuffer, recSize);   
    digitalWrite(LED2pin, myXBeeBuffer.LED2);
    ledcWrite(0, myXBeeBuffer.Buzzer*255);
    Serial.println("LED2 : "+ String(myXBeeBuffer.LED2) + " ; Buzzer : " + String(myXBeeBuffer.Buzzer));
  }

  myClock = (millis()/200)%2;
  if ((myClock == 1) and (myOldClock == 0)){
    myXBeeBuffer.ESensorA0 = analogRead(ESensorA0pin);
    myXBeeBuffer.BP2 = digitalRead(BP2pin);
    uint16_t sendSize = 0;
    sendSize = myTransfer.txObj(myXBeeBuffer, sendSize);
    myTransfer.sendData(sendSize);
    //Serial.println(myXBeeBuffer.BP2);
  }
  myOldClock = myClock;
  
}
