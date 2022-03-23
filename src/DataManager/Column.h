#pragma once

#include <string>
#include <vector>

#include "Card.h"

using namespace std;

class Column {
public:
  Column(string title);

  void add_card(Card card, bool put_at_bottom = true);
  void delete_card(size_t card_index);

  bool move_card_up(size_t card_index);
  bool move_card_down(size_t card_index);

  string title;
  vector<Card> cards;
};
