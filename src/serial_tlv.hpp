#ifndef SERIAL_TLV_HPP
#define SERIAL_TLV_HPP

#include "Arduino.h"
#include "tlv.hpp"

namespace tlv {
class SerialTLV {
   private:
    unsigned char* _packet;
    int _baud;
    void _print(int base);

   public:
    SerialTLV(unsigned char* packet, int baud);
    void hex();
};
};  // namespace tlv
#endif
