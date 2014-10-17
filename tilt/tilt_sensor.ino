int const green = 7;
int const tilt = 4;
void setup(){
	pinMode(green, OUTPUT);
	pinMode(tilt, INPUT_PULLUP);
}

void loop(){
	if(digitalRead(tilt) == LOW){
		digitalWrite(green, HIGH);
		delay(15);
	}else{
		digitalWrite(green, LOW);
	}
}