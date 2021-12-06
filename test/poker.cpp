#include "../poker.h"
#include "test_util.h"

#include <iostream>

void test_card_compare() {
    card c1(0), c2(10);
    if (c1 < c2) {
        throw test_exception("card compare");
    }
    if (!(c2 < c1)) {
        throw test_exception("card compare");
    }
}

int main() {
    std::cout << "[Start] Begin card compare test\n";
    test_card_compare();
    std::cout << "[Success] Pass card compare test\n";
    return 0;
}
