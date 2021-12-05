#include "../list.h"

#include <cstdlib>
#include <iostream>
#include <iterator>
#include <list>
#include <utility>

void test_emplace_back(mystl::list<std::pair<int, int>> &l,
                       std::list<std::pair<int, int>> &t) {
    l.emplace_back(14, 24);
    t.emplace_back(14, 24);
    if (!std::equal(l.begin(), l.end(), t.begin(), t.end())) {
        abort();
    }
}

void test_emplace_front(mystl::list<std::pair<int, int>> &l,
                        std::list<std::pair<int, int>> &t) {
    l.emplace_front(10, 20);
    t.emplace_front(10, 20);
    if (!std::equal(l.begin(), l.end(), t.begin(), t.end())) {
        abort();
    }
}

void test_emplace(mystl::list<std::pair<int, int>> &l,
                  std::list<std::pair<int, int>> &t) {
    l.emplace(std::next(l.begin(), 1), 11, 21);
    t.emplace(std::next(t.begin(), 1), 11, 21);
    if (!std::equal(l.begin(), l.end(), t.begin(), t.end())) {
        abort();
    }

    l.emplace(std::next(l.begin(), 2), 13, 23);
    t.emplace(std::next(t.begin(), 2), 13, 23);
    if (!std::equal(l.begin(), l.end(), t.begin(), t.end())) {
        abort();
    }
}

void test_iterator(mystl::list<std::pair<int, int>> &l,
                   std::list<std::pair<int, int>> &t) {
    if (*std::prev(l.end()) != *std::prev(t.end())) {
        abort();
    }
    if (*std::next(l.begin()) != *std::next(t.begin())) {
        abort();
    }
}

void test_rule_of_five(mystl::list<std::pair<int, int>> &l,
                       std::list<std::pair<int, int>> &t) {
    mystl::list<std::pair<int, int>> l_copy(l);
    std::list<std::pair<int, int>> t_copy(t);
    if (l_copy != l ||
        !std::equal(l_copy.begin(), l_copy.end(), t.begin(), t.end())) {
        abort();
    }
    t_copy = t;
    l_copy = l;
    if (l_copy != l ||
        !std::equal(l_copy.begin(), l_copy.end(), t.begin(), t.end())) {
        abort();
    }
}

int main() {
    mystl::list<std::pair<int, int>> sample({{1, 11}, {2, 12}, {3, 13}});
    std::list<std::pair<int, int>> testcase({{1, 11}, {2, 12}, {3, 13}});
    test_emplace_front(sample, testcase);
    std::cout << "[Success] Pass emplace front test\n";
    test_emplace(sample, testcase);
    std::cout << "[Success] Pass emplace test\n";
    test_emplace_back(sample, testcase);
    std::cout << "[Success] Pass emplace back test\n";
    test_rule_of_five(sample, testcase);
    std::cout << "[Success] Pass copy & move assignment and ctor test\n";
    test_iterator(sample, testcase);
    std::cout << "[Success] Pass iterator behaviour test\n";
    return 0;
}
