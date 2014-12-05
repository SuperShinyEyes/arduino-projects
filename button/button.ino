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

/*
Dr. Ayars, thank you very much for your contribution. 
I have one question. How can I use dayOfWeek?
It seems like I can set it but cannot access it like, now.dayOfWeek()
I checked the header file and cpp file and it seems like it's not just using it.
Could you tell me how I could use it?
Thank you sir!
*/