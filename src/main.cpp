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
  py::class_<Signal>(m, "signal")
      .def(py::init<std::vector<double> &, std::vector<double> &>())
      .def("show", &Signal::show);
  py::class_<Sin, Signal>(m, "sinwave")
      .def(py::init<double, double, double, size_t>());
  py::class_<Cos, Signal>(m, "coswave")
      .def(py::init<double, double, double, size_t>());
  py::class_<Square, Signal>(m, "squarewave")
      .def(py::init<double, double, double, size_t>());
  py::class_<Sawtooth, Signal>(m, "sawtoothwave")
      .def(py::init<double, double, double, size_t>());
}
