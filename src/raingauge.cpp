#include "raingauge.hpp"

using namespace components;

Raingauge::Raingauge(int pin, unsigned long msDelay, float mmPerCount, float inchPerCount)
    : Button(pin, msDelay, HIGH) {
    _count = 0;
    _mmPerCount = mmPerCount;
    _inchPerCount = inchPerCount;
    //_mmTotal = 0.0;
    //_inchTotal = 0.0;

    _inchTotal = _count * _inchPerCount;
    _mmTotal = _count * _mmPerCount;

    _inches = String(_inchTotal, 2) + "\"";
    _millimeters = String(_mmTotal, 2) + "mm";
}

/* add a click to the counter */
void Raingauge::addCount() {
    _count++;
    _inchTotal = _count * _inchPerCount;
    _mmTotal = _count * _mmPerCount;
    _inches = String(_inchTotal, 2) + "\"";
    _millimeters = String(_mmTotal, 2) + "mm";
}

/* reset the counters */
void Raingauge::resetCount() { _count = 0; }

/* how many counts are there? */
unsigned long Raingauge::_getCount() { return _count; }

/* total inches, as string */
String Raingauge::inches() { return _inches; }

/* total mm, as string */
String Raingauge::millimeters() { return _millimeters; }
