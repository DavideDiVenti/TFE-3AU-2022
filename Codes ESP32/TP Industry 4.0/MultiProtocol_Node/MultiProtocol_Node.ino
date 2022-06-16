#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include "DHT.h"
#include "SerialTransfer.h"
#include <SPI.h>
#include <LoRa.h>

//Configutation frd PIN : 3AU board LoRa
#define ss 0
#define rst 14
#define dio0 2
int counter = 0;
int myClock;
int myOldClock;
String LoRaMessageReceived;

//MQTT
const char* ssid = "Davide";
const char* password = "12345678";
const char* mqtt_server = "192.168.137.172";
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg;
char msg[50];
int value;

//local datas
#define DHTTYPE DHT22
#define DHTPIN 27
DHT dht(DHTPIN, DHTTYPE);//déclaration du capteur
float temperature;
float humidity;
const int LED2 = 12;
const int BP1 = 36;
int presentBP1;
int pastBP1;

//XBee
SerialTransfer myTransfer;
struct STRUCT {
  int ESensorA0;
  int Buzzer;
  bool LED2;
  bool BP2;
} myXBeeBuffer;

int presentXBeeBP2;
int pastXBeeBP2;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  pinMode(LED2, OUTPUT);
  pinMode(BP1, INPUT);
  dht.begin();

  myTransfer.begin(Serial2);
  LoRa.setPins(ss, rst, dio0);
  while (!LoRa.begin(866E6)) {
    Serial.println(".");
    delay(500);
  }
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
}

void ReceiveLoRa(){

  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.print("Received packet : ");
    while (LoRa.available()) {
      LoRaMessageReceived = LoRa.readString();
      Serial.println(LoRaMessageReceived); 
    }
    if(LoRaMessageReceived == "BP2"){
      client.publish("MonoProtocol LoRa/Event", "*BP2* in the *PCB MonoProtocol LoRa* is pushed !"); 
    }
    else {
       client.publish("MonoProtocol LoRa/RequestExecuted", LoRaMessageReceived.c_str()); //accusé de réception
    }
   
  }
}

void SendLoRa(char *payload){
  LoRa.beginPacket();
  LoRa.print(payload);
  LoRa.endPacket();
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String payload;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    payload += (char)message[i];
  }
  Serial.println();
//-------------MultiProtocol Requests----------------//
  if (String(topic) == "MultiProtocol/Request") {
    Serial.print("Changing output to ");
    if(payload == "on"){
      Serial.println("on");
      digitalWrite(LED2, LOW);
      client.publish("MultiProtocol/RequestExecuted", "*LED2* : ON"); //accusé de réception
    }
    else if(payload == "off"){
      Serial.println("off");
      digitalWrite(LED2, HIGH);
      client.publish("MultiProtocol/RequestExecuted", "*LED2* : OFF"); //accusé de réception
    }
    else if(payload == "temp"){
      temperature = dht.readTemperature();   
      char tempString[30];
      sprintf(tempString,"*Temperature* : %0.2f°C", temperature);
      Serial.print("Temperature: ");
      Serial.println(tempString);
      client.publish("MultiProtocol/RequestExecuted", tempString); //accusé de réception
    }
    else if(payload == "hum"){
      humidity = dht.readHumidity();
      char humString[30];
      sprintf(humString, "*Humidity* : %0.2f/100", humidity);
      Serial.print("Humidity: ");
      Serial.println(humString);
      client.publish("MultiProtocol/RequestExecuted", humString); //accusé de réception
    }
  }
//-------------MonoProtocol Zigbee Requests----------------// 
  else if (String(topic) == "MonoProtocol Zigbee/Request"){
    char RequestExecutedString[30];
    uint16_t sendSize = 0;
    if(payload == "analog"){          
      sprintf(RequestExecutedString, "*Elegoo Sensor A0* : %u", myXBeeBuffer.ESensorA0);
      client.publish("MonoProtocol Zigbee/RequestExecuted", RequestExecutedString); //accusé de réception
    }
    else if(payload == "Bon"){
      myXBeeBuffer.Buzzer = 1; 
      sendSize = myTransfer.txObj(myXBeeBuffer, sendSize);   
      myTransfer.sendData(sendSize);      
      sprintf(RequestExecutedString, "*Buzzer* : ON");
      client.publish("MonoProtocol Zigbee/RequestExecuted", RequestExecutedString); //accusé de réception
    }
    else if(payload == "Boff"){
      myXBeeBuffer.Buzzer = 0;
      sendSize = myTransfer.txObj(myXBeeBuffer, sendSize);   
      myTransfer.sendData(sendSize);           
      sprintf(RequestExecutedString, "*Buzzer* : OFF");
      client.publish("MonoProtocol Zigbee/RequestExecuted", RequestExecutedString); //accusé de réception
    }
    else if(payload == "Lon"){
      myXBeeBuffer.LED2 = 1;
      sendSize = myTransfer.txObj(myXBeeBuffer, sendSize);   
      myTransfer.sendData(sendSize);            
      sprintf(RequestExecutedString, "*LED2* : ON");
      client.publish("MonoProtocol Zigbee/RequestExecuted", RequestExecutedString); //accusé de réception
    }
    else if(payload == "Loff"){
      myXBeeBuffer.LED2 = 0;
      sendSize = myTransfer.txObj(myXBeeBuffer, sendSize);   
      myTransfer.sendData(sendSize);          
      sprintf(RequestExecutedString, "*LED2* : OFF");
      client.publish("MonoProtocol Zigbee/RequestExecuted", RequestExecutedString); //accusé de réception
    }   
  }
//-------------MonoProtocol LoRa Requests----------------// 
  else if ((String(topic) == "MonoProtocol LoRa/Request")){
    char RequestExecutedString[30];
    if(payload == "temp"){    
      SendLoRa("temp");         
    }
    else if(payload == "lum"){     
      SendLoRa("lum");  
    }
    else if(payload == "on"){      
      SendLoRa("on");
    }
    else if(payload == "off"){  
      SendLoRa("off");       
    }  
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("MultiProtocol/Request");
      client.subscribe("MonoProtocol Zigbee/Request");
      client.subscribe("MonoProtocol LoRa/Request");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  ReceiveLoRa();
    
  presentBP1 = digitalRead(BP1);
  if (presentBP1 == 1 and pastBP1 == 0){
    client.publish("MultiProtocol/Event", "*BP1* in the *PCB MultiProtocol* is pushed !"); //accusé de réception
  }
  pastBP1 = presentBP1;

  presentXBeeBP2 = myXBeeBuffer.BP2;
  if (presentXBeeBP2 == 1 and pastXBeeBP2 == 0){
    client.publish("MonoProtocol Zigbee/Event", "*BP2* in the *PCB MonoProtocol Zigbee* is pushed !"); //accusé de réception
  }
  pastXBeeBP2 = presentXBeeBP2;
  
  if(myTransfer.available())
  {
    uint16_t recSize = 0;    
    recSize = myTransfer.rxObj(myXBeeBuffer, recSize);
  }
    
  delay(20);
}
