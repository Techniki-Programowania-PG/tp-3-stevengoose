#include <cmath>
#include <complex>
#include <matplot/matplot.h>
#include <vector>

class DFT; // forward declaration to be able to return it from Signal

class Signal {
public:
  enum Type {
    SIN,
    COS,
    SQUARE,
    SAWTOOTH,
  };

  Signal(std::vector<double> &x, std::vector<double> &y) : x{x}, y{y} {};

  Signal &operator*=(const double &scalar);
  Signal &operator+=(const Signal &other);
  Signal &operator-=(const Signal &other);

  // Friend allows this function to access private members
  // const makes it not complain as much + everywhere u look they make it const
  friend Signal operator*(const Signal &signal, double const &scalar);
  friend Signal operator*(const double &scalar, const Signal &in);
  friend Signal operator+(const Signal &a, const Signal &b);
  friend Signal operator-(const Signal &a, const Signal &b);

  DFT dft();
  void show();

private:
  std::vector<double> x;
  std::vector<double> y;
};

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

class DFT {
public:
  DFT(std::vector<double> &x, std::vector<std::complex<double>> &y)
      : x{x}, y{y} {};
  Signal invert();
  void show_magnitude();

private:
  std::vector<double> x;
  std::vector<std::complex<double>> y;
};
