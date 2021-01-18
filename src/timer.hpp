#ifndef TIMER_HPP
#define TIMER_HPP

#include "Arduino.h"

namespace utilities {
class Timer {
   private:
    unsigned long _interval, _count;

   public:
    Timer(unsigned long interval);
    bool ready();
};
};  // namespace utilities

#endif
