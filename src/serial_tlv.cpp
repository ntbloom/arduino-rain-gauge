#include "serial_tlv.hpp"

using namespace tlv;

SerialTLV::SerialTLV(unsigned char tag, unsigned char value) : TLV(tag, value){};

SerialTLV::SerialTLV(unsigned char tag, int value) : TLV(tag, value){};

void SerialTLV::hex() {
    for (int i = 0; i < _payload[1]; i++) {
        Serial.println(_payload[i], HEX);
    }
}

