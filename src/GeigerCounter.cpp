#include "GeigerCounter.h"

//initialize static members of class (used to pass instances of class to ISR)
GeigerCounter** GeigerCounter::geigerList = NULL;
byte GeigerCounter::geigerNum = 0;

//constructor for GeigerCounter object. Adds newly created object to array
GeigerCounter::GeigerCounter(byte pin):
  pin(pin) {
  GeigerCounter** newGeigers = new GeigerCounter*[geigerNum + 1];
  for (byte i = 0; i < geigerNum; i++) {
    newGeigers[i] = geigerList[i];
  }
  newGeigers[geigerNum] = this;
  geigerNum++;
  delete[] geigerList;
  geigerList = newGeigers;
}

//explicit destructor to handle removing object from array. Hopefully will never actually be needed
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

//call during setup to connect the ISR to the geiger's pin and start tracking hits
void GeigerCounter::init() {
  pinMode(pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(pin),GeigerCounter::geigerISR,FALLING);
}

//returns the total number of hits the geiger has detected since call to initialize()
unsigned long GeigerCounter::getTotalCount() {
  noInterrupts();
  unsigned long count = totalCount;
  interrupts();
  return count;
}

//returns the number of hits since the last time this function was called. Useful for hits/unit time
unsigned long GeigerCounter::getCycleCount() {
  noInterrupts();
  unsigned long count = cycleCount;
  cycleCount = 0;
  interrupts();
  return count;
}

//called in ISR to determine which geiger triggered the interrupt
bool GeigerCounter::confirm() {
  return digitalRead(pin) == LOW;
}

//static ISR to find and increment the correct geiger's counter variables when interrupt is triggered
void GeigerCounter::geigerISR() {
  for (byte i = 0; i < geigerNum; i++) {
    if (geigerList[i]->confirm()) {
      geigerList[i]->totalCount++;
      geigerList[i]->cycleCount++;
      break;
    }
  }
}