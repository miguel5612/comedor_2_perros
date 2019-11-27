#include <Arduino.h>
#include <MFRC522.h>
#include "Rfid.h"

Rfid::Rfid(int SS_PIN,int RST_PIN) 
{
    mfrc522 = MFRC522(RST_PIN,SS_PIN);
}

void Rfid::loopClearInterrupt()
{
      mfrc522.PCD_WriteRegister(MFRC522::ComIrqReg, 0x80); //Clear interrupts
}

void Rfid::begin()
{
    mfrc522.PCD_Init();  
    delay(4);
    mfrc522.PCD_DumpVersionToSerial();  
}

int* Rfid::read(){
  static int response[4];
  response[0] = 0;  response[1] = 0;  response[2] = 0;  response[3] = 0;
  if ( mfrc522.PICC_IsNewCardPresent()){  
    if ( mfrc522.PICC_ReadCardSerial()) 
    {            
        for (int i = 0; i < mfrc522.uid.size; i++) {
          response[i] = mfrc522.uid.uidByte[i];
        } 
        mfrc522.PICC_HaltA();   
    }      
  }  
  return response;

}
