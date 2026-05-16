// bindings_astre.cpp
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include "Astre.h"
#include "Vecteur.h"

namespace py = pybind11;

PYBIND11_MAKE_OPAQUE(std::vector<Vecteur>);
PYBIND11_MAKE_OPAQUE(std::vector<Astre>);

PYBIND11_MODULE(myAstre, m) {
    
    py::bind_vector<std::vector<Vecteur>>(m, "VecteurList");
    py::bind_vector<std::vector<Astre>>(m, "AstreList");

    py::class_<Astre>(m, "Astre")
        .def(py::init<const std::string&, const std::string&, int, double,
                      const Vecteur&, const Vecteur&>(),
             py::arg("nom") = "", py::arg("couleur") = "", py::arg("taille_aff") = 0, py::arg("mass") = 0,
             py::arg("pos") = Vecteur(), py::arg("vitesse") = Vecteur())
        .def("distance", &Astre::distance)
        .def("move", &Astre::move)
        .def_readwrite("nom", &Astre::nom)
        .def_readwrite("couleur", &Astre::couleur)
        .def_readwrite("taille_aff", &Astre::taille_aff)
        .def_readwrite("mass", &Astre::mass)
        .def_readwrite("pos", &Astre::pos)
        .def_readwrite("dr", &Astre::dr)
        .def_readwrite("vitesse", &Astre::vitesse)
        .def_readwrite("dv", &Astre::dv)
        .def_readwrite("trajectoire", &Astre::trajectoire)
        .def_readwrite("vitesseInitiale" , &Astre::vitesseInitiale);
}
