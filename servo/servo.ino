#include <Servo.h>

Servo myServo;

int const potPin = A0;
int potVal;
int angle;

void setup() {
	myServo.attach(9);
	Serial.begin(9600);
}

void loop() {
	potVal = analogRead(potPin);
	Serial.print("potVal: ");
	Serial.print(potVal);
	angle = 180 - map(potVal, 0, 1023, 0, 179);
        //angle = map(potVal, 1023, 0, 179, 0);
	Serial.print(", angle: ");
	Serial.print(angle);
        Serial.print("\n");
	myServo.write(angle);
	delay(15);
}
