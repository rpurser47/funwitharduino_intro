/*
  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 13
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * potentiometer to LCD VO pin (pin 3)

Fun with Arduino by Rob Purser is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US
Based on a work at https://sites.google.com/site/funarduino/
Copyright Rob Purser, 2013-2014

*/

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 13, 5, 4, 3, 2);

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Raw:");
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  
  Serial.begin(9600);
}

void loop() {
  int reading = analogRead(0);
  // print the analog reading from the temperature sensor:
  // set the cursor to column 5, line 0 (after "Raw:")
  lcd.setCursor(5, 0);
  lcd.print(reading);
  
  float voltage = (float)reading * 5.0 / 1024.0;
  
  char lcdString[20];
  dtostrf(voltage,1,2, lcdString);
  
  // set the cursor to column 10, line 0)
  lcd.setCursor(10, 0);
  lcd.print(lcdString);

  float DegC = (voltage - 0.5) * 100;
  float DegF = DegC * 9.0 / 5.0 + 32.0;

  // set the cursor to column 6, line 1)
  lcd.setCursor(6, 1);
  dtostrf(DegC,1,1, lcdString);
  lcd.print(lcdString);

  // set the cursor to column 11, line 1)
  lcd.setCursor(11, 1);
  dtostrf(DegF,1,1, lcdString);
  lcd.print(lcdString);
  
  delay(500);
}

