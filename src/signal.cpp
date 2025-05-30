#include "signal.h"
#include "matplot/util/common.h"
#include <algorithm>
#include <cmath>
#include <complex>
#include <vector>

// OPERATORS
Signal operator*(const Signal &in, const double &scalar) {
  std::vector<double> result(in.x.size());
  std::transform(in.y.begin(), in.y.end(), result.begin(),
                 [scalar](double v) { return v * scalar; });
  std::vector<double> x = in.x;
  return Signal(x, result);
};
Signal operator*(const double &scalar, const Signal &in) {
  return in * scalar;
};

Signal operator+(const Signal &a, const Signal &b) {
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

Signal operator-(const Signal &a, const Signal &b) {
  if (a.x.empty() || b.x.empty() ||
      a.x.size() / std::abs(a.x.front() - a.x.back()) !=
          b.x.size() / std::abs(b.x.front() - b.x.back())) {
    throw std::invalid_argument(
        "Cannot subtract signals with different amount of samples per second");
  };
  return (-1.0 * b) + a;
};

Signal &Signal::operator*=(const double &scalar) {
  *this = *this * scalar;
  return *this;
};
Signal &Signal::operator+=(const Signal &other) {
  *this = *this + other;
  return *this;
};
Signal &Signal::operator-=(const Signal &other) {
  *this = *this - other;
  return *this;
};

// FUNCTIONS
void Signal::show() {
  // you can't see the square function without expanding the axis
  auto temp = std::minmax_element(y.begin(), y.end());
  double range = std::max(std::abs(*temp.first), std::abs(*temp.second)) + 0.1;
  // Mark all max values on the graph ig
  std::vector<size_t> max_elements;
  for (size_t i = 1; i < y.size() - 1; i++) {
    if (y[i] > y[i - 1] && y[i] > y[i + 1]) {
      std::cout << i << std::endl;
      max_elements.push_back(i);
    };
  };
  matplot::plot(x, y, "-o")->marker_color("r").marker_indices(max_elements);
  matplot::ylim({-range, range});
  matplot::show();
};
void Signal::save(std::string &filename) {
  // you can't see the square function without expanding the axis
  auto temp = std::minmax_element(y.begin(), y.end());
  double range = std::max(std::abs(*temp.first), std::abs(*temp.second)) + 0.1;
  // Mark all max values on the graph ig
  std::vector<size_t> max_elements;
  for (size_t i = 1; i < y.size() - 1; i++) {
    if (y[i] > y[i - 1] && y[i] > y[i + 1]) {
      std::cout << i << std::endl;
      max_elements.push_back(i);
    };
  };
  matplot::plot(x, y, "-o")->marker_color("r").marker_indices(max_elements);
  matplot::ylim({-range, range});
  matplot::save(filename);
};

DFT Signal::dft() {
  int N = y.size();
  std::vector<std::complex<double>> result_y(N);
  std::vector<double> result_x(N);
  double dx = std::abs(x[1] - x[0]);

  for (int k = 0; k < N; k++) {
    std::complex<double> sum(0.0, 0.0);
    for (int n = 0; n < N; n++) {
      sum += std::polar(y[n], -2 * M_PI * n * k / N);
    };
    result_y[k] = sum;
    result_x[k] = (k < (N / 2)) ? (k / (dx * N)) : ((k - N) / (dx * N));
  };
  return DFT(result_x, result_y);
}
void DFT::show_magnitude() {
  std::vector<double> magnitude(y.size());
  std::transform(y.begin(), y.end(), magnitude.begin(),
                 [](std::complex<double> v) { return std::abs(v); });
  matplot::plot(x, magnitude);
  // you can't see the square function without expanding the axis
  double yrange = *std::max_element(magnitude.begin(), magnitude.end()) * 1.1;
  double xrange = *std::max_element(x.begin(), x.end());
  matplot::axis({0, xrange, 0, yrange});
  matplot::show();
};
void DFT::save_magnitude(std::string &filename) {
  std::vector<double> magnitude(y.size());
  std::transform(y.begin(), y.end(), magnitude.begin(),
                 [](std::complex<double> v) { return std::abs(v); });
  matplot::plot(x, magnitude);
  // you can't see the square function without expanding the axis
  double yrange = *std::max_element(magnitude.begin(), magnitude.end()) * 1.1;
  double xrange = *std::max_element(x.begin(), x.end());
  matplot::axis({0, xrange, 0, yrange});
  matplot::save(filename);
};
void DFT::show_phase() {
  std::vector<double> phase(y.size());
  std::transform(y.begin(), y.end(), phase.begin(),
                 [](std::complex<double> v) { return std::arg(v); });
  matplot::plot(x, phase);
  // you can't see the square function without expanding the axis
  double yrange = *std::max_element(phase.begin(), phase.end()) * 1.1;
  double xrange = *std::max_element(x.begin(), x.end());
  matplot::axis({0, xrange, 0, yrange});
  matplot::show();
};
void DFT::save_phase(std::string &filename) {
  std::vector<double> phase(y.size());
  std::transform(y.begin(), y.end(), phase.begin(),
                 [](std::complex<double> v) { return std::arg(v); });
  matplot::plot(x, phase);
  // you can't see the square function without expanding the axis
  double yrange = *std::max_element(phase.begin(), phase.end()) * 1.1;
  double xrange = *std::max_element(x.begin(), x.end());
  matplot::axis({0, xrange, 0, yrange});
  matplot::save(filename);
};
Signal DFT::invert() {
  int N = y.size();
  std::vector<double> result_x(N), result_y(N);
  double dx = 1 / (x[1] * N);
  result_x = matplot::linspace(0, dx * N, N);
  for (int n = 0; n < N; n++) {
    std::complex<double> sum(0.0, 0.0);
    for (int k = 0; k < N; k++) {
      sum += y[k] * std::polar(1.0, 2 * M_PI * k * n / N);
    };
    result_y[n] = std::real(sum) / N;
  };
  return Signal(result_x, result_y);
};
// CONSTRUCTORS
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
