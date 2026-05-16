#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include "Vecteur.h"
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>


namespace py = pybind11;

PYBIND11_MAKE_OPAQUE(std::vector<Vecteur>);

PYBIND11_MODULE(myVecteur, m) {

    py::bind_vector<std::vector<Vecteur>>(m, "VecteurList");

    py::class_<Vecteur>(m, "Vecteur")
        .def(py::init<double, double, double>())
        .def("__add__", &Vecteur::operator+)
        .def("__sub__", &Vecteur::operator-)
        .def("__mul__", &Vecteur::operator*)
        .def("distance", &Vecteur::distance)
        .def("norme", &Vecteur::norme)
        .def("prod_vect", &Vecteur::prod_vect)
        .def_readwrite("x", &Vecteur::x)
        .def_readwrite("y", &Vecteur::y)
        .def_readwrite("z", &Vecteur::z);
}