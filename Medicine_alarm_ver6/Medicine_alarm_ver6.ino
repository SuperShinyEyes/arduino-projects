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
Purpose: To remind that the user takes his medicine regularly.

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
#include <stdarg.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include "DS3231.h"

RTClib RTC;
DS3231 Clock;
// Button pins
#define upButton 3
#define downButton 2
#define lcdBacklightButton 8
#define medicineButton 10
// LED pins
#define redLed 7
#define greenLed 13

// Constants
char ch;
int Contrast=15;

int lcdBacklightButtonState = 0;
int medicineButtonState = 0;

int pressedTime = 0;    // For changing time, hold it down till you enter the change mode
int lcdBacklightOnTime = 0;
int ledControlArg = 0;
int medicineHistory[2][5] = {0};

bool changeTimeDone = false;
bool yesterdayMedicine = true;  // Did you take your medicine last night?
bool todayMedicine = false;     // Have you taken your medicine today?
bool isNewDay_ = false;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, A3, A2);


void setup() {
	//DateTime now = RTC.now();
	//today = now.day();
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

	lcd.print("Medicin Alarm");
	lcd.setCursor(0, 1);
	lcd.print("by Seyoung Park");
	analogWrite(9,28836);
  delay(2000);
}

char *numberToMonth(int m){
	//Serial.print("m original: ");
	//Serial.println(m);
	switch (m) {
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

	    case 12:
	      return "Dec";
	      break;

	    default:
	      return "???";
	      break;
	  }
}

