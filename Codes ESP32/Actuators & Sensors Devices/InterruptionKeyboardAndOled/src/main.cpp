/* @file CustomKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates changing the keypad size and key values.
|| #
    Use with I2C i/o G. D. (Joe) Young Feb 28/12

    Use with MCP23008 I2C i/o G. D. (Joe) Young Jul 29/12
*/
#include <Keypad_MCP.h>
#include <Keypad.h>        // GDY120705
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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
#define LED1        12 // LED1 on pin 12
#define LED2        0  // LED2 on pin 0
#define LED1_ON()   digitalWrite(LED1,HIGH)
#define LED1_OFF()  digitalWrite(LED1,LOW)
#define LED2_ON()   digitalWrite(LED2,HIGH)
#define LED2_OFF()  digitalWrite(LED2,LOW)

// Keypad events
void keypadEvent(KeypadEvent key){
  switch (customKeypad.getState()){
    case PRESSED:
      switch (key){
        case 'A': LED1_ON(); break;
        case 'B': LED1_OFF(); break;
        case 'C': LED2_ON(); break;
        case 'D': LED2_OFF(); break;
      }
      Serial.println(key);
      display.clearDisplay();   
      display.setCursor(0, 0);
      display.print(F("Key: "));  
      display.print(key);  
      display.display(); 
      break;
    case RELEASED:
      switch (key){
      }
      break;
    case HOLD:
      switch (key){
      }
      break;
  }
}

// Setup function
void setup(){
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  LED1_OFF();
  LED2_OFF();
  Wire.begin( );
  customKeypad.begin( );        // GDY120705
  Serial.begin(115200);
  // OLED Display
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds
  // Clear the buffer
  display.clearDisplay();
  display.setTextSize(3); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(F("Key: "));  
  display.display(); // Show initial text
  customKeypad.addEventListener(keypadEvent); //add an event listener for this keypad  
  Serial.println("OLED and Keypad with MCP23008 test...");  
}

// Loop function
void loop(){
  char key = customKeypad.getKey();
  
//  if (key != NO_KEY){
//    Serial.println(key);
//    display.clearDisplay();   
//    display.setCursor(0, 0);
//    display.print(F("Key: "));  
//    display.print(key);  
//    display.display();  
//  }
}

