#ifndef SINGLE_HANDLIST_H
#define SINGLE_HANDLIST_H

#include "handlist.hpp"

namespace ecalc {

// ----------------------------------------------------------------------
/// @brief   for a range including only one Hand.
// ----------------------------------------------------------------------
class SingleHandlist : public Handlist {
public:

    // ----------------------------------------------------------------------
    /// @brief   constructs a new object from a poker hand. hand is converted
    ///          into internal representation
    ///
    /// @param hand to create list from
    // ----------------------------------------------------------------------
  explicit SingleHandlist(const poker::Hand &hand)
      : hand(Handlist::create_hand(hand)) {}

  ~SingleHandlist() {}

  virtual combination get_hand(XOrShiftGenerator &nb_gen, bitset &deck) {
    card c0 = GET_C0(hand);
    card c1 = GET_C1(hand);
    if (BIT_GET(deck, c0) && BIT_GET(deck, c1)) {
      deck = BIT_CLR(BIT_CLR(deck, c0), c1);
      return hand;
    }
    throw std::runtime_error("Hand not assignable.");
  }

private:
  combination hand;
};
}

#endif
