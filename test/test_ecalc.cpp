#include <iostream>
#include <UnitTest++.h>
#include <ecalc.h>

#define NB_SAMPLES 1000

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
    CHECK_CLOSE(0.5, res[0].pwin_tie(), 0.02);
    CHECK_CLOSE(0.5, res[1].pwin_tie(), 0.02);
  }

  TEST_FIXTURE(Setup, EvaluateSingleVsRandom) {
    cards board, dead;
    result_collection res = calc.evaluate_vs_random(
        ECalc::single_handlist(Hand("AhAs")), 1, board, dead, NB_SAMPLES);
    CHECK_CLOSE(0.85204, res[0].pwin_tie(), 0.02);
    CHECK_CLOSE(1-res[0].pwin_tie(), res[1].pwin_tie(), 0.02);
  }

  TEST_FIXTURE(Setup, AcKdVSJsTs) {
    cards dead;
    cards board(
        {(card)Card("Jh").get_card(), (card)Card("Qd").get_card(), (card)Card("Kh").get_card()});
    handlist_collection hands(
        {ECalc::single_handlist(Hand("AcKd")), ECalc::single_handlist(Hand("JsTs"))});
    result_collection res = calc.evaluate(hands, board, dead, NB_SAMPLES);
    CHECK_CLOSE(0.66313, res[0].pwin_tie(), 0.02);
    CHECK_CLOSE(0.33687, res[1].pwin_tie(), 0.02);
  }

  TEST_FIXTURE(Setup, AcKdVSQQplus) {
    cards dead;
    cards board(
        {(card)Card("Jh").get_card(), (card)Card("Qs").get_card(), (card)Card("Kc").get_card()});

    handlist opp_range({ECalc::create_hand(Hand("AhAs")),
                        ECalc::create_hand(Hand("KhKs")),
                        ECalc::create_hand(Hand("QcQd"))});
    handlist_collection hands(
        {ECalc::single_handlist(Hand("AcKd")), opp_range});
    result_collection res = calc.evaluate(hands, board, dead, NB_SAMPLES);

    std::cout << "win: " << res[0].win << std::endl;
    std::cout << "los: " << res[0].los << std::endl;
    std::cout << "tie: " << res[0].tie << std::endl;
    std::cout << "wintie:" << res[0].pwin_tie() << std::endl << "\n";

    std::cout << "win: " << res[1].win << std::endl;
    std::cout << "los: " << res[1].los << std::endl;
    std::cout << "tie: " << res[1].tie << std::endl;
    std::cout << "wintie:" << res[1].pwin_tie() << std::endl;

    CHECK_CLOSE(0.15118, res[0].pwin_tie(), 0.02);
    CHECK_CLOSE(0.84882, res[1].pwin_tie(), 0.02);
  }

  //TEST_FIXTURE(Setup, AcKdVSQQplusDeadcards) {
    //cards dead(
        //{(card)Card("Jh").get_card(), (card)Card("Qd").get_card(), (card)Card("Kc").get_card()});
    //cards board(
        //{(card)Card("Jh").get_card(), (card)Card("Qd").get_card(), (card)Card("Kc").get_card()});

    //handlist opp_range({ECalc::create_hand(Hand("AhAs")),
                        //ECalc::create_hand(Hand("KhKs")),
                        //ECalc::create_hand(Hand("QcQd"))});
    //handlist_collection hands(
        //{ECalc::single_handlist(Hand("AcKd")), opp_range});
    //result_collection res = calc.evaluate(hands, board, dead, NB_SAMPLES);
    //CHECK_CLOSE(0.15101, res[0].pwin_tie(), 0.02);
    //CHECK_CLOSE(0.84899, res[1].pwin_tie(), 0.02);
  //}

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

