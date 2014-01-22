// Fun with Arduino by Rob Purser is licensed under a
// Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US
// Based on a work at https://sites.google.com/site/funarduino 
// Copyright Rob Purser, 2013

#include <Servo.h>
Servo myServo;
int pinPosition = 9;

void setup()
{
  myServo.attach(pinPosition);
}

void loop()
{
  myServo.write(0);
  delay(1000);

  myServo.write(180);
  delay(1000);

  myServo.write(45);
  delay(1000);

  myServo.write(135);
  delay(1000);

  myServo.write(90);
  delay(1000);
}
