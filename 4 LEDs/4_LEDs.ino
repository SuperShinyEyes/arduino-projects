const int red_right = 7;
const int green_right = 6;
const int yellow_right = 5;
const int blue_right = 4;

const int switch_right = 3;
int switch_state_right = LOW;

void setup(){  
  pinMode(red_right, OUTPUT);
  pinMode(green_right, OUTPUT);
  pinMode(yellow_right, OUTPUT);
  pinMode(blue_right, OUTPUT);
  pinMode(switch_right, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop(){
	if(digitalRead(switch_right) == LOW) {
		digitalWrite(red_right, HIGH);
	    digitalWrite(green_right, HIGH);
	    digitalWrite(yellow_right, HIGH);
	    digitalWrite(blue_right, HIGH);
	}
	else{
		digitalWrite(red_right, LOW);
	    digitalWrite(green_right, LOW);
	    digitalWrite(yellow_right, LOW);
	    digitalWrite(blue_right, LOW);
	}
}