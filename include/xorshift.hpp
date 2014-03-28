#ifndef ECALC_XORSHIFT_H
#define ECALC_XORSHIFT_H

#define XORRAND_MAX 4294967295

namespace Poker {
struct xorshift {
  uint32_t x = 123456789;
  uint32_t y = 362436069;
  uint32_t z = 521288629;
  uint32_t w = 88675123;

  xorshift(uint32_t _seed = 0) {
      seed(_seed);
  }

  inline uint32_t rand() {
    uint32_t t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    w ^= (w >> 19) ^ t ^ (t >> 8);

    return w;
  }

  void seed(uint32_t seed) {
    x = seed;
    y = seed + 651688;
    z = seed + 146819;
    w = seed + 84167;
  }
};
}

#endif /* XORSHIFT_H */

