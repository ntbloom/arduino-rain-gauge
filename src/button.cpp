#include "button.hpp"

using namespace components;

Button::Button(int pin, unsigned long msDelay, bool high) {
    _pin = pin;
    _msDelay = msDelay;
    _high = high;

    _lastDebounce = 0;
    pinMode(_pin, INPUT);
}

/* is the button pressed and valid (not bouncing) */
bool Button::isPressed() {
    // check if pin fired
    _read = digitalRead(_pin);
    switch (_high) {
        case HIGH:
            if (!_read) {
                return false;
            }
            break;
        case LOW:
            if (_read) {
                return false;
            }
            break;
    }

    // debounce it
    bool b = false;
    if ((millis() - _lastDebounce) > _msDelay) {
        b = true;
    }
    _lastDebounce = millis();
    return b;
}
