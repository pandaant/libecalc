#ifndef ECALC_H
#define ECALC_H

#define GET_HAND_TRY_MAX 20

#include <poker/hand.hpp>
#include "result.hpp"
#include "types.hpp"
#include "macros.hpp"
#include "handranks.hpp"
#include "handlist.hpp"
#include "xorshift_generator.hpp"

namespace ecalc {
using poker::Hand;
using std::vector;

// ----------------------------------------------------------------------
/// @brief   This class allows to calculate the equity of a hand or
///          range of Hands against other handranges. The result is a
///          struct containing the 3 calculated percentages ( pwin/ptie
///          /plos ) for each range.
// ----------------------------------------------------------------------
class ECalc {
  Handranks &HR;
  XOrShiftGenerator nb_gen;

public:
  // ----------------------------------------------------------------------
  /// @brief  constructs a ECalc object and seeds a generator for it
  ///
  /// @param hr A Lookuptable containing handstrengths
  /// @param seed A seed to initialize the random generator
  // ----------------------------------------------------------------------
  ECalc(Handranks &hr, const uint32_t &seed = 0);

  result_collection evaluate(const Handlist::collection_t &handlists,
                             const cards &boardcards, const cards &deadcards,
                             const int &samples);

  result_collection evaluate_vs_random(Handlist *_handlist,
                                       size_t nb_random_player,
                                       const cards &boardcards,
                                       const cards &deadcards,
                                       const int &samples);

private:
  // ----------------------------------------------------------------------
  /// @brief   lookuptable for divisions from 1/0 to 1/10
  // ----------------------------------------------------------------------
  static const double DLUT[];

  result_collection evaluate(const Handlist::collection_t &handlists,
                             const combination &boardcards, const bitset &deck,
                             const int &samples);

  // ----------------------------------------------------------------------
  /// @brief   draws a card from a deck of cards. The card returned is
  ///          removed from the deck.
  ///
  /// @param deck to pick card from
  ///
  /// @return a card from the deck.
  // ----------------------------------------------------------------------
  card draw_card(bitset &deck);

  // ----------------------------------------------------------------------
  /// @brief   draws boardcards from a deck of cards. if N boardcards are
  ///          already drawn, the function will draw 5 - N random cards
  ///          and remove them from the deck.
  ///
  /// @param board a partially filled board.
  /// @param deck to pick cards from
  // ----------------------------------------------------------------------
  void draw(combination &board, bitset &deck);

  combination get_hand(const handlist &handlist, bitset &deck);
  combination create_board(const cards &_cards) const;
  bitset create_deck(const cards &board, const cards &dead);
  bitset create_bitset(const cards &_cards) const;
};
}

#endif
