#include <Arduino.h>

#ifndef ARDUINO_BOARD
#define STR(s) #s
#define ARDUINO_BOARD STR(USB_PRODUCT)
#endif

void setup() {
	Serial.begin(9600);
	Serial.println("!!! Hello " ARDUINO_BOARD " World !!!");
	pinMode(13, OUTPUT);
}

boolean light = LOW;
void loop() {
	Serial.println(millis());
	delay(1000);
	digitalWrite(13, light);
	light = !light;
}

