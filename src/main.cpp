#include "signal.h"
#include <matplot/matplot.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;
namespace mp = matplot;

float square(float x) { return x * x; }

void plot() { mp::show(); }

PYBIND11_MODULE(tp3, m) {
  m.def("square", &square);
  m.def("plot", &plot);
}
