#include <VirtualWire.h>

#define PIN_left_button 6
#define PIN_right_button 7
#define PIN_transmitter 12

/*
  Controller is consisted of two push buttons, rf transmitter, and
  Teensy. + Batteries
*/

char *controller;  // Char pointer
int left_button_state;
int right_button_state;

void setup() {
  	pinMode(13,OUTPUT);
	vw_set_ptt_inverted(true); //
	vw_set_tx_pin(PIN_transmitter);
	vw_setup(4000);// speed of data transfer Kbps

	pinMode(PIN_right_button, INPUT_PULLUP);
	pinMode(PIN_left_button, INPUT_PULLUP);

	Serial.begin(9600);
}

void send_signal(int ctrl){
	char *direction;
	switch(ctrl){
		case 9:
			direction = "9";
			break;
		case 1:
			direction = "1";
			break;
		default:
			direction = "1";
			break;
	}
	// uint8_t is equivalent to char in stdint.h type 
	// For some reason, 
	vw_send((uint8_t *)direction, strlen(direction));
	vw_wait_tx(); // Wait until the whole message is gone
	digitalWrite(13,1);
	delay(200);
}

void loop(){
	left_button_state = !digitalRead(PIN_left_button);
	right_button_state = !digitalRead(PIN_right_button);
	if(left_button_state){
		send_signal(9);
	}else if(right_button_state){
		send_signal(1);
	}else{
		digitalWrite(13,0);
		delay(10);
	}
	Serial.print(left_button_state);
	

}