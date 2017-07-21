#include "GeigerCounter.h"

namespace Geiger {
	unsigned long totalCount;
	unsigned long cycleCount;
	void geiger_ISR() {
	totalCount++;
	cycleCount++;
	}
}

GeigerCounter::GeigerCounter(byte pin) {
	this->pin = pin;
}

void GeigerCounter::initialize() {
	pinMode(pin, INPUT);
	attachInterrupt(digitalPinToInterrupt(pin),Geiger::geiger_ISR,FALLING);
}

unsigned long GeigerCounter::getTotalCount() {
	return Geiger::totalCount;
}

unsigned long GeigerCounter::getCycleCount() {
	unsigned long cycleCount = Geiger::cycleCount;
	Geiger::cycleCount = 0;
	return cycleCount;
}

