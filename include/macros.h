#ifndef ECALC_MACROS_H
#define ECALC_MACROS_H

// mask for one card
#define CARD_F 0
#define CARD_M 0xFF
#define DECK_M 0x000FFFFFFFFFFFFF

// card masks
#define CARD0_M 0xFFFFFFFFFFFFFF00
#define CARD1_M 0xFFFFFFFFFFFF00FF
#define CARD2_M 0xFFFFFFFFFF00FFFF
#define CARD3_M 0xFFFFFFFF00FFFFFF
#define CARD4_M 0xFFFFFF00FFFFFFFF
#define CARD5_M 0xFFFF00FFFFFFFFFF
#define CARD6_M 0xFF00FFFFFFFFFFFF

// retrive cards
// combination c
#define GET_C0(c) ((c) & CARD_M)
#define GET_C1(c) ((c >> 8) & CARD_M)
#define GET_C2(c) ((c >> 16) & CARD_M)
#define GET_C3(c) ((c >> 24) & CARD_M)
#define GET_C4(c) ((c >> 32) & CARD_M)
#define GET_C5(c) ((c >> 40) & CARD_M)
#define GET_C6(c) ((c >> 48) & CARD_M)

// set cards
// combination c
// card v
#define M_CARD(v) ((combination)((v) & CARD_M))
#define SET_C0(c, v) ((c &CARD0_M) | M_CARD(v))
#define SET_C1(c, v) ((c &CARD1_M) | (M_CARD(v) << 8))
#define SET_C2(c, v) ((c &CARD2_M) | (M_CARD(v) << 16))
#define SET_C3(c, v) ((c &CARD3_M) | (M_CARD(v) << 24))
#define SET_C4(c, v) ((c &CARD4_M) | (M_CARD(v) << 32))
#define SET_C5(c, v) ((c &CARD5_M) | (M_CARD(v) << 40))
#define SET_C6(c, v) ((c &CARD6_M) | (M_CARD(v) << 48))

// bitset functions
// bitset b
// index i (int)
#define BIT_M ((bitset)1)
#define BIT_SET(b, i) (b | (BIT_M << i))
#define BIT_CLR(b, i) (b & ~(BIT_M << i))
#define BIT_GET(b, i) (b &(BIT_M << i))

// set board. not existing cards should be 254
#define CREATE_BOARD(f1, f2, f3, t, r)                                         \
  SET_C6(SET_C5(SET_C4(SET_C3(SET_C2((bitset)0, f1), f2), f3), t), r)

#define CREATE_HAND(c0, c1) SET_C1(SET_C0((combination)0, c0), c1)

#define LOOKUP_HAND(HR, c)                                                     \
  HR[HR[HR[HR[HR[HR[HR[53 + GET_C0(c)] + GET_C1(c)] + GET_C2(c)] +             \
              GET_C3(c)] +                                                     \
           GET_C4(c)] +                                                        \
        GET_C5(c)] +                                                           \
     GET_C6(c)];

#endif
