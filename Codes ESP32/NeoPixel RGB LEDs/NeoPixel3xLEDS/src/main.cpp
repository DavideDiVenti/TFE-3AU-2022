#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define pixelPin 15
#define pixelNumber 3

Adafruit_NeoPixel pixels(pixelNumber, pixelPin, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear();
  pixels.setBrightness(200);

}

void loop() {
  for (int pixel = 0; pixel <= 2; pixel++){
    pixels.setPixelColor(pixel, 255, 0, 0);
    pixels.show();
    delay(250);
  }
  delay(250);
  for (int pixel = 2; pixel >= 0; pixel--){
    pixels.setPixelColor(pixel, 0, 0, 0);
    pixels.show();
    delay(250);
  }
  delay(250);
}