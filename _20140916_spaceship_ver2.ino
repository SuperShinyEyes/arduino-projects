int red_1 = 5;
int red_2 = 4;
int green = 3;
int switchState = 0;

void setup(){
  pinMode(red_1, OUTPUT);
  pinMode(red_2, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(2, INPUT);
}

void loop(){
  switchState = digitalRead(2);
  
  if(switchState == LOW){
    digitalWrite(red_1, HIGH);
    digitalWrite(red_2, LOW);
    digitalWrite(green, LOW);
  }else{
    digitalWrite(red_1, LOW);
    digitalWrite(red_2, HIGH);
    digitalWrite(green, LOW);
    
    delay(250);
    
    digitalWrite(red_2, HIGH);
    digitalWrite(green, HIGH);
    
    delay(50);
  }
}
