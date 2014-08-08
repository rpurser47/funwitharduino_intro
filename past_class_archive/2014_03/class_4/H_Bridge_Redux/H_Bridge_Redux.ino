// Fun with Arduino by Rob Purser is licensed under a
// Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US
// Based on a work at http://goo.gl/NNe35. 
// Copyright Rob Purser, 2013

int pinForward = 9;
int pinReverse = 10;
int pinSpeed = 11;

void setup()
{
  Serial.begin(9600);
  pinMode(pinForward,OUTPUT);
  pinMode(pinReverse,OUTPUT);
  pinMode(pinSpeed,OUTPUT);
}

void loop()
{
  // Forward
  Serial.println("Forward");
  digitalWrite(pinForward,HIGH);
  digitalWrite(pinReverse,LOW);
  analogWrite(pinSpeed,150);
  delay(1000);

  // Spin Down
  Serial.println("Free spin");
  digitalWrite(pinForward,LOW);
  digitalWrite(pinReverse,LOW);
  delay(2000);

  // Reverse
  Serial.println("Reverse");
  digitalWrite(pinReverse,HIGH);
  delay(1000);

  // Brake
  Serial.println("Brake");
  digitalWrite(pinForward,HIGH);
  digitalWrite(pinReverse,HIGH);
  analogWrite(pinSpeed,255);
  delay(2000);
}
