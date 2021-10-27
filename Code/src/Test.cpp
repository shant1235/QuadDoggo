#include <Arduino.h>

void setup2()
{
    pinMode(14,INPUT);
}
void loop2()
{
    Serial.print(digitalRead(14));
  delay(100);
}
