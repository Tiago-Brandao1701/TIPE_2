#include "MonteCarlo.h"

MonteCarlo::MonteCarlo(
    ParamsLancer paramsOpti,
    Bornes bornes,
    std::function<double(Vecteur)> f,
    SimulationLancer& lancer
)
    : paramsOpti(paramsOpti),
      bornes(bornes),
      coutOpti(doubleInfini),
      nbEssais(nbEssaisMonteCarlo),
      courbe(),
      f(f),
      lancer(lancer)
{}

double MonteCarlo::randDouble (const double min, const double max) const{
    std::random_device rd;                       
    std::mt19937 gen(rd());                         
    std::uniform_real_distribution<double> dist(min, max);  
    return dist(gen);
}

ParamsLancer MonteCarlo::randParamsLancer () const {
    double phi = randDouble(bornes.min.phi, bornes.max.phi);
    double theta = randDouble(bornes.min.theta, bornes.max.theta);
    double vitesse = randDouble(bornes.min.vitesse, bornes.max.vitesse);
    return ParamsLancer(phi,theta,vitesse);
}

ParamsLancer MonteCarlo::recherche(){
    std::cout << "debut Monte Carlo \n" << std::endl;
    double coutLancer;
    for (int i = 0; i<nbEssais; i++){
        lancer.paramsLancer = randParamsLancer();
        courbe = lancer.simulation();
        coutLancer = ComparaisonCourbe::score(courbe, lancer.nbPts, f);
        if (coutLancer<coutOpti){
            coutOpti = coutLancer;
            paramsOpti = lancer.paramsLancer;
        }
        if (i%10 == 0){
            std::cout << "essai " << i << std::endl;
            printf("cout opti %f \n", coutOpti);
        }
    }
    std::cout << std::endl;
    return paramsOpti;
}
