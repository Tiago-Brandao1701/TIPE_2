#include <pybind11/pybind11.h>
#include "Bornes.h"
#include "ParamsLancer.h"

namespace py = pybind11;

PYBIND11_MODULE(myBornes, m){

    py::class_<Bornes>(m, "Bornes")
        .def(py::init<const ParamsLancer&, const ParamsLancer&>(),
        py::arg("min") = ParamsLancer(), py::arg("max") = ParamsLancer())
        .def_readwrite("min", &Bornes::min)
        .def_readwrite("max", &Bornes::max);
}