#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "Nrf24.h"


const byte address[5] = {'R','x','A','A','A'};

struct package { int data[4] = {0,0,0,0};};
bool ignorarPerro11 = false;
bool ignorarPerro22 = false;

typedef struct package Package;
Package dataRecieve;
//Package dataTransmit;
char dataToSend[4];

Nrf24::Nrf24(int CSN_PIN,int CE_PIN) 
{    
}

void Nrf24::begin()
{
  radio.begin();
  radio.setDataRate( RF24_250KBPS );
  radio.openReadingPipe(1, address);
  radio.startListening();
  
    pinMode(3, INPUT);
    pinMode(4, INPUT);
}

void Nrf24::send(int perros[4])
{
  
  if(ignorarPerro11) 
  {
    pinMode(3, OUTPUT);
    digitalWrite(3, HIGH);
  }
  
  if(ignorarPerro22) 
  {
    pinMode(3, OUTPUT);
    digitalWrite(3, HIGH);
  }
  radio.stopListening();
  radio.setRetries(3,5); // delay, count
  radio.openWritingPipe(address);
  radio.write(&perros, sizeof(perros));
  radio.openReadingPipe(1, address);
  radio.startListening();  
}

int* Nrf24::read()
{
  static int response[4];
  response[0] = 0;  response[1] = 0;  response[2] = 0;  response[3] = 0;
  if ( radio.available()) {
      radio.read( &dataRecieve, sizeof(dataRecieve) );
    response[0] = dataRecieve.data[0];  response[1] = dataRecieve.data[1];  response[2] = dataRecieve.data[2];  response[3] = dataRecieve.data[3];
    Serial.println(String(dataRecieve.data[0]) + String(dataRecieve.data[1]) +  String(response[2])+  String(dataRecieve.data[3]));
  }
  if(digitalRead(3) & !ignorarPerro11)
  { 
    response[0] = 154; response[1] = 113; response[2] = 138; response[3] = 22;
  }
  if(digitalRead(4) & !ignorarPerro11) 
  {
    response[0] = 158; response[1] = 193; response[2] = 190; response[3] = 21;
  }
  return response;
}
