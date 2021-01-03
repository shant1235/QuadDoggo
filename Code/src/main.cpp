#include <PID_v1.h>
#include <Arduino.h>
#include <PIDAngle.h>
#include <math.h>

#include <Encoder.h>

PIDAngle myPIDAngle1(3, 2, 19, 18, 14, PI*2);
PIDAngle myPIDAngle2(5, 4, 29, 28, 16, PI*2);

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
    //myPIDAngle2.findBounds();
    routine = false;
  }
  double val = analogRead(15);
  y = map(val, 0, 1023, 0, 0.28);
  y = floorf(y * 100) / 100;
  double jointAngle2 = cosh((x * x + y * y - L1 * L1 - L2 * L2) / (2 * L1 * L2));
  double jointAngle1 = tanh(y / x) + tanh((L2 * sin(jointAngle2)) / (L1 + L2 * cos(jointAngle2))) - (PI/3);
  //Serial.println("Y | Angle1 | Angle2 | M1 SET POS PWR | M2 SET POS PWR ");
  Serial.print(y);
  Serial.print(" | ");
   Serial.print(jointAngle1);
   Serial.print(" |");
  // Serial.print(jointAngle2);
  // Serial.print(" | ");
   Serial.print(myPIDAngle1.getSetLocation());
   Serial.print(" ");
   Serial.print(myPIDAngle1.getPosition());
   Serial.print(" ");
   Serial.println(myPIDAngle1.getMotorPower());
  // Serial.print(" || ");
  // Serial.print(myPIDAngle2.getSetLocation());
  // Serial.print(" ");
  // Serial.print(myPIDAngle2.getPosition());
  // Serial.print(" ");
  // Serial.print(myPIDAngle2.getMotorPower());
  // Serial.println(" ");
  //myPIDAngle2.moveTo(y);
  myPIDAngle1.moveTo(jointAngle1);

}
