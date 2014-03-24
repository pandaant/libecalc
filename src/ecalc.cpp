#include "ecalc.h"
#include <algorithm>

namespace Poker {
ECalc::ECalc(Handranks &hr, const uint32_t seed) : HR(hr), nb_gen(seed) {}
result_collection ECalc::evaluate(const handlist_collection &handlists,
                                  const cards &boardcards,
                                  const cards &deadcards, const int &samples) {
  bitset deck = create_deck(boardcards, deadcards);
  combination board = create_board(boardcards);
  return evaluate(handlists, board, deck, samples);
}

result_collection ECalc::evaluate(const handlist_collection &handlists,
                                  const combination &boardcards,
                                  const bitset &deck, const int &samples) {
  int nb_handlists = handlists.size();
  result_collection results(handlists.size());
  std::vector<int> sim_winners;
  std::vector<int> sim_scores(nb_handlists);
  handlist sim_hands(nb_handlists);

  bitset sim_deck;
  combination sim_board;

  int s, p, r, c, max_score, nb_winner;
  for (s = 0; s < samples; ++s) {
    sim_winners.clear();

    sim_deck = deck;
    sim_board = boardcards;

    for (p = 0; p < nb_handlists; ++p) {
      sim_hands[p] = get_hand(handlists[p], sim_deck);
    }

    draw(sim_board, sim_deck);

    for (p = 0; p < nb_handlists; ++p) {
      sim_hands[p] |= sim_board;
      sim_scores[p] = LOOKUP_HAND(HR, sim_hands[p]);
    }

    max_score = *std::max_element(sim_scores.begin(), sim_scores.end());

    for (r = 0; r < nb_handlists; ++r) {
      if (sim_scores[r] == max_score)
        sim_winners.push_back(r);
      else
        ++results[r].los;
    }

    nb_winner = sim_winners.size();
    if (nb_winner == 1)
      ++results[sim_winners[0]].win;
    else {
      for (c = 0; c < nb_winner; ++c)
        results[sim_winners[c]].tie += DLUT[nb_winner];
    }
  }

  return results;
}

handlist ECalc::random_handlist(const bitset &deadcards) {
  int c0, c1;
  handlist hands;
  for (c0 = 0; c0 < 51; ++c0) {
    for (c1 = c0 + 1; c1 < 52; ++c1) {
      if (!(BIT_GET(deadcards, c0) || BIT_GET(deadcards, c1)))
        hands.push_back(SET_C1(SET_C0((combination)0, c0), c1));
    }
  }
  return hands;
}

handlist ECalc::single_handlist(const Hand &hand) {
  return handlist({create_hand(hand)});
}

card ECalc::draw_card(bitset &deck) {
  card rand;
  while (true) {
    rand = get_rand(52);
    if (BIT_GET(deck, (rand - 1))) {
      deck = BIT_CLR(deck, (rand - 1));
      return rand;
    }
  }
}

void ECalc::draw(combination &board, bitset &deck) {
  if (GET_C2(board) == CARD_F)
    board = SET_C2(board, draw_card(deck));
  if (GET_C3(board) == CARD_F)
    board = SET_C3(board, draw_card(deck));
  if (GET_C4(board) == CARD_F)
    board = SET_C4(board, draw_card(deck));
  if (GET_C5(board) == CARD_F)
    board = SET_C5(board, draw_card(deck));
  if (GET_C6(board) == CARD_F)
    board = SET_C6(board, draw_card(deck));
}

int ECalc::get_rand(const uint32_t max) {
  return static_cast<double>(nb_gen.rand()) / XORRAND_MAX * max + 1;
}

combination ECalc::create_board(const cards &_cards) const {
  int missing = 5 - _cards.size();
  cards full_board = _cards;
  full_board.resize(5);
  std::fill(full_board.begin() + (5 - missing), full_board.begin() + 5, CARD_F);
  return CREATE_BOARD(full_board[0], full_board[1], full_board[2],
                      full_board[3], full_board[4]);
}

bitset ECalc::create_bitset(const cards &_cards) const {
  bitset bitc = 0;
  for (int c : _cards)
    bitc = BIT_SET(bitc, (c - 1));
  return bitc;
}

bitset ECalc::create_deck(const cards &board, const cards &dead) {
  bitset deck = DECK_M;
  for (int c : board)
    deck = BIT_CLR(deck, (c - 1));
  for (int c : dead)
    deck = BIT_CLR(deck, (c - 1));
  return deck;
}

combination ECalc::create_hand(const Hand &hand) {
  return CREATE_HAND(hand.get_lowcard().get_card(),
                     hand.get_highcard().get_card());
}

combination ECalc::get_hand(const handlist &handlist, bitset &deck) {
  combination hand = handlist[get_rand(handlist.size()) - 1];
  deck = BIT_CLR(deck, (GET_C0(hand) - 1));
  deck = BIT_CLR(deck, (GET_C1(hand) - 1));
  return hand;
}
};
