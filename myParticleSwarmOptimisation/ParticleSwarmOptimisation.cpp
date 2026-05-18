#include "ParticleSwarmOptimisation.h"
#include <limits>

ParticleSwarmOptimisation::ParticleSwarmOptimisation(
    SimulationLancer& simulationLancer,
    std::function<double(Vecteur)> f,
    Bornes bornes
)
    : simulationLancer(simulationLancer),
      f(f),
      bornes(bornes),
      meilleurCoutGlobal(std::numeric_limits<double>::infinity()),
      gen(std::random_device{}()),
      dist01(0.0, 1.0),
      aPointDepart(false),
      pointDepart()
{
    initialiserEssaim();
}

ParticleSwarmOptimisation::ParticleSwarmOptimisation(
    SimulationLancer& simulationLancer,
    std::function<double(Vecteur)> f,
    Bornes bornes,
    const ParamsLancer& pointDepart
)
    : simulationLancer(simulationLancer),
      f(f),
      bornes(bornes),
      meilleurCoutGlobal(std::numeric_limits<double>::infinity()),
      gen(std::random_device{}()),
      dist01(0.0, 1.0),
      aPointDepart(true),
      pointDepart(pointDepart)
{
    initialiserEssaim();
}

double ParticleSwarmOptimisation::cout(const ParamsLancer& params) {
    simulationLancer.paramsLancer = params;
    std::vector<Vecteur> courbe = simulationLancer.simulation();
    return ComparaisonCourbe::score(courbe, simulationLancer.nbPts, f);
}

double ParticleSwarmOptimisation::alea(double min, double max) {
    return min + (max - min) * dist01(gen);
}

//Borne les essais des particules
void ParticleSwarmOptimisation::borner(ParamsLancer& p) {
    if (p.phi < bornes.min.phi) p.phi = bornes.min.phi;
    if (p.phi > bornes.max.phi) p.phi = bornes.max.phi;

    if (p.theta < bornes.min.theta) p.theta = bornes.min.theta;
    if (p.theta > bornes.max.theta) p.theta = bornes.max.theta;

    if (p.vitesse < bornes.min.vitesse) p.vitesse = bornes.min.vitesse;
    if (p.vitesse > bornes.max.vitesse) p.vitesse = bornes.max.vitesse;
}

//Initialise toutes les particules
void ParticleSwarmOptimisation::initialiserEssaim() {
    essaim.clear();

    for (int i = 0; i < nbParticules; i++) {
        Particule p;

        if (i == 0 && aPointDepart) {
            p.position = pointDepart;
            borner(p.position);
        } else {
            p.position.phi = alea(bornes.min.phi, bornes.max.phi);
            p.position.theta = alea(bornes.min.theta, bornes.max.theta);
            p.position.vitesse = alea(bornes.min.vitesse, bornes.max.vitesse);
        }

        p.vitesse.phi = alea(
            -0.1 * (bornes.max.phi - bornes.min.phi),
             0.1 * (bornes.max.phi - bornes.min.phi)
        );

        p.vitesse.theta = alea(
            -0.1 * (bornes.max.theta - bornes.min.theta),
             0.1 * (bornes.max.theta - bornes.min.theta)
        );

        p.vitesse.vitesse = alea(
            -0.1 * (bornes.max.vitesse - bornes.min.vitesse),
             0.1 * (bornes.max.vitesse - bornes.min.vitesse)
        );

        p.meilleurePosition = p.position;
        p.meilleurCout = cout(p.position);

        if (p.meilleurCout < meilleurCoutGlobal) {
            meilleurCoutGlobal = p.meilleurCout;
            meilleurePositionGlobale = p.position;
        }

        essaim.push_back(p);
    }
}

ParamsLancer ParticleSwarmOptimisation::recherche() {
    printf("Debut PSO \n");
    for (int i = 0; i < nbIterPSO; i++) {
        for (Particule& p : essaim) {
            //Generation des params lancer
            //initialisation des distributions normales
            double r1phi = dist01(gen);
            double r2phi = dist01(gen);
            double r1theta = dist01(gen);
            double r2theta = dist01(gen);
            double r1vitesse = dist01(gen);
            double r2vitesse = dist01(gen);
            //calcul des differents params selon les formules de l'algo
            p.vitesse.phi =
                inertie * p.vitesse.phi
                + coefCognitif * r1phi * (p.meilleurePosition.phi - p.position.phi)
                + coefSocial * r2phi * (meilleurePositionGlobale.phi - p.position.phi);
            p.vitesse.theta =
                inertie * p.vitesse.theta
                + coefCognitif * r1theta * (p.meilleurePosition.theta - p.position.theta)
                + coefSocial * r2theta * (meilleurePositionGlobale.theta - p.position.theta);
            p.vitesse.vitesse =
                inertie * p.vitesse.vitesse
                + coefCognitif * r1vitesse * (p.meilleurePosition.vitesse - p.position.vitesse)
                + coefSocial * r2vitesse * (meilleurePositionGlobale.vitesse - p.position.vitesse);
            p.position.phi += p.vitesse.phi;
            p.position.theta += p.vitesse.theta;
            p.position.vitesse += p.vitesse.vitesse;
            //bornage
            borner(p.position);
            //Simulation
            double c = cout(p.position);
            //MAJ des meilleures positions et couts
            if (c < p.meilleurCout) {
                p.meilleurCout = c;
                p.meilleurePosition = p.position;
            }
            if (c < meilleurCoutGlobal) {
                meilleurCoutGlobal = c;
                meilleurePositionGlobale = p.position;
            }
        }
        if (i%10 == 0){
            printf ("iter: %d \n", i);
        }
    }
    return meilleurePositionGlobale;
}