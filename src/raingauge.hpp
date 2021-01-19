#ifndef RAINGAUGE_HPP
#define RAINGAUGE_HPP

#include "button.hpp"

/* tipper rain gauge */
namespace components {
class Raingauge : public Button {
   private:
    float _mmPerCount, _inchPerCount;
    unsigned long _count;
    float _inchTotal;
    float _mmTotal;
    String _inches, _millimeters;
    void _updateValues();

   public:
    Raingauge(int pin, unsigned long msDelay, float mmPerCount, float inchPerCount);
    void addCount();
    void resetCount();
    String inches();
    String millimeters();
};
};  // namespace components

#endif
