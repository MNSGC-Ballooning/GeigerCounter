#include <GeigerCounter.h>

//Create geiger objects tied to specified pins
GeigerCounter geiger1 = GeigerCounter(2);
GeigerCounter geiger2 = GeigerCounter(3);

//global variables for printing
unsigned long totalCount = 0, cycleCount = 0;

void setup() {
  //Begin serial monitor communication
  Serial.begin(115200);

  //Begin tracking hits on each geiger
  geiger1.initialize();
  geiger2.initialize();
}

void loop() {
  //poll total hits for first geiger counter
  totalCount = geiger1.getTotalCount();
  //poll hits since last time getCycleCount() was called (approx 1 sec)
  cycleCount = geiger1.getCycleCount();
  //Print results to serial monitor
  Serial.println("Geiger1 cycle hits: " + String(cycleCount) + ",  total hits: " + String(totalCount));

  //repeat process for second geiger counter
  totalCount = geiger2.getTotalCount();
  cycleCount = geiger2.getCycleCount();
  Serial.println("Geiger2 cycle hits: " + String(cycleCount) + ",  total hits: " + String(totalCount));

  //wait one second before checking again
  delay(1000);
}
