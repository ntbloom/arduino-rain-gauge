#include "raingauge.hpp"

using namespace components;

Raingauge::Raingauge(int pin, unsigned long msDelay, float mmPerCount, float inchPerCount)
    : Button(pin, msDelay, HIGH) {
    _mmPerCount = mmPerCount;
    _inchPerCount = inchPerCount;
}

/* add a click to the counter */
void Raingauge::addCount() { _count++; }

/* reset the counters */
void Raingauge::resetCount() { _count = 0; }

/* how many counts are there? */
unsigned long Raingauge::_getCount() { return _count; }

/* total rain in inches */
float Raingauge::_inchTotal() { return _count * _inchPerCount; }

/* total rain in mm */
float Raingauge::_mmTotal() { return _count * _mmPerCount; }

/* total inches, as string */
const char* Raingauge::inches() { return "1.23\""; }

/* total mm, as string */
const char* Raingauge::millimeters() { return "9.99mm"; }
