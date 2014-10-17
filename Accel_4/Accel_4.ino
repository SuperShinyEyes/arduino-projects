#include <math.h>
// these constants describe the pins. They won't change:
const int xpin = A3;                  // x-axis of the accelerometer
const int ypin = A2;                  // y-axis
const int zpin = A1;                  // z-axis (only on 3-axis models)

const int red_led = 12;
const int green_led = 13;
// 2-dimensional array collecting accleration data of x, y, z
const int xyz_size = 20;
int xyz[xyz_size][3] = {0};                 
// 3-element Array for standard deviation
float xyz_sd[3] = {0};
// Parking-sleep mode starts when it's measured twice in a row
int measured_as_parked_once = 1; 

void setup()
{
  // initialize the serial communications:
  Serial.begin(9600);

  //Make sure the analog-to-digital converter takes its reference voltage from
  // the AREF pin
  analogReference(EXTERNAL);

  pinMode(xpin, INPUT);
  pinMode(ypin, INPUT);
  pinMode(zpin, INPUT);
  pinMode(green_led, OUTPUT);
  pinMode(red_led, OUTPUT);
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
int is_parked(){
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
    return 1;
  }else{
    return 0;
  }
}

void loop()
{
  // If the car is driving, wait for 40 seconds
  // i.e. when driving, measure once a minute
  if(is_parked() == 0){
    /* Parker might have been moved by accident.
     * Don't turn on the driving mode yet.
     * Check once more. */
    if(measured_as_parked_once == 1){
      measured_as_parked_once = 0;
      Serial.print("The car seems to be driving\n Check once again\n");
    }else{
    digitalWrite(green_led, HIGH);
    delay(1000);
    digitalWrite(green_led, LOW);
    //delay(40000);
    
    Serial.print("The car is driving\n");
    }
  }else{
    if(measured_as_parked_once == 1){
      // If the car is parked, measure every 4 min.
      digitalWrite(red_led, HIGH);
      delay(1000);
      digitalWrite(red_led, LOW);
      Serial.print("The car is parked\n");
      //delay(240000);
    }else{
      measured_as_parked_once = 1;
      Serial.print("The car seems to be parked\n");
      Serial.print("Check once again\n");
    }
  }
}



















