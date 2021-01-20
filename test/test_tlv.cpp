#include <cassert>
#include <iostream>
#define OK cout << __func__ << "...OK\n"

using namespace std;

/* dummy test */
void test_one_plus_one() {
    assert(1 + 1 == 2);
    OK;
}

int main() { test_one_plus_one(); }
