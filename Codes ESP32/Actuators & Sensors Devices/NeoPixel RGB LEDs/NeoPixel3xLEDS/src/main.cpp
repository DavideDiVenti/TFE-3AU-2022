#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
int DataIn = 15;
int pixel = 3;
int i;
Adafruit_NeoPixel pixels(pixel, DataIn, NEO_GRB + NEO_KHZ800);
 
void setup() {
  pixels.begin();
  pixels.clear();
}
 
void loop() {
  
    switch (i){
    case 0 : pixels.setPixelColor(0, pixels.Color(0, 10, 0)); pixels.setPixelColor(1, pixels.Color(2, 2, 2)); pixels.setPixelColor(2, pixels.Color(2, 2, 2)); i++; break;
    case 1 : pixels.setPixelColor(1, pixels.Color(10, 10, 0)); pixels.setPixelColor(2, pixels.Color(2, 2, 2)); pixels.setPixelColor(0, pixels.Color(2, 2, 2)); i++; break;
    case 2 : pixels.setPixelColor(2, pixels.Color(10, 0, 0)); pixels.setPixelColor(0, pixels.Color(2, 2, 2)); pixels.setPixelColor(1, pixels.Color(2, 2, 2)); i=0; break;
    }  
    pixels.show();
  delay(200);
}