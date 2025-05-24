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

std::tuple<std::vector<double>, std::vector<double>>
sin::computeSignalArgs(double frequency, double t_start, double t_end,
                       size_t num_samples) {
  std::vector<double> x = matplot::linspace(t_start, t_end, num_samples);
  std::vector<double> y = matplot::transform(
      x, [frequency](auto x) { return std::sin(frequency * x); });
  return {x, y};
};
