// Fun with Arduino by Rob Purser is licensed under a
// Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// http://creativecommons.org/licenses/by-nc-sa/3.0/deed.en_US
// Based on a work at https://sites.google.com/site/funarduino 
// Copyright Rob Purser, 2013
// Copyright Tom Amlicke, 2014
#include <LiquidCrystal.h>

#define darkLevel 500
#define seekSpeed 120
#define forwardSpeed 150

LiquidCrystal lcd(13,12,8,7,6,2);
int pinRightForward = 9;
int pinRightReverse = 10;
int pinRightSpeed = 11;

int pinLeftForward = 3;
int pinLeftReverse = 4;
int pinLeftSpeed = 5;

int pinRightSensor = A0;
int pinCenterSensor = A1;
int pinLeftSensor = A2;

int BGLevel = 0;
int BGSD = 0;
int detectLevel = 0;
int detectSD = 0;
int rLevel, lLevel, cLevel; // Sensor levels

void setup()
{
  Serial.begin(9600);

  // TO DO: Set up the six digital pins for output using the pinMode command
  pinMode(pinLeftForward,OUTPUT);
  pinMode(pinLeftReverse,OUTPUT);
  pinMode(pinLeftSpeed,OUTPUT);
  pinMode(pinRightForward,OUTPUT);
  pinMode(pinRightReverse,OUTPUT);
  pinMode(pinRightSpeed,OUTPUT);
 lcd.print("hello world!");
}

void loop()
{
  rLevel = sensorRead(pinRightSensor);
  lLevel = sensorRead(pinLeftSensor);
  cLevel = sensorRead(pinCenterSensor);
  followNoCal();
  lcd.clear();
  lcd.print("r:");
  lcd.print( rLevel);
  lcd.print( " c:");
  lcd.print( cLevel);
  lcd.print(" l:");
  lcd.print(lLevel);
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
  digitalWrite(pinLeftForward, LOW);
  digitalWrite(pinLeftReverse, HIGH);
  analogWrite(pinLeftSpeed, speed);
}

void rightForward(byte speed) {
  digitalWrite(pinRightForward, LOW);
  digitalWrite(pinRightReverse, HIGH);
  analogWrite(pinRightSpeed, speed);
}

void leftReverse(byte speed) {
  digitalWrite(pinLeftForward, HIGH);
  digitalWrite(pinLeftReverse, LOW);
  analogWrite(pinLeftSpeed, speed);
}

