// Fun with Arduino by Rob Purser is licensed under a
// Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US
// Based on a work at https://sites.google.com/site/funarduino/
// Copyright Rob Purser, 2013-2014

int flexpotPin = 0;
int buzzerPin = 6;

int led1 = 7;
int led2 = 8;
int led3 = 9;

void setup()
{
  Serial.begin(9600);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
}

void loop()
{
  unsigned int flexpotValue = analogRead(flexpotPin);
  Serial.print("Flexpot: ");
  Serial.print(flexpotValue);
  // My flexpot gave values between about 600 when unbent, to 850 when fully bent.
  unsigned int pitch = map(flexpotValue, 600, 850, 200, 1000);
  Serial.print(" Pitch: ");
  Serial.println(pitch);
  tone(buzzerPin,pitch,100);
  
  unsigned int pinState;
  
  if (pitch < 300) {
     digitalWrite(led1,LOW);
     digitalWrite(led2,LOW);
     digitalWrite(led3,LOW);
  } else if (pitch < 500) {
     digitalWrite(led1,HIGH);
     digitalWrite(led2,LOW);
     digitalWrite(led3,LOW);
  } else if (pitch < 700) {
     digitalWrite(led1,HIGH);
     digitalWrite(led2,HIGH);
     digitalWrite(led3,LOW);
  } else {
     digitalWrite(led1,HIGH);
     digitalWrite(led2,HIGH);
     digitalWrite(led3,HIGH);
  }
}


