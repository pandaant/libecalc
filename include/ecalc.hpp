#ifndef ECALC_H
#define ECALC_H

#define GET_HAND_TRY_MAX 20

#include <poker/hand.h>
#include "result.hpp"
#include "types.hpp"
#include "macros.hpp"
#include "handranks.hpp"
#include "xorshift.hpp"

namespace Poker {

const double DLUT[] = { 0,                   1,                   0.5,
                        0.33333333333333333, 0.25,                0.2,
                        0.16666666666666666, 0.14285714285714285, 0.125,
                        0.11111111111111111, 0.1 };
class ECalc {
  Handranks &HR;
  xorshift nb_gen;

public:
  ECalc(Handranks &hr, const uint32_t seed = 0);
  result_collection evaluate(const handlist_collection &handlists,
                             const cards &boardcards, const cards &deadcards,
                             const int &samples);
  result_collection evaluate_vs_random(const handlist &_handlist,
                                       size_t nb_random_player,
                                       const cards &boardcards,
                                       const cards &deadcards,
                                       const int &samples);
  static handlist single_handlist(const Hand &hand);
  static handlist random_handlist(const bitset &deadcards);
  static combination create_hand(const Hand &hand);

private:
  result_collection evaluate(const handlist_collection &handlists,
                             const combination &boardcards, const bitset &deck,
                             const int &samples);
  card draw_card(bitset &deck);
  unsigned get_rand(const uint32_t max);
  void draw(combination &board, bitset &deck);
  combination get_hand(const handlist &handlist, bitset &deck);
  combination create_board(const cards &_cards) const;
  bitset create_deck(const cards &board, const cards &dead);
  bitset create_bitset(const cards &_cards) const;
};
}

#endif
