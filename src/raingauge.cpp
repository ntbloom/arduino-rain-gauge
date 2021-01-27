#include "raingauge.hpp"

using namespace components;
using namespace tlv;

Raingauge::Raingauge(int pin, unsigned long msDelay, float mmPerCount, float inchPerCount)
    : Button(pin, msDelay, HIGH) {
    _count = 0;
    _mmPerCount = mmPerCount;
    _inchPerCount = inchPerCount;
    _updateValues();

    // initialize a TLV packet to be reused; don't worry about cleaning up
    unsigned char t, v;
    t = 0;
    v = 1;
    TLV* tlv = new TLV(t, v);
    _packet = tlv->encode();
    _serialTLV = new SerialTLV(_packet);
}

/* add a click to the counter */
void Raingauge::addCount() {
    _count++;
    _updateValues();
}

void Raingauge::_updateValues() {
    _inchTotal = _count * _inchPerCount;
    _mmTotal = _count * _mmPerCount;

    _inches = String(_inchTotal, 2) + "\"";
    _millimeters = String(_mmTotal, 1) + "mm";
}

/* reset the counters */
void Raingauge::resetCount() {
    _count = 0;
    _updateValues();
}

/* total inches, as string */
String Raingauge::inches() {
    return _inches;
}

/* total mm, as string */
String Raingauge::millimeters() {
    return _millimeters;
}

/* send a TLV packet on a rain event */
void Raingauge::sendTLVPacket() {
    _serialTLV->sendHex();
}

Raingauge::~Raingauge() {
    delete[] _packet;
}
