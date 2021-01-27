#ifndef SERIAL_TLV_HPP
#define SERIAL_TLV_HPP

#include "Arduino.h"
#include "tlv.hpp"

namespace tlv {
class SerialTLV {
   private:
    unsigned char* _packet;
    unsigned char *_softReset, *_hardReset, *_pause, *_unpause;

    void _send(unsigned char* packet, int base);
    void _makeTLV(unsigned char tag);

   public:
    SerialTLV(unsigned char* packet);

    void sendHex();
    void sendSoftReset();
    void sendHardReset();
    void sendPause();
    void sendUnpause();
    ~SerialTLV();
};
};  // namespace tlv
#endif
