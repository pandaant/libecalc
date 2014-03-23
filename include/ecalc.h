#ifndef ECALC_H
#define ECALC_H

#include "result.h"
#include "types.h"
#include "macros.h"
#include "handranks.h"
#include "xorshift.h"

namespace Poker {

const double DLUT[] = {0,                   1,                   0.5,
                       0.33333333333333333, 0.25,                0.2,
                       0.16666666666666666, 0.14285714285714285, 0.125,
                       0.11111111111111111, 0.1};
class ECalc {
  Handranks &HR;
  xorshift nb_gen;

public:
  ECalc(Handranks &hr, const uint32_t seed = 0);
  result_collection evaluate(const handlist_collection &handlists,
                             const cards &boardcards, const cards &deadcards,
                             const int &samples);
  static handlist hand_combinations(const bitset &deadcards);

private:
  result_collection evaluate(const handlist_collection &handlists,
                             const combination &boardcards, const bitset &deck,
                             const int &samples);
  card draw_card(bitset &deck);
  int get_rand(const uint32_t max);
  // void combination_to_stdout(combination c);
  void draw(combination &board, bitset &deck);
  combination get_hand(const handlist &handlist, bitset &deck);
  combination create_board_from_cards(const cards &_cards) const;
  bitset create_bitset_from_cards(const cards &_cards) const;
  bitset create_deck_from_cards(const cards &board, const cards &dead);
};
};

#endif
