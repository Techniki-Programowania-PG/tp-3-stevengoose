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
  // Friend allows this function to access private members
  friend Signal operator*(Signal &signal, double &scalar);
  friend Signal operator+(Signal &a, Signal &b);
  friend Signal operator-(Signal &a, Signal &b);

  void show();

private:
  std::vector<double> x;
  std::vector<double> y;
};

Signal operator*(Signal &in, double &scalar);
Signal operator*(double &scalar, Signal &in);

class Sin : public Signal {
public:
  Sin(double frequency, double t_start, double t_end, size_t num_samples);
};

class Cos : public Signal {
public:
  Cos(double frequency, double t_start, double t_end, size_t num_samples);
};

class Square : public Signal {
public:
  Square(double frequency, double t_start, double t_end, size_t num_samples);
};

class Sawtooth : public Signal {
public:
  Sawtooth(double frequency, double t_start, double t_end, size_t num_samples);
};
