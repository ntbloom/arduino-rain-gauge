#ifndef RAINGAUGE_HPP
#define RAINGAUGE_HPP

#include "button.hpp"

/* tipper rain gauge */
namespace components {
class Raingauge : public Button {
   private:
    float _mmPerClick;

   public:
    Raingauge(int pin, unsigned long msDelay, float mmPerClick);
    unsigned long count;
    void resetCount();
};
};  // namespace components

#endif
