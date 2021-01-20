#include <cassert>
#include <iostream>

#include "../src/tlv.hpp"

#define OK cout << __func__ << "...OK\n"

using namespace std;
using tlv::TLV;

void assert_equal_arrays(int len, uint8_t one[], uint8_t two[]) {
    for (int i = 0; i < len; i++) {
        assert(one[i] == two[i]);
    }
}

/* dummy test */
void test_one_plus_one() {
    assert(1 + 1 == 2);
    OK;
}

/* test basic TLV data */
void test_simple_tlv_packet() {
    uint8_t value[] = {1};
    TLV* tlv = new TLV(1, 1, value);
    uint8_t expected[] = {01, 01, 01};
    uint8_t* actual = tlv->encode();
    assert_equal_arrays(3, expected, actual);
}

int main() {
    test_one_plus_one();
    test_simple_tlv_packet();
}
