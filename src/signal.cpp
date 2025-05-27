#include "signal.h"
#include <algorithm>
#include <cmath>
#include <vector>

Signal operator*(Signal &in, double &scalar) {
  std::vector<double> result(in.x.size());
  std::transform(in.y.begin(), in.y.end(), result.begin(),
                 [scalar](double v) { return v * scalar; });
  return Signal(in.x, result);
};
Signal operator*(double &scalar, Signal &in) { return in * scalar; };

Signal operator+(Signal &a, Signal &b) {
  if (a.x.empty() || b.x.empty() ||
      a.x.size() / std::abs(a.x.front() - a.x.back()) !=
          b.x.size() / std::abs(b.x.front() - b.x.back())) {
    throw std::invalid_argument(
        "Cannot add signals with different amount of samples per second");
  };
  double resolution = a.x.size() / std::abs(a.x.front() - a.x.back());
  double t_start = std::min(a.x.front(), b.x.front());
  double t_end = std::max(a.x.back(), b.x.back());
  std::vector<double> x =
      matplot::linspace(t_start, t_end, resolution * (t_end - t_start));
  std::vector<double> y_a = a.y, y_b = b.y;
  if (a.x.front() > t_start) {
    y_a.insert(y_a.begin(), (a.x.front() - t_start) * resolution, 0.0);
  } else if (b.x.front() > t_start) {
    y_b.insert(y_b.begin(), (b.x.front() - t_start) * resolution, 0.0);
  };

  if (a.x.back() < t_end) {
    y_a.insert(y_a.end(), (t_end - a.x.back()) * resolution, 0.0);
  } else if (b.x.back() < t_end) {
    y_b.insert(y_b.end(), (t_end - b.x.back()) * resolution, 0.0);
  };
  std::vector<double> y(y_a.size());
  std::transform(y_a.begin(), y_a.end(), y_b.begin(), y.begin(), std::plus<>());
  return Signal(x, y);
};

Signal operator-(Signal &a, Signal &b) {
  if (a.x.empty() || b.x.empty() ||
      a.x.size() / std::abs(a.x.front() - a.x.back()) !=
          b.x.size() / std::abs(b.x.front() - b.x.back())) {
    throw std::invalid_argument(
        "Cannot subtract signals with different amount of samples per second");
  };
  std::vector<double> c_y(b.y.size());
  std::transform(b.y.begin(), b.y.end(), c_y.begin(),
                 [](double v) { return v * (-1); });
  Signal c(b.x, c_y);
  return a + c;
};

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