char *numberToDay(int d){
  //Serial.println(d);
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

int ledControl(int t){
	/* 1.Red light blinking
     *   Since 22:00 when you haven't taken your medicine.
     *   Or until you take medicine of yesterday's
     * 2.Red light
     *   Until 21:59 when you haven't taken your medicine.
     * 3.Green light
     *   You have taken your medicine yesterday and today 
	 */
	DateTime now = RTC.now();
	Serial.print("ledcontrol hour: ");
	Serial.println(now.hour());

	// 1.Red light blinking
	if( (yesterdayMedicine == false) &&  (t < 30) ){
		digitalWrite(redLed, HIGH);
		return (t + 1) % 60;
	}else if(yesterdayMedicine == false){
		digitalWrite(redLed, LOW);
		return (t + 1) % 60;
	}else if(todayMedicine == false && now.hour() >= 22 && t < 30){
		digitalWrite(redLed, HIGH);
		return (t + 1) % 60;
	}else if(todayMedicine == false && now.hour() >= 22){
		digitalWrite(redLed, LOW);
		return (t + 1) % 60;
	}
	// 2.Red light 
	else if(todayMedicine == false){
		digitalWrite(redLed, HIGH);
		return 0;
	}
	// 3.Green light
	else{
		digitalWrite(redLed, LOW);
		digitalWrite(greenLed, HIGH);
		return 0;
	}
}

/* Currently medicein taken time history feature doesn't do much.
 * Initial idea was for the case when someone accidentally presses "tookMedicine"
 * button when he hasn't actually taken the medicine yet.
 * However I figured out that in that case he can simply click the reset button.
 * Now medicineHistory is only used for showing the medicine took time 
 * after modifying the clock.
 */
// If yesterday => 0, if today => 1
void saveMedicineHistory(int yesterdayOrToday){
	DateTime now = RTC.now();
	int i;

	// Update medicineHistory when saving today's history
	if(yesterdayOrToday == 1){
		for(i = 0; i < 5; i++){
			medicineHistory[0][i] = medicineHistory[1][i];
		}
	}
	
	medicineHistory[yesterdayOrToday][0] = now.month();
	medicineHistory[yesterdayOrToday][1] = now.day();
	medicineHistory[yesterdayOrToday][2] = now.dayOfWeek();
	medicineHistory[yesterdayOrToday][3] = now.hour();
	medicineHistory[yesterdayOrToday][4] = now.minute();

	// Debugging purpose
	Serial.println("saving works!");
	for(i = 0; i < 5; i++){
		Serial.print(medicineHistory[yesterdayOrToday][i]);
		Serial.print(" ");
	}Serial.println();
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
  uint8_t h = now.hour();
  if(h < 10){
    lcd.print(0); // For consistent alignment, print time in two-digit
  }
  lcd.print(h, DEC);
  lcd.print(":");
  uint8_t m = now.minute();
  if(m < 10){
    lcd.print(0); // For consistent alignment
  }
  lcd.print(m, DEC);
  lcd.print(" ");
}
int *getTimeArray(){
	DateTime now = RTC.now();
	static int timeArray[5] = {0};
	timeArray[0] = now.month();
	timeArray[1] = now.day();
	timeArray[2] = now.dayOfWeek();
	timeArray[3] = now.hour();
	timeArray[4] = now.minute();
	Serial.print("Hour: ");  // Debugging purpose
	Serial.println(timeArray[3]);
	return timeArray;
}

// March => return 31, 2014 Feb. => 28, 2016 Feb. => 29
int getDateThreshold(){
	DateTime now = RTC.now();
	int m = now.month();
	int y = now.year();
	Serial.print("m original: ");
	Serial.println(now.month());
	int month31day[7] = {1, 3, 5, 7, 8, 10, 12};
	int i;
	if(m == 2 && y % 4 == 0){return 29;}
	else if(m == 2){return 28;}
	else if(m != 2){
		for(i = 0; i < 7; i++){	if(month31day[i] == m){return 31;} }
	}
	else{ return 30; }
}

void change(int currentTime, int threshold, char *timeUnit, void (DS3231::*setFunction)(byte), DS3231& c){
	int i = currentTime;
	lcd.setCursor(0,0);
	lcd.print("Set ");
	lcd.print(timeUnit);
	while(digitalRead(medicineButton) == HIGH){
		if(!digitalRead(upButton)){
			// Hour and Minute can be 00 but other timeUnit can't be 0s.
			if(i == 23 && threshold == 23){ i = 0; Serial.println("jump!");}
			else if(i < 59){ i = i % threshold + 1; Serial.println("norm");}
			else{ i = 0;}
			Serial.print("i: ");
			Serial.println(i);
			(c.*setFunction)(i);
			delay(200); // Don't make it smaller than 200. It might malfunction
		}else if(!digitalRead(downButton)){
			i--;
			if((threshold == 59 || threshold == 23) && i == 0){ i = 0; }
			else if(i <= 0){i = threshold;}
			Serial.print("i: ");
			Serial.println(i);			
			(c.*setFunction)(i);
			delay(200);
		}
		writeTime();
	}
	// Keep this delay long enough. 
	// Otherwise the next timeUnit modification will be skipped.
	delay(300);  
}

void changeTime(){
	int *timeArray = getTimeArray();
	change(timeArray[0], 12, "month", &DS3231::setMonth, Clock);
	// Number of days is different depending on months
	// Feb => 28 or 29. March => 31.
	int dateThreshold = getDateThreshold();
	change(timeArray[1], dateThreshold, "date ", &DS3231::setDate, Clock);
	change(timeArray[2], 7, "day  ", &DS3231::setDoW, Clock);
	change(timeArray[3], 23, "hour ", &DS3231::setHour, Clock);
	change(timeArray[4], 59, "minute", &DS3231::setMinute, Clock);
}

bool isNewDay(){
  DateTime now = RTC.now();
  // Ideally now.second() == 0 can be used instead of isNewDay_
  // However since there are too many delays, 0 second might not be captured
  if(now.hour() == 0 && now.minute() == 0 && isNewDay_ == false){
    Serial.println("Newday!!");
    isNewDay_ = true;
    return true;
  }else{
  	if(now.minute() > 0){ isNewDay_ = false; }
    return false;
  }
}

void writeTimeOnLcd(){
	// set the cursor to column 0, line 0
	// (note: line 1 is the second row, since counting begins with 0):
	ledControl(0);
	writeTime();
	delay(5000);
	lcd.setCursor(0, 0);
	lcd.print("Took medicine @");  // To erase "Yesterday's!"
}

void tookMedicine(){
	analogWrite(9,28836);  // Brightens LCD
	/* Case when you haven't taken a medicine yesterday. 
	 * Probably @ 00:30 or 08:00 when you just woke up. 
	 * LED is still red though because you still need to take today's medicine.
	 */
	if(yesterdayMedicine == false){
		saveMedicineHistory(0);
		yesterdayMedicine = true; 
		lcd.setCursor(0, 0);
		lcd.print("Yesterday's!");
		writeTimeOnLcd(); 
	}
	else if(todayMedicine == false){
		saveMedicineHistory(1);
		todayMedicine = true;
		lcd.setCursor(0, 0);
		lcd.print("Took medicine @"); 
		writeTimeOnLcd();
	}
	Serial.print("Yesterday: ");
	Serial.print(yesterdayMedicine);
	Serial.print("  Today: ");
	Serial.println(todayMedicine);
    delay(5000);
    analogWrite(9,0);
}

// To be used after modifying the clock.
// The time data is used from medicineHistory
void writeLastTimeOnLCD(){
	lcd.setCursor(0, 0);
	lcd.print("Took medicine @    ");
	int yesterdayOrToday;
	// Determine which history to be used.        
	if(todayMedicine == false){ yesterdayOrToday = 0; }
	else{ yesterdayOrToday = 1; }

	if(medicineHistory[yesterdayOrToday][0] == 0){
		lcd.setCursor(0, 1);
		lcd.print("Not yet        ");	
	}else{
	char *monthChar = numberToMonth(medicineHistory[yesterdayOrToday][0]);
	char *dayChar = numberToDay(medicineHistory[yesterdayOrToday][2]);

	// Display time
	lcd.setCursor(0, 1);
	lcd.print(monthChar);
	lcd.print(".");
	lcd.print(medicineHistory[yesterdayOrToday][1]);
	lcd.print(".");
	lcd.print(dayChar);
	lcd.print(" ");
	
	if(medicineHistory[yesterdayOrToday][3] < 10){
	lcd.print(0);
	}
	lcd.print(medicineHistory[yesterdayOrToday][3]);
	lcd.print(":");
	int m = medicineHistory[yesterdayOrToday][4];
	if(m < 10){
	lcd.print(0);
	}
	lcd.print(m);
	lcd.print(" ");
	}
}

void loop() { 
  // Reset at 00:00. red on and green off
  if(isNewDay()){
  	yesterdayMedicine = todayMedicine;
    todayMedicine = false;
    digitalWrite(greenLed, LOW);
  }
  ledControlArg = ledControl(ledControlArg);

  medicineButtonState = !digitalRead(medicineButton);
  lcdBacklightButtonState = !digitalRead(lcdBacklightButton);

  if(medicineButtonState == HIGH){ tookMedicine(); }
  
  if(lcdBacklightOnTime > 0){
  	lcdBacklightOnTime--;
  }else{
  	analogWrite(9,0);
  }
  
  if(lcdBacklightButtonState == HIGH){
  	analogWrite(9,28836);
  	lcdBacklightOnTime = 150;
  	pressedTime++;
  	if(pressedTime > 100){
  		lcd.setCursor(0, 0);
  		lcd.print("                ");
  		changeTime();
  		writeLastTimeOnLCD();  // To refresh LCD
  		pressedTime = 0;
  		delay(100);
  	}
    analogWrite(9,28836);  // Brightens LCD
  }else if(lcdBacklightButtonState == LOW){
  	pressedTime = 0;
  }
}
