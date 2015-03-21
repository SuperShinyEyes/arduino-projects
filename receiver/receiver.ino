#include <VirtualWire.h>
void setup()
{
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_set_rx_pin(12);
    vw_setup(4000);  // Bits per sec
    pinMode(13, OUTPUT);

    vw_rx_start();       // Start the receiver PLL running

    Serial.begin(9600);
}

void test(uint8_t* buf){
  Serial.print(*buf);
}

    void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    //digitalWrite(13, 1);
    if (vw_get_message(buf, &buflen)) // Non-blocking
      {
        test((uint8_t *) buf);
      	if(buf[0]=='1'){
   			digitalWrite(13,1);
        delay(2000);
      } /* 
   		else if(buf[0]=='0'){
  			digitalWrite(13,0);
      }*/
    }else{
      digitalWrite(13, 0);
    }

}

/*
#include <VirtualWire.h>

void setup(){
	vw_set_ptt_inverted(true); // Required for DR3100
	vw_set_rx_pin(12);
	vw_setup(4000); // Vits per sec. Range from 0 to 9600
	pinMode(13, OUTPUT);

	vw_rx_start();  // Start the receiver PLL running
}

void loop(){
	uint8_t buf[VW_MAX_MESSAGE_LEN];
	uint8_t buflen = VW_MAX_MESSAGE_LEN;

	if(vw_get_message(buf, &buflen)) // Non-blocking
	{
		if(buf[0]=='1'){
			digitalWrite(13, 1);
		}
		if(buf[0]=='0'){
			digitalWrite(13, 0);
		}
	}
}*/
