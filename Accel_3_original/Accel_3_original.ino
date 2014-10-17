// these constants describe the pins. They won't change:
const int xpin = A3;                  // x-axis of the accelerometer
const int ypin = A2;                  // y-axis
const int zpin = A1;                  // z-axis (only on 3-axis models)

const int red_led = 12;
const int green_led = 13;
// 2-dimensional array collecting accleration data of x, y, z
const int xyz_size = 20;
int xyz[xyz_size][3] = {0};                 

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

void loop()
{
digitalWrite(green_led, HIGH);
delay(50);
digitalWrite(green_led, LOW);
digitalWrite(red_led, HIGH);
delay(50);
digitalWrite(red_led, LOW);

  int x = analogRead(xpin);
  //add a small delay between pin readings.  I read that you should
  //do this but haven't tested the importance
    delay(1); 

  int y = analogRead(ypin);
  //add a small delay between pin readings.  I read that you should
  //do this but haven't tested the importance
    delay(1); 

  int z = analogRead(zpin);

  // Update xyz array.
  update_xyz(x, y, z);

  
  // delay before next reading:
  delay(1000);
  
  //is_parked(xyz)
}

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


/*
 * As a parameter, it gets a 2-d array (I'm using a global variable now)
 * e.g. [(x, y, z), (x2, y2, z2), (x3, y3, z3), (x4, y4, z4)]
 * Get deviation. If deviation < 1 then return True.
*/
boolean is_parked(){
  float deviation = get_deviation();

}

int get_sum(int a){
  int sum = 0;
  for(int i = 0; i < xyz; i++) {
    sum += xyz[i][a];
  }
  return sum
}

/*
 * How to get deviation:
 * 1. Get the Mean - simple average
 * 2. For each item, subtract the Mean and square the result.
 * 3. Get the average of those squared results. (= Variance)
 * 4. Standard Deviation = Sqrt(Variance)
*/
float get_deviation(){
  // Get mean for x, y, and z separately
  
  int x_mean = get_sum(0) / xyz_size;
  int y_mean = get_sum(1) / xyz_size;
  int z_mean = get_sum(2) / xyz_size;
}
