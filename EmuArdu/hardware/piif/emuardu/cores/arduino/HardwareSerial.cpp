/*
  HardwareSerial.cpp - Hardware serial library for Wiring
  fake version to be emulated with CProcessing interface
*/

#include <stdio.h>

#include "HardwareSerial.h"

void serialEventRun(void) {
	// TODO
}

HardwareSerial::HardwareSerial() {
}

int HardwareSerial::available(void) {
	// TODO
	return 0;
}

int HardwareSerial::peek(void) {
	// TODO
	return -1;
}

int HardwareSerial::read(void) {
	// TODO
	return -1;
}

void HardwareSerial::flush() {
	// TODO
}

size_t HardwareSerial::write(uint8_t c) {
	return printf("%c", c);
}

HardwareSerial Serial;
