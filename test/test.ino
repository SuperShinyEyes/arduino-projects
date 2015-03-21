int a=9;     //declaring integer
char b[2];   //declaring character array
String str;  //declaring string
char *cont;

void setup(){
  Serial.begin(9600);
 
  str=String(a); //converting integer into a string
  str.toCharArray(b,2); //passing the value of the string to the character array
  Serial.print("Value of b is \t");  //display that value
  Serial.println(b);
 
}
 
void test(uint8_t* buf){
	Serial.print(buf[0]);
	delay(1000);
}
void loop(){
	uint8_t dir = 1;
	str = String(dir);
	str.toCharArray(b, 2); 
	test((uint8_t *) b);
	cont = "1";
	Serial.print(cont == "1");
	Serial.print("another");
	Serial.print(49-*"1");
	Serial.print("zero?");
	Serial.println(cont == "9");
	Serial.println(10 % 12);
	Serial.println(10 % 9);
	delay(2000);
	for()
}