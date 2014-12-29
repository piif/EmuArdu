#ifndef EmulatorDescription_h
#define EmulatorDescription_h

#define CAPABILITY_DIGITAL 1
#define CAPABILITY_ANALOG  2
#define CAPABILITY_PWM     4

typedef struct _pinDescriptor {
	int x, y, w, h;   // position&size of this pin in picture
	int capabilities;

} PinDescriptor;

#define LAST_PIN_DESCRIPTOR { 0, 0, 0, 0, -1 }
#define isLast(pin) ((pin).capabilities == -1)

typedef struct _hardware {
	const char *picturePath; // image path, relative to variant path
	int pictureWidth, pictureHeight;
	PinDescriptor *pins;
} Hardware;

// must be declared in per variant pins_arduino.h file
extern Hardware hardware;

#endif // EmulatorDescription_h
