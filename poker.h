#include "list.h"

#include <random>

enum suit { C, D, H, S };

class card {
    enum suit m_suit;
    int m_number;

  public:
    card(enum suit suit, int number);
};

class player {
    mystl::list<card> m_cards[4];
    std::random_device m_rd;
    std::mt19937 m_gen;
    std::uniform_int_distribution<> m_number_gen, m_suit_gen;
    player();
    void add_card(int n);
};
