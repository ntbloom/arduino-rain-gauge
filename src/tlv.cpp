#include "tlv.hpp"

using namespace tlv;

TLV::TLV(uint8_t tag, uint8_t length, uint8_t* value) {
    _tag = tag;
    _length = length;
    _value = value;
}

/* encode payload as TLV byte array */
uint8_t* TLV::encode() {
    _payload[2 + _length];
    _payload[0] = _tag;
    _payload[1] = _length;
    int j = 0;
    for (int i = 2; i < _length; i++) {
        _payload[i] = _value[j++];
    }
    return _payload;
}
