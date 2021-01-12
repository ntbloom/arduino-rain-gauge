#include "button.hpp"

using namespace components;

Button::Button(int pin, unsigned long msDelay, bool high) {
    m_pin = pin;
    m_msDelay = msDelay;
    m_high = high;

    m_lastDebounce = 0;
    pinMode(m_pin, INPUT);
}

/* is the button pressed and valid (not bouncing) */
bool Button::isPressed() {
    // check if pin fired
    m_read = digitalRead(m_pin);
    switch (m_high) {
        case HIGH:
            if (!m_read) {
                return false;
            }
            break;
        case LOW:
            if (m_read) {
                return false;
            }
            break;
    }

    // debounce it
    bool b = false;
    if ((millis() - m_lastDebounce) > m_msDelay) {
        b = true;
    }
    m_lastDebounce = millis();
    return b;
}
