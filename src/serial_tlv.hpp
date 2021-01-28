#ifndef SERIAL_TLV_HPP
#define SERIAL_TLV_HPP

#include "Arduino.h"
#include "tlv.hpp"

#define BAUD 9600

namespace tlv {
/* Abstract base class for sending TLV packets over a serial port */
class ISerialTLV {
   protected:
    int _baud = BAUD;
    virtual void _send(unsigned char* packet, int base) {
        Serial.begin(_baud);
        for (unsigned char i = 0; i < packet[1] + 2; i++) {
            Serial.print(packet[i], base);
        }
        Serial.print('\n');
        Serial.end();
    }
};

/* Create TLV packets on the fly for a component like a temperature gauge */
class ComponentSerialTLV : public ISerialTLV {
   private:
    unsigned char* _packet;

   public:
    ComponentSerialTLV(unsigned char* packet);
    void sendHex();
};

/* Manage static TLV packets that get allocated once and reused */
class StaticSerialTLV : public ISerialTLV {
   private:
    unsigned char *_rain, *_softReset, *_hardReset, *_pause, *_unpause;
    unsigned char* _makeTLV(unsigned char tag);

   public:
    StaticSerialTLV();
    void sendHex();
    void sendRainEvent();
    void sendSoftReset();
    void sendHardReset();
    void sendPause();
    void sendUnpause();
    ~StaticSerialTLV();
};
};  // namespace tlv
#endif
