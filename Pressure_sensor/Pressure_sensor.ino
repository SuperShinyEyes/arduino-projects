// Flexiforce quick start example
// Reads A0 every 100ms and sends voltage value over serial
#define sensor0_pin = A0;
#define sensor1_pin = A1;

int sensor0_value;
int sensor1_value;

float voltage0;
float voltage1;

void setup() {
  // Start serial at 9600 baud
  Serial.begin(9600); 
  Serial.println("starts");
}

void loop(){
  // Read the input on analog pin 0:
  //sensor0_value = analogRead(A0);
  sensor1_value = analogRead(A7);
  
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  //voltage0 = sensor0_value * 1000 * (5.0 / 1023.0);
  voltage1 = sensor1_value * 1000 * (5.0 / 1023.0);
  
  // Print out the value you read:
  Serial.print("Sensor0: ");
  //Serial.print(voltage0);
  Serial.print("Sensor1: ");
  Serial.println(voltage1);
  
  // Wait 100 milliseconds
  delay(100);
}
