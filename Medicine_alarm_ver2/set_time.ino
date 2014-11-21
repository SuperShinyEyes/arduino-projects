/*
DS3231_set.pde
Eric Ayars
4/11

Test of set-time routines for a DS3231 RTC

*/

#include <DS3231.h>
#include <Wire.h>

DS3231 Clock;

byte Year = 2014;
byte Month = 1;
byte Date = 1;
byte DoW = 1;
byte Hour = 0;
byte Minute = 0;
byte Second = 0;

#define downButton 0
#define upButton 1
#define posButton 8

int upButtonState = 0;
int downButtonState = 0;
int posButtonState = 0;
int pos = 0;
byte clockBox = {Month, Date, Dow, Hour, Minute};

void setup() {
	// Start the serial port
	Serial.begin(9600);

	pinMode(downButton, INPUT);
	pinMode(upButton, INPUT);
	pinMode(posButton, INPUT);

	// Start the I2C interface
	Wire.begin();
}

void loop() {

	upButtonState = digitalRead(upButton);
	downButtonState = digitalRead(downButton);

	if(upButtonState == HIGH){

	}

	// If something is coming in on the serial line, it's
	// a time correction so set the clock accordingly.
	if (Serial.available()) {
		GetDateStuff(Year, Month, Date, DoW, Hour, Minute, Second);

		Clock.setClockMode(false);	// set to 24h
		//setClockMode(true);	// set to 12h

		Clock.setYear(Year);
		Clock.setMonth(Month);
		Clock.setDate(Date);
		Clock.setDoW(DoW);
		Clock.setHour(Hour);
		Clock.setMinute(Minute);
		Clock.setSecond(Second);

		// Test of alarm functions
		// set A1 to one minute past the time we just set the clock
		// on current day of week.
		Clock.setA1Time(DoW, Hour, Minute+1, Second, 0x0, true, 
			false, false);
		// set A2 to two minutes past, on current day of month.
		Clock.setA2Time(Date, Hour, Minute+2, 0x0, false, false, 
			false);
		// Turn on both alarms, with external interrupt
		Clock.turnOnAlarm(1);
		Clock.turnOnAlarm(2);

	}
	delay(1000);
}
