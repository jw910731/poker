#include "poker.h"

#include <cstdlib>

player::player(mystl::list<int> &l) : m_deck(l) {}
int player::add_card(int n) {
    int val;
    for (int i = 0; i < n; ++i) {
        auto it = std::next(m_deck.begin(), rand() % m_deck.size());
        val = *it;
        m_deck.erase(it);
        m_cards[val % 4].emplace_back(val / 4);
    }
    return val;
}

card::card(int number) : m_number(number) {}

bool card::operator<(const card &c) const {
    if (c.m_number == 0)
        return true;
    if (m_number == 0)
        return false;
    return m_number < c.m_number;
}

std::ostream &operator<<(std::ostream &os, const card &c) {
    if (c.m_number == 0) {
        os << 'A';
    } else {
        os << c.m_number + 1;
    }
    return os;
}
