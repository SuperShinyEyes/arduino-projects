#include <Servo.h>

const int servo_pin = 6;
Servo servo;

void setup(){
	Serial.begin(9600);
	servo.attach(servo_pin);
	servo.write(0);
}

void loop(){
	Serial.print(servo.read());
	Serial.print("\n");
	servo.detach();
	delay(4000);
	servo.attach(servo_pin);
	delay(1000);
}