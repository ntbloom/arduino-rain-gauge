#ifndef COMPONENT_SERIAL_TLV_HPP
#define COMPONENT_SERIAL_TLV_HPP

#include "iserial_tlv.hpp"

namespace tlv {
/* Create TLV packets on the fly for a component like a temperature gauge */
class ComponentSerialTLV : public ISerialTLV {
   private:
    TLV* _tlv;

   public:
    ComponentSerialTLV(unsigned char tag, int value);
    void update(int value);
    void sendHex();
};
};  // namespace tlv
#endif
