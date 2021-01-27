#include "serial_tlv.hpp"

#define BAUD 9600
#define SOFT_RESET 2
#define HARD_RESET 3
#define PAUSE 4
#define UNPAUSE 5

using namespace tlv;

SerialTLV::SerialTLV(unsigned char* packet) {
    _packet = packet;

    // alloce now but don't worry about deleting these values during runtime
    _softReset = makeTLV(SOFT_RESET);
    _hardReset = _makeTLV(HARD_RESET);
    _pause = _makeTLV(PAUSE);
    _unpause = _makeTLV(UNPAUSE);
}

/* preallocate a TLV packet */
unsigned char* SerialTLV::_makeTLV(unsigned char tag) {
    unsigned char val = 1;
    TLV* tlv = new TLV(tag, val);
    return tlv->encode();
}

/* base functionality for sending packets */
void SerialTLV::_send(unsigned char* packet, int base) {
    Serial.begin(BAUD);
    for (unsigned char i = 0; i < packet[1] + 2; i++) {
        Serial.print(_packet[i], base);
    }
    Serial.print('\n');
    Serial.end();
}

/* send a TLV packet encoded in hex */
void SerialTLV::sendHex() {
    _send(_packet, HEX);
}

/* indicate soft reset (rain counter reset) just happened */
void sendSoftReset() {
    _send(_softReset, HEX);
}

/* send right after power cycle, indicating a hard reset happened */
void sendHardReset() {
    _send(_hardReset, HEX);
}

/* send when sensor is paused */
void sendPause() {
    _send(_pause, HEX);
}

/* send when sensor is unpaused */
void sendUnpause() {
    _send(_unpause, HEX);
}

SerialTLV::~SerialTLV() {
    delete[] _softReset;
    delete[] _hardReset;
    delete[] _pause;
    delete[] _unpause;
}
