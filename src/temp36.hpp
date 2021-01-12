#ifndef TEMP36_HPP
#define TEMP36_HPP

#include "Arduino.h"

/* component for TMP36 analog temperature sensors */
namespace components {
class Temp36 {
   private:
    int m_pin;
    float m_voltage;
    int m_valF, m_valC;
    String m_tempF, m_tempC;

   public:
    Temp36(int pin, float voltage);
    void measure();
    String tempF();
    String tempC();
};
};  // namespace components

#endif
