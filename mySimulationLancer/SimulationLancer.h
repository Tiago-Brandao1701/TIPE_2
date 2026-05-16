#ifndef SIMULARION_LANCER_H
#define SIMULARION_LANCER_H

#include <vector>
#include <cmath>
#include <iostream>

#include "Vecteur.h"
#include "Astre.h"
#include "Logique.h"
#include "ParamsLancer.h"
#include "cstes.h"

/*
Cette classe gere la simulation d'un lancer de satellite d'apres les paramsLancer:
Initialisation:
    -Le satellite est crée, et puis la construction normale
    -Tout astre dans astres contient une trajectoire simulée dans un environment sans le satellite
Pendant l'éxecution du code, a chaque fois que la fonction simulation est appelée:
Début:
    -ParamsLancer est mis a jour
    -Graces aux nouveaux params, la position et vitesse du satellite est mis a jour avec 
    trouvePosSatellite et trouveVitesseSatellite
    -Le temps t est remis a 0
    -Le nombre de points à simuler est déterminé en fonction de la vitesse et de la distance
    à la cible (trouveNbPts) 
Pendant la simulation:
    -L'influence du satellite sur tout astre est négligée, ceci nous permet d'avoir un pfd en
    O(n) au lieu de O(n^2) en utilisant les trajectoires enregistrées dans chaque astre de astres
    -La trajectoire du satellite est enregistrée au fur et à mesure
*/

class SimulationLancer{
public:
    ParamsLancer paramsLancer;
    SimulationLancer (
        std::vector<Astre>& astres,
        const Astre& cible,
        const Astre& terre
);
    void initTrajectoires ();
    std::vector<Vecteur> simulation();
    int nbSimulations;
    Astre getSatellite();
    void updateCI(ParamsLancer newParams);

private:
    std::vector<Astre>& astres;
    const Astre& cible;
    const Astre& terre;
    Astre satellite;
    int nbPts;
    int t;
    bool initTrajAstres;

    void trouveNbPts();
    Vecteur trouvePosSatellite() const;
    Vecteur trouveVitesseSatellite() const;
    Astre creeSatellite();
    void update();
};

#endif