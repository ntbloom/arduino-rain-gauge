#ifndef SERIAL_TLV_HPP
#define SERIAL_TLV_HPP

#include "Arduino.h"
#include "tlv.hpp"

namespace tlv {
class SerialTLV : public TLV {
   public:
    SerialTLV(unsigned char tag, unsigned char value);
    SerialTLV(unsigned char tag, int value);
    void hex();
};
};  // namespace tlv
#endif
