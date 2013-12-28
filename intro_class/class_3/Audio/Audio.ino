// Fun with Arduino by Rob Purser is licensed under a
// Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US
// Based on a work at http://goo.gl/NNe35. 
// Copyright Rob Purser, 2013

int pinSpeaker = 6;

void setup()
{
  pinMode(pinSpeaker,OUTPUT);
}

void loop()
{
  tone(pinSpeaker,120,1000);
  delay(1000);
  tone(pinSpeaker,52,800);
  delay(900);
}
