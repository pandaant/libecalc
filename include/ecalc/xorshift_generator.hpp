#ifndef ECALC_XORSHIFT_H
#define ECALC_XORSHIFT_H

#include <limits>
#include <cstdint>

namespace ecalc {

// ----------------------------------------------------------------------
/// @brief   Very Fast PRNG.
// ----------------------------------------------------------------------
class XOrShiftGenerator {
public:
  /// greatest value that can be returned
  static const uint32_t MAX;
  /// smallest value that can be returned
  static const uint32_t MIN;

  // ----------------------------------------------------------------------
  /// @brief   constructs a new generator object and seed the state with
  ///          supplied seed.
  ///
  /// @param seed_ to initialize the random generator
  // ----------------------------------------------------------------------
  explicit XOrShiftGenerator(uint32_t seed_ = 0) {
    x = 123456789;
    y = 362436069;
    z = 521288629;
    w = 88675123;
    seed(seed_);
  }

  // ----------------------------------------------------------------------
  /// @brief get a random number 
  ///
  /// @return a random number beween MIN and MAX
  // ----------------------------------------------------------------------
  uint32_t operator()() {
    uint32_t t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    w ^= (w >> 19) ^ t ^ (t >> 8);
    return w;
  }

  // ----------------------------------------------------------------------
  /// @brief   get a random number between 1 and max
  ///
  /// @param max biggest value returned.
  ///
  /// @return a randomnumber between 1 and max
  // ----------------------------------------------------------------------
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
