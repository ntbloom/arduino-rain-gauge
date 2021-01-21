#ifndef TLV_HPP
#define TLV_HPP

namespace tlv {
class TLV {
   private:
    unsigned char _tag, _length;
    unsigned char* _payload;
    int _value_i;
    unsigned char _value_c;

   public:
    TLV(unsigned char tag, unsigned char value);
    TLV(unsigned char tag, int value);
    unsigned char* encode();
};
}  // namespace tlv

#endif
