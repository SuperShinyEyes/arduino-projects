const int red_left = 13;
const int green_left = 12;
const int yellow_left = 11;
const int blue_left = 10;

const int red_right = 7;
const int green_right = 6;
const int yellow_right = 5;
const int blue_right = 4;


const int switch_left = 2;

int blink_time = 0;
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
    delay(200);
  }

  if(switch_state_left % 2 == 0) {
    digitalWrite(red_left, HIGH);
    digitalWrite(green_left, HIGH);
    digitalWrite(yellow_left, HIGH);
    digitalWrite(blue_left, HIGH);
  }
  else{
    // Reset blink_time when it's over the cycle
    if(blink_time >= 200) {blink_time = 0;}
    
    blink_time = blinker(red_left, green_left, yellow_left, 
    blue_left, blink_time);
    blink_time++;
    delay(1);
  } 

}

// Function to blink LEDs
// "time" tells which LED to blink
int blinker(const int red, const int green, const int yellow, 
const int blue, int time) {
  
  if(time < 50) {
  digitalWrite(red, HIGH);
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(blue, LOW);
  }
  
  else if(time >= 50 && time < 100) {
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  digitalWrite(yellow, LOW);
  digitalWrite(blue, LOW);
  }

  else if(time >= 100 && time < 150) {
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(yellow, HIGH);
  digitalWrite(blue, LOW);
  }

  else if(time >= 150 && time < 200) {
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(blue, HIGH);
  }
  
  return time;
}
