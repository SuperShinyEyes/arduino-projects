/*
Library Originally added by David A Mellis
Library Modified by Limor Fried
Example added by Tom Igoe
Modified by Tom Igoe
This example is in the public domain. http://www.arduino.cc.en/Tutorial/LiquidCrystal
Contrast modification by Ahmed Murtaza Qureshi (www.engineeringlearning.blogspot.com)
*/

/*
Medicine Alarm vers.1
Created by Seyoung Park
Purpose: To remind that the user takes his medicine correctly.

--Explanation by example--
You take medicine once a day.
A day starts at 00:00 and it ends at 23:59.
Let's say you take medicine at 22:00.
Until 21:59 Red LED is on, meaning you haven't taken medicine yet.

At 22:00 you take your medicine and push a button meaning that you took.
Red LED goes off and Green LED goes on.
LCD screen brightens and says
"Took medicine 
Nov 19.Wed hh:mm"
After 5 sec, LCD dims.

At 24:00 new day starts and Red LED goes on.
*/
#include <LiquidCrystal.h>
#include <Wire.h>
#include "DS3231.h"

RTClib RTC;
DS3231 Clock;
// Button pins
#define upButton 3
#define downButton 3
#define lcdBacklightButton 8
#define medicineButton 10
// LED pins
#define redLed 7
#define greenLed 13

// Constants
bool tookMedicine = false;
char ch;
int Contrast=15;

int lcdBacklightButtonState = 0;
int medicineButtonState = 0;

int pressedTime = 0;
int lcdBacklightOnTime = 0;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, A3, A2);


void setup() {
  Wire.begin();
  Serial.begin(9600);
  
  pinMode(greenLed,OUTPUT);  // For debugging. onBoardLedDebug()
  pinMode(redLed,OUTPUT);
  // Buttons
  pinMode(lcdBacklightButton, INPUT_PULLUP);
  pinMode(medicineButton, INPUT_PULLUP);
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);

  analogWrite(6,Contrast);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Hi!");

  //digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, HIGH);
}

char *numberToMonth(int m){
	switch (m % 12) {
	    case 1:
	      return "Jan";
	      break;

	    case 2:
	      return "Feb";
	      break;

	    case 3:
	      return "Mar";
	      break;

	    case 4:
	      return "Apr";
	      break;

	    case 5:
	      return "May";
	      break;

	    case 6:
	      return "Jun";
	      break;

	    case 7:
	      return "Jul";
	      break;

	    case 8:
	      return "Aug";
	      break;

	    case 9:
	      return "Sep";
	      break;

	    case 10:
	      return "Oct";
	      break;

	    case 11:
	      return "Nov";
	      break;

	    case 0:
	      return "Dec";
	      break;

	    default:
	      return "???";
	      break;
	  }
}

char *numberToDay(int d){
  Serial.println(d);
  switch (d % 7) {
    case 1:
      return "Mon";
      break;

    case 2:
      return "Tue";
      break;

    case 3:
      return "Wed";
      break;

    case 4:
      return "Thu";
      break;

    case 5:
      return "Fri";
      break;

    case 6:
      return "Sat";
      break;

    case 0:
      return "Sun";
      break;

    default:
      return "???";
      break;
  }
}

void writeTime(){
  DateTime now = RTC.now();

  char *monthChar = numberToMonth(now.month());
  char *dayChar = numberToDay(now.dayOfWeek());

  // Display time
  lcd.setCursor(0, 1);
  lcd.print(monthChar);
  lcd.print(".");
  lcd.print(now.day(), DEC);
  lcd.print(".");
  lcd.print(dayChar);
  lcd.print(" ");
  int h = now.hour();
  if(h < 10){
    lcd.print(0);
  }
  lcd.print(h, DEC);
  lcd.print(":");
  int m = now.minute();
  if(m < 10){
    lcd.print(0);
  }
  lcd.print(m, DEC);
}
int *getTimeArray(DateTime now){
	static int timeArray[5] = {0};
	timeArray[0] = now.month();
	timeArray[1] = now.day();
	timeArray[2] = now.dayOfWeek();
	timeArray[3] = now.hour();
	timeArray[4] = now.minute();
	
	return timeArray;
}

