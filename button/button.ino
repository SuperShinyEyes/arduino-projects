const int buttonPin = 8;
const int ledPin = 13;
int buttonState = 0;
void setup(){
	pinMode(buttonPin, INPUT);
	pinMode(ledPin, OUTPUT);
}

void loop(){
	buttonState = digitalRead(buttonPin);
	if(buttonState == HIGH){
		digitalWrite(ledPin, HIGH);
		delay(10);
	}else{
		digitalWrite(ledPin, LOW);
		delay(10);
	}
}

void loop() {
  buttonState = DigitalRead(buttonPin);
  if(buttonState == HIGH){
		digitalWrite(led, HIGH);
		delay(100);
	}else{
		digitalWrite(led, LOW);
		delay(100);
	}
}