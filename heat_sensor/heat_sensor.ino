
#include "DateTime/DateTime.h"
#include "DateTimeStrings/DateTimeStrings.h"

const int sensorPin = A0;
const float baselineTemp = 20.0;

void setup(){
	Serial.begin(9600);

	for(int pinNumber = 10; pinNumber < 13; pinNumber++) {
		pinMode(pinNumber, OUTPUT);
		digitalWrite(pinNumber, LOW);
	}
}

void loop(){
	int sensorVal = analogRead(sensorPin);

	Serial.print("Serial Value: ");
	Serial.print(sensorVal);

	float voltage = (sensorVal/1024.0) * 5.0;

	Serial.print(", Volts: ");
	Serial.print(voltage);
	Serial.print(", degrees C: ");

	float temperature = (voltage - .5) * 100;
	Serial.println(temperature);

	if(temperature < baselineTemp) {
		digitalWrite(10, LOW);
		digitalWrite(11, LOW);
		digitalWrite(12, LOW);
	}else if(temperature >= baselineTemp + 2 && 
		temperature < baselineTemp + 4){
		digitalWrite(10, HIGH);
		digitalWrite(11, LOW);
		digitalWrite(12, LOW);
	}else if(temperature >= baselineTemp + 4 && 
		temperature < baselineTemp + 6){
		digitalWrite(10, HIGH);
		digitalWrite(11, HIGH);
		digitalWrite(12, LOW);
	}else if(temperature >= baselineTemp + 6)	{
		digitalWrite(10, HIGH);
		digitalWrite(11, HIGH);
		digitalWrite(12, HIGH);
	}
	delay(1);
}