#include <Arduino.h>
int LED1 = 0;
int LED2 = 12;
int BP1 = 36;
int BP2 = 4;

int BP1Value;
int BP2Value;

void setup() {

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BP1, INPUT);
  pinMode(BP2, INPUT);

  Serial.begin(115200);
}

void loop() {
  BP1Value = digitalRead(BP1);
  BP2Value = digitalRead(BP2);

  if (BP1Value){
    digitalWrite(LED1, HIGH);
  }
  else {
    digitalWrite(LED1, LOW);
  }

  if (BP2Value){
    digitalWrite(LED2, HIGH);
  }
  else {
    digitalWrite(LED2, LOW);
  }

  Serial.print("BP1 : ");
  Serial.println(BP1Value);
  Serial.print("BP2 : ");
  Serial.println(BP2Value);
  delay(50);
}