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

#define lcdBacklightButton 8
#define medicineButton 10
#define redLed 7
#define greenLed 13

bool isLcdOn = false;
bool tookMedicine = false;
char ch;
int Contrast=15;

int lcdBacklightButtonState = 0;
int medicineButtonState = 0;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  Wire.begin();
  Serial.begin(9600);
  Serial.println("LCD test with PWM contrast adjustment");
  pinMode(greenLed,OUTPUT);  // For debugging. onBoardLedDebug()
  pinMode(redLed,OUTPUT);
  pinMode(lcdBacklightButton, INPUT);
  analogWrite(6,Contrast);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Hi!");

  //digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, HIGH);
}

char *numberToMonth(int m){
  switch (m) {
    case 1:
      return "Jan";
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
  switch (d) {
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

    case 7:
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

  // set the cursor to column 0, line 0
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);
  lcd.print("Took medicine @");
  // Display time
  lcd.setCursor(0, 1);
  //lcd.print(now.month(), DEC);
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
    Serial.println("False!");
    Serial.println(now.minute());
    delay(10);
    return false;
  }
}

void loop() 
{ 
  // If 00:00, reset. red on and green off
  if(isNewDay()){
    tookMedicine = false;
    digitalWrite(greenLed, LOW);
    digitalWrite(redLed, HIGH);
  }

  medicineButtonState = digitalRead(medicineButton);
  
  if(medicineButtonState == HIGH){
    if(tookMedicine == false){
      tookMedicine = true;
      writeTime();
      digitalWrite(redLed, LOW);
      digitalWrite(greenLed, HIGH);
    }
    analogWrite(9,28836);  // Brightens LCD
    delay(6000);
    analogWrite(9,0);
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