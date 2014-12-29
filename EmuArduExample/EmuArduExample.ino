#include <Arduino.h>

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
