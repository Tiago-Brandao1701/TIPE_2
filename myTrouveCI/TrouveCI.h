#ifndef TROUVE_CI_H
#define TROUVE_CI_H

#include <functional>
#include <vector>
#include <string>
#include <stdio.h>

#include "ParamsLancer.h"
#include "MonteCarlo.h"
#include "Astre.h"
#include "cstes.h"
#include "SimulationLancer.h"
#include "Bornes.h"
#include "Vecteur.h"
#include "CreeAstres.h"
#include "DescenteGradient.h"
#include "ParticleSwarmOptimisation.h"

/*
Ce module est la base de toute la logique de recherche des concditions initiales
C'est le module qui fait le lien principal (et un des peus liens) avec python
Pour l'instant, seulement une methode de recherche MonteCarlo (aleatoire) est implémentée,
dans le futur, je vais faire une méthode de descente du gradient et PSO
*/

class TrouveCI {
public:
    ParamsLancer paramsOpti;
    TrouveCI(
        std::function<double(Vecteur)> f,
        const std::string nomCible
    );
    ParamsLancer recherche();
    int getNbSims() const;
    std::vector<Astre> astres;
    Astre satellite;

private:
    Astre& cible;
    Astre& terre;
    std::function<double(Vecteur)> f;
    Bornes bornes;
    SimulationLancer lancer;
    MonteCarlo monteCarlo;
    DescenteGradient descenteGradient;

    Astre& identifieAstre (const std::string nomAstre);
    void updateAllBornes(const Bornes newBornes);
    void donneesPourPython ();
};

#endif
