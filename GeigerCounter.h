#ifndef GeigerCounter_h
#define GeigerCounter_h

#include <Arduino.h>

class GeigerCounter {
	public:
		GeigerCounter(byte pin);
		~GeigerCounter();
		void initialize();
		unsigned long getTotalCount();
		unsigned long getCycleCount();
		bool confirm();
	private:
		byte pin;
		volatile unsigned long totalCount;
		volatile unsigned long cycleCount;
		static GeigerCounter** geigerList;
		static byte geigerNum;
		static void geigerISR();
};

#endif