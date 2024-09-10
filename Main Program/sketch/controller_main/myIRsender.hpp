#ifndef MYIRSENDER_HPP
#define MYIRSENDER_HPP

#include <IRsend.h>
#include "./ircodes.h"
#include "./displaycont.hpp"

//Uncomment for Wifi Serial Monitor
//#include "./wserialmonitor.hpp"

IRsend irsend(4); // IR OUT PIN GPIO4 / D4

int sendNow(int state)
{
  irsend.begin();
  switch (state)
  {
    case 1:
      // Serial.println(F("24 ON was sent."));
      irsend.sendRaw(rawON, 279, 38);
      delay(100);
      irsend.sendRaw(raw22NCH, 279, 38);
      break;
    case 2:
      // Serial.println(F("26 ON was sent."));
      irsend.sendRaw(rawON, 279, 38);
      delay(100);
      irsend.sendRaw(raw26NCL, 279, 38);
      break;
    case 3:
      // Serial.println(F("Fan Mode was sent."));
      irsend.sendRaw(rawON, 279, 38);
      delay(100);
      irsend.sendRaw(raw26NFL, 279, 38);
      break;
    case 4:
      // Serial.println(F("OFF was sent."));
      irsend.sendRaw(rawOFF, 279, 38);
      break;
  }
  displayIRout(state);
  return state;
  // Send a raw data capture at 38kHz.
}

#endif
