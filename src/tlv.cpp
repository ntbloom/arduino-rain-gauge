#include "tlv.hpp"

using namespace tlv;

TLV::TLV(unsigned char tag, unsigned char length, int value) {
    _tag = tag;
    _length = length;
    // TODO: make this work
    value++;
}

/* encode payload as TLV byte array */
unsigned char* TLV::encode() {
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
    unsigned char* result = new unsigned char[3];
    for (int i = 0; i < 2; i++) {
        result[i] = 01;
    }
    return result;
}
