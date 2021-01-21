#include "tlv.hpp"

using namespace tlv;

TLV::TLV(unsigned char tag, unsigned char length, unsigned char value) {
    _tag = tag;
    _length = length;
    _payload = new unsigned char[3];
    _payload[0] = tag;
    _payload[1] = 1;
    _payload[2] = value;
}

/* encode payload as TLV byte array */
unsigned char* TLV::encode() {
    return _payload;
}
