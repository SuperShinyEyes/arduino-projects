#include <Servo.h> 
#include <math.h>

int servoPin = 6;
 
Servo servo;  
 
int angle = 0;   // servo position in degrees 
 
void setup() 
{ 
  Serial.begin(9600);
  servo.attach(servoPin); 
} 
 
 
void loop() 
{ 
  Serial.print(8/3);
  Serial.print("\n");
  Serial.print(floor(3.3));
  // scan from 0 to 180 degrees
  //servo.write(0);
  //delay(1000);
  servo.write(90);
  delay(2000);
  //1servo.write(180);
  delay(1000);
  /*
  for(angle = 0; angle < 180; angle++)  
  {                                  
    servo.write(angle);               
    delay(15);                   
  } 
  // now scan back from 180 to 0 degrees
  for(angle = 180; angle > 0; angle--)    
  {                                
    servo.write(angle);           
    delay(15);       
  }
  */ 
} 