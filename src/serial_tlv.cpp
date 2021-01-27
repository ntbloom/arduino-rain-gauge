#include "serial_tlv.hpp"

using namespace tlv;

SerialTLV::SerialTLV(unsigned char* packet, int baud = 9600) {
    _packet = packet;
    _baud = baud;
}

void SerialTLV::_print(int base) {
    Serial.begin(_baud);
    for (unsigned char i = 0; i < _packet[1] + 2; i++) {
        Serial.print(_packet[i], base);
    }
    Serial.println();
    Serial.end();
}

/* send a TLV packet encoded in hex */
void SerialTLV::hex() {
    _print(HEX);
}
