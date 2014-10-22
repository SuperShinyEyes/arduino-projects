#include <math.h>
#include <Wire.h>
#include "DS3231.h"
#include <Servo.h>

int servo_pin = 6;
Servo servo;
int servo_angle = 0;

RTClib RTC;

// these constants describe the pins. They won't change:
const int xpin = A3;                  // x-axis of the accelerometer
const int ypin = A2;                  // y-axis
const int zpin = A1;                  // z-axis (only on 3-axis models)

const int red_led = 11;
const int blue_led = 10;
const int green_led = 9;

// 2-dimensional array collecting accleration data of x, y, z
const int xyz_size = 20;
int xyz[xyz_size][3] = {0};                 
// 3-element Array for standard deviation
float xyz_sd[3] = {0};
// Parking-sleep mode starts when it's measured twice in a row
int measured_as_parked_once = 1; 

boolean time_has_set = false;

void setup()
{
  // initialize the serial communications:
  Serial.begin(9600);

  Wire.begin();

  servo.attach(servo_pin);
  servo.write(0);
  delay(1000);
  servo.detach();

  //Make sure the analog-to-digital converter takes its reference voltage from
  // the AREF pin
  analogReference(EXTERNAL);

  pinMode(xpin, INPUT);
  pinMode(ypin, INPUT);
  pinMode(zpin, INPUT);
  pinMode(green_led, OUTPUT);
  pinMode(red_led, OUTPUT);
  pinMode(blue_led, OUTPUT);
}

/*
 * Measure accleration once a sec.
 * Measure as much as the size of xyz array.
*/
void measure_accleration(){
  int i = 0;
  for(i = 0; i < xyz_size; i++) {
    xyz[i][0] = analogRead(xpin);
    //add a small delay between pin readings.  I read that you should
    //do this but haven't tested the importance
    delay(1);
    xyz[i][1] = analogRead(ypin);
    delay(1);
    xyz[i][2] = analogRead(zpin);
    delay(1000);
  }
}

int get_sum(int a){
  int sum = 0;
  int i = 0;
  for(i = 0; i < xyz_size; i++) {
    sum += xyz[i][a];
  }
  return sum;
}

/*
 * How to get deviation:
 * 1. Get the Mean - simple average
 * 2. For each item, subtract the Mean and square the result.
 * 3. Get the average of those squared results. (= Variance)
 * 4. Standard Deviation = Sqrt(Variance)
*/
void get_deviation(){
  // Get mean for x, y, and z separately
  
  int x_mean = get_sum(0) / xyz_size;
  int y_mean = get_sum(1) / xyz_size;
  int z_mean = get_sum(2) / xyz_size;

  int x_variance = 0;
  int y_variance = 0;
  int z_variance = 0;
  
  // Sum up (each value - Mean)^2
  int i = 0;
  for(i = 0; i < xyz_size; i++) {
    x_variance += pow(xyz[i][0] - x_mean, 2);
    y_variance += pow(xyz[i][1] - y_mean, 2);
    z_variance += pow(xyz[i][2] - z_mean, 2);
  }

  // Get average/variance
  x_variance /= xyz_size;
  y_variance /= xyz_size;
  z_variance /= xyz_size;

  xyz_sd[0] = sqrt(x_variance);
  xyz_sd[1] = sqrt(y_variance);
  xyz_sd[2] = sqrt(z_variance);
}

void print_xyz(){
  int i = 0;
  for(i = 0; i < xyz_size; i++){
    //Serial.print("x: %d  y: %d  z: %d", xyz[i][0], xyz[i][1], xyz[i][2]);
    Serial.print(xyz[i][0]);
    Serial.print("\t");
    Serial.print(xyz[i][1]);
    Serial.print("\t");
    Serial.print(xyz[i][2]);
    Serial.print("\n");
  }
}

/*
 * As a parameter, it gets a 2-d array (I'm using a global variable now)
 * e.g. [(x, y, z), (x2, y2, z2), (x3, y3, z3), (x4, y4, z4)]
 * Get deviation. If deviation < x then return True.
*/
boolean is_parked(){
  measure_accleration();
  get_deviation();
  print_xyz();
  Serial.print("Standard Deviation: ");
  Serial.print(xyz_sd[0]);
  Serial.print("\t");
  Serial.print(xyz_sd[1]);
  Serial.print("\t");
  Serial.print(xyz_sd[2]);
  Serial.print("\n");
  if(xyz_sd[0] + xyz_sd[1] + xyz_sd[2] < 30) {
    return true;
  }else{
    return false;
  }
}

/*
 * h: hour, m: minute
 * e.g. ser_servo_time(6, 25);
 * Sets the clock to 6:25
*/
void set_servo_time(int h, int m){
  int cur_time = floor(170.0 / (24 * 60) * (h * 60 + m));
  Serial.print("Current angle:");
  Serial.print(cur_time);
  Serial.print("\n");
  servo.write(170 - cur_time);
}

void led_control(int red_value, int green_value, int blue_value){
  analogWrite(red_led, red_value);
  analogWrite(green_led, green_value);
  analogWrite(blue_led, blue_value);
}

void do_once_when_parked(int h, int m){
  // Turn the red led on
  led_control(255, 0, 0);
  Serial.print("Red LED is on\n");
  Serial.print("Now turn on the servo\n");
  servo.attach(servo_pin);
  set_servo_time(h, m);
  delay(1000);
  time_has_set = true;
  Serial.print("Turn off the servo\n");
  servo.detach(); // Turn off the servo
}

void check_capacity(){}

void set_rtc_time(){}

void loop(){

  DateTime now = RTC.now();

  // Print time - hh:mm
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print("\n");

  // If the car is driving, wait for 40 seconds
  // i.e. when driving, measure once a minute
  if(is_parked() == false){
    /* Parker might have been moved by accident.
     * Don't turn on the driving mode yet.
     * Check once more. */
    if(measured_as_parked_once == 1){
      measured_as_parked_once = 0;
      Serial.print("The car seems to be driving\n Check once again\n");
    }else{
      // Set the variable so the time can be newly set when parked again
      time_has_set = false;
      // Turn on the green light
      led_control(0, 255, 0);
      delay(1000);
      //delay(40000);
    
      Serial.print("The car is driving\n");
    }
  }else{
    if(measured_as_parked_once == 1){
      // Set the time only once when the car has parked.
      if(time_has_set == false) do_once_when_parked(now.hour(), now.minute());
      delay(1000);
      Serial.print("The car is parked\n");
      // If the car is parked, measure every 4 min.      
      //delay(240000);
    }else{
      measured_as_parked_once = 1;
      Serial.print("The car seems to be parked\n");
      Serial.print("Check once again\n");
    }
  }
}



















