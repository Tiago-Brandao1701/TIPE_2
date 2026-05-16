#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include "TrajsTheoriques.h"

namespace py = pybind11;

PYBIND11_MODULE(myTrajsTheoriques, m) {
    m.def("geostatMars", &geostatMars, py::arg("point"));
}
