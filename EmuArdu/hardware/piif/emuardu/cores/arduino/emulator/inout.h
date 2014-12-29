#ifndef INOUT_H
#define INOUT_H

#include "Arduino.h"

#define IO_MODE_DIGITAL_IN 0
#define IO_MODE_DIGITAL_OUT 1
#define IO_MODE_ANALOG_IN 2
#define IO_MODE_PWM 4
#define IO_MODE_PULLUP  8

typedef struct _pinState {
	byte mode; // in/out digital, analog in, pwm
	int value; // 0/1 for digital, 0..255 for pwm, 0..999 for analog in
} PinState;

void inoutInit(void);

extern PinState *pinsState;
extern int pinsNumber;

#endif // INOUT_H
