#include "list.h"
#include "poker.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <list>
#include <unordered_map>

const std::unordered_map<char, int>
    suit_mp({{'C', 0}, {'D', 1}, {'H', 2}, {'S', 3}});
char suit_arr[4] = {'C', 'D', 'H', 'S'};

int main() {
    srand(time(NULL));
    mystl::list<int> deck;
    for (int i = 0; i < 54; ++i) {
        deck.emplace_back(i);
    }
    player p[2]{deck, deck};
    int cmd, player = 0;
    while (true) {
        std::cout << "Now operating on player " << player + 1 << "\n";
        std::cout << "0) Quit\n"
                     "1) Deal n cards to player\n"
                     "2) Print card of specific suit with deal order\n"
                     "3) Print card of specific suit with reverse deal order\n"
                     "4) Print card of specific suit with size order\n"
                     "5) Delete card of specific suit\n"
                     "6) Switch operating player\n";
        std::cout << "Input command: ";
        std::cin >> cmd;
        switch (cmd) {
        case 0:
            return 0;
        case 1: {
            int n;
            std::cout << "How much card to deal to player " << player + 1
                      << ": ";
            std::cin >> n;
            if (n > int(deck.size())) {
                std::cout << "No enough card in deck to deal.";
                break;
            }
            p[player].add_card(n);
            break;
        }
        case 2: {
            std::cout << "Which suit? (C, D, H, S): ";
            char s;
            std::cin >> s;
            auto f = suit_mp.find(s);
            if (f == suit_mp.end()) {
                std::cout << "Input error\n";
                break;
            }
            int suit = f->second;
            std::cout << "Result: ";
            for (const auto &v : p[player].m_cards[suit]) {
                std::cout << v << ' ';
            }
            std::cout << '\n';
            break;
        }
        case 3: {
            std::cout << "Which suit? (C, D, H, S): ";
            char s;
            std::cin >> s;
            auto f = suit_mp.find(s);
            if (f == suit_mp.end()) {
                std::cout << "Input error\n";
                break;
            }
            int suit = f->second;
            std::cout << "Result: ";
            for (auto it = p[player].m_cards[suit].rbegin();
                 it != (p[player].m_cards[suit].rend()); ++it) {
                const auto &v = *it;
                std::cout << v << ' ';
            }
            std::cout << '\n';
            break;
        }
        case 4: {
            std::cout << "Which suit? (C, D, H, S): ";
            char s;
            std::cin >> s;
            auto f = suit_mp.find(s);
            if (f == suit_mp.end()) {
                std::cout << "Input error\n";
                break;
            }
            int suit = f->second;
            std::cout << "Result: ";
            mystl::list<card> sorted = p[player].m_cards[suit];
            sorted.sort();
            for (auto it = sorted.begin(); it != sorted.end(); ++it) {
                const auto &v = *it;
                std::cout << v << ' ';
            }
            std::cout << '\n';
            break;
        }
        case 5: {
            std::cout << "Which suit? (C, D, H, S): ";
            char s;
            std::cin >> s;
            auto f = suit_mp.find(s);
            if (f == suit_mp.end()) {
                std::cout << "Input error\n";
                break;
            }
            int suit = f->second;
            std::cout << "Which card number(1~13, 1 is Ace): ";
            int card_num;
            std::cin >> card_num;
            if (card_num < 1 || card_num > 13) {
                std::cout << "Invalid Input\n";
                break;
            }
            card_num--;
            mystl::list<card> sorted = p[player].m_cards[suit];
            sorted.sort();
            auto target =
                std::upper_bound(sorted.begin(), sorted.end(), card(card_num));
            if (target == sorted.end()) {
                std::cout << "Not found. The smallest card is "
                          << (*sorted.begin()).m_number + 1 << '\n';
            } else {
                std::cout << "Erase " << suit_arr[suit]
                          << (*target).m_number + 1 << '\n';
                for (auto it = p[player].m_cards[suit].begin();
                     it != p[player].m_cards[suit].end(); ++it) {
                    if ((*it).m_number == (*target).m_number) {
                        p[player].m_cards[suit].erase(it);
                        break;
                    }
                }
            }
            break;
        }
        case 6: {
            int p;
            std::cout << "Switch to player 1 or 2: ";
            std::cin >> p;
            if (p != 1 && p != 2) {
                std::cout << "Input error\n";
                break;
            }
            player = p - 1;
            break;
        }
        default:
            std::cout << "Error: command error\n";
            break;
        }
    }
    return 0;
}
