#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Arduino.h"

/* basic class for controlling and debouncing buttons */
namespace components {
class Button {
   private:
    int _pin;
    unsigned long _msDelay;
    unsigned long _lastDebounce = 0;
    unsigned long _now = 0;
    bool _high;
    bool _read = LOW;

   public:
    Button(int pin, unsigned long msDelay, bool high);
    bool isPressed();
};
};  // namespace components

#endif
