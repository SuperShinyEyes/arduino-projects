#include <math.h>
#include <stdio.h>
// these constants describe the pins. They won't change:
//const int xpin = A3;                  // x-axis of the accelerometer
//const int ypin = A2;                  // y-axis
//const int zpin = A1;                  // z-axis (only on 3-axis models)

const int red_led = 12;
const int green_led = 13;
// 2-dimensional array collecting accleration data of x, y, z
const int xyz_size = 20;
int xyz[xyz_size][3] = {0};                 
// 3-element Array for standard deviation
float xyz_sd[3] = {0};
// Parking-sleep mode starts when it's measured twice in a row
int measured_as_parked_once = 0; 

void update_xyz(x, y, z){
  // Scoot over to the front
  for(int i = 1; i < xyz_size; i++){
    for(int j = 0; j < 3; j++){
      xyz[i - 1][j] = xyz[i][j];
    }
  }
  // Add the new one in the end
  xyz[19][0] = x;
  xyz[19][1] = y;
  xyz[19][2] = z;
}


int get_sum(int a){
  int sum = 0;
  for(int i = 0; i < xyz_size; i++) {
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
  for(int i = 0; i < xyz_size; i++) {
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

/*
 * As a parameter, it gets a 2-d array (I'm using a global variable now)
 * e.g. [(x, y, z), (x2, y2, z2), (x3, y3, z3), (x4, y4, z4)]
 * Get deviation. If deviation < 0.2 then return True.
*/
int is_parked(){
  get_deviation();
  if(xyz_sd[0] + xyz_sd[1] + xyz_sd[2] < 0.2) {
    return 1;
  }else{
    return 0;
  }
}

void print_xyz(){
  for(int i = 0; i < xyz_size; i++) {
    for(int j = 0; j < 3; j++){
      printf("%d ", xyz[i][j]);
    }
    printf("\n");
  }
}

void arduino_loop(){
  // If the car is driving, wait for 40 seconds
  // i.e. when driving, measure once a minute
  if(is_parked() == 0){
    delay(40000);
    measured_as_parked_once = 0;
  }else{
    if(measured_as_parked_once == 1){
      // If the car is parked, measure every 4 min.
      delay(240000);
    }else{measured_as_parked_once = 1;}
  }
}

int main() {

  for(int i = 0; i < xyz_size; i++){
    xyz[i][0] = i;
    xyz[i][1] = i*5;
    xyz[i][2] = i*10;    
  }

  print_xyz();
  printf("\n");

  get_deviation();
  printf("x: %f, y: %f, z: %f\n", xyz_sd[0], xyz_sd[1], xyz_sd[2]);
  printf("\n");

  printf("Is the car parked?\n");
  if(is_parked() == 1){
    printf("Yes\n");
  }else{
    printf("No, it's driving.\n");
  }


  return 0;
}















