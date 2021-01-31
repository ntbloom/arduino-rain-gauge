#include "component_serial_tlv.hpp"

#include "iserial_tlv.hpp"

using namespace tlv;

ComponentSerialTLV::ComponentSerialTLV(unsigned char* packet) {
    _packet = packet;
}

/* send a TLV packet encoded in hex */
void ComponentSerialTLV::sendHex() {
    _send(_packet, HEX);
}

