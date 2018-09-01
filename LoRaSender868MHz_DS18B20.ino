//*****************************************************************************************************************************//
//Made By: Chris Minheere
//1-09-2018
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

  //**********Lora Transceiver Settings***********//
  //More ino at:https://github.com/sandeepmistry/arduino-LoRa/blob/master/API.md

  sensors.begin();
  LoRa.setTxPower(20);                    //Change the TX power of the radio.
  //LoRa.setTxPower(txPower, outputPin);
  LoRa.setSpreadingFactor(12);            //Change the spreading factor of the radio.
  LoRa.setSignalBandwidth(125E3);         //Change the signal bandwidth of the radio.
  LoRa.setCodingRate4(4 / 5);             //Change the coding rate of the radio.
  LoRa.setSyncWord(0x11);                 //Change the sync word of the radio.
  //LoRa.disableCrc();                    //Enable or disable CRC usage, by default a CRC is not used.
  LoRa.setPreambleLength(8);              //Change the preamble length of the radio.
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);
  sensors.requestTemperatures();
  //delay(750); //Sensor gets time to collect data, not necessary if you are using SF12
  Serial.print(sensors.getTempCByIndex(0));

  // send packet
  LoRa.beginPacket();
  LoRa.print(sensors.getTempCByIndex(0));
  LoRa.print("        +");
  LoRa.print(counter);
  LoRa.endPacket();
  LoRa.idle();

  counter++;

  delay(20000);
}
