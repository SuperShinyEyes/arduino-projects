const int red_left = 13;
const int green_left = 12;
const int yellow_left = 11;
const int blue_left = 10;

const int red_right = 7;
const int green_right = 6;
const int yellow_right = 5;
const int blue_right = 4;

const int switch_left = 2;
const int switch_right = 3;

int blink_time_left = 0;
int blink_time_right = 0;
int switch_state_left = LOW;
int switch_state_right = LOW;

int interval_left = 6000;

void setup(){
  pinMode(red_left, OUTPUT);
  pinMode(green_left, OUTPUT);
  pinMode(yellow_left, OUTPUT);
  pinMode(blue_left, OUTPUT);
  pinMode(switch_left, INPUT_PULLUP);
  
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
  
  if(interval_left <= 0){
    interval_left = 0;
  }else{--interval_left;}

  // Check if the left button is pressed.
  if(digitalRead(switch_left) == HIGH) {
    if(interval_left == 0) {
      ++switch_state_left; // Increment by 1.
      Serial.println(switch_state_left);
      //delay(150);
      interval_left = 6000;
    }
    // Check if the left button is pressed.
  }
  
  // Check if the right button is pressed.
  if(digitalRead(switch_right) == HIGH) {
    ++switch_state_right; // Increment by 1.
    Serial.println(switch_state_right);
    delay(150);
  }

  if(switch_state_left % 2 == 0) {
    digitalWrite(red_left, HIGH);
    digitalWrite(green_left, HIGH);
    digitalWrite(yellow_left, HIGH);
    digitalWrite(blue_left, HIGH);
  }
  else{
    // Reset blink_time when it's over the cycle
    if(blink_time_left >= 6000) {blink_time_left = 0;}
    
    blinker_left(red_left, green_left, yellow_left, 
    blue_left, blink_time_left);
    blink_time_left++;
  }
 
 if(switch_state_right % 2 == 0) {
    digitalWrite(red_right, HIGH);
    digitalWrite(green_right, HIGH);
    digitalWrite(yellow_right, HIGH);
    digitalWrite(blue_right, HIGH);
  } else{
    // Reset blink_time when it's over the cycle
    if(blink_time_right >= 6000) {blink_time_right = 0;}
    
    blinker_right(red_right, green_right, yellow_right, 
    blue_right, blink_time_right);
    blink_time_right++;
  }

}

// Function to blink LEDs
// "time" tells which LED to blink
void blinker_left(const int red, const int green, const int yellow, 
const int blue, int time) {
  
  if(time < 1500) {
  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(blue, LOW);
  }
  
  else if(time >= 1500 && time < 3000) {
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  digitalWrite(yellow, LOW);
  digitalWrite(blue, LOW);
  }

  else if(time >= 3000 && time < 4500) {
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(yellow, HIGH);
  digitalWrite(blue, LOW);
  }

  else if(time >= 4500 && time < 6000) {
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(blue, HIGH);
  }
}

void blinker_right(const int red, const int green, const int yellow, 
const int blue, int time) {
  
  if(time < 1500) {
  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(blue, LOW);
  }
  
  else if(time >= 1500 && time < 3000) {
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  digitalWrite(yellow, LOW);
  digitalWrite(blue, LOW);
  }

  else if(time >= 3000 && time < 4500) {
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(yellow, HIGH);
  digitalWrite(blue, LOW);
  }

  else if(time >= 4500 && time < 6000) {
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(blue, HIGH);
  }
}
