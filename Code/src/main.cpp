#include <PID_v1.h>
#include <Arduino.h>
#include <PIDAngle.h>
#include <math.h>

#include <Encoder.h>

PIDAngle myPIDAngle1(3, 2, 19, 18, 14, PI / 2);
PIDAngle myPIDAngle2(5, 4, 29, 28, 16, PI);

boolean routine = true;
double x, y = 0.01;
double L1 = 15.5/100;
double L2 = 13.3/100;
void setup()
{
}

void loop()
{
  if (routine)
  {
    myPIDAngle1.findBounds();
    myPIDAngle2.findBounds();
    routine = false;
  }
  double val = analogRead(15);
  y = map(val, 0, 1023, 0.1, 0.28);
  double jointAngle2 = -1 * cosh((x * x + y * y - L1 * L1 - L2 * L2) / (2 * L1 * L2));
  double jointAngle1 = tanh(y / x) + tanh((L2 * sin(jointAngle2)) / (L1 + L2 * cos(jointAngle2)));
  Serial.print(y);
  Serial.print(" ");
  Serial.print(jointAngle1);
  Serial.print(" ");
  //Serial.print(2*PI + jointAngle2);
  Serial.print(" ");
  Serial.print(myPIDAngle1.getMotorPower());
  Serial.print(" ");
  //Serial.print(myPIDAngle2.getMotorPower());
  Serial.println(" ");
  myPIDAngle2.moveTo(2*PI +jointAngle2);
  //myPIDAngle1.moveTo(jointAngle1);

}
