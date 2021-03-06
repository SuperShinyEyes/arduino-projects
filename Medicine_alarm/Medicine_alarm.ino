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

char ch;
int Contrast=15;
#define lcdBacklightButton 8
#define medicineButton 13
#define redLed 7
#define greenLed 13

int lcdBacklightButtonState = 0;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() 
{
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
  lcd.print("Had medicine @");

  digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, HIGH);
}

void writeTime(){
  DateTime now = RTC.now();
  lcd.setCursor(0, 0);
  lcd.print(now.hour(), DEC);
  Serial.print(now.hour(), DEC);
}

void onBoardLedDebug(){
  digitalWrite(13,LOW);
  delay(1000);
  digitalWrite(13,HIGH);
}

void loop() 
{
  DateTime now = RTC.now();
  
  lcdBacklightButtonState = digitalRead(lcdBacklightButton);

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(now.month(), DEC);
  lcd.print(".");
  lcd.print(now.day(), DEC);
  lcd.print(".");
  lcd.print(now.hour(), DEC);
  //lcd.setCursor(2, 1);
  lcd.print(":");
  //lcd.setCursor(3, 1);
  lcd.print(now.minute(), DEC);
  if(lcdBacklightButtonState == HIGH){
    //writeTime();
    Serial.println("Clicked!");
    analogWrite(9,28836);
    delay(100);
  }
  
}

void serialEvent()
{
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