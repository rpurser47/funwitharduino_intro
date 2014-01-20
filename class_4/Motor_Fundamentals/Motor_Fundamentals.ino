

// Fun with Arduino by Rob Purser is licensed under a
// Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US
// Based on a work at https://sites.google.com/site/funarduino 
// Copyright Rob Purser, 2013

int pinMotor = 11;

void setup()
{
  pinMode(pinMotor,OUTPUT);
}

void loop()
{
  analogWrite(pinMotor,150);
  delay(3000);

  analogWrite(pinMotor,0);
  delay(2000);	

  analogWrite(pinMotor,255);
  delay(4000);

  analogWrite(pinMotor,0);
  delay(2000);
}
