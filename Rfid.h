#include <Bridge.h>
#include <BridgeClient.h>
#include <BridgeServer.h>
#include <BridgeSSLClient.h>
#include <BridgeUdp.h>
#include <Console.h>
#include <FileIO.h>
#include <HttpClient.h>
#include <Mailbox.h>
#include <Process.h>
#include <YunClient.h>
#include <YunServer.h>

#ifndef Rfid_h
#define Rfid_h

#include <MFRC522.h>

#include "Arduino.h"

class Rfid {
  public:
    Rfid(int SS_PIN,int RST_PIN);
    int * read();
    void begin();
    void loopClearInterrupt();
  private:
    MFRC522 mfrc522;
};

#endif
