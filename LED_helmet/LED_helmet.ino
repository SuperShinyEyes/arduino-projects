#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#include <VirtualWire.h>

#define PIN_LED_left 6
#define PIN_LED_right 7

char *direction = "0"; // 1-: left, 0: straight, 1: right
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip_left = Adafruit_NeoPixel(25, PIN_LED_left, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip_right = Adafruit_NeoPixel(25, PIN_LED_right, NEO_GRB + NEO_KHZ800);

void setup() {
  strip_left.begin();
  strip_left.show(); // Initialize all pixels to 'off'

  strip_right.begin();
  strip_right.show(); // Initialize all pixels to 'off'

  /* For RF receiver */
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_set_rx_pin(12);
  vw_setup(4000);  // Bits per sec
  vw_rx_start();       // Start the receiver PLL running

  Serial.begin(9600);
}

/*
  LED helmet by Seyoung Park
  LEDs are attached on the back of a bike helmet.
  LEDs act as rear lights of cars and motor bikes.

  LED helmet is consisted of two parts: 
  [LEDs & RF receiver] + [RF transmitter & Push-buttons]

  When driving straight, LEDs will lit up without blinking only one side.
  When you are turning right, then you would click the right button on the controller.
  The signal will be sent to the RF receiver, which is attached to the LEDs and it will 
  blink the LEDs on the corresponding side.

  After you've made your turn push any button, so that blinking will stop.
*/
char* start_blink(uint8_t* buf){
  char *turning_direction;
  if(buf[0]=='1'){ 
    blink(strip_right, 50);
    turning_direction = "1";
  }else if(buf[0]=='9'){ 
    blink(strip_left, 50);
    turning_direction = "9";
  }
  return turning_direction;
}

void blink(Adafruit_NeoPixel strip, uint8_t wait){
  uint32_t color = strip.Color(255, 0, 0); // Red
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, color);
      strip.show();
      delay(wait);
  }
}

void drive(){
  rainbow(20);
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  // Make a turn. Start Blinking!
  if (direction == "0" && vw_get_message(buf, &buflen)){
    direction = start_blink((uint8_t *) buf);
    Serial.println("New direction!");
    Serial.println(direction);
  }// You are keep driving
  else if(direction == "0"){  
    drive();
  }// You want to stop blinking
  else if(direction != "0" && vw_get_message(buf, &buflen)){
    direction = "0";
    drive();
  }// The LEDs are blinking and you still want them to blink
  else if (direction != "0"){
    start_blink((uint8_t *) direction);
  }
  // Some example procedures showing how to display to the pixels:
  /*
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  // Send a theater pixel chase in...
  theaterChase(strip.Color(127, 127, 127), 50); // White
  theaterChase(strip.Color(127,   0,   0), 50); // Red
  theaterChase(strip.Color(  0,   0, 127), 50); // Blue

  rainbow(20);
  rainbowCycle(20);
  theaterChaseRainbow(50);
  */
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<7; i++) {
      strip_right.setPixelColor(i, Wheel(strip_right, (i+j) & 255));
      strip_left.setPixelColor(i, Wheel(strip_left, (i+j) & 255));
    }
    strip_right.show();
    strip_left.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(Adafruit_NeoPixel strip, byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}