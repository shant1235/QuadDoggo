
#include "Arduino.h"
#include "PID_v1.h"
#include "Encoder.h"

#ifndef PIDAngle_h
#define PIDAngle_h


class PIDAngle
{
public:
    PIDAngle(int CH_A, int CH_B, int Dir, int pwm_out,int limitSwitch, double leftLimit);
    void moveTo(double setLocation);
    void turnClockWise(double power);
    void turnCounterClockWise(double power);
    void stopRotate();
    void findBounds();
    double getMotorPower();

private:
    int _CH_A ; 
    int _CH_B; 
    int _Dir;
    int _pwm_out;
    int _limitSwitch ; 
    double _leftLimit;
    double _setLocation;
    PID _myPID;
    Encoder _myEnc;

};

#endif