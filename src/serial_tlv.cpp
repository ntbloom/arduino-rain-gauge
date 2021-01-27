#include "serial_tlv.hpp"

#define BAUD 9600

using namespace tlv;

SerialTLV::SerialTLV(unsigned char* packet) {
    _packet = packet;
}

/* base functionality for sending packets */
void SerialTLV::_send(int base) {
    Serial.begin(BAUD);
    for (unsigned char i = 0; i < _packet[1] + 2; i++) {
        Serial.print(_packet[i], base);
    }
    Serial.println();
    Serial.end();
}

/* send a TLV packet encoded in hex */
void SerialTLV::sendHex() {
    _send(HEX);
}
