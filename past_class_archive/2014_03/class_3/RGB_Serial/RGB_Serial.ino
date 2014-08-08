// Fun with Arduino by Rob Purser is licensed under a
// Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US
// Based on a work at http://goo.gl/NNe35. 
// Copyright Rob Purser, 2013

int pinsRGB[] = { 11, 10, 9};

void setup()
{
  Serial.begin(9600);

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
    // Read the serial port
    int incomingByte = Serial.read();
    // Ignore anything except ASCII 48 to 57, '0' to '9'
    int command = constrain(incomingByte,48,57);
    // Translate '0' to 0, '9' to 255, etc.
    int output = map(command,48,57,0,255);

    Serial.print("Setting pin ");
    Serial.print(pinsRGB[pinIndex]);
    Serial.print(" to ");
    Serial.println(output);
    analogWrite(pinsRGB[pinIndex],output);
    pinIndex = (pinIndex + 1) % 3;
  }
}
