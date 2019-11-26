#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "Nrf24.h"


const byte address[6] = "00001";

struct package { int data[4] = {0,0,0,0};};

typedef struct package Package;
Package dataRecieve;
Package dataTransmit;

Nrf24::Nrf24(int CSN_PIN,int CE_PIN) 
{    
}

void Nrf24::begin()
{
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.startListening();
}

void Nrf24::send(int perros[4])
{
  radio.stopListening();
  radio.openWritingPipe(address);
  dataTransmit.data[0] = perros[0];
  dataTransmit.data[1] = perros[1];
  dataTransmit.data[2] = perros[2];
  dataTransmit.data[3] = perros[3];
  radio.write(&dataTransmit, sizeof(dataTransmit));
  radio.openReadingPipe(0, address);
  radio.startListening();  
}

int* Nrf24::read()
{
  static int response[4];
  response[0] = 0;  response[1] = 0;  response[2] = 0;  response[3] = 0;
  if ( radio.available()) {
    while (radio.available()){
      radio.read( &dataRecieve, sizeof(dataRecieve) );
    }    
    response[0] = dataRecieve.data[0];  response[1] = dataRecieve.data[1];  response[2] = dataRecieve.data[2];  response[3] = dataRecieve.data[3];
  }
  return response;
}
