#ifndef TLV_HPP
#define TLV_HPP

namespace tlv {
class TLV {
   private:
    unsigned char _tag, _length;
    unsigned char *_payload, *_value;

   public:
    TLV(unsigned char tag, unsigned char length, int ivalue);
    TLV(unsigned char tag, unsigned char length, float fvalue);
    unsigned char* encode();
};
}  // namespace tlv

#endif
