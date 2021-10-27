#include <PID_v1.h>
#include <Arduino.h>

#include <Encoder.h>
#include "PIDAngle.h"

// #define LIMIT_SWITCHA 14
// #define LIMIT_SWITCHB A17
// #define CHANNEL_A 3
// #define CHANNEL_B 2
// #define DIR_A 25
// #define PWM_A 24

double pi = 3.14;

// Best PID : Kp = 500, Ki = 1, Kd = 25
PIDAngle::PIDAngle(int CH_A, int CH_B, int Dir, int pwm_out, int limitSwitch, double leftLimit, boolean reverse)
    : _myEnc(CH_A, CH_B), _myPID(&_newPosition, &_motorPower, &_setLocation, 10, 5, 0, DIRECT)
{

  _CH_A = CH_A;
  _CH_B = CH_B;
  _Dir = Dir;
  _pwm_out = pwm_out;
  _leftLimit = leftLimit;
  _limitSwitch = limitSwitch;
  _reverse = reverse;

  pinMode(_limitSwitch, INPUT);
  _myPID.SetMode(AUTOMATIC);
  _myPID.SetOutputLimits(0, 200);
  //_myPID.SetSampleTime(400);

  pinMode(_CH_A, INPUT);
  pinMode(_CH_B, INPUT);
  pinMode(_Dir, OUTPUT);
  pinMode(_pwm_out, OUTPUT);
  Serial.begin(19200);
}

long oldPosition = -999;

void PIDAngle::moveTo(double setLocation)
{
  _setLocation = setLocation;
  //setLocation = map(val,0,1023,0,2*pi);
  if (_setLocation >= _leftLimit)
  {
    _setLocation = _leftLimit;
  }
  _myPID.Compute();
  _temp = _myEnc.read();
  
  _newPosition = map(_temp, 0, 4435.14, 0, 2 * pi);
  _newPosition = floorf(_newPosition * 100) / 100;
  Serial.print(_motorPower);
  Serial.print(" ");
  Serial.print(_setLocation);
  Serial.print(" ");
  Serial.print(_newPosition);
  Serial.print(" ");
  Serial.println(_temp);

  if (_newPosition <= _setLocation)
  {
    if (_reverse)
    {
      _myPID.SetControllerDirection(DIRECT);
      turnClockWise(_motorPower);
    }
    else
    {
      _myPID.SetControllerDirection(DIRECT);
      turnCounterClockWise(_motorPower);
    }
  }
  else if (_newPosition > _setLocation)
  {
    if (_reverse)
    {
      _myPID.SetControllerDirection(REVERSE);
      turnCounterClockWise(_motorPower);
        Serial.println("true");

    }
    else
    {
      _myPID.SetControllerDirection(REVERSE);
      turnClockWise(_motorPower);
    }
  }
}

void PIDAngle::turnClockWise(double power)
{

  if (_reverse)
  {
    digitalWrite(_Dir, LOW);
  }
  else
  {
    digitalWrite(_Dir, HIGH);
  }
  analogWrite(_pwm_out, power);
}
void PIDAngle::turnCounterClockWise(double power)
{

  if (_reverse)
  {
    digitalWrite(_Dir, HIGH);
  }
  else
  {
    digitalWrite(_Dir, LOW);
  }
  analogWrite(_pwm_out, power);
}
void PIDAngle::stopRotate()
{
  digitalWrite(_Dir, LOW);
  analogWrite(_pwm_out, 0);
}

void PIDAngle::findBounds()
{
  int val = digitalRead(_limitSwitch);
  while (val == 0)
  {
    val = digitalRead(_limitSwitch);
    Serial.print(val);
    digitalWrite(_Dir, LOW);
    analogWrite(_pwm_out, 55);
    delay(10);
  }
  _myEnc.write(0);
  stopRotate();
}
double PIDAngle::getMotorPower()
{
  return _motorPower;
}
double PIDAngle::getSetLocation()
{
  return _setLocation;
}
double PIDAngle::getPosition()
{
  return _newPosition;
}