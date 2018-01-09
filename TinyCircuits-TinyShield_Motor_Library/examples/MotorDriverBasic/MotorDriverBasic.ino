//-------------------------------------------------------------------------------
//  TinyCircuits Dual Motor Driver Basic Example
//  Last Updated 30 July 2015
//  
//  This example code shows basic usage of the ASD2302 Dual Motor Driver TinyShield.
//  The library intance is created with the hardware address of the motor driver
//  (up to 4 boards/8 motors) and then intialized with begin(maximum PWM value).
//  The Dual Motor Driver has 16 bit PWM output capability, but keep in mind the
//  output frequency is low when using a large timer value- great for some things,
//  like driving servos. To drive the motors, use setMotor(motor, value) to set
//  motor 1 or 2 to -maxPWM to +maxPWM.
//
//  The board uses the ATtiny841 microcontroller and has direct register access-
//  so just about any of the internal peripherals could be put to use.
//
//  Written by Ben Rose, TinyCircuits http://Tiny-Circuits.com
//
//-------------------------------------------------------------------------------


#include <Wire.h>
#include <MotorDriver.h>

MotorDriver motor(0);//value passed is the address- remove resistor R1 for 1, R2 for 2, R1 and R2 for 3

int maxPWM=10000;
int steps=100;
int stepSize=maxPWM/steps;

void setup(){
  Serial.begin(9600);
  Wire.begin();
  //The value passed to begin() is the maximum PWM value, which is 16 bit(up to 65535)
  //This value also determines the output frequency- by default, 8MHz divided by the maxPWM value
  if(motor.begin(maxPWM)){
    Serial.println("Motor driver not detected!");
    while(1);
  }
  //The failsafe turns off motors if a command is not sent in a certain amount of time.
  //Failsafe is set in milliseconds- comment or set to 0 to disable
  motor.setFailsafe(1000);
}

void loop(){
  int i;
  for(i=-maxPWM;i<maxPWM;i+=stepSize){
    delay(10);
    motor.setMotor(1,i);
    motor.setMotor(2,i);
  }
  for(i=maxPWM;i>-maxPWM;i-=stepSize){
    delay(10);
    motor.setMotor(1,i);
    motor.setMotor(2,i);
  }
}
