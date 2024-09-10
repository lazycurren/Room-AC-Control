#ifndef HTUCONT_H
#define HTUCONT_H

#include <Wire.h>
#include "Adafruit_HTU21DF.h"

//Uncomment for Wifi Serial Monitor
//#include "./wserialmonitor.hpp"

#define SDA_1 23
#define SDA_2 21
#define SDA_3 13

#define SCL 18

Adafruit_HTU21DF htu1 = Adafruit_HTU21DF();
Adafruit_HTU21DF htu2 = Adafruit_HTU21DF();
Adafruit_HTU21DF htu3 = Adafruit_HTU21DF();

float val = 0.0;

float htutemp(int module)
{
  if (module == 1)
  {
    Wire.begin(SDA_1, SCL);
    htu1.begin();
//    Serial.println("HELLO1");
    val = htu1.readTemperature();
    htu1.reset();
    Wire.end();
    return val;
    
  }
  else if (module == 2)
  {
    Wire.begin(SDA_2, SCL);
    htu2.begin();
//    Serial.println("HELLO2");
   val = htu2.readTemperature();
    htu2.reset();
    Wire.end();
    return val;
  }
  else if (module == 3)
  {
    Wire.begin(SDA_3, SCL);
    htu3.begin();
//    Serial.println("HELLO3");
    val = htu3.readTemperature();
    htu3.reset();
    Wire.end();
    return val;
    
  } 
}

float htuhum(int module)
{
  if (module == 1)
  {
    Wire.begin(SDA_1, SCL);
    htu1.begin();
//    Serial.println("HELLO1");
    val = htu1.readHumidity();
    htu1.reset();
    Wire.end();
    return val;
  }
  else if (module == 2)
  {
    Wire.begin(SDA_2, SCL);
    htu2.begin();
//    Serial.println("HELLO2");
    val = htu2.readHumidity();
    htu2.reset();
    Wire.end();
    return val;
  }
  else if (module == 3)
  {
    Wire.begin(SDA_3, SCL);
    htu3.begin();
//    Serial.println("HELLO3");
    val = htu3.readHumidity();
    htu3.reset();
    Wire.end();
    return val;
  }
}

#endif
