#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/functional.h>
#include <pybind11/stl_bind.h>

#include "Astre.h"
#include "TrouveCI.h"

namespace py = pybind11;

PYBIND11_MAKE_OPAQUE(std::vector<Vecteur>);
PYBIND11_MAKE_OPAQUE(std::vector<Astre>);

PYBIND11_MODULE(myTrouveCI, m) {

    py::bind_vector<std::vector<Astre>>(m, "AstreList");

    py::class_<TrouveCI>(m, "TrouveCI")
        .def(py::init<
            std::function<double(Vecteur)>,
            const std::string
        >(),
        py::arg("f"),
        py::arg("nomCible")
        )
        .def_readwrite("astres" ,  &TrouveCI::astres)
        .def_readwrite("satellite" ,  &TrouveCI::satellite)
        .def("recherche", &TrouveCI::recherche)
        .def_readwrite("paramsOpti" , &TrouveCI::paramsOpti)
        .def("getNbSims" , &TrouveCI::getNbSims);
}
