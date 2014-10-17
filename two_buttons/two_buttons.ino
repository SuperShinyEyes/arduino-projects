int ledPin = 5;
int buttonApin = 8;
int buttonBpin = 9;

byte leds = 0;

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(buttonApin, INPUT_PULLUP);
  pinMode(buttonBpin, INPUT_PULLUP);
  
  Serial.begin(9600);
  while(!Serial);
}

void loop()
{
  if (digitalRead(buttonApin) == LOW)
  {
    Serial.println("Button A Pressed");
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
  }
  if (digitalRead(buttonBpin) == LOW)
  {
    digitalWrite(ledPin, LOW);
  }
  
}
