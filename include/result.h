#ifndef ECALC_RESULT_H
#define ECALC_RESULT_H

namespace Poker {
struct result {
  double win;
  double tie;
  double los;

  result() : win(0), tie(0), los(0) {}
  result(double _win, double _tie, double _los)
      : win(_win), tie(_tie), los(_los) {}

  inline double pwin() const { return win / sum(); }
  inline double ptie() const { return tie / sum(); }
  inline double plos() const { return los / sum(); }
  inline double pwin_tie() const { return ((win + tie) / sum()); }
  inline int sum() const { return (win + tie + los); }
};
}

#endif
