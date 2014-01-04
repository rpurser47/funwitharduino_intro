// Fun with Arduino by Rob Purser is licensed under a
// Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US
// Based on a work at https://sites.google.com/site/funarduino
// Copyright Rob Purser, 2013

int pinRed = 11;
int pinGreen = 10;
int pinBlue = 9;

void setup()
{
  pinMode(pinRed,OUTPUT);
  pinMode(pinGreen,OUTPUT);
  pinMode(pinBlue,OUTPUT);
}

void loop()
{
  // Common anode 
  analogWrite(pinGreen,0);
  analogWrite(pinBlue,0);
  // Fade Red from off (0) to on (255)
  for(int intensity = 0;intensity <= 255; intensity++)
  {
    analogWrite(pinRed,intensity);
    delay(20);
  }
  // Fade Green from off (0) to on (255) to make yellow
  for(int intensity = 0;intensity <= 255; intensity++)
  {
    analogWrite(pinGreen,intensity);
    delay(20);
  }
  // Fade Blue from off (0) to on (255) to make white
  for(int intensity = 0;intensity <= 255; intensity++)
  {
    analogWrite(pinBlue,intensity);
    delay(20);
  }
  // Fade Green from on (255) to off (0) to make purple
  for(int intensity = 255;intensity >= 0; intensity--)
  {
    analogWrite(pinGreen,intensity);
    delay(20);
  }
  // Fade Red from on (255) to off (0) to make blue
  for(int intensity = 255;intensity >= 0; intensity--)
  {
    analogWrite(pinRed,intensity);
    delay(20);
  }
  // Fade Blue from on (255) to off (0) 
  for(int intensity = 255;intensity >= 0; intensity--)
  {
    analogWrite(pinBlue,intensity);
    delay(20);
  }
  
}
