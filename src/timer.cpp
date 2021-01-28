#include "timer.hpp"

using namespace utilities;

/* how long to wait, in seconds */
Timer::Timer(unsigned long interval) {
    _interval = interval;
}

/* has that amount of time passed? */
bool Timer::ready() {
    if ((millis() - _count) > (_interval * 1000)) {
        _count = millis();
        return true;
    }
    return false;
}
