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

void Signal::show() {
  matplot::plot(x, y);
  // you can't see the square function without expanding the axis
  matplot::ylim({-1.1, 1.1});
  matplot::show();
};

Sin::Sin(double frequency, double t_start, double t_end, size_t num_samples)
    : Signal([&]() -> Signal {
        std::vector<double> x = matplot::linspace(t_start, t_end, num_samples);
        std::vector<double> y = matplot::transform(x, [frequency](auto x) {
          return std::sin(2 * M_PI * frequency * x);
        });
        return Signal(x, y);
      }()) {};

Cos::Cos(double frequency, double t_start, double t_end, size_t num_samples)
    : Signal([&]() -> Signal {
        std::vector<double> x = matplot::linspace(t_start, t_end, num_samples);
        std::vector<double> y = matplot::transform(x, [frequency](auto x) {
          return std::cos(2 * M_PI * frequency * x);
        });
        return {x, y};
      }()) {};

Square::Square(double frequency, double t_start, double t_end,
               size_t num_samples)
    : Signal([&]() -> Signal {
        std::vector<double> x = matplot::linspace(t_start, t_end, num_samples);
        std::vector<double> y = matplot::transform(x, [frequency](auto x) {
          return std::pow(-1, std::floor(frequency * x));
        });
        return {x, y};
      }()) {};

Sawtooth::Sawtooth(double frequency, double t_start, double t_end,
                   size_t num_samples)
    : Signal([&]() -> Signal {
        std::vector<double> x = matplot::linspace(t_start, t_end, num_samples);
        std::vector<double> y = matplot::transform(x, [frequency](auto x) {
          return 2 * ((x / frequency) - std::floor(0.5 + (x / frequency)));
        });
        return Signal(x, y);
      }()) {};
