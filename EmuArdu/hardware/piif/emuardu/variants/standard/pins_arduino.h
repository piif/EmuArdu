/* pour chaque hardware à emuler :
 * - un tableau de tous les pins + des defines pour les A*
 * - une image et une position de chaque pin
 * - un descripteur pour chaque pin, pour savoir s'il est utilisable pour analog, pwm
 *   voire plus tard serial, i2c ...
 */

#ifndef PinsArduino_h
#define PinsArduino_h

#define VARIANT standard
#define VARIANT_STR "standard"

#ifdef MUST_DEFINE_HARDWARE
PinDescriptor pins[] = {
	{ 774, 20, 30, 30, CAPABILITY_DIGITAL },
	{ 744, 20, 30, 30, CAPABILITY_DIGITAL },
	{ 714, 20, 30, 30, CAPABILITY_DIGITAL },
	{ 684, 20, 30, 30, CAPABILITY_DIGITAL|CAPABILITY_PWM },
	{ 654, 20, 30, 30, CAPABILITY_DIGITAL },
	{ 624, 20, 30, 30, CAPABILITY_DIGITAL|CAPABILITY_PWM },
	{ 594, 20, 30, 30, CAPABILITY_DIGITAL|CAPABILITY_PWM },
	{ 564, 20, 30, 30, CAPABILITY_DIGITAL },

	{ 525, 20, 30, 30, CAPABILITY_DIGITAL },
	{ 495, 20, 30, 30, CAPABILITY_DIGITAL|CAPABILITY_PWM },
	{ 465, 20, 30, 30, CAPABILITY_DIGITAL|CAPABILITY_PWM },
	{ 435, 20, 30, 30, CAPABILITY_DIGITAL|CAPABILITY_PWM },
	{ 405, 20, 30, 30, CAPABILITY_DIGITAL },
	{ 375, 20, 30, 30, CAPABILITY_DIGITAL },

	{ 627, 560, 30, 30, CAPABILITY_DIGITAL|CAPABILITY_ANALOG },
	{ 657, 560, 30, 30, CAPABILITY_DIGITAL|CAPABILITY_ANALOG },
	{ 687, 560, 30, 30, CAPABILITY_DIGITAL|CAPABILITY_ANALOG },
	{ 717, 560, 30, 30, CAPABILITY_DIGITAL|CAPABILITY_ANALOG },
	{ 747, 560, 30, 30, CAPABILITY_DIGITAL|CAPABILITY_ANALOG },
	{ 777, 560, 30, 30, CAPABILITY_DIGITAL|CAPABILITY_ANALOG },

	LAST_PIN_DESCRIPTOR
};

Hardware hardware = {
	"standard/ArduinoUnoSmd.jpg",
	844, 597, pins
};

#endif // MUST_DEFINE_HARDWARE

#define A0 14
#define A1 15
#define A2 16
#define A3 17
#define A4 18
#define A5 19

#endif // PinsArduino_h
