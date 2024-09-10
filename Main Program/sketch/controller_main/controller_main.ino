#include "./displaycont.hpp"
#include "./eepromcont.hpp"
#include "./htuCont.hpp"
#include "./myIRsender.hpp"

//Uncomment for Wifi Serial Monitor
//#include "./wserialmonitor.hpp"

//Global Current Weather Variables
float currentTemp = 0.0;
float currentHumidity = 0.0;

//AC State
int stateAC = 7;

//Turn off fan after cool off
bool fanOff = false;

//DisplayState
bool enableDisp = false;
int stateDisp = 5; // 1 Normal 2 Reading 3 Menu 4 IR OUT

//Temperature Variables
float tempval[4] = {31, 29.00, 28.00, 26.00};


//EEPROM RESET - SET TO FALSE IF TEMP VARS / DISPLAY BOOL NOT CHANGED
//DISABLE/ENABLE FLASH RESETS IN EEPROMCONT.HPP
bool resetEE = false;

//HTU Specific Weather Variables
float htuT[3];
float htuH[3];

//To Control EEPROM TEMPSET MENU
int menupos = 0;

//Temporary Display Timer
int displaytimer = 0;

//Buttons Defined
const int butset = 32;
const int butup = 35;
const int butdown = 34;

//Main Counters
long loopCounter = 0;
long stateTimer = 0;


void setup()
{
  //Uncomment for Wifi Serial Monitor
  //Replace Serial.print with WebSerial.print everywhere
  //wlansetup();

  //Comment when using Wifi Serial Monitor
  //Serial.begin(57600);

  pinMode(butset, INPUT);
  pinMode(butup, INPUT);
  pinMode(butdown, INPUT);

  if (resetEE)
  {
    // Serial.println(F("WARNING: EEPROM ABOUT TO BE RESET!!!"));
    delay(5000);
    // Serial.println(F("EEPROM WAS RESET."));
    eereset(tempval, enableDisp);
  }

  //EEPROM DISPLAY ON OFF SETTING
  // enableDisp = eereaddisp();
  toggleDisp(enableDisp);

  // Store EEPROM values to functioning variables
  for (int i = 0; i < 4; i++)
  {
    tempval[i] = eeread(i + 1);
    // Serial.print(F("Read from EEPROM to RAM storage T"));
    // Serial.print(i+1);
    // Serial.print(F(". Value: "));
    // Serial.println(tempval[i]);
  }

  delay(1000);
}

void loop()
{
  delay(10); // MAIN DELAY

  //15 Second Interval Temp/Humidity Reader
  if (loopCounter % 1500 == 0)
  {
    tempNow();
    humNow();
    if (menupos != 1 && menupos != 2 && menupos != 3 && menupos != 4)
    {
      displayread();
      stateDisp = 2;
      displaytimer = 500;
    }
  }


  //Set Button Reader
  if (enableDisp == true)
  {
    if (digitalRead(butset) == LOW)
    {
      // Serial.println("COMES TO SET");
      delay(200);
      if ((digitalRead(butset) == HIGH))
      {
        // Serial.println(F("Set Button Pressed. "));
        menupos++;
        if (menupos == 1 || menupos == 2 || menupos == 3 || menupos == 4)
        {
          displaymenu(menupos, tempval[menupos - 1]);
          stateDisp = 3;
        }

        //Write EEPROM with Set Button if value changed
        if (menupos == 2 || menupos == 3 || menupos == 4 || menupos == 5)
        {
          if (tempval[menupos - 2] != eeread(menupos - 1))
          {
            eewrite(tempval[menupos - 2], menupos - 1);
            // Serial.print(F("EEPROM VALUE "));
            // Serial.print(menupos-1);
            // Serial.print(F(" UPDATED TO "));
            // Serial.println(tempval[menupos-2]);
          }
          else
          {
            // Serial.print(F("No Change in value "));
            // Serial.println(menupos-1);
          }
        }

        // Return Menu
        if (menupos == 5)
        {
          displaynormal();
          stateDisp = 1;
          menupos = 0;
        }
      }
    }
  }

  //UP / DOWN button reader
  if (menupos == 1 || menupos == 2 || menupos == 3 || menupos == 4)
  {
    if (digitalRead(butup) == LOW)
    {
      // Serial.println("COMES TO UP");
      delay(200);
      if (digitalRead(butup) == HIGH)
      {
        tempval[menupos - 1] += 0.05;
        displaymenu(menupos, tempval[menupos - 1]);
        stateDisp = 3;
      }
    }
    else if (digitalRead(butdown) == LOW)
    {
      // Serial.println("COMES TO DOWN");
      delay(200);
      if (digitalRead(butdown) == HIGH)
      {
        tempval[menupos - 1] -= 0.05;
        displaymenu(menupos, tempval[menupos - 1]);
        stateDisp = 3;
      }
    }
  }
  else if (menupos == 0)
  {
    if (digitalRead(butup) == LOW)
    {
      // Serial.println("COMES TO UP AGAIN");
      delay(200);
      if (digitalRead(butup) == HIGH)
      {
        // eetoggledisp();
        enableDisp = !enableDisp;
        toggleDisp(enableDisp);
        displaynormal();
        stateDisp = 1;
        // Serial.print(F("Display Turned: "));
        /*  if(enableDisp == true)
            {
              // Serial.println(F("ON"));
            }
            else if(enableDisp == false)
            {
              // Serial.println(F("OFF"));
            }   */
      }
    }
    else if (digitalRead(butdown) == LOW)
    {
      // Serial.println("COMES TO Down AGAIN");
      delay(200);
      if (digitalRead(butdown) == HIGH)
      {
        enableDisp = true;
        toggleDisp(true);
        sendNow(4);
        delay(20000);
        ESP.restart();
      }
    }
  }


  //Normal Display
  if (menupos == 1 || menupos == 2 || menupos == 3 || menupos == 4 || displaytimer > 0)
  {
    if (displaytimer > 0)
    {
      displaytimer--;
    }
  }
  else if (stateDisp != 1)
  {
    displaynormal();
    stateDisp = 1;
  }

  //Run AC Control Every Second
  if (loopCounter % 100 == 0)
  {
    stateTimer++;
    acControl();
  }
  // Serial.print(F("LOOP: "));
  // Serial.println((int)loopCounter);


  //Reset every 6 hours
  if (loopCounter >= 2160000)
  {
    ESP.restart();
  }

  loopCounter++;


}

