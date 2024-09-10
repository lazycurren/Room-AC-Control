#ifndef DISPLAYCONT_H
#define DISPLAYCONT_H

#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SDA 21
#define SCL 22

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)

bool dispONOFF;

void defaultdisplay( float a, float b, int timer) 
{
  if(dispONOFF == false)
  {
    return;
  }
  TwoWire *theWire = &Wire1;
  Wire1.begin(SDA, SCL); 
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, OLED_RESET);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  display.clearDisplay();
  display.setTextSize(1); // Draw 1X-scale text
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  
  timer = timer / 100;
  int hh  =   timer  /  3600;
  timer   -=  hh     *  3600;
  int mm  =   timer  /  60;
  timer   -=  mm     *  60;
  int ss  =   timer;

  display.println(F("Temperature:"));
  display.setTextSize(2); 
  display.print(a);
  display.println(F(" C"));
  display.setTextSize(1);
  display.println(F("Humidity:"));
  display.setTextSize(2); 
  display.print(b);
  display.println(F("%"));
  display.setTextSize(1);
  display.print(F("Timer: "));
  display.print(hh);
  display.print(F(":"));
  display.print(mm);
  display.print(F(":"));
  display.println(ss);
  display.display();
}


void displaymenu(int menupos, float value)
{
  if(dispONOFF == false)
  {
    return;
  }
  TwoWire *theWire = &Wire1;
  Wire1.begin(SDA, SCL);
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, OLED_RESET);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  
  switch (menupos)
  {
    case 1: //set T1
      display.println(F("Set T 24: "));
      display.println(value);
      display.display();
    break;
  
    case 2: //set T2
      display.println(F("Set T 26: "));
      display.println(value);
      display.display();
    break;
 
    case 3: //set T3
      display.println(F("Set T Fan: "));
      display.println(value);
      display.display();
    break;
    
    case 4: //set T4
      display.println(F("Set T OFF: "));
      display.println(value);
      display.display();
    break;
  }
}


void displayreading(float temparr[], float humarr[])
{
  if(dispONOFF == false)
  {
    return;
  }
  TwoWire *theWire = &Wire1;
  Wire1.begin(SDA, SCL);
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, OLED_RESET);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  display.clearDisplay();
  display.setTextSize(2); // Draw 1X-scale text
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  
  display.print(temparr[0], 1);
  display.print(F(" "));
  display.println(humarr[0], 1);

  display.print(temparr[1], 1);
  display.print(F(" "));
  display.println(humarr[1], 1);

  display.print(temparr[2], 1);
  display.print(F(" "));
  display.println(humarr[2], 1);
  display.display();
}


void displayIRout(int state)
{
  if(dispONOFF == false)
  {
    return;
  }
  TwoWire *theWire = &Wire1;
  Wire1.begin(SDA, SCL);
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, OLED_RESET);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  display.clearDisplay();
  display.setTextSize(2); // Draw 1X-scale text
  display.setTextColor(WHITE);
  display.setCursor(0, 0);

  display.print(F("Transmit: "));

  switch (state)
  {
    case 1:
      display.print(F("22 COOL HIGH"));
      break;
    case 2:
      display.print(F("26 COOL LOW"));
      break;
    case 3:
      display.print(F("26 FAN LOW"));
      break;
    case 4:
      display.print(F("OFF"));
      break;
  }

  display.display();
}


void toggleDisp(bool state)
{
  dispONOFF = state;
  if(dispONOFF == false)
  {
    TwoWire *theWire = &Wire1;
    Wire1.begin(SDA, SCL);
    Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, OLED_RESET);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.display();
  }
  /*
  else if(dispONOFF == true)
  {
    TwoWire *theWire = &Wire1;
    Wire1.begin(SDA, SCL);
    Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, OLED_RESET);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    
    display.clearDisplay();
    display.setTextSize(2); // Draw 1X-scale text
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println(F("WAIT..."));
    display.display();
  }
  */
}


#endif
