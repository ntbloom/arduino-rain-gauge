#ifndef TEMP36_HPP
#define TEMP36_HPP

#include "Arduino.h"
#include "serial/component_serial_tlv.hpp"
#include "tlv.hpp"

using tlv::TLV;

/* component for TMP36 analog temperature sensors */
namespace components {
class Temp36 {
   private:
    int _pin;
    float _voltage;
    const unsigned char _tag = 1;
    int _valF, _valC;
    String _tempF, _tempC;
    TLV* _tlv;

   public:
    Temp36(int pin, float voltage);
    void measure();
    String tempF();
    String tempC();
    void sendTLVPacket();
};
};  // namespace components

#endif
