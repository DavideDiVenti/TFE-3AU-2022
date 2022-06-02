#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Keypad_MCP.h>
#include <Keypad.h>        // GDY120705
#include <Wire.h>
#include <Adafruit_NeoPixel.h>

int pixelPin = 27;
int pixelNumber = 1;
int pixel;
Adafruit_NeoPixel pixels(pixelNumber, pixelPin, NEO_GRB + NEO_KHZ800);

Adafruit_SSD1306 display(128, 64, &Wire, -1);

// Keypad variables
#define I2CADDR 0x20
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {0, 1, 2, 3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 5, 6, 7}; //connect to the column pinouts of the keypad
char charkey[10];
//initialize an instance of class NewKeypad
Keypad_MCP customKeypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS, I2CADDR); 

int LED1pin = 14;
int LED2pin = 32;

int BP1pin = 34;
int BP2pin = 35;
char charBP12[10];

int ElegooSensorA0pin = 39;
int ElegooSensorD0pin = 25;
char charElegooSensorA0[15];
char charElegooSensorD0[15];

int TouchButtonpin = 12;
char charTouchButton[15];

int buzzerpin = 0;

int myClock;
int myOldClock;

int flagLED = 0;

void printToOLED(int x, int y,  char *message, int size = 1){                   // Fonction affichant un message dans l'OLED à une cetraine position
  display.setTextSize(size);
  display.setCursor(x, y);                                        // On place le cursor du message aux coordonner X Y avant de l'afficher
  display.print(message);                                         // On place ce message sur ce cursor
  display.display();                                              // On affiche le tout
}
void keypadEvent(KeypadEvent key){  
  switch (customKeypad.getState()){
    case PRESSED:
      //Serial.println(key);
      display.setCursor(0, 12);
      display.print(F("Key : "));  
      display.print(key);
      display.display(); 
      break;
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin( );
  customKeypad.begin( );        // GDY120705
  pixels.begin();
  pixels.clear(); 
  pinMode(LED1pin, OUTPUT);
  pinMode(LED2pin, OUTPUT);
  digitalWrite(LED1pin, LOW);
  digitalWrite(LED2pin, LOW);
  pinMode(buzzerpin, OUTPUT);
  pinMode(BP1pin, INPUT);
  pinMode(BP2pin, INPUT);
  pinMode(ElegooSensorD0pin, INPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextColor(WHITE, BLACK);
  customKeypad.addEventListener(keypadEvent); //add an event listener for this keypad  
}

void loop() {
  myClock = (millis()/500)%2; //myClock bascule d'état toutes les 200ms : 0 1 0 1 0 1 ...
  char key = customKeypad.getKey();
  if ((myClock == 1) and (myOldClock == 0)){  //S'il y a des fronts montants de myClock : execution de toutes les taches
    digitalWrite(LED1pin, flagLED); 
    digitalWrite(LED2pin, not(flagLED));    
    
    switch (pixel){
    case 0 : pixels.setPixelColor(0, pixels.Color(0, 10, 0)); digitalWrite(buzzerpin, HIGH); pixel++; break; //Vert
    case 1 :pixels.setPixelColor(0, pixels.Color(0, 0, 0)); digitalWrite(buzzerpin, LOW); pixel=0; break; //Jaune   
    }  
    pixels.show();
    
    sprintf(charBP12, "BP12: %1u %1u", digitalRead(BP1pin),digitalRead(BP2pin));
    sprintf(charTouchButton, "Tch.Bt.: %04u", touchRead(TouchButtonpin));
    sprintf(charElegooSensorA0, "E.S.A0: %04u", analogRead(ElegooSensorA0pin));
    sprintf(charElegooSensorD0, "E.S.D0: %04u", digitalRead(ElegooSensorD0pin));
    
    printToOLED(0, 6, charBP12);
    printToOLED(0, 30, charTouchButton);
    printToOLED(0, 42, charElegooSensorA0);
    printToOLED(0, 54, charElegooSensorD0);
    
    flagLED = ~flagLED;
  }
  
  myOldClock = myClock;

}
