#ifndef GeigerCounter_h
#define GeigerCounter_h

#include <Arduino.h>

namespace Geiger {
	volatile unsigned long totalCount;
	volatile unsigned long cycleCount;
	void ISR() {
		totalCount++;
		cycleCount++;
	}
}

class GeigerCounter {
	public:
		GeigerCounter(byte pin);
		unsigned long getTotalCount();
		unsigned long getCycleCount();
}

#endif