#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include "SimulationLancer.h"

namespace py = pybind11;

PYBIND11_MAKE_OPAQUE(std::vector<Astre>);
PYBIND11_MAKE_OPAQUE(std::vector<Vecteur>);

PYBIND11_MODULE(mySimulationLancer, m) {

    py::class_<SimulationLancer>(m, "SimulationLancer")
        .def(py::init<std::vector<Astre>&, const Astre&, const Astre&>(),
            py::arg("astres"), py::arg("cible"), py::arg("terre"))
        .def("simulation", &SimulationLancer::simulation)
        .def("initTrajectoires",&SimulationLancer::initTrajectoires)
        .def_readwrite("paramsLancer", &SimulationLancer::paramsLancer)
        .def_readwrite("nbSimulations" , &SimulationLancer::nbSimulations);
}
