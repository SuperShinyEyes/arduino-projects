/*
 * MotorKnob
 *
 * A stepper motor follows the turns of a potentiometer
 * (or other sensor) on analog input 0.
 *
 * http://www.arduino.cc/en/Reference/Stepper
 * This example code is in the public domain.
 */

#include <Stepper.h>

// change this to the number of steps on your motor
//#define STEPS 48


// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
Stepper stepper(48, 8, 9, 11, 12);

// the previous reading from the analog input
int previous = 0;

void setup()
{
  Serial.begin(9600);
  // set the speed of the motor to 30 RPMs
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(,OUTPUT);
  digitalWrite(3, HIGH);
  digitalWrite(5, HIGH);
}

void loop()
{
  stepper.setSpeed(map(analogRead(0),0,1023,0,100));  
  // move a number of steps equal to the change in the
  // sensor re	ading
  stepper.step(1);

  // remember the previous value of the sensor
}