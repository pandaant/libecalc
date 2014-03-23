#include <hand.h>
#include <chrono>
#include <vector>
#include <iostream>
#include <UnitTest++.h>
#include <ecalc.h>

SUITE(ECalcBenchmarks) {

  using std::vector;
  using namespace std::chrono;
  using namespace Poker;

  struct Setup {
    ECalc calc;

    Setup() : calc(*(new Handranks("../../bin/data/handranks.dat"))) {}
    ~Setup() {}
  };

  void print_benchmark_result(string name, system_clock::duration duration,
                              int nb_samples) {
    std::cout << name << " | Samples: " << nb_samples << "\t\t\t"
              << duration_cast<seconds>(duration).count() << " s | "
              << duration_cast<milliseconds>(duration).count() << " ms | "
              << duration_cast<microseconds>(duration).count() << " micros"
              << std::endl;
  }

  TEST_FIXTURE(Setup, BenchmarkAhAsVsKhKs) {
    Hand ahas("AhAs");
    Hand khks("KhKs");
    handlist_collection hands(
        {ECalc::single_handlist(ahas.get_lowcard().get_card(),
                                ahas.get_highcard().get_card()),
         ECalc::single_handlist(khks.get_lowcard().get_card(),
                                khks.get_highcard().get_card())});
    cards board, dead;

    auto start = std::chrono::system_clock::now();
    result_collection res = calc.evaluate(hands, board, dead, 10000);
    auto end = std::chrono::system_clock::now();

    print_benchmark_result("AhAs v. KhKs", (end-start), 10000);

    CHECK_CLOSE(0.82637, res[0].pwin_tie(), 0.01);
  }

  TEST_FIXTURE(Setup, BenchmarkAhAsVsRandom) {
    Hand ahas("AhAs");
    handlist_collection hands(
        {ECalc::single_handlist(ahas.get_lowcard().get_card(),
                                ahas.get_highcard().get_card()),
         ECalc::random_handlist(CREATE_HAND(ahas.get_lowcard().get_card(),
                                            ahas.get_highcard().get_card()))});
    cards board, dead;

    auto start = std::chrono::system_clock::now();
    result_collection res = calc.evaluate(hands, board, dead, 10000);
    auto end = std::chrono::system_clock::now();

    print_benchmark_result("AhAs v. Random", (end-start), 10000);
  }

  TEST_FIXTURE(Setup, BenchmarkRandomVsRandom) {
    handlist_collection hands({ECalc::random_handlist(0),
         ECalc::random_handlist(0)});
    cards board, dead;

    auto start = std::chrono::system_clock::now();
    result_collection res = calc.evaluate(hands, board, dead, 10000);
    auto end = std::chrono::system_clock::now();

    print_benchmark_result("2 x Random", (end-start), 10000);
  }

  TEST_FIXTURE(Setup, BenchmarkRandomVsRandomVsRandom) {
    handlist_collection hands({ECalc::random_handlist(0),
         ECalc::random_handlist(0), ECalc::random_handlist(0)});
    cards board, dead;

    auto start = std::chrono::system_clock::now();
    result_collection res = calc.evaluate(hands, board, dead, 10000);
    auto end = std::chrono::system_clock::now();

    print_benchmark_result("3 x Random", (end-start), 10000);
  }

  TEST_FIXTURE(Setup, Benchmark4Random) {
    handlist_collection hands({ECalc::random_handlist(0),
         ECalc::random_handlist(0), ECalc::random_handlist(0), ECalc::random_handlist(0)});
    cards board, dead;

    auto start = std::chrono::system_clock::now();
    result_collection res = calc.evaluate(hands, board, dead, 10000);
    auto end = std::chrono::system_clock::now();

    print_benchmark_result("4 x Random", (end-start), 10000);
  }
}

