#ifndef GeigerCounter_h
#define GeigerCounter_h

#include <Arduino.h>

namespace Geiger {
	void geiger_ISR();
}

class GeigerCounter {
	public:
		GeigerCounter(byte pin);
		void initialize();
		unsigned long getTotalCount();
		unsigned long getCycleCount();
	private:
		byte pin;
};

#endif