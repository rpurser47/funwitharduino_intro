// Fun with Arduino by Rob Purser is licensed under a
// Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US
// Based on a work at https://sites.google.com/site/funarduino
// Copyright Rob Purser, 2013-2014

int pinRed = 11;
int pinGreen = 10;
int pinBlue = 9;

void setup()
{
  // TODO: Add code to configure the red, green, and blue pins for analog output using the pinMode command
  pinMode(pinRed,OUTPUT);
  pinMode(pinGreen,OUTPUT);
  pinMode(pinBlue,OUTPUT);
}

void loop()
{
  for(int t = 0; t < 300; t++)
  {
    // Yes, I used MATLAB to determine this...
    int redIntensity = int((1 - cos(t * 0.0628)) * 127);
    int greenIntensity = int((1 - cos(t * 0.0837)) * 127);
    int blueIntensity = int((1 - cos(t * 0.2512)) * 127);

    //TODO: Add code to write the intensity values out to the pins using the analogWrite command.
    analogWrite(pinRed,redIntensity);
    analogWrite(pinGreen,greenIntensity);
    analogWrite(pinBlue,blueIntensity);

    delay(50);
  }
}
