int red_1 = 5;
int red_2 = 4;
int green = 3;
int buttonPin = 2;

void setup(){
  pinMode(red_1, OUTPUT);
  pinMode(red_2, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop(){
  if(digitalRead(buttonPin) == HIGH){
    digitalWrite(red_1, HIGH);
    digitalWrite(red_2, HIGH);
    digitalWrite(green, HIGH);
  }else{
    digitalWrite(red_1, LOW);
    digitalWrite(red_2, LOW);
    digitalWrite(green, LOW);
  }
}
