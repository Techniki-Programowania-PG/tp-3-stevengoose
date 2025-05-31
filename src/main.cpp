#include "signal.h"
#include <matplot/matplot.h>
#include <pybind11/operators.h>
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
      .def(py::self + py::self)
      .def(py::self - py::self)
      .def(py::self * double())
      .def(double() * py::self)
      .def(py::self *= double())
      .def(py::self += py::self)
      .def(py::self -= py::self)
      .def("dft", &Signal::dft)
      .def("show", &Signal::show)
      .def("save", &Signal::save);
  py::class_<Sin, Signal>(m, "sinwave")
      .def(py::init<double, double, double, size_t>());
  py::class_<Cos, Signal>(m, "coswave")
      .def(py::init<double, double, double, size_t>());
  py::class_<Square, Signal>(m, "squarewave")
      .def(py::init<double, double, double, size_t>());
  py::class_<Sawtooth, Signal>(m, "sawtoothwave")
      .def(py::init<double, double, double, size_t>());
  py::class_<DFT>(m, "dft")
      .def(py::init<std::vector<double> &,
                    std::vector<std::complex<double>> &>())
      .def("invert", &DFT::invert)
      .def("show_magnitude", &DFT::show_magnitude)
      .def("show_phase", &DFT::show_phase)
      .def("save_magnitude", &DFT::save_magnitude)
      .def("save_phase", &DFT::save_phase);
}