void displayread()
{
  displayreading(htuT, htuH);
}

void displaynormal()
{
  defaultdisplay(currentTemp, currentHumidity, loopCounter);
}

void tempNow()
{
  float three = 3.00;
  htuT[0] = htutemp(1);
  htuT[1] = htutemp(2);
  htuT[2] = htutemp(3);

  currentTemp = (htuT[0] + htuT[1] + htuT[2]) / three;
}

void humNow()
{
  float three = 3.00;
  htuH[0] = htuhum(1);
  htuH[1] = htuhum(2);
  htuH[2] = htuhum(3);

  currentHumidity = (htuH[0] + htuH[1] + htuH[2]) / three;
}

void acControl()
{
  //EMERGENCY
  if (currentTemp <= tempval[3])
  {
    for (int i = 0; i < 5; i++)
    {
      stateAC = sendNow(4);
      stateDisp = 4;
      stateTimer = 0;
      displaytimer = 500;
      delay(120000);
      stateTimer += 120;
    }
    ESP.restart();
  }
  
  //START PROCEDURE
  if (currentTemp >= tempval[0])
  {
    fanOff = false;
    acSwitch(1);
  }
  else if (currentTemp >= tempval[1]  && currentTemp < tempval[0])
  {
    fanOff = false;
    acSwitch(2);
  }
  else if (currentTemp <= tempval[2])
  {
    if (fanOff != true)
    {
      acSwitch(3);
    }
  }
  if (stateAC == 3 && stateTimer > 60)
  {
    acSwitch(4);
    fanOff = true;
  }
}

void acSwitch(int command)
{
  if (stateAC == 7)
  {
    stateAC = sendNow(command);
    stateDisp = 4;
    displaytimer = 500;
    stateTimer = 0;
    // Serial.print(F("First command: "));
    // Serial.println(command);
  }
  else if (stateAC == command || stateTimer < 60)
  {
    if (stateTimer >= 150)
    {
      // Serial.println(F("Long State Reaffirm."));
      stateAC = sendNow(command);
      stateDisp = 4;
      displaytimer = 500;
      stateTimer = 0;
      return;
    }
    /*   if(stateTimer < 60)
       {
         // Serial.print(F("Short timer return: "));
         // Serial.println((int)stateTimer);
       }
       else
       {
         // Serial.println(F("No state change."));
       }   */
    return;
  }
  else
  {
    stateAC = sendNow(command);
    stateDisp = 4;
    displaytimer = 500;
    stateTimer = 0;
  }
}
