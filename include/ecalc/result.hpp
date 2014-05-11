#ifndef ECALC_RESULT_H
#define ECALC_RESULT_H

namespace ecalc {

// ----------------------------------------------------------------------
/// @brief   stores the equities for one range in the evaluation process.
// ----------------------------------------------------------------------
struct result {

  // ----------------------------------------------------------------------
  /// @brief   sum of all simulations played
  // ----------------------------------------------------------------------
  int nb_samples;

  // ----------------------------------------------------------------------
  /// @brief   number of times range won a simulation
  // ----------------------------------------------------------------------
  double win;

  // ----------------------------------------------------------------------
  /// @brief   number of times range tied with one or more ranges.
  ///          When a outcome is tied every winning player gets 1/N points
  ///          added to his tievalue where N is number of tieplayers.
  // ----------------------------------------------------------------------
  double tie;

  // ----------------------------------------------------------------------
  /// @brief   number of times handlist lost a simulation.
  // ----------------------------------------------------------------------
  double los;

  result(int _nb_samples) : nb_samples(_nb_samples), win(0), tie(0), los(0) {}
  result(int _nb_samples, double _win, double _tie, double _los)
      : nb_samples(_nb_samples), win(_win), tie(_tie), los(_los) {}

  inline double pwin() const { return win / nb_samples; }
  inline double ptie() const { return tie / nb_samples; }
  inline double plos() const { return los / nb_samples; }
  inline double pwin_tie() const { return ((win + tie) / nb_samples); }
  inline double sum() const { return (win + tie + los); }
};
}

#endif
