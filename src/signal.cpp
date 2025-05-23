#include "signal.h"
#include <vector>

Signal::Signal(Signal::Type type, double frequency, double t_start,
               double t_end, size_t num_samples) {
  switch (type) {
  case Signal::Type::SIN:
    x = matplot::linspace(t_start, t_end, num_samples);
    y = matplot::transform(
        x, [frequency](auto x) { return std::sin(frequency * x); });
    break;
  case Signal::Type::COS:
    break;
  case Signal::Type::SQUARE:
    break;
  case Signal::Type::SAWTOOTH:
    break;
  }
}

Signal::Signal(std::vector<double> &x, std::vector<double> &y) {
  x = x;
  y = y;
}

Signal operator*(Signal &in, double &scalar) {
  std::vector<double> result(in.x.size());
  std::transform(in.y.begin(), in.y.end(), result.begin(),
                 [scalar](double v) { return v * scalar; });
  return Signal(in.x, result);
};

Signal operator*(double &scalar, Signal &in) { return in * scalar; };
