#include <cmath>
#include <matplot/matplot.h>
#include <vector>

class Signal {
public:
  enum Type {
    SIN,
    COS,
    SQUARE,
    SAWTOOTH,
  };

  Signal(std::vector<double> &x, std::vector<double> &y) : x{x}, y{y} {};

  void show();

  std::vector<double> x;
  std::vector<double> y;
};

Signal operator*(Signal &in, double &scalar);
Signal operator*(double &scalar, Signal &in);

class Sin : public Signal {
public:
  Sin(double frequency, double t_start, double t_end, size_t num_samples)
      : Signal([&]() -> Signal {
          std::tuple<std::vector<double>, std::vector<double>> tup =
              computeSignalArgs(frequency, t_start, t_end, num_samples);
          std::vector<double> x = std::get<0>(tup);
          std::vector<double> y = std::get<1>(tup);
          return Signal(x, y);
        }()) {};

private:
  static std::tuple<std::vector<double>, std::vector<double>>
  computeSignalArgs(double frequency, double t_start, double t_end,
                    size_t num_samples);
};

class Cos : public Signal {
public:
  Cos(double frequency, double t_start, double t_end, size_t num_samples)
      : Signal([&]() -> Signal {
          std::tuple<std::vector<double>, std::vector<double>> tup =
              computeSignalArgs(frequency, t_start, t_end, num_samples);
          std::vector<double> x = std::get<0>(tup);
          std::vector<double> y = std::get<1>(tup);
          return Signal(x, y);
        }()) {};

private:
  static std::tuple<std::vector<double>, std::vector<double>>
  computeSignalArgs(double frequency, double t_start, double t_end,
                    size_t num_samples);
};

class Square : public Signal {
public:
  Square(double frequency, double t_start, double t_end, size_t num_samples)
      : Signal([&]() -> Signal {
          std::tuple<std::vector<double>, std::vector<double>> tup =
              computeSignalArgs(frequency, t_start, t_end, num_samples);
          std::vector<double> x = std::get<0>(tup);
          std::vector<double> y = std::get<1>(tup);
          return Signal(x, y);
        }()) {};

private:
  static std::tuple<std::vector<double>, std::vector<double>>
  computeSignalArgs(double frequency, double t_start, double t_end,
                    size_t num_samples);
};

class Sawtooth : public Signal {
public:
  Sawtooth(double frequency, double t_start, double t_end, size_t num_samples)
      : Signal([&]() -> Signal {
          std::tuple<std::vector<double>, std::vector<double>> tup =
              computeSignalArgs(frequency, t_start, t_end, num_samples);
          std::vector<double> x = std::get<0>(tup);
          std::vector<double> y = std::get<1>(tup);
          return Signal(x, y);
        }()) {};

private:
  static std::tuple<std::vector<double>, std::vector<double>>
  computeSignalArgs(double frequency, double t_start, double t_end,
                    size_t num_samples);
};
