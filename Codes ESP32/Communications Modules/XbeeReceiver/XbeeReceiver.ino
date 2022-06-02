#include "SerialTransfer.h"
SerialTransfer myTransfer;

int LED1 = 0;
int LED2 = 12;
int received;

struct STRUCT {
  bool stateLED1;
  bool stateLED2;
} myBuffer;

void setup(){
  Serial.begin(115200);
  Serial2.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  digitalWrite(LED1, LOW);
  digitalWrite(LED1, LOW);
  myTransfer.begin(Serial2);
}

void loop(){
   if(myTransfer.available())
  {
    uint16_t recSize = 0;
    
    recSize = myTransfer.rxObj(myBuffer, recSize);
    Serial.print("state LED1 : ");
    Serial.print(myBuffer.stateLED1);
    Serial.print(" state LED2 : ");
    Serial.println(myBuffer.stateLED2);
    Serial.println();    
    digitalWrite(LED1, myBuffer.stateLED1);
    digitalWrite(LED2, myBuffer.stateLED2);
  }
}
