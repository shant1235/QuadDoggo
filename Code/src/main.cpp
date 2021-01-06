#include <PID_v1.h>
#include <Arduino.h>
#include <PIDAngle.h>
#include <math.h>

#include <Encoder.h>

PIDAngle myPIDAngle1(3, 2, 19, 18, 14, PI * 2, false);
PIDAngle myPIDAngle2(5, 4, 29, 28, 16, PI * 2, false);

boolean routine = true;
double x = 0.038;
double y = 0.05;
double count = 0.01;
double L1 = 0.163;
double L2 = 0.12;
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
  //double val = analogRead(15);
  //y = map(val, 0, 1023, 0.05, 0.27);
  //x = count;
  //count = count + 0.01;
  //if (count == 0.28){
  //  count = 0.01;
  //}
  //y = floorf(y * 100) / 100;
  double jointAngle2 = acos((pow(x, 2) + pow(y, 2) - pow(L1, 2) - pow(L2, 2)) / (2 * L1 * L2));
  double jointAngle1 = atan(y / x) + atan((L2 * sin(jointAngle2)) / (L1 + L2 * cos(jointAngle2))) - (PI / 3);
  //Serial.println("Y | Angle1 | Angle2 | M1 SET POS PWR | M2 SET POS PWR ");
  Serial.print(y);
  Serial.print(" | ");
  Serial.print(jointAngle1);
  Serial.print(" |");
  Serial.print(jointAngle2);
  Serial.print(" | ");
  Serial.print(myPIDAngle1.getSetLocation());
  Serial.print(" ");
  Serial.print(myPIDAngle1.getPosition());
  Serial.print(" ");
  Serial.print(myPIDAngle1.getMotorPower());
  Serial.print(" || ");
  Serial.print(myPIDAngle2.getSetLocation());
  Serial.print(" ");
  Serial.print(myPIDAngle2.getPosition());
  Serial.print(" ");
  Serial.print(myPIDAngle2.getMotorPower());
  Serial.println(" ");
    y = y + 0.01;
    if (y >= 0.27)
    {
      y = 0.05;
    }
  myPIDAngle2.moveTo(jointAngle2);
  myPIDAngle1.moveTo(jointAngle1);
  delay(100);
}
