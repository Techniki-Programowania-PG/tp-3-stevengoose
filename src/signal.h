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

  Signal(Type type, double frequency, double t_start, double t_end,
         size_t num_samples);
  Signal(std::vector<double> &x, std::vector<double> &y);
  std::vector<double> x;
  std::vector<double> y;
};

Signal operator*(Signal &in, double &scalar);
Signal operator*(double &scalar, Signal &in);

class sin : public Signal {
public:
  sin(double frequency, double t_start, double t_end, size_t num_samples)
      : Signal(Signal::Type::SIN, frequency, t_start, t_end, num_samples) {};
};

class cos : public Signal {
public:
  cos(double frequency, double t_start, double t_end, size_t num_samples)
      : Signal(Signal::Type::COS, frequency, t_start, t_end, num_samples) {};
};

class square : public Signal {
public:
  square(double frequency, double t_start, double t_end, size_t num_samples)
      : Signal(Signal::Type::SQUARE, frequency, t_start, t_end, num_samples) {};
};

class sawtooth : public Signal {
public:
  sawtooth(double frequency, double t_start, double t_end, size_t num_samples)
      : Signal(Signal::Type::SAWTOOTH, frequency, t_start, t_end, num_samples) {
        };
};