void changeYear(){
	
}

void changeMonth(DateTime now, int m){
	int i = 0;
	lcd.setCursor(0,5);
	lcd.print("month");
	while(digitalRead(lcdBacklightButton) == HIGH){
		if(!digitalRead(upButton)){
			i++;
			Clock.setMonth(m+i);
			delay(300);
		}
		writeTime();
	}
}

void changeTime(){
	
	Clock.setClockMode(false);	// set to 24h
	DateTime now = RTC.now();
	int *timeArray = getTimeArray(now);
	changeMonth(now, timeArray[0]);
	/*
	int i;
	for(i = 0; i < 5; i++){

		Serial.println("time!");
		Serial.println(timeArray[i]);
	}
	*/
	
	/*

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


	delay(1000);
	*/
}

void onBoardLedDebug(){
  digitalWrite(13,LOW);
  delay(1000);
  digitalWrite(13,HIGH);
}

bool isNewDay(){
  DateTime now = RTC.now();
  if(now.hour() == 0 && now.minute() == 0){
    Serial.println("Newday!!");
    delay(10);
    return true;
  }else{
    //Serial.println("False!");
    //Serial.println(now.minute());
    delay(10);
    return false;
  }
}

void medicineButtonStateIsHigh(){
	if(tookMedicine == false){
      tookMedicine = true;
      // set the cursor to column 0, line 0
	  // (note: line 1 is the second row, since counting begins with 0):
	  lcd.setCursor(0, 0);
	  lcd.print("Took medicine @");
      writeTime();
      digitalWrite(redLed, LOW);
      digitalWrite(greenLed, HIGH);
    }
    analogWrite(9,28836);  // Brightens LCD
    delay(6000);
    analogWrite(9,0);
}

void loop() { 
  // If 00:00, reset. red on and green off
  if(isNewDay()){
    tookMedicine = false;
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
  }

  medicineButtonState = !digitalRead(medicineButton);
  lcdBacklightButtonState = !digitalRead(lcdBacklightButton);

  if(medicineButtonState == HIGH){
    medicineButtonStateIsHigh();
  }
  if(lcdBacklightOnTime > 0){
  	analogWrite(9,28836);
  	lcdBacklightOnTime--;
  }else{
  	//lcdBacklightOnTime = 0;
  	analogWrite(9,0);
  }
  if(lcdBacklightButtonState == HIGH){
  	lcdBacklightOnTime = 500;
  	pressedTime++;
  	if(pressedTime > 100){
  		while(digitalRead(medicineButton)){
	  		lcd.setCursor(0, 1);
	  		lcd.print("Yeah babe");
	  		changeTime();
  		}
  		lcd.setCursor(0, 1);
		lcd.print("          ");
		delay(100);
		digitalRead(medicineButton);
  	}
    analogWrite(9,28836);  // Brightens LCD
    //delay(6000);
    //analogWrite(9,0);
  }else if(lcdBacklightButtonState == LOW){
  	pressedTime = 0;
  	//analogWrite(9,0);
  }
}

void serialEvent(){
     if (Serial.available())
  {
    ch= Serial.read();
    if(ch=='A' && Contrast<255)
    {
      Contrast=Contrast+1;
    }
    if(ch=='B' && Contrast>0)
    {
      Contrast=Contrast-1;
    }
        if(ch=='N')
    {
      analogWrite(9,28836);
    }
       if(ch=='F')
    {
      analogWrite(9,0);
    }
    analogWrite(6,Contrast);
    Serial.println("Current contrast");
    Serial.println(Contrast);
  }
}