void rightReverse(byte speed) {
  digitalWrite(pinRightForward, HIGH);
  digitalWrite(pinRightReverse, LOW);
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


// level 1 Line Follow Behavior

void followNoCal() {
  static boolean centerOnLine = false;
  static boolean onLine = false;
  
  rLevel = sensorRead(pinRightSensor);
  lLevel = sensorRead(pinLeftSensor);
  cLevel = sensorRead(pinCenterSensor);
  
  if (cLevel < darkLevel &&
      centerOnLine == false) {
        drive(seekSpeed);
  }
  
  if (cLevel >= darkLevel) {
    centerOnLine = true;
  }
  
  if (centerOnLine &&
      onLine == false) {
    rightBrake();
    while (rLevel < darkLevel) {
      rLevel = sensorRead(pinRightSensor);
    }
    drive(forwardSpeed);
    onLine = true;
  }
  
  if (cLevel < darkLevel &&
      onLine == true)
  {
    if (rLevel >= darkLevel)
    {
      rightBrake();
      while (cLevel < darkLevel)
      {
        cLevel = sensorRead(pinCenterSensor);
      }
      drive(forwardSpeed);
    }
    else if (lLevel >= darkLevel)
    {
      leftBrake();
      while (cLevel < darkLevel)
      {
        cLevel = sensorRead(pinCenterSensor);;
      }
      drive(forwardSpeed);
    }
  }
}

// level 0 Line Sensors

int sensorRead(int pin) {
  return analogRead(pin);
}

// An attempt at a decent single-call, quick return line detection function.
//  Takes 3 samples and applies a voting algorithm to them. If two of them
//  agree that the current reading is a positive for detection (which, for us,
//  means 2 standard deviations to the background side of the detect level),
//  it returns a true. False, otherwise. This is to reduce the impact of specks
//  and crumbs on the surface.
// A better way would be to poll regularly and look for sudden changes; we
//  can't really rely on being able to do that because of the idiosyncracies of
//  the Arduino environment.
boolean sensorCheck(int pin)
{
  // Are we looking for something that is darker than our normal level (say,
  //  a table edge, or a black stripe on a white surface) or something that
  //  is brighter than our normal level (say, a piece of copper tape?)
  boolean lightOnDark;
  if (BGLevel < detectLevel) {
    lightOnDark = true;
  }
  else {
    lightOnDark = false;
  }

  // We can set the number of samples we want to take (NUM_SAMPS) and the
  //  number of samples that must pass the threshold to count as a positive
  //  detection.
  #define NUM_SAMPS 3
  #define VOTE_PASS 2
  byte resultCounter = 0;
  
  int level[NUM_SAMPS];
  
  // First up, collect a few samples. Give a tiny break between them, so the
  //  sensor has time to move a bit.
  for (byte i = 0; i<NUM_SAMPS; i++)
  {
    level[i] = analogRead(pin);
    delay(5);
  }
  
  // Now we need to consider whether we're going to call a threshold or not.
  //  We'll do that by seeing if we have more than VOTE_PASS samples that are
  //  in the detection range.
  for (byte i = 1; i<NUM_SAMPS; i++)
  {
    // For the lightOnDark case, we're looking for an increase in the voltage,
    //  corresponding to a higher current in the receiver caused by more light
    //  being reflected.
    if (lightOnDark)
    {
      // As the reflectance of the surface increases, level will rise. We'll
      //  call a successful detection _detectLevel - 2*_detectSD; a single
      //  left shift is a cheap way to do a multiply-by-two. For each detection
      //  we increase the counter; at the end we'll compare resultCounter to
      //  VOTE_PASS to make our decision.
      if (level[i]>(detectLevel-(detectSD<<1))) resultCounter++;
    }
    else // dark-on-light condition
    {
      if (level[i]<(detectLevel+(detectSD<<1))) resultCounter++;
    }
  }
  // We've now looked at all of the samples in our array; if resultCounter
  //  is greater than or equal to VOTE_PASS, we'll call it a detection.
  if (resultCounter >= VOTE_PASS) return true;
  else                            return false;
}

// setBGLevel() is used to calibrate the level that we expect to see when we
//  aren't seeing something interesting. It takes some number of samples,
//  averages them, computes the standard deviation, and stores the results
//  as _BGLevel and _BGSD.

int sensorSetBGLevel(int pin)
{
  // To calculate our average and standard deviation, we need three values:
  //  - a running mean value (stored in _BGLevel)
  //  - a temporary last mean value (stored in lastMean)
  //  - the most current read value (level)
  //  - a running value that will yield SD at the end (BGQ)
  // All those values need to be initialized to zero. I'm going to try and stick
  //  to integer math; float sucks.
  BGLevel = 0;
  int level = 0;
  int BGQ = 0;
  int lastMean = 0;
  
  for (byte i = 1; i <= 16; i++)
  {
    // First, we need to capture a data point from each sensor.
    level = analogRead(pin);
    // Store the current mean value, then calculate the current running mean.
    lastMean = BGLevel;
    BGLevel = BGLevel + ((level-BGLevel)/i);
    // BGQ is an intermediate variable. To find the SD at any step along the 
    //  way, we'd do this:
    //    SD = sqrt(BGQ/(i-1))
    // For more information on why this is the case, see the wikipedia article 
    //  on standard deviation. In the meantime, we *don't* need the SD, so we 
    //  can skip the computationally expensive sqrt() operation until the end.
    BGQ = BGQ + ((level-lastMean)*(level-BGLevel));
    // The delay here is completely arbitrary. I want to be collecting data 
    //  for a goodly amount of time, to get a nice distribution. Might think
    //  about randomizing this to improve the data set.
    delay(250);
  }
  
  // Remember up above, where I described how to get SD from BGQ? Here it is:
  BGSD = sqrt(BGQ/15);
  
  // This is a complete sham. I don't want the SD to be *too* small, so I
  //  picked a nice number for a lower bound. No surface is perfect!
  if (BGSD<25) BGSD = 25;
  
  return BGLevel;
}

// setDetectLevel() works exactly the same as setBGLevel(), but with different
//  variables. I should really abstract out the lion's share of these two
//  functions, but I feel like they're small enough to not be worth the time.
int setDetectLevel(int pin)
{
  // To calculate our average and standard deviation, we need three values:
  //  - a running mean value (stored in _detectLevel)
  //  - a temporary last mean value (stored in lastMean)
  //  - the most current read value (level)
  //  - a running value that will yield SD at the end (DQ)
  // All those values need to be initialized to zero. I'm going to try and stick
  //  to integer math; float sucks.
  detectLevel = 0;
  int level = 0;
  int DQ = 0;
  int lastMean = 0;
  
  for (byte i = 1; i <= 16; i++)
  {
    // First, we need to capture a data point from each sensor.
    level = analogRead(pin);
    // Store the current mean value, then calculate the current running mean.
    lastMean = detectLevel;
    detectLevel = detectLevel + ((level-detectLevel)/i);
    // DQ is an intermediate variable. To find the SD at any step along the 
    //  way, we'd do this:
    //    SD = sqrt(DQ/(i-1))
    // For more information on why this is the case, see the wikipedia article 
    //  on standard deviation. In the meantime, we *don't* need the SD, so we 
    //  can skip the computationally expensive sqrt() operation until the end.
    DQ = DQ + ((level-lastMean)*(level-detectLevel));
    // The delay here is completely arbitrary. I want to be collecting data 
    //  for a goodly amount of time, to get a nice distribution. Might think
    //  about randomizing this to improve the data set.
    delay(250);
  }
  
  // Remember up above, where I described how to get SD from DQ? Here it is:
  detectSD = sqrt(DQ/15);
  
  // This is a complete sham. I don't want the SD to be *too* small, so I
  //  picked a nice number for a lower bound. No surface is perfect!
  if (detectSD<25) detectSD = 25;
  
  return detectLevel;
  
}
