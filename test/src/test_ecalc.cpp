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
    handlist_collection hands({ ECalc::random_handlist(0), ECalc::random_handlist(0) });
    result_collection res = calc.evaluate(hands, board, dead, NB_SAMPLES);
    CHECK_CLOSE(0.5, res[0].pwin_tie(), 0.05);
  }

  TEST_FIXTURE(Setup, EvaluateSingleVsRandom) {
    cards board, dead;
    handlist_collection hands({ ECalc::single_handlist(Hand("AhAs")), ECalc::random_handlist(0) });
    result_collection res = calc.evaluate(hands, board, dead, NB_SAMPLES);
    CHECK_CLOSE(0.85204, res[0].pwin_tie(), 0.05);
  }
}

