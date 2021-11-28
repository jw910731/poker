#include "../list.h"

#include <cassert>
#include <iostream>
#include <iterator>
#include <list>
#include <utility>
#include <vector>

void test_emplace() {
    mystl::list<std::pair<int, int>> l;

    l.emplace(l.begin(), 10, 20);
    std::vector<std::pair<int, int>> testcase;
    testcase.emplace(testcase.begin(), 10, 20);
    if (!std::equal(l.begin(), l.end(), testcase.begin(), testcase.end())) {
        abort();
    }

    l.emplace(std::next(l.begin(), 1), 11, 21);
    testcase.emplace(std::next(testcase.begin(), 1), 11, 21);
    if (!std::equal(l.begin(), l.end(), testcase.begin(), testcase.end())) {
        abort();
    }

    l.emplace(std::next(l.begin(), 2), 13, 23);
    testcase.emplace(std::next(testcase.begin(), 2), 13, 23);
    if (!std::equal(l.begin(), l.end(), testcase.begin(), testcase.end())) {
        abort();
    }
}

int main() {
    test_emplace();
    return 0;
}
