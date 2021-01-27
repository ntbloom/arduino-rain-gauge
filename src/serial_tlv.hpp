#ifndef SERIAL_TLV_HPP
#define SERIAL_TLV_HPP

#include "Arduino.h"
#include "tlv.hpp"

namespace tlv {
class SerialTLV {
   private:
    unsigned char* _packet;
    void _send(int base);

   public:
    SerialTLV(unsigned char* packet);
    void sendHex();
};
};  // namespace tlv
#endif
