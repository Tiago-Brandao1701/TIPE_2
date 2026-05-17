#include <pybind11/pybind11.h>
#include <pybind11/functional.h>
#include "ComparaisonCourbe.h"

namespace py = pybind11;

PYBIND11_MODULE(myComparaisonCourbe,m){

    m.def("score", &ComparaisonCourbe::score, "Calcule un score sur une liste de vecteurs");
    py::class_<ComparaisonCourbe>(m, "ComparaisonCourbe")
        .def(py::init<>())  // constructeur par défaut
        .def_static("score", &ComparaisonCourbe::score,
                    py::arg("courbe"),py::arg("nbPts"), py::arg("fonction"))
        .def_static("trouveDistMin", &ComparaisonCourbe::trouveDistMin,
                    py::arg("courbe"));
}