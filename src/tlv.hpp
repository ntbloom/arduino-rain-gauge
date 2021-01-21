#ifndef TLV_HPP
#define TLV_HPP

namespace tlv {
class TLV {
   private:
    unsigned char* _payload;

   public:
    TLV(unsigned char tag, unsigned char value);
    TLV(unsigned char tag, int value);
    ~TLV();
    unsigned char* encode();
};
}  // namespace tlv

#endif
