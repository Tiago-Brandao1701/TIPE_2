#include "TrouveCI.h"
#include <stdexcept>

TrouveCI::TrouveCI(
    const std::function<double(Vecteur)> f_,
    const std::string nomCible
)
    : paramsOpti(),
      astres(creeAstres()),
      satellite(),
      cible(identifieAstre(nomCible)),
      terre(identifieAstre("Terre")),
      f(f_),
      bornes(),
      lancer(astres, cible, terre),
      monteCarlo(paramsOpti, bornes, f_, lancer),
      descenteGradient(lancer, f_, ParamsLancer(0, 0, 0))
{}


Astre& TrouveCI::identifieAstre (const std::string nomAstre){
    for (Astre& astre : astres){
        if(astre.nom ==  nomAstre){
            return astre;
        }
    }
    throw std::runtime_error("Planete recherchée non trouvée dans identifieAstre");
}

void TrouveCI::updateAllBornes(const Bornes newBornes){
    monteCarlo.bornes = newBornes;
    bornes = newBornes;
}

int TrouveCI::getNbSims() const{
    return lancer.nbSimulations;
}

void TrouveCI::donneesPourPython (){
    lancer.paramsLancer = paramsOpti;
    lancer.simulation();
    satellite = lancer.getSatellite();
}

ParamsLancer TrouveCI::recherche (){
    updateAllBornes(
        Bornes(
            ParamsLancer(phiDebutMin, thetaDebutMin, vEvasionMin),
            ParamsLancer(phiDebutMax, thetaDebutMax, vEvasionMax)
        )
    );

    lancer.initTrajectoires();

    paramsOpti = monteCarlo.recherche();

    descenteGradient.paramsOpti = paramsOpti;
    descenteGradient.coutOpti = monteCarlo.coutOpti;

    printf("cout opti avant descente gradient %f\n", descenteGradient.coutOpti);

    paramsOpti = descenteGradient.recherche();

    ParticleSwarmOptimisation pso(lancer, f, bornes, paramsOpti);
    paramsOpti = pso.recherche();

    lancer.paramsLancer = paramsOpti;
    donneesPourPython();

    return paramsOpti;
}


