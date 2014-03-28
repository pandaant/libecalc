#ifndef ECALC_RESULT_H
#define ECALC_RESULT_H

namespace Poker {
struct result {
  int nb_samples;
  double win;
  double tie;
  double los;

  result(int _nb_samples) : nb_samples(_nb_samples), win(0), tie(0), los(0) {}
  result(int _nb_samples, double _win, double _tie, double _los)
      : nb_samples(_nb_samples), win(_win), tie(_tie), los(_los) {}

  inline double pwin() const { return win / nb_samples; }
  inline double ptie() const { return tie / nb_samples; }
  inline double plos() const { return los / nb_samples; }
  inline double pwin_tie() const { return ((win + tie) / nb_samples); }
  inline int sum() const { return (win + tie + los); }
};
}

#endif
