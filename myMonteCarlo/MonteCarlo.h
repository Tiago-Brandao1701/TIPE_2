#ifndef MONTE_CARLO_H
#define MONTE_CARLO_H

#include <vector>
#include <functional>
#include <random>
#include <iostream>

#include "Vecteur.h"
#include "ParamsLancer.h"
#include "Bornes.h"
#include "SimulationLancer.h"
#include "cstes.h"
#include "ComparaisonCourbe.h"

/*
Simule nbEssais trajectoires aleatoirement et trouve les meilleus params parmis ces essais
*/

class MonteCarlo {
public:
    ParamsLancer paramsOpti;
    Bornes bornes;
    MonteCarlo(
        ParamsLancer paramsOpti,
        Bornes bornes,
        std::function<double(Vecteur)> f,
        SimulationLancer& lancer);
    ParamsLancer recherche ();
    double coutOpti;

private:
    const int nbEssais;
    std::vector<Vecteur> courbe;
    std::function<double(Vecteur)> f;
    SimulationLancer& lancer;
    double randDouble (const double min, const double max) const;
    ParamsLancer randParamsLancer () const;
    
};

#endif
