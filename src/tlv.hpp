#ifndef TLV_HPP
#define TLV_HPP
#include <stdint.h>

namespace tlv {
class TLV {
   private:
    uint8_t _tag, _length;
    uint8_t *_value, *_payload;

   public:
    TLV(uint8_t tag, uint8_t length, int val);
    TLV(uint8_t tag, uint8_t length, float val);
    uint8_t* encode();
};
}  // namespace tlv

#endif