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

/* The temperature display will look like this:

  col:0123456789012345
     |----------------|
row:0|Raw: RRRR V.VV  |
    1|Temp: CC.C FF.F |
     |----------------|
   
   R - Raw reading from the analog input
   V - Voltage read from the sensor
   C - Degrees Celsius
   F - Degrees Fahrenheit
   
*/

void setup() {
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print the titles on each row
  // Top row (row 0)
  lcd.print("Raw:");
  // Bottom row (row 1)
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  lcd.print("Temp:");
}

void loop() {
  // TASK 1: Read the temperature sensor on analog input pin 0
  int reading = // INSERT YOUR CODE HERE
  
  // TASK 2: Print the raw analog reading from the temperature sensor at column 5, line 0 (after "Raw:")
  // INSERT YOUR CODE HERE
  
  
  float voltage = (float)reading * 5.0 / 1024.0;
  
  char voltageString[20];
  // dtostrf converts a floating point number to a string
  // dtostrf(float, digLeftOfPeriod, digRightOfPeriod, pointerToString)
  dtostrf(voltage,1,2, voltageString);
  
  // print the voltage at  column 10, line 0)
  lcd.setCursor(10, 0);
  lcd.print(voltageString);

  float DegC = 0;
  float DegF = 0;

  // TASK 3: Calculate the temperature in degrees C.  The conversion formula is (voltage - 0.5) * 100
  DegC = // INSERT YOUR CODE HERE

  // TASK 4: Calculate the temperature in degrees F.  The conversion is DegC * 9.0 / 5.0 + 32.0
  DegF = // INSERT YOUR CODE HERE

  // print the celsius temp at column 6, line 1)
  char degCString[20];
  dtostrf(DegC,1,1, degCString);
  lcd.setCursor(6, 1);
  lcd.print(degCString);

  // print the fahrenheit temp at column 11, line 1)
  char degFString[20];
  lcd.setCursor(11, 1);
  dtostrf(DegF,1,1, degFString);
  lcd.print(degFString);
  
  delay(500);
}

