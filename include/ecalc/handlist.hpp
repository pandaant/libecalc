#ifndef HANDLIST_H
#define HANDLIST_H

#include "types.hpp"
#include "xorshift_generator.hpp"

namespace ecalc {

// ----------------------------------------------------------------------
/// @brief   base class the range for every player. class must be over-
///          loaded with own implementation.
// ----------------------------------------------------------------------
class Handlist {
public:
  typedef std::vector<Handlist*> collection_t;

  virtual ~Handlist() {}
  virtual combination get_hand(xorshift_generator &nb_gen, bitset &deck) = 0;

  static combination create_hand(const poker::Hand &hand) {
    return CREATE_HAND(hand.lowcard().card(), hand.highcard().card());
  }
};
}

#endif
