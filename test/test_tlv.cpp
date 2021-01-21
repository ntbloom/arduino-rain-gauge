/* all-or-nothing, totally unforgiving unit-test suite for tlv encryption */

#include <cassert>
#include <iostream>

#include "../src/tlv.hpp"

#define OK cout << __func__ << "...OK\n"

using namespace std;
using tlv::TLV;

void assert_equal_arrays(int len, unsigned char one[], unsigned char two[]) {
    for (int i = 0; i < len - 1; i++) {
        assert(one[i] == two[i]);
    }
}

/* dummy test */
void test_one_plus_one() {
    assert(1 + 1 == 2);
    OK;
}

/* test TLV packet for rain event */
void test_tlv_rain_packet() {
    unsigned char t, l, v;
    t = 0;
    l = 1;
    v = 1;
    TLV* tlv = new TLV(t, l, v);
    unsigned char expected[] = {0x00, 0x01, 0x01};
    unsigned char* actual = tlv->encode();
    assert_equal_arrays(3, expected, actual);
    OK;
}

/* test TLV packet for soft-reset event */
void test_tlv_soft_reset_packet() {
    unsigned char t, l, v;
    t = 2;
    l = 1;
    v = 1;
    TLV* tlv = new TLV(t, l, v);
    unsigned char expected[] = {t, l, v};
    unsigned char* actual = tlv->encode();
    assert_equal_arrays(3, expected, actual);
    OK;
}

/* test TLV packet for hard-reset event */
void test_tlv_hard_reset_packet() {
    unsigned char t, l, v;
    t = 3;
    l = 1;
    v = 1;
    TLV* tlv = new TLV(t, l, v);
    unsigned char expected[] = {t, l, v};
    unsigned char* actual = tlv->encode();
    assert_equal_arrays(3, expected, actual);
    OK;
}

int main() {
    assert(sizeof(float) == 4);  // value on arduino
    assert(sizeof(int) == 4);    // value on arduino
    test_one_plus_one();
    test_tlv_rain_packet();
    test_tlv_soft_reset_packet();
    test_tlv_hard_reset_packet();
}
