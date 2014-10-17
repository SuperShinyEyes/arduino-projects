const int red_left = 13;
const int green_left = 12;
const int yellow_left = 11;
const int blue_left = 10;
const int switch_left = 2;

int switch_state_left = LOW;
long previousMillis = 0;

long interval = 1000;

void setup(){
  pinMode(red_left, OUTPUT);
  pinMode(green_left, OUTPUT);
  pinMode(yellow_left, OUTPUT);
  pinMode(blue_left, OUTPUT);
  pinMode(switch_left, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop(){
  /* Initially the all LEDs will light up.
   If I press a button, LEDs will blink.
   Press again, LEDs will not blink but just light up.
   */

  unsigned long currentMillis = millis();

  // Check if the button is pressed.
  if(digitalRead(switch_left) == HIGH) {
    ++switch_state_left; // Increment by 1.
    Serial.println(switch_state_left);
    delay(300);
  }

  if(switch_state_left % 2 == 0) {
    digitalWrite(red_left, HIGH);
    digitalWrite(green_left, HIGH);
    digitalWrite(yellow_left, HIGH);
    digitalWrite(blue_left, HIGH);
  }
  else{ 
    digitalWrite(red_left, HIGH);
    digitalWrite(green_left, LOW);
    digitalWrite(yellow_left, LOW);
    digitalWrite(blue_left, LOW);
    delay(100);

    /*
    if (delay_var - millis() > 100)
     do something
     delay_var = millis();
     */
    digitalWrite(red_left, LOW);
    digitalWrite(green_left, HIGH);
    digitalWrite(yellow_left, LOW);
    digitalWrite(blue_left, LOW);
    delay(100);

    digitalWrite(red_left, LOW);
    digitalWrite(green_left, LOW);
    digitalWrite(yellow_left, HIGH);
    digitalWrite(blue_left, LOW);
    delay(100);

    digitalWrite(red_left, LOW);
    digitalWrite(green_left, LOW);
    digitalWrite(yellow_left, LOW);
    digitalWrite(blue_left, HIGH);
    delay(100);
  }

}

//Function to blink LEDs
