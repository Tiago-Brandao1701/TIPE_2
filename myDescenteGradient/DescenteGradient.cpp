#include "DescenteGradient.h"

DescenteGradient::DescenteGradient(
    SimulationLancer& lancer_,
    std::function<double(Vecteur)> f_,
    ParamsLancer paramsOpti_
)
    : paramsOpti(paramsOpti_),
      coutOpti(doubleInfini),
      lancer(lancer_),
      pasApprentissage(pasApprentissageGradient),
      nbIter(nbIterDescenteGradient),
      t(0),
      f(f_),
      m(ParamsLancer(0, 0, 0)),
      v(ParamsLancer(0, 0, 0))
{}
ParamsLancer DescenteGradient::gradient(){
    lancer.paramsLancer = paramsOpti;
    std::cout << "vitesse: " <<paramsOpti.vitesse<<std::endl;
    std::vector<Vecteur> courbe;

    //Derivee partielle par rapport a phi
    lancer.paramsLancer.phi += dphi;
    courbe = lancer.simulation();
    double dpphi = (ComparaisonCourbe::score(courbe, f) - coutOpti)/dphi;
    lancer.paramsLancer.phi = paramsOpti.phi;
    
    //Derivee partielle par rapport a theta
    lancer.paramsLancer.theta += dtheta;
    courbe = lancer.simulation();
    double dptheta = (ComparaisonCourbe::score(courbe, f) - coutOpti)/dtheta;
    lancer.paramsLancer.theta = paramsOpti.theta;
    
    //Derivee partielle par rapport a vitesse
    lancer.paramsLancer.vitesse += dvitesse;
    courbe = lancer.simulation();
    double dpvitesse = (ComparaisonCourbe::score(courbe, f) - coutOpti)/dvitesse;
    lancer.paramsLancer.vitesse = paramsOpti.vitesse;
    
    return ParamsLancer(dpphi,dptheta,dpvitesse);
}


Vecteur DescenteGradient::gradientTest(Vecteur resultat){
    Vecteur trace = resultat;
    
    //Derivee partielle par rapport a phi
    resultat.x += dphi;
    double dpphi = (ComparaisonCourbe::test(resultat) - coutOpti)/dphi;
    resultat.x = trace.x;
    
    //Derivee partielle par rapport a theta
    resultat.y += dtheta;
    double dptheta = (ComparaisonCourbe::test(resultat) - coutOpti)/dtheta;
    resultat.y = trace.y;
    
    //Derivee partielle par rapport a vitesse
    resultat.z += dvitesse;
    double dpvitesse = (ComparaisonCourbe::test(resultat) - coutOpti)/dvitesse;
    resultat.z = trace.z;
    
    return Vecteur(dpphi,dptheta,dpvitesse);
}

Vecteur DescenteGradient::rechercheTest(){
    Vecteur resultat = Vecteur(2,2,2000);
    for (int i = 0; i<1000 && resultat.distance(Vecteur(10,10,2500)) > 1; i++){
        coutOpti = ComparaisonCourbe::test(resultat);
        printf("%f,%f,%f\n", resultat.x, resultat.y, resultat.z);
        resultat -= gradientTest(resultat)*pasApprentissageGradient;
    }
    return resultat;
}

ParamsLancer DescenteGradient::recherche(){
    std::cout << "Debut descente gradient " << std::endl;
    printf("cout %f", coutOpti);
    std::vector<Vecteur> courbe;
    for (int i = 0 ; i<nbIter && coutOpti > 10e6; i++){
        /*courbe = lancer.simulation();
        coutOpti = ComparaisonCourbe::score(courbe , f);
        std::cout << "Iteration: " << i << "\n" << "cout: " << coutOpti << std::endl;
        lancer.updateCI(paramsOpti);
        paramsOpti -= gradient()*pasApprentissageGradient;*/

        // Simulation
        std::vector<Vecteur> courbe = lancer.simulation();
        coutOpti = ComparaisonCourbe::score(courbe, f);

        std::cout << "Iteration: " << i 
                  << "  cout: " << coutOpti 
                  << "  phi: " << paramsOpti.phi
                  << "  theta: " << paramsOpti.theta
                  << "  v: " << paramsOpti.vitesse
                  << std::endl;

        // Mise à jour des conditions initiales
        lancer.updateCI(paramsOpti);

        // Gradient numérique
        ParamsLancer grad = gradient();

        // Mise à jour AdamW
        adamWUpdate(grad);
    }
    return paramsOpti;
}

void DescenteGradient::updateParamsOpti(){
    ParamsLancer grad = gradient();
    paramsOpti.phi -= grad.phi;
    paramsOpti.theta -= grad.theta;
    if (grad.vitesse > 0){
        paramsOpti.vitesse = std::min(paramsOpti.vitesse - grad.vitesse, vEvasionMin);
    }
    else {
        paramsOpti.vitesse = std::max(paramsOpti.vitesse - grad.vitesse, vEvasionMax);
    }
}

void DescenteGradient::adamWUpdate(const ParamsLancer grad) {
    t++;

    // --- Mise à jour des moments ---
    m.phi     = beta1 * m.phi     + (1 - beta1) * grad.phi;
    m.theta   = beta1 * m.theta   + (1 - beta1) * grad.theta;
    m.vitesse = beta1 * m.vitesse + (1 - beta1) * grad.vitesse;

    v.phi     = beta2 * v.phi     + (1 - beta2) * (grad.phi     * grad.phi);
    v.theta   = beta2 * v.theta   + (1 - beta2) * (grad.theta   * grad.theta);
    v.vitesse = beta2 * v.vitesse + (1 - beta2) * (grad.vitesse * grad.vitesse);

    // --- Correction du biais ---
    double mhat_phi     = m.phi     / (1 - std::pow(beta1, t));
    double mhat_theta   = m.theta   / (1 - std::pow(beta1, t));
    double mhat_vitesse = m.vitesse / (1 - std::pow(beta1, t));

    double vhat_phi     = v.phi     / (1 - std::pow(beta2, t));
    double vhat_theta   = v.theta   / (1 - std::pow(beta2, t));
    double vhat_vitesse = v.vitesse / (1 - std::pow(beta2, t));

    // --- Weight decay (AdamW) ---
    paramsOpti.phi     -= pasApprentissageGradient * weightDecay * paramsOpti.phi;
    paramsOpti.theta   -= pasApprentissageGradient * weightDecay * paramsOpti.theta;
    paramsOpti.vitesse -= pasApprentissageGradient * weightDecay * paramsOpti.vitesse;

    // --- Mise à jour des paramètres ---
    paramsOpti.phi     -= pasApprentissageGradient * mhat_phi
                  / (std::sqrt(vhat_phi) + epsilon);

    paramsOpti.theta   -= pasApprentissageGradient * mhat_theta
                  / (std::sqrt(vhat_theta) + epsilon);

    paramsOpti.vitesse -= pasApprentissageGradient * mhat_vitesse
                  / (std::sqrt(vhat_vitesse) + epsilon);

    paramsOpti.vitesse = std::clamp(paramsOpti.vitesse, vEvasionMin, vEvasionMax);
}
