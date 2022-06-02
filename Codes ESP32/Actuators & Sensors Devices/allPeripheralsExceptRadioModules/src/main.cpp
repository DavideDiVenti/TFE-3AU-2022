#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"

int pixelPin = 15;
int pixelNumber = 3;
int pixel;
Adafruit_NeoPixel pixels(pixelNumber, pixelPin, NEO_GRB + NEO_KHZ800);

#include <Wire.h>//https://www.arduino.cc/en/reference/wire
#include <Adafruit_MPU6050.h>//https://github.com/adafruit/Adafruit_MPU6050
#include <Adafruit_Sensor.h>//https://github.com/adafruit/Adafruit_Sensor

//Objects
Adafruit_MPU6050 mpu;

// OLED
#define SCREEN_WIDTH 128                                          // Largeur en pixel de l'OLED
#define SCREEN_HEIGHT 64                                          // Hauteur en pixel de l'OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // Création de notre OLED SSD1306 pour communiquer avec l'I²C (SDA, SCL)

int pinLED1 = 12;
int pinLED2 = 0; 
int flagLED = 0;

int pinBP1 = 36;
int pinBP2 = 4;
char charBP12[10];

int pinRV = 35;
char charRV[15];

int pinPIR = 13;
char charPIR[10];

int pinA0ElegooSensor = 34;
char charA0ElegooSensor[16];

char charAcceleration[20];
char chargyroscope[60];

#define DHTTYPE DHT22
#define DHTPIN 27
DHT dht(DHTPIN, DHTTYPE);//déclaration du capteur
char charT[12];
char charH[12];


int myClock;
int myOldClock;

void printToOLED(int x, int y, int size, char *message){                   // Fonction affichant un message dans l'OLED à une cetraine position
  display.setTextSize(size);
  display.setCursor(x, y);                                        // On place le cursor du message aux coordonner X Y avant de l'afficher
  display.print(message);                                         // On place ce message sur ce cursor
  display.display();                                              // On affiche le tout
}

void setup() {
  pixels.begin();
  pixels.clear(); 

  Serial.begin(115200);

  pinMode(pinLED1, OUTPUT);
  pinMode(pinLED2, OUTPUT);
  digitalWrite(pinLED1, LOW);
  digitalWrite(pinLED2, LOW);

  pinMode(pinBP1, INPUT);
  pinMode(pinBP2, INPUT);

  pinMode(pinPIR, INPUT);

  if (!mpu.begin(0x68)) { // Change address if needed
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);


  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextColor(WHITE, BLACK);                             // Configuration d'écriture de blanc sur noir dans l'OLED
 
  dht.begin();
}

void loop() {
  myClock = (millis()/200)%2; //myClock bascule d'état toutes les 200ms : 0 1 0 1 0 1 ...

  if ((myClock == 1) and (myOldClock == 0)){  //S'il y a des fronts montants de myClock : execution de toutes les taches
    digitalWrite(pinLED1, flagLED);
    digitalWrite(pinLED2, not(flagLED));
    //Read acceleromter data
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    switch (pixel){
    case 0 : pixels.setPixelColor(0, pixels.Color(0, 10, 0)); pixels.setPixelColor(1, pixels.Color(2, 2, 2)); pixels.setPixelColor(2, pixels.Color(2, 2, 2)); pixel++; break; //Vert
    case 1 : pixels.setPixelColor(1, pixels.Color(10, 10, 0)); pixels.setPixelColor(2, pixels.Color(2, 2, 2)); pixels.setPixelColor(0, pixels.Color(2, 2, 2)); pixel++; break; //Jaune
    case 2 : pixels.setPixelColor(2, pixels.Color(10, 0, 0)); pixels.setPixelColor(0, pixels.Color(2, 2, 2)); pixels.setPixelColor(1, pixels.Color(2, 2, 2)); pixel=0; break; //Rouge
    }  
    pixels.show();

    float h = dht.readHumidity();//on lit l'hygrometrie
    float t = dht.readTemperature();//on lit la temperature en celsius (par defaut)
    if (isnan(h) || isnan(t))
    {
      Serial.println("Failed to read from DHT sensor!");
      for (int i = 6; i<10; i++){
        charT[i] = '?';
        charH[i] = '?';
      }
    }
    else {
      sprintf(charT, "Temp: %0.1f", t);   
      sprintf(charH, "Hum : %0.1f", h);
    }
    
    sprintf(charBP12, "BP12: %1u %1u", digitalRead(pinBP1),digitalRead(pinBP2));
    sprintf(charRV, "RV  : %04u", analogRead(pinRV));
    sprintf(charPIR, "PIR : %1u", digitalRead(pinPIR));
    sprintf(charA0ElegooSensor, "E.S.: %04u", analogRead(pinA0ElegooSensor));
    sprintf(charAcceleration, "A.xyz: %0.1f %0.1f %0.1f ", a.acceleration.x, a.acceleration.y, a.acceleration.z);
    sprintf(chargyroscope, "G.xyz: %0.1f %0.1f %0.1f ", g.gyro.x, g.gyro.y, g.gyro.z);
    
    printToOLED(0, 6, 1, charBP12);                                   // Affichage d'un message à l'OLED
    printToOLED(0, 18, 1, charRV);                                    // Affichage d'un message à l'OLED
    printToOLED(0, 30, 1, charT);                               // Affichage d'un message à l'OLED
    printToOLED(0, 42, 1, charAcceleration);                                   // Affichage d'un message à l'OLED
    printToOLED(0, 54, 1, chargyroscope);                                   // Affichage d'un message à l'OLED
    printToOLED(66, 6, 1, charPIR);                                   // Affichage d'un message à l'OLED
    printToOLED(66, 18, 1, charA0ElegooSensor);                                   // Affichage d'un message à l'OLED
    printToOLED(66, 30, 1, charH);                                   // Affichage d'un message à l'OLED


    flagLED = ~flagLED;
  }

  myOldClock = myClock;
  
}