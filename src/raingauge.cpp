#include "raingauge.hpp"

using namespace components;

Raingauge::Raingauge(int pin, unsigned long msDelay, float mmPerClick)
    : Button(pin, msDelay, HIGH) {
    _mmPerClick = mmPerClick;
}
