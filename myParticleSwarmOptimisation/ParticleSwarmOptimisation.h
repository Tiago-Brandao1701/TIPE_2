#ifndef PARTICLE_SWARM_OPTIMISATION_H
#define PARTICLE_SWARM_OPTIMISATION_H

#include <vector>
#include <functional>
#include <random>
#include "SimulationLancer.h"
#include "ParamsLancer.h"
#include "ComparaisonCourbe.h"
#include "Vecteur.h"
#include "cstes.h"
#include "Bornes.h"

/*
Classe du PSO: Fait une recherche par PSO, il faut passer en argument la simulation, la fonction de cout f
et les bornes de l'espace de recherche
*/

class ParticleSwarmOptimisation{

public:
    ParticleSwarmOptimisation(
    SimulationLancer& simulationLancer,
    std::function<double(Vecteur)> f,
    Bornes bornes,
    const ParamsLancer& pointDepart
);

    ParticleSwarmOptimisation(
    SimulationLancer& simulationLancer,
    std::function<double(Vecteur)> f,
    Bornes bornes
);

    ParamsLancer recherche();

private:
    struct Particule {
        ParamsLancer position;  //Il ne s'agit pas de la position et vitesse dans la simulation mais oui dans
        ParamsLancer vitesse;   //l'espace de recherche
        ParamsLancer meilleurePosition;
        double meilleurCout;
    };
    SimulationLancer& simulationLancer;
    std::function<double(Vecteur)> f;
    
    Bornes bornes;
    std::vector<Particule> essaim;

    ParamsLancer meilleurePositionGlobale;
    double meilleurCoutGlobal;

    bool aPointDepart;
    ParamsLancer pointDepart;

    std::mt19937 gen;
    std::uniform_real_distribution<double> dist01;

    double cout(const ParamsLancer& params);
    void initialiserEssaim();
    double alea(double min, double max);
    void borner(ParamsLancer& p);


};

#endif