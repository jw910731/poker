#include "list.h"

#include <list>
#include <ostream>

enum suit { C, D, H, S };

class card {
  public:
    int m_number;
    card(int number);
    card() = default;
    bool operator<(const card &c) const;
};

std::ostream &operator<<(std::ostream &os, const card &c);

class player {
    mystl::list<int> &m_deck;

  public:
    mystl::list<card> m_cards[4];
    player(mystl::list<int> &l);
    void add_card(int n);
};
