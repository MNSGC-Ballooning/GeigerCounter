# GeigerCounter

An interrupt-based library for tracking hits on a geiger counter.
Supports multiple geiger objects, but requires use of external interrupt pins.

## Pin Limitations

While this library can theoretically support as many geigers as there are pins on a board,
the current implementation only allows [external interrupt pins](https://www.arduino.cc/en/Reference/AttachInterrupt)
to be used (pins 2 and 3 on an Uno). Making use of other or additional pins will require extending this library
to support pin change interrupts. Although this is possible, the added versatility is of limited use unless the
project in question makes extremely heavy use of pin interrupts.