const int groundpin = 18;             // analog input pin 4 -- ground
const int powerpin = 19;              // analog input pin 5 -- voltage
const int xpin = A3;                  // x-axis of the accelerometer
const int ypin = A2;                  // y-axis
const int zpin = A1;                  // z-axis (only on 3-axis models)

void setup()
{
  // initialize the serial communications:
  Serial.begin(1200);
  
  // Provide ground and power by using the analog inputs as normal
  // digital pins.  This makes it possible to directly connect the
  // breakout board to the Arduino.  If you use the normal 5V and
  // GND pins on the Arduino, you can remove these lines.
  pinMode(groundpin, OUTPUT);
  pinMode(powerpin, OUTPUT);
  digitalWrite(groundpin, LOW); 
  digitalWrite(powerpin, HIGH);
}

void loop()
{
  int x = analogRead(xpin);
  int y = analogRead(ypin);
  int z = analogRead(zpin);
  float zero_G = 512.0;
  float scale = 102.3;
  
  // print the sensor values:
  Serial.print(((float)x - zero_G)/scale);
  // print a tab between values:
  Serial.print("\t");
  Serial.print(((float)y - zero_G)/scale);
  // print a tab between values:
  Serial.print("\t");
  Serial.print(((float)z - zero_G)/scale);
  Serial.println();
  // delay before next reading:
  delay(1000);
}
