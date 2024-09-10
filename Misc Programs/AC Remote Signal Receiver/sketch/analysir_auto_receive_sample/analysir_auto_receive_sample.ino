#define LEDPIN 13
//you may increase this value on Arduinos with greater than 2k SRAM
#define maxLen 800
#define rxPinIR 3 //pin D2 or D3 on standard arduinos. (other pins may be available on More mordern modules like MEga2560, DUE, ESP8266, ESP32)


volatile  unsigned int irBuffer[maxLen]; //stores timings - volatile because changed by ISR
volatile unsigned int x = 0; //Pointer thru irBuffer - volatile because changed by ISR

void setup() {
  Serial.begin(57600); //change BAUD rate as required
  attachInterrupt(digitalPinToInterrupt(rxPinIR), rxIR_Interrupt_Handler, CHANGE);//set up ISR for receiving IR signal
}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.println(F("Press the button on the remote now - once only"));
  delay(5000); // pause 5 secs
  if (x) { //if a signal is captured
    digitalWrite(LEDPIN, HIGH);//visual indicator that signal received
    Serial.println();
    Serial.print(F("Raw: (")); //dump raw header format - for library
    Serial.print((x - 1));
    Serial.print(F(") "));
    detachInterrupt(digitalPinToInterrupt(rxPinIR));//stop interrupts & capt ure until finshed here
    for (int i = 1; i < x; i++) { //now dump the times
      if (!(i & 0x1)) Serial.print(F("-"));
      Serial.print(irBuffer[i] - irBuffer[i - 1]);
      Serial.print(F(", "));
    }
    x = 0;
    Serial.println();
    Serial.println();
    digitalWrite(LEDPIN, LOW);//end of visual indicator, for this time
    attachInterrupt(digitalPinToInterrupt(rxPinIR), rxIR_Interrupt_Handler, CHANGE);//re-enable ISR for receiving IR signal
  }

}

void rxIR_Interrupt_Handler() {
  if (x > maxLen) return; //ignore if irBuffer is already full
  irBuffer[x++] = micros(); //just continually record the time-stamp of signal transitions

}
