// Fun with Arduino by Rob Purser is licensed under a
// Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US
// Based on a work at http://goo.gl/NNe35. 
// Copyright Rob Purser, 2013

#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 13, 5, 4, 3, 2);

int pinsRGB[] = { 11, 10, 9};

void setup()
{
  Serial.begin(9600);
  
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  
  for(int iPin=0; iPin<3; iPin++)
  {
     pinMode(pinsRGB[iPin],OUTPUT);
     analogWrite(pinsRGB[iPin],0);
  }
}

int pinIndex = 0;

void loop()
{
  if(Serial.available() > 0)
  {
    lcd.clear();
    
    // Read the serial port
    int incomingByte = Serial.read();
    // Ignore anything except ASCII 48 to 57, '0' to '9'
    int command = constrain(incomingByte,48,57);
    // Translate '0' to 0, '9' to 255, etc.
    lcd.print(command); lcd.print(" ");
    int output = map(command,48,57,0,255);
    
    analogWrite(pinsRGB[pinIndex],output);
    lcd.print(pinIndex); lcd.print(" ");
    pinIndex = (pinIndex + 1) % 3;
    lcd.print(output);lcd.print(" ");
  }
}
