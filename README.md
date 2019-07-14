# Libecalc
Libecalc lets you compare Poker Hands and Ranges.

## Requirements
* UnitTest++ for tests (expects headers and lib to be in /usr/{lib,include})

## Build
```bash
$ git clone --recursive https://github.com/pandaant/libecalc

# compile dependencies
$ cd libecalc/dep/libpoker
$ make all

# compile lib
$ cd ../../
$ make all

# build documentation (requires doxygen)
$ make doc

# if you want to run tests
$ cd test 
$ make all run
```

## Usage

### Initialization

```c++
using namespace ecalc;
using namespace poker;

// supply path to handranks file. 
Handranks handranks("handranks.dat");
// initialize ecalc with handranks and seed for rng
ECalc calc(&handranks, 0);
```

### Evaluate Hand vs Random

```c++
// supply vector of cards that is present on the board already (preflop)
cards board, dead;

// Create a handlist with a single specific hand.
Handlist* hand = new SingleHandlist(Hand("AhAs"));

// evaluate hand against random sampled hands
result_collection res = calc.evaluate_vs_random(
    hand,  		// handlist
    1, 			// number of random players to check against
    board, 		// the boardcards
    dead, 		// list of deadcards
    NB_SAMPLES);// number of samples to use. the higher the better

// res stores the percentage of win,tie and loss in a vector for each hand
cout << "pwin: " << res[0].pwin_tie() << endl; // 0.85204
delete hand;
```
### Evaluate 2 specific Hands with board cards

```c++
cards dead;
cards board({(card)Card("Jh").card(), (card)Card("Qd").card(),
             (card)Card("Kh").card()});

Handlist::collection_t hands({new SingleHandlist(Hand("AcKd")),
                              new SingleHandlist(Hand("JsTs"))});

result_collection res = calc.evaluate(hands, board, dead, NB_SAMPLES);
// res[0].pwin_tie() => 0.66313
// res[1].pwin_tie() => 0.33687

for( unsigned i = 0; i < hands.size(); ++i)
    delete hands[i];
```
### Evaluate Hand ranges with board cards

```c++
cards dead;
cards board({(card)Card("Jh").card(), (card)Card("Qd").card(),
             (card)Card("Kh").card()});

Handlist::collection_t hands({
	new SingleHandlist(Hand("AcKd")),
    new ArrayHandlist({Hand("AhAs"), Hand("KhKs"), Hand("QcQd")})
});

result_collection res = calc.evaluate(hands, board, dead, NB_SAMPLES);

for( unsigned i = 0; i < hands.size(); ++i)
    delete hands[i];
```