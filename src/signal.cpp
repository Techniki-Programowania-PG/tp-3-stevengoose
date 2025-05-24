#include "signal.h"
#include <cmath>
#include <vector>

Signal operator*(Signal &in, double &scalar) {
  std::vector<double> result(in.x.size());
  std::transform(in.y.begin(), in.y.end(), result.begin(),
                 [scalar](double v) { return v * scalar; });
  return Signal(in.x, result);
};

Signal operator*(double &scalar, Signal &in) { return in * scalar; };

// I use them in the lambdas to have them neatly in here,
// honestly we could move the constructors from header file here and puth all of
// these inside the lambdas and loose the tuples i was just doing whatever
// TODO: Move compute functions into constructor lambdas, and move constructor
// lambdas from header file here
std::tuple<std::vector<double>, std::vector<double>>
sin::computeSignalArgs(double frequency, double t_start, double t_end,
                       size_t num_samples) {
  std::vector<double> x = matplot::linspace(t_start, t_end, num_samples);
  std::vector<double> y = matplot::transform(
      x, [frequency](auto x) { return std::sin(2 * M_PI * frequency * x); });
  return {x, y};
};

std::tuple<std::vector<double>, std::vector<double>>
cos::computeSignalArgs(double frequency, double t_start, double t_end,
                       size_t num_samples) {
  std::vector<double> x = matplot::linspace(t_start, t_end, num_samples);
  std::vector<double> y = matplot::transform(
      x, [frequency](auto x) { return std::cos(2 * M_PI * frequency * x); });
  return {x, y};
};

std::tuple<std::vector<double>, std::vector<double>>
square::computeSignalArgs(double frequency, double t_start, double t_end,
                          size_t num_samples) {
  std::vector<double> x = matplot::linspace(t_start, t_end, num_samples);
  std::vector<double> y = matplot::transform(x, [frequency](auto x) {
    return std::pow(-1, std::floor(frequency * x));
  });
  return {x, y};
};

std::tuple<std::vector<double>, std::vector<double>>
sawtooth::computeSignalArgs(double frequency, double t_start, double t_end,
                            size_t num_samples) {
  std::vector<double> x = matplot::linspace(t_start, t_end, num_samples);
  std::vector<double> y = matplot::transform(x, [frequency](auto x) {
    return 2 * ((x / frequency) - std::floor(0.5 + (x / frequency)));
  });
  return {x, y};
};
