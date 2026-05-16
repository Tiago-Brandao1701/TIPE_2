#ifndef DESCENTE_GRADIENT
#define DESCENTE_GRADIENT

#include <functional>
#include <iostream>

#include "SimulationLancer.h"
#include "ParamsLancer.h"
#include "Vecteur.h"
#include "cstes.h"
#include "ComparaisonCourbe.h"

/*
Classe qui sert a approximer le resultat graces a une descente du gradient.
*/

class DescenteGradient{
public:
    ParamsLancer paramsOpti;
    double coutOpti;
    ParamsLancer recherche();
    DescenteGradient(
        SimulationLancer& lancer,
        std::function<double(Vecteur)> f,
        ParamsLancer paramsOpti
    );
    Vecteur rechercheTest();
private:
    ParamsLancer gradient();
    SimulationLancer& lancer;
    double pasApprentissage;
    int nbIter;
    int t;
    std::function<double(Vecteur)> f;
    Vecteur gradientTest(Vecteur resultat);
    void updateParamsOpti();
    void adamWUpdate (const ParamsLancer grad);
    ParamsLancer m;
    ParamsLancer v;
};

#endif