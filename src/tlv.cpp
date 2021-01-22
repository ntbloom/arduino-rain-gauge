#include "tlv.hpp"

using namespace tlv;

/* for basic packets with static values */
TLV::TLV(unsigned char tag, unsigned char value) {
    _payload = new unsigned char[3];
    _payload[0] = tag;
    _payload[1] = 1;
    _payload[2] = value;
}

/* for temp data, in celsius */
TLV::TLV(unsigned char tag, int value) {
    _payload = new unsigned char[6];
    _payload[0] = tag;
    _payload[1] = 4;

    /* parse the temp data 4-bits at a time */
    _payload[2] = (value >> 12) & 15;
    _payload[3] = (value >> 8) & 15;
    _payload[4] = (value >> 4) & 15;
    _payload[5] = value & 15;
}

/* encode payload as TLV byte array */
unsigned char* TLV::encode() {
    return _payload;
}

TLV::~TLV() {
    delete[] _payload;
}
