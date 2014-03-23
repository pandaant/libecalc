#ifndef ECALC_DEFS_H
#define ECALC_DEFS_H

#include <vector>
#include <stdint.h>

namespace Poker {
typedef unsigned int card;
typedef uint64_t bitset;
typedef uint64_t combination;
typedef std::vector<card> cards;
typedef std::vector<combination> handlist;
typedef std::vector<result> result_collection;
typedef std::vector<handlist> handlist_collection;
};

#endif
