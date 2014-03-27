#include <iostream>
#include <UnitTest++.h>
#include <ecalc.h>

#define NB_SAMPLES 10000

SUITE(ECalcTests) {

  using std::vector;
  using namespace Poker;

  struct Setup {
    ECalc calc;

    Setup() : calc(*(new Handranks("../../../bin/data/handranks.dat"))) {}
    ~Setup() {}
  };

  TEST_FIXTURE(Setup, EvaluateRandom) {
    cards board, dead;
    handlist_collection hands(
        {ECalc::random_handlist(0), ECalc::random_handlist(0)});
    result_collection res = calc.evaluate(hands, board, dead, NB_SAMPLES);
    CHECK_CLOSE(0.5, res[0].pwin_tie(), 0.05);
  }

  TEST_FIXTURE(Setup, EvaluateSingleVsRandom) {

    cards board, dead;
    result_collection res = calc.evaluate_vs_random(
        ECalc::single_handlist(Hand("AhAs")), 1, board, dead, NB_SAMPLES);
    CHECK_CLOSE(0.85204, res[0].pwin_tie(), 0.05);
  }

  /**
    * Special case when 2 or more players
    * have almost the same range. The
    * second player cant be assigned a hand
   **/
  TEST_FIXTURE(Setup, TestRangeSmallAndEqual) {
    // mark all but 2 cards as dead
    cards board, deadc;
    bitset dead = 0x3ffffffffffff;
    handlist_collection hands(
        {ECalc::random_handlist(dead), ECalc::random_handlist(dead)});
    try {
      result_collection res = calc.evaluate(hands, board, deadc, NB_SAMPLES);
      CHECK(false);
    }
    catch (std::runtime_error e) {
      CHECK(true);
    }
  }
}

