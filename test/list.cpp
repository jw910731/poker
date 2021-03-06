#include "../list.h"
#include "test_util.h"

#include <cstdlib>
#include <exception>
#include <iostream>
#include <iterator>
#include <list>
#include <utility>

void test_emplace_back(mystl::list<std::pair<int, int>> &l,
                       std::list<std::pair<int, int>> &t) {
    l.emplace_back(14, 24);
    t.emplace_back(14, 24);
    if (!std::equal(l.begin(), l.end(), t.begin(), t.end())) {
        throw test_exception("emplace back");
    }
}

void test_emplace_front(mystl::list<std::pair<int, int>> &l,
                        std::list<std::pair<int, int>> &t) {
    l.emplace_front(10, 20);
    t.emplace_front(10, 20);
    if (!std::equal(l.begin(), l.end(), t.begin(), t.end())) {
        throw test_exception("emplace front");
    }
}

void test_emplace(mystl::list<std::pair<int, int>> &l,
                  std::list<std::pair<int, int>> &t) {
    l.emplace(std::next(l.begin(), 1), 11, 21);
    t.emplace(std::next(t.begin(), 1), 11, 21);
    if (!std::equal(l.begin(), l.end(), t.begin(), t.end())) {
        throw test_exception("emplace");
    }

    l.emplace(std::next(l.begin(), 2), 13, 23);
    t.emplace(std::next(t.begin(), 2), 13, 23);
    if (!std::equal(l.begin(), l.end(), t.begin(), t.end())) {
        throw test_exception("emplace");
    }
}

void test_iterator(mystl::list<std::pair<int, int>> &l,
                   std::list<std::pair<int, int>> &t) {
    if (*std::prev(l.end()) != *std::prev(t.end())) {
        throw test_exception("iterator behaviour");
    }
    if (*std::next(l.begin()) != *std::next(t.begin())) {
        throw test_exception("iterator behaviour");
    }
}

void test_rule_of_five(mystl::list<std::pair<int, int>> &l,
                       std::list<std::pair<int, int>> &t) {
    mystl::list<std::pair<int, int>> l_copy(l);
    std::list<std::pair<int, int>> t_copy(t);
    if (l_copy != l ||
        !std::equal(l_copy.begin(), l_copy.end(), t.begin(), t.end())) {
        throw test_exception("copy & move assignment and ctor");
    }
    t_copy = t;
    l_copy = l;
    if (l_copy != l ||
        !std::equal(l_copy.begin(), l_copy.end(), t.begin(), t.end())) {
        throw test_exception("copy & move assignment and ctor");
    }
}

void test_reverse_iter(mystl::list<std::pair<int, int>> &l,
                       std::list<std::pair<int, int>> &t) {
    if (!std::equal(l.rbegin(), l.rend(), t.rbegin(), t.rend())) {
        throw test_exception("reverse iterator");
    }
}

void test_erase(mystl::list<std::pair<int, int>> l,
                std::list<std::pair<int, int>> t) {
    auto lit = l.erase(std::next(l.begin(), 2));
    auto tit = t.erase(std::next(t.begin(), 2));
    if (*lit != *tit || !std::equal(l.begin(), l.end(), t.begin(), t.end())) {
        throw test_exception("erase");
    }

    lit = l.erase(lit, std::prev(l.end(), 1));
    tit = t.erase(tit, std::prev(t.end(), 1));
    if (*lit != *tit || !std::equal(l.begin(), l.end(), t.begin(), t.end())) {
        throw test_exception("erase");
    }
}

void test_pop_back_front(mystl::list<std::pair<int, int>> l,
                         std::list<std::pair<int, int>> t) {
    l.pop_back();
    t.pop_back();
    if (!std::equal(l.begin(), l.end(), t.begin(), t.end())) {
        throw test_exception("pop back and pop front");
    }

    l.pop_back();
    t.pop_back();
    if (!std::equal(l.begin(), l.end(), t.begin(), t.end())) {
        throw test_exception("pop back and pop front");
    }

    l.pop_front();
    t.pop_front();
    if (!std::equal(l.begin(), l.end(), t.begin(), t.end())) {
        throw test_exception("pop back and pop front");
    }
}

