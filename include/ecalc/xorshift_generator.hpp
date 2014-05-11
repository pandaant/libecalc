#ifndef ECALC_XORSHIFT_H
#define ECALC_XORSHIFT_H

#include <limits>
#include <cstdint>

namespace ecalc {
class XOrShiftGenerator {
public:
  static const uint32_t MAX;
  static const uint32_t MIN;

  explicit XOrShiftGenerator(uint32_t _seed = 0) {
    x = 123456789;
    y = 362436069;
    z = 521288629;
    w = 88675123;
    seed(_seed);
  }

  uint32_t operator()() {
    uint32_t t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    w ^= (w >> 19) ^ t ^ (t >> 8);
    return w;
  }

  uint32_t operator()(const uint32_t &max) {
    return static_cast<unsigned>(
        static_cast<double>(XOrShiftGenerator::operator()()) / MAX * max + 1);
  }

  void seed(uint32_t seed) {
    x = seed;
    y = seed + 651688;
    z = seed + 146819;
    w = seed + 84167;
  }

  uint32_t max() const { return MAX; }

  uint32_t min() const { return MIN; }

private:
  uint32_t x, y, z, w;
};
}

#endif
