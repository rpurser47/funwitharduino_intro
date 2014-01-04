// Fun with Arduino by Rob Purser is licensed under a
// Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US
// Based on a work at http://goo.gl/NNe35. 
// Copyright Rob Purser, 2013

int pinToPulse = 11;

void setup()
{
  pinMode(pinToPulse,OUTPUT);
}

void loop()
{
  for(int t = 0; t < 100; t++)
  {
    // Yes, I used MATLAB to determine this...
    // full range
    //int intensity = int((1 - cos(t * 0.0628)) * 127);
    // pleasing range
    int intensity = int(100 - cos(t * 0.0628) * 90);
    analogWrite(pinToPulse,intensity);
    delay(20);
  }
}
