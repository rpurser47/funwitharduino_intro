// Fun with Arduino by Rob Purser is licensed under a
// Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US
// Based on a work at http://goo.gl/NNe35. 
// Copyright Rob Purser, 2013

int pinToPulse = 9;

void setup()
{
  pinMode(pinToPulse,OUTPUT);
}

void loop()
{
  for(int intensity = 0; intensity <= 255; intensity++)
  {
    analogWrite(pinToPulse,intensity);
    delay(20);
  }
  for(int intensity = 255; intensity >= 0; intensity--)
  {
    analogWrite(pinToPulse,intensity);
    delay(20);
  }
}
