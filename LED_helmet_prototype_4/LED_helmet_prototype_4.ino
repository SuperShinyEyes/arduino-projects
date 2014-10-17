const int red_left = 13;
const int green_left = 12;
const int yellow_left = 11;
const int blue_left = 10;

const int switch_left = 2;

int blink_time_left = 0;
int switch_state_left = LOW;

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

  // Check if the button is pressed.
  if(digitalRead(switch_left) == HIGH) {
    ++switch_state_left; // Increment by 1.
    Serial.println(switch_state_left);
    delay(10);
  }
  
  if(switch_state_left % 2 == 0) {
    digitalWrite(red_left, HIGH);
    digitalWrite(green_left, HIGH);
    digitalWrite(yellow_left, HIGH);
    digitalWrite(blue_left, HIGH);
  }
  else{
    // Reset blink_time when it's over the cycle
    if(blink_time_left >= 20000) {blink_time_left = 0;}
    
    blinker(red_left, green_left, yellow_left, 
    blue_left, blink_time_left);
    blink_time_left+=100;
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
