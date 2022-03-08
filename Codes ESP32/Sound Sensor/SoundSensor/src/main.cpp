#include <Arduino.h>
int soundSensorPin = 34;
int soundSensorValue;

void setup() {
  Serial.begin(115200);
}

void loop() {
  soundSensorValue = analogRead(soundSensorPin);
  Serial.println(soundSensorValue);
  delay(500);
}