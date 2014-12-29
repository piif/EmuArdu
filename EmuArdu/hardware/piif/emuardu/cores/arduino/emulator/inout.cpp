#include "inout.h"
#include "description.h"
#include "emulator.h"
#include <stdio.h>

int pinsNumber;
PinState *pinsState;

void inoutInit() {
	PinDescriptor *p = hardware.pins;
	for (pinsNumber = 0; !isLast(*p); pinsNumber++, p++);

	pinsState = new PinState[pinsNumber];
	for (int p = 0; p < pinsNumber; p++) {
		pinsState[p].mode = IO_MODE_DIGITAL_OUT;
		pinsState[p].value = 0;
	}
}

void pinMode(byte pin, byte mode) {
	// INPUT, OUTPUT, or INPUT_PULLUP
	if (pin >= pinsNumber) {
		fprintf(stderr, "pinMode: bad pin number %d\n", pin);
		return;
	}
	switch(mode) {
	case INPUT:
		if (hardware.pins[pin].capabilities & CAPABILITY_ANALOG) {
			pinsState[pin].mode = IO_MODE_ANALOG_IN;
		} else {
			pinsState[pin].mode = IO_MODE_DIGITAL_IN;
		}
		pinsState[pin].value = 0;
		break;
	case OUTPUT:
		pinsState[pin].mode = IO_MODE_DIGITAL_OUT;
		pinsState[pin].value = 0;
		break;
	case INPUT_PULLUP:
		pinsState[pin].mode = IO_MODE_DIGITAL_IN | IO_MODE_PULLUP;
		pinsState[pin].value = 1;
		break;
	}
	hasToRender = true;
}

void digitalWrite(byte pin, byte value) {
	if (pin >= pinsNumber) {
		fprintf(stderr, "digitalWrite: bad pin number %d\n", pin);
		return;
	}
	if (pinsState[pin].mode == IO_MODE_DIGITAL_IN) {
		if (value) {
			pinsState[pin].mode |= IO_MODE_PULLUP;
		} else {
			pinsState[pin].mode &= ~IO_MODE_PULLUP;
		}
		return;
	}
	if (pinsState[pin].mode == IO_MODE_ANALOG_IN) {
		fprintf(stderr, "can't write to pin %d as it's in 'analog read' mode\n", pin);
		return;
	}

	pinsState[pin].value = (value == 0) ? 0 : 1;
	pinsState[pin].mode &= ~IO_MODE_PWM;
	hasToRender = true;
}

int digitalRead(byte pin) {
	if (pin >= pinsNumber) {
		fprintf(stderr, "digitalRead: bad pin number %d\n", pin);
		return 0;
	}
	return (pinsState[pin].value == 0) ? 0 : 1;
}

int analogRead(byte pin) {
	if (pin >= pinsNumber) {
		fprintf(stderr, "digitalRead: bad pin number %d\n", pin);
		return 0;
	}
	if (!(hardware.pins[pin].capabilities & CAPABILITY_ANALOG)) {
		fprintf(stderr, "analogRead: pin number %d can't read analog\n", pin);
	}
	if (!(pinsState[pin].mode & IO_MODE_ANALOG_IN)) {
		fprintf(stderr, "analogRead: pin number %d not in 'analog read' mode\n", pin);
	}
	return pinsState[pin].value;
}
void analogReference(byte mode) {
	fprintf(stderr, "analogReference: not implemented\n");
}

void analogWrite(byte pin, int value) {
	if (pin >= pinsNumber) {
		fprintf(stderr, "analogWrite: bad pin number %d\n", pin);
		return;
	}
	if (!(hardware.pins[pin].capabilities & CAPABILITY_PWM)) {
		fprintf(stderr, "analogWrite: pin number %d can't handle PWM\n", pin);
		return;
	}
	if (!(pinsState[pin].mode & IO_MODE_DIGITAL_OUT)) {
		fprintf(stderr, "analogWrite: pin number %d not in 'write' mode\n", pin);
	}
	pinsState[pin].mode |= IO_MODE_PWM;
	pinsState[pin].value = value & 0xff;
	hasToRender = true;
}

unsigned long pulseIn(byte pin, byte state, unsigned long timeout) {
	fprintf(stderr, "pulseIn: not implemented\n");
	// TODO loop on read+emulatorLoop still switch or timeout then re-loop+emulatorLoop
	// still switch
	return 0;
}

void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val) {
	fprintf(stderr, "shiftOut: not implemented\n");
}
uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder) {
	fprintf(stderr, "shiftIn: not implemented\n");
	return 0;
}