void test_capacity(mystl::list<std::pair<int, int>> &l,
                   std::list<std::pair<int, int>> &t) {
    if (l.size() != t.size()) {
        throw test_exception("capacity");
    }

    mystl::list<int> l2;
    std::list<int> t2;
    if (l2.empty() != t2.empty()) {
        throw test_exception("capacity");
    }

    l2.emplace_back(1);
    t2.emplace_back(2);
    if (l2.empty() != t2.empty()) {
        throw test_exception("capacity");
    }
}

void test_merge() {
    mystl::list<int> la({1, 3, 5, 40, 50}), lb({2, 3, 4, 45, 70});
    std::list<int> ta({1, 3, 5, 40, 50}), tb({2, 3, 4, 45, 70});
    ta.merge(tb);
    la.merge(lb);
    if (!std::equal(la.begin(), la.end(), ta.begin(), ta.end())) {
        throw test_exception("merge");
    }

    mystl::list<int> lc = la;
    std::list<int> tc = ta;
    lc.merge(mystl::list<int>({3, 5, 7, 9, 70}));
    tc.merge(std::list<int>({3, 5, 7, 9, 70}));
    if (!std::equal(lc.begin(), lc.end(), tc.begin(), tc.end())) {
        throw test_exception("merge");
    }

    mystl::list<std::pair<int, int>> ld({{10, 20}});
    std::list<std::pair<int, int>> td({{10, 20}});
    ld.merge(mystl::list<std::pair<int, int>>{{11, 21}, {13, 23}});
    td.merge(std::list<std::pair<int, int>>{{11, 21}, {13, 23}});
    if (!std::equal(ld.begin(), ld.end(), td.begin(), td.end())) {
        throw test_exception("merge");
    }
}

void test_sort(mystl::list<std::pair<int, int>> &l,
               std::list<std::pair<int, int>> &t) {
    l.sort();
    t.sort();
    if (!std::equal(l.begin(), l.end(), t.begin(), t.end())) {
        throw test_exception("sort");
    }

    mystl::list<int> l2 = {4, 5, 6, 2, 8, 10, 12};
    std::list<int> t2 = {4, 5, 6, 2, 8, 10, 12};
    l2.sort();
    t2.sort();
    if (!std::equal(l2.begin(), l2.end(), t2.begin(), t2.end())) {
        throw test_exception("sort");
    }

    mystl::list<int> l3 = {5, 10, 13, 1, 4, 3, 8};
    std::list<int> t3 = {5, 10, 13, 1, 4, 3, 8};
    l3.sort();
    t3.sort();
    if (!std::equal(l3.begin(), l3.end(), t3.begin(), t3.end())) {
        throw test_exception("sort");
    }
}

int main() {
    mystl::list<std::pair<int, int>> sample({{1, 11}, {2, 12}, {3, 13}});
    std::list<std::pair<int, int>> testcase({{1, 11}, {2, 12}, {3, 13}});

    std::cout << "[Start] Begin emplace front test\n";
    test_emplace_front(sample, testcase);
    std::cout << "[Success] Pass emplace front test\n";

    std::cout << "[Start] Begin emplace test\n";
    test_emplace(sample, testcase);
    std::cout << "[Success] Pass emplace test\n";

    std::cout << "[Start] Begin emplace back test\n";
    test_emplace_back(sample, testcase);
    std::cout << "[Success] Pass emplace back test\n";

    std::cout << "[Start] Begin erase test\n";
    test_erase(sample, testcase);
    std::cout << "[Success] Pass erase test\n";

    std::cout << "[Start] Begin pop back and pop front test\n";
    test_pop_back_front(sample, testcase);
    std::cout << "[Success] Pass pop back and pop front test\n";

    std::cout << "[Start] Begin capacity test\n";
    test_capacity(sample, testcase);
    std::cout << "[Success] Pass capacity test\n";

    std::cout << "[Start] Begin copy & move assignment and ctor test\n";
    test_rule_of_five(sample, testcase);
    std::cout << "[Success] Pass copy & move assignment and ctor test\n";

    std::cout << "[Start] Begin iterator behaviour test\n";
    test_iterator(sample, testcase);
    std::cout << "[Success] Pass iterator behaviour test\n";

    std::cout << "[Start] Begin reverse iterator test\n";
    test_reverse_iter(sample, testcase);
    std::cout << "[Success] Pass reverse iterator test\n";

    std::cout << "[Start] Begin merge test\n";
    test_merge();
    std::cout << "[Success] Pass merge test\n";

    std::cout << "[Start] Begin sort test\n";
    test_sort(sample, testcase);
    std::cout << "[Success] Pass sort test\n";
    return 0;
}
