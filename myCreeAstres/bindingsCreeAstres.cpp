#include <pybind11/pybind11.h>
#include <pybind11/stl.h> 

#include "CreeAstres.h"

namespace py = pybind11;

PYBIND11_MODULE(myCreeAstres, m) {
    m.doc() = "Module for creating celestial objects (astres) from JSON data";
    m.def("creeAstres", &creeAstres, "Create astres from JSON data");
}