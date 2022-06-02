//Ce code test les périphériques : BP1, BP2, LED1, LED2, DS18b20, LDR, IR sender, MCP23008, OLED

//inclure if/def pour sélectionner le PCB est ses périphériques
#include <IRremote.hpp>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h> 
#include <DallasTemperature.h>
#include <Keypad_MCP.h>
#include <Keypad.h>        // GDY120705
#include <Wire.h>

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


int LED1pin = 33;
int LED2pin = 32;

int BP1pin = 34;
int BP2pin = 35;
char charBP12[10];

int LDRpin = 39;
char charLDR[15];

int IR_RECpin = 27;
int IR_SENDpin = 12;

int TEMPpin = 25; // DS18B20 Temperature Sensor 1 Wire
char charTEMP[15];
OneWire oneWire(TEMPpin);
DallasTemperature sensors(&oneWire);

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
      IrSender.sendNEC(0x0102, key , true, 0);
      //Serial.println(key);
      display.setCursor(0, 42);
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
  
  pinMode(LED1pin, OUTPUT);
  pinMode(LED2pin, OUTPUT);
  digitalWrite(LED1pin, LOW);
  digitalWrite(LED2pin, LOW);

  pinMode(BP1pin, INPUT);
  pinMode(BP2pin, INPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextColor(WHITE, BLACK);
  customKeypad.addEventListener(keypadEvent); //add an event listener for this keypad  
  sensors.begin();
  IrReceiver.begin(IR_RECpin); // Initializes the IR receiver object 
  IrSender.begin(IR_SENDpin);
}

void loop() {
  myClock = (millis()/500)%2; //myClock bascule d'état toutes les 200ms : 0 1 0 1 0 1 ...
  char key = customKeypad.getKey();
  if ((myClock == 1) and (myOldClock == 0)){  //S'il y a des fronts montants de myClock : execution de toutes les taches
    digitalWrite(LED1pin, flagLED); //activée à l'état bas
    digitalWrite(LED2pin, flagLED); //activée à l'état haut
    sensors.requestTemperatures();
   
    
    sprintf(charBP12, "BP12: %1u %1u", digitalRead(BP1pin),digitalRead(BP2pin));
    sprintf(charLDR, "LDR  : %04u", analogRead(LDRpin));
    sprintf(charTEMP, "TEMP  : %0.2f", sensors.getTempCByIndex(0));
    
    
    printToOLED(0, 6, charBP12);
    printToOLED(0, 18, charLDR);
    printToOLED(0, 30, charTEMP);
    
    flagLED = ~flagLED;
  }
  
  myOldClock = myClock;
}
