#include <Arduino.h>
int PIRSensorPin  = 13;
bool PIRSensorValue  = false;

void setup() {
  Serial.begin(115200);
  pinMode(PIRSensorPin, INPUT);
}

void loop() {
  PIRSensorValue = digitalRead(PIRSensorPin);
  Serial.print("Sensor status : "); 
  Serial.println(PIRSensorValue);
  if (PIRSensorValue) {
    Serial.print("----> Detection");
    delay(500);
  }
  delay(100);
}
