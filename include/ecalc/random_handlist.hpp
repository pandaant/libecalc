#ifndef RANDOM_HANDLIST_H
#define RANDOM_HANDLIST_H

#include "array_handlist.hpp"

namespace ecalc {

class RandomHandlist : public ArrayHandlist {
public:
  explicit RandomHandlist(const bitset &deadcards = 0)
      : ArrayHandlist(create_hands(deadcards)) {}

  static vector<combination> create_hands(const bitset &deadcards) {
    int c0, c1;
    vector<combination> hands;
    for (c0 = 1; c0 < 52; ++c0) {
      for (c1 = c0 + 1; c1 < 53; ++c1) {
        if (!(BIT_GET(deadcards, c0) || BIT_GET(deadcards, c1)))
          hands.push_back(CREATE_HAND(c0, c1));
      }
    }
    return hands;
  }
};
}

#endif
