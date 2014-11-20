#define buttonPin A0
int val= 0;

void setup () {
Serial.begin(9600);
}

void loop () {
 val=analogRead(buttonPin);    //read ANALOG pin 2
 Serial.println(val);              // and show value 0-1023
}