#include "GeigerCounter.h"

GeigerCounter::GeigerCounter(byte pin) {
	pinMode(pin, INPUT);
	attachInterrupt(digitalPinToInterrupt(pin),Geiger::ISR(),FALLING);
}

unsigned long getTotalCount() {
	return Geiger::totalCount();
}

unsigned long getCycleCount() {
	unsigned long cycleCount = Geiger::cycleCount;
	Geiger::cycleCount = 0;
	return cycleCount;
}