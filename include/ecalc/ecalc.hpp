#ifndef ECALC_H
#define ECALC_H

#define GET_HAND_TRY_MAX 20

#include <poker/hand.hpp>
#include "result.hpp"
#include "types.hpp"
#include "macros.hpp"
#include "handranks.hpp"
#include "xorshift_generator.hpp"

namespace ecalc {
using Poker::Hand;
using std::vector;

class ECalc {
  Handranks &HR;
  xorshift_generator nb_gen;

public:
  /**
   * constructor
   * @param hr      A Lookuptable containing handstrengths
   * @param seed    A seed to initialize the random generator
   */
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
  static handlist array_handlist(const vector<Hand> &hands);
  static combination create_hand(const Hand &hand);

private:
  static const double DLUT[];

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
