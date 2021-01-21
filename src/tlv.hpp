#ifndef TLV_HPP
#define TLV_HPP
#include <stdint.h>

namespace tlv {
class TLV {
   private:
    uint8_t _tag, _length;
    uint8_t *_payload, *_value;

   public:
    TLV(uint8_t tag, uint8_t length, int ivalue);
    TLV(uint8_t tag, uint8_t length, float fvalue);
    uint8_t* encode();
};
}  // namespace tlv

#endif
