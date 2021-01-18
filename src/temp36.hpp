#ifndef TEMP36_HPP
#define TEMP36_HPP

#include "Arduino.h"

/* component for TMP36 analog temperature sensors */
namespace components {
class Temp36 {
   private:
    int _pin;
    float _voltage;
    int _valF, _valC;
    String _tempF, _tempC;

   public:
    Temp36(int pin, float voltage);
    void measure();
    String tempF();
    String tempC();
};
};  // namespace components

#endif
