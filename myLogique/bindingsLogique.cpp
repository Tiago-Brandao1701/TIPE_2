#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include "Logique.h"
#include "Vecteur.h"
#include "Astre.h"

namespace py = pybind11;

PYBIND11_MODULE(myLogique, m) {

    py::class_<Logique>(m, "Logique")
        .def(py::init<>())  // constructeur par défaut
        .def_static("interac_grav", &Logique::interac_grav,
                    py::arg("pos1"), py::arg("pos2"), py::arg("mass1"), py::arg("mass2"),
                    "Calcule la force gravitationnelle entre deux objets.")
        .def_static("pfd", &Logique::pfd,
                    py::arg("astres"), py::arg("astre1"), py::arg("pos_astre"), py::arg("t"), py::arg("initTrajAstres"),
                    "Calcule l'accélération d'un astre dû aux autres.")
        .def_static("euler", &Logique::euler,
                    py::arg("astres"), py::arg("astre"), py::arg("t"), py::arg("initTrajAstres"),
                    "Méthode d'Euler pour la mise à jour des vitesses/positions.")
        .def_static("rk", &Logique::rk,
                    py::arg("astres"), py::arg("astre"), py::arg("t"), py::arg("initTrajAstres"),
                    "Méthode de Runge-Kutta pour la mise à jour des vitesses/positions.");
}