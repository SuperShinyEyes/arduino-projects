/*
This code is manipulated from 
Adafruit Arduino - Lesson 3. RGB LED
https://learn.adafruit.com/adafruit-arduino-lesson-3-rgb-leds/arduino-sketch
*/
 
int redPin = 12;
int greenPin = 14;
int bluePin = 15;
 
void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

/*
RGB LED will smoothly alter its colour from 
dark to white.
*/

void loop()
{
  int red = 0; 
  int green = 0; 
  int blue = 0;
  
  while(red < 255) {
    setColor(red, green, blue);
    // I have tried red+= 1, but 1 was too small change.
    // Because 1 is too small, the colour won't change 
    // at all.
    red += 10;
    // If you don't have any delay, you won't see any
    // colour change.
    delay(50);
  }

  while(green < 255) {
    setColor(250, green, blue);
    green += 10;
    delay(50);
  }
  
  while(blue < 255) {
    setColor(250, 250, blue);
    blue += 10;
    delay(50);
  }
  
  delay(1000);
  
  // Turn off LED
  red = 0; 
  green = 0; 
  blue = 0;
  setColor(red, green, blue);
  delay(1000);
  
} 
  

void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
