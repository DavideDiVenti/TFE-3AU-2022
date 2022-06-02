#include <IRremote.hpp> // >v3.0.0
#include <Keypad_MCP.h>
#include <Keypad.h>        // GDY120705
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
                                            
#define PIN_SEND 32
//#define PIN_RECV 33

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

//initialize an instance of class NewKeypad
Keypad_MCP customKeypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS, I2CADDR); 

// OLED display
#define SCREEN_WIDTH    128 // OLED display width, in pixels
#define SCREEN_HEIGHT   64 // OLED display height, in pixels
#define OLED_RESET      -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS  0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// LEDs pins & macro


void keypadEvent(KeypadEvent key){  
  switch (customKeypad.getState()){
    case PRESSED:
      IrSender.sendNEC(0x0102, key , true, 0);
      Serial.println(key);
      display.clearDisplay();   
      display.setCursor(0, 0);
      display.print(F("Key : "));  
      display.print(key);
      display.display(); 
      break;
  }
}

void setup()  
{ 

  Wire.begin( );
  customKeypad.begin( );        // GDY120705
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();
  display.setTextSize(1); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(F("Key: "));  
  display.display(); // Show initial text
  customKeypad.addEventListener(keypadEvent); //add an event listener for this keypad  
  Serial.println("OLED and Keypad with MCP23008 test...");   
  IrReceiver.begin(PIN_RECV); // Initializes the IR receiver object 
  IrSender.begin(PIN_SEND); // Initializes IR sender
}  
                               
void loop()  
{   
  char key = customKeypad.getKey();
}
