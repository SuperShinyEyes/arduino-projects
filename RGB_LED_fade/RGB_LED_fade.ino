int redPin = 11;
int greenPin = 10;
int bluePin = 9;

int redSwitch = 7;
int greenSwitch = 6;
int blueSwitch = 5;

int red = 0;
int green = 0;
int blue = 0;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(redSwitch, INPUT_PULLUP);
  pinMode(greenSwitch, INPUT_PULLUP);
  pinMode(blueSwitch, INPUT_PULLUP);
}

void loop() {
  if(digitalRead(redSwitch) == LOW) {
    red+=5;
    if(red > 255) red = 255;
  }
  
  if(digitalRead(greenSwitch) == LOW) {
    green+=5;
    if(green > 255) green = 255;
  }
  if(digitalRead(blueSwitch) == LOW) {
    blue+=5;
    if(blue > 255) blue = 255;  
  }
  
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
  delay(30);
}
