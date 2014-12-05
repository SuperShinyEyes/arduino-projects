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
#define lcd_clockButton 8

int upButtonState = 0;
int downButtonState = 0;
int lcd_clockButtonState = 0;  // Controls both lcd and clock
int clockBoxIndex = 0;
byte clockBox = {Month, Date, Dow, Hour, Minute};

LiquidCrystal lcd(12, 11, 5, 4, A3, A2);

void setup() {
	// Start the serial port
	Serial.begin(9600);

	pinMode(downButton, INPUT);
	pinMode(upButton, INPUT);
	pinMode(posButton, INPUT);
	analogWrite(6,Contrast);
	lcd.begin(16, 2);
	lcd.print("Hi!");
	// Start the I2C interface
	Wire.begin();
}

void changeTime(){
	while(clockBoxIndex < 5){
		upButtonState = digitalRead(upButton);
		downButtonState = digitalRead(downButton);
		lcd_clockButtonState = digitalRead(lcd_clockButton);
		if(upButtonState == HIGH){
			clockBox[clockBoxIndex]++;
		}else if(downButtonState == HIGH){
			clockBox[clockBoxIndex]--;
		}else if(lcd_clockButtonState== HIGH){
			clockBoxIndex++;
		}

		Clock.setClockMode(false);
		switch(clockBoxIndex){
			case 0:
				Clock.setMonth(Month)	
		}
	}
}

void loop() {

	lcd_clockButtonState = digitalRead(lcd_clockButton);

	if(lcd_clockButtonState == HIGH){
		analogWrite(9,28836);
		delay(2000);
		if(lcd_clockButtonState == HIGH){
			changeTime();
		}
		analogWrite(9,0);
	}

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
