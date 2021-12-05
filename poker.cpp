#include "poker.h"

player::player() : m_gen(m_rd()), m_number_gen(1, 13), m_suit_gen(0, 3) {}
void player::add_card(int n) {
    for (int i = 0; i < n; ++i)
        m_cards[m_suit_gen(m_gen)].emplace_back(m_number_gen(m_gen));
}

card::card(enum suit suit, int number) : m_suit(suit), m_number(number) {}
