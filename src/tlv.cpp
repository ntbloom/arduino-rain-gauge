#include "tlv.hpp"

using namespace tlv;

TLV::TLV(uint8_t tag, uint8_t length, int value) {
    _tag = tag;
    _length = length;
    // TODO: make this work
    value++;
}

/* encode payload as TLV byte array */
uint8_t* TLV::encode() {
    /*
      _payload[2 + _length];
      _payload[0] = _tag;
      _payload[1] = _length;
      int j = 0;
      for (int i = 2; i < _length; i++) {
          _payload[i] = _value[j++];
      }
      return _payload;
      */
    uint8_t* result = new uint8_t[3];
    for (int i = 0; i < 2; i++) {
        result[i] = 01;
    }
    return result;
}
