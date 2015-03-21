#include <VirtualWire.h>
char *controller;  // Char pointer
int button = 8;
int buttonState;

void setup() {
  	pinMode(13,OUTPUT);
	vw_set_ptt_inverted(true); //
	vw_set_tx_pin(12);
	vw_setup(4000);// speed of data transfer Kbps

	pinMode(button, INPUT_PULLUP);
	Serial.begin(9600);
}

void loop(){
	buttonState = !digitalRead(button);
	if(buttonState){
		controller="1";
		// uint8_t is equivalent to char in stdint.h type 
		// For some reason, 
		vw_send((uint8_t *)controller, strlen(controller));
		vw_wait_tx(); // Wait until the whole message is gone
		digitalWrite(13,1);
		delay(500);
	}else{
		digitalWrite(13,0);
		delay(500);
	}
	Serial.print(buttonState);
	/*
	controller="0"  ;
	vw_send((uint8_t *)controller, strlen(controller));
	vw_wait_tx(); // Wait until the whole message is gone
	digitalWrite(13,0);
	delay(2000);
	*/

}

/*
#include <VirtualWire.h>

char *controller;

void setup(){
	pinMode(13, OUTPUT);
	vw_set_ptt_inverted(true);
	vw_set_tx_pin(12);
	vw_setup(4000); //speed of data transfer Kbps
}

void loop(){
	controller="1";
	vw_send((uint8_t *)controller, strlen(controller));
	vw_wait_tx(); // Wait until the whole msg is gone
	digitalWrite(13, 1);
	delay(2000);
	controller="0";
	vw_send((uint8_t *)controller, strlen(controller));
	vw_wait_tx();
	digitalWrite(13, 0);
	delay(2000);
}
*/