const int red_right = 7;
const int green_right = 6;
const int yellow_right = 5;
const int blue_right = 4;

const int switch_right = 3;

int blink_time_right = 0;
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
  /* Initially the all LEDs will light up.
   If I press a button, LEDs will blink.
   Press again, LEDs will not blink but just light up.
   */

  // Check if the button is pressed.
  
  if(digitalRead(switch_right) == HIGH) {
    ++switch_state_right; // Increment by 1.
    Serial.println(switch_state_right);
    delay(10);
  }

 if(switch_state_right % 2 == 0) {
    digitalWrite(red_right, HIGH);
    digitalWrite(green_right, HIGH);
    digitalWrite(yellow_right, HIGH);
    digitalWrite(blue_right, HIGH);
  } else{
    // Reset blink_time when it's over the cycle
    if(blink_time_right >= 20000) {blink_time_right = 0;}
    
    blinker(red_right, green_right, yellow_right, 
    blue_right, blink_time_right);
    blink_time_right++;
  }
 

}

// Function to blink LEDs
// "time" tells which LED to blink
void blinker(const int red, const int green, const int yellow, 
const int blue, int time) {
  
  if(time < 5000) {
  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(blue, LOW);
  }
  
  else if(time >= 5000 && time < 10000) {
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  digitalWrite(yellow, LOW);
  digitalWrite(blue, LOW);
  }

  else if(time >= 10000 && time < 15000) {
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(yellow, HIGH);
  digitalWrite(blue, LOW);
  }

  else if(time >= 15000 && time < 20000) {
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(blue, HIGH);
  }
  
  //return time;
}
