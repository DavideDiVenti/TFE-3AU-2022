#include "SerialTransfer.h"
SerialTransfer myTransfer;

int BP1 = 36;
int BP2 = 4;

int valueBP1;
int valueBP2;
int pastBP1;
int pastBP2;
int toggleBP1;
int toggleBP2;
int counterBP1;
int counterBP2;

struct STRUCT {
  bool stateLED1;
  bool stateLED2;
} myBuffer;

void setup(){
  Serial.begin(115200);
  Serial2.begin(9600);
  pinMode(BP1, INPUT);
  pinMode(BP1, INPUT);
  myTransfer.begin(Serial2);  
}

void loop(){
  valueBP1 = digitalRead(BP1);
  valueBP2 = digitalRead(BP2);
  uint16_t sendSize = 0;
  
  if (valueBP1 == 1 and pastBP1 == 0){ 
    counterBP1++;  
    toggleBP1 = counterBP1%2;
    Serial.print(counterBP1);
    Serial.print(" toggleBP1 : ");
    //Serial2.write(toggleBP1);

    myBuffer.stateLED1 = toggleBP1;
    Serial.println(myBuffer.stateLED1);
    sendSize = myTransfer.txObj(myBuffer, sendSize);
    myTransfer.sendData(sendSize);
  }
  pastBP1 = valueBP1;

  if (valueBP2 == 1 and pastBP2 == 0){
    counterBP2++;  
    toggleBP2 = counterBP2%2;
    Serial.print(counterBP2);
    Serial.print(" toggleBP2 : ");
   
    //Serial2.write(toggleBP2);

    myBuffer.stateLED2 = toggleBP2;
    Serial.println(myBuffer.stateLED2);
    sendSize = myTransfer.txObj(myBuffer, sendSize);
    myTransfer.sendData(sendSize);
  }
  pastBP2 = valueBP2;
 
  delay(50);
}
