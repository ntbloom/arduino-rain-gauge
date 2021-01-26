#ifndef TLV_HPP
#define TLV_HPP

namespace tlv {
class TLV {
   protected:
    unsigned char* _payload;

   public:
    TLV(unsigned char tag, unsigned char value);
    TLV(unsigned char tag, int value);
    unsigned char* encode();
    ~TLV();
};
}  // namespace tlv

#endif
