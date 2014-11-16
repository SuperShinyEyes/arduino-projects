/*
Library Originally added by David A Mellis
Library Modified by Limor Fried
Example added by Tom Igoe
Modified by Tom Igoe
This example is in the public domain. http://www.arduino.cc.en/Tutorial/LiquidCrystal
Contrast modification by Ahmed Murtaza Qureshi (www.engineeringlearning.blogspot.com)
*/
#include <LiquidCrystal.h>
#include <Wire.h>
#include "DS3231.h"

RTClib RTC;

char ch;
int Contrast=15;
const int buttonPin = 8;
int buttonState = 0;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() 
{
  Wire.begin();
  Serial.begin(9600);
  Serial.println("LCD test with PWM contrast adjustment");
  pinMode(13,OUTPUT);
  pinMode(buttonPin, INPUT);
  analogWrite(6,Contrast);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Had medicine @");
}

void writeTime(){
  DateTime now = RTC.now();
  lcd.setCursor(0, 0);
  lcd.print(now.hour(), DEC);
  Serial.print(now.hour(), DEC);
}

void loop() 
{
  DateTime now = RTC.now();
  
  buttonState = digitalRead(buttonPin);
  
  digitalWrite(13,LOW);
  delay(1000);
  digitalWrite(13,HIGH);
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
  if(buttonState == HIGH){
    //writeTime();
    Serial.print("Clicked!");
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