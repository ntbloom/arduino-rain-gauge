#ifndef TIMER_HPP
#define TIMER_HPP

#include "Arduino.h"

namespace utilities {
class Timer {
   private:
    unsigned long _interval;
    unsigned long _count = 0;
    unsigned long _now = 0;

   public:
    Timer(unsigned long interval);
    bool ready();
};
};  // namespace utilities

#endif
