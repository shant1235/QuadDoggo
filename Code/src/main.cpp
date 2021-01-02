#include <PID_v1.h>
#include <Arduino.h>


#include <Encoder.h>

void turnClockWise(double power);
void turnCounterClockWise(double power);
void setLimitSwitchA();
void MotorTurn(double power);
void stopRotate();
void setPositionA();
void findBounds();

#define LIMIT_SWITCHA 14
#define LIMIT_SWITCHB A17
#define CHANNEL_A 3
#define CHANNEL_B 2
#define DIR_A 25
#define PWM_A 24

Encoder myEnc(CHANNEL_A, CHANNEL_B);

volatile byte limitSwitchA, limitSwitchB = LOW;
volatile int aState, bState = 0;
double pi = 3.1415;
int topBoundA ;
int lowerBoundA;
double newPosition, motorPower;
double setLocation = 3.14;//   avoid using pins with LEDs attached
boolean routine = true;
char rx_byte = 0;
String rx_str = "";

PID myPID(&newPosition, &motorPower, &setLocation, 500, 1, 25, DIRECT);
// Best PID : Kp = 500, Ki = 1, Kd = 25 hello
void setup() {
  pinMode(LIMIT_SWITCHA, INPUT);
  myPID.SetMode(AUTOMATIC);

  pinMode(CHANNEL_A, INPUT);
  pinMode(CHANNEL_B, INPUT);



  pinMode(DIR_A, OUTPUT);
  pinMode(15, INPUT);
  myPID.SetMode(AUTOMATIC);

  pinMode(PWM_A, OUTPUT);
  Serial.begin(19200);


}

long oldPosition  = -999;

void loop() {
  if(routine){
    findBounds();
    routine=false;
  }
  double val = analogRead(15);
  setLocation = map(val,0,1023,0,2*pi);
  myPID.Compute();
  double temp = myEnc.read();
  newPosition = map(temp,0,4435.14,0,2*pi);
  Serial.print(motorPower);
  Serial.print(" ");
  Serial.print(setLocation);
  Serial.print(" ");
  Serial.println(newPosition);

   if(newPosition <= setLocation ){
     myPID.SetControllerDirection(DIRECT);

   turnCounterClockWise(motorPower);

   }else if (newPosition > setLocation){
          myPID.SetControllerDirection(REVERSE);

  turnClockWise(motorPower);

  }

}




void turnClockWise(double power) {

  digitalWrite(DIR_A, LOW);
  analogWrite(PWM_A, power);
}
void turnCounterClockWise(double power) {

  digitalWrite(DIR_A, HIGH);
  analogWrite(PWM_A, power);
}
void stopRotate() {
  digitalWrite(DIR_A, LOW);
  analogWrite(PWM_A, 0);
}
void setLimitSwitchA() {

  myEnc.write(0);
  Serial.println("hit");

}

void MotorTurn(double power) {
  if (power == 0) {
    stopRotate();
  } else if (power >= 0 && power <= 255) {
    turnClockWise(power);
  } else if (power <= 0 && power >= -255) {
    turnCounterClockWise(power);
  }
}

void setPositionA() {
  newPosition = myEnc.read();
  Serial.println(newPosition);
}

void findBounds() {

  while (digitalRead(LIMIT_SWITCHA) == LOW) {
    turnClockWise(55);


  }
  myEnc.write(0);
  stopRotate();
}
