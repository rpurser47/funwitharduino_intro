// Fun with Arduino by Rob Purser is licensed under a
// Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US
// Based on a work at https://sites.google.com/site/funarduino 
// Copyright Rob Purser, 2013

int pinRightForward = 9;
int pinRightReverse = 10;
int pinRightSpeed = 11;

int pinLeftForward = 3;
int pinLeftReverse = 4;
int pinLeftSpeed = 5;

void setup()
{
  Serial.begin(9600);

  // TO DO: Set up the six digital pins for output using the pinMode command

  // Make sure everything is off at start
  digitalWrite(pinLeftForward,LOW);
  digitalWrite(pinLeftReverse,LOW);
  digitalWrite(pinRightForward,LOW);
  digitalWrite(pinRightReverse,LOW);
}

void loop()
{
  // TO DO:  Write out the speed command (at least 600) to the enable pins for the left and right
  // motors using the analogWrite command.  What's the maximum value you can put in?

  // Forward
  Serial.println("Forward");
  digitalWrite(pinLeftForward,HIGH);
  digitalWrite(pinLeftReverse,LOW);  //Why do we need this?
  digitalWrite(pinRightForward,HIGH);
  delay(3000);

  // Turn Left by stopping the right wheel
  Serial.println("Turn Left");
  digitalWrite(pinRightForward,LOW);
  delay(3000);

  // Reverse
  Serial.println("Reverse");
  digitalWrite(pinLeftForward,LOW);
  digitalWrite(pinLeftReverse,HIGH);
  digitalWrite(pinRightReverse,HIGH);
  delay(3000);

  // Turn Right by stopping the right wheel (so only left is going backward)
  Serial.println("Turn Right");
  digitalWrite(pinRightReverse,LOW);
  delay(3000);
}
