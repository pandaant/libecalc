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
  ECalc(Handranks* hr, const uint32_t &seed = 0);

  ECalc(const ECalc &oe): HR(oe.HR), nb_gen(oe.nb_gen){}

  //ECalc& operator=(const ECalc &oe){
    //&HR = oe.HR;
    //nb_gen = nb_gen;
    //return *this;
  //}

  // ----------------------------------------------------------------------
  /// @brief   calculates equity for at least 2 handslists 
  ///
  /// @param handlists list of ranges to calculate for
  /// @param boardcards public cards on the board
  /// @param deadcards cards that are not in the deck anymore
  /// @param samples how many simulations to run 
  ///
  /// @return a list of results for each handlist (same order as handlists)
  // ----------------------------------------------------------------------
  result_collection evaluate(const Handlist::collection_t &handlists,
                             const cards &boardcards, const cards &deadcards,
                             const int &samples);

  // ----------------------------------------------------------------------
  /// @brief   calculates the equity of a handlist against at least 1
  ///          random handlist.
  ///
  /// @param handlist handlist that is simulated against nb_random_players
  /// @param nb_random_player number of random handlists to use
  /// @param boardcards public cards on the board
  /// @param deadcards cards that are not in the deck anymore
  /// @param samples how many simulations to run
  ///
  /// @return a list of results for each handlist (same order as handlists).
  ///         The fist result is the handlist from the parameter list.
  // ----------------------------------------------------------------------
  result_collection evaluate_vs_random(Handlist *handlist,
                                       size_t nb_random_player,
                                       const cards &boardcards,
                                       const cards &deadcards,
                                       const int &samples);

private:
  /// lookuptable for divisions from 1/0 to 1/10
  static const double DLUT[];

  // ----------------------------------------------------------------------
  /// @brief   internal evaluation function. is called by other evaluate 
  ///          functions after converting board and deadcards to the 
  ///          internal representation.
  ///
  /// @param handlists list of ranges to calculate for
  /// @param boardcards public cards on the board
  /// @param deck of cards with dead and boardcards removed.
  /// @param samples how many simulations to run 
  ///
  /// @return 
  // ----------------------------------------------------------------------
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

  // ----------------------------------------------------------------------
  /// @brief   converts a collection of cards into the internal bitset
  ///          representation. max 5 cards.
  ///
  /// @param cards_ collection of cards to convert.
  ///
  /// @return internal representation of card collection.
  // ----------------------------------------------------------------------
  combination create_board(const cards &cards_) const;

  // ----------------------------------------------------------------------
  /// @brief   creates a bitset with cards from board and dead removed.
  ///
  /// @param board list of boardcards
  /// @param dead list of deadcards
  ///
  /// @return internal representation of a deck
  // ----------------------------------------------------------------------
  bitset create_deck(const cards &board, const cards &dead);

  // ----------------------------------------------------------------------
  /// @brief   creates a bitset from a collection of cards. max 7 cards
  ///          or overflow will happen. no range check
  ///
  /// @param cards_ collection if cards to covert
  ///
  /// @return bitset representation of cards
  // ----------------------------------------------------------------------
  bitset create_bitset(const cards &cards_) const;
};
}

#endif
