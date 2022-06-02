#include <IRremote.hpp> // >v3.0.0
                                            
//#define PIN_SEND 3
#define PIN_RECV 33

void setup()  
{ 
  Serial.begin(9600); //initialize serial connection to print on the Serial Monitor of the Arduino IDE
  IrReceiver.begin(PIN_RECV); // Initializes the IR receiver object 
  //IrSender.begin(PIN_SEND); // Initializes IR sender
}  
                               
void loop()  
{  

  if (IrReceiver.decode()) {
    Serial.println("Received something...");    
    IrReceiver.printIRResultShort(&Serial); // Prints a summary of the received data
    IrReceiver.resume(); // Important, enables to receive the next IR signal
    switch (IrReceiver.decodedIRData.command){
      case '1' : Serial.println("ONE"); break;
      case '2' : Serial.println("TWO"); break;
      case '3' : Serial.println("THREE"); break;
      case '4' : Serial.println("FOUR"); break;
      case '5' : Serial.println("FIVE"); break;
      case '6' : Serial.println("SIX"); break;
      case '7' : Serial.println("SEVEN"); break;
      case '8' : Serial.println("EIGHT"); break;
      case '9' : Serial.println("NINE"); break;
      case '0' : Serial.println("ZERO"); break;
      case 'A' : Serial.println("LETTER A"); break;
      case 'B' : Serial.println("LETTER B"); break;
      case 'C' : Serial.println("LETTER C"); break;
      case 'D' : Serial.println("LETTER D"); break;
      case '*' : Serial.println("STAR"); break;
      case '#' : Serial.println("HASHTAG"); break;
    }
    
  } 
}
