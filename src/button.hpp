#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Arduino.h"

/* basic class for controlling and debouncing buttons */
namespace components {
class Button {
   private:
    int m_pin;
    unsigned long m_msDelay;
    unsigned long m_lastDebounce;
    bool m_high;
    bool m_read = LOW;

   public:
    Button(int pin, unsigned long msDelay, bool high);
    bool isPressed();
};
};  // namespace components

#endif
