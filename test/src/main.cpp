#include<tr1/random>
#include<chrono>
#include<iostream>
#include "ecalc.h"
#include "handranks.h"

using namespace Poker;


int main() {
  using namespace std::chrono;
  Handranks *rd;
  try {
    rd = new Handranks("../../bin/data/handranks.dat");
  }
  catch (std::runtime_error e) {
    std::cout << e.what() << std::endl;
    return -1;
  }

  cards dead;
  cards board;

  handlist_collection cc;

  card bot_card1 = 51;
  card bot_card2 = 50;
  card bot_card3 = 33;
  card bot_card4 = 32;
  combination bot_hand = 0;
  combination bot_hand2 = 0;
  bot_hand = SET_C0(bot_hand, bot_card1);
  bot_hand = SET_C1(bot_hand, bot_card2);

  bot_hand2 = SET_C0(bot_hand2, bot_card3);
  bot_hand2 = SET_C1(bot_hand2, bot_card4);
  cc.push_back(handlist({bot_hand}));
  // cc.push_back(handlist({bot_hand2}));

  bitset deadset = 0;
  deadset = BIT_SET(deadset, bot_card1);
  deadset = BIT_SET(deadset, bot_card2);
  cc.push_back(ECalc::hand_combinations(deadset));

  ECalc ecalc(*rd, std::tr1::random_device()());

  auto start_bitset = steady_clock::now();
  result_collection results = ecalc.evaluate(cc, board, dead, 10000);
  auto end_bitset = steady_clock::now();
  auto diff_bitset =
      duration_cast<microseconds>(end_bitset - start_bitset).count();

  std::cout << "win: " << results[0].pwin() << std::endl;
  std::cout << "tie: " << results[0].ptie() << std::endl;
  std::cout << "los: " << results[0].plos() << std::endl;
  std::cout << "pwt: " << results[0].pwin_tie() << std::endl;

  std::cout << "time: " << diff_bitset << " micros.\n";

  return 0;
}
