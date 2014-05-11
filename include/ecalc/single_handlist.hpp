#ifndef SINGLE_HANDLIST_H
#define SINGLE_HANDLIST_H

#include "handlist.hpp"

namespace ecalc {

class SingleHandlist : public Handlist {
public:
  explicit SingleHandlist(const poker::Hand &hand)
      : hand(hand), hand_combination(Handlist::create_hand(hand)) {}

  ~SingleHandlist() {}

  virtual combination get_hand(xorshift_generator &nb_gen, bitset &deck) {
    card c0 = GET_C0(hand_combination);
    card c1 = GET_C1(hand_combination);
    if (BIT_GET(deck, c0) && BIT_GET(deck, c1)) {
      deck = BIT_CLR(BIT_CLR(deck, c0), c1);
      return hand_combination;
    }
    throw std::runtime_error("Hand not assignable.");
  }

private:
  Hand hand;
  combination hand_combination;
};
}

#endif
