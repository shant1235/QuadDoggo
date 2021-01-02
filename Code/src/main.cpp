#include <PID_v1.h>
#include <Arduino.h>
#include <PIDAngle.h>

#include <Encoder.h>

PIDAngle myPIDAngle(3, 2, 25, 24, 14, PI*2);
boolean routine = true;

void setup()
{
}

void loop()
{
  if (routine)
  {
    myPIDAngle.findBounds();
    routine = false;
  }
  double val = analogRead(15);
  double setLocation = map(val, 0, 1023, 0, 2 * PI);

  myPIDAngle.moveTo(setLocation);
}
