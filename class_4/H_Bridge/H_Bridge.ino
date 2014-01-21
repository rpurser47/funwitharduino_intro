// Fun with Arduino by Rob Purser is licensed under a
// Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US
// Based on a work at http://goo.gl/NNe35. 
// Copyright Rob Purser, 2013

int pinForward = 9;
int pinReverse = 10;

void setup()
{
  Serial.begin(9600);
  pinMode(pinForward,OUTPUT);
  pinMode(pinReverse,OUTPUT);
}

void loop()
{
  Serial.println("Forward");
  analogWrite(pinForward,150);
  delay(1000);

  Serial.println("Free run");
  analogWrite(pinForward,0);
  delay(2000);

  Serial.println("Reverse");
  analogWrite(pinReverse,150);
  delay(1000);

  Serial.println("Free run");
  analogWrite(pinReverse,0);
  delay(2000);
}
