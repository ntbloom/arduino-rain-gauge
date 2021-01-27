#ifndef RAINGAUGE_HPP
#define RAINGAUGE_HPP

#include "button.hpp"
#include "serial_tlv.hpp"
#include "tlv.hpp"

using namespace tlv;

/* tipper rain gauge */
namespace components {
class Raingauge : public Button {
   private:
    float _mmPerCount, _inchPerCount;
    unsigned long _count;
    unsigned char* _packet;
    SerialTLV* _serialTLV;
    float _inchTotal, _mmTotal;

    String _inches, _millimeters;
    void _updateValues();

   public:
    Raingauge(int pin, unsigned long msDelay, float mmPerCount, float inchPerCount);
    void addCount();
    void resetCount();
    void sendTLVPacket();
    String inches();
    String millimeters();
    ~Raingauge();
};
};  // namespace components

#endif
