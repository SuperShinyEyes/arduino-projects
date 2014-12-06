
#include <Wire.h>
#include "DS3231.h"
RTClib RTC;

int medicineHistory[2][6] = {0};

void setup(){
	Wire.begin();
	Serial.begin(9600);
}

void test(DateTime now){
	Serial.println(now.hour());
	Serial.println("works?");
	delay(2000);
}

void loop(){
	DateTime now = RTC.now();
	test(now);
	int x[6] = {2014, 12, 4, 6, 18, 30};
	int i;
	for(i = 0; i < 6; i++){
		Serial.print(x[i]);
		Serial.print(" ");
	}
	Serial.println();
	delay(3000);
}