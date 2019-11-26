#ifndef Nrf24_h
#define Nrf24_h

#include <nRF24L01.h>
#include <RF24.h>

#include "Arduino.h"

class Nrf24 {
  public:
    Nrf24(int CSN_PIN,int CE_PIN);
    int * read();
    void send(int perro[4]);
    void begin();
  private:
    RF24 radio = RF24(10,9);
};

#endif
