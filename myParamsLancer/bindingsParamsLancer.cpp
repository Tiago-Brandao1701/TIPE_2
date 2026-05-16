// bindings_params.cpp
#include <pybind11/pybind11.h>
#include "ParamsLancer.h"

namespace py = pybind11;

PYBIND11_MODULE(myParamsLancer, m) {
    py::class_<ParamsLancer>(m, "ParamsLancer")
        .def(py::init<double, double, double>(),
             py::arg("phi") = 0.0,
             py::arg("theta") = 0.0,
             py::arg("vitesse") = 0.0)
        .def_readwrite("phi", &ParamsLancer::phi)
        .def_readwrite("theta", &ParamsLancer::theta)
        .def_readwrite("vitesse", &ParamsLancer::vitesse);
}