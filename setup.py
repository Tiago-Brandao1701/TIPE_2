from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import pybind11
import shutil
import os
import sys


def platform_compile_args():
    # MSVC flags vs GCC/Clang flags
    if sys.platform == "win32":
        return ["/std:c++latest", "/EHsc"]
    else:
        # WSL/Linux (g++/clang++)
        return ["-std=c++20", "-O3", "-Wall"]  # tu peux passer à -std=c++17 si besoin


EXTRA_COMPILE_ARGS = platform_compile_args()


class PostBuildExt(build_ext):
    def run(self):
        super().run()
        for ext in self.extensions:
            built_path = self.get_ext_fullpath(ext.name)  # .so on Linux, .pyd on Windows
            target_dir = ext.name  # "myVecteur", "myAstre", etc.
            os.makedirs(target_dir, exist_ok=True)
            shutil.move(built_path, os.path.join(target_dir, os.path.basename(built_path)))


setup(
    ext_modules=[
        Extension(  # myVecteur
            name="myVecteur",
            sources=[
                "myVecteur/Vecteur.cpp",
                "myVecteur/bindingsVecteur.cpp",
            ],
            include_dirs=[
                "myVecteur",
                pybind11.get_include(),
            ],
            language="c++",
            extra_compile_args=EXTRA_COMPILE_ARGS,
        ),
        Extension(  # myAstre
            name="myAstre",
            sources=[
                "myAstre/Astre.cpp",
                "myAstre/bindingsAstre.cpp",
                "myVecteur/Vecteur.cpp",
            ],
            include_dirs=[
                "myAstre",
                "myVecteur",
                pybind11.get_include(),
            ],
            language="c++",
            extra_compile_args=EXTRA_COMPILE_ARGS,
        ),
        Extension(  # myParamsLancer
            name="myParamsLancer",
            sources=[
                "myParamsLancer/ParamsLancer.cpp",
                "myParamsLancer/bindingsParamsLancer.cpp",
            ],
            include_dirs=[
                "myParamsLancer",
                pybind11.get_include(),
            ],
            language="c++",
            extra_compile_args=EXTRA_COMPILE_ARGS,
        ),
        Extension(  # myBornes
            name="myBornes",
            sources=[
                "myBornes/Bornes.cpp",
                "myBornes/bindingsBornes.cpp",
                "myParamsLancer/ParamsLancer.cpp",
            ],
            include_dirs=[
                "myBornes",
                "myParamsLancer",
                pybind11.get_include(),
            ],
            language="c++",
            extra_compile_args=EXTRA_COMPILE_ARGS,
        ),
        Extension(  # cstes
            name="cstes",
            sources=[
                "cstes/cstes.cpp",
                "cstes/bindingsCstes.cpp",
            ],
            include_dirs=[
                "cstes",
                pybind11.get_include(),
            ],
            language="c++",
            extra_compile_args=EXTRA_COMPILE_ARGS,
        ),
        Extension(  # myLogique
            name="myLogique",
            sources=[
                "myLogique/Logique.cpp",
                "myLogique/bindingsLogique.cpp",
                "myAstre/Astre.cpp",
                "myVecteur/Vecteur.cpp",
                "cstes/cstes.cpp",
            ],
            include_dirs=[
                "myLogique",
                "myAstre",
                "myVecteur",
                "cstes",
                pybind11.get_include(),
            ],
            language="c++",
            extra_compile_args=EXTRA_COMPILE_ARGS,
        ),
        Extension(  # myComparaisonCourbe
            name="myComparaisonCourbe",
            sources=[
                "myComparaisonCourbe/ComparaisonCourbe.cpp",
                "myComparaisonCourbe/bindingsComparaisonCourbe.cpp",
                "myVecteur/Vecteur.cpp",
            ],
            include_dirs=[
                "myComparaisonCourbe",
                "myVecteur",
                pybind11.get_include(),
            ],
            language="c++",
            extra_compile_args=EXTRA_COMPILE_ARGS,
        ),
        Extension(  # mySimulationLancer
            name="mySimulationLancer",
            sources=[
                "mySimulationLancer/SimulationLancer.cpp",
                "mySimulationLancer/bindingsSimulationLancer.cpp",
                "myVecteur/Vecteur.cpp",
                "myAstre/Astre.cpp",
                "myLogique/Logique.cpp",
                "myParamsLancer/ParamsLancer.cpp",
                "cstes/cstes.cpp",
            ],
            include_dirs=[
                "mySimulationLancer",
                "myVecteur",
                "myAstre",
                "myLogique",
                "myParamsLancer",
                "cstes",
                pybind11.get_include(),
            ],
            language="c++",
            extra_compile_args=EXTRA_COMPILE_ARGS,
        ),
        Extension(  # myMonteCarlo
            name="myMonteCarlo",
            sources=[
                "myMonteCarlo/MonteCarlo.cpp",
                "myMonteCarlo/bindingsMonteCarlo.cpp",
                "myBornes/Bornes.cpp",
                "mySimulationLancer/SimulationLancer.cpp",
                "myParamsLancer/ParamsLancer.cpp",
                "myAstre/Astre.cpp",
                "myLogique/Logique.cpp",
                "cstes/cstes.cpp",
                "myComparaisonCourbe/ComparaisonCourbe.cpp",
                "myVecteur/Vecteur.cpp",
            ],
            include_dirs=[
                "myMonteCarlo",
                "mySimulationLancer",
                "myBornes",
                "myParamsLancer",
                "myAstre",
                "myLogique",
                "cstes",
                "myComparaisonCourbe",
                "myVecteur",
                pybind11.get_include(),
            ],
            language="c++",
            extra_compile_args=EXTRA_COMPILE_ARGS,
        ),
        Extension(  # myTrouveCI
            name="myTrouveCI",
            sources=[
                "myTrouveCI/TrouveCI.cpp",
                "myTrouveCI/bindingsTrouveCI.cpp",
                "myMonteCarlo/MonteCarlo.cpp",
                "mySimulationLancer/SimulationLancer.cpp",
                "myVecteur/Vecteur.cpp",
                "myAstre/Astre.cpp",
                "myParamsLancer/ParamsLancer.cpp",
                "cstes/cstes.cpp",
                "myBornes/Bornes.cpp",
                "myCreeAstres/CreeAstres.cpp",
                "myLogique/Logique.cpp",
                "myComparaisonCourbe/ComparaisonCourbe.cpp",
                "myDescenteGradient/DescenteGradient.cpp",
                "myParticleSwarmOptimisation/ParticleSwarmOptimisation.cpp",
            ],
            include_dirs=[
                "myTrouveCI",
                "myMonteCarlo",
                "mySimulationLancer",
                "myVecteur",
                "myAstre",
                "myParamsLancer",
                "cstes",
                "myBornes",
                "myCreeAstres",
                "myLogique",
                "myComparaisonCourbe",
                "myDescenteGradient",
                "myParticleSwarmOptimisation",
                pybind11.get_include(),
            ],
            language="c++",
            extra_compile_args=EXTRA_COMPILE_ARGS,
        ),
        Extension(  # myTrajsTheoriques
            name="myTrajsTheoriques",
            sources=[
                "myTrajsTheoriques/TrajsTheoriques.cpp",
                "myTrajsTheoriques/bindingsTrajsTheoriques.cpp",
                "myVecteur/Vecteur.cpp",
                "cstes/cstes.cpp",
            ],
            include_dirs=[
                "myTrajsTheoriques",
                "myVecteur",
                "cstes",
                pybind11.get_include(),
            ],
            language="c++",
            extra_compile_args=EXTRA_COMPILE_ARGS,
        ),
        Extension(  # myCreeAstres
            name="myCreeAstres",
            sources=[
                "myCreeAstres/CreeAstres.cpp",
                "myCreeAstres/bindingsCreeAstres.cpp",
                "myAstre/Astre.cpp",
                "myVecteur/Vecteur.cpp",
            ],
            include_dirs=[
                "myCreeAstres",
                "myAstre",
                "myVecteur",
                pybind11.get_include(),
            ],
            language="c++",
            extra_compile_args=EXTRA_COMPILE_ARGS,
        ),
        Extension(  # myDescenteGradient
            name="myDescenteGradient",
            sources=[
                "myDescenteGradient/DescenteGradient.cpp",
                "myDescenteGradient/bindingsDescenteGradient.cpp",
                "mySimulationLancer/SimulationLancer.cpp",
                "myAstre/Astre.cpp",
                "myLogique/Logique.cpp",
                "myParamsLancer/ParamsLancer.cpp",
                "myVecteur/Vecteur.cpp",
                "myComparaisonCourbe/ComparaisonCourbe.cpp",
                "cstes/cstes.cpp",
            ],
            include_dirs=[
                "myDescenteGradient",
                "mySimulationLancer",
                "myAstre",
                "myLogique",
                "myParamsLancer",
                "myVecteur",
                "myComparaisonCourbe",
                "cstes",
                pybind11.get_include(),
            ],
            language="c++",
            extra_compile_args=EXTRA_COMPILE_ARGS,
        ),
                Extension(  # myParticleSwarmOptimisation
            name="myParticleSwarmOptimisation",
            sources=[
                "myParticleSwarmOptimisation/ParticleSwarmOptimisation.cpp",
                "myParticleSwarmOptimisation/bindingsParticleSwarmOptimisation.cpp",
                "mySimulationLancer/SimulationLancer.cpp",
                "myAstre/Astre.cpp",
                "myLogique/Logique.cpp",
                "myParamsLancer/ParamsLancer.cpp",
                "myBornes/Bornes.cpp",
                "myVecteur/Vecteur.cpp",
                "myComparaisonCourbe/ComparaisonCourbe.cpp",
                "cstes/cstes.cpp",
            ],
            include_dirs=[
                "myParticleSwarmOptimisation",
                "mySimulationLancer",
                "myAstre",
                "myLogique",
                "myParamsLancer",
                "myBornes",
                "myVecteur",
                "myComparaisonCourbe",
                "cstes",
                pybind11.get_include(),
            ],
            language="c++",
            extra_compile_args=EXTRA_COMPILE_ARGS,
        ),
    ],
    cmdclass={"build_ext": PostBuildExt},
    
)
