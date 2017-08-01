#include "GeigerCounter.h"

GeigerCounter** GeigerCounter::geigerList = NULL;
byte GeigerCounter::geigerNum = 0;

GeigerCounter::GeigerCounter(byte pin) {
	this->pin = pin;
	GeigerCounter** newGeigers = new GeigerCounter*[geigerNum + 1];
	for (byte i = 0; i < geigerNum; i++) {
		newGeigers[i] = geigerList[i];
	}
	newGeigers[geigerNum] = this;
	geigerNum++;
	delete[] geigerList;
	geigerList = newGeigers;
}

GeigerCounter::~GeigerCounter() {
	GeigerCounter** newGeigers = new GeigerCounter*[geigerNum - 1];
	for (byte i = 0, j = 0; i < geigerNum; i++) {
		if (!(geigerList[i] == this)) {
			newGeigers[j] = geigerList[i];
			j++;
		}
	}
	geigerNum--;
	delete[] geigerList;
	geigerList = newGeigers;
}

void GeigerCounter::initialize() {
	pinMode(pin, INPUT);
	attachInterrupt(digitalPinToInterrupt(pin),GeigerCounter::geigerISR,FALLING);
}

unsigned long GeigerCounter::getTotalCount() {
	noInterrupts();
	unsigned long count = totalCount;
	interrupts();
	return count;
}

unsigned long GeigerCounter::getCycleCount() {
	noInterrupts();
	unsigned long count = cycleCount;
	cycleCount = 0;
	interrupts();
	return count;
}

bool GeigerCounter::confirm() {
	return digitalRead(pin) == LOW;
}

void GeigerCounter::geigerISR() {
	for (byte i = 0; i < geigerNum; i++) {
		if (geigerList[i]->confirm()) {
			geigerList[i]->totalCount++;
			geigerList[i]->cycleCount++;
			break;
		}
	}
}