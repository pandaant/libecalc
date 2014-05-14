#ifndef ECALC_HANDRANKS_H
#define ECALC_HANDRANKS_H

#include <cstdio>
#include <string.h>
#include <stdexcept>

//http://lbrandy.com/blog/2010/11/memory-mapped-io-for-fun-and-profit/
namespace ecalc {
class Handranks {
  int HR[32487834];

public:
  static Handranks* construct(const char *filename){
    return new Handranks(filename);
  }

  ~Handranks(){}

  const int &operator[](const unsigned &i) const { return HR[i]; }

  bool load_handranks(const char *filename) {
    memset(HR, 0, sizeof(HR));
    FILE *fin = fopen(filename, "rb");
    if (!fin)
      return false;

    fread(HR, sizeof(HR), 1, fin);
    fclose(fin);
    return true;
  }

private:
  Handranks(const Handranks &hr) = default;
  Handranks &operator=(const Handranks &hr) = default;
  Handranks(const char *filename) {
    if (!load_handranks(filename))
      throw std::runtime_error("Handranks file could not be loaded.");
  }
};
}

#endif
