#ifndef TEMP36_HPP
#define TEMP36_HPP

#include "Arduino.h"
#include "serial_tlv.hpp"
#include "tlv.hpp"

/* component for TMP36 analog temperature sensors */
namespace components {
class Temp36 {
   private:
    int _pin;
    float _voltage;
    int _valF, _valC;
    String _tempF, _tempC;
    unsigned char _tag = 1;

   public:
    Temp36(int pin, float voltage);
    void measure();
    String tempF();
    String tempC();
    void sendTLVPacket();
};
};  // namespace components

#endif
