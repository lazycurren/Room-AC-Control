#ifndef EEPROMCONT_H
#define EEPROMCONT_H

//Uncomment for Wifi Serial Monitor
//#include "./wserialmonitor.hpp"

#include "Preferences.h"

//Uncomment for Flash Resets
//#include "nvs_flash.h"

/*
*
**
**  CAUTION: DISABLE FLASH RESETS AND CLEARS IF NOT IN USE.
**
*
*/

 
Preferences preferences;

void eereset(float tempval[], bool ENDSP)
{
//Use These to clear all namespaces  
//  nvs_flash_erase();
//  nvs_flash_init();
  
  preferences.begin("temps", false);

//Use this to clear all preferences under opened namespace
//  preferences.clear();

  if(tempval[0] != preferences.getFloat("t1", 0.0))
  {
    preferences.putFloat("t1", tempval[0]);
    // Serial.println(F("RESET T1 in EEPROM"));
  }
  if(tempval[1] != preferences.getFloat("t2", 0.0))
  {
    preferences.putFloat("t2", tempval[1]);
    // Serial.println(F("RESET T2 in EEPROM"));
  }
  if(tempval[2] != preferences.getFloat("t3", 0.0))
  {
    preferences.putFloat("t3", tempval[2]);
    // Serial.println(F("RESET T3 in EEPROM"));
  }
  if(tempval[3] != preferences.getFloat("t4", 0.0))
  {
    preferences.putFloat("t4", tempval[3]);
    // Serial.println(F("RESET T4 in EEPROM"));
  }
  if( ENDSP != preferences.getBool("ENDSP", false))
  {
    preferences.putBool("ENDSP", ENDSP);
    // Serial.println(F("DISPLAY STATE RESET TO: "));
    // Serial.println(ENDSP);
  }
  preferences.end();
}


float eeread(int value)
{
  preferences.begin("temps", true);
  String toUse;
  
  switch (value)
  {
    case 1:
      toUse = "t1";
      break;
    case 2:
      toUse = "t2";
      break;
    case 3:
      toUse = "t3";
      break;
    case 4:
      toUse = "t4";
      break;
  }
  float sendback = preferences.getFloat(toUse.c_str(), 5.0);
  preferences.end();
  return sendback;
}


void eewrite(float temp, int value)
{
  preferences.begin("temps", false);
  String toUse = "";
  
  switch (value)
  {
    case 1:
      toUse = "t1";
      break;
    case 2:
      toUse = "t2";
      break;
    case 3:
      toUse = "t3";
      break;
    case 4:
      toUse = "t4";
      break;
  }
  preferences.putFloat(toUse.c_str(), temp);
  preferences.end();
}

/*
bool eereaddisp()
{
  preferences.begin("temps", true);
  int sendback = preferences.getBool("ENDSP", true);
  preferences.end();
  if(sendback == 1)
  {
    return true;
  }
  else if(sendback == 0)
  {
    return false;
  }
}

void eetoggledisp()
{
  preferences.begin("temps", false);
  // Serial.print(F("EE DISPLAY WAS: "));
  // Serial.println(preferences.getBool("ENDSP", true));
  // Serial.print(F("EE DISPLAY NOW: "));
  preferences.putBool("ENDSP", !(preferences.getBool("ENDSP", true)));
  // Serial.println(preferences.getBool("ENDSP", true));
  preferences.end();
}
*/


#endif
