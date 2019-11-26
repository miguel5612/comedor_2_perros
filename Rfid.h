#ifndef Rfid_h
#define Rfid_h

#include <MFRC522.h>

#include "Arduino.h"

class Rfid {
  public:
    Rfid(int SS_PIN,int RST_PIN);
    int * read();
    void begin();
  private:
    MFRC522 mfrc522;
};

#endif
