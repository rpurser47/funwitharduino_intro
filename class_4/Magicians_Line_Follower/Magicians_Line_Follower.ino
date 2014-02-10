
// Fun with Arduino by Rob Purser is licensed under a
// Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US
// Based on a work at https://sites.google.com/site/funarduino 
// Copyright Rob Purser, 2013
// Copyright Tom Amlicke, 2014

// darkLevel may need to change based on lighting conditions
#define darkLevel 900
#define seekSpeed 150
#define forwardSpeed 200

int pinRightForward = 9;
int pinRightReverse = 10;
int pinRightSpeed = 11;

int pinLeftForward = 3;
int pinLeftReverse = 4;
int pinLeftSpeed = 5;

int pinRightSensor = A0;
int pinCenterSensor = A1;
int pinLeftSensor = A2;


void setup()
{

  pinMode(pinLeftForward,OUTPUT);
  pinMode(pinLeftReverse,OUTPUT);
  pinMode(pinLeftSpeed,OUTPUT);
  pinMode(pinRightForward,OUTPUT);
  pinMode(pinRightReverse,OUTPUT);
  pinMode(pinRightSpeed,OUTPUT);
    
}

void loop()
{
  // A simple 3 level subsumption architecture 
  // level 2 = Line Following Behavior
  // level 1 = Movement Behavior
  // level 0 = sensor and motor controls
  // Motor controls and movement behavior is modeled on the Redbot
  // library available from Sparkfun.
  // see https://github.com/sparkfun/RedBot
  // see http://en.wikipedia.org/wiki/Subsumption_architecture for more info
  myLineFollow();
}


// level 2 Line Follow Behavior
void myLineFollow() {
  boolean r = sensorRead(pinRightSensor) > darkLevel;
  boolean l = sensorRead(pinLeftSensor) > darkLevel;
  boolean c = sensorRead(pinCenterSensor) > darkLevel;
  static boolean seekRight = true;
  
  if (l == 0 && c == 0 && r == 0) {
      seek(seekRight);
  }
  else if (l == 1 && c == 0 && r == 0) {
      goLeft();
      seekRight = false;
  }
  else if (l == 0 && c == 0 && r == 1) {
      goRight();
      seekRight = true;
  }
  else {
    goForward();
  }
 }
 
void seek(boolean seekRight) {
  drive(seekSpeed);
  if (seekRight) {
    rightBrake();
  }
  else {
    leftBrake();
  }
}

void goLeft() {
  leftBrake();
}

void goRight() {
  rightBrake();
}

void goForward() {
  drive(forwardSpeed);
}


// Level 1 Movement Behavior
void stop() {
  leftStop();
  rightStop();
}

void brake() {
  leftBrake();
  rightBrake();
}

void drive(int speed) {
  if (speed > 0)
  {
    leftForward((byte)(abs(speed)));
    rightForward((byte)(abs(speed)));
  }
  else
  {
    leftReverse((byte)(abs(speed)));
    rightReverse((byte)(abs(speed)));
  }
}

void pivot(int speed) {
  if (speed > 0)
  {
    leftReverse((byte)(abs(speed)));
    rightForward((byte)(abs(speed)));
  }
  else
  {
    leftForward((byte)(abs(speed)));
    rightReverse((byte)(abs(speed)));
  }
}

void rightDrive(int speed) {
  if (speed > 0)
  {
    rightForward((byte)(abs(speed)));
  }
  else
  {
    rightReverse((byte)(abs(speed)));
  }
  
}

void leftDrive(int speed) {
  if (speed > 0)
  {
    leftForward((byte)(abs(speed)));
  }
  else
  {
    leftReverse((byte)(abs(speed)));
  }
  
}

// Level 0 Motor Controls

void leftForward(byte speed) {
  digitalWrite(pinLeftForward, HIGH);
  digitalWrite(pinLeftReverse, LOW);
  analogWrite(pinLeftSpeed, speed);
}

void rightForward(byte speed) {
  digitalWrite(pinRightForward, HIGH);
  digitalWrite(pinRightReverse, LOW);
  analogWrite(pinRightSpeed, speed);
}

void leftReverse(byte speed) {
  digitalWrite(pinLeftForward, LOW);
  digitalWrite(pinLeftReverse, HIGH);
  analogWrite(pinLeftSpeed, speed);
}

void rightReverse(byte speed) {
  digitalWrite(pinRightForward, LOW);
  digitalWrite(pinRightReverse, HIGH);
  analogWrite(pinRightSpeed, speed);
}

void leftStop() {
  digitalWrite(pinLeftForward, LOW);
  digitalWrite(pinLeftReverse, LOW);
  analogWrite(pinLeftSpeed, 0);
}

void rightStop() {
  digitalWrite(pinRightForward, LOW);
  digitalWrite(pinRightReverse, LOW);
  analogWrite(pinRightSpeed, 0);
}

void leftBrake() {
  digitalWrite(pinLeftForward, HIGH);
  digitalWrite(pinLeftReverse, HIGH);
  analogWrite(pinLeftSpeed, 0);
}

void rightBrake() {
  digitalWrite(pinRightForward, HIGH);
  digitalWrite(pinRightReverse, HIGH);
  analogWrite(pinRightSpeed, 0);
}

// Level 0 Sensor

int sensorRead(int pin) {
  return analogRead(pin);
}






