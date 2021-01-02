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


double pi = 3.1415;
double newPosition, motorPower;
double setLocation = 0;//   avoid using pins with LEDs attached
boolean routine = true;


// Best PID : Kp = 500, Ki = 1, Kd = 25 hello
PIDAngle::PIDAngle(int CH_A, int CH_B, int Dir, int pwm_out,int limitSwitch, double leftLimit)
  : _myEnc(CH_A,CH_B)
  , _myPID(&newPosition, &motorPower, &setLocation, 1000, 0, 1, DIRECT) 
{
    

    _CH_A = CH_A; 
    _CH_B = CH_B; 
    _Dir = Dir;
    _pwm_out = pwm_out;
    _leftLimit = leftLimit;
    _setLocation = setLocation;
    _limitSwitch = limitSwitch;
    //Encoder _myEnc(_CH_A, _CH_B);
    //PID _myPID(&newPosition, &motorPower, &setLocation, 1000, 0, 1, DIRECT);
   

  pinMode(_limitSwitch, INPUT);
  _myPID.SetMode(AUTOMATIC);

  pinMode(_CH_A, INPUT);
  pinMode(_CH_B, INPUT);
  pinMode(_Dir, OUTPUT);
  pinMode(_pwm_out, OUTPUT);
  Serial.begin(19200);

}

long oldPosition  = -999;

void PIDAngle::moveTo(double setLocation) {

  //setLocation = map(val,0,1023,0,2*pi);
  if(setLocation >= _leftLimit){
    setLocation = _leftLimit;
  }
  _myPID.Compute();
  double temp = _myEnc.read();
  newPosition = map(temp,0,4435.14,0,2*pi);
  Serial.print(motorPower);
  Serial.print(" ");
  Serial.print(setLocation);
  Serial.print(" ");
  Serial.print(newPosition);
  Serial.print(" ");
  Serial.println(temp);

   if(newPosition <= setLocation ){
     _myPID.SetControllerDirection(DIRECT);

   turnCounterClockWise(motorPower);

   }else if (newPosition > setLocation){
          _myPID.SetControllerDirection(REVERSE);

  turnClockWise(motorPower);

  }

}




void PIDAngle::turnClockWise(double power) {

  digitalWrite(_Dir, LOW);
  analogWrite(_pwm_out, power);
}
void PIDAngle::turnCounterClockWise(double power) {

  digitalWrite(_Dir, HIGH);
  analogWrite(_pwm_out, power);
}
void PIDAngle::stopRotate() {
  digitalWrite(_Dir, LOW);
  analogWrite(_pwm_out, 0);
}


void PIDAngle::findBounds() {

  while (digitalRead(_limitSwitch) == LOW) {
    turnClockWise(55);
  }
  _myEnc.write(0);
  stopRotate();
}