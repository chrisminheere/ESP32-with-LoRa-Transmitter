//*****************************************************************************************************************************//
//Made By: Chris Minheere 
//16-08-2018                                                                                                                              
//Lora Transmitter 868Mhz, On ESP32. 
//Hardware: ESP32, DS18b20, SX1276 868MHz                                                                                                     
                                                                                                                                    
                                                                                                                                     
//Sketch uses 117026 bytes (8%) of program storage space. Maximum is 1310720 bytes.                                                 
//Global variables use 9828 bytes (3%) of dynamic memory, leaving 285084 bytes for local variables. Maximum is 294912 bytes.        
//*****************************************************************************************************************************//


#include <SPI.h>
#include <LoRa.h>
#include <OneWire.h> 
#include <DallasTemperature.h>

int counter = 0;
#define ONE_WIRE_BUS 32 
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);


void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Sender");
  sensors.begin();

  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  //pinMode(ONE_WIRE_BUS,INPUT_PULLUP);
  sensors.begin();
  LoRa.setTxPower(20);
  //LoRa.setTxPower(txPower, outputPin);
  LoRa.setSpreadingFactor(12);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(4/5);
  LoRa.setSyncWord(0x13);
  //LoRa.disableCrc();
  LoRa.setPreambleLength(8);
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);
  sensors.requestTemperatures();
  //delay(750);
  Serial.print(sensors.getTempCByIndex(0));

  // send packet
  LoRa.beginPacket();
  LoRa.print(sensors.getTempCByIndex(0));
  //LoRa.print(counter);
  LoRa.endPacket();

  //counter++;

  delay(500);
}
