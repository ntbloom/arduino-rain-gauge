#include "serial_tlv.hpp"

#define BAUD 9600
#define RAIN_COUNTER 0
#define SOFT_RESET 2
#define HARD_RESET 3
#define PAUSE 4
#define UNPAUSE 5

using namespace tlv;

ComponentSerialTLV::ComponentSerialTLV(unsigned char* packet) {
    _packet = packet;
}

/* send a TLV packet encoded in hex */
void ComponentSerialTLV::sendHex() {
    _send(_packet, HEX);
}

StaticSerialTLV::StaticSerialTLV() {
    _rain = _makeTLV(RAIN_COUNTER);
    _softReset = _makeTLV(SOFT_RESET);
    _hardReset = _makeTLV(HARD_RESET);
    _pause = _makeTLV(PAUSE);
    _unpause = _makeTLV(UNPAUSE);
}

/* preallocate a TLV packet */
unsigned char* StaticSerialTLV::_makeTLV(unsigned char tag) {
    unsigned char val = 1;
    TLV* tlv = new TLV(tag, val);
    return tlv->encode();
}

/* indicates a rain gauge tipper was incremented */
void StaticSerialTLV::sendRainEvent() {
    _send(_rain, HEX);
}

/* indicate soft reset (rain counter reset) just happened */
void StaticSerialTLV::sendSoftReset() {
    _send(_softReset, HEX);
}

/* send right after boot, indicating a hard reset happened */
void StaticSerialTLV::sendHardReset() {
    _send(_hardReset, HEX);
}

/* send when sensor is paused */
void StaticSerialTLV::sendPause() {
    _send(_pause, HEX);
}

/* send when sensor is unpaused */
void StaticSerialTLV::sendUnpause() {
    _send(_unpause, HEX);
}

StaticSerialTLV::~StaticSerialTLV() {
    delete[] _softReset;
    delete[] _hardReset;
    delete[] _pause;
    delete[] _unpause;
}
