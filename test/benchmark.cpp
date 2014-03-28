#include <hand.h>
#include <chrono>
#include <vector>
#include <iostream>
#include <UnitTest++.h>
#include <ecalc.hpp>

#define NB_SAMPLES 10000

SUITE(ECalcBenchmarks) {

  using std::vector;
  using namespace std::chrono;
  using namespace Poker;

  struct Setup {
    ECalc calc;

    Setup() : calc(*(new Handranks("../../../bin/data/handranks.dat"))) {}
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
    cards board, dead;
    handlist_collection hands({ECalc::single_handlist(Hand("AhAs")),
                               ECalc::single_handlist(Hand("KhKs"))});

    auto start = std::chrono::system_clock::now();
    result_collection res = calc.evaluate(hands, board, dead, NB_SAMPLES);
    auto end = std::chrono::system_clock::now();

    CHECK_CLOSE(0.82637, res[0].pwin_tie(), 0.01);
    print_benchmark_result("AhAs v. KhKs", (end - start), NB_SAMPLES);
  }

  TEST_FIXTURE(Setup, BenchmarkAhAsVsRandom) {
    cards board, dead;

    auto start = std::chrono::system_clock::now();
    result_collection res = calc.evaluate_vs_random(ECalc::single_handlist(Hand("AhAs")),
                                          1, board, dead, NB_SAMPLES);
    auto end = std::chrono::system_clock::now();

    print_benchmark_result("AhAs v. Random", (end - start), NB_SAMPLES);
  }

  TEST_FIXTURE(Setup, BenchmarkRandomVsRandom) {
    cards board, dead;
    handlist_collection hands(
        {ECalc::random_handlist(0), ECalc::random_handlist(0)});

    auto start = std::chrono::system_clock::now();
    result_collection res = calc.evaluate(hands, board, dead, NB_SAMPLES);
    auto end = std::chrono::system_clock::now();

    print_benchmark_result("2 x Random", (end - start), NB_SAMPLES);
  }

  TEST_FIXTURE(Setup, BenchmarkRandomVsRandomVsRandom) {
    handlist_collection hands({ECalc::random_handlist(0),
                               ECalc::random_handlist(0),
                               ECalc::random_handlist(0)});
    cards board, dead;

    auto start = std::chrono::system_clock::now();
    result_collection res = calc.evaluate(hands, board, dead, NB_SAMPLES);
    auto end = std::chrono::system_clock::now();

    print_benchmark_result("3 x Random", (end - start), NB_SAMPLES);
  }

  TEST_FIXTURE(Setup, Benchmark4Random) {
    handlist_collection hands(
        {ECalc::random_handlist(0), ECalc::random_handlist(0),
         ECalc::random_handlist(0), ECalc::random_handlist(0)});
    cards board, dead;

    auto start = std::chrono::system_clock::now();
    result_collection res = calc.evaluate(hands, board, dead, NB_SAMPLES);
    auto end = std::chrono::system_clock::now();

    print_benchmark_result("4 x Random", (end - start), NB_SAMPLES);
  }
}

