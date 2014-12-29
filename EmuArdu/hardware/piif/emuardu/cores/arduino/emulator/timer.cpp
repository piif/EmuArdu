
#include <time.h>

// time of program start, in µs since real epoch
unsigned long int epoch;

unsigned long int now() {
	struct timespec now;
	clock_gettime(CLOCK_REALTIME, &now);
	return (now.tv_sec * 1000000L) + (now.tv_nsec / 1000L);

}
void timerInit(void) {
	epoch = now();
}

unsigned long millis(void) {
	return (now() - epoch) / 1000L;
}

unsigned long micros(void) {
	return now() - epoch;
}

void delay(unsigned long ms) {
	struct timespec duration;
	duration.tv_sec = ms / 1000L;
	duration.tv_nsec = (ms % 1000L) * 1000000L;
	clock_nanosleep(CLOCK_REALTIME, 0, &duration, NULL);
}

void delayMicroseconds(unsigned int us) {
	struct timespec duration;
	duration.tv_sec = us / 1000000L;
	duration.tv_nsec = (us % 1000000L) * 1000;
	clock_nanosleep(CLOCK_REALTIME, 0, &duration, NULL);
}
