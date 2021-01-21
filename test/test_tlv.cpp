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

/* test basic TLV data */
void test_simple_tlv_packet() {
    TLV* tlv = new TLV(1, 1, 1);
    unsigned char expected[] = {01, 01, 01};
    unsigned char* actual = tlv->encode();
    assert_equal_arrays(3, expected, actual);
}

int main() {
    test_one_plus_one();
    test_simple_tlv_packet();
}
